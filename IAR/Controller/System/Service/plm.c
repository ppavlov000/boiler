#include "..\main.h"
//-----------------------------------------------------------------------------------
//u8 UControl0=0;
u8 UControl1=0;
extern s16 adc_real_result[NUM_AIN_REAL];
//extern TFanLines FanLines[MAX_FANCOIL_NUMBER];
//-----------------------------------------------------------------------------------
in_flash u8	Monthes_Name[12][10]=
{
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December",												
};
in_flash u8	Monthes_Name_Short[12][5]=
{
	"Jan",
	"Feb",
	"Mar",
	"Apr",
	"May",
	"Jun",
	"Jul",
	"Aug",
	"Sep",
	"Oct",
	"Nov",
	"Dec",												
};
in_flash u8	DaysOfWeek[7][10]=
{
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday",
	"Sunday",
};
in_flash u8	DaysOfWeek_Short[7][5]=
{
	"Mond",
	"Tues",
	"Wedn",
	"Thur",
	"Frid",
	"Satu",
	"Sund",
};
//------------------------------------------------------------------------------
// Russian language
in_flash u8	Monthes_Name_rus[12][10]=
{
	"Январь",
	"Февраль",
	"Март",
	"Апрель",
	"Май",
	"Июнь",
	"Июль",
	"Август",
	"Сентябрь",
	"Октябрь",
	"Ноябрь",
	"Декабрь",												
};
in_flash u8	Monthes_Name_Short_rus[12][5]=
{
	"Янв",
	"Фев",
	"Мар",
	"Апр",
	"Май",
	"Июн",
	"Июл",
	"Авг",
	"Сен",
	"Окт",
	"Ноб",
	"Дек",												
};
in_flash u8	DaysOfWeek_rus[7][13]=
{
	"Понедельник",
	"Вторник",
	"Среда",
	"Четверг",
	"Пятница",
	"Суббота",
	"Воскресенье",
};
in_flash u8	DaysOfWeek_Short_rus[7][5]=
{
	"Пон",
	"Втор",
	"Сред",
	"Четв",
	"Пятн",
	"Субб",
	"Воск",
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
in_flash u8	pdic[][80]=
{
	"\n\r Resetting...",					//0
	"\n\r Parameters stored ",				//1
	"\n\r Test...\n\r",						//2
	"\n\r Current state ",					//3
	"\n\r   Controller configuration",		//4	
	"\n\r     Digital inputs  \n\r       ",	//5		
	"\n\r     Digital outputs  \n\r       ",//6		
	"\n\r     Analog inputs  \n\r       ",	//7		
	"\n\r     Analog outputs  \n\r       ",	//8		
	"\n\r   Temperature settings",			//9		
	"\n\r     Desired temperature ",		//10		
	"\n\r     Mode of operation ",			//11		
	"\n\r   Program  ",		  				//12		
	"RUN",									//13
	"STOPED",								//14
	"\n\r   Pid settings",					//15
	"\n\r     Desired temperature ",		//16
	"\n\r     Mode of operation ",			//17
	"\n\r     Temperature channel AI[",		//18
	"\n\r     Prop cofficient     ",		//19
	"\n\r     Diff cofficient     ",		//20
	"\n\r     Integral cofficient ",		//21
	"\n\r     Integration time    ",		//22						
	"\n\r Ready for downloading program image...",	//23						
	"\n\r Download is successful complete...",		//24						
	"\n\r Download error!",							//25						
	"\n\r No valid user program found\n\r Download new bin please ...",		//26						
	"\n\r User program image corrupted\n\r Download new bin please...",		//27						
	"\n\r User program CRC OK. Loading...\n\r Name:  ",		//28						
	"\n\r     Min power ",						//29
	"\n\r     Max power ",						//30
	"\n\r     Power     ",						//31
	"\n\r Power supply voltage ",				//32
	"\n\r     Servoprivod full cycle time c ",	//33
	"\n\r     3 points server power ",			//34
	"\n\r     Open  line ",					//35
	"\n\r     Close line ",					//36		
	"\n\r     Current temperature ",		//37
	"\n\r Bad command",						//38	
	"\n\r     Slow speed ",					//39
	"\n\r     Fast speed ",					//40			
	"\n\r",									//41		
	"\n\r Season ",							//42		
	"Summer",								//43		
	"Winter",								//44	
	"\n\r Controller ID ",					//45	
	"\n\r     Zero power border ",			//46
	"\n\r     Low  power border ",			//47		
	"\n\r   In_Params",						//48
	"\n\r    ",								//49
	"\n\r   Regs ",							//50
	"\n\r   Timers ",						//51
	"\n\r   Out_Params ",					//52	
	"\n\r     Heat/Cooling ",				//53				
	"Heating",								//54
	"Cooling",								//55				
//	txt,		//33
};
//-----------------------------------------------------------------------------------
in_flash u8	pseason[11][40]=
{
	"\n\r Season parameters",			//0
	"\n\r   Season:                 ",  //1		
	"\n\r   Mode  :                 ",	//2		
	"\n\r   Temperature mode        ",	//3		
	"\n\r   Date mode               ",	//4		
	"\n\r   Preset Temperature      ",	//5		
	"\n\r   Current Temperature     ",	//6		
	"Auto",								//7
	"Manual",							//8		
	"\n\r   Summer                  ",	//9		
	"\n\r   Winter                  ",	//10			

};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void Mod_Store_Parameters()
{
	params_store();
	__sprintf_P(outtxt,pdic[1]);	
}
//-----------------------------------------------------------------------------------
void Mod_Test()
{
//	u8	tmp;
//	pid_handle();
//	__sprintf_P(outtxt,pdic[2]);		
//	Production_Test();
	extern u32 HW_in;
	extern u32 HW;
	BuzzerTime=100;
//	LongToStr(outtxt,&HW,1);	
//	__sprintf(outtxt," ");
//	LongToStr(outtxt,&HW_in,1);
//	__sprintf(outtxt,"\n\r");
	
//	fram_mem_enable();
//	fram_mem_write(PARAM_LOCATION_0+TPARAM_WIDTH-2,(u8*)&HW,2);
//	fram_mem_disable();		
	
}
//-----------------------------------------------------------------------------------
u8 Monthes[12]={31,28,31,30,31,30,31,31,30,31,30,31};
//2008.01.01 - 2 (вторник)
u8 get_day_of_week(TCTime *time)
{
	u8 year_rem;
	u32 date=0,tmp;
	u16 j;
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
		for(j=8;j<time->field.Year;j++)
		{
			date+=365;
			year_rem=j & 0x03;
			if(year_rem==0)
				date++;
		}
	tmp=date/7;
	tmp=date-(tmp*7);
	tmp+=1;
	if(tmp>7)tmp-=7;	
	time->field.Day=tmp;
	return tmp;
}
//-----------------------------------------------------------------------------------
void Mod_Show_Full_Time(TCTime *time)
{
	TCTime ft;
	ft=*time;
//	u8 tmp;
//	fram_get_time();
/*	
	__sprintf(outtxt,"\n\r Date ");
	ByteToStr(outtxt,&ft.field.Date,0);__sprintf(outtxt,".");
	ByteToStr(outtxt,&ft.field.Month,0);__sprintf(outtxt,".");
	ByteToStr(outtxt,&ft.field.Year,0);
*/	
	__sprintf(outtxt,"\n\r ");
	ByteToStrFillZero(outtxt,&ft.field.Date,0,2,'0');
	__sprintf(outtxt," ");
	__sprintf_P(outtxt,Monthes_Name[ft.field.Month-1]);
	__sprintf(outtxt," 20");
	ByteToStrFillZero(outtxt,&ft.field.Year,0,2,'0');
	__sprintf(outtxt,", ");
	__sprintf_P(outtxt,DaysOfWeek	[get_day_of_week(&ft)-1]);	
				
	__sprintf(outtxt," Time ");
	ByteToStrFillZero(outtxt,&ft.field.Hour,0,2,'0');__sprintf(outtxt,".");
	ByteToStrFillZero(outtxt,&ft.field.Minute,0,2,'0');__sprintf(outtxt,".");
	ByteToStrFillZero(outtxt,&ft.field.Second,0,2,'0');
}
//-----------------------------------------------------------------------------------
void Mod_Show_Status_IO()
{
	s16 wtmp;
	u8 j;
	u16 t;
	Mod_Show_Full_Time(&MenuRegs.Time);
	__sprintf_P(outtxt,pdic[45]);ByteToStr(outtxt,&ID,0);	
//	Mod_Show_Full_Time(&MenuRegs.Time_Summ);
//	Mod_Show_Full_Time(&MenuRegs.Time_Wint);
//	__sprintf_P(outtxt,pdic[32]);ShowTemperatureShort(outtxt,&input_voltage);__sprintf(outtxt,"V");
	__sprintf_P(outtxt,pdic[42]);
	if(MenuRegs.Season.season==SEASON_SUMMER)__sprintf_P(outtxt,pdic[43]);
	else __sprintf_P(outtxt,pdic[44]);	
	__sprintf_P(outtxt,pdic[3]);
	// IO state
	__sprintf_P(outtxt,pdic[4]);	
	__sprintf_P(outtxt,pdic[5]);		
	for(j=0;j<NUM_DIN;j++)
	{
		t=1<<j;			
		if(io.din & t) __sprintf(outtxt,"1 ");
		else __sprintf(outtxt,"0 ");
	}
	__sprintf_P(outtxt,pdic[6]);
	for(j=0;j<NUM_DOUT;j++)
	{
		t=1<<j;			
		if(io.dout & t) __sprintf(outtxt,"1 ");
		else __sprintf(outtxt,"0 ");
	}
	__sprintf_P(outtxt,pdic[7]);	
	for(j=0;j<NUM_AIN;j++)
	{
		wtmp=io.ainput[j];
		ShowTemperature(outtxt,&wtmp);				
		__sprintf(outtxt," "); 			
	}
	// Real AI
/*
	__sprintf_P(outtxt,pdic[7]);	
	for(j=0;j<NUM_AIN;j++)
	{
		wtmp=adc_real_result[j];
		ShowTemperature(outtxt,&wtmp);				
		__sprintf(outtxt," "); 			
	}
*/	
	__sprintf_P(outtxt,pdic[8]);	
	for(j=0;j<NUM_AOUT;j++)
	{
		ShowPowerShort(outtxt,(s16*)&io.aoutput[j]);
		__sprintf(outtxt," "); 			
	}
}
//-----------------------------------------------------------------------------------

void Mod_Show_Status_Prog()
{
//	u16 wtmp;
	u8 j;
//	u16 t;
	// Program state
	__sprintf_P(outtxt,pdic[12]);		
	if(intr.status==int_Run)
		__sprintf_P(outtxt,pdic[13]);		
	if(intr.status==int_Stop)
		__sprintf_P(outtxt,pdic[14]);	
	
//	intr.in_params[0]=0x1234;
//	intr.in_params[1]=0xffff;
//	intr.in_params[2]=0x9876;	
	__sprintf_P(outtxt,pdic[48]);		
	for(j=0;j<PARAMETERS_MAX;j++)
	{
		if((j & 0x07)==0x00)__sprintf_P(outtxt,pdic[49]);		
		IntToStrFillZero(outtxt,(u32*)&intr.in_params[j],0,5,5,1);		
		__sprintf(outtxt," ");
	}	

	__sprintf_P(outtxt,pdic[52]);		
	for(j=0;j<PARAMETERS_MAX;j++)
	{
		if((j & 0x07)==0x00)__sprintf_P(outtxt,pdic[49]);		
		IntToStrFillZero(outtxt,(u32*)&intr.out_params[j],0,5,5,1);		
		__sprintf(outtxt," ");
	}	

	__sprintf_P(outtxt,pdic[50]);
	for(j=0;j<REGISTERS_MAX;j++)
	{
		if((j & 0x07)==0x00)__sprintf_P(outtxt,pdic[49]);				
		IntToStrFillZero(outtxt,(u32*)&intr.reg[j],1,8,3,0);	
		__sprintf(outtxt," "); 			
	}	
	__sprintf_P(outtxt,pdic[51]);
	for(j=0;j<TIMERS_MAX;j++)
	{
		if((j & 0x07)==0x00)__sprintf_P(outtxt,pdic[49]);						
		IntToStrFillZero(outtxt,(u32*)&intr.t32[j],1,8,3,0);			
		__sprintf(outtxt," "); 			
	}		
}
//-----------------------------------------------------------------------------------
void Mod_Show_Errors()
{
//	u16 wtmp;
	u8 j,tmp;
//	u16 t;
	// Preset state
//	__sprintf_P(outtxt,pdic[9]);		
//	__sprintf_P(outtxt,pdic[10]);		
//	ShowTemperature(outtxt,&MenuRegs.t0);
//	__sprintf_P(outtxt,pdic[11]);		
//	switch(MenuRegs.mode_of_controller)
//	{
//		case 0:__sprintf(outtxt,"Auto");break;
//		case 1:__sprintf(outtxt,"Summer");break;
//		case 2:__sprintf(outtxt,"Winter");break;				
//	}	
	__sprintf(outtxt,"\n\r  Errors");
	for(j=0;j<MAX_ERRORS_NUM;j++)
	{
		if(errors.item[j].code!=0)
		{
			__sprintf(outtxt,"\n\r    ");ByteToStr(outtxt,&j,0);__sprintf(outtxt,". ");
			__sprintf(outtxt,"Code=");
			tmp=errors.item[j].code>>8;ByteToStrFillZero(outtxt,&tmp,1,2,'0');
			tmp=errors.item[j].code;ByteToStrFillZero(outtxt,&tmp,1,2,'0');
			__sprintf(outtxt," ");
			ByteToStrFillZero(outtxt,&errors.item[j].time.field.Date,0,2,'0');__sprintf(outtxt,"th ");
			__sprintf_P(outtxt,Monthes_Name_Short[errors.item[j].time.field.Month-1]);
			__sprintf(outtxt," 20");
			ByteToStrFillZero(outtxt,&errors.item[j].time.field.Year,0,2,'0');
			__sprintf(outtxt," ");
			ByteToStrFillZero(outtxt,&errors.item[j].time.field.Hour,0,2,'0');__sprintf(outtxt,":");
			ByteToStrFillZero(outtxt,&errors.item[j].time.field.Minute,0,2,'0');__sprintf(outtxt,":");
			ByteToStrFillZero(outtxt,&errors.item[j].time.field.Second,0,2,'0');
		}
	}
}
//-----------------------------------------------------------------------------------
void Mod_Show_Status()
{
	Mod_Show_Status_IO();
//	Mod_Show_Status_Prog();
//	Mod_Show_Status_PID(0);
}
//-----------------------------------------------------------------------------------
void Set_Desired_Temperature()
{	
//	MenuRegs.t0=(s16)Params[0];
}
//-----------------------------------------------------------------------------------
void Set_Point()
{	
	f32 ftmp0;
	f32 ftmp1;	
	f32 ftmp2;	
//	s16 tmp;	
	u8 i;	
	// Make point 1 calculations
	if((Params[0]==0)||(Params[0]==1))
	{
		point_reference_temperature[(u8)Params[0]]=(s16)Params[1];
		__sprintf(outtxt,"\n\r Reference temperature");ShowTemperature(outtxt,&point_reference_temperature[(u8)Params[0]]);			
		__sprintf(outtxt,"\n\r Real temperatures");
		__sprintf(outtxt,"\n\r   ");	
		adc_set_channel(0);
		for(i=0;i<NUM_AIN_REAL;i++)	
		{
			Delay(100);
			adc_conversion();
			point_real_temperature[(u8)Params[0]][i]=ad_res;
			adc_set_channel(i+1);	
			ShowTemperature(outtxt,&point_real_temperature[(u8)Params[0]][i]);__sprintf(outtxt,"  ");			
		}
	}
	// Make point 2 calculations >  cofficients + offsets
	if((Params[0]==1))
	{
//		__sprintf(outtxt,"\n\r Coffs and offsets");
//		__sprintf(outtxt,"\n\r   ");		
		ftmp1=point_reference_temperature[1]-point_reference_temperature[0];
		for(i=0;i<NUM_AIN_REAL;i++)	
		{
			ftmp0=point_real_temperature[1][i]-point_real_temperature[0][i];
			if(ftmp0<1)ftmp0=1;
			ftmp2=ftmp1/ftmp0;
			io.ai_coff[i]=ftmp2;
			
//			point_real_temperature[0][i]=(f32)ad_res*io.ai_coff[i];			
//			point_real_temperature[0][i]=point_real_temperature[0][i]*io.ai_coff[i];			
//			io.ai_offset[i]=point_reference_temperature[0]-point_real_temperature[0][i];
//			io.ai_offset[i]=0;
//			io.ai_offset[i]=point_reference_temperature[0]-point_real_temperature[0][i];			
//			ShowTemperature(outtxt,&io.ai_offset[i]);					
		}
	}
	// Make point 2 calculations >  offsets (optional)
	if((Params[0]==2))
	{
		point_reference_temperature[0]=(s16)Params[1];
		__sprintf(outtxt,"\n\r Reference temperature");ShowTemperature(outtxt,&point_reference_temperature[0]);			
		__sprintf(outtxt,"\n\r Real temperatures");
		__sprintf(outtxt,"\n\r   ");			
		adc_set_channel(0);		
		for(i=0;i<NUM_AIN_REAL;i++)	
		{
			Delay(100);
			adc_conversion();
			point_real_temperature[0][i]=(f32)ad_res*io.ai_coff[i];
			adc_set_channel(i+1);	
			ShowTemperature(outtxt,&point_real_temperature[0][i]);__sprintf(outtxt,"  ");		
		}
		for(i=0;i<NUM_AIN_REAL;i++)	
		{
			io.ai_offset[i]=point_reference_temperature[0]-point_real_temperature[0][i];			
		}
		__sprintf(outtxt,"\n\r Offsets");
		__sprintf(outtxt,"\n\r   ");	
		for(i=0;i<NUM_AIN_REAL;i++)	
		{
			ShowTemperature(outtxt,&io.ai_offset[i]);__sprintf(outtxt,"  ");	
		}			
	}
}
//-----------------------------------------------------------------------------------
void Relay_Off()
{
//	Other.relay[Params[0]]=0;
//	io_relay_set();
}
//-----------------------------------------------------------------------------------
void IO_On()
{	
//	Vacuum.io=1;
	io_io_set();
}
//-----------------------------------------------------------------------------------
void IO_Off()
{
//	Vacuum.io=0;
	io_io_set();
}
//-----------------------------------------------------------------------------------
void Set_AI_10V()
{
//	Vacuum.analog=Params[0];
//	io_analog_set();
	if(Params[0]>=NUM_AIN_REAL)
	{
		__sprintf_P(outtxt,pdic[38]);	
		return;
	}
	io.ai_coff[Params[0]]=1;
	io.ai_offset[Params[0]]=0;	
}
//-----------------------------------------------------------------------------------
void Set_Date()
{
//	fram_set_time(u8 hour,u8 minute,u8 second)
//	fram_set_date(u8 year,u8 month, u8 date,u8 day)	
	fram_set_date((u8)Params[2],(u8)Params[1],(u8)Params[0],1);
}
//-----------------------------------------------------------------------------------
void Set_Time()
{
//	Vacuum.analog=Params[0];
	fram_set_time((u8)Params[0],(u8)Params[1],(u8)Params[2]);
}
//-----------------------------------------------------------------------------------
void Set_Password_On()
{
	MenuRegs.password=1;
	Time_To_Store=3;
}
//-----------------------------------------------------------------------------------
void Set_Password_Off()
{
	MenuRegs.password=0;
	Time_To_Store=3;
}
//-----------------------------------------------------------------------------------
void Set_Password_User()
{
	u32 tmp1,tmp2;
	u8 res;
	u8 i;
	tmp1=tmp2=Params[0];
	for(i=0;i<5;i++)
	{
		tmp1/=10;
		tmp1*=10;
		res=tmp2-tmp1;
		MenuRegs.pass_user[4-i]=res;
		tmp1/=10;
		tmp2=tmp1;
	}
	Time_To_Store=3;
}
//-----------------------------------------------------------------------------------
void Set_Password_Admin()
{
	u32 tmp1,tmp2;
	u8 res;
	u8 i;
	tmp1=tmp2=Params[0];
	for(i=0;i<5;i++)
	{
		tmp1/=10;
		tmp1*=10;
		res=tmp2-tmp1;
		MenuRegs.pass_admin[4-i]=res;
		tmp1/=10;
		tmp2=tmp1;
	}
	Time_To_Store=3;
}
//-----------------------------------------------------------------------------------
void Mod_Console_Toggle()
{
	console_mode=0;
}
//-----------------------------------------------------------------------------------
void Prog_Download()
{
//	u16 CRC;
	Program_Valid=0;
	__sprintf_P(outtxt,pdic[23]);			
	Fram_Addr=CODE_ADDR;
	Xmodem_Start();
	ctmp=XMOD_None;
	while(ctmp==XMOD_None)
	{
		ctmp=Xmodem_Processor();
	}
	if(ctmp==XMOD_Ok)
	{
		__sprintf_P(outtxt,pdic[24]);
		// Check program CRC
		Prog_Check();
		Intr_IRQ0_Start();// Make IO initialisation
	}
	else
		__sprintf_P(outtxt,pdic[25]);
}
//-----------------------------------------------------------------------------------
void Set_ID()
{
	if((Params[0]!=0)&&(Params[0]<16))
	{
		ID=Params[0];
		id_store();
	}
	else
		__sprintf(outtxt,"\n\r Wrong ID value");
}
//-----------------------------------------------------------------------------------
void Prog_Check()
{
	u16 CRC;
	Program_Valid=0;
	// Check program CRC
	wtmp=CheckCRC(1,0);
	FGet(HPLM_FLASH_START+CRC_H_LOC,(u8*)&CRC,2);		
	if(CRC!=wtmp)
		__sprintf_P(outtxt,pdic[26]);		
	else
	{
		wtmp=CheckCRC(2,0);
		FGet(HPLM_FLASH_START+CRC_D_LOC,(u8*)&CRC,2);	
		if(CRC!=wtmp)
			__sprintf_P(outtxt,pdic[27]);			
		else
		{
			__sprintf_P(outtxt,pdic[28]);
			FGet(HPLM_FLASH_START,outtxt,TNAME_WIDTH);
			Program_Valid=1;
		}
		
	}
}
//-----------------------------------------------------------------------------------
void Mod_Show_Season()
{
//	u16 tmp;
//	s32 tmp;
	// PID state
	__sprintf_P(outtxt,pseason[0]);			

	__sprintf_P(outtxt,pseason[1]);	
	if(MenuRegs.Season.season==SEASON_SUMMER)__sprintf_P(outtxt,pdic[43]);
	else __sprintf_P(outtxt,pdic[44]);	

	__sprintf_P(outtxt,pseason[2]);	
	if(MenuRegs.Season.mode==SEASON_AUTO)__sprintf_P(outtxt,pseason[7]);
	else __sprintf_P(outtxt,pseason[8]);	
	
	__sprintf_P(outtxt,pseason[3]);	
	ByteToStr(outtxt,&MenuRegs.Season.switch_temperature,0);

	__sprintf_P(outtxt,pseason[4]);	
	ByteToStr(outtxt,&MenuRegs.Season.switch_date,0);
	
	__sprintf_P(outtxt,pseason[5]);				
	ShowTemperature(outtxt,&MenuRegs.Season.t);				

	__sprintf_P(outtxt,pseason[6]);				
	ShowTemperature(outtxt,&io.ainput[MenuRegs.Season.t_extern_channel]);				
	
	__sprintf_P(outtxt,pseason[9]);	
	ByteToStr(outtxt,&MenuRegs.Season.date[0].field.Date,0);
	__sprintf(outtxt,"/");	
	ByteToStr(outtxt,&MenuRegs.Season.date[0].field.Month,0);

	__sprintf_P(outtxt,pseason[10]);	
	ByteToStr(outtxt,&MenuRegs.Season.date[1].field.Date,0);
	__sprintf(outtxt,"/");	
	ByteToStr(outtxt,&MenuRegs.Season.date[1].field.Month,0);
	
}
//-----------------------------------------------------------------------------------
void params_set_default();
//-----------------------------------------------------------------------------------
void Params_Init()
{
	params_set_default();
	params_store();
}
//-----------------------------------------------------------------------------------
