#include "plm.h"
#include "flash.h"
#include "timer16.h"
#include "inavr.h"
#include "header.h"
//-----------------------------------------------------------------------------------
void plm_reset()
{
  // Init ports
  PORTE|=(0<<dclk)+(0<<data0)+(1<<nconf);
  DDRE=b_dclk+b_data0+b_nconf;
  // Start config
  PORTE&=nb_nconf;
  Delay(10);
  PORTE|=b_nconf;  
}
//-----------------------------------------------------------------------------------
void plm_config(u32 plm_addr)
{
  u8 i,tmp,zn,flag=0;
  u32 len,maxaddr;

  Flash_Select();  
  FGet((u8*)&len,PLM_FLASH_START+8,4);  
  FGet((u8*)&flag,PLM_FLASH_START+7,1);    
  plm_addr+=THEAD_WIDTH;  
  maxaddr=plm_addr+len;
  // Init ports
  PORTE|=(0<<dclk)+(0<<data0)+(1<<nconf);
  DDRE=b_dclk+b_data0+b_nconf;
  // Start config
  PORTE&=nb_nconf;
  Delay(10);
  PORTE|=b_nconf;  
  Delay(1);  
  // wait nstat ==1
  while(!(PINE & b_nstat))
  {}
  Delay(1);
  zn=0;
  //for(j=0;j<len;j++)
  while(plm_addr<maxaddr)
  {
    // Load 1 byte
    if(flag==1)
    {
      if(zn==0)
      {
	      Flash_Set_HAddr(plm_addr);          
        tmp=*((u8*)plm_addr);
        plm_addr++; 
        if(tmp==0)
        {
    	  	Flash_Set_HAddr(plm_addr);            
          zn=*((u8*)plm_addr);
          plm_addr++;
          if(zn!=0)
            zn--;
        }
      }
      else
      {
        zn--;
        tmp=0;
      }
    }
    else
    {
      Flash_Set_HAddr(plm_addr);          
      tmp=*((u8*)plm_addr);
      plm_addr++; 
    }
    for(i=0;i<8;i++)
    {
      PORTE&=nb_dclk;    
//      __delay_cycles(10);          
      if(tmp & 1)
        PORTE|=b_data0;
      else
        PORTE&=nb_data0;
//      __delay_cycles(8);        
      PORTE|=b_dclk;
      tmp=tmp>>1;
     }
  }
  PORTE&=nb_dclk;
  PORTE&=nb_data0;  
  Flash_Deselect();  
}
//-----------------------------------------------------------------------------------
void Plm_Set_HAddr(u32 Addr)
{
  PORTD&=nb_MA16;  
  PORTD&=nb_MA17;
  if(Addr&0x00010000)
    PORTD|=b_MA16;  
  if(Addr&0x00020000)
    PORTD|=b_MA17;  
}
//-----------------------------------------------------------------------------------
void Plm_Select()
{
  PORTD=0x40;
}
//-----------------------------------------------------------------------------------
void Plm_Deselect()
{
  PORTD=0xC0;
}
//-----------------------------------------------------------------------------------
u8 Plm_Read(u32 Addr)
{
  u8 tmp,*ptr;
  Plm_Select();
  Plm_Set_HAddr(Addr);
  ptr=(u8*)Addr;
  tmp=*ptr;
  Plm_Deselect();
  return tmp;
}
