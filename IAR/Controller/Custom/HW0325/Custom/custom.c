#include "..\..\..\System\main.h"
//-----------------------------------------------------------------------------------
u8 PID_Changed=0;
u8 DI4_Changed=0;
//-----------------------------------------------------------------------------------
void custom_handle()
{
	u8 tmp=pid[0].mode;
	u32 tmp32=0;
	// No operations
	return;
	
	if(pid[0].mode!=PID_MODE_ERROR)	
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
/*		if((PID_Changed==0)&&(tmp==PID_MODE_AUTO))
		{
			pid[0].mode=tmp;
			PID_Changed=1;
		}
		if((PID_Changed==1)&&(tmp==PID_MODE_STOP))
		{
			pid[0].mode=tmp;
			PID_Changed=0;
		}
*/		
	}

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
/*		if((DI4_Changed==0)&&((tmp32 && DO_04)!=0))
		{
			io.dout|=DO_04;
			DI4_Changed=1;
		}
		if((DI4_Changed==1)&&((tmp32 && DO_04)==0))
		{
			io.dout&=~DO_04;
			DI4_Changed=0;
		}	
*/	
	
}
//-----------------------------------------------------------------------------------
