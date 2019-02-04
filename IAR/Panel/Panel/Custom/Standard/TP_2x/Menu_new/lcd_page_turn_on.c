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
//-----------------------------------------------------------------------------------
extern __farflash TLCDPict _Menu0;
extern __farflash TLCDPict _Menu1;
extern __farflash TLCDPict _Menu2;
extern __farflash TLCDPict _Menu3;
extern __farflash TLCDPict _Menu4;
//-----------------------------------------------------------------------------------
extern TLCDPictTop Scr_0;
extern TLCDPictTop Scr_12;
//-----------------------------------------------------------------------------------
void scr15_init();
void scr15_close();
void scr15_routine();
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Turn_On=
{
	5,48,89,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,	
	&Scr_0,
	NULL,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_15=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	1,
	0,	
	scr15_init,
	scr15_routine,
	scr15_close,		
};

//-----------------------------------------------------------------------------------
void scr15_init()
{
	u8 i;
	Switch_To_Main_Time=60;
	Obj[0]=_Turn_On;	

	
	FT_Time=100;
	for(i=0;i<Scr_15.Txt_Num;i++)
		Txt[i].Stat=11;
	
}
//-----------------------------------------------------------------------------------
void scr15_close()
{
	u8 i;
	for(i=0;i<Scr_15.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
	lcd_clear_text();
}
//-----------------------------------------------------------------------------------
void scr15_routine()
{

}
//-----------------------------------------------------------------------------------

