//-----------------------------------------------------------------------------------
#include "..\Misc\types.h"
#include "fram31xx.h"
#include "..\main.h"
//-----------------------------------------------------------------------------------
TCTime	ft;
//	u8 i;
u8	Addr[2];
u8	Data[10];
u32 Fram_Addr;
//-----------------------------------------------------------------------------------
void fram_init()	// Must be done once
{	
	u8 tmp;
	tmp=0x00;	// Disable whatchdog
//	fram_mem_read(FRAM_STATUS,&tmp,1);
//	if((tmp & bit_fram_conf_done)==0)	// Fram is not configured
	{
		__sprintf(outtxt,"\n\r Configurating fram...\n\r");	
		tmp=0x8e;	// Enable whatchdog
//		tmp=0x0f;	// Disable whatchdog
		fram_comp_write(fram_reg_Watchdog_Control,&tmp,1);
		tmp=0x0a;
		fram_comp_write(fram_reg_Watchdog_Restart_Flags,&tmp,1);		
		
		tmp=0x1A;	// 3.9V level reset & full mem protection
		fram_comp_write(fram_reg_Companion_Control,&tmp,1);
	
		fram_comp_read(fram_reg_CAL_Control,&tmp,1);		
		tmp&=~0xC0;	// Oscilator enabled
		fram_comp_write(fram_reg_CAL_Control,&tmp,1);

		// Set up sign of configured fram
//		fram_mem_read(FRAM_STATUS,&tmp,1);
//		tmp|=bit_fram_conf_done;	// Set sign of configured fram
//		fram_mem_write(FRAM_STATUS,&tmp,1);		
	}
}
//-----------------------------------------------------------------------------------
void fram_mem_enable()	// Must be done once
{	
	u8 tmp;
	fram_comp_read(fram_reg_Companion_Control,&tmp,1);	
	tmp&=~0x18;	
	fram_comp_write(fram_reg_Companion_Control,&tmp,1);
}
//-----------------------------------------------------------------------------------
void fram_mem_disable()	// Must be done once
{	
	u8 tmp;
	fram_comp_read(fram_reg_Companion_Control,&tmp,1);	
	tmp|=0x18;	
	fram_comp_write(fram_reg_Companion_Control,&tmp,1);
}
//-----------------------------------------------------------------------------------
void fram_mem_write(u16 addr,u8* data, u16 len)
{
#if FRAM_ENABLE			
	Addr[0]=addr>>8;
	Addr[1]=addr;	
	I2C_NiMasterWrite(0xA2,Addr,2,data,len);
#endif	
}
//-----------------------------------------------------------------------------------
void fram_mem_read(u16 addr,u8* data, u16 len)
{
#if FRAM_ENABLE			
	Addr[0]=addr>>8;
	Addr[1]=addr;	
	I2C_NiMasterRead(0xA2,Addr,2,data,len);	
#endif		
}
//-----------------------------------------------------------------------------------
void fram_comp_write(u8 addr,u8* data, u16 len)
{
#if FRAM_ENABLE			
	Addr[0]=addr;
	Addr[1]=0;	
	I2C_NiMasterWrite(0xd2,Addr,1,data,len);
#endif		
}
//-----------------------------------------------------------------------------------
void fram_comp_read(u8 addr,u8* data, u16 len)
{
#if FRAM_ENABLE			
	Addr[0]=addr;
	Addr[1]=0;	
	I2C_NiMasterRead(0xd2,Addr,1,data,len);	
#endif		
}
//-----------------------------------------------------------------------------------
void fram_set_time(u8 hour,u8 minute,u8 second)
{
	u8 tmp,bcbh,bcbl,d[3];
	bcbh=hour/10;
	bcbl=hour-bcbh*10;
	hour=bcbh;
	hour=hour<<4;
	hour|=bcbl;	

	bcbh=minute/10;
	bcbl=minute-bcbh*10;
	minute=bcbh;
	minute=minute<<4;
	minute|=bcbl;	

	bcbh=second/10;
	bcbl=second-bcbh*10;
	second=bcbh;
	second=second<<4;
	second|=bcbl;	

	d[0]=second;
	d[1]=minute;
	d[2]=hour;

	tmp=fram_W;	// Write enable
	fram_comp_write(fram_reg_RTC_Control,&tmp,1);	
	
	fram_comp_write(fram_reg_Second,d,3);		
	
	tmp=0;	// Write disable
	fram_comp_write(fram_reg_RTC_Control,&tmp,1);		
}
//-----------------------------------------------------------------------------------
void fram_set_date(u8 year,u8 month, u8 date,u8 day)
{
	u8 tmp,bcbh,bcbl,d[4];
	
	if(year>99)year=0;
	if(month>12)month=0;
	if(date>31)date=0;
	if(day>7)day=0;
				
	bcbh=year/10;
	bcbl=year-bcbh*10;
	year=bcbh;
	year=year<<4;
	year|=bcbl;	

	bcbh=month/10;
	bcbl=month-bcbh*10;
	month=bcbh;
	month=month<<4;
	month|=bcbl;	

	bcbh=date/10;
	bcbl=date-bcbh*10;
	date=bcbh;
	date=date<<4;
	date|=bcbl;	

	d[0]=day;
	d[1]=date;
	d[2]=month;
	d[3]=year;
				
	tmp=fram_W;	// Write enable
	fram_comp_write(fram_reg_RTC_Control,&tmp,1);	
	fram_comp_write(fram_reg_Day,d,4);		
		
	tmp=0;	// Write disable
	fram_comp_write(fram_reg_RTC_Control,&tmp,1);			
}
//-----------------------------------------------------------------------------------
void fram_get_time()
{
	u8 tmp;//,bcbh,bcbl;
	
	tmp=fram_R;	// Read enable
	fram_comp_write(fram_reg_RTC_Control,&tmp,1);	
	fram_comp_read(fram_reg_Second,&ft.field.Second,7);
	tmp=0;		// Read disable
	fram_comp_write(fram_reg_RTC_Control,&tmp,1);		
	
	tmp=ft.field.Second>>4;tmp*=10;tmp+=ft.field.Second&0x0f;ft.field.Second=tmp;
	tmp=ft.field.Minute>>4;tmp*=10;tmp+=ft.field.Minute&0x0f;ft.field.Minute=tmp;
	tmp=ft.field.Hour>>4;tmp*=10;tmp+=ft.field.Hour&0x0f;ft.field.Hour=tmp;
	tmp=ft.field.Day>>4;tmp*=10;tmp+=ft.field.Day&0x0f;ft.field.Day=tmp;
	tmp=ft.field.Date>>4;tmp*=10;tmp+=ft.field.Date&0x0f;ft.field.Date=tmp;
	tmp=ft.field.Month>>4;tmp*=10;tmp+=ft.field.Month&0x0f;ft.field.Month=tmp;
	tmp=ft.field.Year>>4;tmp*=10;tmp+=ft.field.Year&0x0f;ft.field.Year=tmp;		
	MenuRegs.Time=ft;					
}
//-----------------------------------------------------------------------------------
void fram_watchdog_reset()
{
	u8 tmp;
	if(Time5==0)
	{
		Time5=MAX_WATCHDOG_TIME;
		// Watchdog reset
		tmp=0x0A;
		fram_comp_write(fram_reg_Watchdog_Restart_Flags,&tmp,1);	
	}
}
//-----------------------------------------------------------------------------------
void FGet2(u32 Addr,u8 *Data,u8 Len)
{
	u8 i;
	for(i=0;i<Len;i++)
	{
		*Data=*((u8 in_flash *)Addr+i);
		Data++;
	}
}
///-----------------------------------------------------------------------------------
// who-5 Params fields in eep
u32 CheckCRC(u8 who,u16 PARAM_LOCATION)
{
	u32 len,p,Addr;
	u16 crc;
	u8 ctmp;
	switch(who)
	{
		// Parameters
		case 0:
			Addr=PARAM_LOCATION;
			len=TPARAM_WIDTH-2;
			InitCRC(&crc);
			for(p=0;p<len;p++)	
			{
				fram_mem_read((u16)(Addr+p),&ctmp,1);
				CalcCRC(&ctmp,1,&crc);
			}
			EndCRC(&crc);
		break;
		// Main program header
		case 1:
			Addr=HPLM_FLASH_START;
			len=CRC_H_LOC;
			InitCRC(&crc);
			for(p=0;p<len;p++)	
			{
				FGet((Addr+p),&ctmp,1);
				CalcCRC(&ctmp,1,&crc);
			}
			EndCRC(&crc);
		break;
		// Main program body
		case 2:
			Addr=CODE_ADDR;
			FGet((HPLM_FLASH_START+LENGTH_LOC),(u8*)&len,4);
//			len=TPARAM_WIDTH-2;
			InitCRC(&crc);
			for(p=0;p<len;p++)	
			{
				FGet((Addr+p),&ctmp,1);
				CalcCRC(&ctmp,1,&crc);
			}
			EndCRC(&crc);
		break; 		
	 }
	return crc;
}

//-----------------------------------------------------------------------------------
