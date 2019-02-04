#include "main.h"
#include <intrinsics.h>
#include <iom16c62p.h>

//-----------------------------------------------------------------------------------
// Flash section
//-----------------------------------------------------------------------------------
#define BLOCK_A 		0xF000	// 4KB: F000 - FFFF
#define BLOCK_A_SIZE	4096

#define SYS_Err_FlashErase		(-100)
#define SYS_Err_FlashWrite		(-101)
#define SYS_Err_FlashArg		(-102)

#define Ok	1

//--------------------------------------------------------------------------
typedef struct {
	uchar prcr;
//	uchar pm0;
	uchar pm1;
	uchar cm1;
} CHCLK_SAVE, *pCHCLK_SAVE;

typedef void  (*FLASH_RAM_ERASE_F)(usint volatile *);
typedef uchar (*FLASH_RAM_WRITE_F)(usint volatile *, usint *, usint);

//--------------------------------------------------------------------------
//
//----------------------------------
void Sys_SlowClock(pCHCLK_SAVE save)
{
	// Unprotect registers CM0 and CM1 and PM0 registers by writting to protection register
	save->prcr = PRCR;		// Save Protection register
	PRCR = 3;				// Allow writting to protected system registers

    save->cm1 = CM1;		// Save cm1 regsiter
    save->pm1 = PM1;		// Save pm1 regsiter

	// Insert Wait state for all bus access (needed for talking to the
	// internal flash controller)
	PM1_bit.PM17 = 1;

#if (BCLK_CLOCK <= 10000000)
	// NO NEED TO SLOW DOWN CLOCK
#elif (BCLK_CLOCK <= 20000000)
	// Set main clock divide by 2
	CM1_bit.CM16 = 1;
	CM1_bit.CM17 = 0;
#elif (BCLK_CLOCK <= 40000000)
	// Set main clock divide by 4
	CM1_bit.CM16 = 0;
	CM1_bit.CM17 = 1;
#endif
}

//--------------------------------------------------------------------------
//
//----------------------------------
void Sys_RestoreClock(pCHCLK_SAVE save)
{
    CM1 = save->cm1;		// restore cm0 
    PM1 = save->pm1;		// Restore pm1 register

    PRCR = save->prcr;		// Protection back on
}

//--------------------------------------------------------------------------
//
//----------------------------------
void sys_flash_ram_erase(usint volatile *flash_addr)
{
	FMR0_bit.FMR01 = 0;
	FMR0_bit.FMR01 = 1;		// Set EW0 select bit

	// ! DISABLE ALL FLASH MEMORY LOCK AND PROTECT FUNCTIONALITY !
	// NOTE: In order to use lock/protect bit functionality, please refer to
	// the Flash Memory section in the data sheet for your specific device.
	// Also note the that following bits clear back to 0 every time you enter
	// CPU Rewrite Mode.
	// Note that for some MCUs, if the lock bit is disabled, the error bits
	// do not function.

#if (PROTECT_BITS)
	FMR0_bit.FMR02 = 0;
	FMR0_bit.FMR02 = 1;		// Must write a 0 then a 1 in succession to SET 	
	// Some devices have an extra bit to unprotect all blocks
	FMR1_bit.FMR16 = 0;
	FMR1_bit.FMR16 = 1;		// Must write a 0 then a 1 in succession to SET 	
#endif

	*flash_addr = 0x50;		// Clear status register
	*flash_addr = 0x20;		// Send erase command
	*flash_addr = 0xD0;		// Send erase confirm command

	// Note: In EW0 Mode, we need to poll the Ready/Busy bit until the operation completed
	while(!FMR0_bit.FMR00)	// wait for ready bit if executing in RAM for EW0 mode
#ifdef USE_WATCHDOG
		WDTS = 0;
#else
		;
#endif

	*flash_addr = 0xFF;		// Send Read Array command in order to tell flash controller
							// to go back into Flash Read mode (as opposed to Read Status mode)

	// Disable CPU rewriting commands by clearing EW entry bit
	*((usint *)&FMR0) = 0;
	asm("nop");
	asm("nop");
	asm("nop");
}

//--------------------------------------------------------------------------
__monitor sint Sys_FlashEraseEW0(usint volatile *flash_addr)
{
	CHCLK_SAVE rs;

	// Allocate RAM space to hold the CPU-Rewrite code on the stack
	unsigned char EW0_RamCode[256];

	// Copy code to RAM
	memcpy(EW0_RamCode, (void *)sys_flash_ram_erase, sizeof(EW0_RamCode));

	// Must change main clock speed to meet flash requirements
	Sys_SlowClock(&rs);

	// execute erase 
	((FLASH_RAM_ERASE_F)EW0_RamCode)(flash_addr);

	// restore system clock
	Sys_RestoreClock(&rs);

	if(FMR0_bit.FMR07)				// Erasing error?
		return SYS_Err_FlashErase;

	return Ok;
}

