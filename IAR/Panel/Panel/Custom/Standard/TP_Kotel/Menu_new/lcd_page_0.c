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
#define Obj_Fan_Schedule Obj[12] //13
#define REAL_T_OFF			8
#define PRESET_X_OFFSET		2
#define COM_Y_OFFSET		16

#define KOTEL_MODE_PICTURE_OFFSET	16
//-----------------------------------------------------------------------------------
extern __farflash TLCDPict _Menu0;
extern __farflash TLCDPict _Menu1;
extern __farflash TLCDPict _Menu2;
extern __farflash TLCDPict _Menu3;
extern __farflash TLCDPict _Menu4;
//-----------------------------------------------------------------------------------
extern TLCDPictTop Scr_0;
extern TLCDPictTop Scr_0_1;
extern TLCDPictTop Scr_0_2;
extern TLCDPictTop Scr_0_3;
extern TLCDPictTop Scr_0_4;
//-----------------------------------------------------------------------------------
//extern TLCDPictTop Scr_0;
extern TLCDPictTop Scr_13;
extern __farflash TLCDPict_Txt _Txt_0;
extern __farflash TLCDPict_Txt _Txt_1;
extern __farflash TLCDPict_Txt _Txt_2;
extern __farflash TLCDPict_Txt _Txt_3;
extern __farflash TLCDPict_Txt _Txt_4;
//-----------------------------------------------------------------------------------
#define PID_MODE_STOP		0
#define PID_MODE_AUTO		1
#define PID_MODE_ERROR		2
#define PID_MODE_WARNING	3
//-----------------------------------------------------------------------------------
void M_Get_Controller_Work(u8 id);
void upc_Set_Controller_In_Params(u8 id,u8 addr,u8* value,u8 len);
void upc_Get_Controller_Out_Params(u8 id,u8 addr,u8 len);
void M_Save_Controller_Params(u8 id);

void scr0_init();
void scr0_close();
void scr0_routine();
extern u8 str[40];
extern u8 Common_ID_Mode;
u8 Update_Work_Regs=0;
void regs_to_work();
void work_to_regs();
extern u8 Switch_To_ID_1;
//-----------------------------------------------------------------------------------
void mem_dump(u8 *str,u8 *buff,u8 len);
//-----------------------------------------------------------------------------------
// System variables
u8 Day_Night=0;	
u8 Day_Night_Mode=0;	// 0 - auto 1 - manual
u8 New_Controller_Mode=PID_MODE_STOP;
extern u8 step;
extern u8 new_step;
u8 str[40];
u8 str2[20];
extern u8 Current_ID;
extern u8 Branch_Number;
extern  u16 Store_Time;
extern u8 device_ptr;
extern u8 device_id[MAX_DEVICES_NUM];
extern u8 Start_Up_Time;

u16  exch_params[3];
u16  params[3];
s16 	t_ext;
//-----------------------------------------------------------------------------------

