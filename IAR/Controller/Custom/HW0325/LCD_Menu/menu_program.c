//-----------------------------------------------------------------------------------
#include "..\..\..\System\main.h"
//-----------------------------------------------------------------------------------
TProgLine pl;
u32	addr;
//-----------------------------------------------------------------------------------
void lcd_menu_program()
{
	if(newmenuitem)
	{
		lcd_clear();		
		lcd_set_pos(0,0);
		lcd_printf("Program section");
//		lcd_set_pos(1,0);
//		lcd_printf("");		
		pos=0;
		edit_pos=0;
	}
	newmenuitem=0;	
}
//-----------------------------------------------------------------------------------
void lcd_menu_edit_program_options()
{
	u8 tmp;//,line;
	u8 edit_pos_tmp;
//	u16 t;
	u8 i;
	
//	edit_pos=0;
	if(newmenuitem)
	{
		lcd_clear();			
		for(i=0;i<2;i++)
		{
			tmp=pos+i;		
			if(tmp<3)
			{
				lcd_set_pos(i,0);
		//		lcd_printf("DO");
				ByteToStr(lcd_txt,&tmp,0);
				lcd_printf(lcd_txt);
				switch(tmp)
				{
					case 0:
						lcd_printf(".Run ");	
						if(intr.status==program_run)
							lcd_printf("On");			
						else
							lcd_printf("Off");
					break;
					case 1:
						lcd_printf(".View");	
					break;
					case 2:
						lcd_printf(".Step");	
					break;
				}
			}
		}		
		write_command(0x0f);		
		Delay_mks(1);		
		edit_pos_tmp=edit_pos & 0x01;		
		switch(edit_pos_tmp)
		{
			case 0:lcd_set_pos(0,0);break;
			case 1:lcd_set_pos(1,0);break;
		}		
		newmenuitem=0;		
	}	
		// -------- EDIT --------------]
		// Up arrow
		if(key0==1)
		{
			if(edit_pos!=0)edit_pos--;
			else edit_pos=2;
			pos=edit_pos & 0xfe;
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{
			if(edit_pos<2)edit_pos++;
			else edit_pos=0;
			newmenuitem=1;
			pos=edit_pos & 0xfe;			
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
			switch(edit_pos)
			{
				case 0:
					if(intr.status==program_run)
						intr.status=int_Stop;		
					else
						intr.status=int_Run;
					newmenuitem=1;
				break;
/*				case 1:
					if(io.dout & 0x02)io.dout&=~0x02;
					else io.dout|=0x02;
					newmenuitem=1;
				break;
				case 2:
					if(io.dout & 0x04)io.dout&=~0x04;
					else io.dout|=0x04;
					newmenuitem=1;
				break;
				case 3:
					if(io.dout & 0x08)io.dout&=~0x08;
					else io.dout|=0x08;
					newmenuitem=1;
				break;
*/
			}
			key3=2;			
		}
}
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void lcd_menu_program_run()
{
//	u8 tmp;
	if(newmenuitem)
	{
		lcd_clear();		
		lcd_set_pos(0,0);
		lcd_printf("Run ");	
		if(intr.status==program_run)
			lcd_printf("On");			
		else
			lcd_printf("Off");

		lcd_set_pos(1,0);
		lcd_printf("Press Enter");	
		LCD_Time=500;			
	}
	newmenuitem=0;	
	if(LCD_Time==0)newmenuitem=1;
	
	// Up arrow
		if(key0==1)
		{
			if(LCDMenuPtr->PreviosItem!=NULL)
			{
				newmenuitem=1;
				LCDMenuPtr=(TLCDMenuItem*)LCDMenuPtr->PreviosItem;
				pos=0;	
			}
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{
			if(LCDMenuPtr->NextItem!=NULL)
			{
				newmenuitem=1;
				LCDMenuPtr=(TLCDMenuItem*)LCDMenuPtr->NextItem;
				pos=0;									
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
			if(intr.status==program_run)
				intr.status=int_Stop;		
			else
			{
				Intr_Init();				
				intr.status=int_Run;				
			}
			newmenuitem=1;		
			key3=2;			
		}	
}
//-----------------------------------------------------------------------------------
void lcd_menu_program_list()
{
//	u8 tmp;
	if(newmenuitem)
	{
		lcd_clear();		
		lcd_set_pos(0,0);
		lcd_printf("Program list");	
		lcd_set_pos(1,0);
		lcd_printf("Press Enter");	
		addr=CODE_START_ADDR;
	}
	newmenuitem=0;	
	
	// Up arrow
		if(key0==1)
		{
			if(LCDMenuPtr->PreviosItem!=NULL)
			{
				newmenuitem=1;
				LCDMenuPtr=(TLCDMenuItem*)LCDMenuPtr->PreviosItem;
				pos=0;	
			}
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{
			if(LCDMenuPtr->NextItem!=NULL)
			{
				newmenuitem=1;
				LCDMenuPtr=(TLCDMenuItem*)LCDMenuPtr->NextItem;
				pos=0;									
			}				
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
			if(LCDMenuPtr->UpItem!=NULL)
			{
				LCDMenuPtr=(TLCDMenuItem*)LCDMenuPtr->SubItem;
				newmenuitem=1;				
			}		
			key3=2;			
		}	
}
//-----------------------------------------------------------------------------------
void lcd_menu_program_debug()
{
//	u8 tmp;
	if(newmenuitem)
	{
		lcd_clear();		
		lcd_set_pos(0,0);
		lcd_printf("Program Debug ");	
		lcd_set_pos(1,0);
		lcd_printf("Press Enter");	
	}
	newmenuitem=0;	
	
	// Up arrow
		if(key0==1)
		{
			if(LCDMenuPtr->PreviosItem!=NULL)
			{
				newmenuitem=1;
				LCDMenuPtr=(TLCDMenuItem*)LCDMenuPtr->PreviosItem;
				pos=0;	
			}
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{
			if(LCDMenuPtr->NextItem!=NULL)
			{
				newmenuitem=1;
				LCDMenuPtr=(TLCDMenuItem*)LCDMenuPtr->NextItem;
				pos=0;									
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
			if(LCDMenuPtr->UpItem!=NULL)
			{
				LCDMenuPtr=(TLCDMenuItem*)LCDMenuPtr->SubItem;
				newmenuitem=1;				
			}				
			key3=2;			
		}	
}
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void lcd_menu_program_list_show()
{
//	u8 tmp;
	u8 str[32];
	u16 num;
	if(newmenuitem)
	{
		lcd_clear();		
		lcd_set_pos(0,0);
		fram_mem_read(addr,(u8*)&pl,CODE_LINE_LEN);
//		Intr_Program_Line_Show(&pl,&lcd_data);
		num=addr>>4;
		WordToStr(str,&num,1);
		stradd(str," ");
		stradd(str,lcd_data.l0);		
		lcd_printf(str);
		lcd_set_pos(1,0);		
		lcd_printf(lcd_data.l1);		
//		Intr_Program_Line_Handle();		
//		lcd_printf("Program list");	
//		lcd_set_pos(1,0);
//		lcd_printf("Press Enter");	
	}
	newmenuitem=0;	
	
	// Up arrow
		if(key0==1)
		{
			if(addr>(CODE_START_ADDR+CODE_LINE_LEN))
				addr-=CODE_LINE_LEN;			
			else
				addr=CODE_START_ADDR;
			newmenuitem=1;								
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{
			addr+=CODE_LINE_LEN;			
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
void lcd_menu_program_debug_show()
{
//	u8 tmp;
	if(newmenuitem)
	{
		lcd_clear();		
		lcd_set_pos(0,0);
		lcd_printf("Program Debug ");	
		lcd_set_pos(1,0);
		lcd_printf("Press Enter");	
	}
	newmenuitem=0;	
	
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
