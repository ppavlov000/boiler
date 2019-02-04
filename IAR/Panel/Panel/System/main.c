 //-----------------------------------------------------------------------------------
// Sourse of 8psk mcontroller host
//-----------------------------------------------------------------------------------
#include "main.h"
//-----------------------------------------------------------------------------------
void update_page();	
//-----------------------------------------------------------------------------------
TMain m;
TController CV;
TWorkInfo WorkInfo;
s16 T_Sensor=0;
//-----------------------------------------------------------------------------------
u8 envitation[20];
u8 custom_information_init=0;
u8 custom_information_update=0;
u32 HW=0;
extern  u16 Store_Time;
extern  u8 Store_Sign;
//-----------------------------------------------------------------------------------
__farflash u8	Main_Dict[][40]=
{
	"\n\r Loading default parameters...",	//0
	"\n\r Loading stored parameters...",	//1
	"\n\r"
	"\n\r EL LCD Panel Ver.04"
	"\n\r",									//2
	"\n\r Board number ",			 		//3	
	"Booting panel....",					//4
	"Interface will start in 3 sec",		//5
	"To calibrate touch for 1 sec",			//6
	"Calibration routine ",					//7
	"1 Press left upper point",				//8
	"1 Press right lower point",			//9
	"Release screen",						//10	
};
//-----------------------------------------------------------------------------------
u16 CRC;
u16 Set_Tets_Delay=0;
u8 Test_Mode=0;	// if 1 then software in test mode
extern u8 update_packet;
//-----------------------------------------------------------------------------------
void get_address()
{
//	u8 i;
	u8 tmp=1;
//	u8 count;
	m.Address=get_switch_state();
	if(tmp==0)
	{
		// Beep on
		beep_on();
	}
	else
	{
		// Beep off
		beep_off();
	}	
	envitation[0]='p';
	envitation[1]='a';
	envitation[2]='n';
	envitation[3]='e';
	envitation[4]='l';	
	envitation[5]='_';
	envitation[6]='0';
	envitation[7]='0'+m.Address;
	envitation[8]='>';
	envitation[9]=0;
}
//-----------------------------------------------------------------------------------
void params_load()
{
	u8 i;
	FGet((u8*)&HW,HAPP_FLASH_START+THW_LOC,4);
	if (!params_get()) {
//		_sprintf_P((u8*)outtxt,Main_Dict[0]);
//	 	Error_Code=Err_BAD_EEPROM_RECORD;
		// Defaults
		m.coff.x=0.0688;
		m.coff.y=0.0378;
		m.coff.ox[0]=210;
		m.coff.ox[1]=3490;
		m.coff.oy[0]=320;
		m.coff.oy[1]=3390;
		
		m.BackLit_Value_Max=9;	
		m.BackLit_Value_Min=2;		
		m.Sleep_Time=10;
		
		m.Alarm.field.Second=0;
		m.Alarm.field.Minute=0;		
		m.Alarm.field.Hour=0;		
		m.Alarm_Status=0;

		for(i=0;i<7;i++){
			m.sch[i][0].Hour=7;
			m.sch[i][1].Hour=23;
			m.sch[i][0].Minute=0;
			m.sch[i][1].Minute=0;
			m.sch_enable[i]=1;
		}		
		m.sch_enable[5]=0;
		m.sch_enable[6]=0;
		m.sch_param_ena[0]=0; 			
		m.sch_param_ena[1]=1; 			
		m.sch_param_ena[2]=1; 			
		
		m.sch_auto_manual=0; // Auto
		m.sch_day_night=0; // Day
		m.sch_temperature[0]=220;
		m.sch_temperature[1]=160;

		m.sch_fan_speed[0]=800;
		m.sch_fan_speed[1]=400;

		m.sch_mode[0]=1;
		m.sch_mode[1]=0;

		m.adjust_temperature[0]=0;
		m.adjust_temperature[1]=0;
		m.gradient_temperature=40;
		m.pritochka_speed=500;
		m.TMP441_Channel=0;			// 0-Internal 1-external channels
		m.image_position=0;
		params_store();
	}
	else
	{
		if(m.TMP441_Channel>1)m.TMP441_Channel=0;
		m.image_position=0;
//		FiveMins.field.Minute=m.Alarm.field.Minute;
//		FiveMins.field.Hour=m.Alarm.field.Hour;
	}
}

