//-----------------------------------------------------------------------------------
#include "..\main.h" 
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
in_flash u8	eng_din_dic[2][20]=
{ 
	"Digital inputs",			//0
	"DI channels",				//1
};
in_flash u8	ru_din_dic[2][20]=
{ 
	"Цифровые входы",		//0
	"DI каналы",			//1
};
//-----------------------------------------------------------------------------------
void lcd_menu_show_digital_in()
{

	u8 tmp;
	u16 t;
	if(newmenuitem)
	{
		lcd_clear();		
		lcd_set_pos(0,0);
		tmp=pos;
		lcd_printf("DI");
		ByteToStr(lcd_txt,&tmp,1);
		lcd_printf(lcd_txt);				
		lcd_printf("=");	
		t=1<<tmp;			
		if(io.din & t) lcd_printf("1");	else lcd_printf("0");
		
		tmp=pos+1;				
		if(tmp<io.num_di)
		{
			lcd_set_pos(1,0);
			lcd_printf("DI");
			ByteToStr(lcd_txt,&tmp,1);
			lcd_printf(lcd_txt);		
			lcd_printf("=");		
			t=1<<tmp;			
			if(io.din & t) lcd_printf("1");	else lcd_printf("0");			
		}
/*		
		tmp=pos+2;						
		if(tmp<io.num_di)
		{		
			lcd_set_pos(0,8);
			lcd_printf("DI");
			ByteToStr(lcd_txt,&tmp,1);
			lcd_printf(lcd_txt);				
			lcd_printf("=");		
			t=1<<tmp;			
			if(io.din & t) lcd_printf("1");	else lcd_printf("0");						
		}
		
		tmp=pos+3;						
		if(tmp<io.num_di)
		{		
			lcd_set_pos(1,8);
//			lcd_printf("DI");
			ByteToStr(lcd_txt,&tmp,1);
			lcd_printf(lcd_txt);				
			lcd_printf("=");		
			t=1<<tmp;			
			if(io.din & t) lcd_printf("1");	else lcd_printf("0");						
		}
*/		
		LCD_Time=1000;			
	}
	newmenuitem=0;
	if(LCD_Time==0)newmenuitem=1;
	// Up arrow
		if(key0==1)
		{
			if(pos>=2)pos-=2;
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
			if(pos<(io.num_di-2))pos+=2;
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
void lcd_menu_digital_in()
{
	if(newmenuitem)
	{
		lcd_clear();		
		lcd_set_pos(0,0);
//		lcd_printf("Digital inputs");
		if(MenuRegs.lang==0)
			lcd_printf_P(eng_din_dic[0]);			
		if(MenuRegs.lang==1)
			lcd_printf_P(ru_din_dic[0]);			
		lcd_set_pos(1,0);
//		lcd_printf("DI channels");		
		if(MenuRegs.lang==0)
			lcd_printf_P(eng_din_dic[1]);
		if(MenuRegs.lang==1)
			lcd_printf_P(ru_din_dic[1]);
		pos=0;		
	}
	newmenuitem=0;	
}
//-----------------------------------------------------------------------------------
