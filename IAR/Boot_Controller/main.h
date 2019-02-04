#ifndef __MAIN
#define __MAIN
//-----------------------------------------------------------------------------------
#include "Include\types.h"
#include "functions.h"
#include "spm.h"

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
#include "Include\header.h"
#include "Include\defines.h"
#include "Include\i2c.h"
#include "Include\fram31xx.h"

#include "RS485_Slave\uart_exchange.h"
#include "RS485_Slave\uart_misc.h"
#include "RS485_Slave\uart_protocol.h"
//-----------------------------------------------------------------------------------
#define RS485_ADDRESS	1
//-------------------------------------------------------------------------------------------
// Communicaton speed
#define UPC_RATE		38400 // 57600 lc
//-------------------------------------------------------------------------------------------
#define NUM_DIN		6
#define NUM_DOUT	7
#define NUM_AIN		3
#define NUM_AOUT	1
//-------------------------------------------------------------------------------------------
#define ID_LOCATION 0x00
#define PARAM_LOCATION 0x02
#define TPARAM_WIDTH sizeof(TParam)
//-----------------------------------------------------------------------------------
typedef struct
{
	u8 num_di;
	u8 num_do;
	u8 num_ai;
	u8 num_ao;
				
	u32	din;
	u32 dout;
	u16 aoutput[NUM_AOUT];	
	s16 ainput[NUM_AIN];
	s16 dt;
	u8 Fan_Mode;
	u8 Fan_Lvl;
	f32 ao_coff[NUM_AOUT];	
	f32 ai_coff[NUM_AIN];	
	s16 ai_offset[NUM_AIN];		
	s16 tmp;
}TIO;
//-------------------------------------------------------------------------------------------
typedef struct
{
	TIO io;
	u16 CRC;
}TParam;
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
