#ifndef __CONSOLE
#define __CONSOLE
//-----------------------------------------------------------------------------------
#include <iom128.h>
#include "Include\types.h"
//-----------------------------------------------------------------------------------
#define con_None            0
#define con_Mem             1
#define con_Show            2
#define con_Set             3
#define con_Set_Freq        4
#define con_Set_Rate        5
#define con_Set_Mod         6
#define con_Down_Mod        7

#define con_RMem_arg        100
#define con_WMem_arg1       101
#define con_WMem_arg2       102
#define con_Set_Freq_arg    103
#define con_Set_Rate_arg    104
#define con_Set_Filter_arg  105
//-----------------------------------------------------------------------------------
//extern char outtxt[400];
//extern u32 ltmp;
//extern u8  ctmp;
//extern double dtmp;
//extern u16 wtmp;
//-----------------------------------------------------------------------------------
//void sprintf(char *out,char *in);
//void WordToStr(char *out,u16 *val);
//void LongToStr(char *out,u32 *val);
void con_init();
void strlwr(char *str);
void strfull(s8 *str);
void word_handler();
void con_handle();
void wait_con_free();
void sendchar(u8 sym);
s16 recchar();
void con_parser();
//-----------------------------------------------------------------------------------
#endif
