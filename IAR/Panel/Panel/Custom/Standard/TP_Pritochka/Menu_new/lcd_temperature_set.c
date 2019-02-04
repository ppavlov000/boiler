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
extern TLCDPictTop Scr_0;
extern __farflash TLCDPict_Txt _Txt_0;
extern __farflash TLCDPict_Txt _Txt_1;
extern __farflash TLCDPict_Txt _Txt_2;
extern __farflash TLCDPict_Txt _Txt_3;
extern __farflash TLCDPict_Txt _Txt_4;
//-----------------------------------------------------------------------------------
void scr13_init();
void scr13_close();
void scr13_routine();
//-----------------------------------------------------------------------------------
s16 FAN_Temperature=220;
void FAN_Temperature_Plus()
{
	FAN_Temperature+=1;
	if(FAN_Temperature>300)FAN_Temperature=300;
	FT_Time=0;
}
void FAN_Temperature_Minus()
{
	FAN_Temperature-=1;
	if(FAN_Temperature<180)FAN_Temperature=180;
	FT_Time=0;
}
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Temperature_Set_Exit=
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
__farflash TLCDPict _Temperature_Set_Minus=
{	
	2,52,26,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	FAN_Temperature_Minus,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Temperature_Set_Plus=
{	
	25,52,28,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	FAN_Temperature_Plus,
	NULL,
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
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_Set_txt_5=
{
	20,60,53,
	(bit_visible+bit_txt_1),
	15,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_Set_txt_4=
{
	18,60,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_Set_txt_3=
{
	14,60,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_Set_txt_2=
{
	16,60,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_Set_txt_1=
{
	12,60,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_Set_txt_0=
{
	10,60,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_Set_txt_Sign=
{
	10,60,53,
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
	3,
	7,	
	scr13_init,
	scr13_routine,
	scr13_close,		
};
//-----------------------------------------------------------------------------------
void scr13_init()
{
	u8 i;
	Obj[0]=_Temperature_Set_Exit;	
	Obj[1]=_Temperature_Set_Plus;	
	Obj[2]=_Temperature_Set_Minus;		
	
	
	Txt[0]=_Temperature_Set_txt_Sign;	
	Txt[1]=_Temperature_Set_txt_0;	
	Txt[2]=_Temperature_Set_txt_1;	
	Txt[3]=_Temperature_Set_txt_2;	
	Txt[4]=_Temperature_Set_txt_3;	
	Txt[5]=_Temperature_Set_txt_4;	
	Txt[6]=_Temperature_Set_txt_5;	
	
	FT_Time=100;
	for(i=0;i<7;i++)
		Txt[i].Stat=10;
}
//-----------------------------------------------------------------------------------
void scr13_close()
{
	u8 i;
	for(i=0;i<Scr_13.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
}
//-----------------------------------------------------------------------------------
void scr13_routine()
{
	u8 tmp;		
	u16 temp;
	u8 tmp0;//,tmp1,tmp2; lc
	u8 old_stat;
	s16 temperature;
	if(FT_Time!=0)return;
	FT_Time=500;
//	if(page_offset!=PAGE_0_OFFSET)return;
	//-----------------------------------------------	
	temperature=FAN_Temperature;
	if(temperature>600)temperature=0;
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
	tmp0=temp/1000;
	temp-=tmp0*1000;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(tmp0==0)
		LCDMenuPtr_Tmp_Txt->Stat=16;
//	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
	
	LCDMenuPtr_Tmp_Txt=&Txt[2];			
	tmp0=temp/100;
	temp-=tmp0*100;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[3];	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=12;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
				
	LCDMenuPtr_Tmp_Txt=&Txt[4];				
	tmp0=temp/10;
	temp-=tmp0*10;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[5];
	tmp0=temp;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[6];	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;			
	LCDMenuPtr_Tmp_Txt->Stat=15;			
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);	
}
//-----------------------------------------------------------------------------------

