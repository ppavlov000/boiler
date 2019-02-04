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
#define Obj_Fan_Schedule Obj[12]
//-----------------------------------------------------------------------------------
extern __farflash TLCDPict _Menu0;
extern __farflash TLCDPict _Menu1;
extern __farflash TLCDPict _Menu2;
extern __farflash TLCDPict _Menu3;
extern __farflash TLCDPict _Menu4;
//-----------------------------------------------------------------------------------
//extern TLCDPictTop Scr_0;
extern TLCDPictTop Scr_12;
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
void scr0_init();
void scr0_close();
void scr0_routine();
extern u8 str[40];
extern u8 Common_ID_Mode;

u8 Update_Work_Regs=0;
void regs_to_work();
void work_to_regs();
//-----------------------------------------------------------------------------------
#define _SetMode 		Obj[20]
//#define _Season_butt 	Obj[20]
#define _Day_butt 		Obj[12]
#define _Update_butt	Obj[20]

#define _Season_butt Obj[11]	
#define _Auto_butt Obj[9]	
//-----------------------------------------------------------------------------------
// System variables
//s16 Temperature[3]={0};
//s16 Preset=220;
//u16 Fan_Speed=0;
//u8 Controller_Mode=0; // Auto Manual
//u8 Season=0;
//extern TSeason Season;
//u8 Season_Mode=1;		// 0 - auto 1 - manual
//u8 Day_Night=0;	
u8 Day_Night_Mode=0;	// 0 - auto 1 - manual
// Temporary variables
//s16 New_Preset=0;
//u16 New_Fan_Speed=0;
//u8 New_Controller_Mode=PID_MODE_STOP;
extern u8 step;
extern u8 new_step;
u8 str[40];
u8 str2[20];
extern u8 Current_ID;
extern u8 Branch_Number;
extern  u16 Store_Time;
//********************************************
//********************************************
//********************************************
//--------------------------------------------
u8 FAN_Number=1;
//u8 FAN_Speed=0;
//s16 Temperature=0;
#define FAN_N_1 		Obj[1+5]
#define FAN_N_2 		Obj[2+5]
#define FAN_N_3 		Obj[3+5]

