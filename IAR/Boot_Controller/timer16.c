#include "main.h"
//-----------------------------------------------------------------------------------
u16 time,del_time;
u16 Time0=0;
u16 Time1=0;
u16 Time2=0;
u16 Time3=0;
u16 Beep_Time=0;
u16 Time4=0;
u16 Time5=0;
u16 Time6=0;
u16 UPC_Time=0;
u16 UPC_Time2=0;
//-----------------------------------------------------------------------------------
void Timer_1ms_IRQ()
{
	if(Time0!=0)Time0--;
	if(Time1!=0)Time1--;
	if(Time2!=0)Time2--;
	if(Time3!=0)Time3--;
	if(Beep_Time!=0)
	{
		Beep_Time--;		
		beep_on();
	}
	else
	{
		beep_off();
	}
	if(Time4!=0)Time4--;		
	if(Time5!=0)Time5--;	
	if(Time6!=0)
	{
		Time6--;
		led_on();
	}
	else
		led_off();		
	
	if(UPC_Time!=0)UPC_Time--;	
	else
	{
		upc.rxcount=0;	
	}	
	if(UPC_Time2!=0)UPC_Time2--;		
	upc_TXHandler();		
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
