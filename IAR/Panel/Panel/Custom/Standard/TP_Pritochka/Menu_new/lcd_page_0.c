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
#define _SetMode 		Obj[5]
#define _Season_butt 	Obj[11]
#define _Day_butt 		Obj[12]
#define _Update_butt	Obj[15]

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
*/
//-----------------------------------------------------------------------------------
// System variables
s16 Temperature[3]={0};
//s16 Preset=220;
//u16 Fan_Speed=0;
//u8 Controller_Mode=PID_MODE_STOP;
//u8 Season=0;
//extern TSeason Season;
//u8 Season_Mode=1;		// 0 - auto 1 - manual
u8 Day_Night=0;	
u8 Day_Night_Mode=0;	// 0 - auto 1 - manual
// Temporary variables
//s16 New_Preset=0;
//u16 New_Fan_Speed=0;
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
s16 T_Room=0;
//-----------------------------------------------------------------------------------
void scr0_Update()
{
	new_step=40; // Send updating information 3 times
}
//-----------------------------------------------------------------------------------
void scr0_Auto_Manual()
{
	FT_Time=0;
	m.sch_auto_manual=1;
	if(m.sch_day_night==0)
		m.sch_day_night=1;
	else
		m.sch_day_night=0;
	if(m.sch_day_night==0)pid[0].t0=m.sch_temperature[0];
	if(m.sch_day_night==1)pid[0].t0=m.sch_temperature[1];
	Button_no_update_time=500;
	FT_Time=0;	
	Store_Time=5000;	
	if(Common_ID_Mode==0)new_step=50;
}
//-----------------------------------------------------------------------------------
void scr0_Season()
{
	if(reg_season.season==0)reg_season.season=1;
	else reg_season.season=0;
	reg_season.mode=1; // Manual
	Button_no_update_time=500;
	FT_Time=0;		
	if(Common_ID_Mode==0)new_step=31;
}
//-----------------------------------------------------------------------------------
void Update_Season()
{
	u8 tmp,tmp1;		
	tmp=_Season_butt.pict_num;
	tmp1=_Season_butt.Stat;
	if(reg_season.season==0){
		_Season_butt.Stat=1;
		if(reg_season.mode==0)_Season_butt.pict_num=16;
		else _Season_butt.pict_num=17;
	}
	else{
		_Season_butt.Stat=0;
		if(reg_season.mode==0)_Season_butt.pict_num=16;
		else _Season_butt.pict_num=17;
	}
	if((tmp!=_Season_butt.pict_num)||(tmp1!=_Season_butt.Stat))show_single_bmp(&_Season_butt,0);	
}
//-----------------------------------------------------------------------------------
void Update_Day_Night()
{
	u8 tmp,tmp1;		
	tmp=_Day_butt.pict_num;
	tmp1=_Day_butt.Stat;
	if(Day_Night==0){
		_Day_butt.Stat=1;
		if(Day_Night_Mode==0)_Day_butt.pict_num=18;
		else _Day_butt.pict_num=19;
	}
	else{
		_Day_butt.Stat=0;
		if(Day_Night_Mode==0)_Day_butt.pict_num=18;
		else _Day_butt.pict_num=19;
	}
	if((tmp!=_Day_butt.pict_num)||(tmp1!=_Day_butt.Stat))show_single_bmp(&_Day_butt,0);	
}
//-----------------------------------------------------------------------------------
void MainSetMode()
{	
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
	Button_no_update_time=500;
	show_single_bmp(&_SetMode,0);
	if(Common_ID_Mode==0)new_step=52;
}
//-----------------------------------------------------------------------------------
void MainSetID()
{	
	if(Current_ID!=0)
	{
		if(device_ptr<MAX_DEVICES_NUM-1)
		{
			device_ptr++;
//			if(device_id[device_ptr]==0){Current_ID=0;Common_ID_Mode=1;return;}
			if(device_id[device_ptr]==0){device_ptr=0;}			
			Current_ID=device_id[device_ptr];	
		}
	}
	else
	{
		device_ptr=0;
		Current_ID=device_id[device_ptr];	
		Common_ID_Mode=0;
	}
	FT_Time=0;	
}
//-----------------------------------------------------------------------------------
void Preset_Plus()
{
	pid[0].t0=pid[0].t0+1;
	if(pid[0].t0>=500)	pid[0].t0=500;	
	Button_no_update_time=500;
	if(Common_ID_Mode==0)new_step=50;
	FT_Time=0;
	
}
void Preset_Minus()
{
	pid[0].t0=pid[0].t0-1;
	if(pid[0].t0<=140)	pid[0].t0=140;	
	Button_no_update_time=500;
	if(Common_ID_Mode==0)new_step=50;
	FT_Time=0;
}
//-----------------------------------------------------------------------------------
void Fan_Plus()
{
	pritochka_fan_speed=pritochka_fan_speed+10;
	if(pritochka_fan_speed>=999)pritochka_fan_speed=999;	
	if(pritochka_fan_speed<10)pritochka_fan_speed=10;
	io.aoutput[0]=pritochka_fan_speed;
	Button_no_update_time=500;
	if(Common_ID_Mode==0)new_step=51;
	FT_Time=0;
}
void Fan_Minus()
{
	if(pritochka_fan_speed>=400)pritochka_fan_speed=pritochka_fan_speed-10;
	else pritochka_fan_speed=400;
	io.aoutput[0]=pritochka_fan_speed;
	Button_no_update_time=500;
	if(Common_ID_Mode==0)new_step=51;
	FT_Time=0;
}
//--------------------------------------------
__farflash TLCDPict _Temperature_Season=
{	
	0,58,16,
//	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _ID=
{	
	0,16,93,
#ifdef __ID_BUTTON		
	(bit_visible+bit_active),
#else
	0,
#endif	
	0,
	0,
	0,	
	MainSetID,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Temperature_Mode=
{	
#ifdef __ID_BUTTON			
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
	6,59,14,
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
	24,59,15,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Preset_Minus,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Fan_Plus=
{
	6,80,14,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Fan_Plus,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Fan_Minus=
{
	24,80,15,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Fan_Minus,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Fan_Description=
{
	0,59,20,
	(bit_visible+bit_full),
	0,
	0,
	0,	
	Fan_Minus,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Fan_Winter=
{
	6,101,17,
//	(bit_visible+bit_active+bit_trigger),
	(bit_visible),
	0,
	0,
	0,	
//	scr0_Season,
	NULL,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Fan_Schedule=
{
	0,101,18,
#ifdef __WEEK_SCHEDULE_ENABLE	
	(bit_visible),//+bit_active+bit_trigger),
#else
	0,
#endif	
	0,
	0,
	0,	
//	scr0_Auto_Manual,
	NULL,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Fan_Mode=
{
	14,101,21,
	0,//(bit_visible),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Fan_Update=
{
	17,101,76,
	0,
	0,
	0,
	0,	
//	scr0_Update,
	NULL,
	NULL,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _ID_txt_1=
{
	9,26,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _ID_txt_0=
{
	7,26,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_5=
{
	28,26,53,
	(bit_visible+bit_txt_1),
	15,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_4=
{
	26,26,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_3=
{
	24,26,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_2=
{
	22,26,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_1=
{
	20,26,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_0=
{
	18,26,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_Sign=
{
	16,26,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
//--------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_5=
{
	23,59,53,
	(bit_visible+bit_txt_1),
	15,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_4=
{
	21,59,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_3=
{
	19,59,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_2=
{
	17,59,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_1=
{
	15,59,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_0=
{
	13,59,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_Sign=
{
	11,59,53,
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
	17,
	5+7+7+2,	
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

	Obj[16]=_ID;				
	
	Obj[14].Stat=1;
	Obj[0].Stat=1;
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

	Txt[5+7+7]=_ID_txt_0;	
	Txt[6+7+7]=_ID_txt_1;	
	
	FT_Time=100;
	for(i=0;i<Scr_0.Txt_Num;i++)
		Txt[i].Stat=10;
	
	if(m.sch_auto_manual==0)
		Obj_Fan_Schedule.pict_num=18;
	else
		Obj_Fan_Schedule.pict_num=19;
	
	if(m.sch_day_night==0)
		Obj_Fan_Schedule.Stat=0;
	else
		Obj_Fan_Schedule.Stat=1;

//	if(Current_ID==0)
//		_Update_butt.Flag=(bit_visible+bit_active);
//	else
//		_Update_butt.Flag=0;
//	_Update_butt.Stat=0;
	
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
#ifdef __SWITCH_TO_ID_1	
		if(Switch_To_ID_1==0)
		{
			Current_ID=0;
			MainSetID();
		}
#endif				
	Switch_To_Main_Time=60;
	custom_handle();
	pid[0].heating_cooling=PID_HEATING;	
	pid[1].heating_cooling=PID_COOLING;			
	//-----------------------------------------------		
	tmp=Obj_Fan_Schedule.pict_num;
	tmp2=Obj_Fan_Schedule.Stat;
	if(m.sch_auto_manual==0)
		Obj_Fan_Schedule.pict_num=18;
	else
		Obj_Fan_Schedule.pict_num=19;
	
	if(m.sch_day_night==0)
		Obj_Fan_Schedule.Stat=0;
	else
		Obj_Fan_Schedule.Stat=1;	
	if((Obj_Fan_Schedule.pict_num!=tmp)||(Obj_Fan_Schedule.Stat!=tmp2))show_single_bmp(&Obj_Fan_Schedule,0);
	//-----------------------------------------------	
	if(Common_ID_Mode==0)
		Update_Season();
	//-----------------------------------------------		
	tmp=_SetMode.pict_num;
	if(Button_no_update_time==0)
	switch(pid[0].mode)
	{
		case PID_MODE_STOP:_SetMode.pict_num=10;break;
		case PID_MODE_AUTO:_SetMode.pict_num=9;break;
		case PID_MODE_ERROR:_SetMode.pict_num=12;break;
		case PID_MODE_WARNING:_SetMode.pict_num=11;break;	
	}		
	if(tmp!=_SetMode.pict_num)show_single_bmp(&_SetMode,0);

	//-----------------------------------------------	
#ifdef __ID_BUTTON		
	temp=Current_ID;	
	LCDMenuPtr_Tmp_Txt=&Txt[5+7+7];		
	tmp0=temp/10;
	temp-=tmp0*10;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);


	LCDMenuPtr_Tmp_Txt=&Txt[6+7+7];		
	tmp0=temp;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
#endif	
	//-----------------------------------------------	
	{
		// Real temperature
		temperature=io.ainput[1];	// Real output temperature
		if(temperature>500)temperature=999;
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
	// Preset temperature
	temperature=pid[0].t0;	// Real output temperature
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
	// Fan speed
	if(pritochka_fan_speed<400)
	{
		pritochka_fan_speed=400;
		io.aoutput[0]=pritochka_fan_speed;
		Button_no_update_time=500;
		if(Common_ID_Mode==0)new_step=51;
	}
	
	temperature=io.aoutput[0];		
	if(temperature>=1000)temperature=999;
	temp=temperature;
	LCDMenuPtr_Tmp_Txt=&Txt[0+7+7];					
	tmp0=temp/100;
	temp-=tmp0*100;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
	LCDMenuPtr_Tmp_Txt=&Txt[1+7+7];			
	tmp0=temp/10;
	temp-=tmp0*10;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[2+7+7];	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=12;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[3+7+7];				
	tmp0=temp/1;
	temp-=tmp0*1;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[4+7+7];	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;			
	LCDMenuPtr_Tmp_Txt->Stat=14;			
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	//-----------------------------------------------	
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
//	str[16]=0;
	lcd_sprintf(str,14,2);
/*	
	// Network errors
	// Status bar 14.14:29.15
	strcpy(str,"              ");	
	lcd_sprintf(str,14,14);	
	lcd_sprintf(str,14,15);		
	// Line 0 ------------------------
	strcpy(str,"ID:");
	ByteToStrFillZero(str2,&Current_ID,0,2,'0');
	stradd(str,str2);
	if(Current_ID!=0){
		stradd(str," L");
		ByteToStr(str2,&M_history.lost[M.channel],0);
		stradd(str,str2);	
		stradd(str,"% ");
	}
	else{
		stradd(str," ALL");
	}
//	stradd(str,"R");
//	WordeToStr(str2,&M_history.reset[M.channel],0);
//	stradd(str,str2);	
//	lcd_sprintf(str2,20,15);		
	lcd_sprintf(str,14,14);	
	// Line 1 ------------------------	
	lcd_sprintf("Status: OK",14,15);	
*/
	}	
}
//-----------------------------------------------------------------------------------
void Schedule_N0()
{
//	u16 i,tmp;
	u8 len;
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
						pid[0].mode=work_info->mode;	
						pid[0].t0=work_info->temperature[0];	
						Temperature[0]=work_info->temperature[1];							
						Temperature[1]=work_info->temperature[2];								
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
			}
		}
		// TX section
		if(M_SCH_Time==0)
		{			
			if(new_step!=0){
				step=new_step;
				new_step=0;
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
					M_Get_Controller_Work(Current_ID);
					M_SCH_Time=100;
				break;				
				case 1:
					step++;
					M_Get_Controller_Time(Current_ID,Current_ID);
					M_SCH_Time=100;
				break;				
				case 2:
					step++;
					M_Get_Controller_Register(Current_ID,&io,sizeof(TIO));	
					M_SCH_Time=100;					
				break;
				case 3:
					step++;
					M_Get_Controller_Register(Current_ID,&pid[0],sizeof(TPID));						
					M_SCH_Time=100;					
				break;			
				case 4:
					M_Get_Controller_Register(Current_ID,&MenuRegs,sizeof(TMenuRegisters));
					step++;					
					M_SCH_Time=50;	
				break;
				case 5:
					//M_Get_Controller_Register(Current_ID,&pid[1],sizeof(TPID));
					upc_Set_Controller_In_Params(Current_ID,0,(u8*)&pritochka_fan_speed,1);
					step++;					
					M_SCH_Time=50;	
				break;
				case 6:
					// Direction PID[0]
					M_Set_Controller_Register(1,&pid[0].heating_cooling,1);					
					step++;					
					M_SCH_Time=50;	
				break;
				case 7:
					// Direction PID[1]
					M_Set_Controller_Register(1,&pid[1].heating_cooling,1);					
					step++;					
					M_SCH_Time=50;	
				break;								



				
				case 50:
					M_Set_Controller_Register(Current_ID,&pid[0].t0,2);				
					step=0;					
					M_SCH_Time=50;	
				break;
				case 51:
//					io.aoutput[0]=pritochka_fan_speed;
//					M_Set_Controller_Register(Current_ID,&io.aoutput[0],2);			
					 upc_Set_Controller_In_Params(Current_ID,0,(u8*)&pritochka_fan_speed,1);
					step=0;					
					M_SCH_Time=50;	
				break;
				case 52:
					M_Set_Controller_Register(Current_ID,&pid[0].mode,1);				
					step=0;					
					M_SCH_Time=50;	
				break;


				// Update work record at controller 1
				case 100:
					if(Start_Up_Time!=0){step=0;break;}
					// FAN
					M_Set_Controller_Register(1,&fan[0],sizeof(fan[0]));					
					step++;					
					M_SCH_Time=10;	
				break;
				case 101:
					// Season
					M_Set_Controller_Register(1,&MenuRegs.Season.season,1);					
					step++;					
					M_SCH_Time=10;	
				break;		
				case 102:
					// Temperature PID[0]
					M_Set_Controller_Register(1,&pid[0].t0,2);					
					step++;					
					M_SCH_Time=10;	
				break;
				case 103:
					// Temperature PID[1]
//					M_Set_Controller_Register(1,&pid[1].t0,2);					
					step++;					
					M_SCH_Time=10;	
				break;
				case 104:
					// Direction PID[0]
					M_Set_Controller_Register(1,&pid[0].heating_cooling,1);					
					step++;					
					M_SCH_Time=10;	
				break;
				case 105:
					// Direction PID[1]
					M_Set_Controller_Register(1,&pid[1].heating_cooling,1);					
					step++;					
					M_SCH_Time=10;	
				break;								
				case 106:
					// Direction PID[0]
					M_Set_Controller_Register(1,&pid[0].mode,1);					
					step++;					
					M_SCH_Time=10;	
				break;
				case 107:
					// Direction PID[1]
					M_Set_Controller_Register(1,&pid[1].mode,1);					
					step++;					
					M_SCH_Time=10;	
				break;								
				case 108:
					//M_Get_Controller_Register(Current_ID,&pid[1],sizeof(TPID));
					upc_Set_Controller_In_Params(Current_ID,0,(u8*)&pritochka_fan_speed,1);
					step=110;					
					M_SCH_Time=50;	
				break;

				default:
					step=0;					
				break;
				
			}
		}
		
	}
	
}
//-----------------------------------------------------------------------------------

