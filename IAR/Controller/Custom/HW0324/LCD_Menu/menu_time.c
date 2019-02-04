//-----------------------------------------------------------------------------------
#include "..\..\..\System\main.h"
//-----------------------------------------------------------------------------------
#define MAX_INFO_LINES 6
//-----------------------------------------------------------------------------------
TCTime	menu_ft;
//-----------------------------------------------------------------------------------
extern s8 LCD_Shw_Pos;
//-----------------------------------------------------------------------------------
in_flash u8	eng_time_str[7][16]=
{
	"EastLabs",			//0
	"controller",		//1
	"model:",			//2	
	"HW    ",			//3
	"SW    ",			//4	
	"Issue date ",	//5
	"                ",	//6	
};
in_flash u8	ru_time_str[7][16]=
{
	"ИстЛабс",			//0
	"контроллер",		//1
	"модель:",			//2	
	"Плата ",			//3
	"Софт  ",			//4	
	"Дата выпуска ",	//5
	"                ",	//6	
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
// Show Time
void rp_time()
{
	if(newmenuitem)
	{			
		LCD_Time=1000;	
		rp_simple_show();
		lcd_set_pos(LCD_Shw_Pos,2);
		memset(lcd_txt, 0, sizeof(lcd_txt));
		ByteToStrFillZero(lcd_txt,&ft.field.Date,0,2,'0');lcd_printf(lcd_txt);lcd_printf(".");
		ByteToStrFillZero(lcd_txt,&ft.field.Month,0,2,'0');lcd_printf(lcd_txt);lcd_printf(".");					
		ByteToStrFillZero(lcd_txt,&ft.field.Year,0,2,'0');lcd_printf(lcd_txt);		
		lcd_printf(" ");	
		memset(lcd_txt, 0, sizeof(lcd_txt));
		ByteToStrFillZero(lcd_txt,&ft.field.Hour,0,2,'0');lcd_printf(lcd_txt);lcd_printf(":");
		ByteToStrFillZero(lcd_txt,&ft.field.Minute,0,2,'0');lcd_printf(lcd_txt);											
	}
	rp_simple_action();
}
//-----------------------------------------------------------------------------------
void lcd_show_time()
{
//	s16 tmp;
//	u8 edit_pos;
//	u8 show_pos_tmp;			
	if(newmenuitem)
	{
		lcd_clear();
		memset(lcd_txt, 0, sizeof(lcd_txt));		
		// Line 0
		lcd_set_pos(0,1);
		ByteToStrFillZero(lcd_txt,&ft.field.Date,0,2,'0');
		lcd_printf(lcd_txt);
		lcd_set_pos(0,4);
		if(MenuRegs.lang==1)__sprintf_P(lcd_txt,Monthes_Name_rus[ft.field.Month-1]);
		if(MenuRegs.lang==0)__sprintf_P(lcd_txt,Monthes_Name[ft.field.Month-1]);
		lcd_printf(lcd_txt);
		lcd_set_pos(0,14);
		ByteToStrFillZero(lcd_txt,&ft.field.Year,0,2,'0');
		lcd_printf(lcd_txt);

		lcd_set_pos(1,4);ByteToStrFillZero(lcd_txt,&ft.field.Hour,0,2,'0');lcd_txt[2]='.';lcd_txt[3]=0;lcd_printf(lcd_txt);
		lcd_set_pos(1,7);ByteToStrFillZero(lcd_txt,&ft.field.Minute,0,2,'0');lcd_txt[2]='.';lcd_txt[3]=0;lcd_printf(lcd_txt);
		lcd_set_pos(1,10);ByteToStrFillZero(lcd_txt,&ft.field.Second,0,2,'0');lcd_printf(lcd_txt);
	}
	newmenuitem=0;	
	if(LCD_Time==0)
	{
		newmenuitem=1;	
		LCD_Time=1000;
	}	
		// -------- Keys --------------//
		// Up arrow
		if(key0==1)
		{
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{
			key1=2;
		}
		// Esc
		if(key2==1)
		{
			if(Menu[Menu_Pos].UpItem != 0)
			{
				Menu_Pos=Menu_Pos+Menu[Menu_Pos].UpItem;
				LCD_Cur_Pos=0;
			}	
			newmenuitem=1;				
			key2=2;			
		}
		// Enter		
		if(key3==1)
		{
			if(Menu[Menu_Pos].SubItem != 0)
			{
				Menu_Pos=Menu_Pos+Menu[Menu_Pos].SubItem;
				LCD_Cur_Pos=0;
			}	
			key3=2;			
		}	
}
//-----------------------------------------------------------------------------------
void lcd_choose_time()
{
//	s16 tmp;
//	u8 edit_pos;
	u8 edit_pos_tmp;	
	if(newmenuitem)
	{
		lcd_clear();
		memset(lcd_txt, 0, sizeof(lcd_txt));		
		// Line 0
		lcd_set_pos(0,1);
		ByteToStrFillZero(lcd_txt,&ft.field.Date,0,2,'0');
		lcd_printf(lcd_txt);
		lcd_set_pos(0,4);
		if(MenuRegs.lang==1)__sprintf_P(lcd_txt,Monthes_Name_rus[ft.field.Month-1]);
		if(MenuRegs.lang==0)__sprintf_P(lcd_txt,Monthes_Name[ft.field.Month-1]);
		lcd_printf(lcd_txt);
		lcd_set_pos(0,14);
		ByteToStrFillZero(lcd_txt,&ft.field.Year,0,2,'0');
		lcd_printf(lcd_txt);

		lcd_set_pos(1,4);ByteToStrFillZero(lcd_txt,&ft.field.Hour,0,2,'0');lcd_txt[2]='.';lcd_txt[3]=0;lcd_printf(lcd_txt);
		lcd_set_pos(1,7);ByteToStrFillZero(lcd_txt,&ft.field.Minute,0,2,'0');lcd_txt[2]='.';lcd_txt[3]=0;lcd_printf(lcd_txt);
		lcd_set_pos(1,10);ByteToStrFillZero(lcd_txt,&ft.field.Second,0,2,'0');lcd_printf(lcd_txt);
		
		edit_pos_tmp=pos;
		lcd_set_pos(0,0);lcd_printf(" ");
		lcd_set_pos(0,3);lcd_printf(" ");
		lcd_set_pos(0,13);lcd_printf(" ");
		lcd_set_pos(1,3);lcd_printf(" ");
		lcd_set_pos(1,6);lcd_printf(".");
		lcd_set_pos(1,9);lcd_printf(".");
		switch(edit_pos_tmp)
		{
			case 0:lcd_set_pos(0,0);lcd_printf(">");lcd_set_pos(0,0);break;
			case 1:lcd_set_pos(0,3);lcd_printf(">");lcd_set_pos(1,0);break;
			case 2:lcd_set_pos(0,13);lcd_printf(">");lcd_set_pos(0,0);break;
			case 3:lcd_set_pos(1,3);lcd_printf(">");lcd_set_pos(1,0);break;
			case 4:lcd_set_pos(1,6);lcd_printf(">");lcd_set_pos(0,0);break;
			case 5:lcd_set_pos(1,9);lcd_printf(">");lcd_set_pos(1,0);break;						
		}		
	}		
	newmenuitem=0;	
	if(LCD_Time==0)
	{
		newmenuitem=1;	
		LCD_Time=1000;
	}			
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
			if(pos<5)pos++;
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
			}			
			newmenuitem=1;				
			key2=2;			
		}
		// Enter		
		if(key3==1)
		{
			write_command(0x0c);		
			Delay_mks(1);
			if(Menu[Menu_Pos].SubItem != 0)
			{
				Menu_Pos=Menu_Pos+Menu[Menu_Pos].SubItem;
				LCD_Cur_Pos=0;
				menu_ft=ft;				
				newmenuitem=1;					
			}				
			key3=2;			
		}	
}
//-----------------------------------------------------------------------------------
void lcd_edit_time()
{
//	s16 tmp;
//	u8 edit_pos;
	u8 edit_pos_tmp;	
	if(newmenuitem)
	{
		lcd_clear();
		// Line 0
		lcd_set_pos(0,1);
		ByteToStrFillZero(lcd_txt,&menu_ft.field.Date,0,2,'0');
		lcd_printf(lcd_txt);
		lcd_set_pos(0,4);
		if(MenuRegs.lang==1)__sprintf_P(lcd_txt,Monthes_Name_rus[menu_ft.field.Month-1]);
		if(MenuRegs.lang==0)__sprintf_P(lcd_txt,Monthes_Name[menu_ft.field.Month-1]);
		lcd_printf(lcd_txt);
		lcd_set_pos(0,14);
		ByteToStrFillZero(lcd_txt,&menu_ft.field.Year,0,2,'0');
		lcd_printf(lcd_txt);

		lcd_set_pos(1,4);ByteToStrFillZero(lcd_txt,&menu_ft.field.Hour,0,2,'0');lcd_txt[2]='.';lcd_txt[3]=0;lcd_printf(lcd_txt);
		lcd_set_pos(1,7);ByteToStrFillZero(lcd_txt,&menu_ft.field.Minute,0,2,'0');lcd_txt[2]='.';lcd_txt[3]=0;lcd_printf(lcd_txt);
		lcd_set_pos(1,10);ByteToStrFillZero(lcd_txt,&menu_ft.field.Second,0,2,'0');lcd_printf(lcd_txt);
		
		edit_pos_tmp=pos;
		lcd_set_pos(0,0);lcd_printf(" ");
		lcd_set_pos(0,3);lcd_printf(" ");
		lcd_set_pos(0,13);lcd_printf(" ");
		lcd_set_pos(1,3);lcd_printf(" ");
		lcd_set_pos(1,6);lcd_printf(".");
		lcd_set_pos(1,9);lcd_printf(".");
		switch(edit_pos_tmp)
		{
			case 0:lcd_set_pos(0,0);lcd_printf(">");lcd_set_pos(0,0);break;
			case 1:lcd_set_pos(0,3);lcd_printf(">");lcd_set_pos(0,3);break;
			case 2:lcd_set_pos(0,13);lcd_printf(">");lcd_set_pos(0,13);break;
			case 3:lcd_set_pos(1,3);lcd_printf(">");lcd_set_pos(1,3);break;
			case 4:lcd_set_pos(1,6);lcd_printf(">");lcd_set_pos(1,6);break;
			case 5:lcd_set_pos(1,9);lcd_printf(">");lcd_set_pos(1,9);break;						
		}		
	}	
	write_command(0x0D);		
	Delay_mks(1);
	newmenuitem=0;	
		// -------- Keys --------------//
		// Up arrow
		if(key0==1)
		{
			switch(pos)		
			{
				case 0:if(menu_ft.field.Date<30)menu_ft.field.Date+=1;break;
				case 1:if(menu_ft.field.Month<12)menu_ft.field.Month+=1;break;				
				case 2:if(menu_ft.field.Year<98)menu_ft.field.Year+=1;break;			
				case 3:if(menu_ft.field.Hour<23)menu_ft.field.Hour+=1;break;	
				case 4:if(menu_ft.field.Minute<59)menu_ft.field.Minute+=1;break;	
				case 5:if(menu_ft.field.Second<59)menu_ft.field.Second+=1;break;									
			}
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{
			switch(pos)		
			{
				case 0:if(menu_ft.field.Date>0)menu_ft.field.Date-=1;break;
				case 1:if(menu_ft.field.Month>0)menu_ft.field.Month-=1;break;				
				case 2:if(menu_ft.field.Year>0)menu_ft.field.Year-=1;break;			
				case 3:if(menu_ft.field.Hour>0)menu_ft.field.Hour-=1;break;	
				case 4:if(menu_ft.field.Minute>0)menu_ft.field.Minute-=1;break;	
				case 5:if(menu_ft.field.Second>0)menu_ft.field.Second-=1;break;									
			}
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
				lcd_clear();
				pos=0;
			}
			write_command(0x0c);		
			Delay_mks(1);				
			newmenuitem=1;				
			key2=2;			
		}
		// Enter		
		if(key3==1)
		{
			write_command(0x0c);		
			Delay_mks(1);	
			fram_set_time(menu_ft.field.Hour,menu_ft.field.Minute,menu_ft.field.Second);
			fram_set_date(menu_ft.field.Year,menu_ft.field.Month, menu_ft.field.Date,0);
			ft=menu_ft;				
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
