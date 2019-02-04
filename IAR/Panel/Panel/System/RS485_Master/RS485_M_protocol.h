#ifndef __RS485_M_PROTOCOL
#define __RS485_M_PROTOCOL
//---------------------------------------------------------------------------
#include "..\..\System\Standard\types.h"
//---------------------------------------------------------------------------
#define M_port		PORTA
#define M_pins		PINA
#define M_port_dir	DDRA

//#define M_pin_rx		0x04
//#define M_pin_tx		0x08
#define M_pin_mode	0x20
//---------------------------------------------------------------------------
extern TBuff M_rx,M_tx;
extern TMState M;
//extern TExchange exch;
//extern TExchange own_state;
extern TMHistory M_history;
//extern TExController mcu;
eu8 received;
//extern TExData *ExData;
extern TExSTATUS *Status;
extern TBuff M_buff;
extern u8 M_buff_sign;
extern u8 M_SCH_Time;
//extern TErrors errors;
//extern u8 Transparent_Mode;
//---------------------------------------------------------------------------
void M_init();
void M_state_machine();
void M_TXHandler();
void M_RXHandler();
void M_handler();
u16 M_crc(TBuff *buff);
void M_Set_Channel(u8 channel);
void M_port_switch(u8 channel);


void M_Schedule();
//void M_Set_Panel_Status();
//void M_Set_Panel_Time();
//void M_Set_Panel_Temperature();


void M_Get_Controller_Status(u8 id,u8 channel);
void M_Get_Controller_IO(u8 id,u8 channel);
void M_Get_Controller_PID(u8 pid_num,u8 id,u8 channel);
void M_Get_Controller_Errors(u8 id,u8 channel);
void M_Get_Controller_Time(u8 id,u8 channel);
void M_Get_Controller_Time_Summ(u8 id,u8 channel);
void M_Get_Controller_Time_Wint(u8 id,u8 channel);

void M_Set_Controller_Errors(u8 id,u8 channel);
void M_Set_Controller_IO(u8 id,TIO *pio);
void M_Set_Controller_Status(u8 id,u8 channel);
void M_Set_Controller_PID(u8 pid_num,u8 id, TPID *ppid);
void M_Set_Controller_Time(u8 id,u8 channel);
void M_Set_Controller_Time_Summ(u8 id,u8 channel);
void M_Set_Controller_Time_Wint(u8 id,u8 channel);

//void M_Get_Protok(u8 number);
//void M_Set_Protok(u8 number);
void M_Set_Controller_In_Params(u8 id,u8 channel);
void M_Set_Controller_Out_Params(u8 id,u8 channel);
void M_Get_Controller_In_Params(u8 id,u8 channel);
void M_Get_Controller_Out_Params(u8 id,u8 channel);

void M_Set_Controller_Register(u8 id,void *reg_addr,u8 len);
void M_Get_Controller_Register(u8 id,void *reg_addr,u8 len);
//---------------------------------------------------------------------------
#endif
