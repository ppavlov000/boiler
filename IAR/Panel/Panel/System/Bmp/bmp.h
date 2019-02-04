#ifndef __BMP
#define __BMP
//--------------------------------------------------------------------------------------------------------
#include "..\..\System\Standard\types.h"
#include "BMPPack.h"
//--------------------------------------------------------------------------------------------------------
#define MAX_TIME_PRESSING 100
#define SLEEP_TIMEOUT 60
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
/********************************************
 * Filename: t6963.h                        *
 *                                          *
 * Description: Header file for t6963.c     *
 *                                          *
 *                                          *
 * Date: 06/02/2003                         *
 *******************************************/
/*
The BITMAPFILEHEADER:
start	size	name	stdvalue	purpose	

1	2	bfType	19778	must always be set to 'BM' to declare that this is a .bmp-file.	
3	4	bfSize	??	specifies the size of the file in bytes.	
7	2	bfReserved1	0	must always be set to zero.	
9	2	bfReserved2	0	must always be set to zero.	
11	4	bfOffBits	1078	specifies the offset from the beginning of the file to the bitmap data.

The BITMAPINFOHEADER:
start	size	name	stdvalue	purpose	

15	4	biSize	40	specifies the size of the BITMAPINFOHEADER structure, in bytes.	
19	4	biWidth	100	specifies the width of the image, in pixels.	
23	4	biHeight	100	specifies the height of the image, in pixels.	
27	2	biPlanes	1	specifies the number of planes of the target device, must be set to zero.	
29	2	biBitCount	8	specifies the number of bits per pixel.	
31	4	biCompression	0	Specifies the type of compression, usually set to zero (no compression).	
35	4	biSizeImage	0	specifies the size of the image data, in bytes. If there is no compression, it is valid to set this member to zero.	
39	4	biXPelsPerMeter	0	specifies the the horizontal pixels per meter on the designated targer device, usually set to zero.	
43	4	biYPelsPerMeter	0	specifies the the vertical pixels per meter on the designated targer device, usually set to zero.	
47	4	biClrUsed	0	specifies the number of colors used in the bitmap, if set to zero the number of colors is calculated using the biBitCount member.	
51	4	biClrImportant	0	specifies the number of color that are 'important' for the bitmap, if set to zero, all colors are important.

The RGBQUAD array:
The following table shows a single RGBQUAD structure:

start	size	name	stdvalue	purpose	

1	1	rgbBlue	-	specifies the blue part of the color.	
2	1	rgbGreen	-	specifies the green part of the color.	
3	1	rgbRed	-	specifies the red part of the color.	
4	1	rgbReserved	-	must always be set to zero.
*/
//--------------------------------------------------------------------------------------------------------
typedef struct
{
	u16 bfType;
	u32 bfSize;
	u16 bfReserved1;
	u16 bfReserved2;
	u32 bfOffBits;
}BITMAPFILEHEADER;
//--------------------------------------------------------------------------------------------------------
typedef struct
{
	u32 biSize;
	u32 biWidth;
	u32 biHeight;
	u16 biPlanes;
	u16 biBitCount;
	u32 biCompression;					
	u32 biSizeImage;
	u32 biXPelsPerMeter;
	u32 biYPelsPerMeter;			
	u32 biClrUsed;
	u32 biClrImportant;	
}BITMAPINFOHEADER;
//--------------------------------------------------------------------------------------------------------
typedef struct
{
	u8 rgbBlue;
	u8 rgbGreen;
	u8 rgbRed;
	u8 rgbReserved;			
}RGBQUAD;
//--------------------------------------------------------------------------------------------------------
typedef struct
{
	BITMAPFILEHEADER    bmfh;
	BITMAPINFOHEADER    bmih;
//	RGBQUAD             aColors[];
//	u8					aBitmapBits[];
//	u8					*data;
}TBMP;
//--------------------------------------------------------------------------------------------------------
typedef struct
{
	u8 x;
	u8 y;	
	u8 pict_num;
	u16			Flag;
	u8 			Stat;	
	u32			Action;		// Action bit
	u8			Counter;	// Count of button pressed
	void (* Routine)();		
	void* 		SubItem;	
}TLCDPict;
typedef struct
{
	u16 x;
	u16 y;	
	u16 pict_num;
	u16			Flag;
	u8 			Stat;	
}TLCDPict_Txt;
typedef struct
{
	u8 x;
	u8 y;	
	u8 pict_num;
	u16 Flag;
	u8 Obj_Num;
	u8 Txt_Num;	
	void (* Init)();		// Initialisation	
	void (* Routine)();		// Continuous
	void (* Exit)();		// Exit
}TLCDPictTop;
extern TLCDPict LCD_Root;
//--------------------------------------------------------------------------------------------------------
// Bits of Flag
#define bit_visible		0x0001
#define bit_active		0x0002
#define bit_trigger		0x0004
#define bit_new_page	0x0008
#define bit_txt_1		0x0010
#define bit_full		0x0020
#define bit_blinking	0x0040
#define bit_txt_2		0x0080
#define bit_sign		0x0100
#define bit_static		0x0200
#define bit_alarm		0x0400
#define bit_dimmer		0x0800
//--------------------------------------------------------------------------------------------------------
#ifdef __RENESAS
	#define bl_step	3

	#define bl_100	254		// 98  %
	#define bl_90	205		// 80.4%
	#define bl_80	162		// 63.7%
	#define bl_70	125		// 49  %
	#define bl_60	93		// 36.4%
	#define bl_50	65		// 25.6%
	#define bl_40	43		// 16.8%
	#define bl_30	25		//  9.9%
	#define bl_20	13		//  5  %
	#define bl_10	5		//  1.8%
	#define bl_0	0
