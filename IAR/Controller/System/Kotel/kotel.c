//------------------------------------------------------------------------------
// Kotel software Ver 1.0
// Peter Pavlov
//------------------------------------------------------------------------------
#include "..\main.h"
//------------------------------------------------------------------------------
#if MAX_KOTEL_NUMBER

#define KOT_MODE_1			1	// Switch  1->2 change accordin temperature or timeout
#define KOT_MODE_1_TMEOUT	60*15
#define STOP_TIMEOUT		30*60
//------------------------------------------------------------------------------
// Variables
u8   	sh_on[2]={0};
u8		sh_off[2]={0};
u8   	fan_on[2]={0};
u8  	fan_off[2]={0};

u16 	Kotel_P3_Time=0;
u8  	sh_st[2]={0};
//u8  	fan_st[2]={0};
u16		Stop_Timeout=STOP_TIMEOUT;
u8 		old_kotel_mode=0;
u16 	Mode_1_timeout=KOT_MODE_1_TMEOUT;
// Text
in_flash u8 kotel_mode[][40]=
{
  "Stop",
  "",
};

in_flash u8 kotel_dic[][40]=
{
  "\n\r Kotel V1.0 parameters",     //0
  "\n\r   Mode    ",                //1
  "\n\r   T       ",                //2
  "\n\r   AI[", 					//3
  "\n\r",                           //4
  "\n\r   Fuel    ",                //5
  "\n\r   Fan_0   ",                //6
  "\n\r   Fan_1   ",                //7
  "\n\r   Smoke   ",                //8
  "\n\r   Shnek_0 ",                //9
  "\n\r   Shnek_1 ",                //10

  "\n\r Kotel parameters in mode ", //11
  "\n\r   T       ",                //12
  "\n\r   Fan     ",                //13
  "\n\r   Smoke   ",                //14
  "\n\r   Fan ON  ",                //15
  "\n\r   Fan OFF ",                //16
  "\n\r   Shn ENA ",                //17
  "\n\r   Shn ON  ",                //18
  "\n\r   Shn OFF ",                //19
  "\n\r Kotel fuel type is ", 		//20
  "\n\r  Record 0 ", 				//21
  "\n\r  Record 1 ", 				//22

  "\n\r   Open    ",                //23
  "\n\r   Close   ",                //24
  "\n\r   Power   ",                //25
  "\n\r   T3Max   ",                //26
  "\n\r   P3      ",                //27
};
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
void kotel_init(void)
{	
#if MAX_KOTEL_NUMBER
//	u8 i;
#endif
}
//------------------------------------------------------------------------------
void kotel_handle(void)
{
#if MAX_KOTEL_NUMBER
	u8	i;
	s16	tmp,d,ud;
	s16 diff[2];
	u8 	tmp8;

#if KOT_MODE_1==0
	if((kotel.mode>0)&&(kotel.mode<5))
	{
		tmp8=1;
		for(i=1;i<4;i++)
		{
			diff[0]=kotel.t + kotel.p[kotel.fuel][i-1].t;
//			diff[1]=kotel.t + kotel.p[kotel.fuel][i+1].t;			
			if(io.ainput[kotel.channel] > diff[0])
			{
				tmp8=i+1;
			}
		}
		kotel.mode=tmp8;		
	}
#endif
#if KOT_MODE_1==1	
	if((kotel.mode>1)&&(kotel.mode<5))
	{
		tmp8=2;
		for(i=2;i<4;i++)
		{
			diff[0]=kotel.t + kotel.p[kotel.fuel][i-1].t;
//			diff[1]=kotel.t + kotel.p[kotel.fuel][i+1].t;			
			if(io.ainput[kotel.channel] > diff[0])
			{
				tmp8=i+1;
			}
		}
		kotel.mode=tmp8;		
	}
	if((kotel.mode==1))
	{
		if(Mode_1_timeout==0)
		{
			kotel.mode=2;
		}
	}
	else Mode_1_timeout=KOT_MODE_1_TMEOUT;
#endif	
	diff[0]=kotel.t + kotel.p[kotel.fuel][3].t;
	if(io.ainput[kotel.channel] > diff[0])	
	{
		kotel.mode=5;
	}
	
	if(old_kotel_mode!=kotel.mode)
	{
		kotel.smoke_out=0;		
		for(i=0;i<2;i++)
		{
			kotel.fan_out[i]=0;
			kotel.shnek_out[i]=0;
			sh_on[i]=0;
			sh_off[i]=0;
			fan_on[i]=0;
			fan_off[i]=0;
			sh_st[i]=0;
//			fan_st[i]=0;			
		}		
	}
	old_kotel_mode=kotel.mode;
	switch(kotel.mode)
	{
	case 0:// Full stop
		kotel.smoke_out=0;
		for(i=0;i<2;i++)
		{
			kotel.fan_out[i]=0;
			kotel.shnek_out[i]=0;
		}
		break;
	case 5:// Ostanov
		kotel.smoke_out=kotel.smoke_speed[kotel.fuel]*10L;
		for(i=0;i<2;i++)
		{
			kotel.fan_out[i]=0;
			kotel.shnek_out[i]=0;
		}
		if(Stop_Timeout==0)kotel.mode=0; // Go to full stop
		break;
	case 1:
	case 2:
	case 3:
	case 4:
		Stop_Timeout=STOP_TIMEOUT;
		kotel.smoke_out=kotel.p[kotel.fuel][kotel.mode-1].smoke_speed;
		kotel.smoke_out *= 10;
		// Fan
		for(i=0;i<2;i++)
		{
			if(kotel.fan_out[i]==0)
			{
				if(kotel.p[kotel.fuel][kotel.mode-1].fan_on[i]!=0)
				if(fan_off[i]==0)
				{
					fan_on[i]=kotel.p[kotel.fuel][kotel.mode-1].fan_on[i];
					kotel.fan_out[i]=kotel.p[kotel.fuel][kotel.mode-1].fan_speed[i];
					kotel.fan_out[i] *= 10;
				}
			}
			else
			{
				kotel.fan_out[i]=kotel.p[kotel.fuel][kotel.mode-1].fan_speed[i];
				kotel.fan_out[i] *= 10;
				
				if(kotel.p[kotel.fuel][kotel.mode-1].fan_off[i]!=0)
				if(fan_on[i]==0)
				{
					fan_off[i]=kotel.p[kotel.fuel][kotel.mode-1].fan_off[i];
					kotel.fan_out[i]=0;
				}
			}
			if ((kotel.p[kotel.fuel][kotel.mode-1].fan_off[i]==0) &&\
				(kotel.p[kotel.fuel][kotel.mode-1].fan_on[i]==0))				
					kotel.fan_out[i]=0;
		}
		// Shnek
		for(i=0;i<2;i++)
		{
			if(sh_st[i]==0)
			{
				if(sh_off[i]==0)
				{
					sh_on[i]=kotel.p[kotel.fuel][kotel.mode-1].shnek_on[i];
					if(sh_on[i])
					{
						sh_st[i]=1;
						kotel.shnek_out[i]=1;
					}
				}
			}
			else
			{
				if(sh_on[i]==0)
				{
					sh_off[i]=kotel.p[kotel.fuel][kotel.mode-1].shnek_off[i];
					sh_st[i]=0;
					kotel.shnek_out[i]=0;
				}
			}
			if((sh_on[i]==0)||(kotel.p[kotel.fuel][kotel.mode-1].shnek_ena[i]==0))
			{
				sh_st[i]=0;
				kotel.shnek_out[i]=0;
			}
		}
		break;
	}
	// Calculating 3 point servoprivod values
	{
		d=kotel.power-kotel.p3;//NUM_VALVE_STEP
		if(d<0)ud=-d;
		else ud=d;
		if(ud<NUM_VALVE_STEP)d=0;
		if(d!=0)
		{				
			 if(d>0)
				kotel.open=1;
			 else
				kotel.open=0;
			 if(d<0)
				kotel.close=1;				
			 else
				kotel.close=0;				 	
		}
		else
		{
			kotel.open=0;				
			kotel.close=0;				
		}	
	}
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_Temperature()
{
#if MAX_KOTEL_NUMBER
//	if(Params[0]<NUM_PID)
	kotel.t=Params[0];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_Channel()
{
#if MAX_KOTEL_NUMBER
//	if(Params[0]<NUM_PID)
	kotel.channel=Params[0];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_Fuel()
{
#if MAX_KOTEL_NUMBER
//	if(Params[0]<NUM_PID)
	kotel.fuel=Params[0];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_Mode()
{
#if MAX_KOTEL_NUMBER
//	if(Params[0]<NUM_PID)
	kotel.mode=Params[0];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_Power()
{
#if MAX_KOTEL_NUMBER
	kotel.power=Params[0];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_T3Max()
{
#if MAX_KOTEL_NUMBER
	kotel.t3max=Params[0];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_P3()
{
#if MAX_KOTEL_NUMBER
	kotel.p3=Params[0];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_P_Temperature()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  kotel.p[kotel.fuel][Params[0]].t=(s16)Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_P_Fan_On()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  if(Params[1]<2)
	 	 kotel.p[kotel.fuel][Params[0]].fan_on[Params[1]]=Params[2];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_P_Fan_On_0()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  kotel.p[kotel.fuel][Params[0]].fan_on[0]=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_P_Fan_On_1()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  kotel.p[kotel.fuel][Params[0]].fan_on[1]=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_P_Fan_Off()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  if(Params[1]<2)
	 	kotel.p[kotel.fuel][Params[0]].fan_off[Params[1]]=Params[2];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_P_Fan_Off_0()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  kotel.p[kotel.fuel][Params[0]].fan_off[0]=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_P_Fan_Off_1()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  kotel.p[kotel.fuel][Params[0]].fan_off[1]=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_P_Fan_Speed()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  if(Params[1]<2)
	 	 kotel.p[kotel.fuel][Params[0]].fan_speed[Params[1]]=Params[2];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_P_Fan_Speed_0()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  kotel.p[kotel.fuel][Params[0]].fan_speed[0]=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_P_Fan_Speed_1()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  kotel.p[kotel.fuel][Params[0]].fan_speed[1]=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_P_Smoke()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  kotel.p[kotel.fuel][Params[0]].smoke_speed=Params[1];
	if(Params[0]==5)
	  kotel.smoke_speed[kotel.fuel]=Params[1];
	
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_P_Shnek_Ena()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  if(Params[1]<2)
	 	kotel.p[kotel.fuel][Params[0]].shnek_ena[Params[1]]=Params[2];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_P_Shnek_Ena_0()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  kotel.p[kotel.fuel][Params[0]].shnek_ena[0]=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_P_Shnek_Ena_1()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  kotel.p[kotel.fuel][Params[0]].shnek_ena[1]=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_P_Shnek_On()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  if(Params[1]<2)
	 	kotel.p[kotel.fuel][Params[0]].shnek_on[Params[1]]=Params[2];
#endif
}												
//------------------------------------------------------------------------------
void Set_Kotel_P_Shnek_On_0()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  kotel.p[kotel.fuel][Params[0]].shnek_on[0]=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_P_Shnek_On_1()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  kotel.p[kotel.fuel][Params[0]].shnek_on[1]=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_P_Shnek_Off()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  if(Params[1]<2)
	 	 kotel.p[kotel.fuel][Params[0]].shnek_off[Params[1]]=Params[2];
#endif
}												
//------------------------------------------------------------------------------
void Set_Kotel_P_Shnek_Off_0()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  kotel.p[kotel.fuel][Params[0]].shnek_off[0]=Params[1];
#endif
}
//------------------------------------------------------------------------------
void Set_Kotel_P_Shnek_Off_1()
{
#if MAX_KOTEL_NUMBER
	if(Params[0]<4)
	  kotel.p[kotel.fuel][Params[0]].shnek_off[1]=Params[1];
#endif
}
//-----------------------------------------------------------------------------------
void Mod_Show_Kotel()
{
#if MAX_KOTEL_NUMBER
//	u8 j;
//	u16 tmp;
	// Kotel state
	__sprintf_P(outtxt,kotel_dic[0]);	
    // Current mode
	__sprintf_P(outtxt,kotel_dic[1]);			
	ByteToStr(outtxt,&kotel.mode,0);
    // Preset temperature
	__sprintf_P(outtxt,kotel_dic[2]);			
	ShowTemperature(outtxt,&kotel.t);
    // Reference temperature
	__sprintf_P(outtxt,kotel_dic[3]);			
	ByteToStr(outtxt,&kotel.channel,1);__sprintf(outtxt,"]  ");	
    ShowTemperature(outtxt,&io.ainput[kotel.channel]);
    // Fuel
	__sprintf_P(outtxt,kotel_dic[5]);			
	ByteToStr(outtxt,&kotel.fuel,0);	
    // Fan 0
	__sprintf_P(outtxt,kotel_dic[6]);			
	WordToStrSigned(outtxt,&kotel.fan_out[0]);
    // Fan 1
	__sprintf_P(outtxt,kotel_dic[7]);			
	WordToStrSigned(outtxt,&kotel.fan_out[1]);
    // Smoke
	__sprintf_P(outtxt,kotel_dic[8]);			
	WordToStrSigned(outtxt,&kotel.smoke_out);	
    // Shnek 0
	__sprintf_P(outtxt,kotel_dic[9]);			
	ByteToStr(outtxt,&kotel.shnek_out[0],0);	
    // Shnek 1
	__sprintf_P(outtxt,kotel_dic[10]);			
	ByteToStr(outtxt,&kotel.shnek_out[1],0);

	__sprintf_P(outtxt,kotel_dic[25]);			
	ShowPowerShort(outtxt,&kotel.power);					
	__sprintf_P(outtxt,kotel_dic[26]);			
	WordToStr(outtxt,&kotel.t3max,0);
	__sprintf_P(outtxt,kotel_dic[27]);			
	ShowPowerShort(outtxt,&kotel.p3);

	__sprintf_P(outtxt,kotel_dic[23]);			
	ByteToStr(outtxt,&kotel.open,0);
	__sprintf_P(outtxt,kotel_dic[24]);			
	ByteToStr(outtxt,&kotel.close,0);
#endif	
}
//------------------------------------------------------------------------------
void Mod_Show_Kotel_Params()
{
#if MAX_KOTEL_NUMBER

  	u8 mode=Params[0];
	if((mode>0)&&(mode<5))
	{
		// Kotel parameters
		__sprintf_P(outtxt,kotel_dic[11]);	
		ByteToStr(outtxt,&mode,0);
		__sprintf_P(outtxt,kotel_dic[20]);	
		ByteToStr(outtxt,&kotel.fuel,0);
		// Temperature
		__sprintf_P(outtxt,kotel_dic[2]);			
		ShowTemperature(outtxt,&kotel.p[kotel.fuel][mode].t);
		// Smoke
		__sprintf_P(outtxt,kotel_dic[14]);			
		ByteToStr(outtxt,&kotel.p[kotel.fuel][mode].smoke_speed,0);
		//--------------------------------------------------------------------------
		// Record 0
		__sprintf_P(outtxt,kotel_dic[21]);
		// Fan speed
		__sprintf_P(outtxt,kotel_dic[13]);			
		ByteToStr(outtxt,&kotel.p[kotel.fuel][mode].fan_speed[0],0);
		// Fan on
		__sprintf_P(outtxt,kotel_dic[15]);			
		ByteToStr(outtxt,&kotel.p[kotel.fuel][mode].fan_on[0],0);
		// Fan off
		__sprintf_P(outtxt,kotel_dic[16]);			
		ByteToStr(outtxt,&kotel.p[kotel.fuel][mode].fan_off[0],0);
		// Shnek ena
		__sprintf_P(outtxt,kotel_dic[17]);			
		ByteToStr(outtxt,&kotel.p[kotel.fuel][mode].shnek_ena[0],0);
		// Shnek on
		__sprintf_P(outtxt,kotel_dic[18]);			
		ByteToStr(outtxt,&kotel.p[kotel.fuel][mode].shnek_on[0],0);
		// Shnek off
		__sprintf_P(outtxt,kotel_dic[19]);			
		ByteToStr(outtxt,&kotel.p[kotel.fuel][mode].shnek_off[0],0);
		//--------------------------------------------------------------------------
		// Record 1
		__sprintf_P(outtxt,kotel_dic[22]);
		// Fan speed
		__sprintf_P(outtxt,kotel_dic[13]);			
		ByteToStr(outtxt,&kotel.p[kotel.fuel][mode].fan_speed[1],0);
		// Fan on
		__sprintf_P(outtxt,kotel_dic[15]);			
		ByteToStr(outtxt,&kotel.p[kotel.fuel][mode].fan_on[1],0);
		// Fan off
		__sprintf_P(outtxt,kotel_dic[16]);			
		ByteToStr(outtxt,&kotel.p[kotel.fuel][mode].fan_off[1],0);
		// Shnek ena
		__sprintf_P(outtxt,kotel_dic[17]);			
		ByteToStr(outtxt,&kotel.p[kotel.fuel][mode].shnek_ena[1],0);
		// Shnek on
		__sprintf_P(outtxt,kotel_dic[18]);			
		ByteToStr(outtxt,&kotel.p[kotel.fuel][mode].shnek_on[1],0);
		// Shnek off
		__sprintf_P(outtxt,kotel_dic[19]);			
		ByteToStr(outtxt,&kotel.p[kotel.fuel][mode].shnek_off[1],0);
	}
	if((mode==5))
	{
		// Kotel parameters
		__sprintf_P(outtxt,kotel_dic[11]);	
		ByteToStr(outtxt,&mode,0);
		__sprintf_P(outtxt,kotel_dic[20]);	
		ByteToStr(outtxt,&kotel.fuel,0);
		// Smoke
		__sprintf_P(outtxt,kotel_dic[14]);			
		ByteToStr(outtxt,&kotel.smoke_speed[kotel.fuel],0);
	}
#endif
}
//------------------------------------------------------------------------------
