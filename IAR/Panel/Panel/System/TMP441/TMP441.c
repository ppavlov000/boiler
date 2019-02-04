//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
u8 TMP441_Addr=0x9e;
//-----------------------------------------------------------------------------------
#ifdef __TP020
void __sprintf(u8 *str1,u8 *str2)
{}
#endif
//-----------------------------------------------------------------------------------
void TMP441_init()	// Must be done once
{	
#if TMP441_ENABLE	
	u8 tmp;
	tmp=0x00;	// Disable whatchdog
//	fram_mem_read(FRAM_STATUS,&tmp,1);
//	if((tmp & bit_fram_conf_done)==0)	// Fram is not configured
	{
		__sprintf(outtxt,"\n\r Configurating TMP441...\n\r");	
		tmp=0x0f;
		TMP441_write(TMP441_reg_BetaCompensation,&tmp,1);
		tmp=0x00;
		TMP441_write(TMP441_reg_Config_1,&tmp,1);
		tmp=0x1C;
		TMP441_write(TMP441_reg_Config_2,&tmp,1);
		tmp=0x03;
		TMP441_write(TMP441_reg_Rate,&tmp,1);
	}
#endif	
}
//-----------------------------------------------------------------------------------
void TMP441_write(u8 addr,u8* data, u8 len)
{
#if TMP441_ENABLE	
	I2C_NiMasterWrite(TMP441_Addr,&addr,1,data,len);
#endif	
}
//-----------------------------------------------------------------------------------
void TMP441_read(u8 addr,u8* data, u8 len)
{
#if TMP441_ENABLE		
	I2C_NiMasterWrite(TMP441_Addr,&addr,1,0,0);
	I2C_NiMasterRead(TMP441_Addr,NULL,0,data,len);	
#endif		
}
//-----------------------------------------------------------------------------------
