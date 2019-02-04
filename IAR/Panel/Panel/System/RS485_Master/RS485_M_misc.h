#ifndef __UARTMISC
#define __UARTMISC
//---------------------------------------------------------------------------
#include "..\..\System\Standard\types.h"
//---------------------------------------------------------------------------
#define CHANNELS_NUM 32
//---------------------------------------------------------------------------
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
	u8 Manual_Mode;	
	u8 Controller_Mode;
	s16 Preset_Temperature;	
	s16 Preset_Speed;
	s16 Temperature;
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
typedef struct
{
	u8 timeout[CHANNELS_NUM];
	u16 reset[CHANNELS_NUM];
	u8	lost[CHANNELS_NUM];	
	u8 packets[CHANNELS_NUM];	
}TMHistory;
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
}TMState;
//------------------------------------------------------------------------------
#endif
