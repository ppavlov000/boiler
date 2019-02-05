//-----------------------------------------------------------------------------------
#include "..\..\..\System\main.h"
#include "inavr.h"
#include <iom128.h>
void io_init()
{
	memset(&io,0,sizeof(io));
	// Default
	io.num_di=4;
	io.num_do=5;
	io.num_ai=4;
	io.num_ao=2;

	in_port&=~(p_din0+p_din1+p_din2+p_din3+p_vsence);
	in_port_dir&=~(p_din0+p_din1+p_din2+p_din3+p_vsence);
	out_port&=~(p_dout_rel+p_dout0+p_dout1+p_dout2+p_dout3);
	out_port_dir|=(p_dout_rel+p_dout0+p_dout1+p_dout2+p_dout3);
	aout_port&=~(p_aout0+p_aout1);
	aout_port_dir|=(p_aout0+p_aout1);

	TCNT3=0;
	TCCR3A=0xf3;
	TCCR3B=0x01;	// divider is 1024, one step is equal 92.6mks
	TCCR3C=0;
	OCR3A=0x0000;//(1<<FOC1A);
	OCR3B=0x0000;//(1<<FOC1A);

	io.aoutput[0]=1000;
	io.aoutput[1]=500;
}
//-----------------------------------------------------------------------------------
void io_handle()
{
//	u8 i;
	f32	ftmp;
	//------------- Outputs ------------------
	// Relay
	if(io.dout & 0x01)
		io_port|=p_dout_rel;
	else
		io_port&=~p_dout_rel;
	// Out0
	if(io.dout & 0x02)
		io_port|=p_dout0;
	else
		io_port&=~p_dout0;
	// Out1
	if(io.dout & 0x04)
		io_port|=p_dout1;
	else
		io_port&=~p_dout1;
	// Out2
	if(io.dout & 0x08)
		io_port|=p_dout2;
	else
		io_port&=~p_dout2;
	// Out3
	if(io.dout & 0x10)
		io_port|=p_dout3;
	else
		io_port&=~p_dout3;
		
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
	//------------- Analog output ------------------
	OCR3A=io.aoutput[0];
	OCR3B=io.aoutput[1];
}
//-----------------------------------------------------------------------------------
