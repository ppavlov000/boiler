//-----------------------------------------------------------------------------------
#include "..\..\..\System\main.h"
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
in_flash u8	eng_parameters_dic[2][20]=
{
	"P",				//0
	"MANUAL Mode",				//0	
};
in_flash u8	ru_parameters_dic[2][20]=
{
	"ÀÂÒÎ ðåæèì",				//0
	"ÐÓ×Í ðåæèì",				//0	
};	
u8 str_buff[10];
u8 parameter_pos=0;
u8 parameter_rozryad=0;

void WordToStrFillZero(u8 *out,u16 *val,u8 format);
u8 get_up_menu();
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void lcd_menu_choose_parameters()
{
	u8 tmp;
//	u8 tmp2;	
//	u8 edit_pos;
	u8 edit_pos_tmp;	
	if(newmenuitem)
	{
		lcd_clear();
		memset(lcd_txt, 0, sizeof(lcd_txt));		
		tmp=pos & 0xfe;		
		
		lcd_set_pos(0,1);
		__sprintf_P(lcd_txt,eng_parameters_dic[0]);
		ByteToStr(str_buff,(u8*)&tmp,0);
		stradd(lcd_txt,str_buff);
		lcd_printf(lcd_txt);	
		lcd_set_pos(0,5);
		//IntToStrFillZero(lcd_txt,(u16*)&intr.params[tmp],0,4,3,0);
		WordToStrFillZero(lcd_txt,(u16*)&intr.in_params[tmp],0);
		lcd_printf(lcd_txt);	
		
		tmp=(pos & 0xfe) +1;	
		if(tmp<PARAMETERS_MAX)
		{		
			lcd_set_pos(1,1);
			__sprintf_P(lcd_txt,eng_parameters_dic[0]);
			ByteToStr(str_buff,(u8*)&tmp,0);
			stradd(lcd_txt,str_buff);
			lcd_printf(lcd_txt);	
			lcd_set_pos(1,5);
//			IntToStrFillZero(lcd_txt,(u16*)&intr.params[tmp],0,4,3,0);//WordToStr(lcd_txt,(u16*)&intr.params[tmp2],0);
			WordToStrFillZero(lcd_txt,(u16*)&intr.in_params[tmp],0);
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
			else pos=PARAMETERS_MAX-1;
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{
			if(pos<(PARAMETERS_MAX-1))pos++;
			else pos=0;
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
			if(Menu[Menu_Pos].SubItem != 0)
			{
				Menu_Pos=Menu_Pos+Menu[Menu_Pos].SubItem;
				LCD_Cur_Pos=0;
				newmenuitem=1;	
				lcd_clear();
				parameter_pos=pos;
//				pos=0;				
			}			
			key3=2;			
		}	
}
//-----------------------------------------------------------------------------------
void lcd_menu_edit_parameters()
{
	u8 i;
	u32 tmp=1;
	u32 tmp2=0;
	u32 tmp3=0;
	u8  b[5]={0};
	u8 ap=0;
	u8 str[LCD_MAX_SYMBOLS+1];

	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear();
		lcd_set_pos(0,1);

		__sprintf_P(lcd_txt,eng_parameters_dic[0]);
		ByteToStr(str_buff,(u8*)&parameter_pos,0);
		stradd(lcd_txt,str_buff);
		lcd_printf(lcd_txt);	
		lcd_set_pos(0,5);
		WordToStrFillZero(lcd_txt,(u16*)&intr.in_params[parameter_pos],0);
		memset(str,0,LCD_MAX_SYMBOLS+1);
		for(i=0;i<5;i++)
		{
			str[i]=' ';
			if(parameter_rozryad==i)str[i]='^';
		}
		lcd_printf_pos(0,5,lcd_txt);
		lcd_printf_pos(0+1,5,str);
	}	
	// Editing
//	if(Active_Item)
	{
		newmenuitem=0;		
		if(LCD_Time==0)
			newmenuitem=1;		
		// -------- Keys --------------//
		// Up arrow
		if(key0==1)
		{			
			if(parameter_rozryad>0)parameter_rozryad--;				
			LCD_Time=0;
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{			
			if(parameter_rozryad<(5-1))parameter_rozryad++;		
			LCD_Time=0;		
			newmenuitem=1;
			key1=2;
		}	
		// Esc
		if(key2==1)
		{
			if(get_up_menu() != 0)			
			{
				LCD_Cur_Pos=0;
				lcd_clear();
			}
			parameter_rozryad=0;
			params_store();
			LCD_Time=0;	
			newmenuitem=1;
			key2=2;			
		}
		// Enter		
		if(key3==1)
		{
//			io.dout^=1UL<<Active_IO_Item;
			tmp=1;
			tmp2=intr.in_params[parameter_pos];
			tmp3=intr.in_params[parameter_pos];
			for(i=0;i<5;i++)
			{
				tmp3/=10;
				tmp3*=10;
				b[i]=tmp2-tmp3;
				tmp2/=10;				
				tmp3=tmp2;
			}
			ap=4-parameter_rozryad;
			b[ap]+=1;
			if(b[ap]>=10)b[ap]=0;
			if(ap==4)
				if(b[ap]>2)b[ap]=0;
//			tmp2=b[0]+b[1]*10+b[2]*100+b[3]*1000+b[4]*10000;			
			tmp2=0;
			for(i=0;i<5;i++)
			{
				tmp2*=10;
				tmp2+=b[4-i];
			}
			intr.in_params[parameter_pos]=tmp2;
//			for(i=4;i!=parameter_rozryad;i--)
//			{
//				tmp*=10;
//			}
//			tmp2=intr.params[parameter_pos]/tmp;
//			tmp3=tmp2/10;
//			tmp3=tmp2*10;
//			tmp2=tmp2-tmp3;
//			tmp2+=1;
//			if(tmp2>=10)tmp2=0;
//			intr.params[parameter_pos]=intr.params[parameter_pos]+tmp;
			tmp=0;
			LCD_Time=0;		
			newmenuitem=1;			
			key3=2;			
		}
	}		
}

//-----------------------------------------------------------------------------------
