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
#include "..\Menu_new\lcd_screen_0.h"
//-----------------------------------------------------------------------------------
//#define NO_ALARM
//-----------------------------------------------------------------------------------
#define but_Main_1_on	(DO_03+DO_15)	
#define but_Main_1_off	(DO_03+DO_15)	
//-----------------------------------------------------------------------------------
#define But_Main_Switch			Obj[11]
#define But_Do_Not_Disturb		Obj[6]
#define But_Makeup_Room			Obj[15]
#define But_Curtain_Open		Obj[15]
#define But_Curtain_Close		Obj[15]

#define But_Dimmer_0			Obj[7]
#define But_Dimmer_1			Obj[0]
#define But_Dimmer_2			Obj[5]
#define But_Dimmer_3			Obj[1]
#define But_Dimmer_4			Obj[4]
#define But_Dimmer_5			Obj[15]
#define But_Dimmer_6			Obj[9]
#define But_Dimmer_7			Obj[8]

#define Alarm_bell_obj			Obj[12]
//-----------------------------------------------------------------------------------
u8 Dimmer_Dir[8]={0};	//0=+ 1=-
//-----------------------------------------------------------------------------------
void scr01_init();
void scr01_close();
void scr01_routine();

void bell_pressed_01();
void makeup_routine_01();
void donot_disturb_routine_01();

void dimmer_handle_0();
void dimmer_handle_1();
void dimmer_handle_2();
void dimmer_handle_3();
void dimmer_handle_4();
void dimmer_handle_5();
void dimmer_handle_6();
void dimmer_handle_7();

