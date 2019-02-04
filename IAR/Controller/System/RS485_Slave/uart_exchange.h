#ifndef __EXCHANGE
#define __EXCHANGE
//---------------------------------------------------------------------------
#include "..\Misc\types.h"
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
#define but_Living_Room				0x00000800
#define but_Living_Room_Short		0x00001000
#define but_Entrance_Room			0x00002000
#define but_Entrance_Room_Short		0x00010000
#define but_Main_1					0x00004000
#define but_Main_2					0x00008000
#define but_Main_3					0x00080000
#define	but_Living_Curtain_0		0x00040000
#define	but_Living_Curtain_1		0x00020000

#define mask_curtains_do		(but_DO_14+but_DO_15+but_DO_16+but_DO_17)		
#define mask_fancoil_do			(but_DO_18+but_DO_19+but_DO_20+but_DO_21+but_DO_22+but_DO_23+DO_24+DO_25+DO_26+DO_27)
#define mask_simple_do			0x00003fff		// exept curtains and fancoil

#define but_DO_00	0x00000001
#define but_DO_01	0x00000002
#define but_DO_02	0x00000004
#define but_DO_03	0x00000008
#define but_DO_04	0x00000010
#define but_DO_05	0x00000020
#define but_DO_06	0x00000040
#define but_DO_07	0x00000080
#define but_DO_08	0x00000100
#define but_DO_09	0x00000200
#define but_DO_10	0x00000400
#define but_DO_11	0x00000800
#define but_DO_12	0x00001000
#define but_DO_13	0x00002000
#define but_DO_14	0x00004000
#define but_DO_15	0x00008000
#define but_DO_16	0x00010000
#define but_DO_17	0x00020000
#define but_DO_18	0x00040000
#define but_DO_19	0x00080000
#define but_DO_20	0x00100000
#define but_DO_21	0x00200000
#define but_DO_22	0x00400000
#define but_DO_23	0x00800000

#define	but_Int0					0x80000000
#define	but_Int1					0x40000000
#define	but_Int2					0x20000000
#define	but_Int3					0x10000000
#define	but_Int4					0x08000000
#define	but_Int5					0x04000000
#define	but_Int6					0x02000000

#define	but_Int0s					0x80
#define	but_Int1s					0x40
#define	but_Int2s					0x20
#define	but_Int3s					0x10
#define	but_Int4s					0x08
#define	but_Int5s					0x04
#define	but_Int6s					0x02

#define but_Int_Mask				0xff000000
//---------------------------------------------------------------------------
#define bit_new_push				0x01
//---------------------------------------------------------------------------
typedef struct
{
	u8	Minute;	
	u8	Hour;	
}TTimeFieldsShort;
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
