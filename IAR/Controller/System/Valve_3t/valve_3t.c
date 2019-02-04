//------------------------------------------------------------------------------
#include "..\main.h"
//------------------------------------------------------------------------------
s32	sum;
volatile u16 PID_P3_Time[NUM_PID];
//------------------------------------------------------------------------------
void valve_3t_init(void)
{	
#if MAX_VALVE_3T_NUMBER!=0
	u8 i;
//	memset(&pid,0,sizeof(pid));	
//	memset(pmem,0,NUM_PID*sizeof(TIntMem));			
#endif
}
//------------------------------------------------------------------------------
void valve_3t_handle(void)
{
#if MAX_VALVE_3T_NUMBER!=0
	u8 q;
	s16	tmp,d,ud;
	s16 delta;
	f32	power;
	f32	unsigned_power;
	f32 power_step;
	if(MenuRegs.Manual_Mode==MANUAL_MODE)return; // In manual mode no changes in PID
	for(q=0;q<MAX_VALVE_3T_NUMBER;q++)
	{
		// Calculating 3 point servoprivod values
		d=pid[q].power-pid[q].p3;
		if(d<0)ud=-d;
		else ud=d;
		if(ud<NUM_VALVE_STEP)d=0;

		if(d!=0)
		{				
			 if(d>0)
			 	pid[q].open=1;
			 else
			 	pid[q].open=0;
			 if(d<0)
			 	pid[q].close=1;				
			 else
			 	pid[q].close=0;				 	
		}
		else
		{
			pid[q].open=0;				
			pid[q].close=0;				
		}		
	}
#endif
}
//------------------------------------------------------------------------------
void Set_Pid_Temperature()
{
#if MAX_VALVE_3T_NUMBER!=0
	if(Params[0]<MAX_VALVE_3T_NUMBER)
		pid[Params[0]].t0=Params[1];
#endif
}
//------------------------------------------------------------------------------
