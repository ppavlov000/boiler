//-----------------------------------------------------------------------------------
#include <intrinsics.h>
#include <iom16c62p.h>
#include <stdio.h>
#include "functions.h"
#include "..\System\main.h"

#define Xin_CLOCK	16000000UL

#define PLL_CLOCK	(Xin_CLOCK * 1)

#define F1_CLOCK	PLL_CLOCK
#define F8_CLOCK	(F1_CLOCK/8)

//#define F2N_CLOCK	(Xin_CLOCK/30)

#define BCLK_CLOCK	PLL_CLOCK

#define TICKS_PER_SEC 1000

//#define USE_WATCHDOG	

__no_init u8 PanelAddress @ 0x400;

//-----------------------------------------------------------------------------------
#define Ok	1

//-----------------------------------------------------------------------------------
// Timer section
//-----------------------------------------------------------------------------------
u32 TickCnt;

void Timer_Init()
{
	TickCnt = 0;

	TABSR_bit.TA0S = 0; 	// stop timer

	TA0MR = 0x44;			// time mode, no gate, f8

	TA0 = F8_CLOCK / TICKS_PER_SEC - 1;

	TA0IC = 1;//PRIORITY_TICKS;	// set int level

	TABSR_bit.TA0S = 1; 	// start timer
}

//-----------------------------------------------------------------------------------
#pragma vector=TMRA0
__interrupt void Timer_IRQ()
{
//	__enable_interrupt();
	TickCnt++;
	Timer_1ms_IRQ();
}

//--------------------------------------------------------------------------
//
//----------------------------------
__monitor u32 Tick_Get(void)
{
	return TickCnt;
}

//--------------------------------------------------------------------------
//
//----------------------------------
u32 Tick_Check(u32 timer,u32 time)
{
	u32 t;
	t = Tick_Get();
	if (t < timer) {
		if (t > time) return 0L;
		time -= t;
		t = 0xFFFFFFFFUL;
	}
	t -= timer;
	if (t < time) return time-t;
	return 0L;
}

//-----------------------------------------------------------------------------------
void Delays(u16 val)// value in 10mks
{
	u8 i;
	while(val!=0)  
	{
		for (i=0;i<110;i++) //__no_operation();
			watchdog_reset();
		val--;
	}
}

//--------------------------------------------------------------------------
//
//----------------------------------
void lc_mem_dump(void *adr, u16 size)
{
	u8 *a, n, c;

	n = 0;
	a = (u8 *)adr;
	printf("\n\r");

	while (size--) {
		watchdog_reset();
		c = *a++;
		printf(" %02X", c);
		n++;

		if (!(n&0x0f))
			printf("\n\r");
	}
	printf("\n\r");
}

//-----------------------------------------------------------------------------------
// Flash section
//-----------------------------------------------------------------------------------
#define BLOCK_A 		0xF000	// 4KB: F000 - FFFF
#define BLOCK_A_SIZE	4096

#define SYS_Err_FlashErase		(-100)
#define SYS_Err_FlashWrite		(-101)
#define SYS_Err_FlashArg		(-102)

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
		size++;
//		return SYS_Err_FlashArg;	// ERROR! You must always pass an even number of bytes.

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

/*
//-----------------------------------------------------------------------------------
void EEErase(void)
{
	Sys_FlashEraseEW0((void *)BLOCK_A);
}

//-----------------------------------------------------------------------------------
void EEPut(u8 *Data,u16 Addr,u8 Len)
{
	if (Addr&1) Addr++;
	Sys_FlashWriteEW0((void *)(BLOCK_A + Addr), Data, Len);
}

//-----------------------------------------------------------------------------------
void EEGet(u8 *Data,u16 Addr,u8 Len)
{
	if (Addr&1) Addr++;
	memcpy(Data, (void *)(BLOCK_A + Addr), Len);
}
*/

