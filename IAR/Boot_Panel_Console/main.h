#ifndef __MAIN
#define __MAIN
//-----------------------------------------------------------------------------------
#include "Include\types.h"

#include <string.h>
#include <iom128.h>
#include "console.h"
#include "timer16.h"
#include "iflash.h"
#include "xmodem.h"
#include "inavr.h"
//#include <stdlib.h>
//#include "spm.h"
#include "plm.h"

#include "Include\str.h"
#include "Include\types.h"
#include "Include\param.h"
#include "Include\header.h"
#include "Include\defines.h"
#include "Include\i2c.h"
#include "Include\fram31xx.h"
//#include "Include\tmp441.h"
//-----------------------------------------------------------------------------------
#define ADM706_PORT PORTB
#define ADM706_DIR 	DDRB
#define ADM706_PINS PINB

#define adm_wd 		0x10

#define adm_init		//ADM706_PORT&=~adm_wd;ADM706_DIR|=adm_wd
#define adm_wd_reset	//ADM706_PORT|=adm_wd; __no_operation(); ADM706_PORT&=~adm_wd

#define led_init	DDRC|=0x80;	PORTC&=~0x80
#define led_on	PORTC&=~0x80
#define led_off	PORTC|=0x80
#define led_check PINC & 0x08
//-----------------------------------------------------------------------------------
//extern THead *head;
extern u8 envitation[20];
extern u32 key;
extern u8 stat;
//-----------------------------------------------------------------------------------
void blink_booting();
void blink_bad_image();
//-----------------------------------------------------------------------------------
#endif
