#include "..\..\..\System\main.h"
//-----------------------------------------------------------------------------------
u8 PID_Changed=0;
u8 DI4_Changed=0;
u8 Season_Timeout=0;
u8 Season_Count=3;
#define MAX_SEASON_COUNT	5
//-----------------------------------------------------------------------------------
void Season_Handle()
{
	if(MenuRegs.Season.mode==SEASON_AUTO)
	{
		// Temperature part		
		if(MenuRegs.Season.switch_temperature)
		{
			if(MenuRegs.Season.t<io.ainput[MenuRegs.Season.t_extern_channel])
			{
				if(Season_Timeout==0)
				{
					Season_Count++;
					Season_Timeout=5;
					if(Season_Count>=MAX_SEASON_COUNT)
					{
						Season_Count=MAX_SEASON_COUNT;
						MenuRegs.Season.season=SEASON_SUMMER;					
					}
				}
			}
			else
			{
				if(Season_Timeout==0)
				{
					if(Season_Count)Season_Count--;
					Season_Timeout=5;
					if(Season_Count==0)
					{
						Season_Count=MAX_SEASON_COUNT;
						MenuRegs.Season.season=SEASON_WINTER;					
					}
				}
			}							
		}
		// Date part
		if(MenuRegs.Season.switch_date)
		{
			MenuRegs.Season.season=SEASON_WINTER;						
			if(MenuRegs.Time.field.Month > MenuRegs.Season.date[0].field.Month)
				if(MenuRegs.Time.field.Month < MenuRegs.Season.date[1].field.Month)
					MenuRegs.Season.season=SEASON_SUMMER;

			if(MenuRegs.Time.field.Month == MenuRegs.Season.date[0].field.Month)
				if(MenuRegs.Time.field.Date >= MenuRegs.Season.date[0].field.Date)
					MenuRegs.Season.season=SEASON_SUMMER;

			if(MenuRegs.Time.field.Month == MenuRegs.Season.date[1].field.Month)
				if(MenuRegs.Time.field.Date < MenuRegs.Season.date[1].field.Date)
					MenuRegs.Season.season=SEASON_SUMMER;
		}		
	}
}
//-----------------------------------------------------------------------------------
void custom_handle()
{
//		memset(&MenuRegs.Schedule_Enable,0,1);	
//		memset(&MenuRegs.Schedule_Time,0,4);	
//		memset(&MenuRegs.Timer_Enable,0,1);	
//		memset(&MenuRegs.Timer_Time,0,4);	
	u8 tmp=pid[0].mode;
	u32 tmp32=0;
	
	Season_Handle();
	return;
/*	if(pid[0].mode!=PID_MODE_ERROR)	
	{
		if(MenuRegs.Schedule_Enable)
		{
	//		if(MenuRegs.Time.field.Hour>=MenuRegs.Schedule_Time[0].field.Hour)
	//			__no_operation();
			// Morning
			tmp=PID_MODE_STOP;	
			if(ft.field.Hour>=MenuRegs.Schedule_Time[0].field.Hour)
				if(ft.field.Hour<=MenuRegs.Schedule_Time[1].field.Hour)
				{
					if((ft.field.Hour==MenuRegs.Schedule_Time[0].field.Hour)&&(ft.field.Hour==MenuRegs.Schedule_Time[1].field.Hour))
					{
						if((ft.field.Minute>=MenuRegs.Schedule_Time[0].field.Minute)&&(ft.field.Minute<MenuRegs.Schedule_Time[1].field.Minute))
							tmp=PID_MODE_AUTO;	
					}
					else
						if(ft.field.Hour==MenuRegs.Schedule_Time[0].field.Hour)
						{
							if((ft.field.Minute>=MenuRegs.Schedule_Time[0].field.Minute))
									tmp=PID_MODE_AUTO;	
						}
						else
						{
							if(ft.field.Hour==MenuRegs.Schedule_Time[1].field.Hour)
							{
								if((ft.field.Minute<MenuRegs.Schedule_Time[1].field.Minute))
										tmp=PID_MODE_AUTO;	
							}
							else
								tmp=PID_MODE_AUTO;	
					}
				}
		}
		pid[0].mode=tmp;
//		if((PID_Changed==0)&&(tmp==PID_MODE_AUTO))
//		{
//			pid[0].mode=tmp;
//			PID_Changed=1;
//		}
//		if((PID_Changed==1)&&(tmp==PID_MODE_STOP))
//		{
//			pid[0].mode=tmp;
//			PID_Changed=0;
//		}

//	}

	tmp32=io.dout;
	tmp32&=~DO_04;
	if(MenuRegs.Timer_Enable)
	{
		// Morning
		tmp=0;	
		if(ft.field.Hour>=MenuRegs.Timer_Time[0].field.Hour)
			if(ft.field.Hour<=MenuRegs.Timer_Time[1].field.Hour)
			{
				if((ft.field.Hour==MenuRegs.Timer_Time[0].field.Hour)&&(ft.field.Hour==MenuRegs.Timer_Time[1].field.Hour))
				{
					if((ft.field.Minute>=MenuRegs.Timer_Time[0].field.Minute)&&(ft.field.Minute<MenuRegs.Timer_Time[1].field.Minute))
						tmp32|=DO_04;	
				}
				else
					if(ft.field.Hour==MenuRegs.Timer_Time[0].field.Hour)
					{
						if((ft.field.Minute>=MenuRegs.Timer_Time[0].field.Minute))
								tmp32|=DO_04;	
					}
					else
					{
						if(ft.field.Hour==MenuRegs.Timer_Time[1].field.Hour)
						{
							if((ft.field.Minute<MenuRegs.Timer_Time[1].field.Minute))
									tmp32|=DO_04;	
						}
						else
							tmp32|=DO_04;		
					}
			}
	}	
	io.dout=tmp32;
//		if((DI4_Changed==0)&&((tmp32 && DO_04)!=0))
//		{
//			io.dout|=DO_04;
//			DI4_Changed=1;
//		}
//		if((DI4_Changed==1)&&((tmp32 && DO_04)==0))
//		{
//			io.dout&=~DO_04;
//			DI4_Changed=0;
//		}	
	
*/	
}
//-----------------------------------------------------------------------------------
