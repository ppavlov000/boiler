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
void scr0_init();
void scr0_close();
void scr0_routine();
extern u8 str[40];
extern u8 Common_ID_Mode;
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
s16 Preset=220;
u16 Fan_Speed=500;
u8 Controller_Mode=PID_MODE_AUTO;
//u8 Season=0;
extern TSeason Season;
//u8 Season_Mode=1;		// 0 - auto 1 - manual
u8 Day_Night=0;	
u8 Day_Night_Mode=0;	// 0 - auto 1 - manual
// Temporary variables
s16 New_Preset=0;
u16 New_Fan_Speed=0;
u8 New_Controller_Mode=PID_MODE_STOP;
extern u8 step;
extern u8 new_step;
u8 str[40];
u8 str2[20];
extern u8 Current_ID;
extern u8 Branch_Number;
extern  u16 Store_Time;
s16 T_Room;
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
	if(m.sch_day_night==0)Preset=m.sch_temperature[0];
	if(m.sch_day_night==1)Preset=m.sch_temperature[1];
	Button_no_update_time=500;
	FT_Time=0;	
	Store_Time=5000;	
	if(Common_ID_Mode==0)new_step=20;
}
//-----------------------------------------------------------------------------------
void scr0_Season()
{
	if(Season.season==0)Season.season=1;
	else Season.season=0;
	Season.mode=1; // Manual
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
	if(Season.season==0){
		_Season_butt.Stat=1;
		if(Season.mode==0)_Season_butt.pict_num=16;
		else _Season_butt.pict_num=17;
	}
	else{
		_Season_butt.Stat=0;
		if(Season.mode==0)_Season_butt.pict_num=16;
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
	if(Controller_Mode!=PID_MODE_STOP){
		Controller_Mode=PID_MODE_STOP;
	}
	else{
		Controller_Mode=PID_MODE_AUTO;
	}
	switch(Controller_Mode)
	{
		case PID_MODE_STOP:_SetMode.pict_num=10;break;
		case PID_MODE_AUTO:_SetMode.pict_num=9;break;
		case PID_MODE_ERROR:_SetMode.pict_num=12;break;
		case PID_MODE_WARNING:_SetMode.pict_num=11;break;	
	}		
	New_Controller_Mode=Controller_Mode;
	Button_no_update_time=500;
	show_single_bmp(&_SetMode,0);
	if(Common_ID_Mode==0)new_step=20;
}
//-----------------------------------------------------------------------------------
void Preset_Plus()
{
	Preset=Preset+1;
	if(Preset>=400)	Preset=400;	
	New_Preset=Preset;
	Button_no_update_time=500;
	if(Common_ID_Mode==0)new_step=20;
	FT_Time=0;
	
}
void Preset_Minus()
{
	Preset=Preset-1;
	if(Preset<=140)	Preset=140;	
	New_Preset=Preset;
	Button_no_update_time=500;
	if(Common_ID_Mode==0)new_step=20;
	FT_Time=0;
}
void Fan_Plus()
{
	Fan_Speed=Fan_Speed+10;
	if(Fan_Speed>=999)Fan_Speed=999;	
	if(Fan_Speed<400)Fan_Speed=400;
	New_Fan_Speed=Fan_Speed;
	Button_no_update_time=500;
	if(Common_ID_Mode==0)new_step=20;
	FT_Time=0;
}
void Fan_Minus()
{
	if(Fan_Speed>=400)Fan_Speed=Fan_Speed-10;
	else Fan_Speed=400;
	New_Fan_Speed=Fan_Speed;
	Button_no_update_time=500;
	if(Common_ID_Mode==0)new_step=20;
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
__farflash TLCDPict _Temperature_Mode=
{	
	0,16,9,
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
	7,101,17,
//	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,
	0,	
	scr0_Season,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Fan_Schedule=
{
	0,101,18,
//	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,
	0,	
	scr0_Auto_Manual,
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
	scr0_Update,
	NULL,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
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
	16,
	5+7+7,	
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

	if(Current_ID==0)
		_Update_butt.Flag=(bit_visible+bit_active);
	else
		_Update_butt.Flag=0;
	_Update_butt.Stat=0;
	
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
	Switch_To_Main_Time=60;
	custom_handle();
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
	switch(Controller_Mode)
	{
		case PID_MODE_STOP:_SetMode.pict_num=10;break;
		case PID_MODE_AUTO:_SetMode.pict_num=9;break;
		case PID_MODE_ERROR:_SetMode.pict_num=12;break;
		case PID_MODE_WARNING:_SetMode.pict_num=11;break;	
	}		
	if(tmp!=_SetMode.pict_num)show_single_bmp(&_SetMode,0);
	//-----------------------------------------------	
	if(Common_ID_Mode==0){
		// Real temperature
		temperature=Temperature[2];	// Real output temperature
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
	temperature=Preset;	// Real output temperature
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
	temperature=Fan_Speed;		
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
	if(Common_ID_Mode==0){
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
}
//-----------------------------------------------------------------------------------
void Schedule_N0()
{
//	u16 i,tmp;
	M_state_machine();
	if((M.status==st_none)||(M.status==st_complete))
	{		
		if((M.error==0)&&(M.rxnew==1))
		{
			M.rxnew=0;
			switch(M_rx.field.com.bit.com)
			{
				case com_get_time:		
//					Season=rx.field.data.st.Season;
					ft=*(TTime*)&M_rx.field.d[0];	
				break;
				case com_get_stat:		
//					Season=rx.field.data.st.Season;
					Status=(TExSTATUS*)&M_rx.field.d[30];	
					ft=Status->ft;
					if(Button_no_update_time==0){
						Season.season=Status->Season;
						Controller_Mode=Status->Controller_Mode;
						Fan_Speed=Status->Preset_Speed;
						Preset=Status->Preset_Temperature;	
						Temperature[2]=Status->Temperature;
						T_Room=Status->T_Room;
					}
				break;
				case com_get_errors:		
					errors=*(TErrors*)&M_rx.field.d[0];	
				break;									
				case com_get_io:		
					Temperature[0]=ExData->io.analog[ExData->io.num_ao+0];
					Temperature[1]=ExData->io.analog[ExData->io.num_ao+1];
					Temperature[2]=ExData->io.analog[ExData->io.num_ao+2];
					Fan_Speed=ExData->io.analog[0];
				break;
				case com_get_out_params:		
	//				Time_Wint=rx.field.data.Time;								
				break;				
				case com_get_season:				
					memcpy(&Season,&M_rx.field.d[0],sizeof(TSeason));	
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
			switch(step)
			{
				case 0:
					step++;
					M_Get_Controller_Status(Current_ID,Current_ID);
					//upc_Get_Controller_Time(1,1);
					M_SCH_Time=200;
				break;				
				case 1:
					step++;
//					M_Get_Controller_IO(Current_ID,Current_ID);
					M_SCH_Time=10;					
				break;
				case 2:
					step++;
//					M_Get_Controller_Errors(Current_ID,Current_ID);
//					upc_Get_Controller_Out_Params(1,1);
//					M_Set_Controller_Status(1,1);
					step=0;					
					M_SCH_Time=10;					
				break;
				// Update status information
				case 20:
					step++;
//					M_Get_Controller_Status(Current_ID,Current_ID);
					//upc_Get_Controller_Time(1,1);
					M_SCH_Time=10;
				break;								
				case 21:
					step++;
//					upc_Get_Controller_Out_Params(1,1);
					M_Set_Controller_Status(Current_ID,Current_ID);					
					step=0;					
					M_SCH_Time=10;	
				break;
				case 22:
					step++;
					memset(&errors,0,sizeof(TErrors));
//					M_Set_Controller_Errors(Current_ID,Current_ID);					
					step=0;					
					M_SCH_Time=10;	
				break;

				case 30:
					 M_Get_Season(Current_ID);
					step=0;					
					M_SCH_Time=10;	
				break;
				case 31:
					 M_Set_Season(Current_ID,&Season);
					step=0;					
					M_SCH_Time=10;	
				break;

				case 40:
					step++;
					M_Set_Controller_Status(0,0);					
					M_SCH_Time=50;	
				break;
				case 41:
					step++;
					M_Set_Controller_Status(0,0);					
					M_SCH_Time=50;	
				break;
				case 42:
					M_Set_Controller_Status(0,0);					
					step++;					
					M_SCH_Time=50;	
				break;
				case 43:
					M_Set_Controller_Status(0,0);					
					step++;					
					M_SCH_Time=50;	
				break;
				case 44:
					M_Set_Controller_Status(0,0);					
					step=0;					
					M_SCH_Time=50;	
				break;
				
			}
		}
		
	}
	
}
//-----------------------------------------------------------------------------------

