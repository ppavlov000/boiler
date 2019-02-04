//------------------------------------------------------------------------------
#ifndef __TIMER16
#define __TIMER16
//------------------------------------------------------------------------------
#include "..\main.h"
//------------------------------------------------------------------------------
//#define MAX_BUZZER_TIME 10
//------------------------------------------------------------------------------
extern volatile u16 Time0;
extern volatile u16 Time1;
extern volatile u16 PID_Test_Time;
extern volatile u16 Time5;
extern volatile u16 FramTime;
extern volatile u16 SysSetUp;
extern volatile u16 Adc_Time;
extern volatile u16 LCD_Time;
extern volatile u16 LED_Time;
extern volatile u16 BuzzerTime;
extern volatile u16 UPC_Time;
extern volatile u16 UPC_Time2;
extern u8 Time_To_Store;
//------------------------------------------------------------------------------
void Delay(u16 val);// value in ms
void Delay_mks(u16 val);// value in mks
void Timer_1ms_IRQ();
//------------------------------------------------------------------------------
#endif
