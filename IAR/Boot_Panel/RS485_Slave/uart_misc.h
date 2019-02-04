#ifndef __UARTMISC
#define __UARTMISC
//---------------------------------------------------------------------------
#include "..\Include\types.h"
//---------------------------------------------------------------------------
#define PREAMBULA_LOW	0xAA
#define PREAMBULA_HIGH	0x55
#define PACKET_HEADER_LEN 9
//---------------------------------------------------------------------------
// command structure
struct COMMAND_BITS {     // bits  description
    u16  id:5;		// 3:0   Address of device
    u16  req:1;		// 4     Request is needed
    u16  com:8; 		// 14..5  Command
    u16  trans:1;		// Transparent packet
};

typedef union {
   u16     all;
   struct COMMAND_BITS bit;
}COMMAND_REG;
// Requests
#define com_reqt_status				0	//1..5
#define com_reqt_1					1	//single
#define com_reqt_boot				2	//single
#define com_reqt_start				3	//Starts all panels
#define com_reqt_reset				4 // 0
#define com_reqt_sys_info			5 //
#define com_reqt_sys_name			6 //
#define com_reqt_menu_info			7 //
#define com_reqt_menu_name			8 //
#define com_reqt_prog_start_sys		9 //
#define com_reqt_prog_start_menu	10 //
#define com_reqt_prog				11 //
#define com_reqt_prog_stop			12 //
#define com_reqt_flash_read			13 //


#define com_reqt_res_hw				14	// Reset all with equal HW
#define com_reqt_boot_hw			15	// Enter boot all with equal HW

#define com_reqt_prog_start_sys_hw		16 //
#define com_reqt_prog_start_menu_hw		17 //

#define BOOT_PANEL			0x01
#define BOOT_CONTROLLER		0x02
#define MAIN_PANEL			0x03
#define MAIN_CONTROLLER		0x04
//---------------------------------------------------------------------------
#define st_none				0
#define st_sending			1
#define st_wait_answer		2
#define st_answer_process	3
#define st_complete			4
//---------------------------------------------------------------------------
#define er_none				0
#define er_no_answer		1
#define er_bad_crc			2
//---------------------------------------------------------------------------
typedef struct
{
	u16 pre;
	COMMAND_REG com;
	u8 len;
	u16 crc_data;	
	u16 crc_head;
	u8 d[140];
}TBuffFields;
//---------------------------------------------------------------------------
typedef struct
{
	u8 d[140+PACKET_HEADER_LEN];
}TBuffData;
//---------------------------------------------------------------------------
typedef union
{
	TBuffFields field;
	TBuffData data;	
}TBuff;
//---------------------------------------------------------------------------
// re_status bits
#define b_buttons_pending		0x01
#define b_fancoil_pending		0x02
#define b_time_pending			0x04
// data_status bits
#define b_buttons_new			0x01
#define b_fancoil_new			0x02
#define b_time_new				0x04
typedef struct
{
	u8 txnew;
	u8 rxnew;
	u8 rxcount;
	u8 txcount;	
	u8 status;
	u8 error;	
	u8 done;
	u8 channel;
	// Exchange parameters
	u8 re_status;
	u8 data_status;
}TUpcState;
//---------------------------------------------------------------------------
#endif
