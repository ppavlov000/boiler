#include "..\..\..\..\System\Main.h"
//-----------------------------------------------------------------------------------
//u8 PID_Changed=0;
//u8 DI4_Changed=0;
extern s16 Preset;
extern u8 new_step;
extern u8 str[40];
//-----------------------------------------------------------------------------------
u8 Monthes[12]={31,28,31,30,31,30,31,31,30,31,30,31};
//2008.01.01 - 2 (вторник)
u8 get_day_of_week(TTime *time)
{
	u8 year_rem;
//	u16 year_quot;	
	u32 date=0,tmp;
	u16 j;
	u8 tmp2;
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
	tmp2=tmp;
//	ByteToStr(str,&tmp2,0);
//	lcd_sprintf(str,0,2);
	return tmp;
}
//-----------------------------------------------------------------------------------

void custom_handle()
{
	u8 tmp=m.sch_day_night;
//	u32 tmp32=0;
	get_day_of_week(&ft);
	if(m.sch_auto_manual==0) // Auto
	{		
		// Morning
		tmp=1;
		if(ft.field.Hour>=m.sch[ft.field.Day-1][0].Hour)
			if(ft.field.Hour<=m.sch[ft.field.Day-1][1].Hour)
			{
				if(ft.field.Hour==m.sch[ft.field.Day-1][0].Hour)
					if(ft.field.Hour==m.sch[ft.field.Day-1][1].Hour)
						if((ft.field.Minute>=m.sch[ft.field.Day-1][0].Minute))
							if((ft.field.Minute<m.sch[ft.field.Day-1][1].Minute))							
								tmp=0;

				if(ft.field.Hour==m.sch[ft.field.Day-1][0].Hour)
				{
					if((ft.field.Minute>=m.sch[ft.field.Day-1][0].Minute))
							tmp=0;
				}
				else
				{
					if(ft.field.Hour==m.sch[ft.field.Day-1][1].Hour)
					{
						if((ft.field.Minute<m.sch[ft.field.Day-1][1].Minute))
								tmp=0;
					}
					else
						tmp=0;
				}
			}
		if(m.sch_day_night!=tmp)
		{
			if(tmp==0)Preset=m.sch_temperature[0];
			if(tmp==1)Preset=m.sch_temperature[1];
			Button_no_update_time=500;
			new_step=20;	
			FT_Time=0;				
		}
		m.sch_day_night=tmp;
	}
	
}
//-----------------------------------------------------------------------------------
