#ifndef __EXCHANGE
#define __EXCHANGE
//---------------------------------------------------------------------------
#include "..\Include\types.h"
//---------------------------------------------------------------------------

// Buttons number define
#define	but_Main_Switch				0x00000001
#define	but_Entrance_Light			0x00000002
#define	but_DoNot_Disturb			0x00000004
#define	but_Make_Up_Room			0x00000008
#define	but_Reading_Light_Left		0x00000010
#define	but_Reading_Light_Right		0x00000020
#define	but_Night_Stand_Light_Left	0x00000040
#define	but_Night_Stand_Light_Right	0x00000080
#define	but_Bedroom_Curtain_0		0x00000100
#define	but_Bedroom_Curtain_1		0x00000200
#define	but_Mood_Light				0x00000400
#define but_Lights					0x00000800
#define but_Dressing_Room			0x00001000
#define but_Floor_Lamp				0x00002000
#define but_Chandelier				0x00004000
#define but_Koltuk					0x00008000

#define	but_Int0					0x80000000
#define	but_Int1					0x40000000
#define	but_Int2					0x20000000
#define	but_Int3					0x10000000
#define	but_Int4					0x08000000
#define	but_Int5					0x04000000

#define	but_Int0s					0x80
#define	but_Int1s					0x40
#define	but_Int2s					0x20
#define	but_Int3s					0x10
#define	but_Int4s					0x08
#define	but_Int5s					0x04

#define but_Int_Mask				0xff000000
//---------------------------------------------------------------------------
#define bit_new_push				0x01
//---------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------
typedef union
{
	TTimeFields field;
	u8	data[7];
}TTime;
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
//-------------------------------------------------------------------------------------------
typedef struct
{
	u8		present;
	u32		HW_Version;
	u32		SW_Version;
	TTime Time;
}TPanelInfo;
//---------------------------------------------------------------------------
typedef struct
{
	u32 bst;	// Each bit is correcponding to button
	u8	status;	// What is changing
}TExchange;
//---------------------------------------------------------------------------
#define	bit_none	0
#define	bit_butt	1
#define	bit_min		2
#define	bit_hour	3
#define	bit_day		4
#define	bit_month	5
#define	bit_year	6
#define	bit_temp	7
//---------------------------------------------------------------------------
extern TExchange exch;
//extern TExchange old_exch;
extern TExchange own_state;
//---------------------------------------------------------------------------
#endif
