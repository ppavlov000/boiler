#ifndef __UARTMISC
#define __UARTMISC
//---------------------------------------------------------------------------
#include "..\Misc\types.h"
//---------------------------------------------------------------------------
#define PREAMBULA_LOW	0xAA
#define PREAMBULA_HIGH	0x55
#define PACKET_HEADER_LEN 7
#define CHANNELS_NUM 2
//---------------------------------------------------------------------------
// command structure
struct COMMAND_BITS {     // bits  description
    u16  id:4;		// 3:0   Address of device
    u16  req:1;		// 4     Request is needed
    u16  com:11; 	// 15..5  Command
};

typedef union {
   u16     all;
   struct COMMAND_BITS bit;
}COMMAND_REG;
// Requests
// commands list
#define com_none				0
#define com_get_stat			1
#define com_get_io				2
#define com_get_errors			3
#define com_get_pid_0			4
#define com_get_pid_1			5
#define com_get_pid_2			6
#define com_get_pid_3			7


#define com_set_stat			8
#define com_set_io				9
#define com_set_errors			10
#define com_set_pid_0			11
#define com_set_pid_1			12
#define com_set_pid_2			13
#define com_set_pid_3			14

#define com_get_time			15
#define com_set_time			16
#define com_get_time_summ		17
#define com_set_time_summ		18
#define com_get_time_wint		19
#define com_set_time_wint		20
#define com_set_in_params		21
#define com_get_in_params		22
#define com_set_out_params		23
#define com_get_out_params		24
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
#define er_bad_id			3
//---------------------------------------------------------------------------
typedef struct
{
	u8 status;
	u8 Season;
	TTime	ft;
	u8 Auto_Manual;
}TExSTATUS;//44 bytes
//---------------------------------------------------------------------------
typedef struct
{
	u8 num_di;
	u8 num_do;
	u8 num_ai;
	u8 num_ao;			
	u32	din;
	u32 dout;
//	u16 aoutput[NUM_AOUT];	
//	s16 ainput[NUM_AIN];
	u16 analog[NUM_AOUT+NUM_AIN];	
}TExIO;//44 bytes
//---------------------------------------------------------------------------
#define PID_MODE_STOP		0
#define PID_MODE_AUTO		1
#define PID_MODE_ERROR		2
#define PID_MODE_WARNING	3
//---------------------------------------------------------------------------
#define NUM_ExPID	4
//---------------------------------------------------------------------------
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
	f32 PID_POWER_STEP[2];	
}TExPID; //24 bytes
//---------------------------------------------------------------------------
typedef union
{
	TExSTATUS st;
	TTime Time;
	TExIO io;
	TExPID pid;
	TErrors errors;
	s16 Parameters[30];
	u8 d[140];
}TExData;
typedef struct
{
	u16 pre;
	COMMAND_REG com;
	u8 len;
	u16 crc;
	TExData data;
}TBuffFields;
//---------------------------------------------------------------------------
typedef struct
{
	u8 d[128+PACKET_HEADER_LEN];
}TBuffData;
//---------------------------------------------------------------------------
typedef union
{
	TBuffFields field;
	TBuffData data;	
}TBuff;
//---------------------------------------------------------------------------
typedef struct
{
	u16 timeout[CHANNELS_NUM];
	u16 reset[CHANNELS_NUM];
	u16 bad_crc[CHANNELS_NUM];	
}THistory;
//---------------------------------------------------------------------------
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
	u8 channel_state[CHANNELS_NUM+1];
	u8 channel_cycles;
}TUpcState;

//---------------------------------------------------------------------------
/*
#define rx_none			0x0000
#define rx_stat			0x0001
#define rx_io			0x0002
#define rx_pid0			0x0004
#define rx_pid1			0x0008
#define rx_pid2			0x0010
#define rx_pid3			0x0020
#define rx_errors		0x0040
#define rx_time			0x0080
#define rx_time_summ	0x0100
#define rx_time_wint	0x0200
#define rx_protok0_min	0x0400
#define rx_protok1_min	0x0800
#define rx_params		0x1000


#define tx_none			0x0000
#define tx_stat			0x0001
#define tx_io			0x0002
#define tx_pid0			0x0004
#define tx_pid1			0x0008
#define tx_pid2			0x0010
#define tx_pid3			0x0020
#define tx_errors		0x0040
#define tx_time			0x0080
#define tx_time_summ	0x0100
#define tx_time_wint	0x0200
#define rx_protok0_min	0x0400
#define rx_protok1_min	0x0800
#define tx_params		0x1000

typedef struct
{
	u8 channel_state;	// present or not controllers on 0..4 channels
	u16 update_stat;	
	u16 rx_list;			// 0-nothing,1-stat,2-io,3-pid0,...,6-pid3
	u16 tx_list;			// 0-nothing,1-stat,2-io,3-pid0,...,6-pid3	
	TExSTATUS st;
	TTime Time;
	u8 Season;
	u8 Auto_Manual;
	TTime Time_Summ;
	TTime Time_Wint;	
	TExIO io;
	TExPID pid[NUM_ExPID];
	TErrors errors;
	s16 Parameters[30];
	u16 Zaslonka[2];
	u8	Zaslonka_Mode;
}TExController;
*/
//------------------------------------------------------------------------------
#endif
