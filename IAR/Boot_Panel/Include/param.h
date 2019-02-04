#ifndef __PARAM
#define __PARAM
//---------------------------------------------------------------------------
#include "types.h"
#include "io.h"
#include "errors.h"
#include "fram31xx.h"
//-------------------------------------------------------------------------------------------
#define PARAM_LOCATION 0x00
#define TPARAM_WIDTH sizeof(TParam)
//-------------------------------------------------------------------------------------------
typedef struct
{
	TIO io;
	u16 CRC;
}TParam;
//-------------------------------------------------------------------------------------------
#endif

