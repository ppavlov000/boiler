//------------------------------------------------------------------------------
#ifndef __ADC
#define __ADC
//------------------------------------------------------------------------------
#include "..\System\defines.h"
//#include "io.h"
//------------------------------------------------------------------------------
eu8 	ad_res_l,ad_res_h;
eu16	ad_buff[ADC_MAX_NUM];
es16	ad_res;
eu8		channel;
eu32	ad_tmp32;
es16 point_reference_temperature[2];
es16 point_real_temperature[2][NUM_AIN];
es16	input_voltage;
eu16	ad_res_int;
//------------------------------------------------------------------------------
void adc_init();
void adc_handle();
void adc_set_channel(u8 ch);
s16 adc_conversion();
//------------------------------------------------------------------------------
#endif
