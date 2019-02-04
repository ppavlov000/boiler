//-----------------------------------------------------------------------------------
#include "..\main.h" 
//-----------------------------------------------------------------------------------
in_flash u8	eng_pass_dic[6][17]=
{ 
	"Password",		 	//0
	"Correct",			//1
	"Wrong",			//2	
	"*****",			//3
	"limited mode",		//4		
	"full mode",		//5	

};
in_flash u8	ru_pass_dic[6][17]=
{ 
	"������   ",		//0
	"���������",		//1
	"�����������",		//2	
	"*****",			//3
	"������������ ���",	//4	
	"������ ������",	//5			
};

u8 pressed=0;
u8 password[5];
extern TLCDMenuItem _LCD_Run_Full;
extern TLCDMenuItem _LCD_Run_Limited;
//-----------------------------------------------------------------------------------
void lcd_enter_password()
{
//	s16 tmp;
	u8 i;
//	u8 edit_pos_tmp;	
	if(MenuRegs.password==0)
	{
		write_command(0x0c);		
		Delay_mks(1);											
		pos=0;
		edit_pos=0;
		menu_stat=0;
		LCDMenuPtr=&_LCD_Run_Full;						
		newmenuitem=1;	
		password_lvl=2;	
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
				//if(LCDMenuPtr->SubItem!=NULL)
				{				
					write_command(0x0c);		
					Delay_mks(1);											
					pos=0;
					edit_pos=0;
					menu_stat=0;
					LCDMenuPtr=&_LCD_Run_Full;	
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
//					LCDMenuPtr=&_LCD_Run_Limited;	
					LCDMenuPtr=&_LCD_Run_Full;	
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
