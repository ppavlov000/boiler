#ifndef __SYS_DEFINE
#define __SYS_DEFINE
//------------------------------------------------------------------------------
//#define NUM_DIN			32
//#define NUM_DOUT		32
//#define NUM_AIN			4
//#define NUM_AIN_REAL	3
//#define NUM_AOUT		1
//-----------------------------------------------------------------------------------
#define MAX_CURTAINS_PAIRS	 	4
//#define MAX_FANCOIL_NUMBER		2
#define MAX_SIMPLE_BUTTONS 		20
#define MAX_CURTAINS_BUTTONS 	4
#define MAX_CHANNELS_NUM		5
//-----------------------------------------------------------------------------------
#define CURTAINS_OFF_TIME 	1000	//ms
//-----------------------------------------------------------------------------------
#define CONSOLE_BAUND		38400//lc 115200//5;//35;//71;//9600//35;//19200//5;//115200
#define UPC_BAUND			38400//lc 57600//5;//35;//71;//9600//35;//19200//5;//115200
#define SYS_SET_UP_PERIOD	5000
//#define MAX_PANELS_NUMBER	5

//------------------------------------------------------------------------------
#define ALARM_ON_DELAY	60
//-----------------------------------------------------------------------------------
#define mask_reserve			(0)

#define mask_curtains_0_do		(Curtain_00_open+Curtain_00_close)	
#define mask_curtains_1_do		(Curtain_01_open+Curtain_01_close)	
#define mask_curtains_2_do		(Curtain_02_open+Curtain_02_close)
#define mask_curtains_3_do		(Curtain_03_open+Curtain_03_close)


#define fan_0_low				(0)		
#define fan_0_med				(0)
#define fan_0_high				(0)
#define fan_0_heating			(0)
#define fan_0_cooling			(0)

#define fan_1_low				(0)		
#define fan_1_med				(0)
#define fan_1_high				(0)
#define fan_1_heating			(0)
#define fan_1_cooling			(0)


#define Button_Alarm			(0x80000000)
#define Button_Thief_detected	(0x40000000)
#define MAIN_SWITCH				(0x20000000)
#define LIGHT_ALARM_OUT			DO_XX
#define SOUND_ALARM_OUT			DO_19
#define LED_ALARM_OUT			DO_XX
#define TEST_ALARM_OUT			DO_XX
#define ALARM_OUTPUTS			(LIGHT_ALARM_OUT | SOUND_ALARM_OUT | LED_ALARM_OUT | TEST_ALARM_OUT )

#define DI_SMOKE_DETECTOR		0x01
#define DI_MOTION_DETECTOR		0x02
#define DI_SIREN_DETECTOR		0x04

#define mask_fan_0				(fan_0_low+fan_0_med+fan_0_high+fan_0_heating+fan_0_cooling)		
#define mask_fan_1				(fan_1_low+fan_1_med+fan_1_high+fan_1_heating+fan_1_cooling)		
//-----------------------------------------------------------------------------------
#define mask_fancoil_do			(mask_fan_0+mask_fan_1)		
#define mask_service_do			(0)//(DO_20+DO_21)	
#define mask_curtain_buttons	(mask_curtains_0_do+mask_curtains_1_do+mask_curtains_2_do+mask_curtains_3_do)
#define mask_simple_buttons		(0x00ffffff & ~(mask_fancoil_do + mask_curtain_buttons + mask_reserve+mask_service_do+ALARM_OUTPUTS))
//#define mask_simple_buttons		(0x00ffffff & ~(mask_fancoil_do + mask_curtain_buttons + mask_reserve))
//-----------------------------------------------------------------------------------
#define Button_00				(DO_00)
#define Button_01				(DO_01)
#define Button_02				(DO_02)
#define Button_03				(DO_03)
#define Button_04				(DO_04)
#define Button_05				(DO_05)
#define Button_06				(DO_06)
#define Button_07				(DO_07)
#define Button_08				(DO_17)
#define Button_09				(DO_18)
#define Button_10				(DO_XX)
#define Button_11				(DO_XX)
#define Button_12				(DO_XX)
#define Button_13				(DO_XX)
#define Button_14				(DO_XX)
#define Button_15				(DO_XX)
#define Button_16				(DO_XX)
#define Button_17				(DO_XX)
#define Button_18				(DO_XX)
#define Button_19				(DO_XX)
#define Button_20				(DO_20) // Service function
#define Button_21				(DO_21) // Service function

#define Pict_00					(99)
#define Pict_01					(83)
#define Pict_02					(84)
#define Pict_03					(85)
#define Pict_04					(77)
#define Pict_05					(78)
#define Pict_06					(79)
#define Pict_07					(80)
#define Pict_08					(81)
#define Pict_09					(82)
#define Pict_10					(83)
//-----------------------------------------------------------------------------------
#define Curtain_00_open			(DO_09)
#define Curtain_00_close		(DO_10)
#define Curtain_01_open			(DO_11)
#define Curtain_01_close		(DO_12)
#define Curtain_02_open			(DO_13)
#define Curtain_02_close		(DO_14)
#define Curtain_03_open			(DO_15)
#define Curtain_03_close		(DO_16)

