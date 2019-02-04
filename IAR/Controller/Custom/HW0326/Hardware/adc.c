//------------------------------------------------------------------------------
#include "..\main.h"
//------------------------------------------------------------------------------
u8 	ad_res_l,ad_res_h;
s16	ad_res;
u16	ad_res_int=0;
s16 point_reference_temperature[2];
s16 point_real_temperature[2][NUM_AIN];
s32 filter[NUM_AIN];
s16	input_voltage=0;
u8 channel=0;
u8 tmp;
u16	ad_tmp;
u32	ad_tmp32;
f32	ftmp;
//u8	tmp8[3];
s16 ai_tst[4];
//------------------------------------------------------------------------------
s16 adc_conversion();
void adc_set_channel(u8 ch);
void adc_hardware_init();
//------------------------------------------------------------------------------
void adc_init()
{
//	u8 i,j;
	adc_hardware_init();
	channel=0;	
	adc_set_channel(channel);	
	memset(&filter[0],0,sizeof(filter));
}
//------------------------------------------------------------------------------
void adc_handle()
{
	f32 ftmp;
	ftmp=adc_conversion();
//	ai_tst[channel]=ftmp;
	ftmp=ftmp*io.ai_coff[channel];
	ftmp=ftmp+io.ai_offset[channel];
	filter[channel]=filter[channel]*7;
	filter[channel]+=ftmp;
	filter[channel]=filter[channel]/8;
	ftmp=filter[channel];
	io.ainput[channel]=ftmp;
	channel++;
	if(channel>=NUM_AIN)
	{
		channel=0;
		pid_handle();
	}	
	adc_set_channel(channel);
}
//------------------------------------------------------------------------------
