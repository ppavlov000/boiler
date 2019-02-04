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
#define NUM_PID				2
//------------------------------------------------------------------------------
#define MAX_FANCOIL_NUMBER	1
//------------------------------------------------------------------------------
#define PARAMETERS_MAX		20
//------------------------------------------------------------------------------
#define MAX_ERRORS_NUM		5
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
#ifdef __HW030
	#define NUM_DIN		4
	#define NUM_DOUT	5
	#define NUM_AIN		4
	#define NUM_AOUT	2
#endif
//------------------------------------------------------------------------------
#ifdef __HW031
	#define NUM_DIN		6
	#define NUM_DOUT	5
	#define NUM_AIN		4
	#define NUM_AOUT	2
#endif
//------------------------------------------------------------------------------
#ifdef __HW0322
	#define NUM_DIN		6
	#define NUM_DOUT	7
	#define NUM_AIN		3
	#define NUM_AOUT	1
#endif
//------------------------------------------------------------------------------
#ifdef __HW0323
	#define NUM_DIN		6
	#define NUM_DOUT	7
	#define NUM_AIN		3
	#define NUM_AOUT	1
#endif
//------------------------------------------------------------------------------
#ifdef __HW0324
	#define NUM_DIN		6
	#define NUM_DOUT	8
	#define NUM_AIN		3
	#define NUM_AOUT	1
#endif
//------------------------------------------------------------------------------
#ifdef __HW0325
	#define NUM_DIN		6
	#define NUM_DOUT	6
	#define NUM_AIN		3
	#define NUM_AOUT	1
#endif
//------------------------------------------------------------------------------
#ifdef __HW0326
	#define NUM_DIN		7
	#define NUM_DOUT	7
	#define NUM_AIN		3
	#define NUM_AOUT	1
#endif
//------------------------------------------------------------------------------
#ifdef __SIMULATOR
	#define NUM_DIN		6
	#define NUM_DOUT	5
	#define NUM_AIN		4
	#define NUM_AOUT	2
	#define  __farflash
#endif
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
typedef enum {
  eSw_On,
  eSw_Off,
  eSw_Unknown
} E_ON_OFF;
//------------------------------------------------------------------------------
// Timers
//------------------------------------------------------------------------------
typedef struct
{
	u8	Second;
	u8	Minute;	
	u8	Hour;	
	u8	Day;	
	u8	Date;	
	u8 	Month;	
	u8	Year;	
}TTimeFields;
typedef union
{
	TTimeFields field;
	u8	data[7];
}TCTime;
//------------------------------------------------------------------------------
typedef struct
{
	u8	Minute;	
	u8	Hour;	
}TTimeShortFields;
typedef union
{
	TTimeShortFields field;
	u8	data[2];
}TCTimeShort;
//-----------------------------------------------------------------------------------
typedef struct
{
	u8	Date;	
	u8	Month;	
}TDateFieldsShort;
typedef union
{
	TDateFieldsShort field;
	u8	data[2];
}TDateShort;
//------------------------------------------------------------------------------
// Season definitions
//------------------------------------------------------------------------------
typedef struct
{
	u8 season;
	u8 mode;
	u8 switch_temperature;
	u8 switch_date;	
	TDateShort date[2];
	s16 t;
	u8 switch_power;			
	s16 power_min_summer;
	s16 power_min_winter;	
}TSeason;
//------------------------------------------------------------------------------
// IO definitions
//------------------------------------------------------------------------------
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
	f32 ao_coff[NUM_AOUT];	
	f32 ai_coff[NUM_AIN];	
	s16 ai_offset[NUM_AIN];		
