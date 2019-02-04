//------------------------------------------------------------------------------
#include "..\main.h"
//------------------------------------------------------------------------------
#if NUM_PID
//------------------------------------------------------------------------------
s32	sum;
volatile u16 PID_P3_Time[NUM_PID];
f32 acc[NUM_PID];
f32 acc2[NUM_PID];
s16 diff=0;
s16 tsum[NUM_PID];
f32 ds[NUM_PID];
f32	pp,ii,dd;
s16 pii[NUM_PID];
s16 ppp[NUM_PID];
s16 pdd[NUM_PID];
s16 old[NUM_PID];
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
extern in_flash u8	pdic[][80];
//------------------------------------------------------------------------------
void pid_init(void)
{	
#if NUM_PID
	u8 i;
//	memset(&pid,0,sizeof(pid));	
//	memset(pmem,0,NUM_PID*sizeof(TIntMem));			
	for(i=0;i<NUM_PID;i++)
	{
		pid[i].channel=i;
		pid[i].t0=220;
		pid[i].ti=60;	// sec
		pid[i].power_max=999;
		pid[i].power_min=0;	
		pid[i].t3max=150;
		pid[i].p3=0;		
		pid[i].open=0;
		pid[i].close=0;		
//		pmem[i].cs=0;
//		pmem[i].cm=0;
//		pmem[i].ch=0;
//		pmem[i].ci=0;
		pid[i].p=100;	
		pid[i].i=100;		
		pid[i].d=500;				
		pid[i].mode=0;		
		acc[i]=0;
		acc2[i]=0;
		old[i]=0;
		ds[i]=0;
	}
#endif
}
//------------------------------------------------------------------------------
void pid_handle(void)
{
#if NUM_PID
	u8 q;
	s16	tmp,d,ud;
	s16 delta;
	f32	power;
	f32	unsigned_power;
	f32 power_step;
	if(MenuRegs.Manual_Mode==MANUAL_MODE)return; // In manual mode no changes in PID
	for(q=0;q<NUM_PID;q++)
	{
		if((pid[q].mode==PID_MODE_AUTO)||(pid[q].mode==PID_MODE_WARNING))
		{
			tmp=pid[q].t0-io.ainput[pid[q].channel];
			if(pid[q].heating_cooling==PID_COOLING)tmp=-tmp;
			//---- Calculating PID itself
			//---- proporcional
			pp=tmp;
			pp*=pid[q].p;
			pp/=100;	// get real value
			//---- differential
			dd=tmp-old[q];
			old[q]=tmp;
			dd*=pid[q].d;
			ds[q]*=63;
			ds[q]+=dd;
			ds[q]/=64;
			dd=ds[q];
			if(dd>32000)dd=32000;
			if(dd<-32000)dd=-32000;			
			tmp=dd;
			diff=dd;			
			//---- integral
			sum=0;
			ii=sum;
			ii/=pid[q].ti;
			ii*=pid[q].i;
			ii/=100;
			// Test
			ppp[q]=pp*10;
			pii[q]=ii*10;
			pdd[q]=dd*10;
			
			power=ppp[q]+pii[q]+pdd[q];
			
			if(power<0)
				unsigned_power=-power;
			else
				unsigned_power=power;
			
			if(unsigned_power<pid[q].PID_POWER_LIMIT[0])
				power=0;
			else
			{
				if(unsigned_power<pid[q].PID_POWER_LIMIT[1])
					power_step=pid[q].PID_POWER_STEP[0];	
				else
					power_step=pid[q].PID_POWER_STEP[1];
					
				if(power>0)	
					acc[q]+=power_step;	
				else
					acc[q]-=power_step;
			}
			tsum[q]=power;
			delta=acc[q];
			acc[q]-=delta;
			pid[q].power+=delta;

			if(pid[q].power>999)pid[q].power=999;			
			if(pid[q].power<pid[q].power_min)pid[q].power=pid[q].power_min;	
			if(pid[q].power>pid[q].power_max)pid[q].power=pid[q].power_max;
		}
		// Calculating 3 point servoprivod values
		d=pid[q].power-pid[q].p3;//NUM_VALVE_STEP
		if(d<0)ud=-d;
		else ud=d;
		if(ud<NUM_VALVE_STEP)d=0;
		// Test
//		ud=d;
//		if(d<0)ud=-d;
//		s=pid[q].t3max/1000.0;
//		if(ud>=s)
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
#if NUM_PID
	if(Params[0]<NUM_PID)
		pid[Params[0]].t0=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Pid_Mode()
{
#if NUM_PID
	if(Params[0]<NUM_PID)
		pid[Params[0]].mode=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Pid_Power_Min()
{
#if NUM_PID
	if(Params[0]<NUM_PID)
		pid[Params[0]].power_min=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Pid_Power_Max()
{
#if NUM_PID
	if(Params[0]<NUM_PID)
		pid[Params[0]].power_max=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Pid_Power()
{
#if NUM_PID
	if(Params[0]<NUM_PID)
		pid[Params[0]].power=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Pid_Diff()
{
#if NUM_PID
	if(Params[0]<NUM_PID)
		pid[Params[0]].d=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Pid_Int()
{
#if NUM_PID
	if(Params[0]<NUM_PID)
		pid[Params[0]].i=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Pid_Prop()
{
#if NUM_PID
	if(Params[0]<NUM_PID)
		pid[Params[0]].p=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Pid_Channel()
{
#if NUM_PID
	if(Params[0]<NUM_PID)
		pid[Params[0]].channel=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Pid_Slow()
{
#if NUM_PID
	if(Params[0]<NUM_PID)
		pid[Params[0]].PID_POWER_STEP[0]=(f32)Params[1]/(f32)1000;
#endif
}
//------------------------------------------------------------------------------
void Set_Pid_Fast()
{
#if NUM_PID
	if(Params[0]<NUM_PID)
		pid[Params[0]].PID_POWER_STEP[1]=(f32)Params[1]/(f32)1000;
#endif
}
//------------------------------------------------------------------------------
void Set_Pid_ZeroB()
{
#if NUM_PID
	if(Params[0]<NUM_PID)
		pid[Params[0]].PID_POWER_LIMIT[0]=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Pid_LowB()
{
#if NUM_PID	
  if(Params[0]<NUM_PID)
		pid[Params[0]].PID_POWER_LIMIT[1]=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Pid_Heating()
{
#if NUM_PID
	if(Params[0]<NUM_PID)
		pid[Params[0]].heating_cooling=Params[1];
#endif
}
//-----------------------------------------------------------------------------------
void Mod_Show_Status_PID(u8 num)
{
#if NUM_PID
//	u8 j;
	u16 tmp;
//	s32 tmp;
	// PID state
	__sprintf_P(outtxt,pdic[15]);			
	__sprintf_P(outtxt,pdic[37]);				
	ShowTemperature(outtxt,&io.ainput[pid[num].channel]);				
	__sprintf_P(outtxt,pdic[16]);			
	ShowTemperature(outtxt,&pid[num].t0);
	__sprintf_P(outtxt,pdic[17]);	
	switch(pid[num].mode)
	{
		case 0:__sprintf(outtxt,"DISABLED");break;
		case 1:__sprintf(outtxt,"ENABLED");break;
		case 3:__sprintf(outtxt,"WARNING");break;		
		case 2:__sprintf(outtxt,"BRAKEDOWN");break;		
		
	}	
	__sprintf_P(outtxt,pdic[18]);			
	ByteToStr(outtxt,&pid[num].channel,1);__sprintf(outtxt,"]");
	__sprintf_P(outtxt,pdic[19]);			
	WordToStrSigned(outtxt,&pid[num].p);	
	__sprintf_P(outtxt,pdic[21]);			
	WordToStrSigned(outtxt,&pid[num].i);	
	__sprintf_P(outtxt,pdic[20]);			
	WordToStrSigned(outtxt,&pid[num].d);	
	__sprintf_P(outtxt,pdic[22]);			
	WordToStr(outtxt,&pid[num].ti,0);				
	
	__sprintf_P(outtxt,pdic[29]);			
	ShowPowerShort(outtxt,&pid[num].power_min);					
	__sprintf_P(outtxt,pdic[30]);			
	ShowPowerShort(outtxt,&pid[num].power_max);					
	__sprintf_P(outtxt,pdic[31]);			
	ShowPowerShort(outtxt,&pid[num].power);					
	__sprintf_P(outtxt,pdic[33]);			
	WordToStr(outtxt,&pid[num].t3max,0);
	__sprintf_P(outtxt,pdic[34]);			
	ShowPowerShort(outtxt,&pid[num].p3);
	__sprintf_P(outtxt,pdic[35]);			
	ByteToStr(outtxt,&pid[num].open,0);
	__sprintf_P(outtxt,pdic[36]);			
	ByteToStr(outtxt,&pid[num].close,0);
	// Speeds
	tmp=pid[num].PID_POWER_STEP[0]*1000;
	__sprintf_P(outtxt,pdic[39]);				
	WordToStr(outtxt,&tmp,0);	
	tmp=pid[num].PID_POWER_STEP[1]*1000;
	__sprintf_P(outtxt,pdic[40]);				
	WordToStr(outtxt,&tmp,0);	
	// Limits
	tmp=pid[num].PID_POWER_LIMIT[0];
	__sprintf_P(outtxt,pdic[46]);				
	WordToStr(outtxt,&tmp,0);	
	tmp=pid[num].PID_POWER_LIMIT[1];
	__sprintf_P(outtxt,pdic[47]);				
	WordToStr(outtxt,&tmp,0);		
	__sprintf_P(outtxt,pdic[53]);
	if(pid[num].heating_cooling==PID_HEATING)			
		__sprintf_P(outtxt,pdic[54]);
	else
		__sprintf_P(outtxt,pdic[55]);
	
	// Test
	__sprintf(outtxt,"\n\r");
	__sprintf(outtxt,"\n\r     pp=");			
	WordToStrSigned(outtxt,&ppp[num]);					
	__sprintf(outtxt,"\n\r     pi=");			
	WordToStrSigned(outtxt,&pii[num]);					
	__sprintf(outtxt,"\n\r     pd=");			
	WordToStrSigned(outtxt,&pdd[num]);	
	__sprintf(outtxt,"\n\r     sum=");			
	WordToStrSigned(outtxt,&tsum[num]);	
#endif	
}
//-----------------------------------------------------------------------------------
void Mod_Show_PID()
{
#if NUM_PID
	if(Params[0]<NUM_PID)
		Mod_Show_Status_PID(Params[0]);
	else
		__sprintf(outtxt,"\n\rWrong PID number");
#endif
}
//------------------------------------------------------------------------------
