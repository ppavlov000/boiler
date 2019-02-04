#ifndef __MAIN
#define __MAIN
//-----------------------------------------------------------------------------------
//#define __LEDNOE
//#define __SHEVCHENKO
#define __SWITCH_TO_ID_1			// Switching to First id in list
//#define __ID_BUTTON			
//#define __ID_BUTTON		

#define __WEEK_SCHEDULE_ENABLE			// Week schedule menu	
#define __CHOKE_ENABLE					// Choke menu
#define __RECUPERATOR_ENABLE			// Recuperator menu
#define __MODBUS_ENA			1
//-----------------------------------------------------------------------------------
//#define __DEBUG
#define __RELEASE
//#define _TEST_BAD_COMMUNICATION	
//#define _TEST_TOUCH
//-----------------------------------------------------------------------------------
#ifdef __RENESAS
	#include "..\Hardware_Renesas\pinout.h"
	#include "..\Hardware_Renesas\memory.h"
	#include "..\Hardware_Renesas\functions.h"
#else
	#include "..\Hardware_Atmel\pinout.h"
	#include "..\Hardware_Atmel\memory.h"
	#include "..\Hardware_Atmel\functions.h"
#endif
#include <string.h>
#include "..\..\System\Standard\sys_define.h"
#include "..\..\System\Standard\types.h"
#include "..\..\..\Controller\System\controller_data_define.h"
#include "..\..\System\Standard\panel_data_define.h"
#include "..\..\System\Standard\protocol.h"
#include "Misc\crc.h"
//#include "Uart\console.h"
#include "Service\service.h"
#include "TSC2046\tsc2046.h"
#include "Uart\str.h"
#include "Timer\timer16.h"
#include "T6963\t6963.h"
#include "BMP\bmp.h"
#include "IO\io.h"
#include "RS485_Master\RS485_M_misc.h"
#include "RS485_Master\RS485_M_protocol.h"

#include "RS485_Slave\RS485_S_protocol.h"
#include "MODBUS_Slave\MODBUS_S_protocol.h"
#include "Misc\crc_modbus.h"

#ifdef __TP010
	#include "..\Hardware_Atmel\I2C\i2c.h"
	#include "TMP441\TMP441.h"
	#define TMP441_ENABLE 0
#endif
#ifdef __TP020
	#include "..\Hardware_Atmel\I2C\i2c.h"
	#include "TMP441\TMP441.h"
	#define TMP441_ENABLE 1
#endif

//-----------------------------------------------------------------------------------
#define	Err_NO						0x0000
#define	Err_BAD_EEPROM_RECORD		0x0001
//-----------------------------------------------------------------------------------
#define PARAM_LOCATION 0x00
#define TPARAM_WIDTH sizeof(TPanelParam)
//-----------------------------------------------------------------------------------
typedef struct
{
	TCoff coff;
	u8 BackLit_Value_Max;
	u8 BackLit_Value_Min;	
	u8 Sleep_Time;	
	TTime Alarm;
	u8 Alarm_Status;
	u8 Address;	
	TTime ft;	
	TDimmer Dimmer;	
	TTimeFieldsShort sch[7][2];
	u8 sch_auto_manual; // 0 - auto
	u8 sch_day_night;
	s16 sch_temperature[2]; 	// Day Night temperatures
	s16 adjust_temperature[2];
	s16 gradient_temperature;
	s16 sch_fan_speed[2]; 		// Day Night fan speed
	u8 sch_mode[2]; 			// Day Night on / off
	u8 sch_enable[7]; 			// Each Day Night change enable
	u8 sch_param_ena[3]; 		// Choose parameter updating
	u16 pritochka_speed;	
	u8 TMP441_Channel;
	u8 image_position;
}TMain;
#define pritochka_fan_speed  m.pritochka_speed
//-------------------------------------------------------------------------------------------
typedef struct
{
	TMain m;
	u16 CRC;
}TPanelParam;
//-----------------------------------------------------------------------------------
extern TMain m;
extern TTime ft;
extern u8 envitation[20];
extern __farflash u8	Main_Dict[11][40];
//-----------------------------------------------------------------------------------
eu8 Cycle;
eu16 Error_Code;
eu8 Flag;
eu8 Test_Mode;
extern TWorkInfo WorkInfo;
//-----------------------------------------------------------------------------------
//eu8 Status;
//#define bit_Packet_Received		0x01
//-----------------------------------------------------------------------------------
uchar params_get();
void params_store();
void params_load();
//-----------------------------------------------------------------------------------
#endif
