/********************************************
 * Filename: t6963.c                        *
 *                                          *
 * Description: Toshiba LCD Driver Functions*
 *                                          *
 * by Richard Taylor                        *
 *                                          *
 * Date: 09/02/2003                         *
 *******************************************/
//-----------------------------------------------------------------------------------
#define RUS_TXT		0//0x80+0x20
//-----------------------------------------------------------------------------------
#include "..\main.h"
u8 lcd_txt[40];
u32 page_offset=PAGE_0_OFFSET;
u32 lcd_graphics_home=LCD_GRAPHICS_HOME;
u32 lcd_text_home=LCD_TEXT_HOME;
//-----------------------------------------------------------------------------------
void nop()
{
    no_operation();
}
//-----------------------------------------------------------------------------------
void lcd_show_frame()
{
	u8 x,y;
	for (x=0; x<240; x++)
	{
		lcd_set_pixel(x, 0);
		lcd_set_pixel(x, 127);
	}
	for (y=0; y<128; y++)
	{
		lcd_set_pixel(0,y);
		lcd_set_pixel(239,y);
	}
}
//-----------------------------------------------------------------------------------
/********************************************
 * Function name: initialise                *
 * Description:   S|et page for drawing     *
 *******************************************/
void lcd_set_page(u8 page_number)
{
	switch(page_number)
	{
		case 0: page_offset=PAGE_0_OFFSET; break;
		case 1: page_offset=PAGE_1_OFFSET; break;
	}
	lcd_graphics_home=LCD_GRAPHICS_HOME+page_offset;
	lcd_text_home=LCD_TEXT_HOME;	
}
//-----------------------------------------------------------------------------------
/********************************************
 * Function name: initialise                *
 * Description:   Initialise PIC and LCD    *
 *******************************************/
void lcd_initialise(u8 page_number)
{
	switch(page_number)
	{
		case 0: page_offset=PAGE_0_OFFSET; break;
		case 1: page_offset=PAGE_1_OFFSET; break;
	}
	lcd_graphics_home=LCD_GRAPHICS_HOME+page_offset;
	lcd_text_home=LCD_TEXT_HOME;	
    // Set Char Gen Up
    lcd_write_command(LCD_CG_ROM_MODE_OR);
    // Set Graphic Home Address
    lcd_write_data(lcd_graphics_home);
    lcd_write_data(lcd_graphics_home >> 8);
    lcd_write_command(LCD_GRAPHIC_HOME_ADDRESS_SET);
    // Set Graphic Area
    lcd_write_data(LCD_GRAPHICS_AREA); // Width of 20 Chars
    lcd_write_data(0x00);
    lcd_write_command(LCD_GRAPHIC_AREA_SET);

    // Set Text Home Address
    lcd_write_data((u8)lcd_text_home);
    lcd_write_data(lcd_text_home >> 8);
    lcd_write_command(LCD_TEXT_HOME_ADDRESS_SET);

    // Set Text Area
    lcd_write_data(LCD_TEXT_AREA); // Width of 20 Chars
    lcd_write_data(0x0);
    lcd_write_command(LCD_TEXT_AREA_SET);
//    lcd_write_command(LCD_DISPLAY_MODES_GRAPHICS_ON | LCD_DISPLAY_MODES_TEXT_ON);
}
//-----------------------------------------------------------------------------------
void Wait_Ready()
{
	u8 i=0;
	while(1)
	{
		watchdog_reset();
		i=lcd_read_status();
		i&=0x03;
		if(i!=0x03)no_operation();
		else return;
	}
}
//-----------------------------------------------------------------------------------
void lcd_set_cursor(u8 x,u8 y)
{
    lcd_write_data(x);
    lcd_write_data(y);
    lcd_write_command(0x21);	
}
//-----------------------------------------------------------------------------------
/********************************************
 * Function name: lcd_clear_graphics        *
 * Description:   Wipe  RAM        	        *
 *******************************************/
void lcd_clear_all(void)
{
    unsigned char address_l, address_h;
    unsigned int address, address_limit;
    /* Set Address Pointer */
    address = 0;
    address_l = address & 0xff;
    address_h = address >> 8;
    lcd_write_data(address_l);
    lcd_write_data(address_h);
    lcd_write_command(LCD_ADDRESS_POINTER_SET);

    address_limit = (32U*1024U);
    while (address < address_limit)
    {
    	watchdog_reset();
        lcd_write_data(0x00);
        lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
        address = address + 1;
    }
}
//-----------------------------------------------------------------------------------
/********************************************
 * Function name: lcd_clear_graphics        *
 * Description:   Wipe Graphics RAM         *
 *******************************************/
void lcd_clear_graphics(void)
{
    unsigned char address_l, address_h;
    unsigned int address, address_limit;
    /* Set Address Pointer */
    address = lcd_graphics_home;
    address_l = address & 0xff;
    address_h = address >> 8;
    lcd_write_data(address_l);
    lcd_write_data(address_h);
    lcd_write_command(LCD_ADDRESS_POINTER_SET);

    address_limit = (lcd_graphics_home + LCD_GRAPHICS_SIZE);

    while (address < address_limit)
    {
    	watchdog_reset();
        lcd_write_data(0x00);
        lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
        address = address + 1;
    }
}
//-----------------------------------------------------------------------------------
/********************************************
 * Function name: lcd_clear_text            *
 * Description:   Wipe Text RAM             *
 *******************************************/
