//------------------------------------------------------------------------------
// Sourse EL programmable controller V031
//------------------------------------------------------------------------------
#ifndef __MAIN_H
#define __MAIN_H
//------------------------------------------------------------------------------
#include "Misc\types.h"
#include "define.h"
#include "controller_data_define.h"
#include <string.h>
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#ifdef __ATMEL
	#include "..\Hardware_Atmel\lcd.h"
	#include "..\Hardware_Atmel\I2C\i2c.h"
// Choose exact hardware files
#endif
#ifdef __HW030
	#include "..\Custom\HW030\Hardware\functions.h"
	#include "..\Custom\HW030\Hardware\io.h"
	#include "..\Custom\HW030\LCD_Menu\menu.h"
	#include "..\Custom\HW030\Hardware\pinout.h"
#endif
#ifdef __HW031
	#include "..\Hardware_Atmel\functions.h"
	#include "..\Custom\HW031\Hardware\pinout.h"
	#include "..\Custom\HW031\Hardware\io.h"
	#include "..\Custom\HW031\LCD_Menu\menu.h"
#endif
#ifdef __HW0322
	#include "..\Hardware_Atmel\functions.h"
	#include "..\Custom\HW0322\Hardware\pinout.h"
	#include "..\Custom\HW0322\Hardware\io.h"
	#include "..\Custom\HW0322\LCD_Menu\menu.h"
#endif
#ifdef __HW0323
	#include "..\Hardware_Atmel\functions.h"
	#include "..\Custom\HW0323\Hardware\pinout.h"
	#include "..\Custom\HW0323\Hardware\io.h"
	#include "..\Custom\HW0323\LCD_Menu\menu.h"
#endif
#ifdef __HW0324
	#include "..\Hardware_Atmel\functions.h"
	#include "..\Custom\HW0324\Hardware\pinout.h"
	#include "..\Custom\HW0324\Hardware\io.h"
	#include "..\Custom\HW0324\LCD_Menu\menu.h"
#endif
#ifdef __HW0325
	#include "..\Hardware_Atmel\functions.h"
	#include "..\Custom\HW0325\Hardware\pinout.h"
	#include "..\Custom\HW0325\Hardware\io.h"
	#include "..\Custom\HW0325\LCD_Menu\menu.h"
#endif
#ifdef __HW0326
	#include "..\Hardware_Atmel\functions.h"
	#include "..\Custom\HW0326\Hardware\pinout.h"
	#include "..\Custom\HW0326\Hardware\io.h"
	#include "..\Custom\HW0326\LCD_Menu\menu.h"
#endif
#ifdef __HW050
	#include "..\Hardware_Atmel\functions.h"
	#include "..\Custom\HW050\Hardware\pinout.h"
	#include "..\Custom\HW050\Hardware\io.h"
	#include "..\Custom\HW050\LCD_Menu\menu.h"
#endif

#ifdef __SIMULATOR
	#include "..\Hardware_Simulator\functions.h"
	#include "..\Hardware_Simulator\lcd.h"
	#include "..\Hardware_Simulator\io.h"
	#include "..\Hardware_Simulator\I2C\i2c.h"
#endif

#include "Console\console.h"
#include "Console\str.h"
#include "Timer\timer16.h"
#include "Memory\fram31xx.h"
#include "Memory\eep.h"
#include "Pid\pid.h"

#ifdef __COMPILER2
	#include "Compiler2\Compiler2.h"
#else
	#include "Compiler\Compiler.h"
#endif

#include "IO\adc.h"
#include "TMP441\TMP441.h"

#include "Xmodem\xmodem.h"
#include "Service\plm.h"
#include "Misc\header.h"

#include "Misc\crc.h"
//#include "crc_modbus.h"
//#include "math.h"
//#include "can.h"
//#include <ctype.h>
#include "Service\errors.h"
#include "RS485_Slave\uart_misc.h"
#include "RS485_Slave\uart_protocol.h"
//#include "protection.h"
//------------------------------------------------------------------------------
//#define _SEASON_DATE
//------------------------------------------------------------------------------
// Parameters record
//------------------------------------------------------------------------------
#define PARAM_LOCATION_0 0x0002
#define PARAM_LOCATION_1 0x0100
#define TPARAM_WIDTH sizeof(TParam)
//------------------------------------------------------------------------------
typedef struct
{
	TController	CV;
	u16 CRC;
}TParam;
//------------------------------------------------------------------------------
extern TController CV;
//------------------------------------------------------------------------------
extern in_flash u8	mdic[][80];
//------------------------------------------------------------------------------
eu8 Cycle;
eu16 Error_Code;
//extern TParam DevParams;
eu8 Flag;
eu8 Test_Mode;
eu8 To_Store;
//-----------------------------------------------------------------------------------
extern u8 ID;
//extern TIO io;
//extern TPID pid[NUM_PID];
extern TInterpretatorRegisters intr;
//extern TErrors errors;
//------------------------------------------------------------------------------
void params_store();
void params_load();
void cycle_handler();
void task_handler(u8 Command, u16 Parameter);
void Immediately_DO();
void idle();
void init();
void id_store();
void id_read();
//------------------------------------------------------------------------------
#endif
