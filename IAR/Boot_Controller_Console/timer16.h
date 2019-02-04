#ifndef __TIMER16
#define __TIMER16
//-----------------------------------------------------------------------------------
#include <iom128.h>
#include "Include\types.h"
//-----------------------------------------------------------------------------------
extern volatile u16 Time0;
extern volatile u16 Time1;
extern volatile u16 Time2;
extern volatile u16 Time3;
extern volatile u16 Time4;
extern volatile u16 Time5;
//-----------------------------------------------------------------------------------
void Timer_Init();
void Delay(u16 val);// value in ms
//-----------------------------------------------------------------------------------
#endif
