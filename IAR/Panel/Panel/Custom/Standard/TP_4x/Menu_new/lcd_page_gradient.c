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
extern __farflash TLCDPict _Menu0;
extern __farflash TLCDPict _Menu1;
extern __farflash TLCDPict _Menu2;
extern __farflash TLCDPict _Menu3;
extern __farflash TLCDPict _Menu4;
//-----------------------------------------------------------------------------------
//extern TLCDPictTop Scr_0;
extern TLCDPictTop Scr_13;
extern __farflash TLCDPict_Txt _Txt_0;
extern __farflash TLCDPict_Txt _Txt_1;
extern __farflash TLCDPict_Txt _Txt_2;
extern __farflash TLCDPict_Txt _Txt_3;
extern __farflash TLCDPict_Txt _Txt_4;
//-----------------------------------------------------------------------------------
void scr13_init();
void scr13_close();
void scr13_routine();
extern u8 str[40];
extern u8 Common_ID_Mode;
extern u8 Current_ID;
extern u8 Branch_Number;
extern  u16 Store_Time;
//-----------------------------------------------------------------------------------
void Gradient_Plus()
{
	m.gradient_temperature=m.gradient_temperature+1;
	if(m.gradient_temperature>=200)m.gradient_temperature=200;	
	FT_Time=0;	
}
//-----------------------------------------------------------------------------------
void Gradient_Minus()
{
	m.gradient_temperature=m.gradient_temperature-1;
	if(m.gradient_temperature<0)m.gradient_temperature=0;	
	FT_Time=0;
}
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Gradient_Plus=
{
	5,48,89,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Gradient_Plus,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Gradient_Minus=
{
	22,48,88,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Gradient_Minus,
	NULL,
};
//--------------------------------------------
//--------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _Gradient_txt_5=
{
	21,59,53,
	(bit_visible+bit_txt_1),
	15,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Gradient_txt_4=
{
	19,59,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Gradient_txt_3=
{
	17,59,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Gradient_txt_2=
{
	15,59,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Gradient_txt_1=
{
	13,59,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Gradient_txt_0=
{
	11,59,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Gradient_txt_Sign=
{
	9,59,53,
	(bit_visible+bit_txt_1),
	0,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_13=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	7,
	7,	
	scr13_init,
	scr13_routine,
	scr13_close,		
};

//-----------------------------------------------------------------------------------
void scr13_init()
{
	u8 i;
	Switch_To_Main_Time=60;
	Obj[0]=_Menu0;	
	Obj[1]=_Menu1;	
	Obj[2]=_Menu2;	
	Obj[3]=_Menu3;		
	Obj[4]=_Menu4;	
	
	Obj[5]=_Gradient_Plus;		
	Obj[6]=_Gradient_Minus;
	
	
	Txt[0]=_Gradient_txt_Sign;	
	Txt[1]=_Gradient_txt_0;	
	Txt[2]=_Gradient_txt_1;	
	Txt[3]=_Gradient_txt_2;	
	Txt[4]=_Gradient_txt_3;	
	Txt[5]=_Gradient_txt_4;	
	Txt[6]=_Gradient_txt_5;	
	
	FT_Time=100;
	for(i=0;i<Scr_13.Txt_Num;i++)
		Txt[i].Stat=11;
	
}
//-----------------------------------------------------------------------------------
void scr13_close()
{
	u8 i;
	for(i=0;i<Scr_13.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
	lcd_clear_text();
	Store_Time=100;	
}
//-----------------------------------------------------------------------------------
void scr13_routine()
{
	u16 temp;
	u8 tmp0;//,tmp1,tmp2; lc
	u8 old_stat;
	s16 temperature;
	if(FT_Time!=0)return;
	FT_Time=500;
	if(page_offset!=PAGE_0_OFFSET)return;
	Switch_To_Main_Time=60;	
	//-----------------------------------------------		
	if(Common_ID_Mode==0){
		// Real temperature
		temperature=m.gradient_temperature;	// Real output temperature
		LCDMenuPtr_Tmp_Txt=&Txt[0];
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;		
		if(temperature<0)
		{
			LCDMenuPtr_Tmp_Txt->Stat=10;
			temp=-temperature;
		}
		else
		{
			LCDMenuPtr_Tmp_Txt->Stat=11;	
			temp=temperature;		
		}
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		
		LCDMenuPtr_Tmp_Txt=&Txt[1];			
		tmp0=temp/100;
		temp-=tmp0*100;	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[3];	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=12;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
					
		LCDMenuPtr_Tmp_Txt=&Txt[2];				
		tmp0=temp/10;
		temp-=tmp0*10;	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[4];
		tmp0=temp;
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[5];	
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;			
		LCDMenuPtr_Tmp_Txt->Stat=15;			
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	}
}
//-----------------------------------------------------------------------------------

