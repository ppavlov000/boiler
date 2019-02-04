#ifndef __SET
#define __SET
//-----------------------------------------------------------------------------------
#include "..\main.h"
#include "MenuItems_SERVICE.h"
//-----------------------------------------------------------------------------------
extern TMenuItem _Set;
//-----------------------------------------------------------------------------------
/*
TMenuItem _Set_Address_Value=
{
	&Slovar[31][0],NULL,4,
	Set_Adress,		
	&_Root,	
	NULL,
	NULL,	
};
TMenuItem _Set_Address=
{
	&Slovar[31][0],NULL,0,
	NULL,		
	&_Root,	
	&_Set_Address_Value,
	NULL,
};
*/
//-------------------- Set -------------------------------
TMenuItem _Set=
{
	&Slovar[0][0],NULL,0,
	NULL,		
	NULL,	
	NULL,		
//	&_Set_Address,
	&_Reset,
};
//-----------------------------------------------------------------------------------
#endif
