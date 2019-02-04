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
u8 	pass_pos=0;
u8  pass_edit_mode=0;
u8  pass_enter_mode=1;
u8  pass_col=0;
u8  Password_State=0;
extern u8 custom_information_update;
TPassword Password_Buffer={0xff};
TPassword Password={1,2,3,4,5,6};
//-----------------------------------------------------------------------------------
void scr11_init();
void scr11_close();
void scr11_routine();
extern TLCDPictTop Scr_11;
//-----------------------------------------------------------------------------------
void Show_Pass(TPassword *Password,u8 *str)
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
//-----------------------------------------------------------------------------------
void Pass_New_Digit(u8 data)
{
	u8 str[2];
	if(pass_enter_mode==0)return;
	if(pass_col<PASS_SYMBOLS)
	{
		if((data>=0)&&(data<=9))
		{	
			Password_Buffer.Digit[pass_col]=data;
			str[1]=0;
			if(pass_edit_mode==1)
			{
				str[0]='0'+data;
				lcd_sprintf(str,5+pass_col,6);
			}
			else
			{
				str[0]='*';
				lcd_sprintf(str,5+pass_col,6);
			}
			pass_col++;
		}
	}
}
//-----------------------------------------------------------------------------------
void Pass_Digit_0()
{
	Pass_New_Digit(0);
}
//----------------------------
void Pass_Digit_1()
{
	Pass_New_Digit(1);
}
//----------------------------
void Pass_Digit_2()
{
	Pass_New_Digit(2);
}
//----------------------------
void Pass_Digit_3()
{
	Pass_New_Digit(3);
}
//----------------------------
void Pass_Digit_4()
{
	Pass_New_Digit(4);
}
//----------------------------
void Pass_Digit_5()
{
	Pass_New_Digit(5);
}
//----------------------------
void Pass_Digit_6()
{
	Pass_New_Digit(6);
}
//----------------------------
void Pass_Digit_7()
{
	Pass_New_Digit(7);
}
//----------------------------
void Pass_Digit_8()
{
	Pass_New_Digit(8);
}
//----------------------------
void Pass_Digit_9()
{
	Pass_New_Digit(9);
}
//----------------------------
void Pass_Digit_C()
{
	u8 str[2];
	if(pass_enter_mode==0)return;	
	if(pass_col!=0)pass_col--;
	Password_Buffer.Digit[pass_col]=0;
	str[0]=' ';
	str[1]=0;
	if(pass_edit_mode==1)	
		lcd_sprintf(str,5+pass_col,6);	
	else
		lcd_sprintf(str,5+pass_col,6);	
}
//----------------------------
void Pass_Digit_Ok()
{
	u8 i;
	pass_col=0;
	if(pass_edit_mode==0)
	{
		//char str[9];
		//for(i=0;i<8;i++)
		//	str[i] = Password.Digit[i]+'0';
		//str[8] = 0;
		//lcd_sprintf(str,5,9);
		for(i=0;i<8;i++)
			if(Password.Digit[i]!=Password_Buffer.Digit[i])
			{
				lcd_sprintf("Incorrect",5,8);	
				Password_State=0;			
				return;
			}
		lcd_sprintf("Correct ",5,8);	
		Password_State=1;
		Pass_Time=2;
		Time4=1000;
		Pass_Time_Expired=5;
	}
	else
	{
		for(i=0;i<8;i++)
			Password.Digit[i]=Password_Buffer.Digit[i];
		Password_State=1;
		pass_edit_mode=0;
		Pass_Time=2;
		Time4=1000;
		lcd_sprintf("Done",7,8);			
		custom_information_update=3;
		//upc_Set_Custom_Info();
	}
		
}
//----------------------------
void Pass_Butt_Edit()
{
	u8 i;
	if(Password_State==0)return;	
	pass_edit_mode=1;
	pass_col=0;	
	for(i=0;i<PASS_SYMBOLS;i++)
		Password_Buffer.Digit[i]=0xff;	
	lcd_clear_text();	
	lcd_sprintf("New  Password",2,4);			
}
//----------------------------
void Pass_Butt_Esc()
{
	pass_edit_mode=0;
	pass_enter_mode=0;
	pass_col=0;	
}
//-----------------------------------------------------------------------------------
#define Pict_Base 65
//--------------------------------------------
__farflash TLCDPict Pass_Button_Exit=
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
__farflash TLCDPict Pass_Button_0=
{	
	23,97,Pict_Base+0,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Pass_Digit_0,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict Pass_Button_1=
{	
	20,25,Pict_Base+1,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Pass_Digit_1,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict Pass_Button_2=
{	
	23,25,Pict_Base+2,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Pass_Digit_2,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict Pass_Button_3=
{	
	26,25,Pict_Base+3,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Pass_Digit_3,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict Pass_Button_4=
{	
	20,49,Pict_Base+4,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Pass_Digit_4,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict Pass_Button_5=
{	
	23,49,Pict_Base+5,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Pass_Digit_5,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict Pass_Button_6=
{	
	26,49,Pict_Base+6,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Pass_Digit_6,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict Pass_Button_7=
{	
	20,73,Pict_Base+7,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Pass_Digit_7,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict Pass_Button_8=
{	
	23,73,Pict_Base+8,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Pass_Digit_8,
	NULL,		
};
//--------------------------------------------
__farflash TLCDPict Pass_Button_9=
{	
	26,73,Pict_Base+9,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Pass_Digit_9,
	NULL,		
};
//--------------------------------------------
__farflash TLCDPict Pass_Button_C=
{	
	20,97,Pict_Base+10,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Pass_Digit_C,
	NULL,		
};
//--------------------------------------------
__farflash TLCDPict Pass_Button_E=
{	
	26,97,Pict_Base+11,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Pass_Digit_Ok,
	NULL,		
};
//--------------------------------------------
__farflash TLCDPict Pass_Button_Up=
{	
	17,25,0,
	(bit_visible+bit_active),
	0,
	0,
	0,
	NULL,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict Pass_Button_Down=
{	
	17,49,1,
	(bit_visible+bit_active),
	0,
	0,
	0,
	NULL,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict Pass_Button_Edit=
{	
	17,73,2,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Pass_Butt_Edit,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict Pass_Button_Esc=
{	
	17,97,3,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Pass_Butt_Esc,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict Pass_Button_0X=
{	
	0,0,Pict_Base+0,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Pass_Digit_0,
	NULL,		
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_11=
{
	0,0,0,
	0,
	17,
	5,	
	scr11_init,
	scr11_routine,
	scr11_close,		
};
//-----------------------------------------------------------------------------------
void scr11_init()
{
	u8 i;
	u8 str[10];
	Obj[0]=Pass_Button_0;
	Obj[1]=Pass_Button_1;
	Obj[2]=Pass_Button_2;
	Obj[3]=Pass_Button_3;
	Obj[4]=Pass_Button_4;
	Obj[5]=Pass_Button_5;
	Obj[6]=Pass_Button_6;
	Obj[7]=Pass_Button_7;
	Obj[8]=Pass_Button_8;	
	Obj[9]=Pass_Button_9;	
	Obj[10]=Pass_Button_C;	
	Obj[11]=Pass_Button_E;	
	Obj[12]=Pass_Button_Exit;			

	Obj[13]=Pass_Button_Up;	
	Obj[14]=Pass_Button_Down;	
	Obj[15]=Pass_Button_Edit;	
	Obj[16]=Pass_Button_Esc;	

	Obj[20]=_Null;	

	FT_Time=100;
	for(i=0;i<PASS_SYMBOLS;i++)
		Password_Buffer.Digit[i]=0xff;
	pass_pos=0;
	pass_col=0;
	pass_enter_mode=1;
	lcd_sprintf("Enter Password",2,4);	
//	Show_Pass(&Password_Buffer,str);
//	lcd_sprintf(str,2,6);
	
}
//-----------------------------------------------------------------------------------
void scr11_close()
{
	u8 i;
	for(i=0;i<Scr_0.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
	lcd_clear_text();
}
//-----------------------------------------------------------------------------------
void scr11_routine()
{
//	u8 tmp;	
//	u8 i;
	u8 str[32];

	if(pass_edit_mode==1)return;	
	if(FT_Time!=0)return;	
	if(page_offset!=PAGE_0_OFFSET)return;
	FT_Time=1000;
	if((Pass_Time==0)&&(Password_State==1)&&(pass_edit_mode==0))
	{
		push.status=1;
		Obj[12].SubItem=&Scr_4;
		push.LCDMenuPtr=&Obj[12];		
	}
//	Show_Pass(&Password_Buffer,str);
//	lcd_sprintf(str,2,6);
}
//-----------------------------------------------------------------------------------
