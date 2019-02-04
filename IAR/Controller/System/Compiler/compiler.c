//-----------------------------------------------------------------------------------
#ifndef __COMPILER2
//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
u8 i;
//u8 Manual_Mode=0;
u8 Program_Valid=0;
TProgLine pline;
//-----------------------------------------------------------------------------------
void Intr_Init()
{
	memset((void *)&intr, 0, sizeof(intr));	
	intr.addr=CODE_START_ADDR;
	intr.status=int_Stop;	// off
}
//-----------------------------------------------------------------------------------
void Intr_Program_Start()
{
	if(Program_Valid==0)return;
	memset((void *)&intr, 0, sizeof(intr));		
	intr.addr=CODE_START_ADDR;
	intr.status=int_Run;	// ON
}
//-----------------------------------------------------------------------------------
void Intr_IRQ0_Start()
{
	if(Program_Valid==0)return;
	memset((void *)&intr, 0, sizeof(intr));		
	intr.addr=CODE_IRQ0_ADDR;
	intr.status=int_Run;	// ON
}
//-----------------------------------------------------------------------------------
void Intr_IRQ1_Start()
{
	if(Program_Valid==0)return;
	memset((void *)&intr, 0, sizeof(intr));		
//	memcpy(&intr.in_params,&MenuRegs.params,sizeof(intr.in_params));	
	intr.addr=CODE_IRQ1_ADDR;
//	__sprintf(outtxt,"\n\r");
//	LongToStr(outtxt,(u32*)&intr.addr,1);	
	intr.status=int_Run;	// ON
}
//-----------------------------------------------------------------------------------
void Intr_IRQ2_Start()
{
	if(Program_Valid==0)return;
	memset((void *)&intr, 0, sizeof(intr));		
//	memcpy(&intr.in_params,&MenuRegs.params,sizeof(intr.in_params));
	intr.addr=CODE_IRQ2_ADDR;
//	__sprintf(outtxt,"\n\r");
//	LongToStr(outtxt,(u32*)&intr.addr,1);	
	intr.status=int_Run;	// ON
}
//-----------------------------------------------------------------------------------
void Intr_IRQ3_Start()
{
	if(Program_Valid==0)return;
	memset((void *)&intr, 0, sizeof(intr));	
//	memcpy(&intr.in_params,&MenuRegs.params,sizeof(intr.in_params));	
	intr.addr=CODE_IRQ3_ADDR;
//	__sprintf(outtxt,"\n\r");
//	LongToStr(outtxt,(u32*)&intr.addr,1);	
	intr.status=int_Run;	// ON
}