//-----------------------------------------------------------------------------------
uchar params_get() // lc
{
	EEGet((u8*)&m,PARAM_LOCATION,TPARAM_WIDTH-2);
	EEGet((u8*)&CRC,PARAM_LOCATION+TPARAM_WIDTH-2,2);	
	return (CRC == CheckCRC(5))?1:0;
}
//-----------------------------------------------------------------------------------
void params_store() // lc
{
	EEPut((u8*)&m,PARAM_LOCATION,TPARAM_WIDTH-2);
	CRC=CheckCRC(5);	
	EEPut((u8*)&CRC,PARAM_LOCATION+TPARAM_WIDTH-2,2);	
}
//-----------------------------------------------------------------------------------
void init()
{
	hardware_init();
	// Init ADM706 Watchdog
	watchdog_init();
	watchdog_reset();
	//Custom functions initialisation
	Timer_Init();
	TSC_Init();
	params_load();	
	init_bmp();
	io_init();
	rx_mode();
	//upc_init();	
	Slave_Init();
	M_init();
	beep_init();
	
#if	TMP441_ENABLE	
	I2C_Init();	
	TMP441_init();
#endif		
	
	enable_interrupt();
	Delay(10);	
	get_address();
}
//-----------------------------------------------------------------------------------
//void dimmer_handle_custom();
extern TLCDPictTop Scr_0;
extern TLCDPictTop Scr_44;
//extern TLCDPictTop Scr_12;
//extern TLCDPictTop Scr_Password;
//extern TLCDPictTop *Scr_Return;
//extern TLCDPictTop *Scr_Enter;
//-----------------------------------------------------------------------------------
void custom_handle();
extern u8 Current_ID;
extern u8 device_found;
extern u8 device_id[MAX_DEVICES_NUM];
extern u8 Common_ID_Mode;
void scr44_Scan();
extern u8 Switch_To_ID_1;
extern u8 Start_Up_Time;

//-----------------------------------------------------------------------------------
void main()
{
#if TMP441_ENABLE		
	u8 i=0;
	s8 stmp;
	u8 utmp;
	s16 temp;
	f32 ftmp;
#endif	
	
	init();
	startup();
	Start_Up_Time=15;
	
	LCDTopPtr=&Scr_44;	
	LCDTopPtr->Init();
	repaint_page();	
	scr44_Scan();
	Switch_To_Main_Time=5;
	while(1)
	{
		watchdog_reset();
//		dimmer_handle_custom();
//		M_handler();
		M_Schedule();
		handle_page();			
//		update_page();	
#if __MODBUS_ENA==1		
		modbus_s_PacketHandler();		
#endif		
		if(LED_Time==0)
		{
			Ext_IRQ0();			
			LED_Time=100;				
			toggle_led();			
		}
		if(Time1==0)
		{
			Time1=500;
			int_state|=but_Int3s;			
			time_blink++;	
			get_address();		
#if TMP441_ENABLE		
			i++;
			if(i & 0x02)
			{
				// TMP441 get temperature
//				TMP441_read(TMP441_reg_Local_T_H,(u8*)&utmp,1);
//				temp=stmp;				
//				ByteToStr(lcd_txt,&utmp,1);
//				lcd_sprintf(lcd_txt,0,3);


				if(m.TMP441_Channel==0)
					TMP441_read(TMP441_reg_Remote0_T_H,(u8*)&stmp,1);
				else
					TMP441_read(TMP441_reg_Local_T_H,(u8*)&stmp,1);

				temp=stmp;
				temp*=10;
				if(m.TMP441_Channel==0)
					TMP441_read(TMP441_reg_Remote0_T_L,&utmp,1);			
				else
					TMP441_read(TMP441_reg_Local_T_L,&utmp,1);								
				utmp>>=4;
				ftmp=utmp*0.0625*10;
				if(temp<0) 	temp-=ftmp;
				else		temp+=ftmp;
				T_Sensor=temp;				
			}
#endif			

		}
		if((Store_Time==0)&&(Store_Sign!=0))
		{
			params_store();
			Store_Sign=0;
		}
		if((Switch_To_Main_Time==0)&&(LCDTopPtr!=&Scr_0))
		{
			if(LCDTopPtr==&Scr_44)
				if(device_found!=0)
				{
					Current_ID=device_id[0];
					Common_ID_Mode=0;
				}
			LCDTopPtr->Exit();
			LCDTopPtr=&Scr_0;	
			LCDTopPtr->Init();
			repaint_page();							
		}
	}	
}
//-----------------------------------------------------------------------------------

