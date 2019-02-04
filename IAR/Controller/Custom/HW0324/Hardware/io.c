//------------------------------------------------------------------------------
#include "..\..\..\System\main.h"
#include "inavr.h"
#include <iom128.h>
//------------------------------------------------------------------------------
void io_init()
{
	memset(&io,0,sizeof(io));
	// Default
	io.num_di=NUM_DIN;
	io.num_do=NUM_DOUT;
	io.num_ai=NUM_AIN;
	io.num_ao=NUM_AOUT;	
					
	in_port&=~(p_din0+p_din1+p_din2+p_din3+p_din4+p_din5);
	in_port_dir&=~(p_din0+p_din1+p_din2+p_din3+p_din4+p_din5);
	
//	in_port_alt&=~(p_din6_alt);
//	in_port_alt_dir&=~(p_din6_alt);

	out_port_1&=~(p_dout_0+p_dout_1+p_dout_2+p_dout_3);
	out_port_1_dir|=(p_dout_0+p_dout_1+p_dout_2+p_dout_3);

	out_port_2&=~(p_dout_4 + p_dout_5);
	out_port_2_dir|=(p_dout_4 + p_dout_5);
	
	out_port_3&=~(p_dout_6+p_dout_7);
	out_port_3_dir|=(p_dout_6+p_dout_7);

//	aout_port&=~(p_aout0);
//	aout_port_dir|=(p_aout0);
	
	led_port&=~(led_out);
	led_port_dir|=(led_out);
	
	// Analog outputs
//	TCNT3=0;
//	TCCR3A=0xC3;
//	TCCR3B=0x01;	// divider is 1024, one step is equal 92.6mks
//	TCCR3C=0;
//	OCR3A=0x0000;//(1<<FOC1A);
//	OCR3B=0x0000;//(1<<FOC1A);
	
	io.aoutput[0]=0;
//	io.aoutput[1]=500;	
//	MenuRegs.t0=200;			
	
}
//------------------------------------------------------------------------------
void io_handle()
{
//	u8 i;
//	f32	ftmp;
//    u16 tmp16_2;
//    u16 tmp16;	
	
	//------------- Outputs ------------------

	// Out0
	if(io.dout & 0x01)
		out_port_1|=p_dout_0;
	else
		out_port_1&=~p_dout_0;	

	// Out1
	if(io.dout & 0x02)
		out_port_2|=p_dout_5;
	else
		out_port_2&=~p_dout_5;		
	
	// Out2
	if(io.dout & 0x04)
		out_port_1|=p_dout_1;
	else
		out_port_1&=~p_dout_1;	
	
	// Out3
	if(io.dout & 0x08)
		out_port_1|=p_dout_2;
	else
		out_port_1&=~p_dout_2;	
	
	// Out4
	if(io.dout & 0x10)
		out_port_1|=p_dout_3;
	else
		out_port_1&=~p_dout_3;	
	
	// Out5
	if(io.dout & 0x20)
		out_port_2|=p_dout_4;
	else
		out_port_2&=~p_dout_4;	
		
	// Out6
	if(io.dout & 0x40)
		out_port_3|=p_dout_6;
	else
		out_port_3&=~p_dout_6;		
	
	if(io.dout & 0x80)
		out_port_3|=p_dout_7;
	else
		out_port_3&=~p_dout_7;			
		
	//------------- Inputs ------------------
	// In0
	if(in_port_ins & p_din0)
		io.din&=~0x01;	
	else
		io.din|=0x01;
	// In1
	if(in_port_ins & p_din1)
		io.din&=~0x02;	
	else
		io.din|=0x02;
	// In2
	if(in_port_ins & p_din2)
		io.din&=~0x04;	
	else
		io.din|=0x04;
	// In3
	if(in_port_ins & p_din3)
		io.din&=~0x08;	
	else
		io.din|=0x08;	
	// In4
	if(in_port_ins & p_din4)
		io.din&=~0x10;	
	else
		io.din|=0x10;	
	// In5
	if(in_port_ins & p_din5)
		io.din&=~0x20;	
	else
		io.din|=0x20;	
	// In6
//	if(in_pin_alt & p_din6_alt)
//		io.din&=~0x40;	
//	else
//		io.din|=0x40;	
	//------------- Analog output ------------------
	
//	for(i=0;i<NUM_AOUT;i++)
//	{
//		tmp16=io.aoutput[i];
//		tmp16_2=io.aoutput[i];		
//		tmp16_2/=100;
//		tmp16=tmp16+tmp16_2*3;
//		if(tmp16>45)tmp16-=40;
//		else tmp16=0;
//		switch(i)
//		{
//			case 0: OCR3A=tmp16;break;
//			case 1: OCR3B=tmp16;break;
//			case 2: OCR3C=tmp16;break;
//			case 3: OCR1A=tmp16;break;
//			case 4: OCR1B=tmp16;break;
//			case 5: OCR1C=tmp16;break;															
//		}
//	}
	
/*
	// Season checking
#ifdef _SEASON_DATE	
	// Winter		
	MenuRegs.Season=1;	// Winter
	if((MenuRegs.Time.field.Month>MenuRegs.Time_Summ.field.Month)&&(MenuRegs.Time.field.Month<MenuRegs.Time_Wint.field.Month))	
		MenuRegs.Season=0;	// Summer
	else
		if(MenuRegs.Time.field.Month==MenuRegs.Time_Summ.field.Month)
		{
			if(MenuRegs.Time.field.Date>=MenuRegs.Time_Summ.field.Date)
				MenuRegs.Season=0;	// Summer
		}
		else
			if(MenuRegs.Time.field.Month==MenuRegs.Time_Wint.field.Month)
				if(MenuRegs.Time.field.Date<MenuRegs.Time_Wint.field.Date)
					MenuRegs.Season=0;	// Summer
#endif	
*/
}
//------------------------------------------------------------------------------
