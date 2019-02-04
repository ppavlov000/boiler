//-----------------------------------------------------------------------------------
#include "..\..\..\System\main.h"
//-----------------------------------------------------------------------------------
#define MAX_INFO_LINES 8
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TMenuRecodr in_flash* menu_str;
in_flash TMenuRecodr	eng_info_str[8]=
{
	"EastLabs",			0,		//0
	"controller",		0,		//1
	"model:",			0,		//2	
	"HW    ",			0,		//3
	"SW    ",			0,		//4	
	"Issue date ",		0,		//5
	"peter_pavlov",    0,		//7	
	"  @mail.ru",		0,		//8		
	
};
in_flash TMenuRecodr	ru_info_str[8]=
{
	"ИстЛабс",			0,		//0
	"контроллер",		0,		//1
	"модель:",			0,		//2
	"Плата ",			0,		//3
	"Софт  ",			0,		//4
	"Дата выпуска ",	0,		//5
	"peter_pavlov",    0,		//7	
	"  @mail.ru",		0,		//8		
};
in_flash u8 empty_line[LCD_MAX_SYMBOLS]={"               "};
//-----------------------------------------------------------------------------------
void lcd_show_info()
{
//	s16 tmp;
	u8 i,j;
	u8 pos_old;
//	u8 edit_pos;
//	u8 show_pos_tmp;	
	if(newmenuitem)
	{
		if(MenuRegs.lang==0)
			menu_str=&eng_info_str[0];
		if(MenuRegs.lang==1)
			menu_str=&ru_info_str[0];		
		for(i=pos;i<(MAX_INFO_LINES-2);i++)
			if(menu_str[i].lvl<=password_lvl)
			{
				pos=i;
				break;
			}	
			
		lcd_clear();
		memset(lcd_txt, 0, sizeof(lcd_txt));				
		for(i=pos;i<pos+2;i++)					
		{
			lcd_set_pos(i-pos,0);
			if(i<MAX_INFO_LINES)	
			{						
				if(menu_str[i].lvl>password_lvl)
				{
					pos_old=i;
					for(j=i+1;j<(MAX_INFO_LINES);j++)
						if(menu_str[j].lvl<=password_lvl)
						{
							i=j;
							break;
						}
				}	
				if(menu_str[i].lvl<=password_lvl)
				{				
					__sprintf_P(lcd_txt,menu_str[i].str);					
					lcd_printf(lcd_txt);	
					switch(i)
					{
						case 3:
							FGet(HAPP_FLASH_START+THW_LOC,(u8*)&ltmp,4);	
							LongToStr(lcd_txt,&ltmp,1);
							lcd_set_pos(i-pos,8);
							lcd_printf(lcd_txt);
						break;
						case 4:
							FGet(HAPP_FLASH_START+TSW_LOC,(u8*)&ltmp,4);	
							LongToStr(lcd_txt,&ltmp,1);
							lcd_set_pos(i-pos,8);
							lcd_printf(lcd_txt);
						break;				
					}
				}
				else
				{
					__sprintf_P(lcd_txt,empty_line);				
					lcd_printf(lcd_txt);			
				}	
			}
			else
			{
				__sprintf_P(lcd_txt,empty_line);				
				lcd_printf(lcd_txt);			
			}			
		}
	}
	newmenuitem=0;	
		// -------- Keys --------------//
		// Up arrow
		if(key0==1)
		{
			pos_old=pos;
			if(pos!=0)pos--;
			for(i=pos;i!=0;i--)
				if(menu_str[i].lvl<=password_lvl)
				{
					pos=i;
					break;
				}
			if(menu_str[pos].lvl>password_lvl)pos=pos_old;
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{
			pos_old=pos;
			if(pos<(MAX_INFO_LINES-2))pos++;
			for(i=pos;i<(MAX_INFO_LINES-2);i++)
				if(menu_str[i].lvl<=password_lvl)
				{
					pos=i;
					break;
				}
			if(menu_str[pos].lvl>password_lvl)pos=pos_old;
			
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
				newmenuitem=1;	
				lcd_clear();
			}	
			key2=2;			
		}
		// Enter		
		if(key3==1)
		{
			if(Menu[Menu_Pos].SubItem != 0)
			{
				Menu_Pos=Menu_Pos+Menu[Menu_Pos].SubItem;
				LCD_Cur_Pos=0;
				pos=0;
				newmenuitem=1;	
				lcd_clear();
			}		
			key3=2;			
		}	
}

//-----------------------------------------------------------------------------------
