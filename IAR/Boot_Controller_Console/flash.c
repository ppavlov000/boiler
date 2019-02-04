#include "main.h"
#include "flash.h"
#include "xmodem.h"
#include "timer16.h"
#include "plm.h"
#include "inavr.h"
#include "eep.h"
#include "crc.h"
#include <iom128.h>
#include "header.h"
#include "console.h"
#include <string.h>
#include <stdlib.h>
//-----------------------------------------------------------------------------------
  u8 i;
  u16 j;
  u8 *ptr;
  u8 c;  
  u8 sector[SECTOR_SIZE];
  u16 bs=0;
	u32 Flash_Addr;  
//-----------------------------------------------------------------------------------
void ExtBus_Init()
{
  MCUCR|=0x80;
  XMCRA=0;//(1<<SRW01)+(1<<SRW11)+(1<<SRW00);
  XMCRB=0;
  PORTD=0xC0;
  DDRD=0xf0;
}
//-----------------------------------------------------------------------------------
u8 Flash_Read(u32 Addr)
{
  u8 tmp;
  Flash_Select();
  Flash_Set_HAddr(Addr);
  ptr=(u8*)Addr;
  tmp=*ptr;
  Flash_Deselect();
  return tmp;
}
//-----------------------------------------------------------------------------------
void Flash_Set_HAddr(u32 Addr)
{
  PORTD&=nb_MA16;  
  PORTD&=nb_MA17;
  if(Addr&0x00010000)
    PORTD|=b_MA16;  
  if(Addr&0x00020000)
    PORTD|=b_MA17;  
}
//-----------------------------------------------------------------------------------
void Flash_Select()
{
  PORTD=0x80;
}
//-----------------------------------------------------------------------------------
void Flash_Deselect()
{
  PORTD=0xC0;
}
//-----------------------------------------------------------------------------------
void StoreSector()
{
	u32 Addr;
  Flash_Set_HAddr(Flash_Addr);    	
	Addr=Flash_Addr;
  // Store sector
  Addr&=0xffffff00;      
  bs=0;      
  for(j=0;j<SECTOR_SIZE;j++)
  {
    *((u8*)Addr)=sector[j];
    Addr++;
  }
  Flash_Addr+=SECTOR_SIZE;      
  Delay(20);
}
//-----------------------------------------------------------------------------------
void Flash_Start_Write(u32 Addr)
{
  bs=0;
  Flash_Addr=Addr;
  Flash_Select();  
}
//-----------------------------------------------------------------------------------
u8 Flash_Write(u8 *Data,u8 Size)
{
  while(Size>0)
  {
    Size--;
    sector[bs]=*Data;
    bs++;
    Data++;
    if(bs>=SECTOR_SIZE)
      StoreSector();
  }
 	return 0;	// All ok
}
//-----------------------------------------------------------------------------------
void Flash_End_Write()
{
  if(bs!=0)// There is data in sector
  {
    StoreSector();
  }
  Flash_Deselect();
}
//-----------------------------------------------------------------------------------
void FGet(u8 *Data,u16 Addr,u8 Len)
{
  u8 i;
  for(i=0;i<Len;i++)
  {
    *Data= *((u8*)Addr+i);
    Data++;
  }
}
//-----------------------------------------------------------------------------------
u32 CheckCRC(u32 Addr)
{
  u32 len,p;
  u16 crc,tmp;
  Flash_Select();
  Flash_Set_HAddr(Addr);
  FGet((u8*)&len,Addr+8,4);
  FGet((u8*)&crc,Addr+12,2);  
  Addr+=14;
  InitCRC(&tmp);
  for(p=0;p<len;p++)  
  {
    CalcCRC(((u8*)Addr+p),1,&tmp);
  }
  EndCRC(&tmp);  
  Flash_Deselect();
  return tmp;
}
//-----------------------------------------------------------------------------------
