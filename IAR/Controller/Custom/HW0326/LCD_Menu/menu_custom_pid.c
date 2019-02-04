//-----------------------------------------------------------------------------------
#include "..\..\..\System\main.h"
//-----------------------------------------------------------------------------------
#define MAX_INFO_LINES 6
//-----------------------------------------------------------------------------------
extern TCTime	menu_ft;
//-----------------------------------------------------------------------------------
extern s8 LCD_Shw_Pos;
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
// Show Time
void rp_custom_pid_time()
{
	if(newmenuitem)
	{			
		LCD_Time=1000;	
		rp_simple_show();
		lcd_set_pos(LCD_Shw_Pos,13);
		memset(lcd_txt, 0, sizeof(lcd_txt));
//		ByteToStrFillZero(lcd_txt,&ft.field.Date,0,2,'0');lcd_printf(lcd_txt);lcd_printf(".");
//		ByteToStrFillZero(lcd_txt,&ft.field.Month,0,2,'0');lcd_printf(lcd_txt);lcd_printf(".");					
//		ByteToStrFillZero(lcd_txt,&ft.field.Year,0,2,'0');lcd_printf(lcd_txt);		
//		lcd_printf(" ");	
//		memset(lcd_txt, 0, sizeof(lcd_txt));
//		ByteToStrFillZero(lcd_txt,&ft.field.Hour,0,2,'0');lcd_printf(lcd_txt);lcd_printf(":");
//		ByteToStrFillZero(lcd_txt,&ft.field.Minute,0,2,'0');
		if(MenuRegs.Schedule_Enable)lcd_printf("ON");
		else lcd_printf("OFF");		
	}
	rp_simple_action();
}
//-----------------------------------------------------------------------------------
void lcd_custom_pid_show_time()
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
		if(MenuRegs.Schedule_Enable)lcd_printf("ON");
		else lcd_printf("OFF");			
		lcd_set_pos(0,7);ByteToStrFillZero(lcd_txt,&MenuRegs.Schedule_Time[0].field.Hour,0,2,'0');lcd_txt[9]='.';lcd_txt[10]=0;lcd_printf(lcd_txt);
		lcd_set_pos(0,10);ByteToStrFillZero(lcd_txt,&MenuRegs.Schedule_Time[0].field.Minute,0,2,'0');lcd_printf(lcd_txt);
		lcd_set_pos(1,7);ByteToStrFillZero(lcd_txt,&MenuRegs.Schedule_Time[1].field.Hour,0,2,'0');lcd_txt[9]='.';lcd_txt[10]=0;lcd_printf(lcd_txt);
		lcd_set_pos(1,10);ByteToStrFillZero(lcd_txt,&MenuRegs.Schedule_Time[1].field.Minute,0,2,'0');lcd_printf(lcd_txt);
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
void lcd_custom_pid_choose_time()
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
		if(MenuRegs.Schedule_Enable)lcd_printf("ON");
		else lcd_printf("OFF");			
		lcd_set_pos(0,7);ByteToStrFillZero(lcd_txt,&MenuRegs.Schedule_Time[0].field.Hour,0,2,'0');lcd_txt[9]='.';lcd_txt[10]=0;lcd_printf(lcd_txt);
		lcd_set_pos(0,10);ByteToStrFillZero(lcd_txt,&MenuRegs.Schedule_Time[0].field.Minute,0,2,'0');lcd_printf(lcd_txt);
		lcd_set_pos(1,7);ByteToStrFillZero(lcd_txt,&MenuRegs.Schedule_Time[1].field.Hour,0,2,'0');lcd_txt[9]='.';lcd_txt[10]=0;lcd_printf(lcd_txt);
		lcd_set_pos(1,10);ByteToStrFillZero(lcd_txt,&MenuRegs.Schedule_Time[1].field.Minute,0,2,'0');lcd_printf(lcd_txt);
	
		edit_pos_tmp=pos;
		lcd_set_pos(0,0);lcd_printf(" ");
		lcd_set_pos(0,6);lcd_printf(" ");
		lcd_set_pos(0,9);lcd_printf(".");
		lcd_set_pos(1,6);lcd_printf(" ");
		lcd_set_pos(1,9);lcd_printf(".");
		switch(edit_pos_tmp)
		{
			case 0:lcd_set_pos(0,0);lcd_printf(">");lcd_set_pos(0,0);break;
			case 1:lcd_set_pos(0,6);lcd_printf(">");lcd_set_pos(1,0);break;
			case 2:lcd_set_pos(0,9);lcd_printf(">");lcd_set_pos(0,0);break;
			case 3:lcd_set_pos(1,6);lcd_printf(">");lcd_set_pos(1,0);break;
			case 4:lcd_set_pos(1,9);lcd_printf(">");lcd_set_pos(0,0);break;
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
			if(pos<4)pos++;
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
void lcd_custom_pid_edit_time()
{
//	s16 tmp;
//	u8 edit_pos;
	u8 edit_pos_tmp;	
	if(newmenuitem)
	{
		lcd_clear();
		// Line 0
		lcd_set_pos(0,1);
		if(MenuRegs.Schedule_Enable)lcd_printf("ON");
		else lcd_printf("OFF");			
		lcd_set_pos(0,7);ByteToStrFillZero(lcd_txt,&MenuRegs.Schedule_Time[0].field.Hour,0,2,'0');lcd_txt[9]='.';lcd_txt[10]=0;lcd_printf(lcd_txt);
		lcd_set_pos(0,10);ByteToStrFillZero(lcd_txt,&MenuRegs.Schedule_Time[0].field.Minute,0,2,'0');lcd_printf(lcd_txt);
		lcd_set_pos(1,7);ByteToStrFillZero(lcd_txt,&MenuRegs.Schedule_Time[1].field.Hour,0,2,'0');lcd_txt[9]='.';lcd_txt[10]=0;lcd_printf(lcd_txt);
		lcd_set_pos(1,10);ByteToStrFillZero(lcd_txt,&MenuRegs.Schedule_Time[1].field.Minute,0,2,'0');lcd_printf(lcd_txt);
	
		edit_pos_tmp=pos;
		lcd_set_pos(0,0);lcd_printf(" ");
		lcd_set_pos(0,6);lcd_printf(" ");
		lcd_set_pos(0,9);lcd_printf(".");
		lcd_set_pos(1,6);lcd_printf(" ");
		lcd_set_pos(1,9);lcd_printf(".");
		switch(edit_pos_tmp)
		{
			case 0:lcd_set_pos(0,0);lcd_printf(">");lcd_set_pos(0,0);break;
			case 1:lcd_set_pos(0,6);lcd_printf(">");lcd_set_pos(0,6);break;
			case 2:lcd_set_pos(0,9);lcd_printf(">");lcd_set_pos(0,9);break;
			case 3:lcd_set_pos(1,6);lcd_printf(">");lcd_set_pos(1,6);break;
			case 4:lcd_set_pos(1,9);lcd_printf(">");lcd_set_pos(1,9);break;
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
				case 0:if(MenuRegs.Schedule_Enable)MenuRegs.Schedule_Enable=0;else MenuRegs.Schedule_Enable=1; break;
				case 1:if(MenuRegs.Schedule_Time[0].field.Hour<23)MenuRegs.Schedule_Time[0].field.Hour+=1;break;	
				case 2:if(MenuRegs.Schedule_Time[0].field.Minute<59)MenuRegs.Schedule_Time[0].field.Minute+=1;break;	
				case 3:if(MenuRegs.Schedule_Time[1].field.Hour<23)MenuRegs.Schedule_Time[1].field.Hour+=1;break;	
				case 4:if(MenuRegs.Schedule_Time[1].field.Minute<59)MenuRegs.Schedule_Time[1].field.Minute+=1;break;	
			}
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{
			switch(pos)		
			{
				case 0:if(MenuRegs.Schedule_Enable)MenuRegs.Schedule_Enable=0;else MenuRegs.Schedule_Enable=1; break;
				case 1:if(MenuRegs.Schedule_Time[0].field.Hour>0)MenuRegs.Schedule_Time[0].field.Hour-=1;break;	
				case 2:if(MenuRegs.Schedule_Time[0].field.Minute>0)MenuRegs.Schedule_Time[0].field.Minute-=1;break;	
				case 3:if(MenuRegs.Schedule_Time[1].field.Hour>0)MenuRegs.Schedule_Time[1].field.Hour-=1;break;	
				case 4:if(MenuRegs.Schedule_Time[1].field.Minute>0)MenuRegs.Schedule_Time[1].field.Minute-=1;break;	
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
			if(Menu[Menu_Pos].UpItem != 0)
			{
				Menu_Pos=Menu_Pos+Menu[Menu_Pos].UpItem;
				LCD_Cur_Pos=0;
				lcd_clear();
//				pos=0;
			}	
			params_store();
			key3=2;			
		}	
}
//-----------------------------------------------------------------------------------
