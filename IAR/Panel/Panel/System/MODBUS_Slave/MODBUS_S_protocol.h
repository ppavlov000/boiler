#ifndef __MODBUS
#define __MODBUS
//---------------------------------------------------------------------------
#include "..\..\System\Standard\types.h"
//---------------------------------------------------------------------------
#define 	MODBUS_BAUND			38400//lc 57600//5;//35;//71;//9600//35;//19200//5;//115200
#define		MODBUS_SILENCE			50//(4*10*100.0/(MODBUS_BAUND))	// 10 bit per byte transmit, 4 symbols
#define 	MOD_TX_BUF_LEN			20
#define 	MOD_RX_BUF_LEN			20
//-----------------------------------------------------------------------------------
evu8 mod_rxd;
evu8 mod_tx[MOD_TX_BUF_LEN];
evu8 mod_rx[MOD_RX_BUF_LEN];
evu8 mod_rx_packet[MOD_RX_BUF_LEN];
evu8 mod_tx_ptr;
evu8 mod_rx_ptr_end;
evu8 mod_rx_ptr_start;
evu8 mod_tx_ptr_end;
evu8 mod_tx_ptr_start;
evu16 mod_rx_timout;
//-----------------------------------------------------------------------------------
#if __MODBUS_ENA==1
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void modbus_s_init();
void modbus_s_TXHandler();
void modbus_s_RXHandler();
void modbus_TxPacket(u8 *str, u8 len);
u8 modbus_s_Check_New_Packet();
void modbus_s_PacketHandler();
//---------------------------------------------------------------------------
#endif
#endif
