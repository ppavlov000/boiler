//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
TTime	ft;
u8	Addr[2];
u8	Data[10];
u32 Fram_Addr;
//-----------------------------------------------------------------------------------
void fram_init()	// Must be done once
{
	u8 tmp;
	tmp=0x00;	// Disable whatchdog
//	if((tmp & bit_fram_conf_done)==0)	// Fram is not configured
	{
		sprintf(outtxt,"\n\r Configurating fram...\n\r");
		tmp=0x8e;	// Enable whatchdog
//		tmp=0x0f;	// Disable whatchdog
		fram_comp_write(fram_reg_Watchdog_Control,&tmp,1);
		tmp=0x0a;
		fram_comp_write(fram_reg_Watchdog_Restart_Flags,&tmp,1);

		tmp=0x1A;	// 3.9V level reset
		fram_comp_write(fram_reg_Companion_Control,&tmp,1);

		fram_comp_read(fram_reg_CAL_Control,&tmp,1);
		tmp&=~0xC0;	// Oscilator enabled
		fram_comp_write(fram_reg_CAL_Control,&tmp,1);
	}
}
//-----------------------------------------------------------------------------------
void fram_mem_write(u16 addr,u8* data, u8 len)
{
	Addr[0]=addr>>8;
	Addr[1]=addr;
	I2C_NiMasterWrite(0xA0,Addr,2,data,len);
}
//-----------------------------------------------------------------------------------
void fram_mem_read(u16 addr,u8* data, u8 len)
{
	Addr[0]=addr>>8;
	Addr[1]=addr;
	I2C_NiMasterRead(0xA0,Addr,2,data,len);
}
//-----------------------------------------------------------------------------------
void fram_comp_write(u8 addr,u8* data, u8 len)
{
	Addr[0]=addr;
	Addr[1]=0;
	I2C_NiMasterWrite(0xd0,Addr,1,data,len);
}
//-----------------------------------------------------------------------------------
void fram_comp_read(u8 addr,u8* data, u8 len)
{
	Addr[0]=addr;
	Addr[1]=0;
	I2C_NiMasterRead(0xd0,Addr,1,data,len);
}
//-----------------------------------------------------------------------------------
void fram_watchdog_reset()
{
	u8 tmp;
	if(Time5==0)
	{
		Time5=MAX_WATCHDOG_TIME;
	}
}
//-----------------------------------------------------------------------------------
void FGet2(u32 Addr,u8 *Data,u8 Len)
{
	u8 i;
	for(i=0;i<Len;i++)
	{
		*Data=*((u8 __farflash *)Addr+i);
		Data++;
	}
}
//-----------------------------------------------------------------------------------
// who-5 Params fields in eep
u32 CheckCRC2(u8 who)
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
				FGet2((Addr+p),&ctmp,1);
				CalcCRC(&ctmp,1,&crc);
			}
			EndCRC(&crc);
		break;
	 }
	return crc;
}
//-----------------------------------------------------------------------------------
