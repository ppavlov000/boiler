#ifndef __INTERPRETATOR_OBJECTS
#define __INTERPRETATOR_OBJECTS
//-----------------------------------------------------------------------------------
#include <iom128.h>
#include "types.h"
#include "header.h"
//-----------------------------------------------------------------------------------
typedef struct
{
	s16 t;				// Temperature of freezzing
	u8 enable;			// Enable 
	u8 detected;		// Error condition reached
	u8 ai_channel;		// Temperature channel
	u8 IRQ_channel;		// IRQ to execute	
}TFreeze;

typedef struct
{
	u32	t;				// Valve time constant
	u8 enable;			// Enable 	
	s16	power;			// Value of opened stae
	s16 power_min;		// limitation of power
	s16 power_max;		// limitation of power	
	u8	do_on;			// Number of on output
	u8	do_off;			// Number of off output	
}T3StateValve;
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
