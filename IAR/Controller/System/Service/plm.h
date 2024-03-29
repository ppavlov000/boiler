//------------------------------------------------------------------------------
#ifndef _PLM
#define _PLM
//------------------------------------------------------------------------------
#include "..\main.h"
//------------------------------------------------------------------------------
#define UControl0 ModParams.Status
eu8 UControl1;
extern in_flash u8	Monthes_Name[12][10];
extern in_flash u8	Monthes_Name_Short[12][5];
extern in_flash u8	DaysOfWeek[7][10];
extern in_flash u8	DaysOfWeek_Short[7][5];

extern in_flash u8	Monthes_Name_rus[12][10];
extern in_flash u8	Monthes_Name_Short_rus[12][5];
extern in_flash u8	DaysOfWeek_rus[7][13];
extern in_flash u8	DaysOfWeek_Short_rus[7][5];
extern f32	pp,ii,dd;
//------------------------------------------------------------------------------
void Mod_Reset();
void Mod_Store_Parameters();
void Mod_Routine();
void Mod_Test();
void Mod_Show_Status();
void Valve_On();
void Valve_Off();
void Relay_On();
void Relay_Off();
void IO_On();
void IO_Off();
void Led_On();
void Led_Off();
void Set_AI_10V();
void Mod_Console_Toggle();
void Set_Time();
void Set_Date();
void Prog_Download();
void Set_Point();
void Set_Desired_Temperature();
void Prog_Check();
void Mod_Show_PID();
void Params_Init();
void Mod_Show_Errors();
void Mod_Show_Status_Prog();
void Production_Test();
void Mod_Show_Full_Time();
void Set_Password_On();
void Set_Password_Off();
void Set_Password_User();
void Set_Password_Admin();
void Set_ID();
//------------------------------------------------------------------------------
#endif
