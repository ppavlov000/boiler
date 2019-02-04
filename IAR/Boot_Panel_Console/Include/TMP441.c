//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
u8 TMP441_Addr=0x9e;
//-----------------------------------------------------------------------------------
void TMP441_init()	// Must be done once
{	
	u8 tmp;
	tmp=0x00;	// Disable whatchdog
//	fram_mem_read(FRAM_STATUS,&tmp,1);
//	if((tmp & bit_fram_conf_done)==0)	// Fram is not configured
	{
		sprintf(outtxt,"\n\r Configurating TMP441...\n\r");	
	}
}
//-----------------------------------------------------------------------------------
void TMP441_write(u8 addr,u8* data, u8 len)
{
	I2C_NiMasterWrite(TMP441_Addr,&addr,1,data,len);
}
//-----------------------------------------------------------------------------------
void TMP441_read(u8 addr,u8* data, u8 len)
{
	I2C_NiMasterWrite(TMP441_Addr,&addr,1,0,0);
	I2C_NiMasterRead(TMP441_Addr,NULL,0,data,len);	
}
//-----------------------------------------------------------------------------------
