#ifndef __DATA_DEFINE
#define __DATA_DEFINE
//-----------------------------------------------------------------------------------
typedef struct
{
	u8 Power[8];	
	u8 State;
}TDimmer;
//-----------------------------------------------------------------------------------
typedef struct
{
	u8 Power;	
	u8 Channel;
	u8 State;	
}TDimmer_Short;
//-----------------------------------------------------------------------------------
typedef struct
{
	u8	Minute;	
	u8	Hour;	
}TTimeFieldsShort;
//-----------------------------------------------------------------------------------
typedef union
{
	TTimeFieldsShort field;
	u8	data[2];
}TTimeShort;
//-----------------------------------------------------------------------------------
typedef struct
{
	u8	Second;
	u8	Minute;	
	u8	Hour;	
	u8	Day;	
	u8	Date;	
	u8 	Month;	
	u8	Year;	
}TTimeFullFields;

typedef union
{
	TTimeFullFields field;
	u8	data[7];
}TTimeFull;
//-------------------------------------------------------------------------------------------
typedef struct
{
  u8  		Name[103];
  u32		HW_Version;
  u32		SW_Version;
  TTimeFull Time;
  u8  		WH_Update;
  u8  		Flag;
  u32 		Length;
  u16 		CRC_D;	// CRC of data
  u16 		CRC_H;	// CRC of header
}THead;
//-------------------------------------------------------------------------------------------
typedef struct
{
	u8		present;
	u32		HW_Version;
	u32		SW_Version;
	TTimeFull Time;
}THeadShort;
//-------------------------------------------------------------------------------------------
typedef struct
{
	THeadShort	Info[2];
}TPanelInfo;
//-----------------------------------------------------------------------------------
typedef struct
{
	u32 bst;	// Each bit is correcponding to button
	u8	status;	// What is changing
	TDimmer_Short ds;
	u8 Password_Mode;
	u8 Password_Downcount;		
}TExchange;
//-----------------------------------------------------------------------------------
#define	bit_none	0
#define	bit_butt	1
#define	bit_min		2
#define	bit_hour	3
#define	bit_day		4
#define	bit_month	5
#define	bit_year	6
#define	bit_temp	7
//-----------------------------------------------------------------------------------
typedef struct
{
	u8 Digit[16];
}TPhoneRecord;
//-----------------------------------------------------------------------------------
#define PASS_SYMBOLS	6
//-----------------------------------------------------------------------------------
typedef struct
{
	u8 Digit[PASS_SYMBOLS];
}TPassword;
//-----------------------------------------------------------------------------------
typedef struct
{
	TPassword Password;
	TPhoneRecord PhoneList[5];
}TCustomInfo;
//-----------------------------------------------------------------------------------
extern u8 	Password_Mode;
#define PM_NONE						0
#define PM_ACTIVATION_COUNTDOWN		1
#define PM_ALARM_COUNTDOWN			2
#define PM_ARMED					3
#define PM_ALARM					4
#define PM_NEW_PASSWORD				5
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
#define TTime TCTime
typedef struct
{
	u8 	id;
	u8	type;
	u32		hw_sys;
	TTime	sys_time;	
	u32		hw_usr;
	TTime	usr_time;	
	u8 	mode;
	s16	t;
	s16	tp;
	s16 power;
}TDevice_Info;
//-----------------------------------------------------------------------------------
#define MAX_DEVICES_NUM	32
//-----------------------------------------------------------------------------------
#endif