void lcd_clear_text(void)
{
    unsigned char address_l, address_h;
    unsigned int address, address_limit;
    /* Set Address Pointer */
    address = lcd_text_home;
    address_l = address & 0xff;
    address_h = address >> 8;
    lcd_write_data(address_l);
    lcd_write_data(address_h);
    lcd_write_command(LCD_ADDRESS_POINTER_SET);

    address_limit =  (lcd_text_home + LCD_TEXT_SIZE);
    while (address < address_limit)
    {
    	watchdog_reset();
        lcd_write_data(0x00);
        lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
        address = address + 1;
    }
}
//-----------------------------------------------------------------------------------
/********************************************
 *******************************************/
void lcd_ru_charset()
{
    u32 address;
	u32	offset;
	u32	code;
	u8 	line;	
	code=0x80;
	offset=0x00;
	line=0;

	offset=0;
	// À
	code='À';
    address = line+(code<<3)+(offset<<11);
//    character = character - 0x20;   /* Adjust standard ASCII to T6963 ASCII */
//    lcd_write_data(address & 0xff);
//    lcd_write_data(address >> 0x08);
//    lcd_write_command(LCD_ADDRESS_POINTER_SET);
//    lcd_write_data(character);
//    lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
}
//-----------------------------------------------------------------------------------
/********************************************
 * Function name: lcd_write_text            *
 * Description:   Write Character to X, Y   *
 *                0 <= X <= LCD Text Width  *
 *                0 <= Y <= LCD Text Height *
 *******************************************/
void lcd_write_text(unsigned char character, unsigned char x, unsigned char y)
{
    unsigned int address;

    address = (y * LCD_TEXT_AREA) + x + lcd_text_home;
    character = character - 0x20;   /* Adjust standard ASCII to T6963 ASCII */
    lcd_write_data(address & 0xff);
    lcd_write_data(address >> 0x08);
    lcd_write_command(LCD_ADDRESS_POINTER_SET);
    lcd_write_data(character);
    lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
}
//-----------------------------------------------------------------------------------
/********************************************
 * Function name: lcd_set_pixel             *
 * Description:   Set a single Pixel on     *
 *                0 <= X <= LCD Width       *
 *                0 <= Y <= LCD Height      *
 *******************************************/
void lcd_set_pixel(u8 x, u8 y)
{
    unsigned char data;
    u16 address;

    address = (y * LCD_GRAPHICS_AREA) + (x / 8) + lcd_graphics_home;

    x = x & 0x07;
    x=7-x;
    data=1<<x;

    lcd_write_data(address & 0xff);
    lcd_write_data(address >> 0x08);
    lcd_write_command(LCD_ADDRESS_POINTER_SET);

    /* Read existing display */
    lcd_write_command(LCD_DATA_READ_NO_INCREMENT);
    data = data | lcd_read_data();

    /* Write modified data */
    lcd_write_data(data);
    lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
}
//-----------------------------------------------------------------------------------
/********************************************
 * Function name: lcd_clear_pixel           *
 * Description:   Clear a single Pixel      *
 *                0 <= X <= LCD Width       *
 *                0 <= Y <= LCD Height      *
 *******************************************/
void lcd_clear_pixel(unsigned char x, unsigned char y)
{
    unsigned char data;
    u16 address;

    address = (y * LCD_GRAPHICS_AREA) + (x / 8) + lcd_graphics_home;

    x = x & 0x07;
    x=7-x;
    data=1<<x;
    data=0xff-data;

    lcd_write_data(address & 0xff);
    lcd_write_data(address >> 0x08);
    lcd_write_command(LCD_ADDRESS_POINTER_SET);

    /* Read existing display */
    lcd_write_command(LCD_DATA_READ_NO_INCREMENT);
    data = data & lcd_read_data();

    /* Write modified data */
    lcd_write_data(data);
    lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
}
//-----------------------------------------------------------------------------------
/********************************************
 * Function name: lcd_write_text            *
 * Description:   Write Character to X, Y   *
 *                0 <= X <= LCD Text Width  *
 *                0 <= Y <= LCD Text Height *
 *******************************************/
void lcd_sprintf(u8 *in, unsigned char x, unsigned char y)
{
    unsigned int address;
//	u8 character;
//	u16 address;
   	address = (y * LCD_TEXT_AREA) + x + lcd_text_home;
    lcd_write_data(address & 0xff);
    lcd_write_data(address >> 0x08);
    lcd_write_command(LCD_ADDRESS_POINTER_SET);
    while(*in!=0)
    {
    	watchdog_reset();
	    lcd_write_data(*in+RUS_TXT-0x20);
    	lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
    	in++;
    }
}
//-----------------------------------------------------------------------------------
void lcd_sprintf_P(u8 __farflash *in, unsigned char x, unsigned char y)
{
    unsigned int address;
//	u8 character;
//	u16 address;
   	address = (y * LCD_TEXT_AREA) + x + lcd_text_home;
    lcd_write_data(address & 0xff);
    lcd_write_data(address >> 0x08);
    lcd_write_command(LCD_ADDRESS_POINTER_SET);
    while(*in!=0)
    {
    	watchdog_reset();
	    lcd_write_data(*in+RUS_TXT-0x20);
    	lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
    	in++;
    }
}
//-----------------------------------------------------------------------------------
