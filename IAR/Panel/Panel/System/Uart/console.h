#ifndef __CONSOLE
#define __CONSOLE
//-----------------------------------------------------------------------------------
#include "..\..\..\System\Standard\types.h"
//-----------------------------------------------------------------------------------
#define con_None            0
#define con_Mem             1
#define con_Show            2
#define con_Set             3
#define con_Set_Freq        4
#define con_Set_Rate        5
#define con_Set_Mod         6

#define con_RMem_arg        100
#define con_WMem_arg1       101
#define con_WMem_arg2       102
#define con_Set_Freq_arg    103
#define con_Set_Rate_arg    104
#define con_Set_Filter_arg  105
#define con_CIC_arg         106
#define con_RF_arg          107
#define con_WF_arg1         108
#define con_WF_arg2         109
#define con_WG_arg          110

//-----------------------------------------------------------------------------------
#define BuffLength	64
//-----------------------------------------------------------------------------------
#define	Help_Len			1
#define	Help_Word_Len		160
#define Slovar_Len	 		32
#define Slovar_Word_Len		12
#define Last_Commands_Num	5
#define Menu_List_Count		5
//-----------------------------------------------------------------------------------
typedef struct 
{
	__farflash u8* Word;
	__farflash u8* Help0;	
	u8 			Flag;
	void (* Routine)();
		
	void* 		UpItem;	
	void* 		SubItem;
	void* 		NextItem;	
}TMenuItem;
__farflash eu8 Slovar[Slovar_Len][Slovar_Word_Len];
extern TMenuItem _Root;
eu32 Params[5];
eu8 console_mode;
//-----------------------------------------------------------------------------------
void con_init();
void strfull(u8 *str);
void word_handler();
void con_handle();
void wait_con_free();
void con_parser();
//void strcpy2(u8* str1,u8* str2);;
//-----------------------------------------------------------------------------------
#endif
