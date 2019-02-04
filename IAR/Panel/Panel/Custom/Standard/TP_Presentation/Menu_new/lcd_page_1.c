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
//extern TLCDPictTop Scr_0;
extern TLCDPictTop Scr_4;
extern TLCDPictTop Scr_10;
extern TLCDPictTop Scr_11;
extern TLCDPictTop Scr_12;
extern TLCDPictTop Scr_15;
extern __farflash TLCDPict_Txt _Txt_0;
extern __farflash TLCDPict_Txt _Txt_1;
extern __farflash TLCDPict_Txt _Txt_2;
extern __farflash TLCDPict_Txt _Txt_3;
extern __farflash TLCDPict_Txt _Txt_4;
//-----------------------------------------------------------------------------------
void scr1_init();
void scr1_close();
void scr1_routine();
//-----------------------------------------------------------------------------------
extern u8 Branch_Number;
extern u8 step;
extern u8 new_step;
extern u8 Common_ID_Mode;
extern u8 Current_ID;
extern u8 Switch_To_ID_1;
extern s16 T_Sensor;

//BMP_22=H:\Ura\Projects\20090914_Shevchenko\Iar\Panel\Panel\System\Pictures\EL\Scr_1\set_tech.bmp
//BMP_23=H:\Ura\Projects\20090914_Shevchenko\Iar\Panel\Panel\System\Pictures\EL\Scr_1\set_protok.bmp
//BMP_24=H:\Ura\Projects\20090914_Shevchenko\Iar\Panel\Panel\System\Pictures\EL\Scr_1\set_Season.bmp
//BMP_25=H:\Ura\Projects\20090914_Shevchenko\Iar\Panel\Panel\System\Pictures\EL\Scr_1\set_Day_Night.bmp
void M_Save_Controller_Params(u8 id);
//-----------------------------------------------------------------------------------
void Send_Save_command()
{
	M_Save_Controller_Params(Current_ID);
	M_SCH_Time=10;
}
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_1_Tech=
{	
	0,16,22,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,	
	NULL,
	&Scr_4,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_1_Protok=
{	
	0,16+27,23,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,	
	NULL,
	&Scr_10,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_1_Season=
{	
	0,16+2*27,24,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,	
	NULL,
	&Scr_12,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_1_Day=
{	
	0,16+3*27,25,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,	
	NULL,
	&Scr_11,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_1_Save=
{	
	16,16+3*27,56,
	(bit_visible+bit_active),
//	0,
	0,
	0,
	0,	
	Send_Save_command,
	&Scr_11,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_1=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	5+5,
	0,	
	scr1_init,
	scr1_routine,
	scr1_close,		
};
//-----------------------------------------------------------------------------------
void scr1_init()
{
//	u8 i;
	Branch_Number=0;
	new_step=step=0;
	Obj[0]=_Menu0;	
	Obj[1]=_Menu1;	
	Obj[2]=_Menu2;	
	Obj[3]=_Menu3;		
	Obj[4]=_Menu4;	
	
	Obj[5]=_Page_1_Tech;	
	Obj[6]=_Page_1_Protok;	
	Obj[7]=_Page_1_Season;	
	Obj[8]=_Page_1_Day;	
	Obj[9]=_Page_1_Save;	

	Obj[1].Stat=1;
}
//-----------------------------------------------------------------------------------
void scr1_close()
{
	u8 i;
	for(i=0;i<Scr_1.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
}
//-----------------------------------------------------------------------------------
void scr1_routine()
{
//	u8 tmp;		
//	u16 temp;
//	u8 tmp0;//,tmp1,tmp2; lc
//	u8 old_stat;
//	s16 temperature;
	if(FT_Time!=0)return;
	FT_Time=500;
	if(page_offset!=PAGE_0_OFFSET)return;
}
//-----------------------------------------------------------------------------------

