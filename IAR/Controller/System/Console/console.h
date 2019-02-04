//------------------------------------------------------------------------------
#ifndef __CONSOLE
#define __CONSOLE
//------------------------------------------------------------------------------
#include "..\Misc\types.h"
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
#define BuffLength	64
//------------------------------------------------------------------------------
#define	Help_Len			1
#define	Help_Word_Len		160
#define Slovar_Len	 		60
#define Slovar_Word_Len		20
#define Last_Commands_Num	5
#define Menu_List_Count		5
//------------------------------------------------------------------------------
typedef struct
{
	u8 Word[Slovar_Word_Len];
	u8* Help0;	
	u8 			Flag;
	void (* Routine)();
		
	in_flash void* 		UpItem;	
	in_flash void* 		SubItem;
	in_flash void* 		NextItem;	
}TCMenuItem;

//in_flash eu8 Slovar[Slovar_Len][Slovar_Word_Len];
extern in_flash TCMenuItem _Root;
eu32 Params[5];
eu8 console_mode;
//------------------------------------------------------------------------------
void con_init();
void strfull(u8 *str);
void word_handler();
void con_handle();
void wait_con_free();
void sendchar(u8 sym);
s16 recchar();
void con_parser();
//void strcpy2(u8* str1,u8* str2);
void GetFlashStr(u8 *word,u8* ptr);
void Echo_On();
void Echo_Off();
//------------------------------------------------------------------------------
#endif