//--------------------------------------------------------------------------
//
//----------------------------------
uchar sys_flash_ram_write(usint volatile *flash_addr, usint *data, usint size)
{
	uchar ret_value;

	ret_value = 0;

	FMR0_bit.FMR01 = 0;
	FMR0_bit.FMR01 = 1;		// Set EW0 select bit

	// ! DISABLE ALL FLASH MEMORY LOCK AND PROTECT FUNCTIONALITY !
	// NOTE: In order to use lock/protect bit functionality, please refer to
	// the Flash Memory section in the data sheet for your specific device.
	// Also note the that following bits clear back to 0 every time you enter
	// CPU Rewrite Mode.
	// Note that for some MCUs, if the lock bit is disabled, the error bits
	// do not function.

#if (PROTECT_BITS)
	FMR0_bit.FMR02 = 0;
	FMR0_bit.FMR02 = 1;		// Must write a 0 then a 1 in succession to SET 	
	// Some devices have an extra bit to unprotect all blocks
	FMR1_bit.FMR16 = 0;
	FMR1_bit.FMR16 = 1;		// Must write a 0 then a 1 in succession to SET 	
#endif

	*flash_addr = 0x50;			// Clear status register

	while (size) {
		// Write to the flash sequencer by writting to that area of flash memory
		*flash_addr = 0x40;		// Send write command
		*flash_addr = *data;	// Write next word of data

		// Note: In EW0 Mode, we need to poll the Ready/Busy bit until the operation completed
		while(!FMR0_bit.FMR00)	// wait for ready bit if executing in RAM for EW0 mode
#ifdef USE_WATCHDOG
		WDTS = 0;
#else
		;
#endif

		// Read flash program status flag
		if (FMR0_bit.FMR06) {	// Write error?
			ret_value = 1;		// Signal that we had got an error
			break;				// Break out of while loop
		}

		flash_addr++;			// Advance to next flash write address
		data++;					// Advance to next data buffer address

		size -= 2;				// Subract 2 from byte counter
	}

	*flash_addr = 0xFF;		// Send Read Array command in order to tell flash controller
							// to go back into Flash Read mode (as opposed to Read Status mode)

	// Disable CPU rewriting commands by clearing EW entry bit
	*((usint *)&FMR0) = 0;
	asm("nop");

	return ret_value;
}

//--------------------------------------------------------------------------
__monitor sint Sys_FlashWriteEW0(void *flash_addr, void *data,	usint size)
{
	uchar ret_value;

	CHCLK_SAVE rs;

	// Allocate RAM space to hold the CPU-Rewrite code on the stack
	unsigned char EW0_RamCode[256];

	// Check for odd number of bytes
	if (size&1)
		return SYS_Err_FlashArg;	// ERROR! You must always pass an even number of bytes.

	// Check for odd address
	if ((lint)flash_addr & 1)
		return SYS_Err_FlashArg;	// ERROR! You must always pass an even flash address

	// Copy code to RAM
	memcpy(EW0_RamCode, (void *)sys_flash_ram_write, sizeof(EW0_RamCode));

	// Must change main clock speed to meet flash requirements
	Sys_SlowClock(&rs);

	// execute write
	ret_value = ((FLASH_RAM_WRITE_F)EW0_RamCode)(flash_addr, data, size);

	// restore system clock
	Sys_RestoreClock(&rs);

	return ret_value?SYS_Err_FlashWrite:Ok;
}


vu8 Ready_for_programming=0;
vu8 Programming_Finished=0;
vu8 data_len;
vu16 data_packet_number;
vu16 data_packet_number_old;
vu8 data_status=0;
vu8 data[128];
THead *head;
u8 xmod_status;
//-----------------------------------------------------------------------------------
void Flash_Downloader()
{
//	if (upc_check_rx())
//		upc_RXHandler();

	if(Ready_for_programming && upc.done)
	{
		// Checking WH Version !!!!
		if(xmod_status!=0)
		{
			xmod_status=0;		
			if(xmod_status==1)ltmp=HAPP_FLASH_START;
			if(xmod_status==2)ltmp=HPLM_FLASH_START;
			head=(THead*)&data[0];
//	lc		if(head->WH_Update==0) 
			if(data[THWF_LOC] == 0) // lc
			{
				FGet((u8*)&ltmp,ltmp+THW_LOC,4);
//	lc			if(head->HW_Version!=ltmp)
				if( memcmp((void *)&data[THW_LOC], &ltmp, 4) && 
					ltmp != 0xffffffffUL) // lc
					return;
			}
		}	
//		sprintf(outtxt,"\n\r N "); WordToStr(outtxt,&data_packet_number,0);
		if(data_packet_number==(data_packet_number_old+1))
		{
			Flash_Write((u8*)&data[0],data_len);
			data_packet_number_old=data_packet_number;
		}
		Ready_for_programming=0;
	}
	if(Programming_Finished)
	{
		stat=check_flash_images();
		Programming_Finished=0;
	}
}