/*
	#define bl_step	650U // lc

	#define bl_100	65000U
	#define bl_90	45000U
	#define bl_80	35000U
	#define bl_70	25000U
	#define bl_60	15000U
	#define bl_50	7000U
	#define bl_40	5500U
	#define bl_30	4000U
	#define bl_20	2500U
	#define bl_10	1000U
	#define bl_0	0U
*/
#else
	#define bl_step	1 // lc

	#define bl_100	1023
	#define bl_90	810
	#define bl_80	640
	#define bl_70	490
	#define bl_60	360
	#define bl_50	250
	#define bl_40	160
	#define bl_30	90
	#define bl_20	40
	#define bl_10	10
	#define bl_0	0
#endif
eu16 bl[11];
//--------------------------------------------------------------------------------------------------------
typedef struct
{
	u8 status;
	TLCDPict*		LCDMenuPtr;
}TManualPush;
extern TManualPush push;
//--------------------------------------------------------------------------------------------------------
eu16 BackLit_Value;
eu8 bmp_update;
eu8 enter_tech_menu;
eu8 txt_mode;
eu8 alarm_state;
eu8 int_state;
eu8 time_blink;
eu8 int_pos;
extern TTimeShort FiveMins;
extern TTimeShort int_time;
extern TTimeShort set_time;
eu8 update_time;
eu8 update_time2;
eu8 bar_stat[16];
extern TLCDPict*		LCDMenuPtr;
extern TLCDPict*		LCDMenuPtr_Tmp;
extern TLCDPict*		LCDMenuPtr_Tmp2;
extern TLCDPict_Txt*	LCDMenuPtr_Tmp_Txt;
extern TLCDPictTop*		LCDTopPtr;
extern u8 spec[2];
//--------------------------------------------------------------------------------------------------------
void show_bmp();
void show_button(u16 x8, u16 y8,u8 pnum,u8 pmode);
void init_bmp();
void repaint_page();
void clear_page();
void show_single_bmp(TLCDPict*	lcd_ptr,u8 inverted);
void clear_single_bmp(TLCDPict*	lcd_ptr);
u8  handle_single_bmp(TLCDPict*	lcd_ptr);
void handle_page();

void show_single_bmp_txt(TLCDPict_Txt*	lcd_ptr);
void clear_single_bmp_txt(TLCDPict_Txt*	lcd_ptr);

void startup();
void calibrate_bmp();
void sleep_enable();
void sleep_disable();
void show_byte(u8 *out,u8 in,u8 offset);
//--------------------------------------------------------------------------------------------------------
#endif
