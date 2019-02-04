#ifndef __UARTPROTOCOL
#define __UARTPROTOCOL
//---------------------------------------------------------------------------
#include "..\Misc\types.h"
#include "uart_misc.h"
//---------------------------------------------------------------------------
extern TBuff rx,tx;
extern TUpcState upc;
//extern TExchange own_state;
//eu8 re_status;
//eu8 received;
eu8 first_start;
//eu8 m_Address;
//---------------------------------------------------------------------------
void upc_init();
void upc_RXHandler();
void upc_TXHandler();
u16 upc_crc_data(TBuff *buff);
u16 upc_crc_head(TBuff *buff);
void upc_answer_sys();
void upc_answer_io();
//void upc_answer_pid(u8 pid_num);
//void upc_answer_errors();

void upc_set_sys();
void upc_set_io();
//void upc_set_pid(u8 pid_num);
//void upc_set_errors();

void upc_answer_time();
//void upc_answer_time_summ();
//void upc_answer_time_wint();
void upc_set_time();
//void upc_set_time_summ();
//void upc_set_time_wint();
void upc_set_in_parameters();
void upc_answer_out_parameters();
void upc_answer_set_manual();
//void upc_answer_get_season();
//void upc_answer_set_season();

void upc_answer_set_register();
void upc_answer_get_register();
//---------------------------------------------------------------------------
#endif
