#ifndef _DEFINES_H_
#define _DEFINES_H_
//------------------------------------------------------------------------------
#include "Misc\types.h"
//------------------------------------------------------------------------------
//#define __HW030
//#define __HW031
//#define __HW0322
//#define __HW0323
//#define __HW0324
//#define __HW0325
//#define __HW0326
//#define __HW050
//------------------------------------------------------------------------------
//#define __SIMULATOR
#define __ATMEL
//#define __RENESAS
//------------------------------------------------------------------------------
//#define __DEBUG
#define __RELEASE
//#define __NO_FRAM
//#define __NO_ADC
//------------------------------------------------------------------------------
#define LCD_ENABLE			0
#define FRAM_ENABLE			1
#define ADC_ENABLE			1
#define TMP441_ENABLE		0
//#define FAN_PRESENT			0
//------------------------------------------------------------------------------
#define LCD_MAX_LINES 2
#define LCD_MAX_SYMBOLS 16
//------------------------------------------------------------------------------
#define CPU_CLOCK 11059200L
//------------------------------------------------------------------------------
#define	Err_NO						0x0000
#define	Err_BAD_EEPROM_RECORD		0x0001
//------------------------------------------------------------------------------
#define SYS_SET_UP_PERIOD	2000
//------------------------------------------------------------------------------
#define MAX_ID	31
//------------------------------------------------------------------------------
#define CONSOLE_BOUNDRATE 	38400
#define RS485_BOUNDRATE 	38400
//------------------------------------------------------------------------------
#define ADC_MAX_NUM			4
#define ADC_FILTER_TAPS		32
#define ADC_SAMPLES_TIME	20		// 10ms
//------------------------------------------------------------------------------
// for 11.0592 MHz
//------------------------------------------------------------------------------
#define UART_BaudRate_2400     287
#define UART_BaudRate_4800     143
#define UART_BaudRate_9600     71
#define UART_BaudRate_14400    47
#define UART_BaudRate_19200    35
#define UART_BaudRate_28800    23
#define UART_BaudRate_38400    17
#define UART_BaudRate_57600    11
#define UART_BaudRate_115200   5

//------------------------------------------------------------------------------
#define Ok   1
#define None 0
#define Err -1
//------------------------------------------------------------------------------
#define ERRORS_I2C      -450
//------------------------------------------------------------------------------
//typedef ulint                   t_ticks;
//#define mat_t_ticks             0xffffffffU
#define  sptr          (char in_flash *)
#define  vptr          (void in_flash *)

#define in_flash  __farflash
#define BOOTFLASH __farflash
#define APPFLASH  __farflash
//------------------------------------------------------------------------------
#define Bit(n)           (1 << n)
#define SetBit(addr,n)   (addr |=  (1 << n))
#define ClearBit(addr,n) (addr &= ~(1 << n))
#define CheckBit(addr,n) (addr &   (1 << n))
//------------------------------------------------------------------------------
#define  ledSys(f)     (f?SetBit(DDRF,0):ClearBit(DDRF,0))
//------------------------------------------------------------------------------
#undef   max
#define  max(a,b)       (((a) > (b)) ? (a) : (b))
#undef   min
#define  min(a,b)       (((a) < (b)) ? (a) : (b))
//------------------------------------------------------------------------------
#define DO_XX   0x00000000
#define DO_00	0x00000001
#define DO_01	0x00000002
#define DO_02	0x00000004
#define DO_03	0x00000008
#define DO_04	0x00000010
#define DO_05	0x00000020
#define DO_06	0x00000040
#define DO_07	0x00000080
#define DO_08	0x00000100
#define DO_09	0x00000200
#define DO_10	0x00000400
#define DO_11	0x00000800
#define DO_12	0x00001000
#define DO_13	0x00002000
#define DO_14	0x00004000
#define DO_15	0x00008000
#define DO_16	0x00010000
#define DO_17	0x00020000
#define DO_18	0x00040000
#define DO_19	0x00080000
#define DO_20	0x00100000
#define DO_21	0x00200000
#define DO_22	0x00400000
#define DO_23	0x00800000
#define DO_24	0x01000000
//------------------------------------------------------------------------------
#endif

