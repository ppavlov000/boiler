//-----------------------------------------------------------------------------------
#ifndef __IO
#define __IO
//-----------------------------------------------------------------------------------
#include "types.h"

#define io_data_port	PORTA
#define io_data_pins	PINA
#define io_data_dir	DDRA

#define ioc_data_port	PORTG
#define ioc_data_pins	PING
#define ioc_data_dir	DDRG
// Pins
#define	b_rd	0x02
#define	b_wr	0x01
#define	b_ale	0x04
//Macros
#define rd_on	ioc_data_port|=b_rd
#define rd_off	ioc_data_port&=~b_rd
#define wr_on	ioc_data_port|=b_wr
#define wr_off	ioc_data_port&=~b_wr
#define ale_on	ioc_data_port|=b_ale
#define ale_off	ioc_data_port&=~b_ale
//-------------------------------------------------------------------------------------------
#define NUM_DIN		8
#define NUM_DOUT	20
#define NUM_AIN		2
#define NUM_AOUT	4
//#define NUM_POUT	5
//-----------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------
typedef struct
{
	u8 num_di;
	u8 num_do;
	u8 num_ai;
	u8 num_ao;
				
	u32	din;
	u32 dout;
	u16 aoutput[NUM_AOUT];	
	s16 ainput[NUM_AIN];
	s16 dt;
	u8 Fan_Mode;
	u8 Fan_Lvl;
	f32 ao_coff[NUM_AOUT];	
	f32 ai_coff[NUM_AIN];	
	s16 ai_offset[NUM_AIN];		
	s16 tmp;
}TIO;
//TIO_Static;
//-----------------------------------------------------------------------------------
typedef struct
{
	u32	din;
	u32 dout;
	u16 aoutput[NUM_AOUT];	
	s16 ainput[NUM_AIN];
}TIO_Dinamic;
//-----------------------------------------------------------------------------------
extern TIO io;
//-----------------------------------------------------------------------------------
void io_init();
void io_relay_set();
void io_io_set();
void io_analog_set();
void io_handle();
void io_write(u8 data,u8 addr);
u8 io_read(u8 addr);
//-----------------------------------------------------------------------------------
#endif
