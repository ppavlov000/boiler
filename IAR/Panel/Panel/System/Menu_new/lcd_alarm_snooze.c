//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
#include "..\Menu_New\lcd_template.h"
#include "..\Menu_New\lcd_calibrate.h"
#include "..\Menu_New\lcd_alarm.h"
#include "..\Menu_New\lcd_alarm_snooze.h"
//-----------------------------------------------------------------------------------
extern TLCDPictTop Scr_0;
extern TLCDPictTop Scr_0;
extern __farflash TLCDPict_Txt _Txt_0;
extern __farflash TLCDPict_Txt _Txt_1;
extern __farflash TLCDPict_Txt _Txt_2;
extern __farflash TLCDPict_Txt _Txt_3;
extern __farflash TLCDPict_Txt _Txt_4;
//-----------------------------------------------------------------------------------
void scr2_init();
void scr2_routine();
void scr2_close();
void Mod_Time_5();
void Snooze_Alarm_Off();
void Snooze_Exit();
//--------------------------------------------
__farflash TLCDPict _Snooze_Clock=
{	// Reading
	10,14,46,
	(bit_visible+bit_full),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Snooze_Off=
{	
	8,87,45,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,	
	Snooze_Alarm_Off,
	&Scr_0,
};
//--------------------------------------------
__farflash TLCDPict _Snooze_5min=
{	
	16,87,47,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,	
	Mod_Time_5,
	&Scr_0,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Snooze=
{
	0,0,29,
//	(bit_visible+bit_full),
	0,
	0,
	0,	
	0,	
	show_time_snooze,
	NULL,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_2=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	3,
	5,	
	scr2_init,
	scr2_routine,
	scr2_close,		
};
//-----------------------------------------------------------------------------------
void scr2_init()
{
	u8 i;
	Obj[0]=_Snooze_5min;
	Obj[1]=_Snooze_Off;	
	Obj[2]=_Snooze_Clock;
	
	Txt[0]=_Txt_0;	
	Txt[1]=_Txt_1;	
	Txt[2]=_Txt_2;	
	Txt[3]=_Txt_3;	
	Txt[4]=_Txt_4;	
	
	FT_Time=100;
	for(i=0;i<Scr_1.Txt_Num;i++)
		Txt[i].Stat=10;
		
	Txt[2].Stat=13;		
	
	Snooze_Time=60;//c
}
//-----------------------------------------------------------------------------------
void scr2_close()
{
	u8 i;
	for(i=0;i<Scr_2.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
}
//-----------------------------------------------------------------------------------
void scr2_routine()
{
	u8 tmp;			
	if(Snooze_Time==0)
	{
		sleep_disable();
		m.Alarm_Status=0;
		FiveMins.field.Minute=m.Alarm.field.Minute;
		FiveMins.field.Hour=m.Alarm.field.Hour;
		push.status=1; 
		push.LCDMenuPtr=&Obj[1];
		return;
	}	
	if(FT_Time!=0)return;	
	if(int_state & but_Int3s)
	{
		int_state&=~but_Int3s;		
		if(time_blink & 1)
		{
			BackLit_Value=bl[m.BackLit_Value_Max];
			BUZZ_Time=500;
		}
		else
		{
			BackLit_Value=bl[0];
		}
	// Alarm time
		show_single_bmp_txt(&Txt[2]);

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
void Mod_Time_5()
{
	FiveMins.field.Minute=m.ft.field.Minute+5;
	if(FiveMins.field.Minute>59)
	{
		FiveMins.field.Minute-=60;
		if(FiveMins.field.Hour<23)FiveMins.field.Hour+=1;
		else FiveMins.field.Hour=0;
	}
}
//-----------------------------------------------------------------------------------
void Snooze_Alarm_Off()
{
	m.Alarm_Status=0;
	FiveMins.field.Minute=m.Alarm.field.Minute;
	FiveMins.field.Hour=m.Alarm.field.Hour;
}
//-----------------------------------------------------------------------------------
void Snooze_Exit()
{
	FiveMins.field.Minute=m.Alarm.field.Minute;
	FiveMins.field.Hour=m.Alarm.field.Hour;
}
//-----------------------------------------------------------------------------------

