//-----------------------------------------------------------------------------------
#include "..\..\..\System\main.h"
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
in_flash u8	eng_prmode_dic[2][20]=
{
	"AUTO Mode",				//0
	"MANUAL Mode",				//0	
};
in_flash u8	ru_prmode_dic[2][20]=
{
	"ÀÂÒÎ ðåæèì",				//0
	"ÐÓ×Í ðåæèì",				//0	
};	
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void lcd_menu_choose_prmode()
{
	s16 tmp;
//	u8 edit_pos;
	u8 edit_pos_tmp;	
	if(newmenuitem)
	{
		lcd_clear();
		memset(lcd_txt, 0, sizeof(lcd_txt));		
		tmp=pos & 0xfe;		
		lcd_set_pos(0,1);
		if(MenuRegs.lang==0)__sprintf_P(lcd_txt,eng_prmode_dic[tmp]);			
		if(MenuRegs.lang==1)__sprintf_P(lcd_txt,ru_prmode_dic[tmp]);			
		lcd_printf(lcd_txt);	
		tmp=(pos & 0xfe) +1;	
		if(tmp<2)
		{		
			lcd_set_pos(1,1);
			if(MenuRegs.lang==0)__sprintf_P(lcd_txt,eng_prmode_dic[tmp]);			
			if(MenuRegs.lang==1)__sprintf_P(lcd_txt,ru_prmode_dic[tmp]);			
			lcd_printf(lcd_txt);									
		}

		edit_pos_tmp=pos & 0x01;		
		lcd_set_pos(0,0);lcd_printf(" ");
		lcd_set_pos(1,0);lcd_printf(" ");
		switch(edit_pos_tmp)
		{
			case 0:lcd_set_pos(0,0);lcd_printf(">");break;
			case 1:lcd_set_pos(1,0);lcd_printf(">");break;
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
			if(pos<(2-1))pos++;
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
				newmenuitem=1;	
				lcd_clear();
				pos=0;				
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
				newmenuitem=1;	
				MenuRegs.Manual_Mode=pos;
				params_store();
				lcd_clear();
				pos=0;				
			}			
			key3=2;			
		}	
}

//-----------------------------------------------------------------------------------
