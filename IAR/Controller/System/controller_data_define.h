#ifndef _DATA_DEFINES_H_
#define _DATA_DEFINES_H_
//------------------------------------------------------------------------------
#define NUM_PID				1
#define MAX_FANCOIL_NUMBER	1
#define MAX_KOTEL_NUMBER	0
#define MAX_VALVE_3T_NUMBER	0
//------------------------------------------------------------------------------
#define MAX_KOTEL_MODES		4
#define MAX_KOTEL_FUELS		1		
//------------------------------------------------------------------------------
#define PARAMETERS_MAX		20
//------------------------------------------------------------------------------
#define MAX_ERRORS_NUM		4
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
	#define NUM_AIN_THERMO	0
#endif
//------------------------------------------------------------------------------
#ifdef __HW0323
	#define NUM_DIN		6
	#define NUM_DOUT	7
	#define NUM_AIN		3
	#define NUM_AOUT	1
	#define NUM_AIN_REAL 3
	#define NUM_AIN_THERMO	0
#endif
//------------------------------------------------------------------------------
#ifdef __HW0324
	#define NUM_DIN		6
	#define NUM_DOUT	8
	#define NUM_AIN		4
	#define NUM_AOUT	1
	#define NUM_AIN_REAL 3
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
	#define NUM_AIN		4
	#define NUM_AOUT	1
	#define NUM_AIN_REAL 3
#endif
//------------------------------------------------------------------------------
#ifdef __HW050
	#define NUM_DIN		8
	#define NUM_DOUT	8
	#define NUM_AIN		5
	#define NUM_AOUT	3
	#define NUM_AIN_REAL 3
	#define NUM_AIN_THERMO 1
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
// season definition
#define SEASON_SUMMER	0
#define SEASON_WINTER	1
// season mode definition
#define SEASON_AUTO		0
#define SEASON_MANUAL	1
typedef struct
{
	u8 season;
	u8 mode;
	u8 switch_temperature;
	u8 switch_date;	
	TDateShort date[2];
	s16 t;
	u8 t_extern_channel;
#ifdef	__SHEVCHENKO
	u8 switch_power;			
#endif	
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
	f32 ai_coff[NUM_AIN_REAL];	
	s16 ai_offset[NUM_AIN_REAL];		
}TIO;
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
//	u8 reserve[2];
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
//typedef enum {
//  pid_Winter,
//  pid_Summer,
//}PID_SEASON;
//------------------------------------------------------------------------------
#define PID_HEATING		0
#define PID_COOLING		1
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
	u8 heating_cooling;
}TPID;
//------------------------------------------------------------------------------
typedef struct
{
//	s16	tm[NUM_MIN];		// memory	min
	s16	ts[NUM_SEC];		// memory	sec	
	s16	ti[NUM_INT];		// memory	smples during second
	u8	cs,cm,ch,ci;		// counters	
}TIntMem;
//------------------------------------------------------------------------------
//  Valve 3t parameters
//------------------------------------------------------------------------------
typedef struct
{
	s16	power;		// Input
	u16	t3max;		// period of servoprivod full cycle in sec		
	s16	p3;			// Output
	u8 open;        // Line open
	u8 close;       // Line close
}TValve3t;
//------------------------------------------------------------------------------
//  Fancoil parameters
//------------------------------------------------------------------------------
// Day_Night definitions
#define fan_Day 	0
#define fan_Night 	1

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
	u8 Day_Night;
	u8 Channel;	
//	u8 reserve;		
}TFanCoil;

typedef struct
{
	u8 fan_speed;			// bits 0-low 1-med 2-high
	u8 valve_pos;		// bits 0-heat 1-cooling
}TFanLines;
//------------------------------------------------------------------------------
// Kotel records
//------------------------------------------------------------------------------
typedef struct
{
	s16 		t;	
	u8			fan_speed[2];
	u8			fan_on[2];	
	u8			fan_off[2];	
	u8			smoke_speed;	
	u8			shnek_ena[2];	
	u8			shnek_on[2];
	u8			shnek_off[2];
}TKotelModeRec;

typedef struct
{
	u8 				mode;
	s16 			t;
    u8              channel;
	u8				fuel;
    s16             fan_out[2];
    s16             smoke_out;
    u8              shnek_out[2];
	s16				power;		// Desired valve position
	u16				t3max;		// period of servoprivod full cycle in sec		
	s16				p3;			// Calculated valve position
	u8 				open;
	u8 				close;
	u8				smoke_speed[MAX_KOTEL_FUELS]; // At mode 5 smoke speed
	TKotelModeRec	p[MAX_KOTEL_FUELS][MAX_KOTEL_MODES];	// 3 different fuels and 4 general parameters mode
}TKotel;
//------------------------------------------------------------------------------
// Fast access records
//------------------------------------------------------------------------------
typedef struct
{
	u32 serial;
	TCTime time;
}TProgramInfoRecord;

typedef struct
{
	u8 identificator;
	TProgramInfoRecord prog[2];
}TProgramInfo;

#define TYPE_NOT_DEFINED	0
#define TYPE_FANCOIL_2X		1
#define TYPE_FANCOIL_4X		2
#define TYPE_PRITOCHKA		3
#define TYPE_KOTEL			4

#define TYPE_ALL_SEASON		90
#define TYPE_ALL_T			91
typedef struct
{
	u8 type;
	u8 season;
	u8 mode;
	s16 temperature[3];
	s16 speed[3];
}TWorkInfo;
//------------------------------------------------------------------------------
// Controller record
//------------------------------------------------------------------------------
typedef struct
{
	TIO 			_io;
	TMenuRegisters 	menu_regs;
	TErrors 		_errors;	
#if MAX_VALVE_3T_NUMBER!=0
	TPID 			v3t[MAX_VALVE_3T_NUMBER];
#endif
#if NUM_PID!=0
	TPID 			_pid[NUM_PID];
#endif
#if MAX_FANCOIL_NUMBER!=0
	TFanCoil 		_fan[MAX_FANCOIL_NUMBER];
#endif
#if MAX_KOTEL_NUMBER!=0
	TKotel			_kotel;
#endif
}TControllerFields;
typedef union
{
	TControllerFields field;
	u8 d[sizeof(TControllerFields)];
}TController;
//------------------------------------------------------------------------------
extern TController CV;
#define io CV.field._io
#define pid CV.field._pid
#define MenuRegs CV.field.menu_regs
#define errors CV.field._errors
#define fan CV.field._fan
#define reg_data CV.d
#define reg_season CV.field.menu_regs.Season
#define kotel CV.field._kotel
//------------------------------------------------------------------------------
//typedef struct
//{
//	
//}TSysExchange;
//------------------------------------------------------------------------------
#endif

