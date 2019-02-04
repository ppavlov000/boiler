//-----------------------------------------------------------------------------------
#include "..\Main.h"
//-----------------------------------------------------------------------------------
#include "..\Menu_New\lcd_template.h"
#include "..\Menu_New\lcd_calibrate.h"
#include "..\Menu_New\lcd_alarm.h"
#include "..\Menu_New\lcd_alarm_snooze.h"
#include "..\Menu_New\lcd_ac_menu.h"
#include "..\Menu_New\lcd_tech_menu.h"
#include "..\Menu_New\lcd_set_time.h"
#include "..\Menu_New\lcd_tech_contrast.h"
#include "..\Menu_New\lcd_tech_temperature.h"
//-----------------------------------------------------------------------------------
extern TLCDPictTop Scr_0;
//-----------------------------------------------------------------------------------
void scr3_init();
void scr3_routine();
void scr3_close();
void handle_fan_buttons_0();
void handle_fan_buttons_1();
void handle_fan_buttons_2();
void handle_fan_buttons_3();
void handle_fan_buttons_4();
void Mod_Temperature_Up();
void Mod_Temperature_Down();
//-----------------------------------------------------------------------------------
//--------------------------------------------
__farflash TLCDPict _T_Button_9=
{
	// Exit
	27,0,21,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,	
	0,	
	NULL,
	&Scr_0,		
};
//--------------------------------------------
__farflash TLCDPict _T_Button_8=
{
	// temperature bar
	6,45,39,
	(bit_visible+bit_full),
	0,
	0,	
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _T_Button_7=
{
	// heating/cooling
	0,0,23,
	(bit_visible),
	0,
	0,	
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _T_Button_6=
{
	// Minus
	1,44,26,
	(bit_visible+bit_active),
	0,
	0,
	0,		
//	Mod_BackLit_Down,
	Mod_Temperature_Down,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _T_Button_5=
{
	// Plus
	25,44,28,
	(bit_visible+bit_active),
	0,
	0,
	0,		
	Mod_Temperature_Up,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _T_Button_4=
{
	// High
	24,87,22,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,		
	handle_fan_buttons_4,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _T_Button_3=
{
	// Med
	18,87,25,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,		
	handle_fan_buttons_3,
	NULL,
};

//--------------------------------------------
__farflash TLCDPict _T_Button_2=
{
	// Low
	12,87,24,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,		
	handle_fan_buttons_2,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _T_Button_1=
{
	// Off
	6,87,27,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,		
	handle_fan_buttons_1,
	NULL,
};
//--------------------------------------------
// Auto
__farflash TLCDPict _T_Button_0=
{
	0,87,19,

	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,		
	handle_fan_buttons_0,
	NULL,
};
//-----------------------------------------------------------------------------------
// Wall tp fan coil menu
__farflash TLCDPict _Page1=
{
	0,0,0,
	0,
	0,
	0,
	0,		
	NULL,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Bar_0=
{
	7,53,40,
	(bit_visible+bit_txt_1+bit_txt_2),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_3=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	11,
	0,	
	scr3_init,
	scr3_routine,
	scr3_close,		
};
//-----------------------------------------------------------------------------------
void scr3_init()
{
	 u8 i;
//	memset(Obj,0,16*sizeof(TLCDPict));
//	memset(Txt,0,20*sizeof(TLCDPict_Txt));	
//	_sprintf(outtxt,"\n\r Init");
	Obj[0]=_T_Button_0;
	Obj[1]=_T_Button_1;	
	Obj[2]=_T_Button_2;
	Obj[3]=_T_Button_3;
	Obj[4]=_T_Button_4;
	Obj[5]=_T_Button_5;
	Obj[6]=_T_Button_6;
	Obj[7]=_T_Button_7;
	Obj[8]=_T_Button_8;
	Obj[9]=_T_Button_9;
	Obj[10]=_Bar_0;	
	FT_Time=200;
	for(i=0;i<16;i++)
		bar_stat[i]=0;
	int_state|=but_Int0s;	
//	update_fan_buttons();
//	FT_Time=100;
}
//-----------------------------------------------------------------------------------
void scr3_close()
{
//	u8 i;
//	LCDTopPtr=&Scr_3;
	clear_page();
	params_store();		
}
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//--------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void scr3_routine()
{
	u8 i, old_stat;
	//**************************************************		
//	u8 sign;
//	sign=0;
//	if(page_offset!=PAGE_0_OFFSET)return;
	for(i=0;i<16;i++)
	{
		Obj[10].x=7+i;
		old_stat=bar_stat[i];
		if(m.fan.Temperature>(i))
			Obj[10].Stat=1;
		else
			Obj[10].Stat=0;		
		bar_stat[i]=Obj[10].Stat;
		if(Obj[10].Stat!=old_stat)
			show_single_bmp(&Obj[10],0);
	}		
	
	switch(m.fan.Valve)
	{
		case 0:
			if((Obj[7].Stat!=0)||(Obj[7].pict_num!=54))
			{
				Obj[7].pict_num=54;
				Obj[7].Stat=0;
				show_single_bmp(&Obj[7],0);
			}		
		break;	
		case 1:
			if((Obj[7].Stat!=0)||(Obj[7].pict_num!=23))
			{
				Obj[7].pict_num=23;
				Obj[7].Stat=0;
				show_single_bmp(&Obj[7],0);
			}		
		break;
		case 2:
			if((Obj[7].Stat!=1)||(Obj[7].pict_num!=23))
			{
				Obj[7].pict_num=23;
				Obj[7].Stat=1;
				show_single_bmp(&Obj[7],0);
			}		
		break;	
	}	
	//**************************************************		
	switch(m.fan.Fan_Mode)
	{
		case 0:	
			if(Obj[0].Stat!=1)
			{
				Obj[0].Stat=1;
				show_single_bmp(&Obj[0],0);												
			}
		break;
		case 1:	
			if(Obj[0].Stat!=0)
			{		
				Obj[0].Stat=0;
				show_single_bmp(&Obj[0],0);
			}				
		break;
	}
	//**************************************************		
	switch(m.fan.Fan_Lvl)
	{
		case 0:	
//			Obj[1.Stat=1;
//			show_single_bmp(&Obj[1);
			if(Obj[1].Stat!=1){Obj[1].Stat=1;show_single_bmp(&Obj[1],0);}
			if(Obj[2].Stat!=0){Obj[2].Stat=0;show_single_bmp(&Obj[2],0);}
			if(Obj[3].Stat!=0){Obj[3].Stat=0;show_single_bmp(&Obj[3],0);}
			if(Obj[4].Stat!=0){Obj[4].Stat=0;show_single_bmp(&Obj[4],0);}					
		break;
		case 1:			
//			Obj[2.Stat=1;
//			show_single_bmp(&Obj[2);			
			if(Obj[1].Stat!=0){Obj[1].Stat=0;show_single_bmp(&Obj[1],0);}
			if(Obj[2].Stat!=1){Obj[2].Stat=1;show_single_bmp(&Obj[2],0);}
			if(Obj[3].Stat!=0){Obj[3].Stat=0;show_single_bmp(&Obj[3],0);}
			if(Obj[4].Stat!=0){Obj[4].Stat=0;show_single_bmp(&Obj[4],0);}				
		break;
		case 2:		
//			Obj[3.Stat=1;
//			show_single_bmp(&Obj[3);			
			if(Obj[1].Stat!=0){Obj[1].Stat=0;show_single_bmp(&Obj[1],0);}
			if(Obj[2].Stat!=0){Obj[2].Stat=0;show_single_bmp(&Obj[2],0);}
			if(Obj[3].Stat!=1){Obj[3].Stat=1;show_single_bmp(&Obj[3],0);}
			if(Obj[4].Stat!=0){Obj[4].Stat=0;show_single_bmp(&Obj[4],0);}							
		break;
		case 3:		
//			Obj[4.Stat=1;
//			show_single_bmp(&Obj[4);			
			if(Obj[1].Stat!=0){Obj[1].Stat=0;show_single_bmp(&Obj[1],0);}
			if(Obj[2].Stat!=0){Obj[2].Stat=0;show_single_bmp(&Obj[2],0);}
			if(Obj[3].Stat!=0){Obj[3].Stat=0;show_single_bmp(&Obj[3],0);}
			if(Obj[4].Stat!=1){Obj[4].Stat=1;show_single_bmp(&Obj[4],0);}							
		break;
	}	
}
//-----------------------------------------------------------------------------------
void Mod_Temperature_Up()
{
//	s16 Diff;
	Set_Int_State_0();
	m.fan.Temperature+=1;
	if(m.fan.Temperature>16)m.fan.Temperature=16;
	upc.data_status|=b_fancoil_new;
}
//-----------------------------------------------------------------------------------
void Mod_Temperature_Down()
{
//	s16 Diff;
	Set_Int_State_0();
	m.fan.Temperature-=1;
	if(m.fan.Temperature<0)m.fan.Temperature=0;	
	upc.data_status|=b_fancoil_new;
}
//-----------------------------------------------------------------------------------
void handle_fan_buttons_0()
{
//	s16	Diff;
	if(Obj[0].Stat==0)
		m.fan.Fan_Mode=1;
	else
		m.fan.Fan_Mode=0;		
	upc.data_status|=b_fancoil_new;
	scr3_routine();
}
//-----------------------------------------------------------------------------------
void handle_fan_buttons_1()
{
//	s16	Diff;
	m.fan.Fan_Lvl=0;
	m.fan.Fan_Mode=1;
	upc.data_status|=b_fancoil_new;
	scr3_routine();
}
//-----------------------------------------------------------------------------------
void handle_fan_buttons_2()
{
//	s16	Diff;
			m.fan.Fan_Lvl=1;	
			m.fan.Fan_Mode=1;	
	upc.data_status|=b_fancoil_new;
	scr3_routine();
}
//-----------------------------------------------------------------------------------
void handle_fan_buttons_3()
{
//	s16	Diff;
			m.fan.Fan_Lvl=2;
			m.fan.Fan_Mode=1;	
	upc.data_status|=b_fancoil_new;
	scr3_routine();
}
//-----------------------------------------------------------------------------------
void handle_fan_buttons_4()
{
//	s16	Diff;
	m.fan.Fan_Lvl=3;
	m.fan.Fan_Mode=1;	
	upc.data_status|=b_fancoil_new;
	scr3_routine();
}
//-----------------------------------------------------------------------------------
