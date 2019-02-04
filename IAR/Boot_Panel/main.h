#ifndef __MAIN
#define __MAIN
//-----------------------------------------------------------------------------------
#include "Include\types.h"
#include "functions.h"
#ifdef __RENESAS
	#include <stdio.h>
	#include "func_ren.h"
#else
	#include "spm.h"
#endif
#include <string.h>
#include "timer16.h"
#include "iflash.h"
//#include "xmodem.h"
#include "plm.h"
#include "str.h"
//#include "console.h"

//#include "Include\str.h"
#include "Include\crc.h"
#include "Include\types.h"
//#include "Include\param.h"
#include "Include\header.h"
#include "Include\defines.h"

#include "RS485_Slave\uart_exchange.h"
#include "RS485_Slave\uart_misc.h"
#include "RS485_Slave\uart_protocol.h"
//-----------------------------------------------------------------------------------
// Communicaton speed
#define UPC_RATE		38400 // 57600 lc
//-----------------------------------------------------------------------------------
//extern THead *head;
extern u8 m_Address;
extern u8 envitation[20];
extern u32 key;
extern u8 stat;
//-----------------------------------------------------------------------------------
void blink_booting();
void blink_bad_image();
void get_address();
void show_header(u32 addr);
u8 check_flash_images();
//-----------------------------------------------------------------------------------
#endif
