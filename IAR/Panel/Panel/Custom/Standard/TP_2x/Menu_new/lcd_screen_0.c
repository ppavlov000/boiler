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
#include "dimmer.h"
//-----------------------------------------------------------------------------------
#include "..\Menu_new\lcd_screen_0.h"
//-----------------------------------------------------------------------------------
#define NO_ALARM
//-----------------------------------------------------------------------------------
#define But_Main_Switch			Obj[5]
#define But_Do_Not_Disturb		Obj[15]
#define But_Makeup_Room			Obj[15]
#define But_Curtain_Open		Obj[15]
#define But_Curtain_Close		Obj[15]
#define Alarm_bell_obj			Obj[4]
#define Thief_alarm_obj			Obj[5]
//-----------------------------------------------------------------------------------
void scr0_init();
void scr0_close();
void scr0_routine();
void update_page();
void bell_pressed();
void makeup_routine();
void donot_disturb_routine();
void onoff_pressed();

void dimmer_handle_0();
void dimmer_plus(u8 num);
void dimmer_minus(u8 num);
void dimmer_off(u8 num);

extern TLCDPictTop Scr_12;
extern TLCDPictTop Scr_10;
extern TLCDPictTop Scr_Password;
extern TLCDPictTop scr_alarm_confirm;
extern vs8 thief_alarm_timeout;