//-----------------------------------------------------------------------------------

//u8 i;
//u16 j,itmp;
//u8 *ptr;
//u8 c;  
//u8 sector[SECTOR_SIZEB];
//u16 bs=0;
u32 Flash_Addr;  
u8 header=1;	
//u8 APPFLASH *fptr;	

//-----------------------------------------------------------------------------------
/*
u8 Flash_Read(u32 Addr)
{
	u8 tmp;
	ptr = (u8*)Addr;
	tmp = *ptr;
	return tmp;
}
*/

//-----------------------------------------------------------------------------------
//void StoreSector()
//{
//    if (key==0x55AA7733)
//		Sys_FlashWriteEW0((void *)Flash_Addr, sector, SECTOR_SIZEB);

//  	Flash_Addr += SECTOR_SIZEB;
//	bs = 0;
//}

//-----------------------------------------------------------------------------------
void Flash_Start_Write(u32 Addr)
{
//	bs = 0;
	Flash_Addr = Addr;
}

//-----------------------------------------------------------------------------------
u8 Flash_Write(u8 *Data,u8 Size)
{
	switch (header) {
		case 1: // application
			header=0;
		    if (key==0x55AA7733) {
				Sys_FlashEraseEW0((usint volatile *)0xC0000);
				Sys_FlashEraseEW0((usint volatile *)0xD0000);
				Sys_FlashWriteEW0((void *)HAPP_FLASH_START, Data, Size);
			}
		break;
		case 2: // data
			header=0;
		    if (key==0x55AA7733) {
				Sys_FlashEraseEW0((usint volatile *)0xE0000);
				Sys_FlashEraseEW0((usint volatile *)0xF0000);
				Sys_FlashWriteEW0((void *)HPLM_FLASH_START, Data, Size);
			}
		break;
		case 0:
		    if (key==0x55AA7733) {
				Sys_FlashWriteEW0((void *)Flash_Addr, Data, Size);
			}
	
		  	Flash_Addr += Size;
		break;
	}
	return 0;	// All ok
}

//-----------------------------------------------------------------------------------
//void Flash_Write_Sector(u32 Addr, u8 *Data, u8 Size)
//{
//}

//-----------------------------------------------------------------------------------
void Flash_End_Write()
{
//	if (bs) { // There is data in sector
//		StoreSector();
//	}

//	flash_reenable_page();
}

//-----------------------------------------------------------------------------------
void FGet(u8 *Data,u32 Addr,u8 Len)
{
	memcpy(Data, (void *)Addr, Len);
}

//-----------------------------------------------------------------------------------
// who-1 Atmel data field
// who-2 Altera data field
// who-3 Atmel header field
// who-4 Altera header field
u32 CheckCRC(u8 who)
{
	u32 len,p,Addr;
	u16 crc,tmp;
	switch(who) {
		case 1:
			Addr=HAPP_FLASH_START;    
			FGet((u8*)&len,Addr+LENGTH_LOC,4);
			FGet((u8*)&crc,Addr+CRC_D_LOC,2);  
			Addr=APPL_FLASH_START;
			InitCRC(&tmp);
			for(p=0;p<len;p++) {
				ctmp=*(u8 APPFLASH *)(Addr+p);      
				CalcCRC(&ctmp,1,&tmp);
				blink_booting();
			}
			EndCRC(&tmp);  
		break;
		case 2:
			Addr=HPLM_FLASH_START;    
			FGet((u8*)&len,Addr+LENGTH_LOC,4);
			FGet((u8*)&crc,Addr+CRC_D_LOC,2);  
			Addr=PLM_FLASH_START;      
			InitCRC(&tmp);
			for(p=0;p<len;p++) {
				ctmp=*(u8 APPFLASH *)(Addr+p);
				CalcCRC(&ctmp,1,&tmp);
				blink_booting();
			}
			EndCRC(&tmp);  
		break; 
		case 3:
			Addr=HAPP_FLASH_START;
			len=126;
			FGet((u8*)&crc,Addr+CRC_H_LOC,2);  
			InitCRC(&tmp);
			Addr=HAPP_FLASH_START;      
			for(p=0;p<len;p++) {
				ctmp=*(u8 APPFLASH *)(Addr+p);
				CalcCRC(&ctmp,1,&tmp);
				blink_booting();
			}
			EndCRC(&tmp);
		break; 
		case 4:
			Addr=HPLM_FLASH_START;
			len=126;
			FGet((u8*)&crc,Addr+CRC_H_LOC,2);  
			InitCRC(&tmp);
			Addr=HPLM_FLASH_START;      
			for(p=0;p<len;p++) {
				ctmp=*(u8 APPFLASH *)(Addr+p);
				CalcCRC(&ctmp,1,&tmp);
				blink_booting();
			}
			EndCRC(&tmp);
		break; 
	}
	return tmp;
}

//-----------------------------------------------------------------------------------
