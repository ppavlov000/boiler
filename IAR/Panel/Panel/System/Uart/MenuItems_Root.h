#ifndef __ROOT
#define __ROOT
#include "console.h"
//-----------------------------------------------------------------------------------
TMenuItem _SetFec=
{
	&Slovar[16][0],NULL,0,
	NULL,
	NULL,
};
//---------------------------------
TMenuItem _SetRate=
{
	&Slovar[5][0],NULL,0,
	NULL,
	&_SetFec,
};
//---------------------------------
TMenuItem _SetFreq=
{
	&Slovar[4][0],NULL,0,
	NULL,
	&_SetRate,
};
//---------------------------------
TMenuItem _Set=
{
	&Slovar[0][0],NULL,0,
	&_SetFreq,
	NULL,
};
//-----------------------------------------------------------------------------------
#endif
