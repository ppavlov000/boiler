#include "..\main.h"
//#include "..\..\Custom\Standard\TP_0\Menu_new\dimmer.h"
//-----------------------------------------------------------------------------------
//extern TLCDPictTop Scr_2;
//-----------------------------------------------------------------------------------
u16 time,del_time;
volatile u16 Time0=0;
volatile u16 Time1=0;
volatile u16 Time2=0;
volatile u16 Time3=0;
volatile u16 Time4=0;
volatile u16 Snooze_Time=0;

volatile u16 FT_Time=0;
volatile u16 BUZZ_Time=0;
volatile u16 LED_Time=0;
volatile u16 BMP_Time=0;
volatile u16 TSC_Time=0;
volatile u16 BL_Time=20000;
volatile u16 SI_Time=0;
volatile u16 R0_Time=0;
volatile u16 R1_Time=0;
volatile u16 UPC_Time=0;
u16 M_Time=0;
volatile u16 UPC_Time2=0;
volatile u16 Button_no_update_time=0;
volatile u16 SLEEP_Time=0;
volatile u16 Dimmer_Time=0;
volatile u16 Dimmer_Time2=0;

u8 Sign_To_Save=0;
u16 Time_To_Save=0;

u16 Store_Time=0;
u8 Switch_To_Main_Time=0;
u8 Switch_To_ID_1=0;
u8 Start_Up_Time=0;
u8 Store_Sign=1;
u8 M_SCH_Time=0;
u16 Dimmer_Time3;
vu8 Pass_Time=0;
//eu8 Pass_Time_Expired;
//eu8  Password_OK;
vf32	iftmp;
vs8	ictmp;
u8 bl_counter=0;
//extern u8 	Password_Time;
vs8 thief_alarm_timeout = -1;
//eu8 Moon_Curtains;
u8 Time_Pulses=10;
//-----------------------------------------------------------------------------------
void Timer_1ms_IRQ()
{
#if __MODBUS_ENA
	if(mod_rx_timout)mod_rx_timout--;	
#endif
	if(Time_Pulses)Time_Pulses--;
	else
	{
		Time_Pulses=10;
		if(M_SCH_Time!=0)M_SCH_Time--;
	
		if(Time0!=0)Time0--;
		if(Time1!=0)Time1--;
		if(Time2!=0)Time2--;
		if(Time3!=0)Time3--;	
		if(FT_Time!=0)FT_Time--;		
		if(LED_Time!=0)LED_Time--;	
		if(BMP_Time!=0)BMP_Time--;		
		if(TSC_Time!=0)TSC_Time--;			
		if(SI_Time!=0)SI_Time--;					
		if(R0_Time!=0)R0_Time--;	
		if(R1_Time!=0)R1_Time--;		
		if(Store_Time!=0){
			Store_Time--;	
			Store_Sign=1;
		}
		if(Time_To_Save!=0)
		{
			Time_To_Save--;	
			Sign_To_Save=1;
		}
		
		if(Dimmer_Time3!=0)Dimmer_Time3--;			
		if(UPC_Time!=0)UPC_Time--;			
		if(M_Time!=0)M_Time--;				
		if(UPC_Time2!=0)UPC_Time2--;	
		if(Button_no_update_time!=0)Button_no_update_time--;
	//	if(dimmer_sequence_timeout!=0) dimmer_sequence_timeout--;		
		if (Time4!=0)
			Time4--;
		else
		{
	//		if (thief_alarm_timeout > 0) thief_alarm_timeout--;
	//		if(Snooze_Time!=0)Snooze_Time--;		
	//		if(Password_Time!=0)Password_Time--;		
			if(SLEEP_Time!=0)SLEEP_Time--;
			if(Pass_Time!=0)Pass_Time--;	
			if(Start_Up_Time!=0)Start_Up_Time--;	
			if(Switch_To_Main_Time!=0)Switch_To_Main_Time--;
			if(Switch_To_ID_1!=0)Switch_To_ID_1--;
	//		if(Pass_Time_Expired!=0)Pass_Time_Expired--;	
	//		else Password_OK=0;
			Time4=1000;
		}		
		if(BUZZ_Time!=0)
		{
			beep_on();		
			BUZZ_Time--;	
		}
		else	
			beep_off();	
			
	//	if((alarm_state==0)&&(LCDTopPtr!=&Scr_2))
		{
			if((m.BackLit_Value_Max-m.BackLit_Value_Min)>2)
			{
				if(m.Sleep_Time!=0)
				{
					if(BL_Time!=0)BL_Time--;
						if(BL_Time==0)
						{
							bl_counter++;
							if (bl_counter >= 8) // lc (bl_counter == 8)
							{
								if(BackLit_Value>bl[m.BackLit_Value_Min])
								{
									if (BackLit_Value > bl_step)  // lc
										BackLit_Value -= bl_step; // lc
									else
										BackLit_Value = 0;        // lc
								}
								bl_counter=0;
							}
						}
				}
				else
				{
					BL_Time=10;
					BackLit_Value=bl[m.BackLit_Value_Max];
				}
			}
		}
		set_backlight_pwm(BackLit_Value);	
#if __MODBUS_ENA==0	
		upc_TXHandler();
#endif		
	}
}
//-----------------------------------------------------------------------------------
void Delay(u16 val)// value in ms
{
	Time3=val;
	while(Time3!=0)	
	{
		watchdog_reset();
	}
}
//-----------------------------------------------------------------------------------
