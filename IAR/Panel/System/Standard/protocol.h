#ifndef __PROTOCOL
#define __PROTOCOL
//---------------------------------------------------------------------------
#include "types.h"
//---------------------------------------------------------------------------
#define PREAMBULA_LOW	0xAA
#define PREAMBULA_HIGH	0x55
#define PACKET_HEADER_LEN 9
//---------------------------------------------------------------------------
#define MAX_ANSWER_DELAY	20	// ms UPC_Time
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
//---------------------------------------------------------------------------
// Requests
#define com_reqt_status				0	//1..5
#define com_reqt_1					1	//single
#define com_reqt_2					2	//single
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
#define com_set_tansp   			18	// Set panel to transparent mode
#define com_release_transp			19	// Release panel from transparent mode
#define com_transp					50	// Transparent packet


#define com_get_stat	20
#define com_get_io		21
#define com_get_errors	22
#define com_get_pid_0	23
#define com_get_pid_1	24
#define com_get_pid_2	25
#define com_get_pid_3	26


#define com_set_stat	27
#define com_set_io		28
#define com_set_errors	29
#define com_set_pid_0	30
#define com_set_pid_1	31
#define com_set_pid_2	32
#define com_set_pid_3	33


#define com_get_time		34
#define com_set_time		35
#define com_get_time_summ	36
#define com_set_time_summ	37
#define com_get_time_wint	38
#define com_set_time_wint	39
#define com_set_in_params		40
#define com_get_in_params		41
#define com_set_out_params		42
#define com_get_out_params		43
#define com_store_params	44
#define com_set_manual		45

#define com_get_season		46
#define com_set_season		47

#define com_get_register	50
#define com_set_register	51

#define com_get_work_rec	52
#define com_set_work_rec	53

#define com_get_prog_rec	54
//---------------------------------------------------------------------------
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
//	u8 id;	
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
#endif
