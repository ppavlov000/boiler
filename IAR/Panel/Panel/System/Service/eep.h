#ifndef __EEP
#define __EEP
//-----------------------------------------------------------------------------------
#include "..\Misc\types.h"
//#define __HAS_EEPROM__ 
//-----------------------------------------------------------------------------------
void EEPut(u8 *Data,u16 Addr,u8 Len);
void EEGet(u8 *Data,u16 Addr,u8 Len);
//-----------------------------------------------------------------------------------
#endif