#define FAN_SPEED 		Obj[5+5]
//--------------------------------------------
void Choose_FAN_1()
{
	FAN_Number=1;	
//	if(FAN_N_1.Stat!=0){
//		FAN_N_1.Stat=0;
//		show_single_bmp(&FAN_N_1,0);
//	}
	if(FAN_N_2.Stat!=0){
		FAN_N_2.Stat=0;
		show_single_bmp(&FAN_N_2,0);
	}
	if(FAN_N_3.Stat!=0){
		FAN_N_3.Stat=0;
		show_single_bmp(&FAN_N_3,0);
	}	
}
//-----------------------------------------------------------------------------------
void Choose_FAN_2()
{
	FAN_Number=2;	
	if(FAN_N_1.Stat!=0){
		FAN_N_1.Stat=0;
		show_single_bmp(&FAN_N_1,0);
	}
//	if(FAN_N_2.Stat!=0){
//		FAN_N_2.Stat=0;
//		show_single_bmp(&FAN_N_2,0);
//	}
	if(FAN_N_3.Stat!=0){
		FAN_N_3.Stat=0;
		show_single_bmp(&FAN_N_3,0);
	}	
}
//-----------------------------------------------------------------------------------
void Choose_FAN_3()
{
	FAN_Number=3;	
	if(FAN_N_1.Stat!=0){
		FAN_N_1.Stat=0;
		show_single_bmp(&FAN_N_1,0);
	}
	if(FAN_N_2.Stat!=0){
		FAN_N_2.Stat=0;
		show_single_bmp(&FAN_N_2,0);
	}
}
//-----------------------------------------------------------------------------------
void Choose_SPEED()
{
	u8 tmp;
	{
		fan[0].Fan_Lvl++;
		if(fan[0].Fan_Lvl>3)fan[0].Fan_Lvl=0;
		if(FAN_SPEED.pict_num!=81+fan[0].Fan_Lvl)
		{
			FAN_SPEED.pict_num=81+fan[0].Fan_Lvl;
			show_single_bmp(&FAN_SPEED,0);
		}
	}		
//	fan[0].Fan_Lvl=FAN_Speed;
	{
		fan[0].Fan_Mode=1; // Manual mode always
		tmp=_Auto_butt.Stat;
		if(fan[0].Fan_Mode==0)
			_Auto_butt.Stat=1;
		else
			_Auto_butt.Stat=0;
		if((tmp!=_Auto_butt.Stat))show_single_bmp(&_Auto_butt,0);	
		
		Button_no_update_time=500;
		if(Common_ID_Mode==0)new_step=61;	
	}
}
//-----------------------------------------------------------------------------------
void scr0_Auto_Manual()
{
	FT_Time=0;
//	m.sch_auto_manual=1;
//	if(m.sch_day_night==0)
//		m.sch_day_night=1;
//	else
//		m.sch_day_night=0;
//	if(m.sch_day_night==0)fan[0].T=m.sch_temperature[0];
//	if(m.sch_day_night==1)fan[0].T=m.sch_temperature[1];
	if(fan[0].Day_Night==fan_Day)
	{
		fan[0].Day_Night=fan_Night;
		m.BackLit_Value_Min=0;
		m.BackLit_Value_Max=5;	
	}
	else
	{
		m.BackLit_Value_Min=2;
		m.BackLit_Value_Max=9;
		fan[0].Day_Night=fan_Day;
	}
	Button_no_update_time=500;
	FT_Time=0;	
	Store_Time=5000;	
	if(Common_ID_Mode==0)new_step=62;
}
//-----------------------------------------------------------------------------------
void Update()
{
	u8 tmp;		

	if(FAN_SPEED.pict_num!=81+fan[0].Fan_Lvl)
	{
		FAN_SPEED.pict_num=81+fan[0].Fan_Lvl;
		show_single_bmp(&FAN_SPEED,0);
	}
	// Season
	tmp=_Season_butt.Stat;
	if(MenuRegs.Season.season==0)
		_Season_butt.Stat=1;
	else
		_Season_butt.Stat=0;
	if((tmp!=_Season_butt.Stat))show_single_bmp(&_Season_butt,0);	

	// Day/Night
	tmp=_Day_butt.Stat;
	if(fan[0].Day_Night==fan_Day)
		_Day_butt.Stat=0;
	else
		_Day_butt.Stat=1;
	if((tmp!=_Day_butt.Stat))show_single_bmp(&_Day_butt,0);	
	
	// Mode
//	u8 tmp;		
	tmp=_Auto_butt.Stat;
	if(fan[0].Fan_Mode==0)
		_Auto_butt.Stat=1;
	else
		_Auto_butt.Stat=0;
	if((tmp!=_Auto_butt.Stat))show_single_bmp(&_Auto_butt,0);	
}
//-----------------------------------------------------------------------------------
void Preset_Plus()
{
	fan[0].T=fan[0].T+1;
	if(fan[0].T>=400)	fan[0].T=400;	
	Button_no_update_time=500;
	if(Common_ID_Mode==0)new_step=63;
	FT_Time=0;
	
}
//-----------------------------------------------------------------------------------
void Preset_Minus()
{
	fan[0].T=fan[0].T-1;
	if(fan[0].T<=140)fan[0].T=140;	
	Button_no_update_time=500;
	if(Common_ID_Mode==0)new_step=63;
	FT_Time=0;
}
//-----------------------------------------------------------------------------------
void scr0_Season()
{
	if(MenuRegs.Season.season==SEASON_SUMMER)
	{
		MenuRegs.Season.season=SEASON_WINTER;
		pid[0].heating_cooling=PID_HEATING;		
		
	}
	else
	{
		MenuRegs.Season.season=SEASON_SUMMER;
		pid[0].heating_cooling=PID_COOLING;		
	}
	Button_no_update_time=500;
	FT_Time=0;		
	if(Common_ID_Mode==0)new_step=64;
}
//-----------------------------------------------------------------------------------
void scr0_Mode()
{
//	if(Controller_Mode==0)Controller_Mode=1;
//	else Controller_Mode=0;

	if(fan[0].Fan_Mode==0)fan[0].Fan_Mode=1;
	else fan[0].Fan_Mode=0;
	
	Button_no_update_time=500;
	FT_Time=0;			
	if(Common_ID_Mode==0)new_step=60;
}
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Preset_Plus=
{
	5,48,89,
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
	22,48,88,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Preset_Minus,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Temperature_Main=
{	
	0,48,86,
//	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------

__farflash TLCDPict _Temperature_Night=
{	
	25,48,77,
//	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,
	0,	
	scr0_Auto_Manual,
	NULL,
};
/*
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Temperature_Night=
{
	25,48,18,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr0_Auto_Manual,
	NULL,
};
*/
//--------------------------------------------
__farflash TLCDPict _Temperature_Fan_1=
{	
	0,0,78,
//	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,
	0,	
	Choose_FAN_1,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Temperature_Fan_2=
{	
	5,0,79,
//	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,
	0,	
	Choose_FAN_2,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Temperature_Fan_3=
{	
	10,0,80,
//	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,
	0,	
	Choose_FAN_3,
	NULL,
};

//--------------------------------------------
__farflash TLCDPict _Temperature_Auto=
{	
	0,88,87,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr0_Mode,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Temperature_Speed=
{	
	10,88,81,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Choose_SPEED,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict __Temperature_Season=
{	
	20,88,85,
	(bit_visible+bit_active+bit_trigger),
//	0,
	0,
	0,
	0,	
	scr0_Season,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Temperature_Adjust=
{
	10,60,75,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,	
	NULL,
	&Scr_12,		
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_5=
{
	21,26,53,
	(bit_visible+bit_txt_1),
	15,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_4=
{
	19,26,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_3=
{
	17,26,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_2=
{
	15,26,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_1=
{
	13,26,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_0=
{
	11,26,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_Sign=
{
	9,26,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
//--------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_5=
{
	21,59,53,
	(bit_visible+bit_txt_1),
	15,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_4=
{
	19,59,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_3=
{
	17,59,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_2=
{
	15,59,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_1=
{
	13,59,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_0=
{
	11,59,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_Sign=
{
	9,59,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
//--------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _Fan_txt_4=
{
	21,80,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Fan_txt_3=
{
	19,80,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Fan_txt_2=
{
	17,80,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Fan_txt_1=
{
	15,80,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Fan_txt_0=
{
	13,80,53,
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
	15,
	7+7,	
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
	Obj[0]=_Menu0;	
	Obj[1]=_Menu1;	
	Obj[2]=_Menu2;	
	Obj[3]=_Menu3;		
	Obj[4]=_Menu4;	
	
/*
	Obj[5]=_Temperature_Mode;		
	Obj[6]=_Temperature_Season;		

	Obj[7]=_Preset_Plus;		
	Obj[8]=_Preset_Minus;

	Obj[9]=_Fan_Plus;		
	Obj[10]=_Fan_Minus;
	
	Obj[11]=_Fan_Winter;		
	Obj[12]=_Fan_Schedule;
	
	Obj[13]=_Fan_Description;
	Obj[14]=_Fan_Mode;				
	Obj[15]=_Fan_Update;				

*/
	Obj[5]=_Temperature_Main;	
	Obj[6]=_Temperature_Fan_1;	
	Obj[7]=_Temperature_Fan_2;	
	Obj[8]=_Temperature_Fan_3;		

	Obj[9]=_Temperature_Auto;	
	Obj[10]=_Temperature_Speed;	
	Obj[11]=__Temperature_Season;		
	Obj[12]=_Temperature_Night;	

	Obj[13]=_Preset_Plus;		
	Obj[14]=_Preset_Minus;
	
//	Obj[14].Stat=1;
//	Obj[0].Stat=1;
//	Obj[5]=_Temperature_Speed;	
//	Obj[6]=_Temperature_Season;		
//	Obj[7]=_Temperature_Night;		
//	Obj[8]=_Temperature_Adjust;		
	
	
	Txt[0]=_Temperature_txt_Sign;	
	Txt[1]=_Temperature_txt_0;	
	Txt[2]=_Temperature_txt_1;	
	Txt[3]=_Temperature_txt_2;	
	Txt[4]=_Temperature_txt_3;	
	Txt[5]=_Temperature_txt_4;	
	Txt[6]=_Temperature_txt_5;	

	Txt[0+7]=_Preset_txt_Sign;	
	Txt[1+7]=_Preset_txt_0;	
	Txt[2+7]=_Preset_txt_1;	
	Txt[3+7]=_Preset_txt_2;	
	Txt[4+7]=_Preset_txt_3;	
	Txt[5+7]=_Preset_txt_4;	
	Txt[6+7]=_Preset_txt_5;	

	Txt[0+7+7]=_Fan_txt_0;	
	Txt[1+7+7]=_Fan_txt_1;	
	Txt[2+7+7]=_Fan_txt_2;	
	Txt[3+7+7]=_Fan_txt_3;	
	Txt[4+7+7]=_Fan_txt_4;	
	
	FT_Time=100;
	for(i=0;i<Scr_0.Txt_Num;i++)
		Txt[i].Stat=10;
	
	pid[0].heating_cooling=PID_HEATING;	
	pid[1].heating_cooling=PID_COOLING;		
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
//	u8 tmp,tmp2;		
	u16 temp;
	u8 tmp0;//,tmp1,tmp2; lc
	u8 old_stat;
	s16 temperature;
	if(FT_Time!=0)return;
	FT_Time=500;
	if(page_offset!=PAGE_0_OFFSET)return;
	Switch_To_Main_Time=60;	
	//-----------------------------------------------		
	fan[0].Day_Night=fan_Day;
	pid[0].t0=fan[0].T;
	pid[1].t0=fan[0].T;		
	if(MenuRegs.Season.season==SEASON_SUMMER)
	{
		pid[0].heating_cooling=PID_COOLING;		
	}
	else
	{
		pid[0].heating_cooling=PID_HEATING;		
	}
	
	custom_handle();
	// Update buttons with parameters
	Update();
	//-----------------------------------------------		
//	return;
//	custom_handle();
	//-----------------------------------------------		
/*	//-----------------------------------------------	
	if(Common_ID_Mode==0)
		Update_Season();
	//-----------------------------------------------		
	tmp=_SetMode.pict_num;
	if(Button_no_update_time==0)
	switch(Controller_Mode)
	{
		case PID_MODE_STOP:_SetMode.pict_num=10;break;
		case PID_MODE_AUTO:_SetMode.pict_num=9;break;
		case PID_MODE_ERROR:_SetMode.pict_num=12;break;
		case PID_MODE_WARNING:_SetMode.pict_num=11;break;	
	}		
	if(tmp!=_SetMode.pict_num)show_single_bmp(&_SetMode,0);
*/	
	//-----------------------------------------------	
	if(Common_ID_Mode==0){
		// Real temperature
		temperature=io.ainput[1]+m.adjust_temperature[0];	// Real output temperature
		if(temperature>999)temperature=999;
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
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		
		LCDMenuPtr_Tmp_Txt=&Txt[1];			
		tmp0=temp/100;
		temp-=tmp0*100;	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[3];	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=12;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
					
		LCDMenuPtr_Tmp_Txt=&Txt[2];				
		tmp0=temp/10;
		temp-=tmp0*10;	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[4];
		tmp0=temp;
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[5];	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;			
		LCDMenuPtr_Tmp_Txt->Stat=15;			
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	}
	//-----------------------------------------------	
	// Preset temperature
	temperature=fan[0].T+m.adjust_temperature[0];	// Real output temperature
//	if(temperature>500)temperature=0;
	LCDMenuPtr_Tmp_Txt=&Txt[0+7];
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
	
	LCDMenuPtr_Tmp_Txt=&Txt[1+7];			
	tmp0=temp/100;
	temp-=tmp0*100;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[3+7];	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=12;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
				
	LCDMenuPtr_Tmp_Txt=&Txt[2+7];				
	tmp0=temp/10;
	temp-=tmp0*10;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[4+7];
	tmp0=temp;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[5+7];	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;			
	LCDMenuPtr_Tmp_Txt->Stat=15;			
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	//-----------------------------------------------	
	//-----------------------------------------------	
	//-----------------------------------------------	
	
	if(int_state & but_Int3s)
	{
		int_state&=~but_Int3s;	

	ByteToStrFillZero(str,&MenuRegs.Time.field.Date,0,2,'0');
	stradd(str,"/");
	ByteToStrFillZero(str2,&MenuRegs.Time.field.Month,0,2,'0');
	stradd(str,str2);
	stradd(str,"/20");
	ByteToStrFillZero(str2,&MenuRegs.Time.field.Year,0,2,'0');
	stradd(str,str2);
	stradd(str," ");

	ByteToStrFillZero(str2,&MenuRegs.Time.field.Hour,0,2,'0');
	if(time_blink & 1){
		stradd(str,str2);stradd(str,":");}
	else{
		stradd(str,str2);stradd(str," ");}
	ByteToStrFillZero(str2,&MenuRegs.Time.field.Minute,0,2,'0');stradd(str,str2);
	lcd_sprintf(str,14,2);
	}	
}
//-----------------------------------------------------------------------------------
void Schedule_N0()
{
	u16 addr;
	u8 len;
	M_state_machine();
	if((M.status==st_none)||(M.status==st_complete))
	{		
		if((M.error==0)&&(M.rxnew==1))
		{
			M.rxnew=0;
			switch(M_rx.field.com.bit.com)
			{
				case com_get_register:		
					if(Button_no_update_time==0)
					{
						memcpy(&addr,&M_rx.field.d[0],2);		
						len=M_rx.field.d[2];
						memcpy(&reg_data[addr],&M_rx.field.d[3],len);	
					}
				break;						
			}
		}
		if(M_SCH_Time==0)
		{			

			if(new_step!=0){
				step=new_step;
				new_step=0;
			}
			if(Update_Work_Regs)
			{
				Update_Work_Regs=0;
				work_to_regs();
				step=100;
			}			
			if(M_buff_sign)
			{
				M_buff_sign=0;
				M_tx=M_buff;
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
					M_SCH_Time=100;	
					M_Get_Controller_Register(Current_ID,&io.ainput[0],6);	
				break;
				case 1:		
					step++;
					M_SCH_Time=100;	
					M_Get_Controller_Register(Current_ID,&MenuRegs.Time,sizeof(MenuRegs.Time));	
				break;
				case 2:		
					step++;
					M_SCH_Time=100;	
					M_Get_Controller_Register(Current_ID,&fan[0].T,sizeof(fan[0]));
				break;
				case 3:		
					step++;
					M_SCH_Time=100;	
					M_Get_Controller_Register(Current_ID,&MenuRegs.Season.season,1);
				break;
				case 4:		
					step++;
					M_SCH_Time=100;	
					M_Get_Controller_Register(Current_ID,&errors,sizeof(errors));
				break;
				case 5:
					// Temperature PID[0]
					M_Set_Controller_Register(Current_ID,&pid[0].t0,2);					
					step++;					
					M_SCH_Time=10;	
				break;
				case 6:
					// Temperature PID[1]
					M_Set_Controller_Register(Current_ID,&pid[1].t0,2);					
					step++;					
					M_SCH_Time=10;	
				break;
				case 7:
					// Temperature PID[1]
					M_Set_Controller_Register(Current_ID,&pid[0].heating_cooling,1);					
					step++;					
					M_SCH_Time=10;	
				break;
				case 8:
					// Temperature PID[1]
					M_Set_Controller_Register(Current_ID,&pid[1].heating_cooling,1);					
					step++;					
					M_SCH_Time=10;	
				break;
				case 9:
					// Temperature PID[1]
					fan[0].Day_Night=fan_Day;
					M_Set_Controller_Register(Current_ID,&fan[0].Day_Night,1);
					step++;					
					M_SCH_Time=10;	
				break;

				
				case 60:
					// Only Fan mode
					M_Set_Controller_Register(Current_ID,&fan[0].Fan_Mode,1);					
					step=0;					
					M_SCH_Time=10;	
				break;
				case 61:
					// Fan mode + Fan speed
					M_Set_Controller_Register(Current_ID,&fan[0].Fan_Mode,2);					
					step=0;					
					M_SCH_Time=10;	
				break;
				case 62:
					// Day/Night
					M_Set_Controller_Register(Current_ID,&fan[0].Day_Night,1);					
					step=0;					
					M_SCH_Time=10;	
				break;
				case 63:
					// Temperature
					M_Set_Controller_Register(Current_ID,&fan[0].T,2);					
					step=0;					
					M_SCH_Time=10;	
				break;
				case 64:
					// Season
					M_Set_Controller_Register(Current_ID,&MenuRegs.Season.season,1);					
					step=0;					
					M_SCH_Time=10;	
				break;
				case 65:
					// Errors
					memset(&errors,0,sizeof(errors));
					M_Set_Controller_Register(Current_ID,&errors,sizeof(errors));					
					step=0;					
					M_SCH_Time=10;	
				break;

				// Update work record
				case 100:
					// FAN
					M_Set_Controller_Register(Current_ID,&fan[0],sizeof(fan[0]));					
					step++;					
					M_SCH_Time=10;	
				break;
				case 101:
					// Season
					M_Set_Controller_Register(Current_ID,&MenuRegs.Season.season,1);					
					step++;					
					M_SCH_Time=10;	
				break;
				
				default:
					step=0;	
				break;
			}
		}
		
	}
	
}
//-----------------------------------------------------------------------------------