//-----------------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------------
void lc_store_param(TMain *data)
{
	u16 crc;

	Sys_FlashEraseEW0((void *)BLOCK_A);
//printf("erase\n\r");
//lc_mem_dump((void *)BLOCK_A, sizeof(TMain));
	Sys_FlashWriteEW0((void *)BLOCK_A, data, sizeof(TMain));
//printf("write\n\r");
//lc_mem_dump((void *)BLOCK_A, sizeof(TMain));

	InitCRC(&crc);
	CalcCRC((u8 *)data, sizeof(TMain), &crc);
	EndCRC(&crc);
	
	Sys_FlashWriteEW0((void *)(BLOCK_A + BLOCK_A_SIZE - 2), &crc, sizeof(crc));

//printf("crc\n\r");
//lc_mem_dump(&crc, 2);
//lc_mem_dump((void *)(BLOCK_A + BLOCK_A_SIZE - 2), 2);
}


//-----------------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------------
u8 lc_load_param(TMain *data)
{
	u16 stored_crc, crc;

	memcpy(data, (void *)BLOCK_A, sizeof(TMain));
	memcpy(&stored_crc, (void *)(BLOCK_A + BLOCK_A_SIZE - 2), sizeof(stored_crc));
//printf("read\n\r");
//lc_mem_dump((void *)BLOCK_A, sizeof(TMain));

	InitCRC(&crc);
	CalcCRC((u8 *)data, sizeof(TMain), &crc);
	EndCRC(&crc);

//printf("crc\n\r");
//lc_mem_dump(&crc, 2);
//lc_mem_dump(&stored_crc, 2);

	return (stored_crc == crc)?1:0;
}


//-----------------------------------------------------------------------------------
// Flash section
//-----------------------------------------------------------------------------------
void FGet(u8 *Data, u32 Addr, u16 Len)
{
	watchdog_reset();
	memcpy(Data, (void *)Addr, Len);
}
//-----------------------------------------------------------------------------------
void GetFlashStr(u8 *word,u8 *ptr)
{
	watchdog_reset();
	strcpy((char *)word, (char *)ptr);
}

//-----------------------------------------------------------------------------------
// Console section
//-----------------------------------------------------------------------------------
#define UARTCON_RxBufferSize 128
#define UARTCON_RxBufferMask (UARTCON_RxBufferSize - 1)
#if (UARTCON_RxBufferSize & UARTCON_RxBufferMask)
#error RX buffer size is not a power of 2
#endif

//--------------------------------------------------------------------------
typedef struct {
//  unsigned char Tmp;
  unsigned char RxBuf[UARTCON_RxBufferSize];
  unsigned char RxPut;
  unsigned char RxGet;
  unsigned char RxSize;
} UARTCON;

UARTCON	UartCon;

void con_hardware_init(u32 baund)
{
	memset(&UartCon, 0, sizeof(UartCon));
	
	// --- pin settings ----------------------------------------
	// TXD1 out
	PD6_bit.PD6_7 = 1;

	// RXD1 in
	PD6_bit.PD6_6 = 0;

	//--- Special Mode Registers -------------------------------
	U1SMR  = 0;
	U1SMR2 = 0;
	U1SMR3 = 0;
	U1SMR4 = 0;

	//--- Baud Rate Register -----------------------------------
	U1BRG = (F1_CLOCK / (baund * 16)) - 1;

	//--- Transmit/Receive Mode Register -----------------------
	U1MR_bit.SMD0 = 1;	// mode UART 8bit
	U1MR_bit.SMD1 = 0;
	U1MR_bit.SMD2 = 1;

	U1MR_bit.CKDIR = 0;	// internal clock

	U1MR_bit.STPS = 0;	// 1 stop bit

//	U1MR_bit.PRY = 0;	// 0 : Odd parity / 1 : Even parity
	U1MR_bit.PRYE = 0;	// disable parity

	U1MR_bit.IOPOL = 0;	// not inversed

	//--- Transmit/Receive Control Register 0 ------------------
	U1C0_bit.CLK0 = 0;	// 0 1: Selects f8
	U1C0_bit.CLK1 = 0;

//	U1C0_bit.CRS = 0;	// 0 : Selects CTS function / 1 : Selects RTS function
	U1C0_bit.CRD = 1;	// Disables CTS/RTS function

	U1C0_bit.NCH = 0;	// 0 : TxDi/SDAi and SCLi are ports for the CMOS output

	U1C0_bit.CKPOL = 0;	// 0 : tx on the falling edge rx on the rising edge

	U1C0_bit.UFORM = 0;	// 0 : LSB first / 1 : MSB first

	//--- Transmit/Receive Control Register 1 ------------------
	U1C1_bit.TE = 1;	// Transmit enable
	U1C1_bit.TI = 0;	// 

	U1C1_bit.RE = 1;	// Receive enable

//	U1C1_bit.U1RRM = 0;

	U1C1_bit.U1LCH = 0;	// Data Logic Select Bit 0: Not inversed / 1: Inverse

//	U1C1_bit.U1ERE = 0;	// 

    UCON_bit.U1IRS	= 0;
    UCON_bit.U1RRM	= 0;
    UCON_bit.CLKMD0	= 0;
    UCON_bit.CLKMD1	= 0;
//    UCON_bit.RCSP	= 0;

	S1RIC = 2;//PRIORITY_UART1;
}