void update_page_00();
void update_page_01();
void special_buttons_handle_00(TLCDPict*	lcd_ptr);
void special_buttons_handle_01(TLCDPict*	lcd_ptr);
void check_alarm_00();
void check_alarm_01();
u8 Moon_Curtains=0;
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
void lock_pressed_handler (void)
{
	if (thief_alarm_timeout > 0)
		thief_alarm_timeout = -1;
	else if (!(own_state.bst & Button_Alarm))
	{
		thief_alarm_timeout = 60;
		Thief_alarm_obj.Flag |= bit_blinking;
	}
	/*else
	{
		LCDTopPtr->Exit();
		LCDTopPtr=&Scr_Password;
		LCDTopPtr->Init();
		repaint_page();
	}*/
}
//--------------------------------------------
__farflash TLCDPict _Button_onoff=
{	
	13,0,17,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	onoff_pressed,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Button_00=
{	
	0,88,Pict_00,
	(bit_visible+bit_active+bit_trigger),
	0,
	Button_00,
	0,
	NULL,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Button_01=
{	
	13,88,Pict_00,
	(bit_visible+bit_active+bit_trigger),
	0,
	Button_01,	
	0,	
	NULL,	
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Button_02=
{	
	25,88,Pict_00,
	(bit_visible+bit_active+bit_trigger),
	0,
	Button_02,	
	0,	
	NULL,	
	NULL,	
};
/*
//--------------------------------------------
__farflash TLCDPict _Button_03=
{	
	25,88,Pict_01,
	(bit_visible+bit_active+bit_trigger+bit_dimmer),
	0,
	Button_03,	
	0,	
	dimmer_handle_3,	
	NULL,	
};
*/
/*
//--------------------------------------------
__farflash TLCDPict _Button_bell=
{	// Bell
	20,53,14,
	(bit_visible+bit_active+bit_new_page),
	1,
	0,
	0,	
	bell_pressed,
	&Scr_1,
};*/

//--------------------------------------------
__farflash TLCDPict _Button_lock=
{	// Lock
	25,44,98,
	(bit_visible+bit_active+bit_trigger+bit_new_page),
	0,
	0,
	0,	
	NULL,//lock_pressed_handler,
	&scr_alarm_confirm
};
//--------------------------------------------
__farflash TLCDPict _Button_snow=
{	// Snow
	0,44,18,
	(bit_visible+bit_active+bit_trigger+bit_new_page),
	0,
	0,
	0,
	NULL,
	&Scr_12,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
__farflash TLCDPict_Txt _Txt_4=
{
	18,54,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Txt_3=
{
	16,54,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Txt_2=
{
	14,54,53,
	(bit_visible+bit_txt_1),
	13,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Txt_1=
{
	12,54,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Txt_0=
{
	10,54,53,
	(bit_visible+bit_txt_1),
	10,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_0=
{
	0,0,0,
	0,
	6,
	5,	
	scr0_init,
	scr0_routine,
	scr0_close,		
};
//-----------------------------------------------------------------------------------
void scr0_init()
{
	Obj[0]=_Button_00;
	Obj[1]=_Button_01;
	Obj[2]=_Button_02;
//	Obj[3]=_Button_03;
//	Obj[3]=_Button_bell;	
	Obj[3]=_Button_lock;
	Obj[4]=_Button_snow;		
	Obj[5]=_Button_onoff;
	Obj[15]=_Null;	

	Txt[0]=_Txt_0;	
	Txt[1]=_Txt_1;	
	Txt[2]=_Txt_2;	
	Txt[3]=_Txt_3;	
	Txt[4]=_Txt_4;	
	
	FT_Time=100;
	Txt[0].Stat=10;
	Txt[1].Stat=10;
	Txt[3].Stat=10;
	Txt[4].Stat=10;	
	
#ifndef NO_ALARM
	if(m.Alarm_Status)
		Alarm_bell_obj.Stat=0;
	else
		Alarm_bell_obj.Stat=1;
#endif	
}
//-----------------------------------------------------------------------------------
void scr0_close()
{
	u8 i;
	for(i=0;i<Scr_0.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
}
//-----------------------------------------------------------------------------------
void scr0_routine()
{
	u8 tmp;	
		
	if(FT_Time!=0)return;	
	if(page_offset!=PAGE_0_OFFSET)return;
/*	
	if (!thief_alarm_timeout)
	{
		thief_alarm_timeout = -1;
		own_state.bst |= Button_Alarm;
		own_state.status |= bit_new_push;
		Thief_alarm_obj.Flag &= ~(bit_blinking);
		Thief_alarm_obj.Stat = 0;
		show_single_bmp	(&Thief_alarm_obj, 0);
		LCDTopPtr->Exit();
		LCDTopPtr=&Scr_Password;
		LCDTopPtr->Init();
		repaint_page();
	}
	else if (thief_alarm_timeout == -1)
	{
		if (own_state.bst & Button_Alarm)
		{
			LCDTopPtr->Exit();
			LCDTopPtr=&Scr_Password;
			LCDTopPtr->Init();
			repaint_page();			
		}
	}
	
	if (thief_alarm_timeout != -1)
		SLEEP_Time=2;
*/	
	if(int_state & but_Int3s)
	{
		int_state&=~but_Int3s;	
		if(time_blink & 1)
			show_single_bmp_txt(&Txt[2]);
		else
			clear_single_bmp_txt(&Txt[2]);		

		LCDMenuPtr_Tmp_Txt=&Txt[0];		
		tmp=m.ft.field.Hour/10;
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}
	
		LCDMenuPtr_Tmp_Txt=&Txt[1];			
		tmp=m.ft.field.Hour-tmp*10;
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}
						
		LCDMenuPtr_Tmp_Txt=&Txt[3];			
		tmp=m.ft.field.Minute/10;
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}

		LCDMenuPtr_Tmp_Txt=&Txt[4];			
		tmp=m.ft.field.Minute-tmp*10;
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}
	}
}
//-----------------------------------------------------------------------------------
void update_page()
{
	if(LCDTopPtr==&Scr_0)
	  update_page_00();
//	if(LCDTopPtr==&Scr_01)
//	  update_page_01();
}
//-----------------------------------------------------------------------------------
void update_page_00()
{
	u8 old_stat;
	u32 tmp;
	u8 i;
	if(page_offset!=PAGE_0_OFFSET)return;
	if(LCDTopPtr!=&Scr_0)return;
	
	
	
	if(bmp_update)
	{
		for(i=0;i<Scr_0.Obj_Num;i++)	
		{
			
			old_stat=Obj[i].Stat;				
			if((Obj[i].Action & mask_simple_buttons)!=0)
			{
//				if(own_state.bst & DO_24)BUZZ_Time=100;				
				tmp=own_state.bst & Obj[i].Action;
				if(tmp==DO_24)BUZZ_Time=100;				
				if(tmp == Obj[i].Action)
					Obj[i].Stat=1;
				else
					Obj[i].Stat=0;
			
				if(old_stat!=Obj[i].Stat)
					show_single_bmp(&Obj[i],0);			
			}
		}
		// Some special buttons
		// Curtains
		old_stat=But_Curtain_Open.Stat;			
		if(own_state.bst & But_Curtain_Open.Action)
		{
			if(spec[1]==0)
			{
				But_Curtain_Open.Stat=1;
				spec[1]=2;
			}
		}
		else
		{
			if(spec[1]==2)
			{
				But_Curtain_Open.Stat=0;
				spec[1]=0;
			}
		}
		if(old_stat!=But_Curtain_Open.Stat)
			show_single_bmp(&But_Curtain_Open,0);
		//------------------------------------				
		old_stat=But_Curtain_Close.Stat;			
		if(own_state.bst & But_Curtain_Close.Action)
		{
			if(spec[0]==0)
			{
				But_Curtain_Close.Stat=1;
				spec[0]=2;
			}
		}
		else
		{
			if(spec[0]==2)
			{
				But_Curtain_Close.Stat=0;
				spec[0]=0;
			}
		}	
		if(old_stat!=But_Curtain_Close.Stat)
			show_single_bmp(&But_Curtain_Close,0);
		
		
	}
	bmp_update=0;
	update_dimmers();
	
	/*if ((m.Dimmer.State & 0x0F)== 0x0F)
	{
		if (But_Main_Switch.Stat == 0)
		{
			But_Main_Switch.Stat = 1;
			show_single_bmp(&But_Main_Switch,0);
		}
	}
	else if (But_Main_Switch.Stat == 1)
	{
		But_Main_Switch.Stat = 0;
		show_single_bmp(&But_Main_Switch,0);
	}*/

}

//-----------------------------------------------------------------------------------
void check_alarm()
{
	if(LCDTopPtr==&Scr_0)
	  check_alarm_00();
//	if(LCDTopPtr==&Scr_01)
//	  check_alarm_01();
}

//-----------------------------------------------------------------------------------
void check_alarm_00()
{
#ifdef NO_ALARM
	return;
#else
//	if(page_offset!=PAGE_0_OFFSET)return;
	if(LCDTopPtr!=&Scr_0)return;  	
	// Checking alarm
	int_time.field.Minute=FiveMins.field.Minute;
	int_time.field.Hour=FiveMins.field.Hour;					

    if(alarm_state==0)
    {
	    if(LCDTopPtr!=&Scr_1)
	    if(m.Alarm_Status)
	    {	    	
    		if(int_time.field.Hour==m.ft.field.Hour)
    		{
	    		if(int_time.field.Minute==m.ft.field.Minute)    	
		    	{
		    		BackLit_Value=bl[m.BackLit_Value_Max];
    		    	alarm_state=1;
    		    	// Disable screen saver
					sleep_disable();
					//-----------------------  		    	
					LCDTopPtr->Exit();
			    	LCDTopPtr=&Scr_2;	
			    	LCDTopPtr->Init();
			    	repaint_page();	
			    	    		
	    		}
	    	}
	    }
    }
    else
    {
   		if((int_time.field.Hour!=m.ft.field.Hour)||(int_time.field.Minute!=m.ft.field.Minute))
   		{
    		alarm_state=0;					    		
	    }
    }
#endif	
}
//-----------------------------------------------------------------------------------
void special_buttons_handle(TLCDPict*	lcd_ptr)
{
	if(LCDTopPtr==&Scr_0)
	  special_buttons_handle_00(lcd_ptr);
//	if(LCDTopPtr==&Scr_01)
//	  special_buttons_handle_01(lcd_ptr);
}

//-----------------------------------------------------------------------------------
void special_buttons_handle_00(TLCDPict*	lcd_ptr)
{
	if(LCDTopPtr!=&Scr_0)return;
	// Main switch handling
	if(LCDTopPtr==&Scr_0)
	{
/*		if(lcd_ptr==&But_Main_Switch)
		{
			if(But_Main_Switch.Stat==1)
			{
				own_state.bst|=but_Main_1_on;		
				own_state.ds.State=0xff;
				m.Dimmer.State=own_state.ds.State;
			}
			else
			{
				own_state.bst&=~but_Main_1_off;																	
				own_state.ds.State=0x00;			
				m.Dimmer.State=own_state.ds.State;
			}
			own_state.status|=bit_new_push;																		
			if(But_Main_Switch.Routine!=NULL)But_Main_Switch.Routine();						
		}	
*/		
	}
}
//-----------------------------------------------------------------------------------
void bell_pressed()
{	
	clear_single_bmp(&Alarm_bell_obj);		
}

//-----------------------------------------------------------------------------------
void onoff_pressed()
{
//	BUZZ_Time=10;
	if (But_Main_Switch.Stat == 1)
		own_state.bst |= Main_0_on;
	else
		own_state.bst &= ~Main_0_off;
	own_state.status |= bit_new_push;
	/*if (But_Main_Switch.Stat)
	{		
		dimmer_on(3);
		dimmer_sequence_timeout = 500;
		dimmer_sequence_state = 3;
		//dimmer_plus(1);
		//dimmer_plus(2);
		//dimmer_plus(3);
	}
	else
	{
		dimmer_off(3);
		dimmer_sequence_timeout = 500;
		dimmer_sequence_state = -3;		
		//dimmer_off(1);
		//dimmer_off(2);
		//dimmer_off(3);
	}*/
	
	//clear_single_bmp(&Alarm_bell_obj);		
}

//-----------------------------------------------------------------------------------
void makeup_routine()
{
	But_Do_Not_Disturb.Stat=0;
	show_single_bmp(&But_Do_Not_Disturb,0);	
	own_state.bst&=~DO_00;	
}
//-----------------------------------------------------------------------------------
void donot_disturb_routine()
{
	But_Makeup_Room.Stat=0;
	show_single_bmp(&But_Makeup_Room,0);	
	own_state.bst&=~DO_01;	
}
//-----------------------------------------------------------------------------------
