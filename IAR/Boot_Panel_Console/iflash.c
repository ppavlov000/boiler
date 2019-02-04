#include "main.h"
#include "spm.h"
//-----------------------------------------------------------------------------------
  u8 i;
  u16 j,itmp;
  u8 *ptr;
  u8 c;
  u8 sector[SECTOR_SIZEB];
  u16 bs=0;
	u32 Flash_Addr;
  u8 header=1;	
  u8 APPFLASH *fptr;	
//-----------------------------------------------------------------------------------
void flash_reenable_page(void)
{
  while(SPMCSR & (1<<SPMEN));
  __DataToR0ByteToSPMCR_SPM(0,(1<<RWWSRE)|(1<<SPMEN));
}
//-----------------------------------------------------------------------------------
u8 Flash_Read(u32 Addr)
{
  u8 tmp;
  ptr=(u8*)Addr;
  tmp=*ptr;
  return tmp;
}
//-----------------------------------------------------------------------------------
void StoreSector()
{
	u32 Addr;
	Addr=Flash_Addr;
	// Store sector
	Addr&=0xffffff00;
	bs=0;
	for(j=0;j<SECTOR_SIZEW;j++)
	{
//    *((u8*)Addr)=sector[j];
		fptr=(u8 APPFLASH *)Addr;
		itmp=sector[2*j]+(sector[2*j+1]<<8);
		if(key==0x55AA7733)
			spmWriteWord(fptr,itmp);		
    	Addr+=2;
	}
	Addr=Flash_Addr;
	Addr&=0xffffff00;
	fptr=(u8 APPFLASH *)Addr;
    if(key==0x55AA7733)
		spmErasePage(fptr);
	if(key==0x55AA7733)
		spmProgramPage(fptr);
//	Delay(20);
  	Flash_Addr+=SECTOR_SIZEB;
}
//-----------------------------------------------------------------------------------
void Flash_Start_Write(u32 Addr)
{
  bs=0;
  Flash_Addr=Addr;
}
//-----------------------------------------------------------------------------------
u8 Flash_Write(u8 *Data,u8 Size)
{
  switch(header)
  {
    case 1:
      header=0;
      Flash_Write_Sector(HAPP_FLASH_START,Data,Size);
    break;
    case 2:
      header=0;
      Flash_Write_Sector(HPLM_FLASH_START,Data,Size);
    break;
    case 0:
      while(Size>0)
      {
        Size--;
        sector[bs]=*Data;
        bs++;
        Data++;
        if(bs>=SECTOR_SIZEB)
          StoreSector();
      }
     break;
    }
 	return 0;	// All ok
}
//-----------------------------------------------------------------------------------
void Flash_Write_Sector(u32 Addr,u8 *Data,u8 Size)
{
  fptr=(u8 APPFLASH *)Addr;
  while(Size>0)
  {
    itmp=*Data+(*(Data+1)<<8);
		spmWriteWord(fptr,itmp);
		fptr+=2;
    Data+=2;
    if(Size>2)
      Size-=2;
    else Size=0;
  }
  Addr&=0xffffff00;
  fptr=(u8 APPFLASH *)Addr;
  spmErasePage(fptr);
	spmProgramPage(fptr);
}
//-----------------------------------------------------------------------------------
void Flash_End_Write()
{
  if(bs!=0)// There is data in sector
  {
    StoreSector();
  }
  flash_reenable_page();
}
//-----------------------------------------------------------------------------------
void FGet(u8 *Data,u32 Addr,u8 Len)
{
  u8 i;
  for(i=0;i<Len;i++)
  {
    *Data=*((u8 APPFLASH *)Addr+i);
    Data++;
  }
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
  u8 u8tmp;
  switch(who)
  {
    case 1:
      Addr=HAPP_FLASH_START;
      FGet((u8*)&len,Addr+LENGTH_LOC,4);
      FGet((u8*)&crc,Addr+CRC_D_LOC,2);
      Addr=APPL_FLASH_START;
      InitCRC(&tmp);
      for(p=0;p<len;p++)
      {
        //u8tmp=*(u8 APPFLASH *)(Addr+p);
		FGet(&u8tmp,Addr+p,1);
        CalcCRC(&u8tmp,1,&tmp);
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
      for(p=0;p<len;p++)
      {
        //u8tmp=*(u8 APPFLASH *)(Addr+p);
		FGet(&u8tmp,Addr+p,1);
        CalcCRC(&u8tmp,1,&tmp);
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
      for(p=0;p<len;p++)
      {
        u8tmp=*(u8 APPFLASH *)(Addr+p);
        CalcCRC(&u8tmp,1,&tmp);
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
      for(p=0;p<len;p++)
      {
        u8tmp=*(u8 APPFLASH *)(Addr+p);
        CalcCRC(&u8tmp,1,&tmp);
        blink_booting();
      }
      EndCRC(&tmp);
    break;
   }
  return tmp;
}
//-----------------------------------------------------------------------------------