//	u8 ai_type[NUM_AIN];			
//	s16 tmp;
}TIO;
//TIO_Static;
//------------------------------------------------------------------------------
// Menu LCD registers
//------------------------------------------------------------------------------
typedef struct
{
	u8 pass_user[5];	// Password only digits
	u8 pass_admin[5];	// Password only digits	
	u8 password;// Sign of password
	u8 lang;	// Language of menu 0 - english 1-russian
	TCTime Time;
	TSeason	Season;
	u8 Manual_Mode;
	u8 reserve[2];
//	s16	params[PARAMETERS_MAX];	
	u8 Schedule_Enable;
	TCTimeShort	Schedule_Time[2];
	u8 Timer_Enable;
	TCTimeShort	Timer_Time[2];
}TMenuRegisters;

#define MANUAL_MODE 0x01
#define AUTO_MODE 	0x00
//------------------------------------------------------------------------------
// Errors record
//------------------------------------------------------------------------------
typedef struct
{
	s16	code;
	TCTime time;
}TError_msg;
//------------------------------------------------------------------------------
typedef struct
{
	TError_msg item[MAX_ERRORS_NUM];
}TErrors;
//------------------------------------------------------------------------------
// PID
//------------------------------------------------------------------------------
#define NUM_INT		10
#define NUM_SEC		30
#define NUM_MIN		60
//------------------------------------------------------------------------------
#define NUM_VALVE_STEP		2
//------------------------------------------------------------------------------
#define PID_MODE_STOP		0
#define PID_MODE_AUTO		1
#define PID_MODE_ERROR		2
#define PID_MODE_WARNING	3
//------------------------------------------------------------------------------
typedef enum {
  pid_Winter,
  pid_Summer,
}PID_SEASON;
//------------------------------------------------------------------------------
typedef struct
{
//	u8 tmp;
	u8 channel;		// number of AI as input
	s16	p;			// proportional
	s16	i;			// integral
	s16	d;			// differential cofficient
	s16	t0;			// Desired temperature
	s16	power;		// output of pid
	s16 power_min;	// limitation of power
	s16 power_max;	// limitation of power
	u8 mode;		//0-disable 1-enable
	u16	ti;			// period of integration in sec	
	u16	t3max;		// period of servoprivod full cycle in sec		
	s16	p3;			// output of pid
	u8 open;
	u8 close;
	f32 PID_POWER_STEP[2];	// 0 - slow speed, 1 - fast speed
	u16 PID_POWER_LIMIT[2];	// 0 - zero power border, 1 - low power border
}TPID;
//------------------------------------------------------------------------------
typedef  struct
{
	TPID p[NUM_PID];
}TPID_STRUCT;
//------------------------------------------------------------------------------
typedef struct
{
//	s16	tm[NUM_MIN];		// memory	min
	s16	ts[NUM_SEC];		// memory	sec	
	s16	ti[NUM_INT];		// memory	smples during second
	u8	cs,cm,ch,ci;		// counters	
}TIntMem;
//------------------------------------------------------------------------------
//  Fancoil parameters
//------------------------------------------------------------------------------
typedef struct
{
	s16 T;
	u8 Fan_Mode;	
	u8 Fan_Lvl;	
	s8 Valve;
	s16 TLow;
	s16 TMedium;
	s16 THigh;		
	s16 Hysteresis;
	u16 Fan_Time;
	u16 Valve_Time_1;	
	u16 Valve_Time_2;
	s16 Valve_Hysteresis;
}TFanCoil;
//------------------------------------------------------------------------------
// Controller record
//------------------------------------------------------------------------------
typedef struct
{
	TIO io;
	TPID pid[NUM_PID];	
	TMenuRegisters MenuRegs;
	TErrors errors;	
	TFanCoil fan[MAX_FANCOIL_NUMBER];
}TController;
//------------------------------------------------------------------------------
// Parameters record
//------------------------------------------------------------------------------
#define PARAM_LOCATION_0 0x0002
#define PARAM_LOCATION_1 0x0100
#define TPARAM_WIDTH sizeof(TController)
//------------------------------------------------------------------------------
typedef struct
{
	TController	CV;
	u16 CRC;
}TParam;
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

