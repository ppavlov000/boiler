//-----------------------------------------------------------------------------------
#include "..\main.h" 
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
in_flash u8	eng_dout_dic[2][20]=
{ 
	"Digital outputs",			//0
	"DO channels",				//1
};
in_flash u8	ru_dout_dic[2][20]=
{ 
	"Цифровые выходы",		//0
	"DO каналы",			//1
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void lcd_menu_show_digital_out()
{
	u8 tmp;
	u32 t;
	if(newmenuitem)
	{
		lcd_clear();		
		lcd_set_pos(0,0);
		tmp=pos;
		lcd_printf("DO");
		ByteToStr(lcd_txt,&tmp,1);
		lcd_printf(lcd_txt);				
		lcd_printf("=");	
		t=1;		
		t=t<<tmp;			
		if(io.dout & t) lcd_printf("1");	else lcd_printf("0");
		
		tmp=pos+1;				
		if(tmp<io.num_do)
		{
			lcd_set_pos(1,0);
			lcd_printf("DO");
			ByteToStr(lcd_txt,&tmp,1);
			lcd_printf(lcd_txt);		
			lcd_printf("=");		
			t=1;		
			t=t<<tmp;			
			if(io.dout & t) lcd_printf("1");	else lcd_printf("0");			
		}
/*		
		tmp=pos+2;						
		if(tmp<io.num_do)
		{		
			lcd_set_pos(0,8);
			lcd_printf("DO");
			ByteToStr(lcd_txt,&tmp,1);
			lcd_printf(lcd_txt);				
			lcd_printf("=");		
			t=1;		
			t=t<<tmp;			
			if(io.dout & t) lcd_printf("1");	else lcd_printf("0");						
		}
		
		tmp=pos+3;						
		if(tmp<io.num_do)
		{		
			lcd_set_pos(1,8);
			lcd_printf("DO");
			ByteToStr(lcd_txt,&tmp,1);
			lcd_printf(lcd_txt);				
			lcd_printf("=");		
			t=1;		
			t=t<<tmp;			
			if(io.dout & t) lcd_printf("1");	else lcd_printf("0");						
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
			if(pos<(io.num_do-2))pos+=2;
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
			if(LCDMenuPtr->SubItem!=NULL)
			{
				edit_pos=pos;			
				newmenuitem=1;
				LCDMenuPtr=(TLCDMenuItem*)LCDMenuPtr->SubItem;		
			}		
			key3=2;			
		}	
}
//-----------------------------------------------------------------------------------
void lcd_menu_edit_digital_out()
{
	u8 tmp;
	u32 t;
	u8 edit_pos_tmp;	
	u32 io_tmp;	
		
//	edit_pos=pos;
	if(newmenuitem)
	{
		lcd_clear();		
		lcd_set_pos(0,0);
		tmp=pos;
		lcd_printf("DO");
		ByteToStr(lcd_txt,&tmp,1);
		lcd_printf(lcd_txt);				
		lcd_printf("=");	
		t=1;		
		t=t<<tmp;			
		if(io.dout & t) lcd_printf("1");	else lcd_printf("0");
		
		tmp=pos+1;				
		if(tmp<io.num_do)
		{
			lcd_set_pos(1,0);
			lcd_printf("DO");
			ByteToStr(lcd_txt,&tmp,1);
			lcd_printf(lcd_txt);		
			lcd_printf("=");		
			t=1;		
			t=t<<tmp;			
			if(io.dout & t) lcd_printf("1");	else lcd_printf("0");			
		}
/*		
		tmp=pos+2;						
		if(tmp<io.num_do)
		{		
			lcd_set_pos(0,8);
//			lcd_printf("DO");
			ByteToStr(lcd_txt,&tmp,1);
			lcd_printf(lcd_txt);				
			lcd_printf("=");		
			t=1;		
			t=t<<tmp;			
			if(io.dout & t) lcd_printf("1");	else lcd_printf("0");						
		}
		
		tmp=pos+3;						
		if(tmp<io.num_do)
		{		
			lcd_set_pos(1,8);
//			lcd_printf("DO");
			ByteToStr(lcd_txt,&tmp,1);
			lcd_printf(lcd_txt);				
			lcd_printf("=");
			t=1;		
			t=t<<tmp;			
			if(io.dout & t) lcd_printf("1");	else lcd_printf("0");						
		}	
*/
		write_command(0x0f);		
		Delay_mks(1);
		edit_pos_tmp=edit_pos & 0x01;		
		switch(edit_pos_tmp)
		{
			case 0:lcd_set_pos(0,5);break;
			case 1:lcd_set_pos(1,5);break;
//			case 2:lcd_set_pos(0,11);break;
//			case 3:lcd_set_pos(1,11);;break;									
		}		
		newmenuitem=0;		
	}	
		// -------- EDIT --------------]
		// Up arrow
		if(key0==1)
		{
			if(edit_pos!=0)edit_pos--;
//			else edit_pos=io.num_do-1;
			pos=edit_pos & 0xfe;
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{
			if(edit_pos<(io.num_do-1))edit_pos++;
//			else edit_pos=0;
			pos=edit_pos & 0xfe;			
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
			write_command(0x0c);		
			Delay_mks(1);					
			key2=2;			
		}
		// Enter		
		if(key3==1)
		{
			io_tmp=1;			
			io_tmp=io_tmp<<edit_pos;
			if(io.dout & io_tmp)io.dout&=~io_tmp;
			else io.dout|=io_tmp;
			newmenuitem=1;				
			key3=2;			
		}
}
//-----------------------------------------------------------------------------------
void lcd_menu_digital_out()
{
	if(newmenuitem)
	{
		lcd_clear();		
		lcd_set_pos(0,0);
//		lcd_printf("Digital inputs");
		if(MenuRegs.lang==0)
			lcd_printf_P(eng_dout_dic[0]);			
		if(MenuRegs.lang==1)
			lcd_printf_P(ru_dout_dic[0]);			
		lcd_set_pos(1,0);
//		lcd_printf("DI channels");		
		if(MenuRegs.lang==0)
			lcd_printf_P(eng_dout_dic[1]);
		if(MenuRegs.lang==1)
			lcd_printf_P(ru_dout_dic[1]);
		pos=0;		
	}
	newmenuitem=0;	
}
//-----------------------------------------------------------------------------------
