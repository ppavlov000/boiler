#ifndef __INTERPRETATOR_OBJECTS
#define __INTERPRETATOR_OBJECTS
//-----------------------------------------------------------------------------------
//#include <iom128.h>
#include "types.h"
#include "header.h"
//-----------------------------------------------------------------------------------
typedef struct
{
	u16 code;				// Temperature of freezzing
	u8 detected;		// Error condition reached
	u8 ai_channel;		// Temperature channel
	u8 IRQ_channel;		// IRQ to execute	
}TError;
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void obj_handler();
//-----------------------------------------------------------------------------------
#endif
