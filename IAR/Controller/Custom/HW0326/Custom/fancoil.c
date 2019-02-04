#include "..\..\..\System\main.h"
//-----------------------------------------------------------------------------------
__farflash u8	fancoil_dic[33][40]=
{
	"\n\r   Fancoil configuration",		//0
	"\n\r     Center temperature     ",	//1		
	"\n\r     Temperature step       ", //2		
	"\n\r     T Low                  ",	//3		
	"\n\r     T Medium               ",	//4		
	"\n\r     T High                 ",	//5		
	"\n\r     T Hysteresis           ",	//6		
	"\n\r     T Emeregency           ",	//7		
	"\n\r     Fancoil switching time ",	//8		
	"\n\r     Valve switching time   ",	//9		
	"\n\r     Current temperature    ",	//10
	"\n\r     Emergency temperature ",	//11	
	
	"\n\r   Fancoil state",				//12
	"\n\r     Fan mode               ",	//13	
	"\n\r     Fan state              ",	//14
	"\n\r     Valve state            ",	//15	
	"Heating",							//16			
	"Cooling",							//17		
	"Off",								//18		
	"Auto",								//19	
	"Manual",							//20		
	"\n\r     Preset temperature     ",	//21	
	"\n\r     Preset temperature     ",	//22
	"\n\r     Difference             ",	//23
	"\n\r     Valve transfer time    ",	//24	
	"\n\r     Valve Hysteresis       ",	//25		
	"\n\r     Day/Night:             ",	//26		
	"Day",								//27
	"Night",							//28	
	"\n\r     Fan speed ",				//29
	"\n\r     Valve pos ",				//30		
	"\n\r     Temperature AI[",			//31
	"\n\r     Difference             ", //32	
};

u8 auto_protection=0;
u8 Valve_Old_State=0;
u8 Valve_Old[2]={0,0};
s16 Old_Difference=0;
u8 Polarity;
s16 Hysteresis_2;
u32 valve_lines[2]={0,0};
u8 Fan_Switch_Enable[MAX_FANCOIL_NUMBER];
u8 Valve_Switch_Enable[MAX_FANCOIL_NUMBER];
u8 Valve_Transfer_Enable[MAX_FANCOIL_NUMBER];

