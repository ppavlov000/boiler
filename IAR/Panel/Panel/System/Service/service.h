#ifndef _PLM
#define _PLM
//-----------------------------------------------------------------------------------
#include "..\..\System\Standard\types.h"
#include "..\TSC2046\tsc2046.h"
//-----------------------------------------------------------------------------------
eu16 addr;
//-------------------------------------------------------------------------------------------
extern __farflash u8	Monthes_Name[12][10];
extern __farflash u8	Monthes_Name_Short[12][5];
extern __farflash u8	DaysOfWeek[8][10];
extern __farflash u8	DaysOfWeek_Short[8][5];
//-----------------------------------------------------------------------------------
void Mod_Reset();
void Mod_Store_Parameters();
void Mod_Routine();
void Mod_Test();
void Mod_Show_Status();
void Mod_Show_Full_Time();
u32 CheckCRC(u8 who);
u16 get_reg_addr(u8* addr);
//-----------------------------------------------------------------------------------
#endif
