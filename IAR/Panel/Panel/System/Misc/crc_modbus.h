#ifndef __CRC_MODBUS
#define __CRC_MODBUS
//---------------------------------------------------------------------------
#include "..\..\..\System\Standard\types.h"
//---------------------------------------------------------------------------
unsigned short CRC16 ( unsigned char *puchMsg,unsigned short usDataLen ); /* The function returns the CRC as a unsigned short type */
//---------------------------------------------------------------------------
#endif
