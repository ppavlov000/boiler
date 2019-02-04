//-----------------------------------------------------------------------------------
#include "..\..\..\System\main.h"
//-----------------------------------------------------------------------------------
// Errors list
#define  cont_no_error 				0x0000
#define  cont_bad_thermo_sensor 	0x0100
#define  cont_freezing_channel		0x0200
#define  cont_freezing_external		0x0300
#define  cont_low_temperature		0x0400
#define  cont_high_temperature		0x0500
#define  cont_bad_fan				0x0600
#define  cont_bad_filter			0x0700
#define  cont_bad_220				0x0800
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
in_flash u8	eng_err_dic[9][20]=
{
	"No problems",		//0
	"Sensor",			//1
	"Freez chn",		//2
	"Freez ext",		//3	
	"Low temp",			//4		
	"High temp",		//5		
	"Bad fan",			//6
	"Filter",			//7		
	"Bad 220",			//8	
};
in_flash u8	ru_err_dic[10][20]=
{
	"Нет ошибок",		//0
	"Т сенсор",			//1	
	"Замр кан",			//2
	"Замр внеш",		//3	
	"Низкая  T",		//4
	"Высокая T ",		//5
	"Вентилят",			//6
	"Фильтр",			//7	
	"Сеть",				//8

};	
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void lcd_menu_show_errors()
{
//	s16 tmp;
	u8 err_number, err_channel;
//	u8 edit_pos;
//	u8 edit_pos_tmp;	
	if(newmenuitem)
	{
		lcd_clear();
		memset(lcd_txt, 0, sizeof(lcd_txt));		
		if(errors.item[0].code==0)
		{
			// No Errors at all
			lcd_set_pos(0,0);
			if(MenuRegs.lang==0)
				lcd_printf_P(eng_err_dic[0]);			
			if(MenuRegs.lang==1)
				lcd_printf_P(ru_err_dic[0]);			
		}
		if(errors.item[pos].code!=0)
		{
			err_number=errors.item[pos].code>>8;
			err_channel=errors.item[pos].code;
			lcd_set_pos(0,0);
			lcd_txt[0]='0'+pos;lcd_txt[1]=' ';lcd_txt[2]=0;
			lcd_printf(lcd_txt);
			lcd_set_pos(0,2);		
			ByteToStrFillZero(lcd_txt,(u8*)&err_number,0,1,'0');
			lcd_printf(lcd_txt);	
			lcd_set_pos(0,4);		
			ByteToStrFillZero(lcd_txt,(u8*)&err_channel,0,1,'0');			
			lcd_printf(lcd_txt);	
	
			lcd_set_pos(0,7);						
			if(MenuRegs.lang==0)
				lcd_printf_P(eng_err_dic[err_number]);			
			if(MenuRegs.lang==1)
				lcd_printf_P(ru_err_dic[err_number]);	
			lcd_set_pos(1,0);
			ByteToStrFillZero(lcd_txt,&errors.item[pos].time.field.Date,0,2,'0');lcd_printf(lcd_txt);lcd_printf(".");
			lcd_set_pos(1,3);
			ByteToStrFillZero(lcd_txt,&errors.item[pos].time.field.Month,0,2,'0');lcd_printf(lcd_txt);lcd_printf(".");
			lcd_set_pos(1,6);
			ByteToStrFillZero(lcd_txt,&errors.item[pos].time.field.Year,0,2,'0');lcd_printf(lcd_txt);
			lcd_set_pos(1,11);
			ByteToStrFillZero(lcd_txt,&errors.item[pos].time.field.Hour,0,2,'0');lcd_printf(lcd_txt);lcd_printf(":");		
			lcd_set_pos(1,14);
			ByteToStrFillZero(lcd_txt,&errors.item[pos].time.field.Minute,0,2,'0');lcd_printf(lcd_txt);		
		}
	}
	newmenuitem=0;	
		// -------- Keys --------------//
		// Up arrow
		if(key0==1)
		{
			if(pos!=0)pos--;
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{
			if(pos<(MAX_ERRORS_NUM-1))
				if(errors.item[pos+1].code!=0)pos++;
			newmenuitem=1;
			key1=2;
		}
		// Esc
		if(key2==1)
		{
			if(Menu[Menu_Pos].UpItem != 0)
			{
				Menu_Pos=Menu_Pos+Menu[Menu_Pos].UpItem;
				LCD_Cur_Pos=0;
				pos=0;
				lcd_clear();
			}		
			newmenuitem=1;				
			key2=2;			
		}
		// Enter		
		if(key3==1)
		{
			if(Menu[Menu_Pos].UpItem != 0)
			{
				Menu_Pos=Menu_Pos+Menu[Menu_Pos].UpItem;
				LCD_Cur_Pos=0;
				lcd_clear();
				pos=0;
			}		
			key3=2;			
		}	
}
//-----------------------------------------------------------------------------------
