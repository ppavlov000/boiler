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
#define But_Main_Switch			Obj[20]
#define But_Do_Not_Disturb		Obj[20]
#define But_Makeup_Room			Obj[20]
#define But_Curtain_Open		Obj[20]
#define But_Curtain_Close		Obj[20]
#define Alarm_bell_obj			Obj[20]
//-----------------------------------------------------------------------------------
TLCDPictTop *Scr_Return;
TLCDPictTop *Scr_Enter;
//-----------------------------------------------------------------------------------
//#define ALARM_PASS_SYMBOLS	6
#define PASSWORD_IDLE_TIME 10
//-----------------------------------------------------------------------------------
//extern TPassword Password_Buffer;
//extern TPassword Password;
TPassword Password_Buffer={0};
TPassword Password={1,2,3,4,5,6};
//TPassword Password_test={1,2,3,4,5,6};
//u8  Password_State=0;
u8 Pass_Time_Expired=0;
u8	Password_OK=0;		// Return parameter
u8 	Password_Mode=0;
u8 	Password_Downcount=0;
u8 	Password_Time=0;
extern u8 custom_information_update;
//-----------------------------------------------------------------------------------
u8 	alarm_pass_pos=0;
u8  alarm_pass_edit_mode=0;
u8  alarm_pass_col=0;
u8  alarm_Password_State=0;
//u8 	alarm_pass_time = 0;
u8  old_alarm_state = 0;
//-----------------------------------------------------------------------------------
#define ALARM_KEYPAD_POS_X 		1
#define ALARM_KEYPAD_POS_Y 		32
#define ALARM_KEYPAD_WIDTH 		7
#define ALARM_KEYPAD_HEIGHT 	32
#define ALARM_PASS_POS_X 		9
#define ALARM_PASS_TEXT_POS_X 	10
#define ALARM_PASS_TEXT_POS_Y 	2
//-----------------------------------------------------------------------------------
void scr_alarm_pass_init();
void scr_alarm_pass_close();
void scr_alarm_pass_routine();
//-----------------------------------------------------------------------------------
/*
void Show_alarm_Pass(TPassword *Password,u8 *str)
{
	u8 i;
	for(i=0;i<PASS_SYMBOLS;i++)
	{
		*str=0;
		if(Password->Digit[i]!=0xff)*str='0'+Password->Digit[i];
		else *str='*';
		str++;
		*str=0;
	}
}
*/
//-----------------------------------------------------------------------------------
void alarm_Pass_New_Digit(u8 data)
{
//	u8 str[2];
	Password_Time=PASSWORD_IDLE_TIME;
	if(alarm_pass_col<PASS_SYMBOLS)
	{
		if(alarm_pass_col == 0)
		{
			lcd_sprintf("         ", ALARM_PASS_TEXT_POS_X, ALARM_PASS_TEXT_POS_Y);
			for (int i = 0; i < PASS_SYMBOLS; i++)
			{
				Txt[0].Stat = 16;
				Txt[0].x = ALARM_PASS_POS_X + i*2;
				show_single_bmp_txt(&Txt[0]);
			}
		}
		if((data>=0)&&(data<=9))
		{	
			Password_Buffer.Digit[alarm_pass_col]=data;
//			str[1]=0;
			{
				Txt[0].Stat = 18;
				Txt[0].x = ALARM_PASS_POS_X + alarm_pass_col*2;
				show_single_bmp_txt(&Txt[0]);
			}
			alarm_pass_col++;
		}
	}
}
//-----------------------------------------------------------------------------------
void alarm_Pass_Digit_0()
{
	alarm_Pass_New_Digit(0);
}
//----------------------------
void alarm_Pass_Digit_1()
{
	alarm_Pass_New_Digit(1);
}
//----------------------------
void alarm_Pass_Digit_2()
{
	alarm_Pass_New_Digit(2);
}
//----------------------------
void alarm_Pass_Digit_3()
{
	alarm_Pass_New_Digit(3);
}
//----------------------------
void alarm_Pass_Digit_4()
{
	alarm_Pass_New_Digit(4);
}
//----------------------------
void alarm_Pass_Digit_5()
{
	alarm_Pass_New_Digit(5);
}
//----------------------------
void alarm_Pass_Digit_6()
{
	alarm_Pass_New_Digit(6);
}
//----------------------------
void alarm_Pass_Digit_7()
{
	alarm_Pass_New_Digit(7);
}
//----------------------------
void alarm_Pass_Digit_8()
{
	alarm_Pass_New_Digit(8);
}
//----------------------------
void alarm_Pass_Digit_9()
{
	alarm_Pass_New_Digit(9);
}
//-----------------------------------------------------------------------------------
void alarm_Pass_Digit_C()
{
	Password_Time=PASSWORD_IDLE_TIME;
	if(alarm_pass_col == 0)
	{
		lcd_sprintf("         ", ALARM_PASS_TEXT_POS_X, ALARM_PASS_TEXT_POS_Y);
		for (int i = 0; i < PASS_SYMBOLS; i++)
		{
			Txt[0].Stat = 16;
			Txt[0].x = ALARM_PASS_POS_X + i*2;
			show_single_bmp_txt(&Txt[0]);
		}
	}
	if(alarm_pass_col!=0) alarm_pass_col--;
	Password_Buffer.Digit[alarm_pass_col]=0;
	{
		Txt[0].Stat = 16;
		Txt[0].x = ALARM_PASS_POS_X + alarm_pass_col*2;
		show_single_bmp_txt(&Txt[0]);
	}
}
//-----------------------------------------------------------------------------------
void alarm_Pass_Digit_Ok()
{
	u8 i;
	Password_Time=PASSWORD_IDLE_TIME;
	
	switch(Password_Mode)
	{
	case PM_NEW_PASSWORD:
		Password=Password_Buffer;
		custom_information_update=3;
		own_state.Password_Mode=PM_NONE;
		own_state.status |= bit_new_push;		
		break;
	default:
		alarm_pass_col=0;
		for(i=0;i<PASS_SYMBOLS;i++)
			if(Password.Digit[i]!=Password_Buffer.Digit[i])
			{
				lcd_sprintf("Incorrect", ALARM_PASS_TEXT_POS_X, ALARM_PASS_TEXT_POS_Y);	
				for (int i = 0; i < PASS_SYMBOLS; i++)
				{
					Txt[0].Stat = 16;
					Txt[0].x = ALARM_PASS_POS_X + i*2;
					show_single_bmp_txt(&Txt[0]);
				}
				//alarm_Password_State=0;		
				alarm_pass_pos=0;
				alarm_pass_col=0;
				Password_OK=0;		
				return;
			}
		// Correct password
		if (own_state.bst & Button_Alarm)
		{
			own_state.bst &= ~(Button_Alarm | Button_Thief_detected | ALARM_OUTPUTS);
			own_state.Password_Mode=PM_NONE;
			own_state.status |= bit_new_push;
		}		
		break;
	}	
	Pass_Time_Expired=60;
	Password_OK=1;
//	Password_State=1;
	LCDTopPtr->Exit();
	LCDTopPtr=Scr_Enter;
	LCDTopPtr->Init();
	repaint_page();
}
//-----------------------------------------------------------------------------------
#define Pict_Base 86
//--------------------------------------------
__farflash TLCDPict alarm_Pass_Button_0=
{	
	ALARM_KEYPAD_POS_X + ALARM_KEYPAD_WIDTH*2,ALARM_KEYPAD_POS_Y + ALARM_KEYPAD_HEIGHT*2,Pict_Base+0,
	(bit_visible+bit_active),
	0,
	0,
	0,
	alarm_Pass_Digit_0,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict alarm_Pass_Button_1=
{	
	ALARM_KEYPAD_POS_X + ALARM_KEYPAD_WIDTH*0, ALARM_KEYPAD_POS_Y + ALARM_KEYPAD_HEIGHT*0,Pict_Base+1,
	(bit_visible+bit_active),
	0,
	0,
	0,
	alarm_Pass_Digit_1,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict alarm_Pass_Button_2=
{	
	ALARM_KEYPAD_POS_X + ALARM_KEYPAD_WIDTH*1, ALARM_KEYPAD_POS_Y + ALARM_KEYPAD_HEIGHT*0,Pict_Base+2,
	(bit_visible+bit_active),
	0,
	0,
	0,
	alarm_Pass_Digit_2,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict alarm_Pass_Button_3=
{	
	ALARM_KEYPAD_POS_X + ALARM_KEYPAD_WIDTH*2, ALARM_KEYPAD_POS_Y + ALARM_KEYPAD_HEIGHT*0,Pict_Base+3,
	(bit_visible+bit_active),
	0,
	0,
	0,
	alarm_Pass_Digit_3,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict alarm_Pass_Button_4=
{	
	ALARM_KEYPAD_POS_X + ALARM_KEYPAD_WIDTH*3, ALARM_KEYPAD_POS_Y + ALARM_KEYPAD_HEIGHT*0,Pict_Base+4,
	(bit_visible+bit_active),
	0,
	0,
	0,
	alarm_Pass_Digit_4,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict alarm_Pass_Button_5=
{	
	ALARM_KEYPAD_POS_X + ALARM_KEYPAD_WIDTH*0, ALARM_KEYPAD_POS_Y + ALARM_KEYPAD_HEIGHT*1,Pict_Base+5,
	(bit_visible+bit_active),
	0,
	0,
	0,
	alarm_Pass_Digit_5,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict alarm_Pass_Button_6=
{	
	ALARM_KEYPAD_POS_X + ALARM_KEYPAD_WIDTH*1, ALARM_KEYPAD_POS_Y + ALARM_KEYPAD_HEIGHT*1,Pict_Base+6,
	(bit_visible+bit_active),
	0,
	0,
	0,
	alarm_Pass_Digit_6,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict alarm_Pass_Button_7=
{	
	ALARM_KEYPAD_POS_X + ALARM_KEYPAD_WIDTH*2, ALARM_KEYPAD_POS_Y + ALARM_KEYPAD_HEIGHT*1,Pict_Base+7,
	(bit_visible+bit_active),
	0,
	0,
	0,
	alarm_Pass_Digit_7,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict alarm_Pass_Button_8=
{	
	ALARM_KEYPAD_POS_X + ALARM_KEYPAD_WIDTH*3, ALARM_KEYPAD_POS_Y + ALARM_KEYPAD_HEIGHT*1,Pict_Base+8,
	(bit_visible+bit_active),
	0,
	0,
	0,
	alarm_Pass_Digit_8,
	NULL,		
};
//--------------------------------------------
__farflash TLCDPict alarm_Pass_Button_9=
{	
	ALARM_KEYPAD_POS_X + ALARM_KEYPAD_WIDTH*1, ALARM_KEYPAD_POS_Y + ALARM_KEYPAD_HEIGHT*2,Pict_Base+9,
	(bit_visible+bit_active),
	0,
	0,
	0,
	alarm_Pass_Digit_9,
	NULL,		
};
//--------------------------------------------
__farflash TLCDPict alarm_Pass_Button_C=
{	
	ALARM_KEYPAD_POS_X + ALARM_KEYPAD_WIDTH*0, ALARM_KEYPAD_POS_Y + ALARM_KEYPAD_HEIGHT*2,Pict_Base+11,
	(bit_visible+bit_active),
	0,
	0,
	0,
	alarm_Pass_Digit_C,
	NULL,		
};
//--------------------------------------------
__farflash TLCDPict alarm_Pass_Button_E=
{	
	ALARM_KEYPAD_POS_X + ALARM_KEYPAD_WIDTH*3, ALARM_KEYPAD_POS_Y + ALARM_KEYPAD_HEIGHT*2,Pict_Base+10,
	(bit_visible+bit_active),
	0,
	0,
	0,
	alarm_Pass_Digit_Ok,
	NULL,		
};

//--------------------------------------------
__farflash TLCDPict_Txt _Txt_asterix=
{
	ALARM_PASS_POS_X,9,53,
	(bit_visible+bit_txt_1),
	18,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_Password=
{
	0,0,0,
	0,
	12,
	1,	
	scr_alarm_pass_init,
	scr_alarm_pass_routine,
	scr_alarm_pass_close,		
};

//-----------------------------------------------------------------------------------
void scr_alarm_pass_init()
{
	u8 i;
//	u8 str[10];
	Obj[0]=alarm_Pass_Button_0;
	Obj[1]=alarm_Pass_Button_1;
	Obj[2]=alarm_Pass_Button_2;
	Obj[3]=alarm_Pass_Button_3;
	Obj[4]=alarm_Pass_Button_4;
	Obj[5]=alarm_Pass_Button_5;
	Obj[6]=alarm_Pass_Button_6;
	Obj[7]=alarm_Pass_Button_7;
	Obj[8]=alarm_Pass_Button_8;	
	Obj[9]=alarm_Pass_Button_9;	
	Obj[10]=alarm_Pass_Button_C;	
	Obj[11]=alarm_Pass_Button_E;	
	Txt[0]=_Txt_asterix;
	for (int i = 0; i < PASS_SYMBOLS; i++)
	{
		Txt[0].Stat = 16;
		Txt[0].x = ALARM_PASS_POS_X + i*2;
		show_single_bmp_txt(&Txt[0]);
	}
	old_alarm_state = 0;
	Obj[20]=_Null;

	
	FT_Time=200;
	for(i=0;i<PASS_SYMBOLS;i++)
		Password_Buffer.Digit[i]=0;
	alarm_pass_pos=0;
	alarm_pass_col=0;
	Password_OK=0;
	Password_Time=PASSWORD_IDLE_TIME;
}
//-----------------------------------------------------------------------------------
void scr_alarm_pass_close()
{
	for (int i = 0; i < PASS_SYMBOLS; i++)
	{
		Txt[0].Stat = 16;
		Txt[0].x = ALARM_PASS_POS_X + i*2;
		show_single_bmp_txt(&Txt[0]);
	}
	u8 i;
	for(i=0;i<Scr_0.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
	lcd_clear_text();
}

//-----------------------------------------------------------------------------------
void scr_alarm_pass_routine()
{
//	u8 tmp;	
//	u8 i;
//	u8 old_pass_time = 0;
	u8 tmp_num;
	u8 str[3];

	switch(Password_Mode)
	{
	case PM_NONE:
		if((Password_Time==0))
		{
			LCDTopPtr->Exit();
			LCDTopPtr=Scr_Return;
			LCDTopPtr->Init();
			repaint_page();
		}		
		break;
	case PM_NEW_PASSWORD:
		if(FT_Time==0){
			lcd_sprintf("   Enter NEW Password    ",3,0);	
		};
		break;
	case PM_ACTIVATION_COUNTDOWN:
		if(FT_Time==0){
			tmp_num = Password_Downcount / 10;
			str[0] = (tmp_num)?(tmp_num + '0'):' ';
			str[1] = Password_Downcount - tmp_num*10 + '0';
			str[2] = 0;
			lcd_sprintf("Time to activation    sec",3,0);			
			lcd_sprintf(str,22,0);			
//			if(Password_Downcount==0) {
//				Password_Mode=PM_ARMED;
//				lcd_sprintf("   Alarm system active     ",3,0);	
//				lcd_sprintf("                           ",3,1);
				// Send to main ALARM status
//				own_state.Password_Mode=Password_Mode;
//				own_state.bst |= (Button_Alarm);
//				own_state.status |= bit_new_push;
//			}
		}
		break;
	case PM_ALARM_COUNTDOWN:
		if(FT_Time==0){
			tmp_num = Password_Downcount / 10;
			str[0] = (tmp_num)?(tmp_num + '0'):' ';
			str[1] = Password_Downcount - tmp_num*10 + '0';
			str[2] = 0;
			lcd_sprintf("Remaining time        sec",3,0);			
			lcd_sprintf(str,22,0);					
//			if(Password_Downcount==0) {
//				Password_Mode=PM_ALARM;
//				lcd_sprintf("   Alarm! Alarm! Alarm!    ",3,0);	
//				lcd_sprintf("                           ",3,1);			
//				own_state.bst |= (ALARM_OUTPUTS);
//				own_state.Password_Mode=Password_Mode;			
//				own_state.status |= bit_new_push;				
//			}
		}
		break;	
	case PM_ARMED:
		if(FT_Time==0){
				lcd_sprintf("   Alarm system active     ",3,0);	
				lcd_sprintf("                           ",3,1);
		};
//		own_state.Password_Downcount=30;
		break;
	case PM_ALARM:		
		if(FT_Time==0){
				lcd_sprintf("   Alarm! Alarm! Alarm!    ",3,0);	
				lcd_sprintf("                           ",3,1);			
		}
		break;		
	};
//	if(alarm_pass_edit_mode==1)return;	
	if(FT_Time!=0)return;	
	if(page_offset!=PAGE_0_OFFSET)return;
	FT_Time=1000;
/*	if((Password_Time==0))
	{
		LCDTopPtr->Exit();
		LCDTopPtr=&Scr_Return;
		LCDTopPtr->Init();
		repaint_page();
	}
*/	
}
//-----------------------------------------------------------------------------------
