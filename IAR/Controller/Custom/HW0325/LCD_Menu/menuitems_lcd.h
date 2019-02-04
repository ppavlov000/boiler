#ifndef __SET
#define __SET
//-----------------------------------------------------------------------------------
#include "main.h"
//-----------------------------------------------------------------------------------
extern TLCDMenuItem _LCD_Operation_Mode;
extern TLCDMenuItem _LCD_Language;
extern TLCDMenuItem _LCD_Choose_Pid_Parameter;
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDMenuItem _LCD_Edit_Pid_Parameter=
{
	1,
	lcd_menu_edit_pid_parameter,		
	&_LCD_Choose_Pid_Parameter,	
	NULL,
	NULL,
	NULL,	
};
//-----------------------------------------------------------------------------------
TLCDMenuItem _LCD_Choose_Pid_Parameter=
{
	1,
	lcd_menu_choose_pid_parameter,		
	NULL,
	&_LCD_Edit_Pid_Parameter,
	NULL,
	NULL,	
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDMenuItem _LCD_Show_Pid_3=
{
	1,
	lcd_menu_show_pid_3,		
	&_LCD_Pid_3,	
	&_LCD_Choose_Pid_Parameter,
	NULL,
	NULL,	
};
//---------------------------------------------------
TLCDMenuItem _LCD_Show_Pid_2=
{
	1,
	lcd_menu_show_pid_2,		
	&_LCD_Pid_2,	
	&_LCD_Choose_Pid_Parameter,
	NULL,
	NULL,	
};
//---------------------------------------------------
TLCDMenuItem _LCD_Show_Pid_1=
{
	1,
	lcd_menu_show_pid_1,		
	&_LCD_Pid_1,	
	&_LCD_Choose_Pid_Parameter,
	NULL,
	NULL,	
};
//---------------------------------------------------
TLCDMenuItem _LCD_Show_Pid_0=
{
	1,
	lcd_menu_show_pid_0,		
	&_LCD_Pid_0,	
	&_LCD_Choose_Pid_Parameter,
	NULL,
	NULL,	
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDMenuItem _LCD_Choose_Language=
{
	1,
	lcd_menu_choose_language,		
	&_LCD_Language,	
	&_LCD_Choose_Pid_Parameter,
	NULL,
	NULL,	
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDMenuItem _LCD_Program_Debug_Show=
{
	1,
	lcd_menu_program_debug_show,		
	&_LCD_Program_Debug,	
	NULL,
	NULL,
	NULL,		
};
//-----------------------------------------------------------------------------------
TLCDMenuItem _LCD_Program_List_Show=
{
	1,
	lcd_menu_program_list_show,	
	&_LCD_Program_List,	
	NULL,
	NULL,
	NULL,		
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDMenuItem _LCD_Program_Debug=
{
	1,
	lcd_menu_program_debug,		
	&_LCD_Program,	
	&_LCD_Program_Debug_Show,
	&_LCD_Program_List,
	NULL,		
};
//-----------------------------------------------------------------------------------
TLCDMenuItem _LCD_Program_List=
{
	1,
	lcd_menu_program_list,	
	&_LCD_Program,	
	&_LCD_Program_List_Show,
	&_LCD_Program_Run,
	&_LCD_Program_Debug,		
};
//-----------------------------------------------------------------------------------
TLCDMenuItem _LCD_Program_Run=
{
	1,
	lcd_menu_program_run,		
	&_LCD_Program,	
	NULL,
	NULL,
	&_LCD_Program_List,		
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDMenuItem _LCD_Edit_Digital_Out=
{
	1,
	lcd_menu_edit_digital_out,		
	&_LCD_Show_Digital_Out,	
	NULL,
	NULL,
	NULL,		
};
//---------------------------------------------------
TLCDMenuItem _LCD_Show_Digital_Out=
{
	1,
	lcd_menu_show_digital_out,		
	&_LCD_Digital_Out,	
	&_LCD_Edit_Digital_Out,
	NULL,
	NULL,		
};
//---------------------------------------------------
TLCDMenuItem _LCD_Show_Digital_In=
{
	1,
	lcd_menu_show_digital_in,		
	&_LCD_Digital_In,	
	NULL,
	NULL,
	NULL,		
};
//---------------------------------------------------
TLCDMenuItem _LCD_Show_Analog_Out=
{
	0,
	lcd_menu_show_analog_out,		
	&_LCD_Analog_Out,	
	NULL,
	NULL,
	NULL,		
};
//---------------------------------------------------
TLCDMenuItem _LCD_Show_Analog_In=
{
	1,
	lcd_menu_show_analog_in,		
	&_LCD_Analog_In,	
	NULL,	
	NULL,		
	NULL,
};
//---------------------------------------------------
TLCDMenuItem _LCD_Choose_Operation_Mode=
{
	1,
	lcd_menu_choose_mode,		
	&_LCD_Root,	
	NULL,
	NULL,
	NULL,	
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDMenuItem _LCD_Language=
{
	0,
	lcd_show_language,
	&_LCD_Root,	
	&_LCD_Choose_Language,		
	&_LCD_Digital_Out,		
	NULL,
};
//---------------------------------------------------
TLCDMenuItem _LCD_Digital_Out=
{
	0,
	lcd_menu_digital_out,
	&_LCD_Root,	
	&_LCD_Show_Digital_Out,		
	&_LCD_Digital_In,		
	&_LCD_Language,
};
//---------------------------------------------------
TLCDMenuItem _LCD_Digital_In=
{
	0,
	lcd_menu_digital_in,		
	&_LCD_Root,	
	&_LCD_Show_Digital_In,		
	&_LCD_Analog_Out,		
	&_LCD_Digital_Out,
};
//---------------------------------------------------
TLCDMenuItem _LCD_Analog_Out=
{
	0,
	lcd_menu_analog_out,		
	&_LCD_Root,	
	&_LCD_Show_Analog_Out,		
	&_LCD_Analog_In,		
	&_LCD_Digital_In,
};
//---------------------------------------------------
TLCDMenuItem _LCD_Analog_In=
{
	0,
	lcd_menu_analog_in,		
	&_LCD_Root,	
	&_LCD_Show_Analog_In,		
	&_LCD_Pid_1,		
	&_LCD_Analog_Out,
};
//---------------------------------------------------
/*
TLCDMenuItem _LCD_Pid_3=
{
	0,
	lcd_menu_pid_3,		
	&_LCD_Root,	
	&_LCD_Show_Pid_3,		
	&_LCD_Pid_2,		
	&_LCD_Analog_In,
};
//---------------------------------------------------
TLCDMenuItem _LCD_Pid_2=
{
	0,
	lcd_menu_pid_2,		
	&_LCD_Root,	
	&_LCD_Show_Pid_2,		
	&_LCD_Pid_1,		
	&_LCD_Pid_3,
};
*/
//---------------------------------------------------
TLCDMenuItem _LCD_Pid_1=
{
	0,
	lcd_menu_pid_1,		
	&_LCD_Root,	
	&_LCD_Show_Pid_1,		
	&_LCD_Pid_0,		
	&_LCD_Analog_In,
};
//---------------------------------------------------
TLCDMenuItem _LCD_Pid_0=
{
	0,
	lcd_menu_pid_0,		
	&_LCD_Root,	
	&_LCD_Show_Pid_0,		
	&_LCD_Operation_Mode,		
	&_LCD_Pid_1,
};
//---------------------------------------------------
TLCDMenuItem _LCD_Operation_Mode=
{
	0,
	lcd_show_operation_mode,		
	&_LCD_Root,		
	&_LCD_Choose_Operation_Mode,
	NULL,
	&_LCD_Pid_0,	
};
//---------------------------------------------------
TLCDMenuItem _LCD_Program=
{
	0,
	lcd_menu_program,		
	&_LCD_Root,	
	&_LCD_Program_Run,		
	&_LCD_Digital_Out,		
	&_LCD_Analog_In,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
#endif
