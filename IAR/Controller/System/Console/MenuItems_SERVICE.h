#ifndef __SERVICE
#define __SERVICE
//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
void Mod_Show_FAN();
void Mod_Show_Season();
void Mod_Show_Kotel();
void Mod_Show_Kotel_Params();
//-----------------------------------------------------------------------------------
extern in_flash TCMenuItem _Set;
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Echo_Off=
{
	"off",NULL,0,
	Echo_Off,	
	&_Root,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Echo_On=
{
	"on",NULL,0,
	Echo_On,	
	&_Root,	
	NULL,
	&_Echo_Off,
};
in_flash TCMenuItem _Echo=
{
	"echo",NULL,0,
	NULL,	
	&_Root,	
	&_Echo_On,
	NULL,
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Init=
{
	"init",NULL,0,
	Params_Init,	
	&_Root,	
	NULL,
	&_Echo,
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Program_Stop=
{
	"stop",NULL,0,
	Intr_Program_Stop,	
	&_Root,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Program_Start=
{
	"start",NULL,0,
	Intr_Program_Start,	
	&_Root,	
	NULL,
	&_Program_Stop,
};
in_flash TCMenuItem _Program=
{
	"program",NULL,0,
	NULL,	
	&_Root,	
	&_Program_Start,
	&_Init,
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Download_Program=
{
	"program",NULL,0,
	Prog_Download,	
	&_Root,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Download=
{
	"download",NULL,0,
	NULL,	
	&_Root,	
//	&_Download_Program,
	NULL,	
	&_Program,
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Config=
{
	"config",NULL,0,
	fram_init,	
	&_Root,	
	NULL,
	&_Download,
};

//-----------------------------------------------------------------------------------
#if MAX_KOTEL_NUMBER
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Show_KOT_Params_Number=
{
	"number",NULL,4,
	Mod_Show_Kotel_Params,	
	&_Root,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Show_KOT_Params=
{
	"parameters",NULL,0,
	NULL,	
	&_Root,	
	&_Show_KOT_Params_Number,
	NULL,
};
//-------------------------------------
in_flash TCMenuItem _Show_KOT_Stat=
{
	"status",NULL,0,
	Mod_Show_Kotel,	
	&_Root,	
	NULL,
	&_Show_KOT_Params,
};
//-------------------------------------
in_flash TCMenuItem _Show_KOT=
{
	"kotel",NULL,0,
	NULL,	
	&_Root,	
	&_Show_KOT_Stat,
	NULL,
};
//-------------------------------------
#endif
//-------------------------------------
in_flash TCMenuItem _Show_Season=
{
	"season",NULL,0,
	Mod_Show_Season,	
	&_Root,	
	NULL,
#if MAX_KOTEL_NUMBER
	&_Show_KOT,
#else
	NULL,
#endif
};
//-------------------------------------
in_flash TCMenuItem _Show_FAN_Number=
{
	"number",NULL,4,
	Mod_Show_FAN,	
	&_Root,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Show_FAN=
{
	"fan",NULL,0,
	NULL,	
	&_Root,	
	&_Show_FAN_Number,
	&_Show_Season,
};
//-------------------------------------
in_flash TCMenuItem _Show_Prog=
{
	"program",NULL,0,
	Mod_Show_Status_Prog,	
	&_Root,	
	NULL,
	&_Show_FAN,
};
//-------------------------------------
in_flash TCMenuItem _Show_Errors=
{
	"errors",NULL,0,
	Mod_Show_Errors,	
	&_Root,	
	NULL,
	&_Show_Prog,
};
//-------------------------------------
in_flash TCMenuItem _Show_PID_Number=
{
	"number",NULL,4,
	Mod_Show_PID,	
	&_Root,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Show_PID=
{
	"pid",NULL,0,
	NULL,	
	&_Root,	
	&_Show_PID_Number,
	&_Show_Errors,
};
//-------------------------------------
in_flash TCMenuItem _Show_Status=
{
	"status",NULL,0,
	Mod_Show_Status,	
	&_Root,	
	NULL,
	&_Show_PID,
};
//-------------------------------------
in_flash TCMenuItem _Show=
{
	"show",NULL,0,
	NULL,	
	&_Root,	
	&_Show_Status,
	&_Config,
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Console_Toggle=
{
	"toggle",NULL,0,
	Mod_Console_Toggle,	
	&_Root,	
	NULL,
	&_Show,
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Test=
{
	"test",NULL,0,
	Mod_Test,	
	&_Root,	
	NULL,
	&_Console_Toggle,
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Store_Parameters=
{
	"parameters",NULL,0,
	Mod_Store_Parameters,
	&_Root,	
	NULL,
	NULL,
};
//-------------------------
in_flash TCMenuItem _Store=
{
	"store",NULL,0,
	NULL,		
	&_Root,	
	&_Store_Parameters,
	&_Test,
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Reset=
{
	"reset",NULL,0,
	reset,		
	&_Root,	
	NULL,
	&_Store,
};
//-----------------------------------------------------------------------------------
#endif
