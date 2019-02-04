#include "..\main.h"
//-----------------------------------------------------------------------------------
#define PID_TIME_MAX 600

//u16 time,del_time;
volatile u16 Time0=0;
volatile u16 Time1=0;
volatile u16 Time5=0;
volatile u16 PID_Time=PID_TIME_MAX;
volatile u16 PID_Test_Time=0;
volatile u16 FramTime=0;
volatile u16 BuzzerTime=0;
volatile u16 DelayTime=0;
volatile u16 SysSetUp=0;
volatile u16 Adc_Time=0;
volatile u16 Time6=0;
volatile u16 LCD_Time=0;
volatile u16 LED_Time=0;
volatile u16 Sec_Time=0;
volatile u16 UPC_Time=0;
volatile u16 UPC_Time2=0;

extern u8 Season_Timeout;
extern u16 	Mode_1_timeout;

#if MAX_KOTEL_NUMBER	
eu16	Stop_Timeout;
eu8   	sh_on[2];
eu8   	sh_off[2];
eu8   	fan_on[2];
eu8   	fan_off[2];
eu16 	Kotel_P3_Time;
#endif
#if MAX_FANCOIL_NUMBER	
extern u8 Fan_Switch_Enable[MAX_FANCOIL_NUMBER];
extern u8 Valve_Switch_Enable[MAX_FANCOIL_NUMBER];
extern u8 Valve_Transfer_Enable[MAX_FANCOIL_NUMBER];
#endif

u8 Time_To_Store=0;
//vf32	iftmp;
//vs8	ictmp;
//-----------------------------------------------------------------------------------
void Timer_1ms_IRQ()
{
	u8 i;
//	__enable_interrupt();
	if(Time0!=0)Time0--;

	if(intr.t32[0]!=0)intr.t32[0]--;		
	if(intr.t32[1]!=0)intr.t32[1]--;		
	if(intr.t32[2]!=0)intr.t32[2]--;		
	if(intr.t32[3]!=0)intr.t32[3]--;					
	
	if(Time1!=0)
	{
		Time1--;	
		if(PID_Test_Time!=0)PID_Test_Time--;			
		if(PID_Time!=0)PID_Time--;	
		else
		{
			PID_Time=PID_TIME_MAX;
			PID_Test_Time=240;
		}
	}
	else
	{
		Time1=1000;	
		if(intr.t32[4]!=0)intr.t32[4]--;		
		if(intr.t32[5]!=0)intr.t32[5]--;		
		if(intr.t32[6]!=0)intr.t32[6]--;		
		if(intr.t32[7]!=0)intr.t32[7]--;	
		if(Time_To_Store!=0){Time_To_Store--;To_Store=1;}
		if(Season_Timeout!=0)Season_Timeout--;	
#if MAX_KOTEL_NUMBER
		if(Stop_Timeout!=0)Stop_Timeout--;
		if(Mode_1_timeout!=0)Mode_1_timeout--;		
		for(i=0;i<2;i++)
		{
			if(sh_on[i]!=0)sh_on[i]--;
			if(sh_off[i]!=0)sh_off[i]--;
			if(fan_on[i]!=0)fan_on[i]--;
			if(fan_off[i]!=0)fan_off[i]--;
		}			
#endif		
#if MAX_FANCOIL_NUMBER			
		for(i=0;i<MAX_FANCOIL_NUMBER;i++)
		{
			if(Fan_Switch_Enable[i]!=0)Fan_Switch_Enable[i]--;
			if(Valve_Switch_Enable[i]!=0)Valve_Switch_Enable[i]--;
			if(Valve_Transfer_Enable[i]!=0)Valve_Transfer_Enable[i]--;
		}		
#endif		
	}
	if(Time5!=0)Time5--;
	if(Time6!=0)Time6--;	
	if(FramTime!=0)FramTime--;
	if(DelayTime!=0)DelayTime--;	
	if(SysSetUp!=0)SysSetUp--;		
	if(Adc_Time!=0)Adc_Time--;			
	if(LCD_Time!=0)LCD_Time--;		
	if(LED_Time!=0)
	{
		LED_Time--;		
		led_on();
	}
	else
		led_off();
	if(UPC_Time!=0)UPC_Time--;
	if(UPC_Time2!=0)UPC_Time2--;
		
	if(Key0_Time!=0)Key0_Time--;			
	if(Key1_Time!=0)Key1_Time--;			
	if(Key2_Time!=0)Key2_Time--;			
	if(Key3_Time!=0)Key3_Time--;	
	if(Key_Repeat_Time!=0)Key_Repeat_Time--;		

	keys_handler();
	
	if(BuzzerTime!=0)
	{
		BuzzerTime--;		
		beep_on();		
	}
	else
		 beep_off();	

#if NUM_PID
	if(MenuRegs.Manual_Mode!=MANUAL_MODE)
		for(i=0;i<NUM_PID;i++)			
		{
			if(PID_P3_Time[i]!=0)
				PID_P3_Time[i]--;
			else
			{
				PID_P3_Time[i]=pid[i].t3max;
				if(pid[i].open!=0)
				{
					if(pid[i].p3<999)
						pid[i].p3+=1;
				}
				if(pid[i].close!=0)
				{
					if(pid[i].p3>0)
						pid[i].p3-=1;
				}
			}		
		}
#endif
#if MAX_KOTEL_NUMBER
	if(MenuRegs.Manual_Mode!=MANUAL_MODE)
	{
			if(Kotel_P3_Time!=0)
				Kotel_P3_Time--;
			else
			{
				Kotel_P3_Time=kotel.t3max;
				if(kotel.open!=0)
				{
					if(kotel.p3<999)
						kotel.p3+=1;
				}
				if(kotel.close!=0)
				{
					if(kotel.p3>0)
						kotel.p3-=1;
				}
			}		
	}
#endif
	upc_TXHandler();
}
//-----------------------------------------------------------------------------------
/*#pragma vector=TIMER3_COMPA_vect
__interrupt void Timer3_IRQ()
{
	adc_handle();
}*/
//-----------------------------------------------------------------------------------
void Delay(u16 val)// value in ms
{
	DelayTime=val;
	while(DelayTime!=0)	
	{
	}
}
//-----------------------------------------------------------------------------------
void Delay_mks(u16 val)// value in mks
{
	u8 i,j;
	for(i=0;i<val;i++)
		for(j=0;j<60;j++)
			no_operation();
}
//-----------------------------------------------------------------------------------
