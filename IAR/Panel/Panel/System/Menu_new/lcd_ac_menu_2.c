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
	18,54,71,
	(bit_visible+bit_full),
	0,
	0,	
	0,	
	NULL,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _T_Button_8=
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
__farflash TLCDPict _T_Button_7=
{
	// heating/cooling
	0,0,23,
	0,
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
	3,44,26,
	(bit_visible+bit_active),
	0,
	but_Int0,
	0,		
//	Mod_BackLit_Down,
	Mod_Temperature_Down,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _T_Button_5=
{
	// Plus
	23,44,28,
	(bit_visible+bit_active),
	0,
	but_Int0,
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
__farflash TLCDPict_Txt _AC_Temperature_txt_5=
{
	20,50,53,
	(bit_visible+bit_txt_1),
	16,
};
//--------------------------------------------
__farflash TLCDPict_Txt _AC_Temperature_txt_4=
{
	18,50,53,
	(bit_visible+bit_txt_1),
	16,
};
//--------------------------------------------
__farflash TLCDPict_Txt _AC_Temperature_txt_3=
{
	16,50,53,
	(bit_visible+bit_txt_1),
	16,
};
//--------------------------------------------
__farflash TLCDPict_Txt _AC_Temperature_txt_2=
{
	14,50,53,
	(bit_visible+bit_txt_1),
	16,
};
//--------------------------------------------
__farflash TLCDPict_Txt _AC_Temperature_txt_1=
{
	12,50,53,
	(bit_visible+bit_txt_1),
	16,
};
//--------------------------------------------
__farflash TLCDPict_Txt _AC_Temperature_txt_0=
{
	10,50,53,
	(bit_visible+bit_txt_1),
	16,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_3=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	10,
	4,	
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

	Txt[0]=_AC_Temperature_txt_0;	
	Txt[1]=_AC_Temperature_txt_1;	
	Txt[2]=_AC_Temperature_txt_2;	
	Txt[3]=_AC_Temperature_txt_3;	
//	Txt[4]=_AC_Temperature_txt_4;	
//	Txt[5]=_AC_Temperature_txt_5;
	
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
	u8 i;
//	LCDTopPtr=&Scr_3;
	for(i=0;i<Scr_0.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);	
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
	u16 temp;
	u16 tmp0,tmp1;
	//**************************************************		
	if(m.fan.Temperature_2<3)
	{
		m.fan.Temperature_2=3;
		upc.data_status|=b_fancoil_new;
	}
	if(m.fan.Temperature_2>19)
	{
		m.fan.Temperature_2=19;	
		upc.data_status|=b_fancoil_new;
	}
	
	temp=175+m.fan.Temperature_2*5;
		
	LCDMenuPtr_Tmp_Txt=&Txt[0];			
	tmp0=temp/100;
	temp-=tmp0*100;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
				
	LCDMenuPtr_Tmp_Txt=&Txt[1];				
	tmp0=temp/10;
	temp-=tmp0*10;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[2];	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=12;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[3];
	tmp0=temp;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

//	LCDMenuPtr_Tmp_Txt=&Txt[4];	
//	old_stat=LCDMenuPtr_Tmp_Txt->Stat;			
//	LCDMenuPtr_Tmp_Txt->Stat=15;			
//	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	//**************************************************		
	switch(m.fan.Fan_Mode_2)
	{
		case 0:	
			if(Obj[0].Stat!=1)
			{
				Obj[0].Stat=1;
				show_single_bmp(&Obj[0],0);												
			}
			if(Obj[1].Stat!=0){Obj[1].Stat=0;show_single_bmp(&Obj[1],0);}
			if(Obj[2].Stat!=0){Obj[2].Stat=0;show_single_bmp(&Obj[2],0);}
			if(Obj[3].Stat!=0){Obj[3].Stat=0;show_single_bmp(&Obj[3],0);}
			if(Obj[4].Stat!=0){Obj[4].Stat=0;show_single_bmp(&Obj[4],0);}				
		break;
		case 1:	
			if(Obj[0].Stat!=0)
			{		
				Obj[0].Stat=0;
				show_single_bmp(&Obj[0],0);
			}	
			switch(m.fan.Fan_Lvl_2)
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
		break;
	}
}
//-----------------------------------------------------------------------------------
void Mod_Temperature_Up()
{
//	s16 Diff;
	m.fan.Temperature_2+=1;
	if(m.fan.Temperature_2>19)m.fan.Temperature_2=19;
	upc.data_status|=b_fancoil_new;
}
//-----------------------------------------------------------------------------------
void Mod_Temperature_Down()
{
//	s16 Diff;
	m.fan.Temperature_2-=1;
	if(m.fan.Temperature_2<3)m.fan.Temperature_2=3;	
	upc.data_status|=b_fancoil_new;
}
//-----------------------------------------------------------------------------------
void handle_fan_buttons_0()
{
//	s16	Diff;
	if(Obj[0].Stat==0)
		m.fan.Fan_Mode_2=1;
	else
		m.fan.Fan_Mode_2=0;		
	upc.data_status|=b_fancoil_new;
	scr3_routine();
}
//-----------------------------------------------------------------------------------
void handle_fan_buttons_1()
{
//	s16	Diff;
	m.fan.Fan_Lvl_2=0;
	m.fan.Fan_Mode_2=1;
	upc.data_status|=b_fancoil_new;
	scr3_routine();
}
//-----------------------------------------------------------------------------------
void handle_fan_buttons_2()
{
//	s16	Diff;
			m.fan.Fan_Lvl_2=1;	
			m.fan.Fan_Mode_2=1;	
	upc.data_status|=b_fancoil_new;
	scr3_routine();
}
//-----------------------------------------------------------------------------------
void handle_fan_buttons_3()
{
//	s16	Diff;
			m.fan.Fan_Lvl_2=2;
			m.fan.Fan_Mode_2=1;	
	upc.data_status|=b_fancoil_new;
	scr3_routine();
}
//-----------------------------------------------------------------------------------
void handle_fan_buttons_4()
{
//	s16	Diff;
	m.fan.Fan_Lvl_2=3;
	m.fan.Fan_Mode_2=1;	
	upc.data_status|=b_fancoil_new;
	scr3_routine();
}
//-----------------------------------------------------------------------------------