#define Pict_Curtain_00_Open	(80)
#define Pict_Curtain_00_Close	(81)
#define Pict_Curtain_01_Open	(80)
#define Pict_Curtain_01_Close	(81)
#define Pict_Curtain_02_Open	(80)
#define Pict_Curtain_02_Close	(81)
#define Pict_Curtain_03_Open	(80)
#define Pict_Curtain_03_Close	(81)
//-----------------------------------------------------------------------------------
#define Main_0_on				(DO_00+DO_01+DO_02)	
#define Main_0_off				(DO_00+DO_01+DO_02+DO_03+DO_04+DO_05+DO_06+DO_07+DO_08+DO_17+DO_18)	

#define Main_1_on				(DO_03+DO_04)	
#define Main_1_off				(DO_03+DO_04)	
//-----------------------------------------------------------------------------------
#define Special_Button_00		(DO_XX)
#define Button_21_Off			(DO_XX)
//-----------------------------------------------------------------------------------
#define DO_XX   0x00000000
#define DO_00	0x00000001
#define DO_01	0x00000002
#define DO_02	0x00000004
#define DO_03	0x00000008
#define DO_04	0x00000010
#define DO_05	0x00000020
#define DO_06	0x00000040
#define DO_07	0x00000080
#define DO_08	0x00000100
#define DO_09	0x00000200
#define DO_10	0x00000400
#define DO_11	0x00000800
#define DO_12	0x00001000
#define DO_13	0x00002000
#define DO_14	0x00004000
#define DO_15	0x00008000
#define DO_16	0x00010000
#define DO_17	0x00020000
#define DO_18	0x00040000
#define DO_19	0x00080000
#define DO_20	0x00100000
#define DO_21	0x00200000
#define DO_22	0x00400000
#define DO_23	0x00800000
#define DO_24	0x01000000
//-----------------------------------------------------------------------------------
#define DIM_01	0x00200000
#define DIM_02	0x00400000
#define DIM_03	0x00800000
#define DIM_04	0x01000000
#define DIM_05	0x02000000
#define DIM_06	0x04000000
#define DIM_07	0x08000000
#define DIM_08	0x00000000
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
#define di	io.din
#define _do	io.dout
#define ai	io.ainput
#define ao	io.aoutput
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
// Kotel V01
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
// Analog inputs define
#define 	t_in	 		ai[0]
#define 	t_out	 		ai[1]
#define 	t_fuel			ai[2]
#define 	t_smoke 		ai[3]
//#define 	t_ext 			ai[4]
// Digital inputs define
#define 	di_PL 			di & (1<<0)
#define 	di_PH	 		di & (1<<1)
#define 	di_T110 		di & (1<<2)
#define 	di_TOP_O	 	di & (1<<3)
#define 	di_TS_GOR	 	di & (1<<4)
#define 	di_ALO			di & (1<<5)
#define 	di_Start		di & (1<<6)
#define 	di_Stop	 		di & (1<<7)
// Digital output define
#define 	do_FIRE	 		_do & (1<<0)
#define 	do_GOR			_do & (1<<1)
#define 	do_YL	 		_do & (1<<2)
#define 	do_YR	 		_do & (1<<3)
#define 	do_FORW	 		_do & (1<<4)
#define 	do_REV	 		_do & (1<<5)
#define 	do_Alarm	 	_do & (1<<6)
#define 	do_FC		 	_do & (1<<7)
// Analog output define
#define 	ao_air1 		ao[1]
#define 	ao_air2 		ao[2]
#define 	ao_smoke 		ao[0]

// Controller 1
// Digital inputs define
#define 	di_BUN_O 		params[1] & (1<<0)
#define 	di_Fuel_L 		params[1] & (1<<1)
#define 	di_TK1	 		params[1] & (1<<2)
#define 	di_TK2	 		params[1] & (1<<3)
#define 	di_TK3	 		params[1] & (1<<4)
#define 	di_TK4 			params[1] & (1<<5)
// Digital output define
#define 	do_ASH	 		params[2] & (1<<0)
#define 	do_Alarm1	 	params[2] & (1<<1)
#define 	do_FUEL1	 	params[2] & (1<<2)
#define 	do_PumpK	 	params[2] & (1<<3)
#define 	do_t110	 		params[2] & (1<<4)
#define 	do_work	 		params[2] & (1<<5)

// Define Errors
#define 	err_low_preasure		0x0100
#define 	err_high_preasure		0x0200
#define 	err_high_kot_t			0x0300
#define 	err_bad_smoke			0x0400
#define 	err_bad_shnek_1			0x0501
#define 	err_bad_shnek_2			0x0502
#define 	err_bad_fan_1			0x0601
#define 	err_bad_fan_2			0x0602
#define 	err_topka_open			0x0700
#define 	err_screw_motor			0x0800
#define 	err_fan_motor			0x0900
// Kotel modes
#define 	kot_off 			0
#define 	kot_1				1
#define 	kot_2 				2
#define 	kot_3 				3
#define 	kot_4 				4
#define 	kot_stop 			5
//-----------------------------------------------------------------------------------
#define 	shnek			4
#define		sh_0_for		0x0001
#define		sh_0_back		0x0002
#define		sh_1_for		0x0003
//-----------------------------------------------------------------------------------
#endif