//--------------------------------------------------------------------------
#pragma vector=UART1_RX
__interrupt void UartCon_RxInt(void)
{
	usint buf;

//	__enable_interrupt();

	buf = U1RB;

	if (UartCon.RxSize < UARTCON_RxBufferSize) {// && !(buf&0x8000)) {
		UartCon.RxBuf[UartCon.RxPut] = buf & 0xff;
		UartCon.RxPut++;
		UartCon.RxPut &= UARTCON_RxBufferMask;
		UartCon.RxSize++;
	}
}
//-----------------------------------------------------------------------------------
u8 console_check_rx()	// if return value is 1 then something is in a buffer
{
	if (UartCon.RxSize) return 1;
	return 0;
}
//-----------------------------------------------------------------------------------
u8 console_check_tx()
{
	if (U1C1_bit.TI) return 1;
//	if(UCSR0A & (1<<TXC0))return 1;
	return 0;
}
//-----------------------------------------------------------------------------------
void console_clear_tx_flag()
{
//	UCSR0A|=(1<<TXC0);
}
//-----------------------------------------------------------------------------------
void console_tx_byte(u8 byte)
{
	while (!(U1C1_bit.TI)) 
		watchdog_reset();
	U1TB = (usint)(byte&0xff);
}
//-----------------------------------------------------------------------------------
int putchar(int c)
{
	console_tx_byte(c&0xff);
    return c;
}

//-----------------------------------------------------------------------------------
u8 console_rx_byte()
{
	u8 c;
	if (!UartCon.RxSize) return 0;
	c = UartCon.RxBuf[UartCon.RxGet];
	UartCon.RxGet++;
	UartCon.RxGet &= UARTCON_RxBufferMask;
	UartCon.RxSize--;
	return c;
}
//-----------------------------------------------------------------------------------
void console_wait_rx_new_byte()
{
	while (!UartCon.RxSize)
		watchdog_reset();
}
//-----------------------------------------------------------------------------------
void sendchar(u8 sym)
{
	outtxt[0]=sym;
	outtxt[1]=0;
	wait_con_free();
}
//-----------------------------------------------------------------------------------
s16 recchar()
{
	if (!UartCon.RxSize) return -1;
	return console_rx_byte();
}

