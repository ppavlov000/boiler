//------------------------------------------------------------------------------
#ifndef _ERRORS
#define _ERRORS
//------------------------------------------------------------------------------
#include "..\Memory\fram31xx.h"
//------------------------------------------------------------------------------
//#define ERRORS_I2C      	-450
//------------------------------------------------------------------------------
//#define ERRORS_EQUIPMENT   -300
//#define ERRORS_COMMON   -400
//#define ERRORS_I2C      -450
//#define ERRORS_SI2C     -500
//#define ERRORS_CLI      -550
//#define ERRORS_HYNIX    -600
//#define ERRORS_I2CCMD   -650
//------------------------------------------------------------------------------
//#define COMMON_Err_Config           (ERRORS_COMMON-0)
//#define COMMON_Err_UnknownIntState  (ERRORS_COMMON-1)
//#define COMMON_Err_ArgumentRange    (ERRORS_COMMON-2)
//#define COMMON_Err_NameToLong       (ERRORS_COMMON-3)
//------------------------------------------------------------------------------
//#define EQUIPMENT_Err_Sensor           (ERRORS_EQUIPMENT-0)
//#define EQUIPMENT_Err_Freezing			(ERRORS_EQUIPMENT-1)
//#define EQUIPMENT_Err_ArgumentRange    (ERRORS_EQUIPMENT-2)
//void Err_DisplayMessage(sint e);
//------------------------------------------------------------------------------
void error_init();
void error_insert(s16 code);
//------------------------------------------------------------------------------
#endif
