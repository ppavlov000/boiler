#include "..\..\..\..\System\Main.h"
//-----------------------------------------------------------------------------------
//u8 PID_Changed=0;
//u8 DI4_Changed=0;
//extern s16 Preset;
extern u8 new_step;
extern u8 str[40];
u16 time_mins[2];
u16 time_curr;

//-----------------------------------------------------------------------------------
u8 Monthes[12]={31,28,31,30,31,30,31,31,30,31,30,31};
//2008.01.01 - 2 (вторник)
u8 get_day_of_week(TTime *time)
{
	u8 year_rem;
//	u16 year_quot;	
	u32 date=0,tmp;
	u16 j;
//	u8 tmp2;
//	while
	year_rem=time->field.Year & 0x03;
	for(j=1;j<13;j++)
	{
		if(time->field.Month!=j)
		{
			date+=Monthes[j-1];			
			if(year_rem==0)		
				if(j==1)		
					date++;	
		}
		else
		{
			date+=time->field.Date;
			break;
		}
	}
//	sprintf(outtxt,"\n\r date=");
//	LongToStr(outtxt,&date,0);
	
//	if(time.field.Year>8)
		for(j=8;j<time->field.Year;j++)
		{
			date+=365;
			year_rem=j & 0x03;
			if(year_rem==0)
				date++;
		}
//	sprintf(outtxt,"\n\r date=");
//	LongToStr(outtxt,&date,0);
	
	tmp=date/7;
	tmp=date-(tmp*7);
//	tmp+=7;
	tmp+=1;
	if(tmp>7)tmp-=7;	
//	sprintf(outtxt,"\n\r day=");
//	LongToStr(outtxt,&tmp,0);	
	time->field.Day=tmp;
//	tmp2=tmp;
//	ByteToStr(str,&tmp2,0);
//	lcd_sprintf(str,0,2);
	return tmp;
}
//	u8 str4[10];
//	u8 str3[40];

//-----------------------------------------------------------------------------------
void custom_handle()
{
	u8 tmp=m.sch_day_night;
	TTime ft;
//	u32 tmp32=0;
	get_day_of_week(&MenuRegs.Time);
	ft=MenuRegs.Time;
	
	time_curr=ft.field.Hour*60+ft.field.Minute;
	time_mins[0]=m.sch[ft.field.Day-1][0].Hour*60+m.sch[ft.field.Day-1][0].Minute;
	time_mins[1]=m.sch[ft.field.Day-1][1].Hour*60+m.sch[ft.field.Day-1][1].Minute;
	
/*		u8 i;
		str3[0]=0;
		for(i=0;i<3;i++)
		{
			ByteToStr(str4,&m.sch_param_ena[i],0);
			stradd(str3,str4);
			stradd(str3," ");			
		}
		lcd_sprintf(str3,0,2);		
*/	
	if(m.sch_auto_manual==0) 			// Auto
	{		
		// Morning
		tmp=1;
		//(1) Day
		if((time_curr>=time_mins[0])&&(time_curr<time_mins[1]))tmp=0;
		//(2) Night
		if((time_curr>=time_mins[1])&&(time_curr<24*60))tmp=1;
		//(3) Night
		if((time_curr<time_mins[0])&&(time_curr>=0))tmp=1;
		//(4) Night
		if(time_mins[0]==time_mins[1])tmp=1;		// If dates are equal then night only
		//(5) Night
//		if((time_mins[0]>time_mins[1]))tmp=1;		// If time is not correct then night!
		//(6) Night		
		if(m.sch_enable[ft.field.Day-1]==0)tmp=1; 	// Enabled schedule for this day, if off then night only

/*		
	WordToStr(str3,&time_curr,0);	
	WordToStr(str4,&time_mins[0],0);
	stradd(str3," ");
	stradd(str3,str4);
	WordToStr(str4,&time_mins[1],0);
	stradd(str3," ");
	stradd(str3,str4);	
	ByteToStr(str4,&tmp,0);	
	stradd(str3," ");
	stradd(str3,str4);
	lcd_sprintf(str3,0,2);		
*/	
		
		if(m.sch_day_night!=tmp)
		{
			if(tmp==0)
			{
				if(m.sch_param_ena[0])				
					pid[0].t0=m.sch_temperature[0];
				if(m.sch_param_ena[1]){
					pritochka_fan_speed=m.sch_fan_speed[0];
					io.aoutput[0]=m.sch_fan_speed[0];				
				}
				if(m.sch_param_ena[2])				
					pid[0].mode=m.sch_mode[0];
			}
			if(tmp==1)
			{
				if(m.sch_param_ena[0])				
					pid[0].t0=m.sch_temperature[1];
				if(m.sch_param_ena[1]){
					pritochka_fan_speed=m.sch_fan_speed[1];
					io.aoutput[0]=m.sch_fan_speed[1];				
				}
				if(m.sch_param_ena[2])				
					pid[0].mode=m.sch_mode[1];
			}
			Button_no_update_time=500;
			new_step=100;	
			
			
/*
#if MAX_FANCOIL_NUMBER	
			if(tmp==0)
			{
				fan[0].Day_Night=fan_Day;
				m.BackLit_Value_Min=2;
				m.BackLit_Value_Max=9;
			}
			if(tmp==1)
			{
				fan[0].Day_Night=fan_Night;
				m.BackLit_Value_Min=0;
				m.BackLit_Value_Min=5;
			}
			Button_no_update_time=500;
			new_step=62;	
			FT_Time=0;				
#endif				
*/			
		}
		m.sch_day_night=tmp;
	}
	
}
//-----------------------------------------------------------------------------------
void work_to_regs()
{
	if(WorkInfo.type==TYPE_ALL_SEASON)
	{
		MenuRegs.Season.season=WorkInfo.season;
		return;
	}
	if(WorkInfo.type==TYPE_ALL_T)
	{
		fan[0].T=WorkInfo.temperature[0];
		pid[0].t0=WorkInfo.temperature[0];
		pid[1].t0=WorkInfo.temperature[0];		
		return;
	}

	if(WorkInfo.type!=TYPE_PRITOCHKA)return;	
	MenuRegs.Season.season=WorkInfo.season;
	// Recalculating pid preset temperatures
	pid[0].mode=WorkInfo.mode;
	pid[1].mode=WorkInfo.mode;
	//io.aoutput[0]=WorkInfo.speed[0];
	pritochka_fan_speed=WorkInfo.speed[0];
	io.aoutput[0]=pritochka_fan_speed;
//	in_param=WorkInfo.speed[0];
	pid[0].t0=WorkInfo.temperature[0];
	pid[1].t0=WorkInfo.temperature[0];
	pid[0].heating_cooling=PID_HEATING;		
	pid[1].heating_cooling=PID_HEATING;		
}
//-----------------------------------------------------------------------------------
void regs_to_work()
{
//	TWorkInfo *work_info=(TWorkInfo*)&tx.field.d[0];
	WorkInfo.type=TYPE_PRITOCHKA;
	WorkInfo.season=MenuRegs.Season.season;
	WorkInfo.mode=pid[0].mode;
	WorkInfo.temperature[0]=pid[0].t0;
	WorkInfo.temperature[1]=io.ainput[pid[0].channel];	
	WorkInfo.temperature[2]=0;	

	WorkInfo.speed[0]=io.aoutput[0];	
	WorkInfo.speed[1]=0;	
	WorkInfo.speed[2]=0;		
}
//-----------------------------------------------------------------------------------
