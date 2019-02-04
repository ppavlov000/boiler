//-----------------------------------------------------------------------------------
#include "..\Main.h"
//-----------------------------------------------------------------------------------
#include "..\Menu_New\lcd_template.h"
#include "..\Menu_New\lcd_calibrate.h"
#include "..\Menu_New\lcd_alarm.h"
#include "..\Menu_New\lcd_alarm_snooze.h"
//-----------------------------------------------------------------------------------
extern TLCDPictTop Scr_0;
extern __farflash TLCDPict_Txt _Txt_0;
extern __farflash TLCDPict_Txt _Txt_1;
extern __farflash TLCDPict_Txt _Txt_2;
extern __farflash TLCDPict_Txt _Txt_3;
extern __farflash TLCDPict_Txt _Txt_4;
//-----------------------------------------------------------------------------------
void scr1_init();
void scr1_routine();
void scr1_close();	
void Mod_Alarm_On();
void Mod_Alarm_Off();
void Mod_Time_Up();
void Mod_Time_Down();
//--------------------------------------------
__farflash TLCDPict _Alarm_Exit=
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
TLCDPict _Alarm_ATime_Sign_Min=
{
	// Blank
	16,54,50,
	(bit_visible+bit_full),
	0,
	0,
	0,	
	Set_Int_State_2,
	NULL,	
};
//--------------------------------------------
TLCDPict _Alarm_ATime_Sign_Hour=
{
	// Blank
	10,54,50,
	(bit_visible+bit_full),
	0,
	0,
	0,	
	Set_Int_State_1,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Alarm_Clock=
{	// Reading
	6,14,43,
	(bit_visible+bit_full),
	0,
	0,
	0,	
	NULL,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Alarm_Bell=
{	// Nightstand lamp
	6,49,56,
	(bit_visible),
	1,
	0,
	0,	
	NULL,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Alarm_Minus=
{	
	1,48,26,
	(bit_visible+bit_active),
	0,	
	0,
	0,
	Mod_Time_Down,
	NULL,
};

//--------------------------------------------
__farflash TLCDPict _Alarm_Plus=
{	
	24,48,28,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Mod_Time_Up,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Alarm_Off=
{	// Bedroom Curtain open
	8,87,45,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Mod_Alarm_Off,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Alarm_On=
{	// Bedroom Curtain close
	16,87,44,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Mod_Alarm_On,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Alarm=
{
	0,0,29,
//	(bit_visible+bit_full),
	0,
	0,
	0,	
	0,	
	show_time_alarm,
	NULL,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
__farflash TLCDPict_Txt _AcTime_4=
{
	18,14,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
__farflash TLCDPict_Txt _AcTime_3=
{
	16,14,53,
	(bit_visible+bit_txt_1),
	10,	
};
//--------------------------------------------
__farflash TLCDPict_Txt _AcTime_2=
{
	14,14,53,
	(bit_visible+bit_txt_1),
	13,
};
//--------------------------------------------
__farflash TLCDPict_Txt _AcTime_1=
{
	12,14,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
__farflash TLCDPict_Txt _AcTime_0=
{
	10,14,53,
	(bit_visible+bit_txt_1),
	10,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_1=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	9,
	10,	
	scr1_init,
	scr1_routine,
	scr1_close,		
};
//-----------------------------------------------------------------------------------
void scr1_init()
{
	u8 i;
	Obj[0]=_Alarm_On;
	Obj[1]=_Alarm_Off;	
	Obj[2]=_Alarm_Plus;
	Obj[3]=_Alarm_Minus;
	Obj[4]=_Alarm_Bell;
	Obj[5]=_Alarm_Clock;
	Obj[6]=_Alarm_Exit;
	Obj[7]=_Alarm_ATime_Sign_Hour;
	Obj[8]=_Alarm_ATime_Sign_Min;
	
	Txt[0]=_Txt_0;	
	Txt[1]=_Txt_1;	
	Txt[2]=_Txt_2;	
	Txt[3]=_Txt_3;	
	Txt[4]=_Txt_4;	
	
	Txt[5]=_AcTime_0;	
	Txt[6]=_AcTime_1;	
	Txt[7]=_AcTime_2;	
	Txt[8]=_AcTime_3;	
	Txt[9]=_AcTime_4;	
	
	FT_Time=100;
	for(i=0;i<Scr_1.Txt_Num;i++)
		Txt[i].Stat=10;
		
	Txt[2].Stat=13;		
	Txt[7].Stat=13;
	
	int_state|=but_Int0s;
	int_state&=~but_Int1s;
	int_state&=~but_Int2s;		
	int_pos=2;
	FiveMins.field.Minute=m.Alarm.field.Minute;
	FiveMins.field.Hour=m.Alarm.field.Hour;		
	alarm_state=0;	
	if(m.Alarm_Status)
		Obj[4].Stat=0;
	else
		Obj[4].Stat=1;	
}
//-----------------------------------------------------------------------------------
void scr1_close()
{
	u8 i;
	for(i=0;i<Scr_1.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
	params_store();	
}
//-----------------------------------------------------------------------------------
void scr1_routine()
{
	u8 tmp;	
	if(FT_Time!=0)return;
//	if(page_offset!=PAGE_0_OFFSET)return;
	if(m.Alarm_Status)
	{
		if(Obj[4].Stat!=0)
		{
			Obj[4].Stat=0;
			show_single_bmp(&Obj[4],0);			
		}
	}
	else
	{
		if(Obj[4].Stat!=1)
		{
			Obj[4].Stat=1;
			show_single_bmp(&Obj[4],0);			
		}
	}



	
	if(int_state & but_Int1s)
	{
		int_state&=~but_Int1s;	
		int_state|=but_Int0s;		
		if(int_pos!=1)
			int_pos=1;
		Txt[3].Stat=10;
		Txt[4].Stat=10;
	}
	if(int_state & but_Int2s)
	{
		int_state&=~but_Int2s;	
		int_state|=but_Int0s;		
		if(int_pos!=2)
			int_pos=2;
		
		Txt[0].Stat=10;
		Txt[1].Stat=10;
	}
	if(int_state & but_Int0s)
	{
		int_state&=~but_Int0s;
		// Alarm time
		show_single_bmp_txt(&Txt[2]);
		// *** Hours ***
		LCDMenuPtr_Tmp_Txt=&Txt[0];
		tmp=m.Alarm.field.Hour/10;
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}
	
		LCDMenuPtr_Tmp_Txt=&Txt[1];			
		tmp=m.Alarm.field.Hour-tmp*10;
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}
		LCDMenuPtr_Tmp_Txt=&Txt[3];			
		tmp=m.Alarm.field.Minute/10;
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}

		LCDMenuPtr_Tmp_Txt=&Txt[4];			
		tmp=m.Alarm.field.Minute-tmp*10;
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}		
	}
	if(int_state & but_Int3s)
	{
		int_state&=~but_Int3s;	
		// Actual time
		if(time_blink & 1)
			show_single_bmp_txt(&Txt[7]);
		else
			clear_single_bmp_txt(&Txt[7]);		

		LCDMenuPtr_Tmp_Txt=&Txt[5];		
		tmp=m.ft.field.Hour/10;
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}
	
		LCDMenuPtr_Tmp_Txt=&Txt[6];			
		tmp=m.ft.field.Hour-tmp*10;
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}
						
		LCDMenuPtr_Tmp_Txt=&Txt[8];			
		tmp=m.ft.field.Minute/10;
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}

		LCDMenuPtr_Tmp_Txt=&Txt[9];			
		tmp=m.ft.field.Minute-tmp*10;
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}	
		// Blinking
		// *** Hours ***
//		if(int_state & but_Int1s)
		if(int_pos==1)			
		{
			LCDMenuPtr_Tmp_Txt=&Txt[0];
			tmp=m.Alarm.field.Hour/10;
			if(time_blink & 1)
				tmp=16;
			if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
			{
				LCDMenuPtr_Tmp_Txt->Stat=tmp;
				show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
			}
	
			LCDMenuPtr_Tmp_Txt=&Txt[1];			
			tmp=m.Alarm.field.Hour-tmp*10;
			if(time_blink & 1)
				tmp=16;			
			if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
			{
				LCDMenuPtr_Tmp_Txt->Stat=tmp;
				show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
			}
		}		
		// *** Minutes ***
//		if(int_state & but_Int2s)
		if(int_pos==2)			
		{
			LCDMenuPtr_Tmp_Txt=&Txt[3];			
			tmp=m.Alarm.field.Minute/10;
			if(time_blink & 1)
				tmp=16;			
			if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
			{
				LCDMenuPtr_Tmp_Txt->Stat=tmp;
				show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
			}

			LCDMenuPtr_Tmp_Txt=&Txt[4];			
			tmp=m.Alarm.field.Minute-tmp*10;
			if(time_blink & 1)
				tmp=16;			
			if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
			{
				LCDMenuPtr_Tmp_Txt->Stat=tmp;
				show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
			}		
		
		}		
			
	}
}
//-----------------------------------------------------------------------------------
void Mod_Alarm_On()
{
	m.Alarm_Status=1;
//	_Button_10.Stat=0;
	Obj[4].Stat=0;	
	show_single_bmp(&Obj[4],0);
	FiveMins.field.Minute=m.Alarm.field.Minute;
	FiveMins.field.Hour=m.Alarm.field.Hour;
}
//-----------------------------------------------------------------------------------
void Mod_Alarm_Off()
{
	m.Alarm_Status=0;
//	_Button_10.Stat=1;
	Obj[4].Stat=1;	
	show_single_bmp(&Obj[4],0);
	FiveMins.field.Minute=m.Alarm.field.Minute;
	FiveMins.field.Hour=m.Alarm.field.Hour;
}
//-----------------------------------------------------------------------------------
void Mod_Time_Up()
{
	Set_Int_State_0();
	if(int_pos==2)
	{
		if(m.Alarm.field.Minute<59)m.Alarm.field.Minute+=1;
		else
		{
			 m.Alarm.field.Minute=0;
			if(m.Alarm.field.Hour<23)m.Alarm.field.Hour+=1;
			else m.Alarm.field.Hour=0;
		}
	}
	if(int_pos==1)
	{
			if(m.Alarm.field.Hour<23)m.Alarm.field.Hour+=1;
			else m.Alarm.field.Hour=0;
	}	
	FiveMins.field.Minute=m.Alarm.field.Minute;
	FiveMins.field.Hour=m.Alarm.field.Hour;	
}
//-----------------------------------------------------------------------------------
void Mod_Time_Down()
{
	Set_Int_State_0();
	if(int_pos==2)
	{
		if(m.Alarm.field.Minute>0)m.Alarm.field.Minute-=1;
		else
		{
			m.Alarm.field.Minute=59;
			if(m.Alarm.field.Hour>0)m.Alarm.field.Hour-=1;
			else m.Alarm.field.Hour=0;
		}
	}
	if(int_pos==1)
	{
			if(m.Alarm.field.Hour>0)m.Alarm.field.Hour-=1;
			else m.Alarm.field.Hour=23;
	}
	FiveMins.field.Minute=m.Alarm.field.Minute;
	FiveMins.field.Hour=m.Alarm.field.Hour;	
}
//-----------------------------------------------------------------------------------
