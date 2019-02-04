#ifndef __SET
#define __SET
//-----------------------------------------------------------------------------------
#include "..\..\..\System\main.h"
//-----------------------------------------------------------------------------------
/*

extern TLCDMenuItem _LCD_Operation_Mode;
extern TLCDMenuItem _LCD_Language;
extern TLCDMenuItem _LCD_Choose_Pid_Parameter;

extern TLCDMenuItem _LCD_Info;
extern TLCDMenuItem _LCD_Time;

extern TLCDMenuItem _LCD_Edit_Time;
extern TLCDMenuItem _LCD_Choose_Time;
extern TLCDMenuItem _LCD_Show_Time;
extern TLCDMenuItem _LCD_Password;

extern TLCDMenuItem _LCD_Run_Full;
extern TLCDMenuItem _LCD_Run_Limited;
//-----------------------------------------------------------------------------------
void lcd_choose_time();
void lcd_edit_time();
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
	&_LCD_Run_Full,
	&_LCD_Edit_Pid_Parameter,
	NULL,
	NULL,	
};
//-----------------------------------------------------------------------------------
TLCDMenuItem _LCD_Show_Errors_Full=
{
	1,
	lcd_menu_show_errors,		
	&_LCD_Run_Full,	
	NULL,
	NULL,
	NULL,	
};
TLCDMenuItem _LCD_Show_Errors_Limited=
{
	1,
	lcd_menu_show_errors,		
	&_LCD_Run_Limited,	
	NULL,
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
//---------------------------------------------------
//---------------------------------------------------
TLCDMenuItem _LCD_Edit_Time=
{
	1,
	lcd_edit_time,		
	&_LCD_Choose_Time,	
	NULL,
	NULL,
	NULL,	
};
//---------------------------------------------------
TLCDMenuItem _LCD_Choose_Time=
{
	1,
	lcd_choose_time,		
	&_LCD_Show_Time,	
	&_LCD_Edit_Time,
	NULL,
	NULL,	
};
//---------------------------------------------------
TLCDMenuItem _LCD_Show_Time=
{
	1,
	lcd_show_time,		
	&_LCD_Time,	
	&_LCD_Choose_Time,
	NULL,
	NULL,	
};
//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------
TLCDMenuItem _LCD_Show_Info=
{
	1,
	lcd_show_info,		
	&_LCD_Info,	
	NULL,
	NULL,
	NULL,	
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------

//---------------------------------------------------
TLCDMenuItem _LCD_Digital_Out=
{
	0,
	lcd_menu_digital_out,
	&_LCD_Run_Full,	
	&_LCD_Show_Digital_Out,		
	&_LCD_Digital_In,		
	NULL,
};
//---------------------------------------------------
TLCDMenuItem _LCD_Digital_In=
{
	0,
	lcd_menu_digital_in,		
	&_LCD_Run_Full,	
	&_LCD_Show_Digital_In,		
	&_LCD_Analog_Out,		
	&_LCD_Digital_Out,
};
//---------------------------------------------------
TLCDMenuItem _LCD_Analog_Out=
{
	0,
	lcd_menu_analog_out,		
	&_LCD_Run_Full,	
	&_LCD_Show_Analog_Out,		
	&_LCD_Analog_In,		
	&_LCD_Digital_In,
};
//---------------------------------------------------
TLCDMenuItem _LCD_Analog_In=
{
	0,
	lcd_menu_analog_in,		
	&_LCD_Run_Full,	
	&_LCD_Show_Analog_In,		
	&_LCD_Time,		
	&_LCD_Analog_Out,
};
//---------------------------------------------------
TLCDMenuItem _LCD_Time=
{
	0,
	lcd_title_time,
	&_LCD_Run_Full,	
	&_LCD_Show_Time,		
	&_LCD_Language,		
	&_LCD_Analog_In,
};
//---------------------------------------------------
TLCDMenuItem _LCD_Language=
{
	0,
	lcd_title_language,
	&_LCD_Run_Full,	
	&_LCD_Choose_Language,		
	&_LCD_Info,		
	&_LCD_Time,
};
//---------------------------------------------------
TLCDMenuItem _LCD_Info=
{
	0,
	lcd_title_info,
//	&_LCD_Run_Full,	
	NULL,	
	&_LCD_Show_Info,		
	NULL,		
	&_LCD_Language,
};
//---------------------------------------------------
TLCDMenuItem _LCD_Run_Limited=
{
	1,
//	lcd_menu_show_info_limited,
	NULL,
	&_LCD_Password,
	NULL,
	NULL,
	NULL,
};
//---------------------------------------------------
TLCDMenuItem _LCD_Run_Full=
{
	1,
//	lcd_menu_show_info_full,
	NULL,	
	&_LCD_Password,	
	NULL,		
	NULL,		
	NULL,
};
//---------------------------------------------------
TLCDMenuItem _LCD_Password=
{
	1,
//	lcd_enter_password,
	NULL,	
	NULL,	
	NULL,	
	NULL,		
	NULL,	
};
*/
//---------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
#endif
