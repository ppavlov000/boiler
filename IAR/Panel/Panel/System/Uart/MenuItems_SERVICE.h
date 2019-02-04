#ifndef __SERVICE
#define __SERVICE
//-----------------------------------------------------------------------------------
#include "console.h"
#ifndef __RENESAS
  #include "inavr.h"
#endif
#include "..\Service\service.h"
//-----------------------------------------------------------------------------------
extern TMenuItem _Set;
//-----------------------------------------------------------------------------------
TMenuItem _Show_Status=
{
	&Slovar[13][0],NULL,0,
	Mod_Show_Status,	
	&_Root,	
	NULL,
	NULL,
};

TMenuItem _Show=
{
	&Slovar[12][0],NULL,0,
	NULL,	
	&_Root,	
	&_Show_Status,
	NULL,
};
//---------------------------------------------
/*
TMenuItem _Set_Test_Value=
{
	&Slovar[0][0],NULL,1,
	Mod_Test,		
	NULL,	
	NULL,
	NULL,
};
//-----------------------------------------------------------------------------------
TMenuItem _Test=
{
	&Slovar[11][0],NULL,0,
	Mod_Test,	
	NULL,	
	&_Set_Test_Value,
	&_Show,
};
*/

TMenuItem _Test=
{
	&Slovar[11][0],NULL,0,
	Mod_Test,	
	&_Root,	
	NULL,
	&_Show,
};

//-----------------------------------------------------------------------------------
TMenuItem _Store_Parameters=
{
	&Slovar[4][0],NULL,0,
	Mod_Store_Parameters,
	&_Root,	
	NULL,
	NULL,
};
//-------------------------
TMenuItem _Store=
{
	&Slovar[2][0],NULL,0,
	NULL,		
	&_Root,	
	&_Store_Parameters,
	&_Test,
};
//-----------------------------------------------------------------------------------
TMenuItem _Reset=
{
	&Slovar[7][0],NULL,0,
	Mod_Reset,		
	&_Root,	
	NULL,
	&_Store,
};
//-----------------------------------------------------------------------------------
#endif
