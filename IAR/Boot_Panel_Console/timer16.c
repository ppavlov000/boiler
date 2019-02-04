#include "timer16.h"
#include "inavr.h"
//-----------------------------------------------------------------------------------
u16 time,del_time;
volatile u16 Time0=0;
volatile u16 Time1=0;
volatile u16 Time2=0;
volatile u16 Time3=0;
volatile u16 Time4=0;
volatile u16 Time5=0;
//-----------------------------------------------------------------------------------
#pragma vector=TIMER1_COMPA_vect
__interrupt void Timer_IRQ()
{
	if(Time0!=0)Time0--;
	if(Time1!=0)Time1--;
	if(Time2!=0)Time2--;
	if(Time3!=0)Time3--;		
	if(Time4!=0)Time4--;		
	if(Time5!=0)Time5--;		
}
//-----------------------------------------------------------------------------------
void Timer_Init()
{
 	TCCR1A=0;
	TCCR1B=0x09;  
	TCCR1C=0;//(1<<FOC1A);
	OCR1A=7372;  // pulses per 1ms
	TIMSK=(1<<OCIE1A);
	TCNT1=0;
	time=0;
	Time0=0;
	Time1=0;  
	Time2=0;
 	Time3=0;    
}
//-----------------------------------------------------------------------------------
void Delay(u16 val)// value in ms
{
	Time3=val;
	while(Time3!=0)  
	{
	}
}
//-----------------------------------------------------------------------------------
