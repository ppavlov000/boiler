#include "..\System\main.h"
#include "inavr.h"
#include <iom128.h>
//-----------------------------------------------------------------------------------
TLcd_Text	lcd_data;
//-----------------------------------------------------------------------------------
void lcd_io_init()
{
//	u8 i;
	lcd_data_port=0x00;
	lcd_data_dir=0x00;

	ld_off;
	rw_off;
	en_off;

	ld_out;
	rw_out;
	en_out;
}
//---------------------------------------------------------------------
u8 get_byte()
{
	u8 data=0;
	data=lcd_data_pins;
	return data;
}
//---------------------------------------------------------------------
void write_command(u8 data)
{
	lcd_data_dir=0xff;
	ld_off;
	rw_off;
	en_on;
	lcd_data_port=data;
	Delay_mks(1);
	en_off;
}
//---------------------------------------------------------------------
void write_data(u8 data)
{
	lcd_data_dir=0xff;
	ld_on;
	rw_off;
	en_on;
	lcd_data_port=data;
	Delay_mks(1);
	en_off;
}
//---------------------------------------------------------------------
void lcd_init()
{
//	u8	i;
	ld_out;
	rw_out;
	en_out;
	Delay(100);
	write_command(0x3f);
	Delay(10);
	write_command(0x0c);
	Delay(10);
	write_command(1);
	Delay(10);
	write_command(0x06);
	Delay(10);
}
//---------------------------------------------------------------------
void lcd_clear()
{
	write_command(1);
	Delay(3);
}
//---------------------------------------------------------------------
void lcd_set_pos(u8 line,u8 pos)
{
	if(line==0)
	{
		pos|=0x80;
		write_command(pos);
	}
	if(line==1)
	{
		pos|=0xC0;
		write_command(pos);
	}
	Delay_mks(1);
}
//---------------------------------------------------------------------
u8 lcd_read_status()
{
	return 0;
}
//-----------------------------------------------------------------------------------
u8 lcd_char_decode(u8 symbol)
{
	u8 c=symbol;
		switch(c)
		{
//��������������������������������
			case '�':c='A';break;
			case '�':c=0xA0;break;
			case '�':c='B';break;
			case '�':c=0xA1;break;
			case '�':c=0xE0;break;
			case '�':c='E';break;
			case '�':c='E';break;
			case '�':c=0xA3;break;
			case '�':c=0xA4;break;
			case '�':c=0xA5;break;
			case '�':c=0xA6;break;
			case '�':c='K';break;
			case '�':c=0xA7;break;
			case '�':c='M';break;
			case '�':c='H';break;
			case '�':c='O';break;
			case '�':c=0xA8;break;
			case '�':c='P';break;
			case '�':c='C';break;
			case '�':c='T';break;
			case '�':c=0xA9;break;
			case '�':c=0xAA;break;
			case '�':c='X';break;
			case '�':c=0xE1;break;
			case '�':c=0xAB;break;
			case '�':c=0xAC;break;
			case '�':c=0xE2;break;
			case '�':c=0xAD;break;
			case '�':c=0xAE;break;
			case '�':c='b';break;
			case '�':c=0xAF;break;
			case '�':c=0xB0;break;
			case '�':c=0xB1;break;
			// Low case
			case '�':c='a';break;
			case '�':c=0xB2;break;
			case '�':c=0xB3;break;
			case '�':c=0xB4;break;
			case '�':c=0xE3;break;
			case '�':c='e';break;
			case '�':c=0xB6;break;
			case '�':c=0xb7;break;
			case '�':c=0xb8;break;
			case '�':c=0xb9;break;
			case '�':c=0xba;break;
			case '�':c=0xbb;break;
			case '�':c=0xbc;break;
			case '�':c=0xbd;break;
			case '�':c='o';break;
			case '�':c=0xbe;break;
			case '�':c='p';break;
			case '�':c='c';break;
			case '�':c=0xbf;break;
			case '�':c='y';break;
			case '�':c=0xe4;break;
			case '�':c='x';break;
			case '�':c=0xE5;break;
			case '�':c=0xc0;break;
			case '�':c=0xc1;break;
			case '�':c=0xe6;break;
			case '�':c=0xc2;break;
			case '�':c=0xc3;break;
			case '�':c=0xc4;break;
			case '�':c=0xc5;break;
			case '�':c=0xc6;break;
			case '�':c=0xc7;break;
		}
	return c;
}
//-----------------------------------------------------------------------------------
void lcd_printf(u8 *in)
{
	u8 c;
	while(*in!=0)
	{
		c=lcd_char_decode(*in);
		if((c!=0x0a)&&(c!=0x0d))
		{
			write_data(c);
			Delay_mks(1);
		}
		else
		{
			lcd_set_pos(1,0);
		}
		in++;
	}
}

