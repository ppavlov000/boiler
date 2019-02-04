#ifndef _XMODEM_H_
#define _XMODEM_H_
//-----------------------------------------------------------------------------------
#include "types.h"
//-----------------------------------------------------------------------------------
#define SOH 0x01
#define EOT 0x04
#define ACK 0x06
#define NAK 0x15
#define CAN 0x18
//-----------------------------------------------------------------------------------
// Status of operation
#define XMOD_None 	0	// no error
#define XMOD_Ok 		1
#define XMOD_Error	2
//-----------------------------------------------------------------------------------
#define XMOD_DataSize			128
#define XMOD_AttemptsCount 10
#define XMOD_AttemptsTimer 4000	// 6s
#define XMOD_PacketTimer	 10000	// 6s
//-----------------------------------------------------------------------------------
typedef struct {
	u8	State;
	u8	SubState;
	u16 Block;
	u16 Attempt;
	u16 Received;
	u8 Packet[XMOD_DataSize];
	u8 Lrc;
} XMODEM;
extern XMODEM Xmodem;
//-----------------------------------------------------------------------------------
#define XMOD_St_NextAttempt		1
#define XMOD_St_WaitBegin			2
#define	 XMOD_SSt_WaitSohOrEot	 1
#define	 XMOD_SSt_WaitSeq				2
#define	 XMOD_SSt_WaitCmplSeq		3
#define XMOD_St_ReceivePacket	3
#define XMOD_St_CheckPacket		4
#define XMOD_St_SavePacket		 5
//-----------------------------------------------------------------------------------
void Xmodem_Start();
void Xmodem_SetState(u8 st,u8 sst);
u8 Xmodem_Processor();
#endif
