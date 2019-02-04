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
extern u8 step;
extern u8 new_step;
extern u8 str[40];
extern  u16 Store_Time;
//-----------------------------------------------------------------------------------
void scr11_init();
void scr11_close();
void scr11_routine();
extern u8 Current_ID;
extern u8 Branch_Number;
void custom_handle();
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
#define STR_BASE 5	
u8 pos_col=0;
u8 pos_row=0;
u8 pos_col_new=0;
u8 pos_row_new=0;
//-----------------------------------------------------------------------------------
void scr11_Auto_Manual()
{
	FT_Time=0;
	if(m.sch_auto_manual==0)
		m.sch_auto_manual=1;
	else
		m.sch_auto_manual=0;
	Store_Time=5000;	
//	if(m.sch_auto_manual==0)
//		Obj[10].Stat=0;
//	else
//		Obj[10].Stat=1;	
}
//--------------------------------------------------------
void scr11_up()
{
	FT_Time=0;	
	if(pos_row_new>0)pos_row_new--;
}
//--------------------------------------------------------
void scr11_down()
{
	FT_Time=0;
	if(pos_col_new!=4){
		if(pos_row_new<6)pos_row_new++;	
	}
	else
		if(pos_row_new<1)pos_row_new++;	
}
//--------------------------------------------------------
void scr11_left()
{
	FT_Time=0;
	if(pos_col_new>0)pos_col_new--;	
}
//--------------------------------------------------------
void scr11_right()
{
	FT_Time=0;
	if(pos_col_new<4)pos_col_new++;		
	if(pos_col_new==4)
		if(pos_row_new>1)pos_row_new=1;	
	
}
//--------------------------------------------------------
void scr11_plus()
{
	u8 col=pos_col>>1;
	FT_Time=0;
	Store_Time=5000;	
	if(pos_col_new!=4){
		if(pos_col & 1)
		{		
			m.sch[pos_row][col].Minute++;
			if(m.sch[pos_row][col].Minute>59)m.sch[pos_row][col].Minute=0;
		}
		else
		{
			m.sch[pos_row][col].Hour++;
			if(m.sch[pos_row][col].Hour>23)m.sch[pos_row][col].Hour=0;
		}
	}
	else{
		m.sch_temperature[pos_row]++;
		if(m.sch_temperature[pos_row]>400)m.sch_temperature[pos_row]=400;
	}
}
//--------------------------------------------------------
void scr11_minus()
{
	u8 col=pos_col>>1;
	FT_Time=0;
	Store_Time=5000;	
	if(pos_col_new!=4){	
		if(pos_col & 1)
		{		
			if(m.sch[pos_row][col].Minute>0) m.sch[pos_row][col].Minute--;
			else	m.sch[pos_row][col].Minute=59;
		}
		else
		{
			if(m.sch[pos_row][col].Hour>0) m.sch[pos_row][col].Hour--;
			else	m.sch[pos_row][col].Hour=23;		
		}
	}
	else{
			m.sch_temperature[pos_row]--;
			if(m.sch_temperature[pos_row]<100)m.sch_temperature[pos_row]=100;
	}
	
}

void print_cursor_y(u8 *str)
{
		switch(pos_col){
		case 0:
			lcd_sprintf(str,6,STR_BASE+7);	
			break;
		case 1:
			lcd_sprintf(str,9,STR_BASE+7);	
			break;
		case 2:
			lcd_sprintf(str,12,STR_BASE+7);	
			break;
		case 3:
			lcd_sprintf(str,15,STR_BASE+7);	
			break;
		case 4:
			lcd_sprintf(str,21,STR_BASE+2);	
			break;
		}
//		case 5:
//			lcd_sprintf(str,21,STR_BASE+7);	
//			break;
//		case 6:
//			lcd_sprintf(str,24,STR_BASE+7);	
//			break;
//		case 7:
//			lcd_sprintf(str,27,STR_BASE+7);	
//			break;
//		}	
		
}

