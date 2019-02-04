//-----------------------------------------------------------------------------------
#ifndef __IO
#define __IO
//-----------------------------------------------------------------------------------
//#define NUM_DIN		32
//#define NUM_DOUT	32
//#define NUM_AIN		3
//#define NUM_AOUT	1
//-----------------------------------------------------------------------------------
/*
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
	f32 ao_coff[NUM_AOUT];	
	f32 ai_coff[NUM_AIN];	
	s16 ai_offset[NUM_AIN];		
	s16 tmp;
}TIO;
//TIO_Static;
*/
//-----------------------------------------------------------------------------------
typedef struct
{
	u32	din;
	u32 dout;
	u16 aoutput[NUM_AOUT];	
	s16 ainput[NUM_AIN];
}TIO_Dinamic;
//-----------------------------------------------------------------------------------
//extern TIO io;
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
#endif