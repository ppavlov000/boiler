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
u8 pos=0;
u8 edit_mode=0;
u8 col=0;
extern u8 custom_information_update;

TPhoneRecord PhoneList[5]=
{
	{'+',3,8,0,4,4,5,2,8,2,9,0,1,0xff,0xff,0xff},
	{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
	{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
	{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
	{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
};
TPhoneRecord Phone_Buffer;
//-----------------------------------------------------------------------------------
void scr10_init();
void scr10_close();
void scr10_routine();
void update_page();
extern TLCDPictTop Scr_10;
void update_page_00();
//-----------------------------------------------------------------------------------
void Show_Number(TPhoneRecord *Record,u8 *str)
{
	u8 i;
	for(i=0;i<16;i++)
	{
		*str=0;
		if(Record->Digit[i]!=0xff)*str='0'+Record->Digit[i];
		else break;
		if(Record->Digit[i]=='+')*str='+';
		str++;
		*str=0;
	}
}
//-----------------------------------------------------------------------------------
void New_Digit(u8 data)
{
	u8 str[2];
	if(edit_mode==0)return;
	if(col<15)
	{
		if((data>=0)&&(data<=9))
		{	
			Phone_Buffer.Digit[col]=data;
			str[0]='0'+data;
			str[1]=0;
			lcd_sprintf(str,3+col,6+pos);
			col++;
		}
	}
}
//-----------------------------------------------------------------------------------
void Print_Carret()
{
	lcd_sprintf(" 1)",0,6);		
	lcd_sprintf(" 2)",0,7);		
	lcd_sprintf(" 3)",0,8);		
	lcd_sprintf(" 4)",0,9);		
	lcd_sprintf(" 5)",0,10);
	lcd_sprintf(">",0,6+pos);
}
//-----------------------------------------------------------------------------------
void Digit_0()
{
	New_Digit(0);
}
//----------------------------
void Digit_1()
{
	New_Digit(1);
}
//----------------------------
void Digit_2()
{
	New_Digit(2);
}
//----------------------------
void Digit_3()
{
	New_Digit(3);
}
//----------------------------
void Digit_4()
{
	New_Digit(4);
}
//----------------------------
void Digit_5()
{
	New_Digit(5);
}
//----------------------------
void Digit_6()
{
	New_Digit(6);
}
//----------------------------
void Digit_7()
{
	New_Digit(7);
}
//----------------------------
void Digit_8()
{
	New_Digit(8);
}
//----------------------------
void Digit_9()
{
	New_Digit(9);
}
//----------------------------
void Digit_C()
{
	u8 str[2];
	if(edit_mode==0)return;
	if(col!=0)col--;
	Phone_Buffer.Digit[col]=0xff;
	str[0]=' ';
	str[1]=0;
	lcd_sprintf(str,3+col,6+pos);	
}
//----------------------------
void Digit_E()
{
	edit_mode=0;
	col=0;
	PhoneList[pos]=Phone_Buffer;
	custom_information_update=3;
}
//----------------------------
void Butt_Up()
{
	if(edit_mode==1)return;
	if(pos>0)pos--;	
	FT_Time=0;
	Print_Carret();
}
//----------------------------
void Butt_Down()
{
	if(edit_mode==1)return;	
	pos++;
	if(pos>4)pos=4;	
	FT_Time=0;
	Print_Carret();
}
//----------------------------
void Butt_Edit()
{
	u8 i;
	edit_mode=1;
	col=0;	
	lcd_sprintf("                ",3,6+pos);	
	for(i=0;i<16;i++)
		Phone_Buffer.Digit[i]=0xff;
	
}
//----------------------------
void Butt_Esc()
{
	edit_mode=0;
	col=0;	
}
//-----------------------------------------------------------------------------------
#define Pict_Base 65
//--------------------------------------------
__farflash TLCDPict _Button_Exit=
{
	// Exit
	27,0,21,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,	
	0,	
	NULL,
	&Scr_4,		
};
//--------------------------------------------
__farflash TLCDPict _Button_0=
{	
	23,97,Pict_Base+0,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Digit_0,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Button_1=
{	
	20,25,Pict_Base+1,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Digit_1,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Button_2=
{	
	23,25,Pict_Base+2,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Digit_2,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Button_3=
{	
	26,25,Pict_Base+3,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Digit_3,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Button_4=
{	
	20,49,Pict_Base+4,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Digit_4,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Button_5=
{	
	23,49,Pict_Base+5,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Digit_5,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Button_6=
{	
	26,49,Pict_Base+6,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Digit_6,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Button_7=
{	
	20,73,Pict_Base+7,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Digit_7,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Button_8=
{	
	23,73,Pict_Base+8,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Digit_8,
	NULL,		
};
//--------------------------------------------
__farflash TLCDPict _Button_9=
{	
	26,73,Pict_Base+9,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Digit_9,
	NULL,		
};
//--------------------------------------------
__farflash TLCDPict _Button_C=
{	
	20,97,Pict_Base+10,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Digit_C,
	NULL,		
};
//--------------------------------------------
__farflash TLCDPict _Button_E=
{	
	26,97,Pict_Base+11,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Digit_E,
	NULL,		
};
//--------------------------------------------
__farflash TLCDPict _Button_Up=
{	
	17,25,0,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Butt_Up,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Button_Down=
{	
	17,49,1,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Butt_Down,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Button_Edit=
{	
	17,73,2,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Butt_Edit,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Button_Esc=
{	
	17,97,3,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Butt_Esc,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Button_0X=
{	
	0,0,Pict_Base+0,
	(bit_visible+bit_active),
	0,
	0,
	0,
	Digit_0,
	NULL,		
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_10=
{
	0,0,0,
	0,
	17,
	5,	
	scr10_init,
	scr10_routine,
	scr10_close,		
};
//-----------------------------------------------------------------------------------
void scr10_init()
{
	Obj[0]=_Button_0;
	Obj[1]=_Button_1;
	Obj[2]=_Button_2;
	Obj[3]=_Button_3;
	Obj[4]=_Button_4;
	Obj[5]=_Button_5;
	Obj[6]=_Button_6;
	Obj[7]=_Button_7;
	Obj[8]=_Button_8;	
	Obj[9]=_Button_9;	
	Obj[10]=_Button_C;	
	Obj[11]=_Button_E;	
	Obj[12]=_Button_Exit;			

	Obj[13]=_Button_Up;	
	Obj[14]=_Button_Down;	
	Obj[15]=_Button_Edit;	
	Obj[16]=_Button_Esc;	
	
	Obj[20]=_Null;	

	FT_Time=100;
	pos=0;
	lcd_sprintf("  Phone numbers",0,4);	
	Print_Carret();		
}
//-----------------------------------------------------------------------------------
void scr10_close()
{
	u8 i;
	for(i=0;i<Scr_0.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
	lcd_clear_text();
}
//-----------------------------------------------------------------------------------
void scr10_routine()
{
	u8 tmp;	
	u8 i;
	u8 str[32];

	if(edit_mode==1)return;	
	if(FT_Time!=0)return;	
	if(page_offset!=PAGE_0_OFFSET)return;
	FT_Time=1000;
	for(i=0;i<5;i++)
	{
		Show_Number(&PhoneList[i],str);
		lcd_sprintf(str,3,6+i);
	}
}
//-----------------------------------------------------------------------------------