//-----------------------------------------------------------------------------------
void scr11_sbros()
{
	lcd_clear_text();
//	FT_Time=500;
	new_step=22;
}
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_11_Sbros=
{	
	26,29,29,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	scr11_sbros,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Page_11_Auto_Manual=
{	
	19,77,46,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,
	scr11_Auto_Manual,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Page_11_Up=
{	
	0,108,42,
	(bit_visible+bit_active),
	0,
	0,	
	0,	
	scr11_up,	
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Page_11_Down=
{	
	5,108,43,
	(bit_visible+bit_active),
	0,
	0,	
	0,	
	scr11_down,	
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Page_11_Left=
{	
	10,108,40,
	(bit_visible+bit_active),
	0,
	0,	
	0,	
	scr11_left,	
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Page_11_Right=
{	
	15,108,41,
	(bit_visible+bit_active),
	0,
	0,	
	0,	
	scr11_right,	
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Page_11_Plus=
{	
	20,108,44,
	(bit_visible+bit_active),
	0,
	0,	
	0,	
	scr11_plus,	
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Page_11_Minus=
{	
	25,108,45,
	(bit_visible+bit_active),
	0,
	0,	
	0,	
	scr11_minus,	
	NULL,	
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_11=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	12,
	0,	
	scr11_init,
	scr11_routine,
	scr11_close,		
};
//-----------------------------------------------------------------------------------
void scr11_init()
{
//	u8 i;
	Obj[0]=_Menu0;	
	Obj[1]=_Menu1;	
	Obj[2]=_Menu2;	
	Obj[3]=_Menu3;		
	Obj[4]=_Menu4;	
	
	Obj[5]=_Page_11_Up;	
	Obj[6]=_Page_11_Down;	
	Obj[7]=_Page_11_Left;	
	Obj[8]=_Page_11_Right;	
	Obj[9]=_Page_11_Plus;	
	Obj[10]=_Page_11_Minus;	

	Obj[11]=_Page_11_Auto_Manual;	

	
	Obj[1].Stat=1;
	if(m.sch_auto_manual==0)
		Obj[11].Stat=0;
	else
		Obj[11].Stat=1;
}
//-----------------------------------------------------------------------------------
void scr11_close()
{
	u8 i;
	for(i=0;i<Scr_1.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
	lcd_clear_text();
}
//-----------------------------------------------------------------------------------
void scr11_routine()
{
	u8 tmp,i;		
//	u16 temp;
//	u8 tmp0;//,tmp1,tmp2; lc
//	u8 old_stat;
//	s16 temperature;
	if(FT_Time!=0)return;
	FT_Time=500;
	if(page_offset!=PAGE_0_OFFSET)return;
	lcd_sprintf("Day time",7,STR_BASE-2);			
	lcd_sprintf("Day/Night T",18,STR_BASE-2);				
	for(i=0;i<7;i++)
	{
		// First line
		lcd_sprintf("                               ",STR_BASE+i,1);			
		lcd_sprintf_P(DaysOfWeek_Short[i],1,STR_BASE+i);						
		ByteToStrFillZero(str,&m.sch[i][0].Hour,0,2,'0');str[2]=':';str[3]=0;
		lcd_sprintf(str,6,STR_BASE+i);				
		ByteToStrFillZero(str,&m.sch[i][0].Minute,0,2,'0');
		lcd_sprintf(str,9,STR_BASE+i);		
		
		lcd_sprintf("-",11,STR_BASE+i);
		
		ByteToStrFillZero(str,&m.sch[i][1].Hour,0,2,'0');str[2]=':';str[3]=0;
		lcd_sprintf(str,12,STR_BASE+i);				
		ByteToStrFillZero(str,&m.sch[i][1].Minute,0,2,'0');
		lcd_sprintf(str,15,STR_BASE+i);				
/*		// Second Line
		lcd_sprintf_P(DaysOfWeek_Short[i],1,STR_BASE+i);						
		ByteToStrFillZero(str,&m.sch[i][2].Hour,0,2,'0');str[2]=':';str[3]=0;
		lcd_sprintf(str,18,STR_BASE+i);				
		ByteToStrFillZero(str,&m.sch[i][2].Minute,0,2,'0');
		lcd_sprintf(str,21,STR_BASE+i);		
		
		lcd_sprintf("-",23,STR_BASE+i);
		
		ByteToStrFillZero(str,&m.sch[i][3].Hour,0,2,'0');str[2]=':';str[3]=0;
		lcd_sprintf(str,24,STR_BASE+i);				
		ByteToStrFillZero(str,&m.sch[i][3].Minute,0,2,'0');
		lcd_sprintf(str,27,STR_BASE+i);			
*/		
	}
	
	ShowTemperatureShort(str,&m.sch_temperature[0]);
	lcd_sprintf(str,19,STR_BASE+0);
	ShowTemperatureShort(str,&m.sch_temperature[1]);
	lcd_sprintf(str,19,STR_BASE+1);
	
	if(pos_row_new!=pos_row)
	{
		lcd_sprintf(" ",0,STR_BASE+pos_row);
		pos_row=pos_row_new;
	}
	if(pos_col_new!=pos_col)
	{
		print_cursor_y("  ");
		pos_col=pos_col_new;
	}
	lcd_sprintf(">",0,STR_BASE+pos_row);	
	print_cursor_y("^^");	
}
//-----------------------------------------------------------------------------------