void dimmer_plus(u8 num);
void dimmer_minus(u8 num);
void dimmer_off(u8 num);
//-----------------------------------------------------------------------------------
u8 dimmer_slope[8]={0};
u8 dimmer_new_press=0;
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Alarm_Button_01=
{	// Bell
	20,53,14,
	(bit_visible+bit_active+bit_new_page),
	1,
	0,
	0,	
	bell_pressed_01,
	&Scr_1,
};
//--------------------------------------------
__farflash TLCDPict _Main_01=
{	// Main switch
	0,0,17,
	(bit_visible+bit_active+bit_trigger),
	0,
	but_Main_1_on,
	0,
	NULL,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Spot_01=
{	
	6,88,81,
	(bit_visible+bit_active+bit_trigger+bit_dimmer),
	0,
	0,	
	0,	
	dimmer_handle_0,
	NULL,
};

//--------------------------------------------
__farflash TLCDPict _Torsh_01=
{	
	13,88,75,
	(bit_visible+bit_active+bit_trigger+bit_dimmer),
	0,
	0,	
	0,	
	dimmer_handle_6,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Bulb_01=
{	
	6,0,79,
	(bit_visible+bit_active+bit_trigger+bit_dimmer),
	0,
	DO_03,	
	0,
	dimmer_handle_7,
	NULL,
};

//--------------------------------------------
__farflash TLCDPict _Book_01=
{	
	25,0,80,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,
	NULL,
	&Scr_0,
};
//--------------------------------------------
__farflash TLCDPict _Night2_01=
{	// Makeup
	0,88,76,
	(bit_visible+bit_active+bit_trigger+bit_dimmer),
	0,
	0,	
	0,	
	dimmer_handle_2,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Jalouisie_01=
{	
	19,88,78,
	(bit_visible+bit_active+bit_trigger+bit_dimmer),
	0,
	0,	
	0,	
	dimmer_handle_4,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Mood_01=
{	
	25,88,18,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,
	NULL,
	&Scr_3,	
};
//--------------------------------------------
__farflash TLCDPict _Button_1_01=
{	// Bedroom Curtain open
	19,0,82,
	(bit_visible+bit_active+bit_trigger+bit_dimmer),
	0,
	0,	
	0,	
	dimmer_handle_3,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Button_0_01=
{	// Bedroom Curtain close
	13,0,74,
	(bit_visible+bit_active+bit_trigger+bit_dimmer),
	0,
	0,	
	0,	
	dimmer_handle_1,
	NULL,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_01=
{
	0,0,0,
	0,
	13,
	5,	
	scr01_init,
	scr01_routine,
	scr01_close,		
};
//-----------------------------------------------------------------------------------
void scr01_init()
{
	Obj[0]=_Button_0_01;
	Obj[1]=_Button_1_01;
	
	Obj[2]=_Mood_01;
	Obj[3]=_Null;
	Obj[4]=_Jalouisie_01;
	Obj[5]=_Night2_01;
	Obj[6]=_Null;
	Obj[7]=_Spot_01;
	Obj[8]=_Bulb_01;
	Obj[9]=_Torsh_01;	
	Obj[10]=_Book_01;
	Obj[11]=_Main_01;
	Obj[12]=_Alarm_Button_01;	
	
		
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
void scr01_close()
{
	u8 i;
	for(i=0;i<Scr_0.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
}
//-----------------------------------------------------------------------------------
void scr01_routine()
{
	u8 tmp;	
		
	if(FT_Time!=0)return;	
	if(page_offset!=PAGE_0_OFFSET)return;
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
void dimmer_handle_0()
{
  	if(But_Dimmer_0.Stat==0)dimmer_off(0);	
	else dimmer_plus(0);
}
//-----------------------------------------------------------------------------------
void dimmer_handle_1()
{
  	if(But_Dimmer_1.Stat==0)dimmer_off(1);	
	else dimmer_plus(1);
}
//-----------------------------------------------------------------------------------
void dimmer_handle_2()
{
  	if(But_Dimmer_2.Stat==0)dimmer_off(2);	
	else dimmer_plus(2);
}

//-----------------------------------------------------------------------------------
void dimmer_handle_3()
{
  	if(But_Dimmer_3.Stat==0)dimmer_off(3);	
	else dimmer_plus(3);
}

//-----------------------------------------------------------------------------------
void dimmer_handle_4()
{
  	if(But_Dimmer_4.Stat==0)dimmer_off(4);	
	else dimmer_plus(4);
}
//-----------------------------------------------------------------------------------
void dimmer_handle_5()
{
  	if(But_Dimmer_5.Stat==0)dimmer_off(5);	
	else dimmer_plus(5);
}
//-----------------------------------------------------------------------------------
void dimmer_handle_6()
{
  	if(But_Dimmer_6.Stat==0)dimmer_off(6);	
	else dimmer_plus(6);
}
//-----------------------------------------------------------------------------------
void dimmer_handle_7()
{
  	if(But_Dimmer_7.Stat==0)dimmer_off(7);	
	else dimmer_plus(7);
}
//-----------------------------------------------------------------------------------
void dimmer_plus(u8 num)
{
  	if(Dimmer_Time2==0)
	{
		if(dimmer_new_press==0)
		{
			dimmer_slope[num]++;
			dimmer_new_press=1;
			if(dimmer_slope[num] & 1)
				Dimmer_Dir[num]=0;
			else
				Dimmer_Dir[num]=1;
		}
		if(Dimmer_Dir[num]==0)
		{
			if(R0_Time==0)
				m.Dimmer.Power[num]+=2;
			if(m.Dimmer.Power[num]>=99)
			{
				m.Dimmer.Power[num]=99;	
	//			Dimmer_Time2=1000;
	//			Dimmer_Dir[num]=1;
			}
		}
		else
		{
			if(m.Dimmer.Power[num]>=2)
			{
				m.Dimmer.Power[num]-=2;
			}
			else
			{
				m.Dimmer.Power[num]=0;	
				Dimmer_Dir[num]=0;		
				Dimmer_Time2=2000;
			}
		}
	} 
	own_state.status|=bit_new_push;	
	own_state.ds.Power=m.Dimmer.Power[num];
	own_state.ds.Channel=num;	
	m.Dimmer.State|=(1<<num);			
	own_state.ds.State=m.Dimmer.State;
}
//-----------------------------------------------------------------------------------
void dimmer_off(u8 num)
{
//	m.Dimmer.Power[num]=0;	
	own_state.status|=bit_new_push;	
	own_state.ds.Power=m.Dimmer.Power[num];
	own_state.ds.Channel=num;	
	m.Dimmer.State&=~(1<<num);				
	own_state.ds.State=m.Dimmer.State;
}
//-----------------------------------------------------------------------------------
void update_page_01()
{
	u8 old_stat;
	u32 tmp;
	u8 i;
	if(page_offset!=PAGE_0_OFFSET)return;
	if(LCDTopPtr!=&Scr_01)return;
	if(bmp_update)
	{
		for(i=0;i<Scr_01.Obj_Num;i++)	
		{
			
			old_stat=Obj[i].Stat;	
			if((Obj[i].Action & mask_simple_buttons)!=0)
			{
				tmp=own_state.bst & Obj[i].Action;
				if(tmp == Obj[i].Action)
					Obj[i].Stat=1;
				else
					Obj[i].Stat=0;
			
				if(old_stat!=Obj[i].Stat)
					show_single_bmp(&Obj[i],0);			
			}
		}

		tmp=1<<0;
		old_stat=But_Dimmer_0.Stat;			
		if(m.Dimmer.State & tmp)
			But_Dimmer_0.Stat=1;
		else
			But_Dimmer_0.Stat=0;				  
		if(old_stat!=But_Dimmer_0.Stat)
			show_single_bmp(&But_Dimmer_0,0);			

		tmp=1<<1;
		old_stat=But_Dimmer_1.Stat;			
		if(m.Dimmer.State & tmp)
			But_Dimmer_1.Stat=1;
		else
			But_Dimmer_1.Stat=0;				  
		if(old_stat!=But_Dimmer_1.Stat)
			show_single_bmp(&But_Dimmer_1,0);			

		tmp=1<<2;
		old_stat=But_Dimmer_2.Stat;			
		if(m.Dimmer.State & tmp)
			But_Dimmer_2.Stat=1;
		else
			But_Dimmer_2.Stat=0;				  
		if(old_stat!=But_Dimmer_2.Stat)
			show_single_bmp(&But_Dimmer_2,0);			

		tmp=1<<3;
		old_stat=But_Dimmer_3.Stat;			
		if(m.Dimmer.State & tmp)
			But_Dimmer_3.Stat=1;
		else
			But_Dimmer_3.Stat=0;				  
		if(old_stat!=But_Dimmer_3.Stat)
			show_single_bmp(&But_Dimmer_3,0);			

		tmp=1<<4;
		old_stat=But_Dimmer_4.Stat;			
		if(m.Dimmer.State & tmp)
			But_Dimmer_4.Stat=1;
		else
			But_Dimmer_4.Stat=0;				  
		if(old_stat!=But_Dimmer_4.Stat)
			show_single_bmp(&But_Dimmer_4,0);			

		tmp=1<<5;
		old_stat=But_Dimmer_5.Stat;			
		if(m.Dimmer.State & tmp)
			But_Dimmer_5.Stat=1;
		else
			But_Dimmer_5.Stat=0;				  
		if(old_stat!=But_Dimmer_5.Stat)
			show_single_bmp(&But_Dimmer_5,0);			

		tmp=1<<6;
		old_stat=But_Dimmer_6.Stat;			
		if(m.Dimmer.State & tmp)
			But_Dimmer_6.Stat=1;
		else
			But_Dimmer_6.Stat=0;				  
		if(old_stat!=But_Dimmer_6.Stat)
			show_single_bmp(&But_Dimmer_6,0);			

		tmp=1<<7;
		old_stat=But_Dimmer_7.Stat;			
		if(m.Dimmer.State & tmp)
			But_Dimmer_7.Stat=1;
		else
			But_Dimmer_7.Stat=0;				  
		if(old_stat!=But_Dimmer_7.Stat)
			show_single_bmp(&But_Dimmer_7,0);	
/*		// Some special buttons
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
*/		
	}		
	bmp_update=0;
}
//-----------------------------------------------------------------------------------
void check_alarm_01()
{
#ifdef NO_ALARM
	return;
#else
//	if(page_offset!=PAGE_0_OFFSET)return;
	if(LCDTopPtr!=&Scr_01)return;
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
void special_buttons_handle_01(TLCDPict*	lcd_ptr)
{
	if(LCDTopPtr!=&Scr_01)return;
	// Main switch handling
	if(LCDTopPtr==&Scr_01)
	{
		if(lcd_ptr==&But_Main_Switch)
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
	}
}
//-----------------------------------------------------------------------------------
void bell_pressed_01()
{	
	clear_single_bmp(&Alarm_bell_obj);		
}
//-----------------------------------------------------------------------------------
void makeup_routine_01()
{
	But_Do_Not_Disturb.Stat=0;
	show_single_bmp(&But_Do_Not_Disturb,0);	
	own_state.bst&=~DO_00;	
}
//-----------------------------------------------------------------------------------
void donot_disturb_routine_01()
{
	But_Makeup_Room.Stat=0;
	show_single_bmp(&But_Makeup_Room,0);	
	own_state.bst&=~DO_01;	
}
//-----------------------------------------------------------------------------------
