#include "..\main.h"
//-----------------------------------------------------------------------------------
#define AIN_MISTAKE 4
//-----------------------------------------------------------------------------------
u8 test_ptr=0;
u8 test_state=0;
//-----------------------------------------------------------------------------------
in_flash u8	tdic[39][80]=
{
	"\n\r Resetting...",						//0
	"\n\r Parameters stored ",					//1
	"\n\r Testing routine...\n\r",				//2
	"\n\r To choose test press UP/DOWN arrows \n\r",						//3
	"\n\r",										//4	
	"\n\r TEST PASSED",							//5		
	"\n\r TEST FAIL",							//6		
	" 5. Real timer test",		//7		
	"\n\r TESTS NOT FINISHED",		//8		
	"\n\r     ",				//9		
	"\n\r  Configurating real time clock",		//10		
	" 6. RS485 test stage ",				//11		
	"\n\r  Set correct time in format > set time hh:mm:ss",		 			//12		
	"\n\r  where mm-month, yy-year ",			//13
	"\n\r  where ww-day of week, dd-day of month ",	//14
	"\n\r  Set correct date in format > set date ww:dd:mm:yy ",	//15
	" 1. AI calibration for PT1000 ",			//16
	"\n\r  Please plug in AI socket connector AI_0 and press Enter",		//17
	"\n\r  Please plug in AI socket connector AI_2 and press Enter",		//18
	"\n\r  Please plug in AI socket connector AI_0 and press Enter ",		//19
	"\n\r  Please wait for 10 sec",				//20
	"\n\r  Please plug in AI socket connector AI_1 and press Enter",		//21
	"\n\r  Real temperature \n\r   ",			//22						
	"\n\r  Saving parameters...",     			//23						
	" 2. DI testing ",						//24						
	"\n\r  Please plug in DI socket connector DI 0x55 and press Enter",		//25						
	"\n\r  Please plug in DI socket connector DI 0xAA and press Enter",		//26						
	"\n\r  Readed DI Value  0x",				//27						
	" 3. DO testing ",						//28						
	"\n\r  Please check all leds. They must be ON ",						//29
	"\n\r  Please check one by one all leds. Press Enter to continue",								//30
	"\n\r  Press Enter to continue",						//31
	" 4. AO testing ",						//32
	"\n\r  All outputs will change from 0 to 10V. Press Enter to continue",			//33
	"\n\r  All outputs are ",					//34
	"\n\r  V",				//35			
	"\n\r  AI ",				//36
	" GOOD ",				//37			
	" BAD ",				//38						
//	txt,		//32
//	txt,		//33
};
//-----------------------------------------------------------------------------------
void Delay2(u16 val)// value in ms
{
	u8 in;
	Time0=val;
	while(Time0!=0)	
	{
		watchdog_reset();	
		if(console_check_rx())	
		{
			in=console_rx_byte();
			if(in==0x0D)return;
		}
	}
}
//-----------------------------------------------------------------------------------
s16 Wait()
{
	u8 in;
//	u8 i;
	while(1)
	{
		watchdog_reset();	
		if(console_check_rx())	
		{
				in=console_rx_byte();
				switch(in)
				{
					case 27:			
						// This is ESC sequence
						//ESC=1;
						__sprintf_P(outtxt,tdic[4]);
						return -1;										
					case 0x0A:
					break;
					case 0x0D:
						return 1;			
				}
		}
		
	}
}
//-----------------------------------------------------------------------------------
void AI_Test()
{
	f32 ftmp0;
	f32 ftmp1;	
	f32 ftmp2;	
//	f32 ftmp;
//	s16 tmp;	
	u8 i;	
	u8 stat=0;
//	u8 st=0;
	//*******************************************************************************
	// Analog inputs	
	//*******************************************************************************	
	watchdog_reset();	
//	__sprintf_P(outtxt,tdic[16]);	
	__sprintf_P(outtxt,tdic[17]);	if(Wait()==-1)return;
	__sprintf_P(outtxt,tdic[20]);Delay2(15000);
	// Make point 0 calculations
	{
		point_reference_temperature[0]=202; // 1k056 inserted
		adc_set_channel(0);
//		__sprintf(outtxt,"\n\r    ");
		for(i=0;i<io.num_ai;i++)	
		{
			Delay(50);
			adc_conversion();
			Delay(50);
			adc_conversion();			
			point_real_temperature[0][i]=ad_res;
			adc_set_channel(i+1);	
//			ShowTemperature(outtxt,&point_real_temperature[0][i]);__sprintf(outtxt,"  ");			
		}
	}
	watchdog_reset();		
	__sprintf_P(outtxt,tdic[18]);	if(Wait()==-1)return;
	__sprintf_P(outtxt,tdic[20]);Delay2(15000);
	point_reference_temperature[1]=785;	//1K2 inserted
	// Make point 1 calculations >  cofficients + offsets
	{
		adc_set_channel(0);
	//	__sprintf(outtxt,"\n\r    ");
		for(i=0;i<io.num_ai;i++)	
		{
			Delay(50);
			adc_conversion();
			Delay(50);
			adc_conversion();
//			if(ad_res<0x00ff)ad_res=0xffff;
			point_real_temperature[1][i]=ad_res;
			adc_set_channel(i+1);	
//			ShowTemperature(outtxt,&point_real_temperature[1][i]);__sprintf(outtxt,"  ");			
		}
	}	
	{
		ftmp1=point_reference_temperature[1]-point_reference_temperature[0];
		for(i=0;i<io.num_ai;i++)	
		{
			ftmp0=point_real_temperature[1][i]-point_real_temperature[0][i];
			if(ftmp0<1)ftmp0=1;
			ftmp2=ftmp1/ftmp0;
			io.ai_coff[i]=ftmp2;
		}
	}	
	watchdog_reset();	
	__sprintf_P(outtxt,tdic[19]);	if(Wait()==-1)return;
	__sprintf_P(outtxt,tdic[20]);Delay2(15000);
	// Make point 2 calculations >  offsets (optional)
	{
		adc_set_channel(0);
		for(i=0;i<io.num_ai;i++)	
		{
			Delay(50);
			adc_conversion();
			Delay(50);
			adc_conversion();
			point_real_temperature[0][i]=(f32)ad_res*io.ai_coff[i];
			adc_set_channel(i+1);	
//			ShowTemperature(outtxt,&point_real_temperature[0][i]);__sprintf(outtxt,"  ");		
		}
		for(i=0;i<io.num_ai;i++)	
		{
			io.ai_offset[i]=point_reference_temperature[0]-point_real_temperature[0][i];			
		}		
	}	
	watchdog_reset();	
	// Measuring middle value
//	__sprintf_P(outtxt,tdic[21]);if(Wait()==-1)return;
//	__sprintf_P(outtxt,tdic[20]);Delay2(10000);
//	__sprintf_P(outtxt,tdic[22]);	
	__sprintf_P(outtxt,tdic[4]);		
	{
		adc_set_channel(0);	
		adc_conversion();	
		for(i=0;i<io.num_ai;i++)	
		{
			Delay(50);
			adc_conversion();
			Delay(50);
			adc_conversion();
			adc_set_channel(i+1);	
			point_real_temperature[0][i]=ad_res;
//			ShowTemperature(outtxt,&point_real_temperature[0][i]);__sprintf(outtxt,"->");
			point_real_temperature[0][i]*=io.ai_coff[i];
			point_real_temperature[0][i]+=io.ai_offset[i];
			if((point_real_temperature[0][i]>(202+AIN_MISTAKE))||(point_real_temperature[0][i]<(202-AIN_MISTAKE)))
			{
				stat=1;			
				__sprintf_P(outtxt,tdic[36]);ByteToStr(outtxt,&i,0);		
				__sprintf_P(outtxt,tdic[38]);				
			}
			else
			{
				__sprintf_P(outtxt,tdic[36]);ByteToStr(outtxt,&i,0);		
				__sprintf_P(outtxt,tdic[37]);				
			}
			ShowTemperature(outtxt,&point_real_temperature[0][i]);
//			if((point_real_temperature[0][i]>(202+AIN_MISTAKE))||(point_real_temperature[0][i]<(202-AIN_MISTAKE)))stat=1;
		}
	}
	watchdog_reset();	
	__sprintf_P(outtxt,tdic[23]);
	Time_To_Store=3;
	if(stat==0)
	{
		__sprintf_P(outtxt,tdic[5]);	
		test_state|=0x01;
	}
	else
		__sprintf_P(outtxt,tdic[6]);		
	__sprintf_P(outtxt,tdic[4]);		
}
//-----------------------------------------------------------------------------------
void DI_Test()
{
	u8 stat=0;
	//*******************************************************************************
	// Digital inputs
	//*******************************************************************************
	watchdog_reset();	
	__sprintf_P(outtxt,tdic[24]);
	__sprintf_P(outtxt,tdic[25]);	if(Wait()==-1)return;
	io_handle();
	io.din&=0x0000003f;
	__sprintf_P(outtxt,tdic[27]);ByteToStr(outtxt,(u8*)&io.din,1);
	if(io.din!=0x15)stat=1;
	__sprintf_P(outtxt,tdic[26]);	if(Wait()==-1)return;
	io_handle();
	io.din&=0x0000003f;
	__sprintf_P(outtxt,tdic[27]);ByteToStr(outtxt,(u8*)&io.din,1);	
	if(io.din!=0x2A)stat=1;
	if(stat==0)
	{
		__sprintf_P(outtxt,tdic[5]);	
		test_state|=0x02;
	}
	else
		__sprintf_P(outtxt,tdic[6]);			
	__sprintf_P(outtxt,tdic[4]);			
}
//-----------------------------------------------------------------------------------
void DO_Test()
{
	u8 i;	
	//*******************************************************************************
	// Digital outputs
	//*******************************************************************************	
	watchdog_reset();	
	__sprintf_P(outtxt,tdic[28]);
	__sprintf_P(outtxt,tdic[31]);	if(Wait()==-1)return;
	for(i=0;i<100;i++)
	{
		watchdog_reset();	
		io.dout|=0x0000001f;
		io_handle();
		Delay(20);
		io.dout&=~0x0000001f;
		io_handle();
		Delay(20);		
	}
	
	io.dout|=0x0000001f;
	io_handle();
	__sprintf_P(outtxt,tdic[29]);	if(Wait()==-1)return;
	io.dout|=0x00000000;
	io_handle();
	
	__sprintf_P(outtxt,tdic[30]);ByteToStr(outtxt,(u8*)&io.din,1);
	io.dout=0x00000001;	
	for(i=0;i<5;i++)
	{
		io_handle();
		Delay2(500);
		io.dout=io.dout<<1;
	}	
//	__sprintf_P(outtxt,tdic[31]);	while(recchar()!=13){};
	io.dout|=0x00000000;
	io_handle();	
	test_state|=0x04;
	__sprintf_P(outtxt,tdic[4]);			
}
//-----------------------------------------------------------------------------------
void AO_Test()
{
//	f32 ftmp0;
//	f32 ftmp1;	
//	f32 ftmp2;	
	f32 ftmp;
	u8 i;
	//*******************************************************************************
	// Analog outputs
	//*******************************************************************************
	watchdog_reset();		
	__sprintf_P(outtxt,tdic[32]);
	__sprintf_P(outtxt,tdic[33]);	if(Wait()==-1)return;	
	for(i=0;i<11;i+=1)
	{
		ftmp=i;
		ftmp*=10;
		__sprintf_P(outtxt,tdic[34]);ByteToStr(outtxt,&i,0);__sprintf(outtxt,"V");
		io.aoutput[0]=i*10;
		io.aoutput[1]=i*10;
//		io.aoutput[2]=i*100;
//		io.aoutput[3]=i*100;
		io_handle();
		Delay2(2000);
	}
	for(i=0;i<11;i+=1)
	{
		ftmp=i;
		ftmp*=100;
		__sprintf_P(outtxt,tdic[34]);ByteToStr(outtxt,&i,0);__sprintf(outtxt,"V");
		io.aoutput[0]=i*100;
		io.aoutput[1]=i*100;
//		io.aoutput[2]=i*100;
//		io.aoutput[3]=i*100;
		io_handle();
		Delay2(2000);
	}
	io.aoutput[0]=0;
	io.aoutput[1]=0;
//	io.aoutput[2]=0;
//	io.aoutput[3]=0;
	io_handle();	
/*	
	__sprintf_P(outtxt,tdic[10]);
	__sprintf_P(outtxt,tdic[15]);
	__sprintf_P(outtxt,tdic[14]);
	__sprintf_P(outtxt,tdic[13]);			
	__sprintf_P(outtxt,tdic[12]);
	__sprintf_P(outtxt,tdic[11]);		
	__sprintf_P(outtxt,tdic[31]);	while(recchar()!=13){};	
*/
	test_state|=0x08;
	__sprintf_P(outtxt,tdic[4]);
}
//-----------------------------------------------------------------------------------
void RTC_Test()
{
//	u8 i;
	u8 stat=0;
	fram_set_date(7,9,20,5);
	fram_set_time(15,12,30);	
	fram_init();
	Delay2(2000);
	fram_get_time();
	if((ft.field.Date!=20)||(ft.field.Second==30))stat=1;
	if(stat==0)
	{
		__sprintf_P(outtxt,tdic[5]);	
		test_state|=0x10;
	}
	else
		__sprintf_P(outtxt,tdic[6]);			
	__sprintf_P(outtxt,tdic[4]);
}
//-----------------------------------------------------------------------------------
void RS485_Test()
{
/*	u8 i,j;
	u8 stat=0;
	u8 st=0;
	u8 din;
	u8 count;
	u8 sign;
	u8 bad=0;
//	__sprintf_P(outtxt,tdic[11]);
//	__sprintf_P(outtxt,tdic[31]);	if(Wait()==-1)return;	
//	return;
	console_mode=2;
	for(i=0;i<5;i++)
	{
		upc_Set_Channel(i+1);
		dir_init();
		st=0;	
		Time0=0;
		count=0;
		sign=0;
		while(count!=5)
		{
			if(Time0==0)
			{
				sign=1;
				Time0=100;
				count++;
			}
			if(dir_handle2(0x0d,sign)=='>')
			{
				count=5;
				st=1;
			}
			sign=0;
			watchdog_reset();		
		}
		if(st==0)
		{
			stat=1;
			bad|=1<<i;
		}
					
	}
	
	console_mode=1;
	con_init();
	upc_init();
	if(stat==0)
	{
		__sprintf_P(outtxt,tdic[5]);	
		test_state|=0x20;
	}
	else
	{
		__sprintf_P(outtxt,tdic[6]);			
		for(i=1;i<6;i++)
		{
			if(bad & (1<<(i-1)))
			{
				__sprintf(outtxt,"\n\r Bad  channel ");
				ByteToStr(outtxt,&i,0);
			}
			else
			{
				__sprintf(outtxt,"\n\r Good channel ");
				ByteToStr(outtxt,&i,0);
			}			
		}		
	}
*/	
	__sprintf_P(outtxt,tdic[4]);
}
//-----------------------------------------------------------------------------------
s16 Choose_Test()
{
	u8 in;
	u8 i;
	__sprintf_P(outtxt,tdic[3]);
	switch(test_ptr)
	{
		case 0: __sprintf_P(outtxt,tdic[16]);break;	
		case 1: __sprintf_P(outtxt,tdic[24]);break;	
		case 2: __sprintf_P(outtxt,tdic[28]);break;	
		case 3: __sprintf_P(outtxt,tdic[32]);break;	
		case 4: __sprintf_P(outtxt,tdic[7]);break;	
		case 5: __sprintf_P(outtxt,tdic[11]);break;		
		
	}	
	while(1)
	{
		watchdog_reset();	
		if(console_check_rx())	
		{
				in=console_rx_byte();
				switch(in)
				{
					case 27:			
						// This is ESC sequence
						//ESC=1;
						Time0=50;
						while(!console_check_rx())
						{
							if(Time0==0)
							{
								return -1;
							}
						}
						in=console_rx_byte();
						while(!console_check_rx())
						{
							if(Time0==0)
							{
								return -1;
							}
						}
						in=console_rx_byte();
						// Handle ESC sequence
						switch(in)
						{
							case 0x41:
								// Up arrow
								if(test_ptr>0)
								{
									test_ptr--;
									// Erase current line
									for(i=0;i<30;i++)
									{
										sendchar(0x08);
										sendchar(' ');
										sendchar(0x08);
										inptr--;					
										*inptr=0;					
									}									
									switch(test_ptr)
									{
										case 0: __sprintf_P(outtxt,tdic[16]);break;	
										case 1: __sprintf_P(outtxt,tdic[24]);break;	
										case 2: __sprintf_P(outtxt,tdic[28]);break;	
										case 3: __sprintf_P(outtxt,tdic[32]);break;	
										case 4: __sprintf_P(outtxt,tdic[7]);break;
										case 5: __sprintf_P(outtxt,tdic[11]);break;	
									}
								}				
							break;
							case 0x42:
								// Down arrow
								if(test_ptr<5)
								{
									test_ptr++;
									// Erase current line
									for(i=0;i<30;i++)
									{
										sendchar(0x08);
										sendchar(' ');
										sendchar(0x08);
										inptr--;					
										*inptr=0;					
									}										
									switch(test_ptr)
									{
										case 0: __sprintf_P(outtxt,tdic[16]);break;	
										case 1: __sprintf_P(outtxt,tdic[24]);break;	
										case 2: __sprintf_P(outtxt,tdic[28]);break;	
										case 3: __sprintf_P(outtxt,tdic[32]);break;
										case 4: __sprintf_P(outtxt,tdic[7]);break;
										case 5: __sprintf_P(outtxt,tdic[11]);break;	
									}
								}						
							break;			
						}													
					break;
					case 0x0A:
					break;
					case 0x0D:
							return test_ptr;		
		
				}
		}
		
	}
}
//-----------------------------------------------------------------------------------
void Production_Test()
{

//	f32 ftmp0;
//	f32 ftmp1;	
//	f32 ftmp2;	
//	f32 ftmp;
//	s16 tmp;	
	u8 i;	
	u8 bit=1;
	
	__sprintf_P(outtxt,tdic[2]);
		while(1)	
	{
		switch(Choose_Test())
		{
			case -1:
				if(test_state!=0x2F)
				{
					__sprintf_P(outtxt,tdic[8]);
					for(i=0;i<5;i++)
					{
						if((test_state & bit)==0)
						switch(i)
						{
							case 0: __sprintf_P(outtxt,tdic[9]);__sprintf_P(outtxt,tdic[16]);break;	
							case 1: __sprintf_P(outtxt,tdic[9]);__sprintf_P(outtxt,tdic[24]);break;	
							case 2: __sprintf_P(outtxt,tdic[9]);__sprintf_P(outtxt,tdic[28]);break;	
							case 3: __sprintf_P(outtxt,tdic[9]);__sprintf_P(outtxt,tdic[32]);break;
							case 4: __sprintf_P(outtxt,tdic[9]);__sprintf_P(outtxt,tdic[7]);break;	
							case 5: __sprintf_P(outtxt,tdic[9]);__sprintf_P(outtxt,tdic[11]);break;
						}		
						bit=bit<<1;				
					}
				}
			return;
			case 0: AI_Test();break;
			case 1: DI_Test();break;
			case 2: DO_Test();break;
			case 3: AO_Test();break;						
			case 4: RTC_Test();break;						
			case 5: RS485_Test();break;
		}
	}
}
//-----------------------------------------------------------------------------------
