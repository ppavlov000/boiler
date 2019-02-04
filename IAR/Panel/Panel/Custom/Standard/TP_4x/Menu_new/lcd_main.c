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
void scr0_init();
void scr0_close();
void scr0_routine();
//-----------------------------------------------------------------------------------
u8 FAN_Number=1;
u8 FAN_Speed=0;
s16 Temperature[3]={0};
s16 Preset=0;
//-----------------------------------------------------------------------------------
/*
__farflash TLCDPict _Temperature_Exit=
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
__farflash TLCDPict _Temperature_Main=
{	
	0,44,17,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Temperature_Night=
{	
	25,44,74,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Temperature_Fan_1=
{	
	0,0,65,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	Choose_FAN_1,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Temperature_Fan_2=
{	
	5,0,66,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	Choose_FAN_2,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Temperature_Fan_3=
{	
	10,0,67,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	Choose_FAN_3,
	NULL,
};

//--------------------------------------------
__farflash TLCDPict _Temperature_Auto=
{	
	0,88,72,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Temperature_Speed=
{	
	10,88,69,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Choose_SPEED,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Temperature_Season=
{	
	20,88,73,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	NULL,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Temperature_Adjust=
{
	10,60,75,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,	
	NULL,
	&Scr_13,		
};
*/
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_5=
{
	20,60,53,
	(bit_visible+bit_txt_1),
	15,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_4=
{
	18,60,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_3=
{
	14,60,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_2=
{
	16,60,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_1=
{
	12,60,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_0=
{
	10,60,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Temperature_txt_Sign=
{
	10,60,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
//--------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_5=
{
	20,80,53,
	(bit_visible+bit_txt_1),
	15,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_4=
{
	18,80,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_3=
{
	14,80,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_2=
{
	16,80,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_1=
{
	12,80,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_0=
{
	10,80,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Preset_txt_Sign=
{
	10,80,53,
	(bit_visible+bit_txt_1),
	0,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_0=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	5,
	7,	
	scr0_init,
	scr0_routine,
	scr0_close,		
};
//-----------------------------------------------------------------------------------
void scr0_init()
{
	u8 i;
	Obj[0]=_Menu0;	
	Obj[1]=_Menu1;	
	Obj[2]=_Menu2;	
	Obj[3]=_Menu3;		
	Obj[4]=_Menu4;	

	Obj[0].Stat=1;
//	Obj[5]=_Temperature_Speed;	
//	Obj[6]=_Temperature_Season;		
//	Obj[7]=_Temperature_Night;		
//	Obj[8]=_Temperature_Adjust;		
	
	
	Txt[0]=_Temperature_txt_Sign;	
	Txt[1]=_Temperature_txt_0;	
	Txt[2]=_Temperature_txt_1;	
	Txt[3]=_Temperature_txt_2;	
	Txt[4]=_Temperature_txt_3;	
	Txt[5]=_Temperature_txt_4;	
	Txt[6]=_Temperature_txt_5;	

	Txt[0+7]=_Preset_txt_Sign;	
	Txt[1+7]=_Preset_txt_0;	
	Txt[2+7]=_Preset_txt_1;	
	Txt[3+7]=_Preset_txt_2;	
	Txt[4+7]=_Preset_txt_3;	
	Txt[5+7]=_Preset_txt_4;	
	Txt[6+7]=_Preset_txt_5;	
	
//	Txt[7]=Txt_0;	
//	Txt[8]=Txt_1;	
//	Txt[9]=Txt_2;	
//	Txt[10]=Txt_3;	
//	Txt[11]=Txt_4;	

	
//	Txt[12]=Date_0;	
//	Txt[13]=Date_1;	
//	Txt[14]=Date_2;	
//	Txt[15]=Date_3;	
//	Txt[16]=Date_4;	
	
	FT_Time=100;
	for(i=0;i<7;i++)
		Txt[i].Stat=10;
}
//-----------------------------------------------------------------------------------
void scr0_close()
{
	u8 i;
	for(i=0;i<Scr_0.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
}
//-----------------------------------------------------------------------------------
void scr0_routine()
{
	u8 tmp;		
	u16 temp;
	u8 tmp0;//,tmp1,tmp2; lc
	u8 old_stat;
	s16 temperature;
	if(FT_Time!=0)return;
	FT_Time=500;
	if(page_offset!=PAGE_0_OFFSET)return;
	//-----------------------------------------------	
	temperature=Temperature[2];	// Real output temperature
	
	if(temperature>500)temperature=0;
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
	//-----------------------------------------------	
	
	temperature=Preset;	// Preset temperature temperature
	
	if(temperature>500)temperature=0;
	LCDMenuPtr_Tmp_Txt=&Txt[0+7];
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
	
	
	LCDMenuPtr_Tmp_Txt=&Txt[1+7];					
	tmp0=temp/1000;
	temp-=tmp0*1000;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(tmp0==0)
		LCDMenuPtr_Tmp_Txt->Stat=16;
//	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
	
	LCDMenuPtr_Tmp_Txt=&Txt[2+7];			
	tmp0=temp/100;
	temp-=tmp0*100;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[3+7];	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=12;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
				
	LCDMenuPtr_Tmp_Txt=&Txt[4+7];				
	tmp0=temp/10;
	temp-=tmp0*10;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[5+7];
	tmp0=temp;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[6+7];	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;			
	LCDMenuPtr_Tmp_Txt->Stat=15;			
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	//-----------------------------------------------	
}
//-----------------------------------------------------------------------------------

