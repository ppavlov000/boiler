#ifndef __FRAM
#define __FRAM
//-----------------------------------------------------------------------------------
//#include "..\Misc\types.h"
#include "..\define.h"
#include "..\controller_data_define.h"
//-----------------------------------------------------------------------------------
#define MAX_WATCHDOG_TIME	1000
//-----------------------------------------------------------------------------------
#define fram_reg_Serial7 						0x18
#define fram_reg_Serial6 						0x17
#define fram_reg_Serial5  						0x16
#define fram_reg_Serial4  						0x15
#define fram_reg_Serial3  						0x14
#define fram_reg_Serial2  						0x13
#define fram_reg_Serial1  						0x12
#define fram_reg_Serial0  						0x11
#define fram_reg_Counter_2_MSB 					0x10
#define fram_reg_Counter_2_LSB 					0x0f
#define fram_reg_Counter_1_MSB 					0x0e
#define fram_reg_Counter_1_LSB 					0x0d

#define fram_reg_Event_Count_Control 			0x0C
// bits
#define	fram_RC 			0x08
#define	fram_CC 			0x04
#define	fram_C2P 		0x02
#define	fram_C1P 		0x01

#define fram_reg_Companion_Control	 			0x0B
// bits
#define	fram_SNL 		0x80
#define	fram_WP1 		0x10
#define	fram_WP0 		0x08
#define	fram_VBC 		0x04
#define	fram_VTP1	 	0x02
#define	fram_VTP0	 	0x01

#define fram_reg_Watchdog_Control	 			0x0A
// bits
#define	fram_WDE 		0x80
#define	fram_WDT4 		0x10
#define	fram_WDT3 		0x08
#define	fram_WDT2 		0x04
#define	fram_WDT1	 	0x02
#define	fram_WDT0	 	0x01

#define fram_reg_Watchdog_Restart_Flags	 		0x09
// bits
#define	fram_WTR 		0x80
#define	fram_POR 		0x40
#define	fram_LB	 		0x20
#define	fram_WR3 		0x08
#define	fram_WR2 		0x04
#define	fram_WR1	 	0x02
#define	fram_WR0		0x01

#define fram_reg_Year					 		0x08
#define fram_reg_Month					 		0x07
#define fram_reg_Date					 		0x06
#define fram_reg_Day					 		0x05
#define fram_reg_Hour					 		0x04
#define fram_reg_Minute					 		0x03
#define fram_reg_Second					 		0x02

#define fram_reg_CAL_Control						0x01
// bits
#define	fram_OSCEN 		0x80
#define	fram_CALS	 	0x20
#define	fram_CAL4 		0x10
#define	fram_CAL3 		0x08
#define	fram_CAL2 		0x04
#define	fram_CAL1	 	0x02
#define	fram_CAL0		0x01

#define fram_reg_RTC_Control					 	0x00
// bits
#define	fram_CF	 		0x40
#define	fram_CAL 		0x04
#define	fram_W		 	0x02
#define	fram_R			0x01
//-----------------------------------------------------------------------------------
#define FRAM_STATUS		0x00
#define bit_fram_conf_done	0x01
//-----------------------------------------------------------------------------------
extern TCTime ft;
//extern TTime	error_time;
eu32 Fram_Addr;
//-----------------------------------------------------------------------------------
//u32 CheckCRC(u8 who);
void fram_init();
void fram_mem_write(u16 addr,u8* data, u16 len);
void fram_mem_read(u16 addr,u8* data, u16 len);
void fram_comp_write(u8 addr,u8* data, u16 len);
void fram_comp_read(u8 addr,u8* data, u16 len);
void fram_set_time(u8 hour,u8 minute,u8 second);
void fram_set_date(u8 year,u8 month, u8 date,u8 day);
u32 CheckCRC(u8 who,u16 PARAM_LOCATION);
void fram_get_time();
void fram_watchdog_reset();
void fram_mem_enable();
void fram_mem_disable();
//-----------------------------------------------------------------------------------
#endif
