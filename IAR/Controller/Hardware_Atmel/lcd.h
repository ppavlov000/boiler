//------------------------------------------------------------------------------
#ifndef _LCD
#define _LCD
//------------------------------------------------------------------------------
#include "main.h"
//------------------------------------------------------------------------------
typedef struct
{
	u8	l0[LCD_MAX_SYMBOLS];
	u8	l1[LCD_MAX_SYMBOLS];	
}TLcd_Text;
//------------------------------------------------------------------------------
extern TLcd_Text	lcd_data;
//------------------------------------------------------------------------------
//void Mod_Reset();
void lcd_init();
void lcd_io_init();
void lcd_clear();
void write_command(u8 data);
void lcd_printf(u8 *in);
void lcd_printf_P(u8 in_flash *in);
void lcd_set_pos(u8 line,u8 pos);
void LCD_Show_Full_Time();

void lcd_clear_pos(s8 position);
void lcd_printf_P_pos(s8 y,s8 x,u8 in_flash *in);
void lcd_printf_pos(s8 y,s8 x,u8 *in);
//------------------------------------------------------------------------------
#endif
