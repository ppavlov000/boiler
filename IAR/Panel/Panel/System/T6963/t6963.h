#ifndef __T6963
#define __T6963

/********************************************
 * Filename: t6963.h                        *
 *                                          *
 * Description: Header file for t6963.c     *
 *                                          *
 *                                          *
 * Date: 06/02/2003                         *
 *******************************************/
/* Pragmas */
//#pragma CLOCK_FREQ      4000000
#define CLOCK_FREQ      4000000

/* LCD Parameters */
//#define LCD_TEXT_WIDTH          0x14    /* Text Width = Graphics Width / Character Width */
//#define LCD_TEXT_HEIGHT         0x08    /* Text Height = Graphics Height / Character Height */
//#define LCD_GRAPHICS_WIDTH      0xA0    /* Width of display (0xA0 = 160 pixels) */
//#define LCD_GRAPHICS_HEIGHT     0x80    /* Height of display (0x80 = 128 pixels) */
#define LCD_NUMBER_OF_SCREENS   0x02    /* for > 68 pixels height, is probably split into 2 screens */
                                        /* into 2 screens */
#define LCD_CHARACTER_WIDTH     0x08    /* Is character 8x8 or 6x8 (0x08 / 0x06) */

/* Define the Memory Map */
#define LCD_GRAPHICS_HOME   0x01e0  /* This will usually be at the start of RAM */
#define LCD_GRAPHICS_AREA   0x1E    /* A graphic character is 8 bits wide (same as 8x8 char) */
#define LCD_GRAPHICS_SIZE   0x0F00  /* Size of graphics RAM */
#define LCD_TEXT_HOME       0x0000  /* Graphics Area + Text Attribute Size (same size as text size) */
#define LCD_TEXT_AREA       0x1E    /* Text line is 20 chars wide */
#define LCD_TEXT_SIZE       0x01e0  /* Size of text RAM */

#define PAGE_SIZE 			0x2000
#define PAGE_0_OFFSET 		0
#define PAGE_1_OFFSET 		LCD_GRAPHICS_HOME + LCD_GRAPHICS_SIZE

/*  Memory Map for 240x128 pixel display */
/*  This display is made up of two screens */
/*  Both 240x128 pixels */

/*  Screen 1 */

/*  0x0000  ----------------------------- */
/*          | Graphic RAM Area          | */
/*          | 0x0000 to 0x07FF          | */
/*          | (256x64 pixels)           | */
/*  0x0F00  ----------------------------- */
/*          | Text Attribute Area       | */
/*  0x0F00  ----------------------------- */
/*          | Text RAM Area             | */
/*          | 512 Bytes                 | */
/*          | (256x64 pixels)           | */
/*  0x10e0  ----------------------------- */

/*  Screen 2 (Automatically derived from Screen 1) */

/*  0x8000  ----------------------------- */
/*          | Graphic RAM Area          | */
/*          | 0x0000 to 0x07FF          | */
/*          | (256x64 pixels)           | */
/*  0x8800  ----------------------------- */
/*          | Text Attribute Area       | */
/*  0x8A00  ----------------------------- */
/*          | Text RAM Area             | */
/*          | 512 Bytes                 | */
/*          | (256x64 pixels)           | */
/*  0x8C00  ----------------------------- */


/* Control Word Definitions */
#define LCD_CURSOR_POINTER_SET          0x21//00100001b
#define LCD_OFFSET_REGISTER_SET         0x22//00100010b
#define LCD_ADDRESS_POINTER_SET         0x24//00100100b

#define LCD_TEXT_HOME_ADDRESS_SET       0x40//01000000b
#define LCD_TEXT_AREA_SET               0x41//01000001b
#define LCD_GRAPHIC_HOME_ADDRESS_SET    0x42//01000010b
#define LCD_GRAPHIC_AREA_SET            0x43//01000011b

#define LCD_CG_ROM_MODE_OR              0x80//10000000b
#define LCD_CG_ROM_MODE_EXOR            0x81//10000001b
#define LCD_CG_ROM_MODE_AND             0x83//10000011b
#define LCD_CG_ROM_MODE_TEXT            0x84//10000100b
#define LCD_CG_RAM_MODE_OR              0x88//10001000b
#define LCD_CG_RAM_MODE_EXOR            0x89//10001001b
#define LCD_CG_RAM_MODE_AND             0x8b//10001011b
#define LCD_CG_RAM_MODE_TEXT            0x8c//10001100b

/* 1001 0000 is all off, OR together for ON modes */
#define LCD_DISPLAY_MODES_ALL_OFF       0x90//10010000b
#define LCD_DISPLAY_MODES_GRAPHICS_ON   0x98//10011000b
#define LCD_DISPLAY_MODES_TEXT_ON       0x94//10010100b
#define LCD_DISPLAY_MODES_CURSOR_ON     0x92//10010010b
#define LCD_DISPLAY_MODES_CURSOR_BLINK  0x91//10010001b

/* Cursor Pattern Select */
#define LCD_CURSOR_PATTERN_UNDERLINE    0xA0//10100000b
#define LCD_CURSOR_PATTERN_BLOCK        0xA7//10100111b

/* Send Auto_XX Command, then block of data, then Auto_reset */
#define LCD_DATA_AUTO_WRITE_SET         0xB0//10110000b
#define LCD_DATA_AUTO_READ_SET          0xB1//10110001b
#define LCD_DATA_AUTO_RESET             0xB2//10110010b

/* Send R/W Then one byte Data */
#define LCD_DATA_WRITE_AUTO_INCREMENT   0xC0//11000000b
#define LCD_DATA_READ_AUTO_INCREMENT    0xC1//11000001b
#define LCD_DATA_WRITE_NO_INCREMENT     0xC4//11000100b
#define LCD_DATA_READ_NO_INCREMENT      0xC5//11000101b


#define LCD_SCREEN_COPY                 0xE8//11000101b

/* Status Register Bits */
#define LCD_STATUS_BUSY1    0x01
#define LCD_STATUS_BUSY2    0x02
#define LCD_STATUS_DARRDY   0x04
#define LCD_STATUS_DAWRDY   0x08

#define LCD_STATUS_CLR      0x20
#define LCD_STATUS_ERR      0x40
#define LCD_STATUS_BLINK    0x80

/* Definitions */
#define ALL_INPUTS  0x00
#define ALL_OUTPUTS 0xFF
//------------------------------------------------------------------------------
eu32 page_offset;
eu32 lcd_graphics_home;
eu32 lcd_text_home;
//------------------------------------------------------------------------------
/* Function Declarations */
void interrupt(void);
void Wait_Ready();
void lcd_clear_graphics(void);
void lcd_clear_text(void);
void lcd_write_text(unsigned char character, unsigned char x, unsigned char y);
void lcd_set_pixel(unsigned char x, unsigned char y);
void lcd_clear_pixel(unsigned char x, unsigned char y);
unsigned char lcd_bit_to_byte(unsigned char bit);
void lcd_reset(void);
void lcd_initialise(u8 page_number);
void lcd_sprintf(u8 *in, unsigned char x, unsigned char y);
void lcd_sprintf_P(u8 __farflash *in, unsigned char x, unsigned char y);
void lcd_clear_all(void);
void lcd_set_page(u8 page_number);
void lcd_set_cursor(u8 x,u8 y);
//------------------------------------------------------------------------------
eu8 lcd_txt[40];
//------------------------------------------------------------------------------
#endif
