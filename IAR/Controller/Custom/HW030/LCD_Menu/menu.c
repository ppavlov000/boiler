//-----------------------------------------------------------------------------------
#include "..\..\..\System\main.h"
#include "menuitems_lcd_1.h"
//-----------------------------------------------------------------------------------
vu8 Key0_Time=KEYS_TIME;
vu8 Key1_Time=KEYS_TIME;
vu8 Key2_Time=KEYS_TIME;
vu8 Key3_Time=KEYS_TIME;
vu16 Key_Repeat_Time=0;
vu8 key0=2;
vu8 key1=2;
vu8 key2=2;
vu8 key3=2;
u16 pos=0;
u8 pos2=0;
u16 edit_pos=0;
u8 lcd_txt[32];
u8 menu_stat=0;
u8 current_pid=0;
u8 pass_match=0;
u8 password_lvl=0;
u8 LCD_Cur_Pos=0;
s8 LCD_Shw_Pos=0;
u8 Active_Item=0;
u8 Active_PID=0;
u8 Active_PID_Item=0;
u8 Active_IO_Item=0;
//-----------------------------------------------------------------------------------
#define TOP_RECORDS_NUM 4
//extern in_flash u8	empty_str[17];
//-----------------------------------------------------------------------------------
void rp00();
void rp01();
void rp02();
void rp03();
void rp_text();
void rp_time();
void lcd_choose_time();
void lcd_edit_time();
void lcd_menu_show_errors();
void lcd_show_info();
void lcd_menu_choose_language();
void rp_pid_0();
void rp_pid_1();

void rp_PID_MODE();
void rp_PID_T();
void rp_PID_POWER();
void rp_PID_P();
void rp_PID_D();
void rp_PID_I();
void rp_PID_PMAX();
void rp_PID_PMIN();
void rp_PID_FAST();
void rp_PID_SLOW();
void rp_PID_SSUM();
void rp_PID_ZEROB();
void rp_PID_LOWB();

void ed_PID_MODE();
void ed_PID_T();
void ed_PID_POWER();
void ed_PID_P();
void ed_PID_D();
void ed_PID_I();
void ed_PID_PMAX();
void ed_PID_PMIN();
void ed_PID_FAST();
void ed_PID_SLOW();
void ed_PID_SSUM();
void ed_PID_ZEROB();
void ed_PID_LOWB();

void rp_PID_MODE_0();
void rp_PID_MODE_1();
void rp_DO();
void rp_DI();
void rp_AO();
void rp_AI();
void rp_pass_ena();
void rp_set_pass();

