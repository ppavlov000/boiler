#ifndef __UARTPROTOCOL
#define __UARTPROTOCOL
//---------------------------------------------------------------------------
#include "..\Misc\types.h"
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#define EMT_Panel
//#define EL_Panel
//---------------------------------------------------------------------------
#define upc_port		PORTD
#define upc_pins		PIND
#define upc_port_dir	DDRD

#define pin_rx		0x04
#define pin_tx		0x08
#define pin_mode	0x10

#define switch_port		PORTA
#define switch_pins		PINA
#define switch_port_dir	DDRA

#define pin_s0		0x01
#define pin_s1		0x02
#define pin_s2		0x04
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
extern TBuff rx,tx;
extern TUpcState upc;
//extern TExchange exch;
//extern TExchange own_state;
extern THistory history;
//extern TExController mcu;
eu8 received;
//---------------------------------------------------------------------------
void upc_init();
void upc_state_machine();
void upc_TXHandler();
void upc_RXHandler();
void upc_handler();
u16 upc_crc(TBuff *buff);
void upc_Set_Channel(u8 channel);
void upc_port_switch(u8 channel);

//void upc_Set_Panel_Status();
//void upc_Set_Panel_Time();
//void upc_Set_Panel_Temperature();


void upc_Get_Controller_Status(u8 id,u8 channel);
void upc_Get_Controller_IO(u8 id,u8 channel);
void upc_Get_Controller_PID(u8 pid_num,u8 id,u8 channel);
void upc_Get_Controller_Errors(u8 id,u8 channel);
void upc_Get_Controller_Time(u8 id,u8 channel);
void upc_Get_Controller_Time_Summ(u8 id,u8 channel);
void upc_Get_Controller_Time_Wint(u8 id,u8 channel);

void upc_Set_Controller_Errors(u8 id,u8 channel);
void upc_Set_Controller_IO(u8 id,u8 channel);
void upc_Set_Controller_Status(u8 id,u8 channel);
void upc_Set_Controller_PID(u8 pid_num,u8 id,u8 channel);
void upc_Set_Controller_Time(u8 id,u8 channel);
void upc_Set_Controller_Time_Summ(u8 id,u8 channel);
void upc_Set_Controller_Time_Wint(u8 id,u8 channel);

//void upc_Get_Protok(u8 number);
//void upc_Set_Protok(u8 number);
void upc_Set_Controller_In_Params(u8 id,u8 channel);
void upc_Set_Controller_Out_Params(u8 id,u8 channel);
void upc_Get_Controller_In_Params(u8 id,u8 channel);
void upc_Get_Controller_Out_Params(u8 id,u8 channel);
//---------------------------------------------------------------------------
#endif
