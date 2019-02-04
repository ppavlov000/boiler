#include "..\main.h"
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
u8 UControl1=0;
u16 addr;
//-----------------------------------------------------------------------------------
__farflash u8	Monthes_Name[12][10]=
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
__farflash u8	Monthes_Name_Short[12][5]=
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
__farflash u8	DaysOfWeek[8][10]=
{
	" Monday  ",
	" Tuesday ",
	"Wednesday",
	"Thursday ",
	" Friday  ",
	"Saturday ",
	" Sunday  ",
	"         ",	
};
__farflash u8	DaysOfWeek_Short[8][5]=
{
	"Mon",
	"Tue",
	"Wed",
	"Thu",
	"Fri",
	"Sat",
	"Sun",
	"    ",	
};
__farflash u8	pdic[38][80]=
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
	"\n\r   Program is ",					//12		
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
	"\n\r Valid user program found\n\r ",		//28						
	"\n\r     Min power ",						//29
	"\n\r     Max power ",						//30
	"\n\r     Power     ",						//31
	"\n\r Power supply voltage ",				//32
	"\n\r     Servoprivod full cycle time c ",	//33
	"\n\r     3 points server power ",			//34
	"\n\r     Open  line ",					//35
	"\n\r     Close line ",					//36		
	"\n\r     Current temperature ",		//37
//	txt,		//33
};
//-----------------------------------------------------------------------------------
void Mod_Show_Status_IO();
//-----------------------------------------------------------------------------------
void Mod_Reset()
{
//	_sprintf(outtxt,"\n\r Resetting...");					
	reset();
}
//-----------------------------------------------------------------------------------
void Mod_Store_Parameters()
{
	params_store();
//	_sprintf(outtxt,"\n\r Parameters stored ");
}
//-----------------------------------------------------------------------------------
void Mod_Test()
{	
/*
	u32 i;
	for(i=0;i<255UL;i++) {
		set_backlight_pwm(i);
		Delay(100);
	}
*/
	u8 i;
//	_sprintf(outtxt,"\n\r Test...");
	for(i=0;i<100;i++)
	{
	lcd_initialise(0);
	lcd_initialise(1);
	lcd_initialise(2);
	lcd_initialise(3);			
	}
	lcd_initialise(0);	

//	calibrate_bmp();
}
//-----------------------------------------------------------------------------------
void Mod_Show_Status()
{
//	u16 wtmp;
//	u8 i,j,tmp;
}
//-----------------------------------------------------------------------------------
void Mod_Show_Full_Time()
{
//	u8 tmp;
//	fram_get_time();
	
//	_sprintf(outtxt,"\n\r Date ");
///	ByteToStr(outtxt,&m.ft.field.Date,0);_sprintf(outtxt,".");
//	ByteToStr(outtxt,&m.ft.field.Month,0);_sprintf(outtxt,".");
//	ByteToStr(outtxt,&m.ft.field.Year,0);

/*	
	_sprintf(outtxt,"\n\r ");
	ByteToStrFillZero(outtxt,&ft.field.Date,0,2,'0');
	_sprintf(outtxt," ");
	_sprintf_P(outtxt,Monthes_Name[ft.field.Month-1]);
	_sprintf(outtxt," 20");
	ByteToStrFillZero(outtxt,&ft.field.Year,0,2,'0');
	_sprintf(outtxt,", ");
	_sprintf_P(outtxt,DaysOfWeek	[ft.field.Day-1]);	
				
	_sprintf(outtxt,"\n\r Time ");
	ByteToStrFillZero(outtxt,&ft.field.Hour,0,2,'0');_sprintf(outtxt,".");
	ByteToStrFillZero(outtxt,&ft.field.Minute,0,2,'0');_sprintf(outtxt,".");
	ByteToStrFillZero(outtxt,&ft.field.Second,0,2,'0');
*/
}
//-----------------------------------------------------------------------------------
void Mod_Down_Picture()
{
/*
	u16 CRC;
	_sprintf(outtxt,"\n\r   Downloading");			
	addr=0;
	Xmodem_Start();
	ctmp=XMOD_None;
	while(ctmp==XMOD_None)
	{
		ctmp=Xmodem_Processor();
	}
	if(ctmp==XMOD_Ok)
	{
		_sprintf(outtxt,"\n\r   Complete");
		// Check program CRC
		show_bmp();
		
	}
	else
		_sprintf(outtxt,"\n\r   Error");
*/
}
//-----------------------------------------------------------------------------------
u16 get_reg_addr(u8* reg_addr)
{
	u16 addr=0;
	u8 *ptr=&reg_data[0];
	addr=reg_addr-ptr;
	return addr;
}
//-----------------------------------------------------------------------------------
// who-5 Params fields in eep
#ifndef __RENESAS
u32 CheckCRC(u8 who)
{
	u32 len,p,Addr;
	u16 crc;
	u8 ctmp;
	switch(who)
	{
		case 5:
			Addr = PARAM_LOCATION;
			len  = TPARAM_WIDTH-2;
			InitCRC(&crc);
			for(p=0;p<len;p++)	
			{
				EEGet(&ctmp,(u16)(Addr+p),1);
				CalcCRC(&ctmp,1,&crc);
			}
			EndCRC(&crc);
		break;
	 }
	return crc;
}
#endif
//-----------------------------------------------------------------------------------
