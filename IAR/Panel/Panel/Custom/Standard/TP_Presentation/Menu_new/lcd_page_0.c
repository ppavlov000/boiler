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
#define COM_Y_OFFSET		8
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
extern s16 T_Sensor;
//-----------------------------------------------------------------------------------
#define _SetMode 		Obj[5]
#define _Season_butt 	Obj[11]
#define _Day_butt 		Obj[12]
#define _Update_butt	Obj[15]
//-----------------------------------------------------------------------------------
// System variables
s16 Temperature[3]={0};
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
s16 T_Room=0;
u32 	dout=0;
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
void MainSetID_0()
{	
	if(Obj[0].Stat!=1){Obj[0].Stat=1;show_single_bmp(&Obj[0],0);};
	if(Obj[1].Stat!=0){Obj[1].Stat=0;show_single_bmp(&Obj[1],0);};
	if(Obj[2].Stat!=0){Obj[2].Stat=0;show_single_bmp(&Obj[2],0);};
	FT_Time=0;	

}
//-----------------------------------------------------------------------------------
void MainSetID_1()
{	
	if(Obj[0].Stat!=0){Obj[0].Stat=0;show_single_bmp(&Obj[0],0);};
	if(Obj[1].Stat!=1){Obj[1].Stat=1;show_single_bmp(&Obj[1],0);};
	if(Obj[2].Stat!=0){Obj[2].Stat=0;show_single_bmp(&Obj[2],0);};
	FT_Time=0;	
}
//-----------------------------------------------------------------------------------
void MainSetID_2()
{	
	if(Obj[0].Stat!=0){Obj[0].Stat=0;show_single_bmp(&Obj[0],0);};
	if(Obj[1].Stat!=0){Obj[1].Stat=0;show_single_bmp(&Obj[1],0);};
	if(Obj[2].Stat!=1){Obj[2].Stat=1;show_single_bmp(&Obj[2],0);};
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
	if(pid[0].t0<=-500)	pid[0].t0=-500;	
	Button_no_update_time=500;
	if(Common_ID_Mode==0)new_step=50;
	FT_Time=0;
}
//-----------------------------------------------------------------------------------
void Get_D0()
{
	u8 i;
	u32 t;
	u8 old;
	if(Button_no_update_time==0)
	{
		t=0x00000001;
		for(i=0;i<7;i++)
		{
			old=Obj[14+i].Stat;
			Obj[14+i].Stat=0;
			if(io.dout & t)Obj[14+i].Stat=1;
			t=t<<1;
			if(old!=Obj[14+i].Stat)show_single_bmp(&Obj[14+i],0);
		}
	}
}
//-----------------------------------------------------------------------------------
void Get_DI()
{
	u8 i;
	u32 t;
	u8 old;
	if(Button_no_update_time==0)
	{
		t=1;
		for(i=0;i<7;i++)
		{
			old=Obj[7+i].Stat;
			Obj[7+i].Stat=0;
			if(io.din & t)Obj[7+i].Stat=1;
			t=t<<1;
			if(old!=Obj[14+i].Stat)show_single_bmp(&Obj[7+i],0);
		}
	}
}
//-----------------------------------------------------------------------------------
void Set_D0(u32 t,u8 stat)
{	
	if(stat)
		io.dout|=t;
	else
		io.dout&=~t;
	Button_no_update_time=500;
	if(Common_ID_Mode==0)new_step=53;
}
//-----------------------------------------------------------------------------------
void Set_D0_00()
{	
	Set_D0(0x00000001,Obj[14+0].Stat);
}
void Set_D0_01()
{	
	Set_D0(0x00000002,Obj[14+1].Stat);
}
void Set_D0_02()
{	
	Set_D0(0x00000004,Obj[14+2].Stat);
}
void Set_D0_03()
{	
	Set_D0(0x00000008,Obj[14+3].Stat);
}
void Set_D0_04()
{	
	Set_D0(0x00000010,Obj[14+4].Stat);
}
void Set_D0_05()
{	
	Set_D0(0x00000020,Obj[14+5].Stat);
}
void Set_D0_06()
{	
	Set_D0(0x00000040,Obj[14+6].Stat);
}
void Set_D0_07()
{	
	Set_D0(0x00000080,Obj[14+7].Stat);
}

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
__farflash TLCDPict Tab_Menu2=
{	//
	14+4,0,7,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,	
	0,	
	MainSetID_2,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict Tab_Menu1=
{	//
	6+4,0,6,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,	
	0,	
	MainSetID_1,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict Tab_Menu0=
{	//
	0+4,0,5,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,	
	0,	
	MainSetID_0,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Mode_0=
{	
	1+4*0,0,5,
	(bit_visible),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Mode_1=
{	
	1+4*1,0,6,
	(bit_visible),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Mode_2=
{	
	1+4*2,0,7,
	(bit_visible),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Mode_3=
{	
	1+4*3,0,8,
	(bit_visible),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Mode_4=
{	
	1+4*4,0,9,
	(bit_visible),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Mode_5=
{	
	1+4*5,0,10,
	(bit_visible),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Mode_6=
{	
	1+4*6,0,11,
	(bit_visible),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Mode_7=
{	
	1+4*7,0,12,
	(bit_visible),
	0,
	0,
	0,	
	NULL,
	NULL,
};

//--------------------------------------------
__farflash TLCDPict _Device_0=
{	
	1+4*0,104,5,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	Set_D0_00,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Device_1=
{	
	1+4*1,104,6,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	Set_D0_01,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Device_2=
{	
	1+4*2,104,7,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	Set_D0_02,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Device_3=
{	
	1+4*3,104,8,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	Set_D0_03,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Device_4=
{	
	1+4*4,104,9,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	Set_D0_04,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Device_5=
{	
	1+4*5,104,10,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	Set_D0_05,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Device_6=
{	
	1+4*6,104,11,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	Set_D0_06,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Device_7=
{	
	1+4*7,104,12,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	Set_D0_07,
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
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
__farflash TLCDPict_Txt _ID_txt_1=
{
	9,38-REAL_T_OFF,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _ID_txt_0=
{
	7,38-REAL_T_OFF,53,
	(bit_visible+bit_txt_1),
	0,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_5=
{
	21,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	15,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_4=
{
	19,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_3=
{
	17,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_2=
{
	15,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_1=
{
	13,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_0=
{
	11,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_Sign=
{
	9,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_5=
{
	23-PRESET_X_OFFSET,58+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	15,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_4=
{
	21-PRESET_X_OFFSET,58+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_3=
{
	19-PRESET_X_OFFSET,58+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_2=
{
	17-PRESET_X_OFFSET,58+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_1=
{
	15-PRESET_X_OFFSET,58+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_0=
{
	13-PRESET_X_OFFSET,58+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_Sign=
{
	11-PRESET_X_OFFSET,58+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
__farflash TLCDPict_Txt _T1_txt_5=
{
	12+17,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	15,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T1_txt_4=
{
	10+17,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T1_txt_3=
{
	8+17,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T1_txt_2=
{
	6+17,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T1_txt_1=
{
	4+17,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T1_txt_0=
{
	2+17,33-REAL_T_OFF+COM_Y_OFFSET,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _T1_txt_Sign=
{
	0+17,33-REAL_T_OFF+COM_Y_OFFSET,53,
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
	21,
	0+7+7+7,	
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
	Obj[3]=_Menu3;		
	Obj[4]=_Menu4;	
	
	Obj[0].Flag=0;	
	Obj[1].Flag=0;	
	Obj[2].Flag=0;	
	Obj[3].Flag=0;	
	Obj[4].Flag=0;	
	
	Obj[5]=_Preset_Plus;		
	Obj[6]=_Preset_Minus;

	Obj[7]=_Mode_0;		
	Obj[8]=_Mode_1;		
	Obj[9]=_Mode_2;		
	Obj[10]=_Mode_3;		
	Obj[11]=_Mode_4;		
	Obj[12]=_Mode_5;		
	Obj[13]=_Mode_6;		

	Obj[14]=_Device_0;		
	Obj[15]=_Device_1;		
	Obj[16]=_Device_2;		
	Obj[17]=_Device_3;		
	Obj[18]=_Device_4;
	Obj[19]=_Device_5;
	Obj[20]=_Device_6;	
//	Obj[21]=_Device_7;
	
	Obj[0].Stat=1;
	
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

	Txt[0+7+7]=_T1_txt_Sign;	
	Txt[1+7+7]=_T1_txt_0;	
	Txt[2+7+7]=_T1_txt_1;	
	Txt[3+7+7]=_T1_txt_2;	
	Txt[4+7+7]=_T1_txt_3;	
	Txt[5+7+7]=_T1_txt_4;	
	Txt[6+7+7]=_T1_txt_5;	
	
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
	Obj[0]=_Menu0;	
	Obj[1]=_Menu1;	
	Obj[2]=_Menu2;	
	Obj[3]=_Menu3;		
	Obj[4]=_Menu4;	
	
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
	FT_Time=100;
	if(page_offset!=PAGE_0_OFFSET)return;
	 Get_D0();
	 Get_DI();

	
#ifdef __SWITCH_TO_ID_1
	if(Switch_To_ID_1==0)
	{
		Current_ID=0;
		MainSetID();
	}
#endif				
	Switch_To_Main_Time=60;
	pid[0].heating_cooling=PID_HEATING;	
	pid[1].heating_cooling=PID_COOLING;			
	//-----------------------------------------------		
	{
		temperature=io.ainput[0];	// Real output temperature
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
/*
	{
		temperature=io.ainput[1];	// Real output temperature
		if(temperature>999)temperature=999;
		LCDMenuPtr_Tmp_Txt=&Txt[0+7+7];
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
		
		LCDMenuPtr_Tmp_Txt=&Txt[1+7+7];			
		tmp0=temp/100;
		temp-=tmp0*100;	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[3+7+7];	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=12;
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
					
		LCDMenuPtr_Tmp_Txt=&Txt[2+7+7];				
		tmp0=temp/10;
		temp-=tmp0*10;	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[4+7+7];
		tmp0=temp;
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[5+7+7];	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;			
		LCDMenuPtr_Tmp_Txt->Stat=15;			
		if(Common_ID_Mode!=0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	}
*/	
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
					M_Get_Controller_Register(Current_ID,&io,sizeof(TIO));						
//					M_Get_Controller_Work(Current_ID);
					M_SCH_Time=10;
				break;				
				case 1:
					step++;
					M_Get_Controller_Time(Current_ID,Current_ID);
					M_SCH_Time=10;
				break;				
				case 2:
					step=0;
					M_Get_Controller_Register(Current_ID,&pid[0].t0,2);																
//					M_Get_Controller_Register(Current_ID,&io,sizeof(TIO));	
					M_SCH_Time=10;					
				break;
				case 3:
					step++;
//					M_Get_Controller_Register(Current_ID,&pid[0],sizeof(TPID));						
					M_SCH_Time=10;					
				break;			
				case 4:
					M_Get_Controller_Register(Current_ID,&MenuRegs,sizeof(TMenuRegisters));
					step++;					
					M_SCH_Time=10;	
				break;
				case 5:
					//M_Get_Controller_Register(Current_ID,&pid[1],sizeof(TPID));
					upc_Set_Controller_In_Params(Current_ID,0,(u8*)&pritochka_fan_speed,1);
					step++;					
					M_SCH_Time=10;	
				break;



				
				case 50:
					M_Set_Controller_Register(Current_ID,&pid[0].t0,2);				
					step=0;					
					M_SCH_Time=50;	
					Time_To_Save=3000;
				break;
				case 51:
//					io.aoutput[0]=pritochka_fan_speed;
//					M_Set_Controller_Register(Current_ID,&io.aoutput[0],2);			
					 upc_Set_Controller_In_Params(Current_ID,0,(u8*)&pritochka_fan_speed,1);
					step=0;					
					M_SCH_Time=50;
					Time_To_Save=3000;
				break;
				case 52:
					M_Set_Controller_Register(Current_ID,&pid[0].mode,1);				
					step=0;					
					M_SCH_Time=50;	
					Time_To_Save=3000;
				break;
				case 53:
					M_Set_Controller_Register(Current_ID,&io.dout,4);				
					step=0;					
					M_SCH_Time=50;	
				break;

/*
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
				case 102:
					// Temperature PID[0]
					M_Set_Controller_Register(Current_ID,&pid[0].t0,2);					
					step++;					
					M_SCH_Time=10;	
				break;
				case 103:
					// Temperature PID[1]
					M_Set_Controller_Register(Current_ID,&pid[1].t0,2);					
					step++;					
					M_SCH_Time=10;	
				break;
				case 104:
					// Direction PID[0]
					M_Set_Controller_Register(Current_ID,&pid[0].heating_cooling,1);					
					step++;					
					M_SCH_Time=10;	
				break;
				case 105:
					// Direction PID[1]
					M_Set_Controller_Register(Current_ID,&pid[1].heating_cooling,1);					
					step++;					
					M_SCH_Time=10;	
				break;								
				case 106:
					// Direction PID[0]
					M_Set_Controller_Register(Current_ID,&pid[0].mode,1);					
					step++;					
					M_SCH_Time=10;	
				break;
				case 107:
					// Direction PID[1]
					M_Set_Controller_Register(Current_ID,&pid[1].mode,1);					
					step++;					
					M_SCH_Time=10;	
				break;								
*/
				// Update work record at controller 1
				case 100:
					if(Start_Up_Time!=0){step=0;break;}
					// FAN
					M_Set_Controller_Register(1,&fan[0],sizeof(fan[0]));					
					step++;					
					M_SCH_Time=10;	
					Time_To_Save=3000;
				break;
				case 101:
					// Season
					M_Set_Controller_Register(1,&MenuRegs.Season.season,1);					
					step++;					
					M_SCH_Time=10;	
					Time_To_Save=3000;
				break;		
				case 102:
					// Temperature PID[0]
					M_Set_Controller_Register(1,&pid[0].t0,2);					
					step++;					
					M_SCH_Time=10;	
					Time_To_Save=3000;
				break;
				case 103:
					// Temperature PID[1]
					M_Set_Controller_Register(1,&pid[1].t0,2);					
					step++;					
					M_SCH_Time=10;	
					Time_To_Save=3000;
				break;
				case 104:
					// Direction PID[0]
					M_Set_Controller_Register(1,&pid[0].heating_cooling,1);					
					step++;					
					M_SCH_Time=10;	
					Time_To_Save=3000;
				break;
				case 105:
					// Direction PID[1]
					M_Set_Controller_Register(1,&pid[1].heating_cooling,1);					
					step++;					
					M_SCH_Time=10;	
					Time_To_Save=3000;
				break;								
				case 106:
					// Direction PID[0]
					M_Set_Controller_Register(1,&pid[0].mode,1);					
					step++;					
					M_SCH_Time=10;	
					Time_To_Save=3000;
				break;
				case 107:
					// Direction PID[1]
					M_Set_Controller_Register(1,&pid[1].mode,1);					
					step++;					
					M_SCH_Time=10;
					Time_To_Save=3000;
				break;								
				case 108:
					//M_Get_Controller_Register(Current_ID,&pid[1],sizeof(TPID));
					upc_Set_Controller_In_Params(Current_ID,0,(u8*)&pritochka_fan_speed,1);
					step=110;					
					M_SCH_Time=50;	
					Time_To_Save=3000;
				break;
				
//******************************************************************************
#ifdef __LEDNOE
//******************************************************************************
				// Update work record at controller 2
				case 110:
					// FAN
					M_Set_Controller_Register(2,&fan[0],sizeof(fan[0]));					
					step++;					
					M_SCH_Time=10;	
					Time_To_Save=3000;
				break;
				case 111:
					// Season
					M_Set_Controller_Register(2,&MenuRegs.Season.season,1);					
					step++;					
					M_SCH_Time=10;	
					Time_To_Save=3000;
				break;		
				case 112:
					// Temperature PID[0]
					M_Set_Controller_Register(2,&pid[0].t0,2);					
					step++;					
					M_SCH_Time=10;
					Time_To_Save=3000;
				break;
				case 113:
					// Temperature PID[1]
					M_Set_Controller_Register(2,&pid[1].t0,2);					
					step++;					
					M_SCH_Time=10;	
					Time_To_Save=3000;
				break;
				case 114:
					// Direction PID[0]
					M_Set_Controller_Register(2,&pid[0].heating_cooling,1);					
					step++;					
					M_SCH_Time=10;
					Time_To_Save=3000;
				break;
				case 115:
					// Direction PID[1]
					M_Set_Controller_Register(2,&pid[1].heating_cooling,1);					
					step++;					
					M_SCH_Time=10;
					Time_To_Save=3000;
				break;								
				case 116:
					// Direction PID[0]
					M_Set_Controller_Register(2,&pid[0].mode,1);					
					step++;					
					M_SCH_Time=10;	
					Time_To_Save=3000;
				break;
				case 117:
					// Direction PID[1]
					M_Set_Controller_Register(2,&pid[1].mode,1);					
					step=120;					
					M_SCH_Time=10;
					Time_To_Save=3000;
				break;								

				// Update work record at controller 3
				case 120:
					// FAN
					M_Set_Controller_Register(3,&fan[0],sizeof(fan[0]));					
					step++;					
					M_SCH_Time=10;
					Time_To_Save=3000;
				break;
				case 121:
					// Season
					M_Set_Controller_Register(3,&MenuRegs.Season.season,1);					
					step++;					
					M_SCH_Time=10;
					Time_To_Save=3000;
				break;		
				case 122:
					// Temperature PID[0]
					M_Set_Controller_Register(3,&pid[0].t0,2);					
					step++;					
					M_SCH_Time=10;	
					Time_To_Save=3000;
				break;
				case 123:
					// Temperature PID[1]
					M_Set_Controller_Register(3,&pid[1].t0,2);					
					step++;					
					M_SCH_Time=10;
					Time_To_Save=3000;
				break;
				case 124:
					// Direction PID[0]
					M_Set_Controller_Register(3,&pid[0].heating_cooling,1);					
					step++;					
					M_SCH_Time=10;	
					Time_To_Save=3000;
				break;
				case 125:
					// Direction PID[1]
					M_Set_Controller_Register(3,&pid[1].heating_cooling,1);					
					step++;					
					M_SCH_Time=10;
					Time_To_Save=3000;
				break;								
				case 126:
					// Direction PID[0]
					M_Set_Controller_Register(3,&pid[0].mode,1);					
					step++;					
					M_SCH_Time=10;	
					Time_To_Save=3000;
				break;
				case 127:
					// Direction PID[1]
					M_Set_Controller_Register(3,&pid[1].mode,1);					
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
//******************************************************************************				
#endif				
//******************************************************************************
				default:
					step=0;					
				break;
				
			}
		}
		
	}
	
}
//-----------------------------------------------------------------------------------

