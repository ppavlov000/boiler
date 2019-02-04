//-----------------------------------------------------------------------------------
#include "..\main.h" 
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
in_flash u8	eng_ain_dic[2][20]=
{ 
	"Analog inputs",			//0
	"AI channels",				//1
};
in_flash u8	ru_ain_dic[2][20]=
{ 
	"Аналог входы",			//0
	"AI каналы",			//1
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void lcd_menu_show_analog_in()
{
	u8 tmp;
	if(newmenuitem)
	{
		lcd_clear();		
		lcd_set_pos(0,0);
		tmp=pos;
		lcd_printf("AI");
		ByteToStr(lcd_txt,&tmp,1);
		lcd_printf(lcd_txt);				
		lcd_printf("=");		
		ShowTemperature(lcd_txt,&io.ainput[tmp]);
		lcd_printf(lcd_txt);					
		
		tmp=pos+1;				
		if(tmp<io.num_ai)
		{
			lcd_set_pos(1,0);
			lcd_printf("AI");
			ByteToStr(lcd_txt,&tmp,1);
			lcd_printf(lcd_txt);		
			lcd_printf("=");	
			ShowTemperature(lcd_txt,&io.ainput[tmp]);
			lcd_printf(lcd_txt);									
		}		
		LCD_Time=500;			
	}
	newmenuitem=0;
	if(LCD_Time==0)newmenuitem=1;
	// Up arrow
		if(key0==1)
		{
			if(pos>=2)pos-=2;
//			pos+=2;
//			if(pos>io.num_ai-1)pos-=4;
//			else pos=io.num_ai-1;
/*			else 
			{
				if(LCDMenuPtr->PreviosItem!=NULL)
				{
					newmenuitem=1;
					LCDMenuPtr=LCDMenuPtr->PreviosItem;			
					pos=0;	
				}
			}
*/
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{
			if(pos<(io.num_ai-2))pos+=2;
//			else pos=0;
/*			else
			{
				if(LCDMenuPtr->NextItem!=NULL)
				{
					newmenuitem=1;
					LCDMenuPtr=LCDMenuPtr->NextItem;	
					pos=0;									
				}				
			}
*/
			newmenuitem=1;
			key1=2;
		}
		// Esc
		if(key2==1)
		{
			if(LCDMenuPtr->UpItem!=NULL)
			{
				LCDMenuPtr=(TLCDMenuItem*)LCDMenuPtr->UpItem;						
				newmenuitem=1;				
			}
			key2=2;			
		}
		// Enter		
		if(key3==1)
		{
			key3=2;			
		}	
}
//-----------------------------------------------------------------------------------
void lcd_menu_analog_in()
{
	if(newmenuitem)
	{
		lcd_clear();		
		lcd_set_pos(0,0);
		if(MenuRegs.lang==0)
			__sprintf_P(lcd_txt,eng_ain_dic[0]);			
		if(MenuRegs.lang==1)
			__sprintf_P(lcd_txt,ru_ain_dic[0]);	
		lcd_printf(lcd_txt);			
//		lcd_printf("Analog inputs");
		lcd_set_pos(1,0);
//		lcd_printf("AI channels");		
		if(MenuRegs.lang==0)
			__sprintf_P(lcd_txt,eng_ain_dic[1]);			
		if(MenuRegs.lang==1)
			__sprintf_P(lcd_txt,ru_ain_dic[1]);	
		lcd_printf(lcd_txt);			
		pos=0;
	}
	newmenuitem=0;	
}
//-----------------------------------------------------------------------------------
