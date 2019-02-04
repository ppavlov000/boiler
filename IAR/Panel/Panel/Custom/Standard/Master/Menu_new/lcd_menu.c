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
extern TLCDPictTop Scr_0;
extern TLCDPictTop Scr_1;
extern TLCDPictTop Scr_2;
extern TLCDPictTop Scr_3;
extern TLCDPictTop Scr_44;
//-----------------------------------------------------------------------------------
// Menu
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Menu4=
{	//
	24,0,4,
	(bit_visible+bit_active+bit_new_page+bit_trigger),
	0,
	0,	
	0,	
	NULL,
	&Scr_44,	
};
//--------------------------------------------
__farflash TLCDPict _Menu3=
{	//
	18,0,3,
//	(bit_visible+bit_active+bit_new_page+bit_trigger),
	0,
	0,
	0,	
	0,	
	NULL,
	&Scr_3,	
};
//--------------------------------------------
__farflash TLCDPict _Menu2=
{	//
	12,0,2,
//	(bit_visible+bit_active+bit_new_page+bit_trigger),
	0,
	0,
	0,	
	0,	
	NULL,
	&Scr_2,	
};
//--------------------------------------------
__farflash TLCDPict _Menu1=
{	//
	6,0,1,
//	(bit_visible+bit_active+bit_new_page+bit_trigger),
	0,
	0,
	0,	
	0,	
	NULL,
	&Scr_1,	
};
//--------------------------------------------
__farflash TLCDPict _Menu0=
{	//
	0,0,0,
	(bit_visible+bit_active+bit_new_page+bit_trigger),
	0,
	0,	
	0,	
	NULL,
	&Scr_0,	
};
//-----------------------------------------------------------------------------------

