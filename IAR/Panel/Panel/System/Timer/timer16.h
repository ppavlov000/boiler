#ifndef __TIMER16
#define __TIMER16
//-----------------------------------------------------------------------------------
#include "..\..\System\Standard\types.h"
//-----------------------------------------------------------------------------------
extern volatile u16 Time0;
extern volatile u16 Time1;
extern volatile u16 Time2;
extern volatile u16 Time4;
extern volatile u16 Snooze_Time;
extern volatile u16 LED_Time;
extern volatile u16 BMP_Time;
extern volatile u16 TSC_Time;
extern volatile u16 FT_Time;
extern volatile u16 BL_Time;
extern volatile u16 SI_Time;
extern volatile u16 R0_Time;
extern volatile u16 R1_Time;
extern volatile u16 UPC_Time;
extern volatile u16 UPC_Time2;
extern volatile u16 SLEEP_Time;
extern volatile u16 Button_no_update_time;
extern volatile u16 Dimmer_Time;
extern volatile u16 Dimmer_Time2;
extern u8 Switch_To_Main_Time;
eu8 Sign_To_Save;
eu16 Time_To_Save;
//evu8 Pass_Time;
//evu8 Pass_Time_Expired;
evu16 BUZZ_Time;
//-----------------------------------------------------------------------------------
void Delay(u16 val);// value in ms
void Timer_1ms_IRQ();
//-----------------------------------------------------------------------------------
#endif
