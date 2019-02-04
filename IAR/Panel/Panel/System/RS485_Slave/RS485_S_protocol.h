#ifndef __UARTPROTOCOL
#define __UARTPROTOCOL
//---------------------------------------------------------------------------
#include "..\..\System\Standard\types.h"
//---------------------------------------------------------------------------
#define	but_Int0					0x01000000
#define	but_Int1					0x02000000
#define	but_Int2					0x04000000
#define	but_Int3					0x08000000
#define	but_Int4					0x10000000
#define	but_Int5					0x20000000
#define	but_Int6					0x40000000
#define	but_Int7					0x80000000

#define	but_Int0s					0x01
#define	but_Int1s					0x02
#define	but_Int2s					0x04
#define	but_Int3s					0x08
#define	but_Int4s					0x10
#define	but_Int5s					0x20
#define	but_Int6s					0x40
#define	but_Int7s					0x80

//#define but_Int_Mask				0x00000000
//---------------------------------------------------------------------------
#define bit_new_push				0x01
// re_status bits
#define b_buttons_pending		0x01
#define b_fancoil_pending		0x02
#define b_time_pending			0x04
// data_status bits
#define b_buttons_new			0x01
#define b_fancoil_new			0x02
#define b_time_new				0x04
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
	// Exchange parameters
	u8 re_status;
	u8 data_status;
//	TTime ft;	
//	TExchange exch;
}TUpcState;
//---------------------------------------------------------------------------
extern TExchange exch;
//extern TExchange old_exch;
extern TExchange own_state;
//---------------------------------------------------------------------------
extern TBuff rx,tx;
extern TUpcState upc;
//extern TExchange own_state;
//eu8 re_status;
//eu8 received;
eu8 first_start;
//-----------------------------------------------------------------------------------
// Common function
u16 upc_crc_head(TBuff *buff);
u16 upc_crc_data(TBuff *buff);
//---------------------------------------------------------------------------
#if __MODBUS_ENA==0
//---------------------------------------------------------------------------
void upc_init();
void upc_TXHandler();
void upc_Set_Panel_Temperature();
void upc_Set_Panel_Time();
void upc_answer_sys();
void upc_answer_reset();
void upc_RXHandler();
void upc_answer_info(u8 what);
void upc_answer_alarm();
void upc_answer_set_alarm();
void upc_Answer_Custom_Info();
void upc_Set_Custom_Info();

void upc_answer_set_transparent();
void upc_answer_release_transparent();
void upc_S_transparent_packet();
void upc_S_transparent_packet_2();
void upc_S_return_transparent_packet();
void M_Set_Manual_Mode(u8 id,u8 mode);
void M_Set_Season(u8 id,TSeason *_season);
void M_Get_Season(u8 id);
//---------------------------------------------------------------------------
#endif
#endif