#define B_Smoke 		Obj[7]
#define B_Fan1 			Obj[8]
#define B_Fan2 			Obj[9]
#define B_Shnek1		Obj[10]
#define B_Shnek2		Obj[11]
#define B_Topka			Obj[12]
#define B_Bunker		Obj[13]
#define B_Error			Obj[14]
#define B_Kotel_Mode	Obj[15]
//-----------------------------------------------------------------------------------
void scr0_Update()
{
	u8 old;
	old=B_Smoke.Stat;
	B_Smoke.Stat=0;
	if(ao_smoke!=0)B_Smoke.Stat=1;
	if(B_Smoke.Stat!=old)show_single_bmp(&B_Smoke,0);

	old=B_Fan1.Stat;
	B_Fan1.Stat=0;
	if(ao_air1!=0)B_Fan1.Stat=1;
	if(B_Fan1.Stat!=old)show_single_bmp(&B_Fan1,0);

	old=B_Fan2.Stat;
	B_Fan2.Stat=0;
	if(ao_air2!=0)B_Fan2.Stat=1;
	if(B_Fan2.Stat!=old)show_single_bmp(&B_Fan2,0);

	old=B_Shnek1.Stat;
	B_Shnek1.Stat=0;
	if(do_FORW)B_Shnek1.Stat=1;
	if(B_Shnek1.Stat!=old)show_single_bmp(&B_Shnek1,0);

	old=B_Shnek2.Stat;
	B_Shnek2.Stat=0;
	if(do_FUEL1)B_Shnek2.Stat=1;
	if(B_Shnek2.Stat!=old)show_single_bmp(&B_Shnek2,0);

	old=B_Topka.Stat;
	B_Topka.Stat=0;
	if(di_TOP_O==0)B_Topka.Stat=1;
	if(B_Topka.Stat!=old)show_single_bmp(&B_Topka,0);

	old=B_Bunker.Stat;
	B_Bunker.Stat=0;
	if((di_Fuel_L)==0)B_Bunker.Stat=1;
	if(B_Bunker.Stat!=old)show_single_bmp(&B_Bunker,0);

	old=B_Error.Stat;
	B_Error.Stat=0;
	if((do_Alarm1)!=0)
	{
		if(Time4<500)B_Error.Stat=1;
	}
	if(B_Error.Stat!=old)show_single_bmp(&B_Error,0);
	

	old=B_Kotel_Mode.pict_num;
	B_Kotel_Mode.pict_num=0;
	if(kotel.mode==0)B_Kotel_Mode.pict_num=KOTEL_MODE_PICTURE_OFFSET+0;
	if(kotel.mode==1)B_Kotel_Mode.pict_num=KOTEL_MODE_PICTURE_OFFSET+1;
	if(kotel.mode==2)B_Kotel_Mode.pict_num=KOTEL_MODE_PICTURE_OFFSET+2;
	if(kotel.mode==3)B_Kotel_Mode.pict_num=KOTEL_MODE_PICTURE_OFFSET+3;
	if(kotel.mode==4)B_Kotel_Mode.pict_num=KOTEL_MODE_PICTURE_OFFSET+4;
	if(kotel.mode==5)B_Kotel_Mode.pict_num=KOTEL_MODE_PICTURE_OFFSET+5;
	if(B_Kotel_Mode.Stat!=old)show_single_bmp(&B_Kotel_Mode,0);
}
//-----------------------------------------------------------------------------------
void MainSetMode()
{	
/*	
	if(pid[0].mode!=PID_MODE_STOP){
		pid[0].mode=PID_MODE_STOP;
	}
	else{
		pid[0].mode=PID_MODE_AUTO;
	}
	switch(pid[0].mode)
	{
		case PID_MODE_STOP:_SetMode.pict_num=10;break;
		case PID_MODE_AUTO:_SetMode.pict_num=9;break;
		case PID_MODE_ERROR:_SetMode.pict_num=12;break;
		case PID_MODE_WARNING:_SetMode.pict_num=11;break;	
	}	
*/	
	Button_no_update_time=500;
//	show_single_bmp(&_SetMode,0);
	if(Common_ID_Mode==0)new_step=52;
}
//-----------------------------------------------------------------------------------
void Preset_Plus()
{
	kotel.t=kotel.t+10;
	if(kotel.t>=900)kotel.t=900;	
	Button_no_update_time=500;
	if(Common_ID_Mode==0)new_step=50;
	FT_Time=0;
}
void Preset_Minus()
{
	kotel.t=kotel.t-10;
	if(kotel.t<600)kotel.t=600;	
	Button_no_update_time=500;
	if(Common_ID_Mode==0)new_step=50;
	FT_Time=0;
}
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
__farflash TLCDPict Tab_Menu4=
{	//
	24+0,0,2,
	(bit_visible+bit_active+bit_trigger+bit_new_page),
	0,
	0,	
	0,	
	NULL,
	&Scr_0_4,	
};
//--------------------------------------------
__farflash TLCDPict Tab_Menu3=
{	//
	18+0,0,8,
	(bit_visible+bit_active+bit_trigger+bit_new_page),
	0,
	0,	
	0,	
	NULL,
	&Scr_0_3,	
};
//--------------------------------------------
__farflash TLCDPict Tab_Menu2=
{	//
	12+0,0,7,
	(bit_visible+bit_active+bit_trigger+bit_new_page),
	0,
	0,	
	0,	
	NULL,
	&Scr_0_2,	
};
//--------------------------------------------
__farflash TLCDPict Tab_Menu1=
{	//
	6+0,0,6,
	(bit_visible+bit_active+bit_trigger+bit_new_page),
	0,
	0,	
	0,	
	NULL,
	&Scr_0_1,	
};
//--------------------------------------------
__farflash TLCDPict Tab_Menu0=
{	//
	0+0,0,5,
	(bit_visible+bit_active+bit_trigger+bit_new_page),
	0,
	0,	
	0,	
	NULL,
	&Scr_0,	
};
//--------------------------------------------
__farflash TLCDPict _Device_0=
{	
	0+3*0,104,9,
	(bit_visible),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Device_1=
{	
	0+3*1,104,10,
	(bit_visible),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Device_2=
{	
	0+3*2,104,10,
	(bit_visible),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Device_3=
{	
	0+3*3,104,11,
	(bit_visible),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Device_4=
{	
	0+3*4,104,11,
	(bit_visible),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Device_5=
{	
	0+3*5,104,12,
	(bit_visible),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Device_6=
{	
	0+3*6,104,13,
	(bit_visible),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Device_7=
{	
	0+3*9,104,52,
	(bit_visible+bit_blinking),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Temperature_Mode=
{	
#ifndef __SHEVCHENKO			
	17,101,9,
#else
	0,16,9,
#endif
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	MainSetMode,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Preset_Plus=
{
	4-PRESET_X_OFFSET,59+COM_Y_OFFSET,14,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Preset_Plus,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Preset_Minus=
{
	24-PRESET_X_OFFSET,59+COM_Y_OFFSET,15,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Preset_Minus,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Kotel_Mode=
{
	2+14, 33-REAL_T_OFF+COM_Y_OFFSET, KOTEL_MODE_PICTURE_OFFSET+0,
	(bit_visible+bit_full),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_4=
{
	21-PRESET_X_OFFSET,59+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_3=
{
	19-PRESET_X_OFFSET,59+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_2=
{
	17-PRESET_X_OFFSET,59+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_1=
{
	15-PRESET_X_OFFSET,59+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_0=
{
	13-PRESET_X_OFFSET,59+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_Sign=
{
	11-PRESET_X_OFFSET,59+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _T1_txt_4=
{
	12,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T1_txt_3=
{
	10,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T1_txt_2=
{
	8,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T1_txt_1=
{
	6,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T1_txt_0=
{
	4,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T1_txt_Sign=
{
	2,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _T2_txt_4=
{
	10+18,9-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T2_txt_3=
{
	8+18,9-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T2_txt_2=
{
	6+18,9-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T2_txt_1=
{
	4+18,9-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T2_txt_0=
{
	2+18,9-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T2_txt_Sign=
{
	0+18,9-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
__farflash TLCDPict_Txt _T3_txt_4=
{
	12,9-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T3_txt_3=
{
	10,9-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T3_txt_2=
{
	8,9-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T3_txt_1=
{
	6,9-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T3_txt_0=
{
	4,9-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T3_txt_Sign=
{
	2,9-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
//--------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _T1_txt_Name=
{
	0,9-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T2_txt_Name=
{
	0+16,9-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T3_txt_Name=
{
	0,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_0=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	16,
	0+6+6+6+6+3,	
	scr0_init,
	scr0_routine,
	scr0_close,		
};
//-----------------------------------------------------------------------------------
void scr0_init()
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
	
	Obj[0].Stat=1;
		
	Obj[0].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[1].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[2].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[3].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[4].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	
	Obj[5]=_Preset_Plus;		
	Obj[6]=_Preset_Minus;

	Obj[7]=_Device_0;		
	Obj[8]=_Device_1;		
	Obj[9]=_Device_2;		
	Obj[10]=_Device_3;		
	Obj[11]=_Device_4;	
	Obj[12]=_Device_5;	
	Obj[13]=_Device_6;	
	Obj[14]=_Device_7;	
	Obj[15]=_Kotel_Mode;	
	
	
	Obj[0].Stat=1;
	
	Txt[0]=_T3_txt_Sign;	
	Txt[1]=_T3_txt_0;	
	Txt[2]=_T3_txt_1;	
	Txt[3]=_T3_txt_2;	
	Txt[4]=_T3_txt_3;	
	Txt[5]=_T3_txt_4;	

	Txt[0+6]=_Preset_txt_Sign;	
	Txt[1+6]=_Preset_txt_0;	
	Txt[2+6]=_Preset_txt_1;	
	Txt[3+6]=_Preset_txt_2;	
	Txt[4+6]=_Preset_txt_3;	
	Txt[5+6]=_Preset_txt_4;	

	Txt[0+6+6]=_T1_txt_Sign;	
	Txt[1+6+6]=_T1_txt_0;	
	Txt[2+6+6]=_T1_txt_1;	
	Txt[3+6+6]=_T1_txt_2;	
	Txt[4+6+6]=_T1_txt_3;	
	Txt[5+6+6]=_T1_txt_4;	


	Txt[0+6+6+6]=_T2_txt_Sign;	
	Txt[1+6+6+6]=_T2_txt_0;	
	Txt[2+6+6+6]=_T2_txt_1;	
	Txt[3+6+6+6]=_T2_txt_2;	
	Txt[4+6+6+6]=_T2_txt_3;	
	Txt[5+6+6+6]=_T2_txt_4;		
	
	Txt[6+6+6+6+0]=_T1_txt_Name;
	Txt[6+6+6+6+1]=_T2_txt_Name;
	Txt[6+6+6+6+2]=_T3_txt_Name;
	
	FT_Time=100;
	for(i=0;i<Scr_0.Txt_Num;i++)
		Txt[i].Stat=10;
	
	device_ptr=0;
	Current_ID=device_id[device_ptr];	
}
//-----------------------------------------------------------------------------------
void scr0_close()
{
	u8 i;

	for(i=0;i<Scr_0.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
	lcd_clear_text();
}
//-----------------------------------------------------------------------------------
void custom_handle();
//-----------------------------------------------------------------------------------
void scr0_routine()
{
	u8 tmp,tmp2;		
	u16 temp;
	u8 tmp0;//,tmp1,tmp2; lc
	u8 old_stat;
	s16 temperature;
	if(FT_Time!=0)return;
	FT_Time=500;
	if(page_offset!=PAGE_0_OFFSET)return;

	scr0_Update();
//	lcd_sprintf("abcdefg",0,9);
	tmp='À';
	ByteToStr(lcd_txt,&tmp,0);
//	lcd_sprintf(lcd_txt,0,10);
	tmp='a';
	ByteToStr(lcd_txt,&tmp,0);
//	lcd_sprintf(lcd_txt,0,11);
	tmp='à';
	ByteToStr(lcd_txt,&tmp,0);
//	lcd_sprintf(lcd_txt,0,11);
	
#ifdef __SWITCH_TO_ID_1
	if(Switch_To_ID_1==0)
	{
		Current_ID=1;
	}
#endif				
	Switch_To_Main_Time=60;
	//-----------------------------------------------		
	// Real kotel temperature
	{
		temperature=io.ainput[kotel.channel];	
		if(temperature>999)temperature=999;
		
		LCDMenuPtr_Tmp_Txt=&Txt[6+6+6+6+0];			
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=20;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		
		LCDMenuPtr_Tmp_Txt=&Txt[0];
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;		
		if(temperature<0)
		{
			LCDMenuPtr_Tmp_Txt->Stat=10;
			temp=-temperature;
		}
		else
		{
			LCDMenuPtr_Tmp_Txt->Stat=11;	
			temp=temperature;		
		}
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		
		LCDMenuPtr_Tmp_Txt=&Txt[1];			
		tmp0=temp/100;
		temp-=tmp0*100;	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[3];	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=12;
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
					
		LCDMenuPtr_Tmp_Txt=&Txt[2];				
		tmp0=temp/10;
		temp-=tmp0*10;	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[4];
		tmp0=temp;
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[5];	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;			
		LCDMenuPtr_Tmp_Txt->Stat=15;			
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	}
	//-----------------------------------------------	
	// Real output temperature
	{
		temperature=t_smoke;	
		if(temperature>999)temperature=999;
		
		LCDMenuPtr_Tmp_Txt=&Txt[6+6+6+6+1];			
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=21;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		
		LCDMenuPtr_Tmp_Txt=&Txt[0+6+6];
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;		
		if(temperature<0)
		{
			LCDMenuPtr_Tmp_Txt->Stat=10;
			temp=-temperature;
		}
		else
		{
			LCDMenuPtr_Tmp_Txt->Stat=11;	
			temp=temperature;		
		}
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		
		LCDMenuPtr_Tmp_Txt=&Txt[1+6+6];			
		tmp0=temp/100;
		temp-=tmp0*100;	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[3+6+6];	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=12;
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
					
		LCDMenuPtr_Tmp_Txt=&Txt[2+6+6];				
		tmp0=temp/10;
		temp-=tmp0*10;	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[4+6+6];
		tmp0=temp;
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[5+6+6];	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;			
		LCDMenuPtr_Tmp_Txt->Stat=15;			
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	}	
	//-----------------------------------------------		
	//Smoke
	{
		temperature=t_ext;	
		if(temperature>999)temperature=999;
		
		LCDMenuPtr_Tmp_Txt=&Txt[6+6+6+6+2];			
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=22;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		
		LCDMenuPtr_Tmp_Txt=&Txt[0+6+6+6];
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;		
		if(temperature<0)
		{
			LCDMenuPtr_Tmp_Txt->Stat=10;
			temp=-temperature;
		}
		else
		{
			LCDMenuPtr_Tmp_Txt->Stat=11;	
			temp=temperature;		
		}
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		
		LCDMenuPtr_Tmp_Txt=&Txt[1+6+6+6];			
		tmp0=temp/100;
		temp-=tmp0*100;	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[3+6+6+6];	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=12;
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
					
		LCDMenuPtr_Tmp_Txt=&Txt[2+6+6+6];				
		tmp0=temp/10;
		temp-=tmp0*10;	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[4+6+6+6];
		tmp0=temp;
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[5+6+6+6];	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;			
		LCDMenuPtr_Tmp_Txt->Stat=15;			
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	}
	//-----------------------------------------------	
	// Preset temperature
	temperature=kotel.t;	// Real output temperature
	LCDMenuPtr_Tmp_Txt=&Txt[0+6];
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;		
	if(temperature<0)
	{
		LCDMenuPtr_Tmp_Txt->Stat=10;
		temp=-temperature;
	}
	else
	{
		LCDMenuPtr_Tmp_Txt->Stat=11;	
		temp=temperature;		
	}
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
	LCDMenuPtr_Tmp_Txt=&Txt[1+6];			
	tmp0=temp/100;
	temp-=tmp0*100;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[3+6];	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=12;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
				
	LCDMenuPtr_Tmp_Txt=&Txt[2+6];				
	tmp0=temp/10;
	temp-=tmp0*10;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[4+6];
	tmp0=temp;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[5+6];	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;			
	LCDMenuPtr_Tmp_Txt->Stat=15;			
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	//-----------------------------------------------	
	if(int_state & but_Int3s)
	{
		int_state&=~but_Int3s;	

	ByteToStrFillZero(str,&ft.field.Date,0,2,'0');
	stradd(str,"/");
	ByteToStrFillZero(str2,&ft.field.Month,0,2,'0');
	stradd(str,str2);
	stradd(str,"/20");
	ByteToStrFillZero(str2,&ft.field.Year,0,2,'0');
	stradd(str,str2);
	stradd(str," ");

	ByteToStrFillZero(str2,&ft.field.Hour,0,2,'0');
	if(time_blink & 1){
		stradd(str,str2);stradd(str,":");}
	else{
		stradd(str,str2);stradd(str," ");}
	ByteToStrFillZero(str2,&ft.field.Minute,0,2,'0');stradd(str,str2);
//	lcd_sprintf(str,8,2);
	}	
}
//-----------------------------------------------------------------------------------
void Schedule_N0()
{
//	u16 	i,tmp;
	u16		tmp16;
	u8 		len;
	TWorkInfo *work_info=(TWorkInfo*)&M_rx.field.d[0];

	M_state_machine();
	if((M.status==st_none)||(M.status==st_complete))
	{		
		if((M.error==0)&&(M.rxnew==1))
		{
			M.rxnew=0;
			switch(M_rx.field.com.bit.com)
			{
				case com_get_time:		
					ft=*(TTime*)&M_rx.field.d[0];	
				break;
				case com_get_work_rec:		
					if(Button_no_update_time==0)
					{
						reg_season.season=work_info->season;	
						kotel.mode=work_info->mode;	
						kotel.t=work_info->temperature[0];					
					}
				break;
				case com_get_register:		
					if(Button_no_update_time==0)
					{
						memcpy(&addr,&M_rx.field.d[0],2);		
						len=M_rx.field.d[2];
						memcpy(&reg_data[addr],&M_rx.field.d[3],len);				
					}
				break;					
				case com_get_out_params:		
					memcpy((u8*)&exch_params[0],&M_rx.field.d[0],6);	
					if(M_rx.field.com.bit.id==2)
					{
						memcpy(&params[0],&exch_params[0],6);	
						t_ext=params[0];
//					mem_dump(str,&M_rx.field.d[0],M_rx.field.len);
//					params[0]=*(u16*)&M_rx.field.d[0];
//					params[1]=*(u16*)&M_rx.field.d[2];
//					params[2]=*(u16*)&M_rx.field.d[4];
//					WordToStr(str,&exch_params[0],1);
//					lcd_sprintf(str,0,8);
//					WordToStr(str,&exch_params[1],1);
//					lcd_sprintf(str,0,9);
//					WordToStr(str,&exch_params[2],1);
//					lcd_sprintf(str,0,10);
//					ByteToStr(str,&M_rx.field.len,0);
//					lcd_sprintf(str,0,11);
					//	*/					
					}
				break;					
			}
		}
		// TX section
		if(M_SCH_Time==0)
		{			
			if((Time_To_Save==0)&&(Sign_To_Save!=0))
			{
				step=200;	
				Sign_To_Save=0;
			}
			else
			{
				if(new_step!=0){
					step=new_step;
					new_step=0;
				}
			}
//			if(Start_Up_Time==0)
				if(Update_Work_Regs)
				{
					Update_Work_Regs=0;
					work_to_regs();
					step=100;
					Button_no_update_time=500;
				}			
			if(M_buff_sign)
			{
				M_buff_sign=0;
				M_tx=M_buff;
			//	memcpy(&M_tx,&rx,sizeof(M_tx));
//				BUZZ_Time=50;
				M.txnew=1;
				M.txcount=0;
				M.status=st_sending;		
				M.rxnew=0;
				M.rxcount=0;		
				M.error=0;
				M.done=0;				
			}
			else
			if(Time0==0)
			switch(step)
			{
				case 0:
					step++;
					tmp16=1;
					upc_Set_Controller_In_Params(0,10,(u8*)&tmp16,1);
					M_SCH_Time=50;
				break;				
				case 1:
					step++;
					M_Get_Controller_Time(1,1);
					M_SCH_Time=50;
				break;				
				case 2:
					step++;
					M_Get_Controller_Register(1,&io,sizeof(TIO));	
					M_SCH_Time=50;					
				break;
				case 3:
					M_Get_Controller_Register(1,&MenuRegs,sizeof(TMenuRegisters));
					step++;					
					M_SCH_Time=50;	
				break;
				case 4:
					M_Get_Controller_Register(1,&kotel.mode,18+5);
					step++;					
					M_SCH_Time=50;	
				break;
				case 5:
					upc_Get_Controller_Out_Params(2,0,3);
					step++;					
					M_SCH_Time=50;	
				break;
				case 6:
					upc_Set_Controller_In_Params(1,0,(u8*)&exch_params[0],3);
					step++;					
					M_SCH_Time=50;	
				break;
				case 7:
					upc_Get_Controller_Out_Params(1,0,3);
					step++;					
					M_SCH_Time=50;	
				break;
				case 8:
					upc_Set_Controller_In_Params(2,0,(u8*)&exch_params[0],3);
					step++;					
					M_SCH_Time=50;	
				break;
				case 9:
//					tmp16=1;
//					upc_Set_Controller_In_Params(0,10,(u8*)&tmp16,1);
					step++;					
//					M_SCH_Time=50;	
				break;
				
				
			
				case 50:
					M_Set_Controller_Register(1,&kotel.t,2);				
					step=0;					
					M_SCH_Time=50;	
					Time_To_Save=3000;
				break;
				case 51:
					 //upc_Set_Controller_In_Params(Current_ID,0,(u8*)&pritochka_fan_speed,1);
					step=0;					
					M_SCH_Time=50;
					Time_To_Save=3000;
				break;
				case 52:
					//M_Set_Controller_Register(Current_ID,&kotel.mode,1);				
					step=0;					
					M_SCH_Time=50;	
					Time_To_Save=3000;
				break;
				
				// Get kotel registers
				case 60:
					M_Get_Controller_Register(1,&kotel.mode,18+5);
					step++;					
					M_SCH_Time=50;	
				break;
				case 61:
					M_Get_Controller_Register(1,&kotel.p[0][0],sizeof(TKotelModeRec));				
					step++;					
					M_SCH_Time=50;	
				break;
				case 62:
					M_Get_Controller_Register(1,&kotel.p[0][1],sizeof(TKotelModeRec));				
					step++;					
					M_SCH_Time=50;	
				break;
				case 63:
					M_Get_Controller_Register(1,&kotel.p[0][2],sizeof(TKotelModeRec));				
					step++;					
					M_SCH_Time=50;	
				break;
				case 64:
					M_Get_Controller_Register(1,&kotel.p[0][3],sizeof(TKotelModeRec));				
					step=60;					
					M_SCH_Time=50;	
				break;
				// set kotel registers
				case 70:
					M_Set_Controller_Register(1,&kotel.p[0][0],sizeof(TKotelModeRec));				
					step=60;					
					M_SCH_Time=50;	
					Time_To_Save=3000;
				break;
				case 71:
					M_Set_Controller_Register(1,&kotel.p[0][1],sizeof(TKotelModeRec));				
					step=60;					
					M_SCH_Time=50;	
					Time_To_Save=3000;
				break;
				case 72:
					M_Set_Controller_Register(1,&kotel.p[0][2],sizeof(TKotelModeRec));				
					step=60;					
					M_SCH_Time=50;	
					Time_To_Save=3000;
				break;
				case 73:
					M_Set_Controller_Register(1,&kotel.p[0][3],sizeof(TKotelModeRec));				
					step=60;					
					M_SCH_Time=50;	
					Time_To_Save=3000;
				break;
				case 74:
					M_Set_Controller_Register(1,&kotel.smoke_speed,MAX_KOTEL_FUELS);				
					step=60;					
					M_SCH_Time=50;	
					Time_To_Save=3000;
				break;

				case 80:
					tmp16=sh_1_for;
//					upc_Set_Controller_In_Params(1,shnek,(u8*)&tmp16,1);
					params[2]|=(1<<2);
					upc_Set_Controller_In_Params(2,2,(u8*)&params[2],1);					
					step=0;					
					M_SCH_Time=50;	
				break;
				case 81:
					tmp16=sh_0_for;
					upc_Set_Controller_In_Params(1,shnek,(u8*)&tmp16,1);
					step=0;					
					M_SCH_Time=50;	
				break;
				case 82:
					tmp16=sh_0_back;
					upc_Set_Controller_In_Params(1,shnek,(u8*)&tmp16,1);
					step=0;					
					M_SCH_Time=50;	
				break;

				// Update work record at controller 1
				case 100:
					if(Start_Up_Time!=0){step=0;break;}
//					M_Set_Controller_Register(1,&fan[0],sizeof(fan[0]));					
					step++;					
					M_SCH_Time=10;	
					Time_To_Save=3000;
				break;
				
				case 200:
					// Save parameters
					M_Save_Controller_Params(0);
					step=0;					
					M_SCH_Time=200;	
				break;					

				default:
					step=0;					
				break;
				
			}
		}
		
	}
	
}
//-----------------------------------------------------------------------------------

