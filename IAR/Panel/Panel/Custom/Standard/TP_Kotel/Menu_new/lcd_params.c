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
void scr0_2_init();
void scr0_2_routine();
void scr0_2_close();
//-----------------------------------------------------------------------------------
extern __farflash TLCDPict _Menu0;
extern __farflash TLCDPict _Menu1;
extern __farflash TLCDPict _Menu2;
extern __farflash TLCDPict _Menu3;
extern __farflash TLCDPict _Menu4;

extern __farflash TLCDPict Tab_Menu0;
extern __farflash TLCDPict Tab_Menu1;
extern __farflash TLCDPict Tab_Menu2;
extern __farflash TLCDPict Tab_Menu3;
extern __farflash TLCDPict Tab_Menu4;
//-----------------------------------------------------------------------------------
extern TLCDPictTop Scr_13;
extern __farflash TLCDPict_Txt _Txt_0;
extern __farflash TLCDPict_Txt _Txt_1;
extern __farflash TLCDPict_Txt _Txt_2;
extern __farflash TLCDPict_Txt _Txt_3;
extern __farflash TLCDPict_Txt _Txt_4;
//-----------------------------------------------------------------------------------
void M_Get_Controller_Work(u8 id);
void upc_Set_Controller_In_Params(u8 id,u8 addr,u8* value,u8 len);
void regs_to_work();
void work_to_regs();

extern u8 str[40];
extern u8 Common_ID_Mode;
extern u8 Switch_To_ID_1;
extern u8 step;
extern u8 new_step;
extern u8 Current_ID;
extern u8 Branch_Number;
extern  u16 Store_Time;
extern u8 device_ptr;
extern u8 device_id[MAX_DEVICES_NUM];
extern u8 Start_Up_Time;
//-----------------------------------------------------------------------------------
void sh_1_fwd()
{
	new_step=80;
}
void sh_0_fwd()
{
	new_step=81;
}
void sh_0_bck()
{
	new_step=82;
}
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
__farflash TLCDPict Shneck_1_forward=
{	//
	0,18,82,
	(bit_visible+bit_active),
	0,
	0,	
	0,	
	sh_1_fwd,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict Shneck_0_back=
{	//
	0,18+42,81,
	(bit_visible+bit_active),
	0,
	0,	
	0,	
	sh_0_bck,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict Shneck_0_forward=
{	//
	5,18+42,82,
	(bit_visible+bit_active),
	0,
	0,	
	0,	
	sh_0_fwd,
	NULL,
};
//--------------------------------------------
TLCDPictTop Scr_0_2=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	5+3,
	0,	
	scr0_2_init,
	scr0_2_routine,
	scr0_2_close,		
};
//-----------------------------------------------------------------------------------
void scr0_2_init()
{
	u8 i;
	Branch_Number=0;
	new_step=step=0;
	Switch_To_Main_Time=60;
	
	Obj[0]=Tab_Menu0;	
	Obj[1]=Tab_Menu1;	
	Obj[2]=Tab_Menu2;	
	Obj[3]=Tab_Menu3;		
	Obj[4]=Tab_Menu4;	
	
	Obj[2].Stat=1;
		
	Obj[0].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[1].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[2].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[3].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[4].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	

	Obj[5]=Shneck_1_forward;	
	Obj[6]=Shneck_0_forward;	
	Obj[7]=Shneck_0_back;		
}
//-----------------------------------------------------------------------------------
void scr0_2_close()
{
	u8 i;
	for(i=0;i<Scr_0_2.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
	lcd_clear_text();
}
//-----------------------------------------------------------------------------------
void scr0_2_routine()
{
	u8 tmp,tmp2;		
	u16 temp;
	u8 tmp0;//,tmp1,tmp2; lc
	u8 old_stat;
	s16 temperature;
	if(FT_Time!=0)return;
	FT_Time=500;
	if(page_offset!=PAGE_0_OFFSET)return;
}
//-----------------------------------------------------------------------------------

