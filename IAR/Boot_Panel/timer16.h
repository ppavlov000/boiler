#ifndef __TIMER16
#define __TIMER16
//-----------------------------------------------------------------------------------
#include "Include\types.h"
//-----------------------------------------------------------------------------------
extern u16 Time0;
extern u16 Time1;
extern u16 Time2;
extern u16 Time3;
extern u16 Time4;
extern u16 Time5;
extern u16 Time6;
extern u16 UPC_Time;
extern u16 UPC_Time2;
//-----------------------------------------------------------------------------------
void Timer_1ms_IRQ();
void Delay(u16 val);// value in ms
//-----------------------------------------------------------------------------------
#endif