in_flash TNewMenuRecord	Menu[ALL_RECORDS_NUM]=
{
//  "Text",  Access LVL, function, up, down, previous, next
	"EastLabs\n\rController ","Ист Лабс\n\rКонтроллер ",		0, 1, rp00, 0, 0, 0, 1,			//0
	"HW\n\rSW", "HW\n\rSW",										0, 1, rp01, 0, 0, 0, 1,			//1
	"Password","Пароль",										0, 1, rp02, 0, 0, 0, 1,			//2
	// Next items are a list
	// Time
	"", "",														0, 0, rp_time,  0, 1, 0, 3,	//14	
	"", "",														0, 1, lcd_choose_time, -1, 1, 0, 0,	//14	
	"", "",														1, 1, lcd_edit_time,   -1, 0, 0, 0,	//14		
	// PID 0
	"PID", "ПИД",												0, 0, rp_pid_0,  0, 1,-3, 50,	//3	
	"Enable=","Вкл   =",										1, 0, rp_PID_MODE, -1,  0,  0, 1,		//4
	"Tmp T0=","Темп T=",										1, 0, rp_PID_T,    -2,  1, -1, 2,		//5
		"Tmp T0=","Темп T=",									1, 0, ed_PID_T,    -1,  0,  0, 0,		//5	
	"Curr P=","Тек  P=",										1, 0, rp_PID_POWER,-4,  0, -2, 1,		//6
	"Prop P=","Проп P=",										1, 0, rp_PID_P,    -5,  1, -1, 2,		//9
		"Prop P=","Проп P=",									2, 0, ed_PID_P,    -1,  0,  0, 0,		//9	
	"Int  I=","Инт  I=",										1, 0, rp_PID_I,    -7,  1, -2, 2,		//10	
		"Int  I=","Инт  I=",									2, 0, ed_PID_I,    -1,  0,  0, 0,		//10		
	"Diff D=","Дифф D=",										1, 0, rp_PID_D,    -8,  1, -2, 2,		//11
		"Diff D=","Дифф D=",									2, 0, ed_PID_D,    -1,  0,  0, 0,		//11
	"Low  S=","Медл S=",										1, 0, rp_PID_SLOW, -10,  1, -2, 2,		//12
		"Low  S=","Медл S=",									2, 0, ed_PID_SLOW, -1,  0,  0, 0,		//12	
	"Fast S=","Быст S=",										1, 0, rp_PID_FAST, -12,  1, -2, 2,	  	//13		
		"Fast S=","Быст S=",									2, 0, ed_PID_FAST, -1,  0,  0, 0,	  	//13			
	"Summ P=","Сумм P=",										1, 0, rp_PID_SSUM, -14,  1, -2, 2,		//8	
		"Summ P=","Сумм P=",									2, 0, ed_PID_SSUM, -1,  0,  0, 0,		//8		
	"Zero B=","Ноль B=",										1, 0, rp_PID_ZEROB,-16, 1, -2, 2,		//12
		"Zero B=","Ноль B=",									2, 0, ed_PID_ZEROB,-1,  0,  0, 0,		//12	
	"Low  B=","Слаб B=",										1, 0, rp_PID_LOWB, -18, 1, -2, 2,	  	//13			
		"Low  B=","Слаб B=",									2, 0, ed_PID_LOWB, -1,  0,  0, 0,	  	//13				
	"Max  P=","Макс P=",										1, 0, rp_PID_PMAX, -20, 1, -2, 2,		//7
		"Max  P=","Макс P=",									2, 0, ed_PID_PMAX, -1,  0,  0, 0,		//7	
	"Min  P=","Мин  P=",										1, 0, rp_PID_PMIN, -22, 1, -2, 0,		//8
		"Min  P=","Мин  P=",									2, 0, ed_PID_PMIN, -1,  0,  0, 0,		//8	

	// PID 1
	"PID", "ПИД",												0, 0, rp_pid_1,  	0,  1,-25, 25,		//3	
	"Enable=","Вкл   =",										1, 0, rp_PID_MODE, -1,  0,  0, 1,		//4
	"Tmp T0=","Темп T=",										1, 0, rp_PID_T,    -2,  1, -1, 2,		//5
		"Tmp T0=","Темп T=",									1, 0, ed_PID_T,    -1,  0,  0, 0,		//5	
	"Curr P=","Тек  P=",										1, 0, rp_PID_POWER,-4,  0, -2, 1,		//6
	"Prop P=","Проп P=",										1, 0, rp_PID_P,    -5,  1, -1, 2,		//9
		"Prop P=","Проп P=",									2, 0, ed_PID_P,    -1,  0,  0, 0,		//9	
	"Int  I=","Инт  I=",										1, 0, rp_PID_I,    -7,  1, -2, 2,		//10	
		"Int  I=","Инт  I=",									2, 0, ed_PID_I,    -1,  0,  0, 0,		//10		
	"Diff D=","Дифф D=",										1, 0, rp_PID_D,    -8,  1, -2, 2,		//11
		"Diff D=","Дифф D=",									2, 0, ed_PID_D,    -1,  0,  0, 0,		//11
	"Low  S=","Медл S=",										1, 0, rp_PID_SLOW, -10,  1, -2, 2,		//12
		"Low  S=","Медл S=",									2, 0, ed_PID_SLOW, -1,  0,  0, 0,		//12	
	"Fast S=","Быст S=",										1, 0, rp_PID_FAST, -12,  1, -2, 2,	  	//13		
		"Fast S=","Быст S=",									2, 0, ed_PID_FAST, -1,  0,  0, 0,	  	//13			
	"Summ P=","Сумм P=",										1, 0, rp_PID_SSUM, -14,  1, -2, 2,		//8	
		"Summ P=","Сумм P=",									2, 0, ed_PID_SSUM, -1,  0,  0, 0,		//8		
	"Zero B=","Ноль B=",										1, 0, rp_PID_ZEROB,-16, 1, -2, 2,		//12
		"Zero B=","Ноль B=",									2, 0, ed_PID_ZEROB,-1,  0,  0, 0,		//12	
	"Low  B=","Слаб B=",										1, 0, rp_PID_LOWB, -18, 1, -2, 2,	  	//13			
		"Low  B=","Слаб B=",									2, 0, ed_PID_LOWB, -1,  0,  0, 0,	  	//13				
	"Max  P=","Макс P=",										1, 0, rp_PID_PMAX, -20, 1, -2, 2,		//7
		"Max  P=","Макс P=",									2, 0, ed_PID_PMAX, -1,  0,  0, 0,		//7	
	"Min  P=","Мин  P=",										1, 0, rp_PID_PMIN, -22, 1, -2, 0,		//8
		"Min  P=","Мин  P=",									2, 0, ed_PID_PMIN, -1,  0,  0, 0,		//8	
	
	// Mistakes
	"Brakedowns", "Аварии",										0, 0, rp_text,  0, 1, -50, 2,	//14
	"","",														0, 1, lcd_menu_show_errors, -1, 0, 0, 0,	//14	
	// Options
	"Options", "Настройки",										0, 0, rp_text,  0, 1,-2, 0,		//15
	"Info","Информация",										0, 0, rp_text, -1, 1, 0, 2,	//14	
		"","",													0, 1, lcd_show_info, -1, 0, 0, 0,	//14	
	"Language","Язык",											0, 0, rp_text, -3, 1,-2, 2,	//14		
		"","",													0, 1, lcd_menu_choose_language, -1, 0, 0, 0,	//14		
	"Digital IN", "Цифровой   Вход",							1, 0, rp_text, -5, 1,-2, 2,	//14		
		"DI", "DI",			   									1, 0, rp_DI,   -1, 0, 0, 0,	//14			
	"Digital OUT","Цифровой   Вых",								1, 0, rp_text, -6, 1,-2, 2,	//14			
		"DO", "DO",			   									1, 0, rp_DO,   -1, 0, 0, 0,	//14				
	"Analog  IN", "Аналоговый Вход",							1, 0, rp_text, -9, 1,-2, 2,	//14		
		"AI", "AI",			   									1, 0, rp_AI,   -1, 0, 0, 0,	//14				
	"Analog  OUT","Аналоговый Вых",								1, 0, rp_text,-11, 1,-2, 2,	//14				
		"AO", "AO",			   									1, 0, rp_AO,   -1, 0, 0, 0,	//14	
		
	"Password","Пароль",										0, 0, rp_text,    -12, 1,-2, 0,	//14
	"Enter","Ввести",											0, 0, rp_text,    -1,  1, 0, 2,	//14						
		"","",													0, 1, rp_set_pass,-1,  0, 0, 0,	//14			
	"Password","Пароль",										1, 0, rp_pass_ena,-3,  0,-2, 1,	//14					
	"Change","Изменить",										1, 0, rp_text,    -4,  0,-1, 0,	//14							
};
u8 Menu_Pos=3;
//-----------------------------------------------------------------------------------
TMenuRegisters MenuRegs;
//-----------------------------------------------------------------------------------
//TLCDMenuItem*	LCDMenuPtr=&_LCD_Root;
//TLCDMenuItem*	Previos_LCDMenuPtr=&_LCD_Root;
u8 newmenuitem=1;
//-----------------------------------------------------------------------------------
void menu_init()
{
	menu_hardware_init();
//	MenuRegs.lang=1;
	Menu_Pos=0;
	LCD_Cur_Pos=0;
	Active_Item=0;	
}
//-----------------------------------------------------------------------------------
void keys_handler()
{
	// Key 0
	if(menu_is_button_0_pressed())
	{
		Key0_Time=KEYS_TIME;		
		key0=0;	// reset key
	}
	else
	{
		if(key0==0)
		{
			if(Key0_Time==0)		
			{
				key0=1;
				BuzzerTime=MAX_BUZZER_TIME;
				Key_Repeat_Time=KEYS_REPEAT_TIME0;
			}
		}
		if(key0==2)
		{
			if(Key_Repeat_Time==0)		
			{
				key0=1;
				BuzzerTime=MAX_BUZZER_TIME;
				Key_Repeat_Time=KEYS_REPEAT_TIME1;
			}
		}			
	}
	// Key 1
	if(menu_is_button_1_pressed())
	{
		Key1_Time=KEYS_TIME;		
		key1=0;	// reset key
	}
	else
	{
		if(key1==0)
		{
			if(Key1_Time==0)		
			{
				key1=1;
				BuzzerTime=MAX_BUZZER_TIME;
				Key_Repeat_Time=KEYS_REPEAT_TIME0;
			}
		}
		if(key1==2)
		{
			if(Key_Repeat_Time==0)		
			{
				key1=1;
				BuzzerTime=MAX_BUZZER_TIME;
				Key_Repeat_Time=KEYS_REPEAT_TIME1;
			}
		}					
	}
	// Key 2
	if(menu_is_button_2_pressed())
	{
		Key2_Time=KEYS_TIME;		
		key2=0;	// reset key
	}
	else
	{
		if(key2==0)
		{
			if(Key2_Time==0)		
			{
				key2=1;
				BuzzerTime=MAX_BUZZER_TIME;
				Key_Repeat_Time=KEYS_REPEAT_TIME0;
			}
		}		
		if(key2==2)
		{
			if(Key_Repeat_Time==0)		
			{
				key2=1;
				BuzzerTime=MAX_BUZZER_TIME;
				Key_Repeat_Time=KEYS_REPEAT_TIME1;
			}
		}								
	}
	// Key 3
	if(menu_is_button_3_pressed())
	{
		Key3_Time=KEYS_TIME;		
		key3=0;	// reset key
	}
	else
	{
		if(key3==0)
		{
			if(Key3_Time==0)		
			{
				key3=1;
				BuzzerTime=MAX_BUZZER_TIME;
				Key_Repeat_Time=KEYS_REPEAT_TIME0;
			}
		}
		if(key3==2)
		{
			if(Key_Repeat_Time==0)		
			{
				key3=1;
				BuzzerTime=MAX_BUZZER_TIME;
				Key_Repeat_Time=KEYS_REPEAT_TIME1;
			}
		}					
	}
}
//-----------------------------------------------------------------------------------
u8 get_prev_menu()
{
	u8 pos=Menu_Pos;
	while(1)
	{
		if(Menu[pos].PreviosItem!=0)			
		{
			pos=pos+Menu[pos].PreviosItem;
			if(Menu[pos].lvl<=password_lvl)	
			{
				Menu_Pos=pos;
				return 1;
			}
		}
		else
			return 0;
	}
}
//-----------------------------------------------------------------------------------
u8 get_next_menu()
{
	u8 pos=Menu_Pos;
	while(1)
	{
		if(Menu[pos].NextItem!=0)			
		{
			pos=pos+Menu[pos].NextItem;
			if(Menu[pos].lvl<=password_lvl)	
			{
				Menu_Pos=pos;
				return 1;
			}
		}
		else
			return 0;
	}
}
//-----------------------------------------------------------------------------------
u8 get_sub_menu()
{
	u8 pos=Menu_Pos;
	while(1)
	{
		if(Menu[pos].SubItem!=0)			
		{
			pos=pos+Menu[pos].SubItem;
			if(Menu[pos].lvl<=password_lvl)	
			{
				Menu_Pos=pos;
				return 1;
			}
		}
		else
			return 0;
	}	
}
//-----------------------------------------------------------------------------------
u8 get_up_menu()
{
	u8 pos=Menu_Pos;
	while(1)
	{
		if(Menu[pos].UpItem!=0)			
		{
			pos=pos+Menu[pos].UpItem;
			if(Menu[pos].lvl<=password_lvl)	
			{
				Menu_Pos=pos;
				return 1;
			}
		}
		else
			return 0;
	}		
}
//-----------------------------------------------------------------------------------
void keys_menu()
{
	u8 i;
	i=Menu_Pos;
	// Upper items		
	if(Menu[Menu_Pos].special==0)	
	{
		Active_Item=0;
		LCD_Shw_Pos=LCD_Cur_Pos;	
		while((LCD_Shw_Pos!=0)&&(get_prev_menu()!=0))	
		{
			LCD_Shw_Pos--;		
			Menu[Menu_Pos].Routine();			
		}
	}	
	// Central item
	Active_Item=1;
	Menu_Pos=i;
	LCD_Shw_Pos=LCD_Cur_Pos;
	Menu[Menu_Pos].Routine();			

	if(Menu[Menu_Pos].special==0)	
	{
		// Bottom items
		i=Menu_Pos;
		Active_Item=0;
		LCD_Shw_Pos=LCD_Cur_Pos;
		while((LCD_Shw_Pos<(LCD_MAX_LINES-1))&&(get_next_menu()!=0))
		{
			LCD_Shw_Pos++;		
			Menu[Menu_Pos].Routine();			
		}
		Menu_Pos=i;				
	}
}
//-----------------------------------------------------------------------------------
// Text
//-----------------------------------------------------------------------------------
void rp_simple_show()
{
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
	}	
}
//-----------------------------------------------------------------------------------
void rp_simple_action()
{
	if(Active_Item)
	{
		newmenuitem=0;		
		if(LCD_Time==0)
			newmenuitem=1;		
		// -------- Keys --------------//
		// Up arrow
		if(key0==1)
		{			
			//Menu_Pos=Menu_Pos+Menu[Menu_Pos].PreviosItem;
			if(get_prev_menu())
				if(LCD_Cur_Pos>0)LCD_Cur_Pos--;				
			LCD_Time=0;
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{			
			//Menu_Pos=Menu_Pos+Menu[Menu_Pos].NextItem;
			if(get_next_menu())
				if(LCD_Cur_Pos<(LCD_MAX_LINES-1))LCD_Cur_Pos++;		
			LCD_Time=0;		
			newmenuitem=1;
			key1=2;
		}	
		// Esc
		if(key2==1)
		{
//			if(Menu[Menu_Pos].UpItem != 0)
			if(get_up_menu() != 0)			
			{
				//Menu_Pos=Menu_Pos+Menu[Menu_Pos].UpItem;
//				get_up_menu();
				LCD_Cur_Pos=0;
				lcd_clear();
			}
			LCD_Time=0;	
			newmenuitem=1;
			key2=2;			
		}
		// Enter		
		if(key3==1)
		{
//			if(LCD_Cur_Pos>0)LCD_Cur_Pos--;
//			if(Menu[Menu_Pos].SubItem != 0)
			if(get_sub_menu() != 0)						
			{
				//Menu_Pos=Menu_Pos+Menu[Menu_Pos].SubItem;
				LCD_Cur_Pos=0;
				lcd_clear();
			}
			LCD_Time=0;		
			newmenuitem=1;			
			key3=2;			
		}
	}	
}
//-----------------------------------------------------------------------------------
void rp_text()
{
	rp_simple_show();	
	rp_simple_action();
}
//-----------------------------------------------------------------------------------
// Show first page
void rp00()
{
	if(newmenuitem)
	{
		lcd_clear();			
		lcd_printf_P(Menu[Menu_Pos].str[MenuRegs.lang]);
		LCD_Time=2000;					
	}
	newmenuitem=0;
	if(LCD_Time==0)
	{
		newmenuitem=1;			
		Menu_Pos=Menu_Pos+Menu[Menu_Pos].NextItem;
	}	
}
//-----------------------------------------------------------------------------------
// Show serial numbers
void rp01()
{
	if(newmenuitem)
	{
		lcd_clear();			
		lcd_printf_P(Menu[Menu_Pos].str[MenuRegs.lang]);
		FGet(HAPP_FLASH_START+THW_LOC,(u8*)&ltmp,4);	
		LongToStr(lcd_txt,&ltmp,0);
		lcd_set_pos(0,3);
		lcd_printf(lcd_txt);
			
		FGet(HAPP_FLASH_START+TSW_LOC,(u8*)&ltmp,4);	
		LongToStr(lcd_txt,&ltmp,0);
		lcd_set_pos(1,3);
		lcd_printf(lcd_txt);									
		LCD_Time=2000;					
	}
	newmenuitem=0;
	if(LCD_Time==0)
	{
		newmenuitem=1;			
		Menu_Pos=Menu_Pos+Menu[Menu_Pos].NextItem;
	}	
}
//-----------------------------------------------------------------------------------
void rp_DO()
{
	u8 i;
	u32 tmp=1;
	u8 str[LCD_MAX_SYMBOLS+1];
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear();
		lcd_printf_P_pos(LCD_Shw_Pos,0,Menu[Menu_Pos].str[MenuRegs.lang]);	
		ByteToStrFillZero(lcd_txt,&Active_IO_Item,0,2,'0');
		lcd_printf_pos(LCD_Shw_Pos,3,lcd_txt);
		memset(str,0,LCD_MAX_SYMBOLS+1);
		for(i=0;i<io.num_do;i++)
		{
			if(io.dout & tmp)
				lcd_txt[i]='1';
			else
				lcd_txt[i]='0';
			str[i]=' ';
			if(Active_IO_Item==i)str[i]='^';
			lcd_txt[i+1]=0;
			tmp=tmp<<1;
		}
		lcd_printf_pos(LCD_Shw_Pos,6,lcd_txt);
		lcd_printf_pos(LCD_Shw_Pos+1,6,str);
	}	
	// Editing
	if(Active_Item)
	{
		newmenuitem=0;		
		if(LCD_Time==0)
			newmenuitem=1;		
		// -------- Keys --------------//
		// Up arrow
		if(key0==1)
		{			
			if(Active_IO_Item>0)Active_IO_Item--;				
			LCD_Time=0;
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{			
			if(Active_IO_Item<(io.num_do-1))Active_IO_Item++;		
			LCD_Time=0;		
			newmenuitem=1;
			key1=2;
		}	
		// Esc
		if(key2==1)
		{
			if(get_up_menu() != 0)			
			{
				LCD_Cur_Pos=0;
				lcd_clear();
			}
			Active_IO_Item=0;
			LCD_Time=0;	
			newmenuitem=1;
			key2=2;			
		}
		// Enter		
		if(key3==1)
		{
			io.dout^=1UL<<Active_IO_Item;
			LCD_Time=0;		
			newmenuitem=1;			
			key3=2;			
		}
	}	
}
//-----------------------------------------------------------------------------------
void rp_DI()
{
	u8 i;
	u32 tmp=1;
	u8 str[LCD_MAX_SYMBOLS+1];
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear();
		lcd_printf_P_pos(LCD_Shw_Pos,0,Menu[Menu_Pos].str[MenuRegs.lang]);	
		ByteToStrFillZero(lcd_txt,&Active_IO_Item,0,2,'0');
		lcd_printf_pos(LCD_Shw_Pos,3,lcd_txt);
		memset(str,0,LCD_MAX_SYMBOLS+1);
		for(i=0;i<io.num_di;i++)
		{
			if(io.din & tmp)
				lcd_txt[i]='1';
			else
				lcd_txt[i]='0';
			str[i]=' ';
			if(Active_IO_Item==i)str[i]='^';
			lcd_txt[i+1]=0;
			tmp=tmp<<1;
		}
		lcd_printf_pos(LCD_Shw_Pos,6,lcd_txt);
		lcd_printf_pos(LCD_Shw_Pos+1,6,str);
	}	
	// Editing
	if(Active_Item)
	{
		newmenuitem=0;		
		if(LCD_Time==0)
			newmenuitem=1;		
		// -------- Keys --------------//
		// Up arrow
		if(key0==1)
		{			
			if(Active_IO_Item>0)Active_IO_Item--;				
			LCD_Time=0;
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{			
			if(Active_IO_Item<(io.num_di-1))Active_IO_Item++;		
			LCD_Time=0;		
			newmenuitem=1;
			key1=2;
		}	
		// Esc
		if(key2==1)
		{
			if(get_up_menu() != 0)			
			{
				LCD_Cur_Pos=0;
				lcd_clear();
			}
			Active_IO_Item=0;
			LCD_Time=0;	
			newmenuitem=1;
			key2=2;			
		}
		// Enter		
		if(key3==1)
		{
			LCD_Time=0;		
			newmenuitem=1;			
			key3=2;			
		}
	}	
}
//-----------------------------------------------------------------------------------
void rp_AI()
{
	u8 i,x,y;
//	u32 tmp=1;
	u8 str[LCD_MAX_SYMBOLS+1];
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear();
		lcd_printf_P_pos(LCD_Shw_Pos,0,Menu[Menu_Pos].str[MenuRegs.lang]);	
		ByteToStrFillZero(lcd_txt,&Active_IO_Item,0,2,'0');
		lcd_printf_pos(LCD_Shw_Pos,2,lcd_txt);
		memset(str,0,LCD_MAX_SYMBOLS+1);
		for(i=0;i<io.num_ai;i++)
		{
			y=i/2;
			x=6*(i-2*y);
			if(y<LCD_MAX_LINES){
				ShowTemperatureShort(lcd_txt,&io.ainput[i]);
//				ShowPowerShort(lcd_txt,&io.ainput[i]);
				lcd_printf_pos(LCD_Shw_Pos+y,5+x,lcd_txt);	
				if(Active_IO_Item==i)lcd_printf_pos(LCD_Shw_Pos+y,4+x,">");	
			}
		}
	}	
	// Editing
	if(Active_Item)
	{
		newmenuitem=0;		
		if(LCD_Time==0)
			newmenuitem=1;		
		// -------- Keys --------------//
		// Up arrow
		if(key0==1)
		{			
			if(Active_IO_Item>0)Active_IO_Item--;				
			LCD_Time=0;
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{			
			if(Active_IO_Item<(io.num_ai-1))Active_IO_Item++;		
			LCD_Time=0;		
			newmenuitem=1;
			key1=2;
		}	
		// Esc
		if(key2==1)
		{
			if(get_up_menu() != 0)			
			{
				LCD_Cur_Pos=0;
				lcd_clear();
			}
			Active_IO_Item=0;
			LCD_Time=0;	
			newmenuitem=1;
			key2=2;			
		}
		// Enter		
		if(key3==1)
		{
			LCD_Time=0;		
			newmenuitem=1;			
			key3=2;			
		}
	}	
}
//-----------------------------------------------------------------------------------
void rp_AO()
{
	u8 i,x,y;
//	u32 tmp=1;
	u8 str[LCD_MAX_SYMBOLS+1];
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear();
		lcd_printf_P_pos(LCD_Shw_Pos,0,Menu[Menu_Pos].str[MenuRegs.lang]);	
		ByteToStrFillZero(lcd_txt,&Active_IO_Item,0,2,'0');
		lcd_printf_pos(LCD_Shw_Pos,2,lcd_txt);
		memset(str,0,LCD_MAX_SYMBOLS+1);
		for(i=0;i<io.num_ao;i++)
		{
			y=i/2;
			x=6*(i-2*y);
			if(y<LCD_MAX_LINES){
//				ShowTemperature(lcd_txt,(s16*)&io.aoutput[i]);
				ShowPowerShort(lcd_txt,(s16*)&io.aoutput[i]);
				lcd_printf_pos(LCD_Shw_Pos+y,5+x,lcd_txt);	
				if(Active_IO_Item==i)lcd_printf_pos(LCD_Shw_Pos+y,4+x,">");	
			}
		}
	}	
	// Editing
	if(Active_Item)
	{
		newmenuitem=0;		
		if(LCD_Time==0)
			newmenuitem=1;		
		// -------- Keys --------------//
		// Up arrow
		if(key0==1)
		{			
			if(Active_IO_Item>0)Active_IO_Item--;				
			LCD_Time=0;
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{			
			if(Active_IO_Item<(io.num_ao-1))Active_IO_Item++;		
			LCD_Time=0;		
			newmenuitem=1;
			key1=2;
		}	
		// Esc
		if(key2==1)
		{
			if(get_up_menu() != 0)			
			{
				LCD_Cur_Pos=0;
				lcd_clear();
			}
			Active_IO_Item=0;
			LCD_Time=0;	
			newmenuitem=1;
			key2=2;			
		}
		// Enter		
		if(key3==1)
		{
			LCD_Time=0;		
			newmenuitem=1;			
			key3=2;			
		}
	}	
}

//-----------------------------------------------------------------------------------
