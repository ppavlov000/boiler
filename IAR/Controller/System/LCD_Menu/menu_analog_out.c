//-----------------------------------------------------------------------------------
#include "..\main.h" 
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
in_flash u8	eng_aout_dic[2][20]=
{ 
	"Analog outputs",			//0
	"AO channels",				//1
};
in_flash u8	ru_aout_dic[2][20]=
{ 
	"Аналог выходы",			//0
	"AO каналы",			//1
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void lcd_menu_show_analog_out()
{
	u8 tmp;
	if(newmenuitem)
	{		
		lcd_clear();		
		lcd_set_pos(0,0);
		tmp=pos;
		lcd_printf("AO");
		ByteToStr(lcd_txt,&tmp,1);
		lcd_printf(lcd_txt);				
		lcd_printf("=");		
		WordToStr(lcd_txt,&io.aoutput[tmp],1);
		lcd_printf(lcd_txt);					
		
		tmp=pos+1;				
		if(tmp<io.num_ao)
		{
			lcd_set_pos(1,0);
			lcd_printf("AO");
			ByteToStr(lcd_txt,&tmp,1);
			lcd_printf(lcd_txt);		
			lcd_printf("=");
			WordToStr(lcd_txt,&io.aoutput[tmp],1);
			lcd_printf(lcd_txt);					
		}				
		LCD_Time=1000;			
	}
	newmenuitem=0;
	if(LCD_Time==0)newmenuitem=1;
	// Up arrow
		if(key0==1)
		{
			if(pos>=4)pos-=4;
//			else pos=io.num_ai-1;
			else 
			{
				if(LCDMenuPtr->PreviosItem!=NULL)
				{
					newmenuitem=1;
					LCDMenuPtr=(TLCDMenuItem*)LCDMenuPtr->PreviosItem;
					pos=0;	
				}
			}
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{
			if(pos<(io.num_ai-4))pos+=4;
//			else pos=0;
			else
			{
				if(LCDMenuPtr->NextItem!=NULL)
				{
					newmenuitem=1;
					LCDMenuPtr=(TLCDMenuItem*)LCDMenuPtr->NextItem;
					pos=0;									
				}				
			}
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
void lcd_menu_analog_out()
{
	if(newmenuitem)
	{
		lcd_clear();		
		lcd_set_pos(0,0);
		if(MenuRegs.lang==0)
			lcd_printf_P(eng_aout_dic[0]);			
		if(MenuRegs.lang==1)
			lcd_printf_P(ru_aout_dic[0]);			
//		lcd_printf("Analog outputs");
		lcd_set_pos(1,0);
//		lcd_printf("AO channels");	
		if(MenuRegs.lang==0)
			lcd_printf_P(eng_aout_dic[1]);
		if(MenuRegs.lang==1)
			lcd_printf_P(ru_aout_dic[1]);
		pos=0;			
	}
	newmenuitem=0;	
}
//-----------------------------------------------------------------------------------