//-----------------------------------------------------------------------------------
// Watchdog section
//-----------------------------------------------------------------------------------
void watchdog_init()
{
#ifdef USE_WATCHDOG
	WDC = 0x80;

	PRCR_bit.PRC1 = 1;	// enable write to PM

	PM1_bit.PM12 = 1;	// reset when the watchdog timer underflows
	PM2_bit.PM22 = 0;	// WDT Count Source: 0:CPU clock 1:On-chip oscillator

	PRCR_bit.PRC1 = 0;	// disable write

	WDC = 0x80;
#endif
}
//-----------------------------------------------------------------------------------
void watchdog_reset()
{
#ifdef USE_WATCHDOG
	WDTS = 0;
#endif
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void reset()
{
	PRCR_bit.PRC1 = 1; // enable write to PM

	PM0_bit.PM03  = 1; // software reset

	PRCR_bit.PRC1 = 0; // disable write to PM
//	while(1);
}

//-----------------------------------------------------------------------------------
// Buzzer section
//-----------------------------------------------------------------------------------
void beep_on()
{
}
//-----------------------------------------------------------------------------------
void beep_off()
{
}
//-----------------------------------------------------------------------------------
void beep_init()
{
}
//-----------------------------------------------------------------------------------
// PWM back light section 
//-----------------------------------------------------------------------------------
void set_backlight_pwm(u16 pwm_value)
{
//	TA1MR = 0x07;			// PWM mode, Pulse is output, 16 bit mode, f1

	TA1 = (pwm_value << 8) | 0x0b;

//	TABSR_bit.TA1S = 1; 	// start timer
//	OCR3A=pwm_value;
}
//-----------------------------------------------------------------------------------
// RS485 section
//-----------------------------------------------------------------------------------
//#define UART485_USE_RX_BUF

//--------------------------------------------------------------------------
#ifdef UART485_USE_RX_BUF

#define UART485_RxBufferSize 128
#define UART485_RxBufferMask (UART485_RxBufferSize - 1)
#if (UART485_RxBufferSize & UART485_RxBufferMask)
#error RX buffer size is not a power of 2
#endif

//--------------------------------------------------------------------------
typedef struct {
//  unsigned char Tmp;
  unsigned char RxBuf[UART485_RxBufferSize];
  unsigned char RxPut;
  unsigned char RxGet;
  unsigned char RxSize;
} UART485;

UART485	Uart485;
#endif

//-----------------------------------------------------------------------------------
void tx_mode()
{
	P6_bit.P6_5 = 1;
}

//-----------------------------------------------------------------------------------
void rx_mode()
{
	P6_bit.P6_5 = 0;
}

//-----------------------------------------------------------------------------------
void upc_hardware_init(u32 baund)
{
#ifdef UART485_USE_RX_BUF
	memset(&Uart485, 0, sizeof(Uart485));
#endif

	U0C1_bit.TE = 0;	// Transmit disable
	U0C1_bit.RE = 0;	// Receive disable

	// --- pin settings ----------------------------------------
	// TXD0 out
	PD6_bit.PD6_3 = 1;

	// RXD0 in
	PD6_bit.PD6_2 = 0;

	// nRx/Tx select
	PD6_bit.PD6_5 = 1;

	//--- Special Mode Registers -------------------------------
	U0SMR  = 0;
	U0SMR2 = 0;
	U0SMR3 = 0;
	U0SMR4 = 0;

	//--- Baud Rate Register -----------------------------------
	U0BRG = (F1_CLOCK / (baund * 16)) - 1;

	//--- Transmit/Receive Mode Register -----------------------
	U0MR_bit.SMD0 = 1;	// mode UART 8bit
	U0MR_bit.SMD1 = 0;
	U0MR_bit.SMD2 = 1;

	U0MR_bit.CKDIR = 0;	// internal clock

	U0MR_bit.STPS = 0;	// 1 stop bit

//	U0MR_bit.PRY = 0;	// 0 : Odd parity / 1 : Even parity
	U0MR_bit.PRYE = 0;	// disable parity

	U0MR_bit.IOPOL = 0;	// not inversed

	//--- Transmit/Receive Control Register 0 ------------------
	U0C0_bit.CLK0 = 0;	// 0 1: Selects f1
	U0C0_bit.CLK1 = 0;

//	U0C0_bit.CRS = 0;	// 0 : Selects CTS function / 1 : Selects RTS function
	U0C0_bit.CRD = 1;	// Disables CTS/RTS function

	U0C0_bit.NCH = 0;	// 0 : TxDi/SDAi and SCLi are ports for the CMOS output

	U0C0_bit.CKPOL = 0;	// 0 : tx on the falling edge rx on the rising edge

	U0C0_bit.UFORM = 0;	// 0 : LSB first / 1 : MSB first

	//--- Transmit/Receive Control Register 1 ------------------
	U0C1_bit.TE = 1;	// Transmit enable
	U0C1_bit.TI = 0;	// 

	U0C1_bit.RE = 1;	// Receive enable

//	U0C1_bit.U0RRM = 0;

	U0C1_bit.U0LCH = 0;	// Data Logic Select Bit 0: Not inversed / 1: Inverse

//	U0C1_bit.U0ERE = 0;	// 

    UCON_bit.U0IRS	= 0;
    UCON_bit.U0RRM	= 0;
    UCON_bit.CLKMD0	= 0;
    UCON_bit.CLKMD1	= 0;
    UCON_bit.RCSP	= 0;

	S0RIC = 2;
}

//-----------------------------------------------------------------------------------	
#pragma vector=UART0_RX
__interrupt void Uart485_RxInt(void)
{
#ifdef UART485_USE_RX_BUF
	usint buf;

//	__enable_interrupt();

	buf = U0RB;

	if (Uart485.RxSize < UART485_RxBufferSize) {// && !(buf&0x8000)) {
		Uart485.RxBuf[Uart485.RxPut] = buf & 0xff;
		Uart485.RxPut++;
		Uart485.RxPut &= UART485_RxBufferMask;
		Uart485.RxSize++;
	}
#endif
	upc_RXHandler();
}

//-----------------------------------------------------------------------------------	
void upc_tx_byte(u8 byte)
{
	while (!(U0C1_bit.TI))
		watchdog_reset();
	U0TB = (u16)(byte&0xff);
}

//-----------------------------------------------------------------------------------
u8 upc_rx_byte()
{
#ifdef UART485_USE_RX_BUF
	u8 c;

	if (!Uart485.RxSize) return 0;
	c = Uart485.RxBuf[Uart485.RxGet];
	Uart485.RxGet++;
	Uart485.RxGet &= UART485_RxBufferMask;
	Uart485.RxSize--;
	return c;
#else
	return U0RB & 0xff;
#endif
}

//-----------------------------------------------------------------------------------
u8 upc_check_tx()
{
	if (U0C1_bit.TI) return 1;
	return 0;
}

//-----------------------------------------------------------------------------------
u8 upc_check_tx_complite()
{
	if (U0C0_bit.TXEPT) return 1;
	return 0;
}

//-----------------------------------------------------------------------------------
void upc_clear_tx_flag()
{
//	UCSR1A|=(1<<TXC1);
}

//-----------------------------------------------------------------------------------
// io section
//-----------------------------------------------------------------------------------
void io_init()
{
}

//-----------------------------------------------------------------------------------
// TSK section
//-----------------------------------------------------------------------------------
#define ts_DCLK		P5_bit.P5_0
#define ts_DOUT		P5_bit.P5_1
#define ts_DIN		P5_bit.P5_2
#define ts_nCS		P5_bit.P5_3
#define ts_BUSY		P5_bit.P5_4

//--------------------------------------------------------------------------
void TSC_Init()
{
	PD5_bit.PD5_0 = 1; // DCLK
	PD5_bit.PD5_1 = 1; // DOUT
	PD5_bit.PD5_2 = 0; // DIN
	PD5_bit.PD5_3 = 1; // nCS
	PD5_bit.PD5_4 = 0; // BUSY

	ts_nCS  = 1;
	ts_DCLK = 0;
	ts_DOUT = 0;
}
//-----------------------------------------------------------------------------------
void no_operation()
{}

//--------------------------------------------------------------------------
u8 ts_rw(u8 din)
{
	u8 f, dout;

	f = 0x80;
	dout = 0;	

	while (f) {
		ts_DOUT = (din&f)?1:0;
		ts_DCLK = 1;

		dout <<= 1;
		if (ts_DIN) dout |= 0x01;

		ts_DCLK = 0;
		f >>= 1;
	}

//	dout <<= 1;
//	if (ts_DIN) dout |= 0x01;

	return dout;
}

//-----------------------------------------------------------------------------------
u16 TSC_Transfer(u8 control,u8 newcontrol)
{
	u16 n;

	__disable_interrupt();

	ts_nCS = 0;

	ts_rw(control | 0x80);
	n = ts_rw(0);
	n <<= 8;
	n |= ts_rw(0);
	n >>= 3;

	ts_nCS = 1;

	__enable_interrupt();

	return n;
}

//-----------------------------------------------------------------------------------
void hardware_init()
{
	__set_interrupt_level(0);

	//--- init Voltage Detection Register (VCR2) --------------
	PRCR_bit.PRC3 = 1;	// enable write

	VCR2 = 0xC0;

	PRCR_bit.PRC3 = 0;	// disable write

	//--- init system clock control register (CM1) ------------
	PRCR_bit.PRC0 = 1;	// enable write

	CM1_bit.CM10 = 0;	// all clock oscillates
	CM1_bit.CM11 = 0;	// use PLL clock

	CM1_bit.CM16 = 0;	// Main Clock Division: 1
	CM1_bit.CM17 = 0;	// 

	PRCR_bit.PRC0 = 0;	// disable write

	//--- init system clock control register (CM2) ------------
	PRCR_bit.PRC0 = 1;	// enable write

	CM2_bit.CM20 = 0;	// oscillation stop detect function

	PRCR_bit.PRC0 = 0;	// disable write

	//--- init system clock control register (CM0) ------------
	PRCR_bit.PRC0 = 1;	// enable write to 

	CM0_bit.CM00 = 0;	// CLKout mode f8
	CM0_bit.CM01 = 1;

	CM0_bit.CM02 = 0;	// no stop in WAIT mode

//	CM0_bit.CM03 = 1;	// Xcin - Xcout drive high
	CM0_bit.CM04 = 0;	// Xc work as IO port

	CM0_bit.CM05 = 0;	// main clock run

	CM0_bit.CM06 = 0;	// Main Clock Division: CM16 and CM17 enabled

	CM0_bit.CM07 = 0;	// System Clock Select Bit: Main clock

	PRCR_bit.PRC0 = 0;	// disable write

	//--- init processor mode (PM2) ---------------------------
//	PRCR_bit.PRC1 = 1;	// enable write to PM

//	PM2_bit.PM22 = 0;	// WDT Count Source: 1:On-chip oscillator

//	PRCR_bit.PRC1 = 0;	// disable write

	//--- Peripheral Clock Select Register (PCLKR) ------------
	PRCR_bit.PRC0 = 1;	// enable write to 

	PCLKR = 0x03;
//	PCLKR_bit.PCLK0 = 1;// Timers A, B Clock Select Bit: f1
//	PCLKR_bit.PCLK1 = 1;// SI/O Clock Select Bit: f1SIO

	PRCR_bit.PRC0 = 0;	// disable write

	//--- backlight -------------------------------------------
	TA1MR = 0x27;			// PWM mode, Pulse is output, 8 bit mode, f1

	TA1 = 0;

	TABSR_bit.TA1S = 1; 	// start timer

	//--- block a enable --------------------------------------
	PRCR_bit.PRC1 = 1;	// enable write

	PM1_bit.PM10  = 1;

	PRCR_bit.PRC1 = 0;	// disable write
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
u8 get_switch_state()
{
//	u8 tmp,i;
//	for(i=0;i<5;i++)
//	{
//		if((addr_pins & tmp)==0)
//		{
//			m.Address=i+1;
//			break;
//		}
//		tmp=tmp<<1;
//	}
//	tmp=addr_pins & 0x1f;
//	return tmp;
	m.Address = PanelAddress;
	return 0;
}

//-----------------------------------------------------------------------------------
void toggle_led()
{
//	if(PINB & 0x80)
//		PORTB&=~0x80;
//	else
//		PORTB|=0x80;	
}
//-----------------------------------------------------------------------------------
void enable_interrupt()
{
	__enable_interrupt();
}
//-----------------------------------------------------------------------------------
void disable_interrupt()
{
	__disable_interrupt();
}
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
#define lcd_Ctrl	P1
#define lcd_CtrlDir	PD1

#define lcd_Cmd		P1_bit.P1_0
#define lcd_nRd		P1_bit.P1_1
#define lcd_nWr		P1_bit.P1_2
#define lcd_nCe		P1_bit.P1_3
#define lcd_nReset	P1_bit.P1_4
#define lcd_nMD2	P1_bit.P1_5	// H: 32 columns ; L: 40 columns
#define lcd_FS1		P1_bit.P1_6	// H: 6*8, L: 8*8

#define lcd_Data	P0
#define lcd_DataDir	PD0

//--- Status Register Bits -------------------------------------------------
#define LCD_STATUS_BUSY1    0x01
#define LCD_STATUS_BUSY2    0x02
#define LCD_STATUS_DARRDY   0x04
#define LCD_STATUS_DAWRDY   0x08

#define LCD_STATUS_CLR      0x20
#define LCD_STATUS_ERR      0x40
#define LCD_STATUS_BLINK    0x80

#define LCD_STATUS_STD		(LCD_STATUS_BUSY1|LCD_STATUS_BUSY2)

/********************************************
 * Function name: initialise                *
 * Description:   Initialise PIC and LCD    *
 *******************************************/
void lcd_reset(void)
{
	//--- set p1 as output ----------------------------
	lcd_CtrlDir = 0xff;
	lcd_Ctrl    = 0xff;

	//-------------------------------------------------
	lcd_nReset = 1;
    Delay(100);
	lcd_nReset = 0;
    Delay(100);
	lcd_nReset = 1;
    Delay(100);

	//-------------------------------------------------
	lcd_nMD2   = 1; // H: 32 columns ; L: 40 columns
	lcd_FS1    = 0; // H: 6*8, L: 8*8

	lcd_nCe = 0;

//	lcd_init(); !!!
}

//--------------------------------------------------------------------------
void lcd_write(u8 data)
{
//	lcd_nCe = 0;
	lcd_DataDir = 0xff;

	lcd_nWr = 0;

	lcd_Data = data;

	lcd_nWr = 1;
//	lcd_nCe = 1;

//	lcd_DataDir = 0x00;
//	__no_operation();
}

//--------------------------------------------------------------------------
u8 lcd_read(void)
{
	u8 data;

	lcd_DataDir = 0x00;

//	lcd_nCe = 0;
	lcd_nRd = 0;

//	__no_operation();
	data = lcd_Data;

	lcd_nRd = 1;
//	lcd_nCe = 1;
	return data;
}

//--------------------------------------------------------------------------
//
//----------------------------------
u8 lcd_read_status(void)
{
//	lcd_wait(LCD_STATUS_STD);

	lcd_Cmd = 1;
	return lcd_read();
}

//-----------------------------------------------------------------------------------
uchar lcd_wait(uchar f)
{
	ulint t;
	t = Tick_Get();
	while ((lcd_read_status() & f) != f) {
		watchdog_reset();
		if (!Tick_Check(t, TICKS_PER_SEC*2))  return 0;
	}

	return 1;
}

//--------------------------------------------------------------------------
void lcd_write_command(u8 data)
{
	lcd_wait(LCD_STATUS_STD);

	lcd_Cmd = 1;
	lcd_write(data);
}

//--------------------------------------------------------------------------
void lcd_write_data(u8 data)
{
	lcd_wait(LCD_STATUS_STD);

	lcd_Cmd = 0;
	lcd_write(data);
}

//--------------------------------------------------------------------------
u8 lcd_read_data(void)
{
	lcd_wait(LCD_STATUS_STD);

	lcd_Cmd = 0;
	return lcd_read();
}

//-----------------------------------------------------------------------------------
