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
//-----------------------------------------------------------------------------------
extern TLCDPictTop Scr_0;
extern __farflash TLCDPict_Txt _Txt_0;
extern __farflash TLCDPict_Txt _Txt_1;
extern __farflash TLCDPict_Txt _Txt_2;
extern __farflash TLCDPict_Txt _Txt_3;
extern __farflash TLCDPict_Txt _Txt_4;
//-----------------------------------------------------------------------------------
//TTime _ft;
#define _ft MenuRegs.Time
u8 blinking_state=0;
u8 blinking_update=0;
extern u8 new_step;
extern u8 step;
extern u8 Current_ID;
extern u8 Branch_Number;
//-----------------------------------------------------------------------------------
void M_Get_Controller_Work(u8 id);
void upc_Set_Controller_In_Params(u8 id,u8 addr,u8* value,u8 len);
void upc_Get_Controller_Out_Params(u8 id,u8 addr,u8 len);
void M_Save_Controller_Params(u8 id);
//-----------------------------------------------------------------------------------
void scr5_init();
void scr5_close();
void scr5_routine();
void Mod_Tech_Time_Up();
void Mod_Tech_Time_Down();
void Store_Time();
void TechTime_Exit_Routine();
void show_time();
u8 get_day_of_week(TTime *time);
//--------------------------------------------
__farflash TLCDPict_Txt _Info_K_2=
{
	12,34,53,
	(bit_visible+bit_txt_1),
	13,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Info_K_1=
{
	10,34,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Info_K_0=
{
	8,34,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
//--------------------------------------------
//--------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _Info_V_1=
{
	16,74,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Info_V_0=
{
	14,74,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
//--------------------------------------------
//--------------------------------------------

__farflash TLCDPict_Txt _Info_Tk_2=
{
	12,74,53,
	(bit_visible+bit_txt_1),
	13,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Info_Tk_1=
{
	10,74,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Info_Tk_0=
{
	8,74,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
//--------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _Info_To_2=
{
	6,34,53,
	(bit_visible+bit_txt_1),
	13,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Info_To_1=
{
	4,34,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Info_To_0=
{
	2,34,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
//--------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _Info_Te_3=
{
	20,34,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Info_Te_2=
{
	18,34,53,
	(bit_visible+bit_txt_1),
	13,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Info_Te_1=
{
	16,34,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Info_Te_0=
{
	14,34,53,
	(bit_visible+bit_txt_1),
	10,
};

//--------------------------------------------
__farflash TLCDPict _TechTime_Exit=
{	
	// Exit
	27,0,27,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,	
	0,	
	NULL,	
	&Scr_4,
};
//--------------------------------------------
__farflash TLCDPict _TechTime_Day_Blank=
{	
	9,100,58,
	(bit_visible+bit_active+bit_static),
	0,	
	0,
	0,
	Set_Int_State_6,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _TechTime_Year_Blank=
{	
	14,34,58,
	(bit_visible+bit_active+bit_static),
	0,	
	0,
	0,
	Set_Int_State_4,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _TechTime_Minute_Blank=
{	
	14,74,57,
	(bit_visible+bit_active+bit_static),
	0,	
	0,
	0,
	Set_Int_State_5,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _TechTime_Hour_Blank=
{	
	8,74,57,
	(bit_visible+bit_active+bit_static),
	0,	
	0,
	0,
	Set_Int_State_2,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _TechTime_Date_Blank=
{	
	2,34,57,
	(bit_visible+bit_active+bit_static),
	0,	
	0,
	0,
	Set_Int_State_1,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _TechTime_Month_Blank=
{	
	8,34,57,
	(bit_visible+bit_active+bit_static),
	0,	
	0,
	0,
	Set_Int_State_0,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _TechTime_Minusm=
{	// entrance Light
	25,60,49,
	(bit_visible+bit_active),
	0,	
	0,
	0,
	Mod_Tech_Time_Down,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _TechTime_Plusm=
{	// Mood Light
	25,28,48,
	(bit_visible+bit_active),
	0,
	0,	
	0,	
	Mod_Tech_Time_Up,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _TechTime=
{
	0,15,16,
//	(bit_visible+bit_full),
	0,
	0,
	0,	
	0,	
	NULL,
	NULL,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_5=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	9,
	15,	
	scr5_init,
	scr5_routine,
	scr5_close,		
};
//-----------------------------------------------------------------------------------
void scr5_init()
{
	u8 i;
	Branch_Number=5;
	new_step=step=0;
	
	Obj[0]=_TechTime_Plusm;
	Obj[1]=_TechTime_Minusm;	
	Obj[2]=_TechTime_Month_Blank;
	Obj[3]=_TechTime_Date_Blank;
	Obj[4]=_TechTime_Hour_Blank;
	Obj[5]=_TechTime_Minute_Blank;
	Obj[6]=_TechTime_Year_Blank;
	Obj[7]=_TechTime_Day_Blank;
	Obj[8]=_TechTime_Exit;

	
	Txt[0]=_Info_Te_0;	
	Txt[1]=_Info_Te_1;	
	Txt[2]=_Info_Te_2;	
	Txt[3]=_Info_Te_3;	
	Txt[4]=_Info_To_0;	
	Txt[5]=_Info_To_1;	
	Txt[6]=_Info_To_2;		
	Txt[7]=_Info_Tk_0;			
	Txt[8]=_Info_Tk_1;
	Txt[9]=_Info_Tk_2;
	Txt[10]=_Info_V_0;
	Txt[11]=_Info_V_1;
	Txt[12]=_Info_K_0;
	Txt[13]=_Info_K_1;
	Txt[14]=_Info_K_2;		
		
	FT_Time=100;
	for(i=0;i<Scr_5.Txt_Num;i++)
		Txt[i].Stat=10;
	
	int_state&=~but_Int0s;
	int_state&=~but_Int1s;
	int_state&=~but_Int2s;		
//	int_state&=~but_Int3s;			
	int_state&=~but_Int4s;		
	int_state&=~but_Int6s;	
	int_state|=but_Int5s;	
	_ft=MenuRegs.Time;		
#ifdef __RENESAS	
	_ft.field.Day-=1;
#endif
	_ft=ft;
}
//-----------------------------------------------------------------------------------
void scr5_close()
{
	u8 i;
	upc.data_status|=b_time_new;
	MenuRegs.Time=_ft;		
	for(i=0;i<Scr_5.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
	lcd_clear_text();
}
//-----------------------------------------------------------------------------------
void scr5_routine()
{
//	u8 tmp;		lc
	
	if(FT_Time!=0)return;
//	if(page_offset!=PAGE_0_OFFSET)return;
//	FT_Time=1000;	
	if(tsc_n)time_blink|=1;
	
	if(int_state & but_Int1s)
	{
		// Date
		int_state&=~but_Int1s;		
//		time_blink=1;
//		show_time();
		blinking_state=0;
	}
	if(int_state & but_Int0s)
	{
		// Month
		int_state&=~but_Int0s;		
//		time_blink=1;
//		show_time();
		blinking_state=1;
	}
	if(int_state & but_Int4s)
	{
		// Year
		int_state&=~but_Int4s;		
//		time_blink=1;
//		show_time();
		blinking_state=2;
	}	
	if(int_state & but_Int2s)
	{
		// Hour
		int_state&=~but_Int2s;		
//		time_blink=1;
//		show_time();
		blinking_state=3;
	}
	if(int_state & but_Int5s)
	{
		// Minute
		int_state&=~but_Int5s;		
//		time_blink=1;
//		show_time();
		blinking_state=4;
	}			
	if(int_state & but_Int6s)
	{
		// Minute
		int_state&=~but_Int6s;		
//		time_blink=1;
//		show_time();
		blinking_state=5;
	}	
	show_time();	
}
//-----------------------------------------------------------------------------------
void show_time()
{
	u8 tmp;
		// Alarm time		
//		_ft=ft;
		get_day_of_week(&_ft);
		// *** Hours ***
		LCDMenuPtr_Tmp_Txt=&Txt[7];
		tmp=_ft.field.Hour/10;
		if(blinking_state==3)
		{
			if((time_blink & 1)==0)
				tmp=16;			
		}
			
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}
	
		LCDMenuPtr_Tmp_Txt=&Txt[8];			
		tmp=_ft.field.Hour-tmp*10;
		if(blinking_state==3)
			if((time_blink & 1)==0)
				tmp=16;			
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}
		// *** : ***
		LCDMenuPtr_Tmp_Txt=&Txt[9];			
		tmp=13;
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}		
		// *** Minutes ***
		LCDMenuPtr_Tmp_Txt=&Txt[10];			
		tmp=_ft.field.Minute/10;
		if(blinking_state==4)
			if((time_blink & 1)==0)
				tmp=16;		
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}

		LCDMenuPtr_Tmp_Txt=&Txt[11];			
		tmp=_ft.field.Minute-tmp*10;
		if(blinking_state==4)
			if((time_blink & 1)==0)
				tmp=16;				
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}	
		
		// *** Days ***
		LCDMenuPtr_Tmp_Txt=&Txt[4];	
		tmp=_ft.field.Date/10;
		if(blinking_state==0)
			if((time_blink & 1)==0)
				tmp=16;		
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}

		LCDMenuPtr_Tmp_Txt=&Txt[5];		
		tmp=_ft.field.Date-tmp*10;			
		if(blinking_state==0)
			if((time_blink & 1)==0)
				tmp=16;		
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);	
		}
		
		LCDMenuPtr_Tmp_Txt=&Txt[6];		
		tmp=12;				
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);	
		}		
		// *** Month ***
		LCDMenuPtr_Tmp_Txt=&Txt[12];	
		tmp=_ft.field.Month/10;
		if(blinking_state==1)
			if((time_blink & 1)==0)
				tmp=16;		
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}

		LCDMenuPtr_Tmp_Txt=&Txt[13];		
		tmp=_ft.field.Month-tmp*10;			
		if(blinking_state==1)
			if((time_blink & 1)==0)
				tmp=16;		
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);	
		}	
		
		LCDMenuPtr_Tmp_Txt=&Txt[14];		
		tmp=12;			
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);	
		}			
		// Year
		LCDMenuPtr_Tmp_Txt=&Txt[0];			
		tmp=2;
		if(blinking_state==2)
			if((time_blink & 1)==0)
				tmp=16;		
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}

		LCDMenuPtr_Tmp_Txt=&Txt[1];			
		tmp=0;
		if(blinking_state==2)
			if((time_blink & 1)==0)
				tmp=16;			
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);	
		}
				
		LCDMenuPtr_Tmp_Txt=&Txt[2];			
		tmp=_ft.field.Year/10;
		if(blinking_state==2)
			if((time_blink & 1)==0)
				tmp=16;			
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}

		LCDMenuPtr_Tmp_Txt=&Txt[3];			
		tmp=_ft.field.Year-tmp*10;
		if(blinking_state==2)
			if((time_blink & 1)==0)
				tmp=16;			
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);	
		}
		// Day of week		
#ifndef __RENESAS		
		_ft.field.Day&=0x07;
		if(_ft.field.Day==0)_ft.field.Day=1;
		if(blinking_state==5)
		{
			if((time_blink & 1)==0)
				lcd_sprintf_P(DaysOfWeek[7],8,13);	
			else
				lcd_sprintf_P(DaysOfWeek[_ft.field.Day-1],8,13);	
		}
		else
			lcd_sprintf_P(DaysOfWeek[_ft.field.Day-1],8,13);				
#else
//		_ft.field.Day&=0x07;
//		if(_ft.field.Day>6)_ft.field.Day=6;
//		if(_ft.field.Day==0)_ft.field.Day=1;		
		if(blinking_state==5)
		{
			if((time_blink & 1)==0)
				lcd_sprintf_P(DaysOfWeek[7],8,13);	
			else
				lcd_sprintf_P(DaysOfWeek[_ft.field.Day-1],8,13);	
		}
		else
			lcd_sprintf_P(DaysOfWeek[_ft.field.Day-1],8,13);				

#endif
}
//-----------------------------------------------------------------------------------
void Mod_Tech_Time_Up()
{
	switch(blinking_state)
	{
		case 0:
			if(_ft.field.Date<31)_ft.field.Date+=1;
			else
				_ft.field.Date=1;		
		break;	
		case 1:
			if(_ft.field.Month<12)_ft.field.Month+=1;
			else
				_ft.field.Month=1;		
		break;		
		case 2:
			if(_ft.field.Year<99)_ft.field.Year+=1;
			else
				_ft.field.Year=0;		
		break;		
		case 3:
			if(_ft.field.Hour<23)_ft.field.Hour+=1;
			else
				_ft.field.Hour=0;		
		break;	
		case 4:
			if(_ft.field.Minute<59)_ft.field.Minute+=1;
			else
				_ft.field.Minute=0;
		break;
#ifndef __RENESAS				
		case 5:
			if(_ft.field.Day<7)_ft.field.Day+=1;
			else
				_ft.field.Day=1;
			lcd_sprintf_P(DaysOfWeek[7],9,13);	
		break;		
#else
		case 5:
			if(_ft.field.Day<6)_ft.field.Day+=1;
			else
				_ft.field.Day=0;
			lcd_sprintf_P(DaysOfWeek[7],9,13);	
		break;		
#endif		
	}
	new_step=2;
	Button_no_update_time=500;
	scr5_routine();
}
//-----------------------------------------------------------------------------------
void Mod_Tech_Time_Down()
{
	switch(blinking_state)
	{
		case 0:
			if(_ft.field.Date>1)_ft.field.Date-=1;
			else
				_ft.field.Date=31;		
		break;	
		case 1:
			if(_ft.field.Month>1)_ft.field.Month-=1;
			else
				_ft.field.Month=12;		
		break;		
		case 2:
			if(_ft.field.Year>0)_ft.field.Year-=1;
			else
				_ft.field.Year=99;		
		break;		
		case 3:
			if(_ft.field.Hour>0)_ft.field.Hour-=1;
			else
				_ft.field.Hour=23;		
		break;	
		case 4:
			if(_ft.field.Minute>0)_ft.field.Minute-=1;
			else
				_ft.field.Minute=59;
		break;
#ifndef __RENESAS						
		case 5:
			if(_ft.field.Day>1)_ft.field.Day-=1;
			else
				_ft.field.Day=7;
			lcd_sprintf_P(DaysOfWeek[7],9,13);	
		break;		
#else
		case 5:
			if(_ft.field.Day>0)_ft.field.Day-=1;
			else
				_ft.field.Day=6;
			lcd_sprintf_P(DaysOfWeek[7],9,13);	
		break;		
#endif
	}
	new_step=2;
	Button_no_update_time=500;
	scr5_routine();	
}
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void Schedule_N5()
{
//	u16 i,tmp;
	u16 tmp16;
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
			if(Time0==0)
			switch(step)
			{
				case 0:		
					step++;
					M_SCH_Time=100;	
					M_Get_Controller_Register(Current_ID,&MenuRegs.Time,7);	
				break;		
				case 1:
					step=0;
					tmp16=1;
					upc_Set_Controller_In_Params(0,10,(u8*)&tmp16,1);
					M_SCH_Time=50;
				break;		
				
				case 2:		
					step=0;
//					ft=MenuRegs.Time;
					M_Set_Controller_Time(0,0);
					M_SCH_Time=10;	
				break;		
				
			}
		}
		
	}
	
}
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
