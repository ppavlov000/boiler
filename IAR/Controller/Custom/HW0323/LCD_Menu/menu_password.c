//-----------------------------------------------------------------------------------
#include "..\..\..\System\main.h"
//-----------------------------------------------------------------------------------
in_flash u8	eng_pass_dic[8][17]=
{
	"Password",		 	//0
	"Correct",			//1
	"Wrong",			//2	
	"*****",			//3
	"limited mode",		//4		
	"full mode",		//5	
	"ENABLE",			//6
	"DISABLE",			//7	

};
in_flash u8	ru_pass_dic[8][17]=
{
	"Пароль   ",		//0
	"Правильно",		//1
	"Неправильно",		//2	
	"*****",			//3
	"ограниченный реж",	//4	
	"полный доступ",	//5			
	"включить",			//6
	"выключит",			//7		
};

u8 pressed=0;
u8 password[5];
u8 pass_changed=0;

extern u8 LCD_Cur_Pos;
extern s8 LCD_Shw_Pos;
extern u8 Active_Item;
extern u8 Active_PID;
extern u8 Active_PID_Item;

u8 get_prev_menu();
u8 get_next_menu();
u8 get_sub_menu();
u8 get_up_menu();
//extern TLCDMenuItem _LCD_Run_Full;
//extern TLCDMenuItem _LCD_Run_Limited;
//-----------------------------------------------------------------------------------
void rp02()
{
//	s16 tmp;
	u8 i;
//	u8 edit_pos_tmp;	
	if(MenuRegs.password==0)
	{
		write_command(0x0c);		
		Delay_mks(1);											
//		pos=0;
//		edit_pos=0;
//		menu_stat=0;
		newmenuitem=1;	
		password_lvl=1;	
		Menu_Pos=Menu_Pos+Menu[Menu_Pos].NextItem;
		lcd_clear();
		return;
	}
	if(newmenuitem)
	{
		lcd_clear();
		if(menu_stat==1)
		{
			write_command(0x0c);		
			Delay_mks(1);			
			lcd_clear();			
			if(MenuRegs.lang==0)
			{
				lcd_set_pos(0,0);
				lcd_printf_P(eng_pass_dic[1]);			
				lcd_set_pos(1,0);
				lcd_printf_P(eng_pass_dic[5]);			
			}
			if(MenuRegs.lang==1)
			{
				lcd_set_pos(0,0);
				lcd_printf_P(ru_pass_dic[1]);			
				lcd_set_pos(1,0);
				lcd_printf_P(ru_pass_dic[5]);			
			}							
			LCD_Time=1000;					
		}
		if(menu_stat==2)
		{
			write_command(0x0c);		
			Delay_mks(1);			
			lcd_clear();			
			if(MenuRegs.lang==0)
			{
				lcd_set_pos(0,0);
				lcd_printf_P(eng_pass_dic[2]);			
				lcd_set_pos(1,0);
				lcd_printf_P(eng_pass_dic[4]);			
			}
			if(MenuRegs.lang==1)
			{
				lcd_set_pos(0,0);
				lcd_printf_P(ru_pass_dic[2]);			
				lcd_set_pos(1,0);
				lcd_printf_P(ru_pass_dic[4]);			
			}											
			LCD_Time=1000;					
		}		
		if(menu_stat==0)
		{		
			// Line 0
			lcd_set_pos(0,0);
			if(MenuRegs.lang==0)
				__sprintf_P(lcd_txt,eng_pass_dic[0]);			
			if(MenuRegs.lang==1)
				__sprintf_P(lcd_txt,ru_pass_dic[0]);	
			lcd_printf(lcd_txt);
			
			lcd_set_pos(0,10);
			if(MenuRegs.lang==0)
				__sprintf_P(lcd_txt,eng_pass_dic[3]);			
			if(MenuRegs.lang==1)
				__sprintf_P(lcd_txt,ru_pass_dic[3]);		
			lcd_printf(lcd_txt);	
			
			write_command(0x0D);		
			Delay_mks(1);		
//			edit_pos_tmp=pos;
			lcd_set_pos(0,10);lcd_printf_P(eng_pass_dic[3]);
			lcd_set_pos(0,10+pos);
			ByteToStr(lcd_txt,(u8*)&edit_pos,0);
			lcd_printf(lcd_txt);
			lcd_set_pos(0,10+pos);
			LCD_Time=5000;	
		}
	}		
	newmenuitem=0;	
	if(LCD_Time==0)
	{
		newmenuitem=1;	
		switch(menu_stat)
		{
			case 0:
				menu_stat=2;
				newmenuitem=1;
				password_lvl=0;	
			break;
			case 1:
				{				
					write_command(0x0c);		
					Delay_mks(1);											
					pos=0;
					edit_pos=0;
					menu_stat=0;
					Menu_Pos=Menu_Pos+Menu[Menu_Pos].NextItem;
					menu_stat=0;
					lcd_clear();
//					password_lvl=1;					
					newmenuitem=1;		
				}				
			break;	
			case 2:
				//if(LCDMenuPtr->SubItem!=NULL)
				{		
					write_command(0x0c);		
					Delay_mks(1);							
					pos=0;
					edit_pos=0;
					menu_stat=0;
//					LCDMenuPtr=&_LCD_Run_Full;	
					Menu_Pos=Menu_Pos+Menu[Menu_Pos].NextItem;	
					lcd_clear();
					menu_stat=0;
//					password_lvl=0;					
					newmenuitem=1;		
				}				
			break;			
		}	
		newmenuitem=1;	
		LCD_Time=1000;
	}			
		// -------- Keys --------------//
		// Up arrow
		if(key0==1)
		{
			if(edit_pos<9)edit_pos++;		
			newmenuitem=1;
			LCD_Time=5000;	
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{
			if(edit_pos!=0)edit_pos--;
			newmenuitem=1;
			key1=2;
		}
		// Esc
		if(key2==1)
		{			
			key2=2;		
			LCD_Time=5000;				
			pass_match=0;	
			if(pos!=0)
			{
				pos--;
				newmenuitem=1;			
			}
			else menu_stat=2;	
			
		}
		// Enter		
		if(key3==1)
		{		
			if(pos<=4)
			{
				password[pos]=edit_pos;
				edit_pos=0;								
				pos++;
			}
			if(pos>4)
			{
				pos=4;			
				menu_stat=2;
				password_lvl=0;
				// Check user
				pass_match=1;
				for(i=0;i<5;i++)
				{
					if(password[i]!=MenuRegs.pass_user[i])
						pass_match=0;			
				}
				if(pass_match!=0)
				{
					menu_stat=1;		
					password_lvl=1;
				}
				// Check admin
				pass_match=1;
				for(i=0;i<5;i++)
				{
					if(password[i]!=MenuRegs.pass_admin[i])
						pass_match=0;			
				}
				if(pass_match!=0)
				{
					menu_stat=1;		
					password_lvl=2;
				}
			}
			newmenuitem=1;		
			LCD_Time=5000;					
			key3=2;			
		}	
}
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void rp_set_pass()
{
//	s16 tmp;
	u8 i;
//	u8 edit_pos_tmp;	
	if(newmenuitem)
	{
		lcd_clear();
		if(menu_stat==1)
		{
			write_command(0x0c);		
			Delay_mks(1);			
			lcd_clear();			
			if(MenuRegs.lang==0)
			{
				lcd_set_pos(0,0);
				lcd_printf_P(eng_pass_dic[1]);			
				lcd_set_pos(1,0);
				lcd_printf_P(eng_pass_dic[5]);			
			}
			if(MenuRegs.lang==1)
			{
				lcd_set_pos(0,0);
				lcd_printf_P(ru_pass_dic[1]);			
				lcd_set_pos(1,0);
				lcd_printf_P(ru_pass_dic[5]);			
			}							
			LCD_Time=1000;					
		}
		if(menu_stat==2)
		{
			write_command(0x0c);		
			Delay_mks(1);			
			lcd_clear();			
			if(MenuRegs.lang==0)
			{
				lcd_set_pos(0,0);
				lcd_printf_P(eng_pass_dic[2]);			
				lcd_set_pos(1,0);
				lcd_printf_P(eng_pass_dic[4]);			
			}
			if(MenuRegs.lang==1)
			{
				lcd_set_pos(0,0);
				lcd_printf_P(ru_pass_dic[2]);			
				lcd_set_pos(1,0);
				lcd_printf_P(ru_pass_dic[4]);			
			}											
			LCD_Time=1000;					
		}		
		if(menu_stat==0)
		{		
			// Line 0
			lcd_set_pos(0,0);
			if(MenuRegs.lang==0)
				__sprintf_P(lcd_txt,eng_pass_dic[0]);			
			if(MenuRegs.lang==1)
				__sprintf_P(lcd_txt,ru_pass_dic[0]);	
			lcd_printf(lcd_txt);
			
			lcd_set_pos(0,10);
			if(MenuRegs.lang==0)
				__sprintf_P(lcd_txt,eng_pass_dic[3]);			
			if(MenuRegs.lang==1)
				__sprintf_P(lcd_txt,ru_pass_dic[3]);		
			lcd_printf(lcd_txt);	
			
			write_command(0x0D);		
			Delay_mks(1);		
//			edit_pos_tmp=pos;
			lcd_set_pos(0,10);lcd_printf_P(eng_pass_dic[3]);
			lcd_set_pos(0,10+pos);
			ByteToStr(lcd_txt,(u8*)&edit_pos,0);
			lcd_printf(lcd_txt);
			lcd_set_pos(0,10+pos);
			LCD_Time=5000;	
		}
	}		
	newmenuitem=0;	
	if(LCD_Time==0)
	{
		newmenuitem=1;	
		switch(menu_stat)
		{
			case 0:
				menu_stat=2;
				newmenuitem=1;
				password_lvl=0;	
			break;
			case 1:
				//if(LCDMenuPtr->SubItem!=NULL)
				{				
					write_command(0x0c);		
					Delay_mks(1);											
					pos=0;
					edit_pos=0;
					menu_stat=0;
					//LCDMenuPtr=&_LCD_Run_Full;	
					Menu_Pos=Menu_Pos+Menu[Menu_Pos].UpItem;
					lcd_clear();
//					password_lvl=1;					
					newmenuitem=1;		
				}				
			break;	
			case 2:
				//if(LCDMenuPtr->SubItem!=NULL)
				{		
					write_command(0x0c);		
					Delay_mks(1);							
					pos=0;
					edit_pos=0;
					menu_stat=0;
//					LCDMenuPtr=&_LCD_Run_Full;	
					Menu_Pos=Menu_Pos+Menu[Menu_Pos].UpItem;	
					lcd_clear();
//					password_lvl=0;					
					newmenuitem=1;		
				}				
			break;			
		}	
		newmenuitem=1;	
		LCD_Time=1000;
	}			
		// -------- Keys --------------//
		// Up arrow
		if(key0==1)
		{
			if(edit_pos<9)edit_pos++;		
			newmenuitem=1;
			LCD_Time=5000;	
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{
			if(edit_pos!=0)edit_pos--;
			newmenuitem=1;
			key1=2;
		}
		// Esc
		if(key2==1)
		{			
			key2=2;		
			LCD_Time=5000;				
			pass_match=0;	
			if(pos!=0)
			{
				pos--;
				newmenuitem=1;			
			}
			else menu_stat=2;	
			
		}
		// Enter		
		if(key3==1)
		{		
			if(pos<=4)
			{
				password[pos]=edit_pos;
				edit_pos=0;								
				pos++;
			}
			if(pos>4)
			{
				pos=4;			
				menu_stat=2;
				password_lvl=0;
				// Check user
				pass_match=1;
				for(i=0;i<5;i++)
				{
					if(password[i]!=MenuRegs.pass_user[i])
						pass_match=0;			
				}
				if(pass_match!=0)
				{
					menu_stat=1;		
					password_lvl=1;
				}
				// Check admin
				pass_match=1;
				for(i=0;i<5;i++)
				{
					if(password[i]!=MenuRegs.pass_admin[i])
						pass_match=0;			
				}
				if(pass_match!=0)
				{
					menu_stat=1;		
					password_lvl=2;
				}
			}
			newmenuitem=1;		
			LCD_Time=5000;					
			key3=2;			
		}	
}
//-----------------------------------------------------------------------------------
void rp_pass_ena()
{
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		if(MenuRegs.lang==0)
		{
			if(MenuRegs.password==0)
				__sprintf_P(lcd_txt,eng_pass_dic[6]);
			if(MenuRegs.password==1)
				__sprintf_P(lcd_txt,eng_pass_dic[7]);			
		}
		if(MenuRegs.lang==1)
		{
			if(MenuRegs.password==0)
				__sprintf_P(lcd_txt,ru_pass_dic[6]);
			if(MenuRegs.password==1)
				__sprintf_P(lcd_txt,ru_pass_dic[7]);			
		}
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
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
			if((pass_changed)&&(MenuRegs.password==1))
			{
				Menu_Pos=3;
				LCD_Cur_Pos=0;
				lcd_clear();	
			}
			else
			{
				if(get_up_menu() != 0)			
				{
					LCD_Cur_Pos=0;
					lcd_clear();
				}
			}
//			if(pass_changed)params_store();							
			LCD_Time=0;	
			newmenuitem=1;
			key2=2;			
		}
		// Enter		
		if(key3==1)
		{
			if(MenuRegs.password==0)
			{
				MenuRegs.password=1;
				password_lvl=0;
				
			}
			else
			{
				MenuRegs.password=0;
				password_lvl=1;
			}
			pass_changed=1;
			newmenuitem=1;			
			key3=2;			
		}
	}	
}
//-----------------------------------------------------------------------------------