//-----------------------------------------------------------------------------------
void Intr_Program_Stop()
{
	intr.status=int_Stop;	// off
}
//-----------------------------------------------------------------------------------
void Intr_Handle()
{
	if(MenuRegs.Manual_Mode==MANUAL_MODE)return;
	if(intr.status!=program_run)return;
	//fram_mem_read(intr.addr,(u8*)&pline,CODE_LINE_LEN);
	FGet(intr.addr,(u8*)&pline,CODE_LINE_LEN);
	intr.addr+=CODE_LINE_LEN;			
	Intr_Program_Line_Handle();
}
//-----------------------------------------------------------------------------------
void Intr_Program_Line_Handle()
{
	Intr_Program_Line_Handle_GoTo();
	Intr_Program_Line_Handle_Math();
	Intr_Program_Line_Handle_Logic();
}
//-----------------------------------------------------------------------------------
s32 get_operand(TOperandFields op)
{
	s32 tmp32;
	switch(op.type)
	{
		case op_ao:					tmp32=io.aoutput[op.body.u8d];break;
		case op_ai:					tmp32=io.ainput[op.body.u8d];break;				
		case op_di:					tmp32=(io.din>>op.body.u16d) & 1;break;				
		case op_do:					tmp32=(io.dout>>op.body.u16d) & 1;break;	
		case op_digit:				tmp32=op.body.s32d;break;					
		case op_reg:				tmp32=intr.reg[op.body.u8d];break;
		case op_time_delay:			tmp32=intr.t32[op.body.u8d]; break;
		case op_time_beep:			tmp32=BuzzerTime; break;

		case op_pid_channel:		tmp32=pid[op.body.u8d].channel;break;		
		case op_pid_t0:				tmp32=pid[op.body.u8d].t0;break;			
		case op_pid_pow_max:		tmp32=pid[op.body.u8d].power_max;break;			
		case op_pid_pow_min:		tmp32=pid[op.body.u8d].power_min;break;			
		case op_pid_pow:			tmp32=pid[op.body.u8d].power;break;			
		case op_pid_ena:			tmp32=pid[op.body.u8d].mode;break;	
		case op_pid_slow:			tmp32=pid[op.body.u8d].PID_POWER_STEP[0]*1000;break;			
		case op_pid_fast:			tmp32=pid[op.body.u8d].PID_POWER_STEP[1]*1000;break;	
		case op_pid_open:			tmp32=pid[op.body.u8d].open;break;			
		case op_pid_close:			tmp32=pid[op.body.u8d].close;break;	
		case op_pid_hc:				tmp32=pid[op.body.u8d].heating_cooling;break;	
		
		case op_season:				tmp32=MenuRegs.Season.season;break;	
		case op_in_parameters:		if(op.body.u8d<PARAMETERS_MAX)tmp32=intr.in_params[op.body.u8d];break;	
		case op_out_parameters:		if(op.body.u8d<PARAMETERS_MAX)tmp32=intr.out_params[op.body.u8d];break;	

#if MAX_FANCOIL_NUMBER
		case op_fan_channel:		tmp32=fan[op.body.u8d].Channel;break;	
		case op_fan_t0:				tmp32=fan[op.body.u8d].T;break;	
		case op_fan_mode:			tmp32=fan[op.body.u8d].Fan_Mode;break;	
		case op_fan_lvl:			tmp32=fan[op.body.u8d].Fan_Lvl;break;	
		case op_fan_low:			tmp32=fan[op.body.u8d].TLow;break;	
		case op_fan_medium:			tmp32=fan[op.body.u8d].TMedium;break;	
		case op_fan_high:			tmp32=fan[op.body.u8d].THigh;break;	
		case op_fan_hyst:			tmp32=fan[op.body.u8d].Hysteresis;break;	
		case op_fan_time:			tmp32=fan[op.body.u8d].Fan_Time;break;	
		case op_fan_day:			tmp32=fan[op.body.u8d].Day_Night;break;	
#endif	
		
	}
	return tmp32;
}
//-----------------------------------------------------------------------------------
void set_operand(TOperandFields op,s32 value)
{
	s32 tmp32=0;
	switch(op.type)
	{
		case op_ao:					io.aoutput[op.body.u8d]=(s16)value;break;
		
		case op_do:				
			tmp32=1<<op.body.u32d;
			if(value!=0)io.dout|=tmp32;
			else io.dout&=~tmp32;		
		break;	
		
		case op_reg:				intr.reg[op.body.u8d]=value;break;
		case op_time_delay:			intr.t32[op.body.u8d]=value; break;
		case op_time_beep:			BuzzerTime=value; break;

		case op_pid_channel:		if(op.body.u8d<NUM_PID)pid[op.body.u8d].channel=value;break;			
		case op_pid_i:				if(op.body.u8d<NUM_PID)pid[op.body.u8d].i=value;break;			
		case op_pid_p:				if(op.body.u8d<NUM_PID)pid[op.body.u8d].p=value;break;			
		case op_pid_d:				if(op.body.u8d<NUM_PID)pid[op.body.u8d].d=value;break;			
		case op_pid_ti:				if(op.body.u8d<NUM_PID)pid[op.body.u8d].ti=value;break;			
		case op_pid_t0:				if(op.body.u8d<NUM_PID)pid[op.body.u8d].t0=value;break;	
		case op_pid_ena:			if(op.body.u8d<NUM_PID)pid[op.body.u8d].mode=value;break;
		case op_pid_pow:			if(op.body.u8d<NUM_PID)pid[op.body.u8d].power=value;break;			
		case op_pid_pow_max:		if(op.body.u8d<NUM_PID)pid[op.body.u8d].power_max=value;break;			
		case op_pid_pow_min:		if(op.body.u8d<NUM_PID)pid[op.body.u8d].power_min=value;break;		
		case op_pid_t3max:			if(op.body.u8d<NUM_PID)pid[op.body.u8d].t3max=value;break;			
		case op_pid_p3:				if(op.body.u8d<NUM_PID)pid[op.body.u8d].p3=value;break;	
		case op_pid_slow:			if(op.body.u8d<NUM_PID)pid[op.body.u8d].PID_POWER_STEP[0]=(f32)value/1000;break;			
		case op_pid_fast:			if(op.body.u8d<NUM_PID)pid[op.body.u8d].PID_POWER_STEP[1]=(f32)value/1000;break;	
		case op_pid_hc:				if(op.body.u8d<NUM_PID)pid[op.body.u8d].heating_cooling=value;break;
		
		
		case op_season:				MenuRegs.Season.season=value;break;	
		case op_in_parameters:		if(op.body.u8d<PARAMETERS_MAX)intr.in_params[op.body.u8d]=value;break;	
		case op_out_parameters:		if(op.body.u8d<PARAMETERS_MAX)intr.out_params[op.body.u8d]=value;break;			
#if MAX_FANCOIL_NUMBER
		case op_fan_channel:		if(op.body.u8d<MAX_FANCOIL_NUMBER)fan[op.body.u8d].Channel=value;break;	
		case op_fan_t0:				if(op.body.u8d<MAX_FANCOIL_NUMBER)fan[op.body.u8d].T=value;break;	
		case op_fan_mode:			if(op.body.u8d<MAX_FANCOIL_NUMBER)fan[op.body.u8d].Fan_Mode=value;break;	
		case op_fan_lvl:			if(op.body.u8d<MAX_FANCOIL_NUMBER)fan[op.body.u8d].Fan_Lvl=value;break;	
		case op_fan_low:			if(op.body.u8d<MAX_FANCOIL_NUMBER)fan[op.body.u8d].TLow=value;break;	
		case op_fan_medium:			if(op.body.u8d<MAX_FANCOIL_NUMBER)fan[op.body.u8d].TMedium=value;break;	
		case op_fan_high:			if(op.body.u8d<MAX_FANCOIL_NUMBER)fan[op.body.u8d].THigh=value;break;	
		case op_fan_hyst:			if(op.body.u8d<MAX_FANCOIL_NUMBER)fan[op.body.u8d].Hysteresis=value;break;	
		case op_fan_time:			if(op.body.u8d<MAX_FANCOIL_NUMBER)fan[op.body.u8d].Fan_Time=value;break;	
		case op_fan_day:			if(op.body.u8d<MAX_FANCOIL_NUMBER)fan[op.body.u8d].Day_Night=value;break;		
#endif			
	}
}
//-----------------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------------
