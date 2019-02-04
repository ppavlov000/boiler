#ifndef __TMP441
#define __TMP441
//-----------------------------------------------------------------------------------
//#include "..\define.h"
#include "..\..\System\Standard\types.h"
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
#define TMP441_reg_Manufacturer_ID				0xFE
#define TMP441_reg_Device_ID					0xFF
#define TMP441_reg_Local_T_H					0x00
#define TMP441_reg_Remote0_T_H					0x01
#define TMP441_reg_Remote0_T_L					0x11
#define TMP441_reg_Remote1_T_H					0x02
#define TMP441_reg_Remote1_T_L					0x12
#define TMP441_reg_BetaCompensation				0x0c

#define TMP441_reg_Config_1						0x09
#define TMP441_reg_Config_2						0x0A
#define TMP441_reg_Rate							0x0B
#define TMP441_reg_OneShot						0x0F
#define TMP441_reg_Local_T_L					0x10

//-----------------------------------------------------------------------------------
void TMP441_init();
void TMP441_write(u8 addr,u8* data, u8 len);
void TMP441_read(u8 addr,u8* data, u8 len);
//-----------------------------------------------------------------------------------
#endif
