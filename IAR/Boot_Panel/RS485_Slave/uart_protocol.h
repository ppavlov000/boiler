#ifndef __UARTPROTOCOL
#define __UARTPROTOCOL
//---------------------------------------------------------------------------
#include "..\Include\types.h"
#include "uart_misc.h"
//---------------------------------------------------------------------------
extern TBuff rx,tx;
extern TUpcState upc;
eu8 first_start;
//---------------------------------------------------------------------------
void upc_init();
void upc_en(u8 en);
void upc_TXHandler();
u16 upc_crc_(TBuff *buff);
u16 upc_crc_head(TBuff *buff);
u16 upc_crc_data(TBuff *buff);

void upc_RXHandler();
void upc_answer_boot_mode();
void upc_answer_info(u8 what);
void upc_answer_prog(u8 what);
void upc_answer_flash_read(u32 address);
void upc_answer_status();
//---------------------------------------------------------------------------
#endif
