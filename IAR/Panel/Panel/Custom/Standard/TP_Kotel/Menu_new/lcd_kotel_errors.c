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

extern __farflash TLCDPict Tab_Menu0;
extern __farflash TLCDPict Tab_Menu1;
extern __farflash TLCDPict Tab_Menu2;
extern __farflash TLCDPict Tab_Menu3;
extern __farflash TLCDPict Tab_Menu4;
//-----------------------------------------------------------------------------------
extern u8 Current_ID;
extern u8 Branch_Number;
extern u8 Switch_To_ID_1;
//-----------------------------------------------------------------------------------
__farflash u8	eng_kot_errors_str[][25]=
{
	"No errors       ",							//0
	"Low preasure    ",							//1
	"High preasure   ",						//2
	"High temperature",						//3
	"Bad smoke fan   ",						//4	
	"Bad screw       ",							//5	
	"Bad fan         ",								//6	
	"Open topka      ",							//7	
	"Screw motor     ",							//8
	"Fan motor       ",							//9	
	"Fire in screw   ",						//10	
	"Not defined     ",							//11	
};
__farflash u8	ru_kot_errors_str[][25]=
{
	"Ошибок нет",							//0
	"Проблема с термодатчиком",	 			//1
	"Канальный дат разморозки",				//2
	"Внешний дат разморозки",				//3
	"Низкая температура",					//4	
	"Высокая температура",					//5	
	"Проблема с ветилятором",				//6	
	"Проблема с фильтром",					//7	
	"Проблема с питанием",					//8	
};
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
extern u8 Common_ID_Mode;
//TErrors errors;
//-----------------------------------------------------------------------------------
void scr0_4_init();
void scr0_4_close();
void scr0_4_routine();
//-----------------------------------------------------------------------------------
void scr0_4_sbros()
{
	lcd_clear_text();
//	FT_Time=500;
	new_step=50;
}
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_0_4_Sbros=
{	
	26,29,29,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	scr0_4_sbros,
	NULL,
};

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_0_4=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	5+1,
	0,	
	scr0_4_init,
	scr0_4_routine,
	scr0_4_close,		
};
//-----------------------------------------------------------------------------------
void scr0_4_init()
{
//	u8 i;
	Branch_Number=2;
	new_step=step=0;
	
	Obj[0]=Tab_Menu0;	
	Obj[1]=Tab_Menu1;	
	Obj[2]=Tab_Menu2;	
	Obj[3]=Tab_Menu3;		
	Obj[4]=Tab_Menu4;	
	
	Obj[4].Stat=1;
		
	Obj[0].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[1].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[2].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[3].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[4].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	
	Obj[5]=_Page_0_4_Sbros;	
}
//-----------------------------------------------------------------------------------
void scr0_4_close()
{
	u8 i;
	for(i=0;i<Scr_1.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
	lcd_clear_text();
}
//-----------------------------------------------------------------------------------
void scr0_4_routine()
{
	u8 tmp,i;		
//	u16 temp;
//	u8 tmp0;//,tmp1,tmp2; lc
//	u8 old_stat;
//	s16 temperature;
	if(FT_Time!=0)return;
	FT_Time=500;
	if(page_offset!=PAGE_0_OFFSET)return;
//	lcd_clear_text();	
	if(Common_ID_Mode)return; // Exit if common mode selected
	for(i=0;i<MAX_ERRORS_NUM;i++)
	{
		if(errors.item[i].code!=0)
		{		
			// Date
			ByteToStrFillZero(lcd_txt,&errors.item[i].time.field.Date,0,2,'0');
			lcd_txt[2]='/';lcd_txt[3]=0;
			lcd_sprintf(lcd_txt,0,3+(i*2));
			ByteToStrFillZero(lcd_txt,&errors.item[i].time.field.Month,0,2,'0');
			lcd_txt[2]='/';lcd_txt[3]=0;
			lcd_sprintf(lcd_txt,3,3+(i*2));
			ByteToStrFillZero(lcd_txt,&errors.item[i].time.field.Year,0,2,'0');
			lcd_sprintf(lcd_txt,6,3+(i*2));	
			// Time
			ByteToStrFillZero(lcd_txt,&errors.item[i].time.field.Hour,0,2,'0');
			lcd_txt[2]=':';lcd_txt[3]=0;
			lcd_sprintf(lcd_txt,9,3+(i*2));
			ByteToStrFillZero(lcd_txt,&errors.item[i].time.field.Minute,0,2,'0');
			lcd_txt[2]=':';lcd_txt[3]=0;
			lcd_sprintf(lcd_txt,12,3+(i*2));
			ByteToStrFillZero(lcd_txt,&errors.item[i].time.field.Second,0,2,'0');
			lcd_sprintf(lcd_txt,15,3+(i*2));				

			tmp=errors.item[i].code>>8;
			ByteToStrFillZero(lcd_txt,&tmp,0,2,'0');
			lcd_sprintf(lcd_txt,18,3+(i*2));				
			tmp=errors.item[i].code;
			ByteToStrFillZero(lcd_txt,&tmp,0,2,'0');
			lcd_sprintf(lcd_txt,21,3+(i*2));				

//			WordToStrFillZero(lcd_txt,&mcu.errors.item[i].code,0,2,'0',0);
//			lcd_sprintf(lcd_txt,18,3+(i*2));				
			lcd_sprintf_P(eng_kot_errors_str[errors.item[i].code>>8],0,3+2*i+1);			
		}		
		if(errors.item[i].code==0)return;
	}		
	
}
//-----------------------------------------------------------------------------------