TFanLines FanLines[MAX_FANCOIL_NUMBER];
//-----------------------------------------------------------------------------------
void Fancoil_Set_VHyst()
{
	if(Params[0]>=MAX_FANCOIL_NUMBER)return;
	fan[Params[0]].Valve_Hysteresis=Params[1];
}
//-----------------------------------------------------------------------------------
void Fancoil_Set_VTime_1()
{
	if(Params[0]>=MAX_FANCOIL_NUMBER)return;	
	fan[Params[0]].Valve_Time_1=Params[1];
}
//-----------------------------------------------------------------------------------
void Fancoil_Set_VTime_2()
{
	if(Params[0]>=MAX_FANCOIL_NUMBER)return;
	fan[Params[0]].Valve_Time_2=Params[1];
}
//-----------------------------------------------------------------------------------
void Fancoil_Set_FTime()
{
	if(Params[0]>=MAX_FANCOIL_NUMBER)return;
	fan[Params[0]].Fan_Time=Params[1];
}
//-----------------------------------------------------------------------------------
void Fancoil_Set_TDelta()
{
	if(Params[0]>=MAX_FANCOIL_NUMBER)return;
	fan[Params[0]].Hysteresis=Params[1];
}
//-----------------------------------------------------------------------------------
void Fancoil_Set_THigh()
{
	if(Params[0]>=MAX_FANCOIL_NUMBER)return;
	fan[Params[0]].THigh=Params[1];
}
//-----------------------------------------------------------------------------------
void Fancoil_Set_TMedium()
{
	if(Params[0]>=MAX_FANCOIL_NUMBER)return;
	fan[Params[0]].TMedium=Params[1];
}
//-----------------------------------------------------------------------------------
void Fancoil_Set_TLow()
{
	if(Params[0]>=MAX_FANCOIL_NUMBER)return;
	fan[Params[0]].TLow=Params[1];
}
//-----------------------------------------------------------------------------------
void Fancoil_Set_T()
{
	if(Params[0]>=MAX_FANCOIL_NUMBER)return;
	fan[Params[0]].T=Params[1];
}
//-----------------------------------------------------------------------------------
void Mod_Show_FAN()
{
//	u8 j;
//	u16 t;
	s16 diff;	
//	f32 ftmp;
	
	if(Params[0]>=MAX_FANCOIL_NUMBER)return;
//	Mod_Show_Full_Time();
	
//	fan_temperature=CV.fan[0].Temperature;
	// Current state
//	__sprintf_P(outtxt,fancoil_dic[26]);ByteToStr(outtxt,(u8*)&Params[0],0);
	__sprintf_P(outtxt,fancoil_dic[12]);
	__sprintf_P(outtxt,fancoil_dic[26]);if(fan[Params[0]].Day_Night==fan_Day)__sprintf_P(outtxt,fancoil_dic[27]);else __sprintf_P(outtxt,fancoil_dic[28]);			
	__sprintf_P(outtxt,fancoil_dic[22]);ShowTemperature(outtxt,&fan[Params[0]].T);
	
	__sprintf_P(outtxt,fancoil_dic[31]);ByteToStr(outtxt,&fan[Params[0]].Channel,1);__sprintf(outtxt,"]     ");	
	ShowTemperature(outtxt,&io.ainput[fan[Params[0]].Channel]);	
	diff=io.ainput[fan[Params[0]].Channel]-fan[Params[0]].T;
	if(diff<0)diff=-diff;
	__sprintf_P(outtxt,fancoil_dic[32]);ShowTemperature(outtxt,&diff);
	
//	__sprintf_P(outtxt,fancoil_dic[21]);ShowTemperature(outtxt,&Map.field.Static.TDesired);		
//	__sprintf_P(outtxt,fancoil_dic[23]);ShowTemperature(outtxt,&Map.field.Static.TDifference);			
	__sprintf_P(outtxt,fancoil_dic[13]);if(fan[Params[0]].Fan_Mode==0)__sprintf_P(outtxt,fancoil_dic[19]);else __sprintf_P(outtxt,fancoil_dic[20]);	
	__sprintf_P(outtxt,fancoil_dic[14]);ByteToStr(outtxt,&fan[Params[0]].Fan_Lvl,0);
	__sprintf_P(outtxt,fancoil_dic[15]);
	if(fan[Params[0]].Valve==0)__sprintf_P(outtxt,fancoil_dic[18]);
	if(fan[Params[0]].Valve==1)__sprintf_P(outtxt,fancoil_dic[16]);
	if(fan[Params[0]].Valve==2)__sprintf_P(outtxt,fancoil_dic[17]);	
	// Parameters
	__sprintf_P(outtxt,fancoil_dic[0]);
//	__sprintf_P(outtxt,fancoil_dic[1]);ShowTemperature(outtxt,&fan[Params[0]].Center);
//	__sprintf_P(outtxt,fancoil_dic[2]);ShowTemperature(outtxt,&fan[Params[0]].Step);
	__sprintf_P(outtxt,fancoil_dic[3]);ShowTemperature(outtxt,&fan[Params[0]].TLow);
	__sprintf_P(outtxt,fancoil_dic[4]);ShowTemperature(outtxt,&fan[Params[0]].TMedium);
	__sprintf_P(outtxt,fancoil_dic[5]);ShowTemperature(outtxt,&fan[Params[0]].THigh);
	__sprintf_P(outtxt,fancoil_dic[6]);ShowTemperature(outtxt,&fan[Params[0]].Hysteresis);
//	__sprintf_P(outtxt,fancoil_dic[7]);ShowTemperature(outtxt,&fan[Params[0]].TEmeregency);						
	__sprintf_P(outtxt,fancoil_dic[8]);WordToStr(outtxt,&fan[Params[0]].Fan_Time,0);
	__sprintf_P(outtxt,fancoil_dic[9]);WordToStr(outtxt,&fan[Params[0]].Valve_Time_1,0);
	__sprintf_P(outtxt,fancoil_dic[24]);WordToStr(outtxt,&fan[Params[0]].Valve_Time_2,0);
	__sprintf_P(outtxt,fancoil_dic[25]);ShowTemperature(outtxt,&fan[Params[0]].Valve_Hysteresis);		
//	__sprintf_P(outtxt,fancoil_dic[10]);ShowTemperature(outtxt,&io.ainput[0]);
//	__sprintf_P(outtxt,fancoil_dic[11]);ShowTemperature(outtxt,&io.ainput[1]);						
	__sprintf_P(outtxt,fancoil_dic[29]);ByteToStr(outtxt,&FanLines[Params[0]].fan_speed,0);
	__sprintf_P(outtxt,fancoil_dic[30]);ByteToStr(outtxt,&FanLines[Params[0]].valve_pos,0);	
}
//-----------------------------------------------------------------------------------
void Fan_Lines_Update(u8 fan_num)
{
	u8 fan_speed=0;

	if(fan[0].Fan_Lvl==0)
		Fan_Switch_Enable[fan_num]=fan[fan_num].Fan_Time;	

	switch(fan[fan_num].Fan_Lvl)
	{
		case 0:
			fan_speed=0x00;
		break;
		case 1:
			fan_speed=0x01;
		break;
		case 2:
			fan_speed=0x02;
		break;
		case 3:
			fan_speed=0x04;
		break;
	}	
	// Need to make changes
	if(FanLines[fan_num].fan_speed!=fan_speed)
	{
		if(FanLines[fan_num].fan_speed==0)
		{
			if(Fan_Switch_Enable[fan_num]==0)						// Timeout is over
			{
				FanLines[fan_num].fan_speed=fan_speed;				// Setup relays
				Fan_Switch_Enable[fan_num]=fan[fan_num].Fan_Time;	// Set up timeout
			}
		}
		else
		{
			FanLines[fan_num].fan_speed=0;
			Fan_Switch_Enable[fan_num]=fan[fan_num].Fan_Time;		// Set up timeout			
		}
	}
	intr.out_params[19]=FanLines[fan_num].fan_speed;
}
//-----------------------------------------------------------------------------------
void Valve_Lines_Update(u8 fan_num)
{
/*
	u32 tmp1,tmp2;
	u8 valve_pos;	
	valve_pos=0;
	switch(fan[fan_num].Valve)
	{
		case 1: valve_pos=0x01; break;
		case 2: valve_pos=0x02; break;				
	}	
	if(valve_pos!=FanLines[fan_num].valve_pos)
	{
		if(valve_lines[0]==0)
		{
			if(tmp1!=valve_lines[1])
				if(Valve_Transfer_Enable[0]==0)
				{
					Map.field.Static.dout&=~(DO_26+DO_27);
					Map.field.Static.dout|=tmp1;
					valve_lines[1]=Map.field.Static.dout & (DO_26+DO_27);
				}
			if(tmp1==valve_lines[1])
				if(Valve_Switch_Enable[0]==0)
				{
					Map.field.Static.dout&=~(DO_26+DO_27);
					Map.field.Static.dout|=tmp1;
					valve_lines[1]=Map.field.Static.dout & (DO_26+DO_27);
				}
		}
		else
		{
			Map.field.Static.dout&=~(DO_26+DO_27);
			Valve_Switch_Enable[0]=Map.field.Static.fp[0].Valve_Time_1;	
			Valve_Transfer_Enable[0]=Map.field.Static.fp[0].Valve_Time_2;				
		}
	}
*/	
}
//-----------------------------------------------------------------------------------
void Fancoil_Temperature_Control()
{
	s16 Diff,Diff2;
	s16 low,med,high;
	u8 fan_lvl;
	if(SysSetUp!=0)	
	{
	
		Fan_Switch_Enable[0]=fan[0].Fan_Time;			// Set up timeout
		Valve_Switch_Enable[0]=fan[0].Valve_Time_1;		// Set up timeout
		Valve_Transfer_Enable[0]=fan[0].Valve_Time_2;	// Set up timeout		
		return;				
	}	
	Diff=io.ainput[fan[0].Channel]-fan[0].T;
	
	if(((Diff>0)&&(Old_Difference<0))||((Diff<0)&&(Old_Difference>0)))
		Polarity=1;
	else
		Polarity=0;	
	Old_Difference=Diff;
	//***************************************************		
	Diff2=Diff;
	if(Diff<0)
	{
		Diff2=-Diff;			 	
		if(MenuRegs.Season.season==SEASON_SUMMER)Diff2=0;
	}
	else
		if(MenuRegs.Season.season==SEASON_WINTER)Diff2=0;

//	if(fan[0].Day_Night==fan_Day)	
	{
		if(fan[0].Fan_Mode==0)
		{		
			switch(fan[0].Fan_Lvl)
			{
				case 0:
					low=fan[0].TLow;
					med=fan[0].TMedium;
					high=fan[0].THigh;				
				break;
				case 1:
//					if(Polarity)
//						low=fan[0].TLow;
//					else
					low=fan[0].TLow-fan[0].Hysteresis;
					med=fan[0].TMedium;
					high=fan[0].THigh;				
				break;
				case 2:
					low=fan[0].TLow-fan[0].Hysteresis;
					med=fan[0].TMedium-fan[0].Hysteresis;
					high=fan[0].THigh;							
				break;						
				case 3:
					low=fan[0].TLow-fan[0].Hysteresis;
					med=fan[0].TMedium-fan[0].Hysteresis;
					high=fan[0].THigh-fan[0].Hysteresis;							
				break;						
			}
			fan_lvl=0;
			// Fancoil fan level processing
			if((Diff2>=low)&&(Diff2<med))
			{
				fan_lvl=1;		
			//	Old_Difference=Diff;
			}
			if((Diff2>=med)&&(Diff2<high))
				fan_lvl=2;		
			if(Diff2>=high)
				fan_lvl=3;		
			fan[0].Fan_Lvl=fan_lvl;					
		}	
		Fan_Lines_Update(0);
	/*	
		// Valve processing
		if(fan[0].Fan_Lvl!=0)
		{
			
			if((Diff>=fan[0].Valve_Hysteresis))
			{
				fan[0].Valve=2;				
			}
			else
			{
				if((Diff<=-fan[0].Valve_Hysteresis))	// Heating
				{
					fan[0].Valve=1;				
				}
				else
				{				
					// Turning off Valve
					if(Diff2<=(fan[0].Valve_Hysteresis/2))
					{
						fan[0].Valve=0;
					}
				}
			}		
		}
		else
		{
			fan[0].Valve=0;;	
		}
		Valve_Lines_Update(0,&fan[0]);	
	*/	
	}
}
//-----------------------------------------------------------------------------------
