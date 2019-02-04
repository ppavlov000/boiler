//-----------------------------------------------------------------------------------
#include "..\..\..\..\System\Main.h"
#include "..\..\..\..\System\Menu_New\lcd_template.h"
#include "..\..\..\..\System\Menu_New\lcd_calibrate.h"
#include "..\..\..\..\System\Menu_New\lcd_alarm.h"
#include "..\..\..\..\System\Menu_New\lcd_alarm_snooze.h"
#include "..\..\..\..\System\Menu_New\lcd_ac_menu.h"
#include "..\..\..\..\System\Menu_New\lcd_tech_menu.h"
#include "..\..\..\..\System\Menu_New\lcd_set_time.h"
#include "..\..\..\..\System\Menu_New\lcd_tech_contrast.h"
#include "..\..\..\..\System\Menu_New\lcd_tech_temperature.h"
#include "dimmer.h"
//-----------------------------------------------------------------------------------
#include "..\Menu_new\lcd_screen_0.h"
//-----------------------------------------------------------------------------------
#define NO_ALARM
//-----------------------------------------------------------------------------------
#define But_Main_Switch			Obj[20]
#define But_Do_Not_Disturb		Obj[20]
#define But_Makeup_Room			Obj[20]
#define But_Curtain_Open		Obj[20]
#define But_Curtain_Close		Obj[20]
#define Alarm_bell_obj			Obj[20]
//-----------------------------------------------------------------------------------
void scr_alarm_confirm_init();
void scr_alarm_confirm_close();
void scr_alarm_confirm_routine();
extern TLCDPictTop Scr_Password;
extern vs8 thief_alarm_timeout;
extern u8 	alarm_pass_time;

extern TLCDPictTop *Scr_Return;
extern TLCDPictTop *Scr_Enter;
//----------------------------
void activate_alarm_pressed()
{
	Password_Mode=PM_ACTIVATION_COUNTDOWN;
//	alarm_pass_time=30;
	own_state.Password_Mode=Password_Mode;
	own_state.Password_Downcount=30;
	own_state.status |= bit_new_push;			
	
	Scr_Return=&Scr_0;
	Scr_Enter=&Scr_0;
	LCDTopPtr->Exit();
	LCDTopPtr=&Scr_Password;
	LCDTopPtr->Init();
	repaint_page();
}

//--------------------------------------------
__farflash TLCDPict _Button_alarm_confirm_mes=
{	
	4,30,77,
	(bit_visible+bit_full),
	0,
	0,
	0,	
	NULL,
	NULL,
};

__farflash TLCDPict _Button_alarm_confirm_yes=
{	// Yes
	22,88,78,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,	
	activate_alarm_pressed,
	NULL//&Scr_1,
};

//--------------------------------------------
__farflash TLCDPict _Button_alarm_confirm_no=
{	// No
	1,88,79,
	(bit_visible+bit_active+bit_trigger+bit_new_page),
	0,
	0,
	0,
	NULL,
	&Scr_0,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop scr_alarm_confirm=
{
	0,0,0,
	0,
	3,
	0,	
	scr_alarm_confirm_init,
	scr_alarm_confirm_routine,
	scr_alarm_confirm_close,		
};

//-----------------------------------------------------------------------------------
void scr_alarm_confirm_init()
{
	Obj[0]=_Button_alarm_confirm_mes;
	Obj[1]=_Button_alarm_confirm_yes;
	Obj[2]=_Button_alarm_confirm_no;
	Obj[20]=_Null;
	FT_Time=100;
}
//-----------------------------------------------------------------------------------
void scr_alarm_confirm_close()
{
	clear_page();
}
//-----------------------------------------------------------------------------------
void scr_alarm_confirm_routine()
{
}
//-----------------------------------------------------------------------------------
