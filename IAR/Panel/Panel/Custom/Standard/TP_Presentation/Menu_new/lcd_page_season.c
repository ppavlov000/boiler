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
extern TLCDPictTop Scr_4;
extern __farflash TLCDPict_Txt _Txt_0;
extern __farflash TLCDPict_Txt _Txt_1;
extern __farflash TLCDPict_Txt _Txt_2;
extern __farflash TLCDPict_Txt _Txt_3;
extern __farflash TLCDPict_Txt _Txt_4;
extern u8 Branch_Number;
extern u8 step;
extern u8 new_step;
extern u8 Current_ID;
u8 scr12_edit_pos=0;
u8 scr12_blink=0;
extern s16 Temperature[3];
//-----------------------------------------------------------------------------------
#define Obj_scr12_Season 		Obj[5]
#define Obj_scr12_Auto_Manual 	Obj[6]
#define Obj_scr12_Temperature	Obj[11]
#define Obj_scr12_Date	 		Obj[12]
//-----------------------------------------------------------------------------------
//TSeason Season;
//-----------------------------------------------------------------------------------
void scr12_init();
void scr12_close();
void scr12_routine();
//-----------------------------------------------------------------------------------
void scr12_plus()
{
	FT_Time=0;
	switch(scr12_edit_pos)
	{
	case 1:	if(reg_season.t<400)reg_season.t++;break;
	case 2:	if(reg_season.date[0].field.Date<31)reg_season.date[0].field.Date++;break;
	case 3:	if(reg_season.date[0].field.Month<12)reg_season.date[0].field.Month++;break;
	case 4:	if(reg_season.date[1].field.Date<31)reg_season.date[1].field.Date++;break;
	case 5:	if(reg_season.date[1].field.Month<12)reg_season.date[1].field.Month++;break;
	}
	new_step=2;	
	Button_no_update_time=1000;
	scr12_blink=1;
}
//-----------------------------------------------------------------------------------
void scr12_minus()
{
	FT_Time=0;
	switch(scr12_edit_pos)
	{
	case 1:	if(reg_season.t>-400)reg_season.t--;break;
	case 2:	if(reg_season.date[0].field.Date>1)reg_season.date[0].field.Date--;break;
	case 3:	if(reg_season.date[0].field.Month>1)reg_season.date[0].field.Month--;break;
	case 4:	if(reg_season.date[1].field.Date>1)reg_season.date[1].field.Date--;break;
	case 5:	if(reg_season.date[1].field.Month>1)reg_season.date[1].field.Month--;break;
	}
	new_step=2;	
	Button_no_update_time=1000;
	scr12_blink=1;
}
//-----------------------------------------------------------------------------------
void scr12_up()
{
	FT_Time=0;
}
//-----------------------------------------------------------------------------------
void scr12_down()
{
	FT_Time=0;
}
//-----------------------------------------------------------------------------------
void scr12_update_season_buttons()
{
	// Season auto / manual
	if(reg_season.mode==0)
	{
		if(Obj_scr12_Auto_Manual.Stat!=0){Obj_scr12_Auto_Manual.Stat=0;show_single_bmp(&Obj_scr12_Auto_Manual,0);}
	}
	else
	{
		if(Obj_scr12_Auto_Manual.Stat!=1){Obj_scr12_Auto_Manual.Stat=1;show_single_bmp(&Obj_scr12_Auto_Manual,0);}
	}
	// Season itself
	if(reg_season.season==1)
	{
		if(Obj_scr12_Season.Stat!=0){Obj_scr12_Season.Stat=0;show_single_bmp(&Obj_scr12_Season,0);}
	}
	else
	{
		if(Obj_scr12_Season.Stat!=1){Obj_scr12_Season.Stat=1;show_single_bmp(&Obj_scr12_Season,0);}
	}
	// Temperature switch
	if(reg_season.switch_temperature==1)
	{
		if(Obj_scr12_Temperature.Stat!=0){Obj_scr12_Temperature.Stat=0;show_single_bmp(&Obj_scr12_Temperature,0);}
	}
	else
	{
		if(Obj_scr12_Temperature.Stat!=1){Obj_scr12_Temperature.Stat=1;show_single_bmp(&Obj_scr12_Temperature,0);}
	}
	// Date switch
	if(reg_season.switch_date==1)
	{
		if(Obj_scr12_Date.Stat!=0){Obj_scr12_Date.Stat=0;show_single_bmp(&Obj_scr12_Date,0);}
	}
	else
	{
		if(Obj_scr12_Date.Stat!=1){Obj_scr12_Date.Stat=1;show_single_bmp(&Obj_scr12_Date,0);}
	}
}
//-----------------------------------------------------------------------------------
void scr12_season()
{
	reg_season.mode=SEASON_MANUAL; // Manual
	if(reg_season.season==SEASON_SUMMER)reg_season.season=SEASON_WINTER;
	else reg_season.season=SEASON_SUMMER;
	scr12_update_season_buttons();
	new_step=2;
	Button_no_update_time=500;
}
//-----------------------------------------------------------------------------------
void scr12_auto_manual()
{
	if(reg_season.mode==SEASON_MANUAL)reg_season.mode=SEASON_AUTO;
	else reg_season.mode=SEASON_MANUAL;
	scr12_update_season_buttons();	
	new_step=2;	
	Button_no_update_time=500;
}
//-----------------------------------------------------------------------------------
void scr12_switch_temperature()
{
	reg_season.switch_date=0;
	if(reg_season.switch_temperature)reg_season.switch_temperature=0;
	else reg_season.switch_temperature=1;
	scr12_update_season_buttons();
	new_step=2;
	Button_no_update_time=500;
}
//-----------------------------------------------------------------------------------
void scr12_switch_date()
{
	reg_season.switch_temperature=0;
	if(reg_season.switch_date)reg_season.switch_date=0;
	else reg_season.switch_date=1;
	scr12_update_season_buttons();	
	new_step=2;	
	Button_no_update_time=500;
}
//-----------------------------------------------------------------------------------
void scr12_set_pos_0()
{
	scr12_edit_pos=1;
}
//-----------------------------------------------------------------------------------
void scr12_set_pos_1()
{
	scr12_edit_pos=2;
}
//-----------------------------------------------------------------------------------
void scr12_set_pos_2()
{
	scr12_edit_pos=3;
}
//-----------------------------------------------------------------------------------
void scr12_set_pos_3()
{
	scr12_edit_pos=4;
}
//-----------------------------------------------------------------------------------
void scr12_set_pos_4()
{
	scr12_edit_pos=5;
}
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_12_Up=
{	
	25,56,42,
//	(bit_visible+bit_active),
	0,
	0,
	0,
	0,	
	scr12_up,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_12_Down=
{	
	25,76,43,
//	(bit_visible+bit_active),
	0,
	0,
	0,
	0,	
	scr12_down,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_12_Plus=
{	
	25,56,44,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	scr12_plus,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_12_Minus=
{	
	25,76,45,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	scr12_minus,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_12_Season=
{
	0,16,73,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr12_season,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_12_Auto_Manual=
{
	11,16,46,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr12_auto_manual,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_12_Temperature=
{
	0,40,74,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr12_switch_temperature,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_12_Date=
{
	0,60,75,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr12_switch_date,
	NULL,
};
//--------------------------------------------
//--------------------------------------------
//--------------------------------------------
__farflash TLCDPict _scr12_Temp_blank=
{	
	10,40,58,
	(bit_visible+bit_active+bit_static),
	0,	
	0,
	0,
//	Set_Int_State_5,
	scr12_set_pos_0,
	NULL,
};
__farflash TLCDPict _scr12_D00_blank=
{	
	0,80,57,
	(bit_visible+bit_active+bit_static),
	0,	
	0,
	0,
//	Set_Int_State_5,
	scr12_set_pos_1,
	NULL,
};
__farflash TLCDPict _scr12_D01_blank=
{	
	6,80,57,
	(bit_visible+bit_active+bit_static),
	0,	
	0,
	0,
//	Set_Int_State_5,
	scr12_set_pos_2,
	NULL,
};
__farflash TLCDPict _scr12_D10_blank=
{	
	12,80,57,
	(bit_visible+bit_active+bit_static),
	0,	
	0,
	0,
//	Set_Int_State_5,
	scr12_set_pos_3,
	NULL,
};
__farflash TLCDPict _scr12_D11_blank=
{	
	18,80,57,
	(bit_visible+bit_active+bit_static),
	0,	
	0,
	0,
//	Set_Int_State_5,
	scr12_set_pos_4,
	NULL,
};
//-----------------------------------------------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _scr12_t_txt_5=
{
	20,40,53,
	(bit_visible+bit_txt_1),
	15,
};
//--------------------------------------------
__farflash TLCDPict_Txt _scr12_t_txt_4=
{
	18,40,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _scr12_t_txt_3=
{
	16,40,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _scr12_t_txt_2=
{
	14,40,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _scr12_t_txt_1=
{
	12,40,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _scr12_t_txt_0=
{
	10,40,53,
	(bit_visible+bit_txt_1),
	0,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _scr12_d0_txt_4=
{
	8,80,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _scr12_d0_txt_3=
{
	6,80,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _scr12_d0_txt_2=
{
	4,80,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _scr12_d0_txt_1=
{
	2,80,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _scr12_d0_txt_0=
{
	0,80,53,
	(bit_visible+bit_txt_1),
	0,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict_Txt _scr12_d1_txt_4=
{
	20,80,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _scr12_d1_txt_3=
{
	18,80,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _scr12_d1_txt_2=
{
	16,80,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _scr12_d1_txt_1=
{
	14,80,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _scr12_d1_txt_0=
{
	12,80,53,
	(bit_visible+bit_txt_1),
	0,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_12=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	18,
	5+6+5,	
	scr12_init,
	scr12_routine,
	scr12_close,		
};
//-----------------------------------------------------------------------------------
void scr12_init()
{
	u8 i;
	Branch_Number=7;
	step=0;
	new_step=0;
	scr12_edit_pos=0;
	
	Obj[0]=_Menu0;	
	Obj[1]=_Menu1;	
	Obj[2]=_Menu2;	
	Obj[3]=_Menu3;		
	Obj[4]=_Menu4;		
	
	Obj[5]=_Page_12_Season;	
	Obj[6]=_Page_12_Auto_Manual;	
	
	Obj[7]=_Page_12_Up;		
	Obj[8]=_Page_12_Down;	
	Obj[9]=_Page_12_Plus;	
	Obj[10]=_Page_12_Minus;	
	
	Obj[11]=_Page_12_Temperature;	
	Obj[12]=_Page_12_Date;		

	Obj[13]=_scr12_Temp_blank;		
	Obj[14]=_scr12_D00_blank;		
	Obj[15]=_scr12_D01_blank;		
	Obj[16]=_scr12_D10_blank;		
	Obj[17]=_scr12_D11_blank;		
	
	
	Obj[1].Stat=1;
	
	Txt[0]=_scr12_t_txt_0;	
	Txt[1]=_scr12_t_txt_1;	
	Txt[2]=_scr12_t_txt_2;	
	Txt[3]=_scr12_t_txt_3;	
	Txt[4]=_scr12_t_txt_4;	
	Txt[5]=_scr12_t_txt_5;	

	Txt[0+6]=_scr12_d0_txt_0;	
	Txt[1+6]=_scr12_d0_txt_1;	
	Txt[2+6]=_scr12_d0_txt_2;	
	Txt[3+6]=_scr12_d0_txt_3;	
	Txt[4+6]=_scr12_d0_txt_4;	

	Txt[0+6+5]=_scr12_d1_txt_0;	
	Txt[1+6+5]=_scr12_d1_txt_1;	
	Txt[2+6+5]=_scr12_d1_txt_2;	
	Txt[3+6+5]=_scr12_d1_txt_3;	
	Txt[4+6+5]=_scr12_d1_txt_4;	
	
	for(i=0;i<Scr_12.Txt_Num;i++)
		Txt[i].Stat=10;	
}
//-----------------------------------------------------------------------------------
void scr12_close()
{
	u8 i;
	for(i=0;i<Scr_12.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
	lcd_clear_text();
}
//-----------------------------------------------------------------------------------
void scr12_routine()
{
//	u8 tmp,i;		
	u16 temp;
	u8 tmp0;//,tmp1,tmp2; lc
//	u8 old_stat;
	u8 old_stat;
	s16 temperature;
	
	if(FT_Time!=0)return;
	FT_Time=500;
	if(page_offset!=PAGE_0_OFFSET)return;
	scr12_blink++;
	//-----------------------------------------------	
	scr12_update_season_buttons();
	//-----------------------------------------------	
	// Real temperature
	temperature=reg_season.t;	// Real output temperature
	if(temperature>500)temperature=500;
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
	if((scr12_blink & 1)&&(scr12_edit_pos==1))LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
	LCDMenuPtr_Tmp_Txt=&Txt[1];			
	tmp0=temp/100;
	temp-=tmp0*100;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if((scr12_blink & 1)&&(scr12_edit_pos==1))LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[3];	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=12;
	if((scr12_blink & 1)&&(scr12_edit_pos==1))LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
				
	LCDMenuPtr_Tmp_Txt=&Txt[2];				
	tmp0=temp/10;
	temp-=tmp0*10;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;	
	if((scr12_blink & 1)&&(scr12_edit_pos==1))LCDMenuPtr_Tmp_Txt->Stat=16;	
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[4];
	tmp0=temp;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if((scr12_blink & 1)&&(scr12_edit_pos==1))LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[5];	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;			
	LCDMenuPtr_Tmp_Txt->Stat=15;	
	if((scr12_blink & 1)&&(scr12_edit_pos==1))LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	//-----------------------------------------------	
	// Date 0
	temp=reg_season.date[0].field.Date;		
	LCDMenuPtr_Tmp_Txt=&Txt[0+6];			
	tmp0=temp/10;
	temp-=tmp0*10;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if((scr12_blink & 1)&&(scr12_edit_pos==2))LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[1+6];			
	tmp0=temp;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if((scr12_blink & 1)&&(scr12_edit_pos==2))LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
				
	LCDMenuPtr_Tmp_Txt=&Txt[2+6];			
	tmp0=19;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	temp=reg_season.date[0].field.Month;		
	LCDMenuPtr_Tmp_Txt=&Txt[3+6];			
	tmp0=temp/10;
	temp-=tmp0*10;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if((scr12_blink & 1)&&(scr12_edit_pos==3))LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[4+6];			
	tmp0=temp;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if((scr12_blink & 1)&&(scr12_edit_pos==3))LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	//-----------------------------------------------	
	// Date 1
	temp=reg_season.date[1].field.Date;		
	LCDMenuPtr_Tmp_Txt=&Txt[0+6+5];			
	tmp0=temp/10;
	temp-=tmp0*10;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if((scr12_blink & 1)&&(scr12_edit_pos==4))LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[1+6+5];			
	tmp0=temp;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if((scr12_blink & 1)&&(scr12_edit_pos==4))LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
				
	LCDMenuPtr_Tmp_Txt=&Txt[2+6+5];			
	tmp0=19;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	temp=reg_season.date[1].field.Month;		
	LCDMenuPtr_Tmp_Txt=&Txt[3+6+5];			
	tmp0=temp/10;
	temp-=tmp0*10;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if((scr12_blink & 1)&&(scr12_edit_pos==5))LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[4+6+5];			
	tmp0=temp;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if((scr12_blink & 1)&&(scr12_edit_pos==5))LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
}
//-----------------------------------------------------------------------------------
void Schedule_N7()
{
//	u16 i,tmp;
	u8 len;
	M_state_machine();
	if((M.status==st_none)||(M.status==st_complete))
	{		
		if((M.error==0)&&(M.rxnew==1))
		{
			M.rxnew=0;
			switch(M_rx.field.com.bit.com)
			{
				case com_get_season:		
					if(Button_no_update_time==0)
						memcpy(&reg_season,&M_rx.field.d[0],sizeof(TSeason));	
				break;		
				case com_get_register:		
					if(Button_no_update_time==0)
					{
						memcpy(&addr,&M_rx.field.d[0],2);		
						len=M_rx.field.d[2];
						memcpy(&reg_data[addr],&M_rx.field.d[3],len);							
					}
				break;					
				
				case com_set_season:		
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
//				case 0:
//					step++;
//					M_Get_Controller_Status(Current_ID,Current_ID);
					//upc_Get_Controller_Time(1,1);
//					M_SCH_Time=100;
//				break;				
				case 0:
//					M_Get_Season(Current_ID);
					// Season
					M_Get_Controller_Register(Current_ID,&MenuRegs.Season,sizeof(TSeason));										
					step=0;					
					M_SCH_Time=100;	
				break;
				case 2:
//					 M_Set_Season(Current_ID,&reg_season);
					M_Set_Controller_Register(Current_ID,&MenuRegs.Season,sizeof(TSeason));										
					step=0;					
					M_SCH_Time=50;	
				break;
			default:
					step=0;									
				break;
			}
		}		
	}	
}
//-----------------------------------------------------------------------------------