//-----------------------------------------------------------------------------------
void lcd_printf_P(u8 in_flash *in)
{
	u8 c;
	while(*in!=0)
	{
		c=lcd_char_decode(*in);
		if((c!=0x0a)&&(c!=0x0d))
		{
			write_data(c);
			Delay_mks(1);
		}
		else
		{
			lcd_set_pos(1,0);
		}
		in++;
	}
}
//-----------------------------------------------------------------------------------
//-  Positioning printf
//-----------------------------------------------------------------------------------
void lcd_printf_pos(s8 y,s8 x,u8 *in)
{
	u8 c;
	if(!((y<0)||(y>=LCD_MAX_LINES)))lcd_set_pos(y,x);
	while(*in!=0)
	{
		if(!((y<0)||(y>=LCD_MAX_LINES)))
		{
			c=lcd_char_decode(*in);
			if((c!=0x0a)&&(c!=0x0d))
			{
				write_data(c);
				Delay_mks(1);
			}
			if(c==0x0d)
			{
				y++;
				lcd_set_pos(y,x);
			}
		}
		else
		{
			if(*in==0x0d)
			{
				y++;
				if(!((y<0)||(y>=LCD_MAX_LINES)))lcd_set_pos(y,x);
			}
		}
		in++;
	}
}
//-----------------------------------------------------------------------------------
void lcd_printf_P_pos(s8 y,s8 x,u8 in_flash *in)
{
	u8 c;
	if(!((y<0)||(y>=LCD_MAX_LINES)))lcd_set_pos(y,x);
	while(*in!=0)
	{
		if(!((y<0)||(y>=LCD_MAX_LINES)))
		{
			c=lcd_char_decode(*in);
			if((c!=0x0a)&&(c!=0x0d))
			{
				write_data(c);
				Delay_mks(1);
			}
			if(c==0x0d)
			{
				y++;
				lcd_set_pos(y,x);
			}
		}
		else
		{
			if(*in==0x0d)
			{
				y++;
				if(!((y<0)||(y>=LCD_MAX_LINES)))lcd_set_pos(y,x);
			}
		}
		in++;
	}
}
//---------------------------------------------------------------------
void lcd_clear_pos(s8 position)
{
	u8 str[LCD_MAX_SYMBOLS+1];
	memset(str,' ',LCD_MAX_SYMBOLS);
	str[LCD_MAX_SYMBOLS]=0;
	lcd_printf_pos(position,0,str);
}
//-----------------------------------------------------------------------------------
void LCD_Show_Full_Time()
{
//	u8 tmp;
//	fram_get_time();

	lcd_clear();
	lcd_set_pos(0,0);

/*
	__sprintf(outtxt,"\n\r Date ");
	ByteToStr(outtxt,&ft.field.Date,0);__sprintf(outtxt,".");
	ByteToStr(outtxt,&ft.field.Month,0);__sprintf(outtxt,".");
	ByteToStr(outtxt,&ft.field.Year,0);
*/
	lcd_printf(" ");
	ByteToStrFillZero(lcd_txt,&ft.field.Date,0,2,'0');lcd_printf(lcd_txt);
	lcd_printf("th ");
	__sprintf_P(lcd_txt,Monthes_Name_Short[ft.field.Month-1]);lcd_printf(lcd_txt);
	lcd_printf(" 20");
	ByteToStrFillZero(lcd_txt,&ft.field.Year,0,2,'0');lcd_printf(lcd_txt);
//	lcd_printf(", ");
//	__sprintf_P(lcd_txt,DaysOfWeek[ft.field.Day-1]);lcd_printf(lcd_txt);

	lcd_set_pos(1,0);
//	lcd_printf(" Time ");
	lcd_printf("      ");
	ByteToStrFillZero(lcd_txt,&ft.field.Hour,0,2,'0');lcd_printf(lcd_txt);lcd_printf(":");
	ByteToStrFillZero(lcd_txt,&ft.field.Minute,0,2,'0');lcd_printf(lcd_txt);//lcd_printf(".");
//	ByteToStrFillZero(lcd_txt,&ft.field.Second,0,2);lcd_printf(lcd_txt);
}
//-----------------------------------------------------------------------------------
