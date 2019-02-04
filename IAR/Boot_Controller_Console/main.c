//-----------------------------------------------------------------------------------
// Sourse of 8psk mcontroller host
//-----------------------------------------------------------------------------------
//#include <stdio.h>
#include "main.h"
//-----------------------------------------------------------------------------------
u8 stat=0;
u16 CRC;
u8 blink_count=0;
u8 envitation[20];
u32 key=0;
//-----------------------------------------------------------------------------------
void init() 
{
	MCUCR=0X01;
	MCUCR=0X02;
//	adm_init;
//	adm_wd_reset;
	Timer_Init();
	con_init();
	led_init;
	I2C_Init();
	fram_init();
	fram_watchdog_reset();
	
	envitation[0]='c';
	envitation[1]='o';
	envitation[2]='n';
	envitation[3]='t';
	envitation[4]='_';		
	envitation[5]='b';
	envitation[6]='o';
	envitation[7]='o';
	envitation[8]='t';
	envitation[9]='>';
	envitation[10]=0;
	key=0x55000000;
	__enable_interrupt();
}
//-----------------------------------------------------------------------------------
void blink_booting()
{
	fram_watchdog_reset();
	if(Time4==0)
	{
		Time4=50;
		if(led_check)
			led_off;
		else
			led_on;
	}
}
//-----------------------------------------------------------------------------------
void blink_bad_image()
{
	fram_watchdog_reset();
	if(Time4==0)
	{
		switch(blink_count)	
		{
			case 0: Time4=200;led_on; break;
			case 1: Time4=200;led_off; break;
			case 2: Time4=200;led_on; break;
			case 3: Time4=200;led_off; break;
			case 4: Time4=200;led_on; break;
			case 5: Time4=600;led_off; break;	
			
			case 6: Time4=400;led_on; break;
			case 7: Time4=400;led_off; break;
			case 8: Time4=400;led_on; break;
			case 9: Time4=400;led_off; break;
			case 10: Time4=400;led_on; break;
			case 11: Time4=600;led_off; break;	
			
			case 12: Time4=200;led_on; break;
			case 13: Time4=200;led_off; break;
			case 14: Time4=200;led_on; break;
			case 15: Time4=200;led_off; break;
			case 16: Time4=200;led_on; break;
			case 17: Time4=1600;led_off; blink_count=0;return; break;		
												
		};
		blink_count++;
	}
}
//-----------------------------------------------------------------------------------
void show_byte(u8 *out,u8 in,u8 offset)
{
	u8 str2[10];
	ByteToStr(str2,&in,0);
	if(ctmp>9)
	{
		out[offset]=str2[0];
		out[offset+1]=str2[1];
	}
	else
	{
		out[offset]='0';
		out[offset+1]=str2[0];
	}	
	out[offset+2]=0;
}
//-----------------------------------------------------------------------------------
void show_data(u8 *out,u8 separator,u32 addr,u8 a0,u8 a1, u8 a2)
{
	u8 str[20];
		FGet((u8*)&ctmp,addr+TTIME_LOC+a0,1);	
		show_byte(str,ctmp,0);			
		str[2]=separator;
		FGet((u8*)&ctmp,addr+TTIME_LOC+a1,1);	
		show_byte(str,ctmp,3);		
		str[5]=separator;
		FGet((u8*)&ctmp,addr+TTIME_LOC+a2,1);	
		show_byte(str,ctmp,6);	
		str[8]=0;	
		strcpy(outtxt,str);	
		wait_con_free();		
}
//-----------------------------------------------------------------------------------
void show_header(u32 addr)
{
		// HW Version
		sprintf(outtxt,"\n\r HW Version ");	
		FGet((u8*)&ltmp,addr+THW_LOC,4);	
		LongToStr(outtxt,&ltmp,0);
		// SW Version
		sprintf(outtxt,"\n\r SW Version ");	
		FGet((u8*)&ltmp,addr+TSW_LOC,4);	
		LongToStr(outtxt,&ltmp,0);
		// Date of creation
		sprintf(outtxt,"\n\r Date of creation  ");
		show_data(outtxt,'/',addr,4,5,6);	
		// Time of creation
		sprintf(outtxt,"  ");	
		show_data(outtxt,':',addr,2,1,0);	
		sprintf(outtxt," \n\r ");		
		FGet((u8*)outtxt,addr+TNAME_LOC,TNAME_WIDTH);
}
//-----------------------------------------------------------------------------------
void main()
{

	init();
	sprintf(outtxt,"\n\r"
							"\n\r Boot Loader Ver.03 September 2007"
							"\n\r Support FM31xx whatchdog is added"
							"\n\r");
 	// Application part	
	sprintf(outtxt,"\n\r Checking Application flash...");	
	FGet((u8*)&wtmp,HAPP_FLASH_START+CRC_H_LOC,2);	  
 	CRC=wtmp;
	wtmp=CheckCRC(3);
	if(wtmp==CRC)
	{
		FGet((u8*)&wtmp,HAPP_FLASH_START+CRC_D_LOC,2);	  
		CRC=wtmp;
		wtmp=CheckCRC(1);
		if(wtmp!=CRC)
			stat|=0x01;
	}
	else
		stat|=0x01;
    
	if(!(stat & 0x01))
	{
		sprintf(outtxt,"\n\r Application flash image CRC Ok\n\r\ ");	
		show_header(HAPP_FLASH_START);
/*		
		// HW Version
		sprintf(outtxt,"\n\r HW Version ");	
		FGet((u8*)&ltmp,HAPP_FLASH_START+THW_LOC,4);	
		LongToStr(outtxt,&ltmp,0);
		// SW Version
		sprintf(outtxt,"\n\r SW Version ");	
		FGet((u8*)&ltmp,HAPP_FLASH_START+TSW_LOC,4);	
		LongToStr(outtxt,&ltmp,0);
		// Date of creation
		sprintf(outtxt,"\n\r Date of creation  ");
		show_data(outtxt,'/',HAPP_FLASH_START,4,5,6);	
		// Time of creation
		sprintf(outtxt,"  ");	
		show_data(outtxt,':',HAPP_FLASH_START,2,1,0);	
		sprintf(outtxt," \n\r ");		
		FGet((u8*)outtxt,HAPP_FLASH_START+TNAME_LOC,TNAME_WIDTH);
*/		
	}
	else
	{
		sprintf(outtxt,"\n\r Application flash image CRC error... "
						"\n\r Please, download correct file..");	
	}
	// Picture part	
	sprintf(outtxt,"\n\r\n\r Checking user program...");	
	FGet((u8*)&wtmp,HPLM_FLASH_START+THEAD_WIDTH-2,2);	  
	CRC=wtmp;
	wtmp=CheckCRC(4);
	if(wtmp==CRC)
	{
		FGet((u8*)&wtmp,HPLM_FLASH_START+THEAD_WIDTH-4,2);	  
		CRC=wtmp;
		wtmp=CheckCRC(2);
		if(wtmp!=CRC)
			stat|=0x02;
	}
	else
		stat|=0x02;
    
	if(!(stat & 0x02))
	{
		sprintf(outtxt,"\n\r User program CRC Ok");	
		show_header(HPLM_FLASH_START);		
	}
	else
	{
		sprintf(outtxt,"\n\r User program CRC error... "
						"\n\r Please, download correct file..");	
	}
	
	fram_watchdog_reset();
 	sprintf(outtxt,"\n\r");		
  //------------------------------------ 
	key|=0x00AA0000;
	if(stat==0)
	{
		sprintf(outtxt,"\n\r"
 	                 "\n\r To enter console press Esc"   	
 	                 "\n\r To continue press Enter"   	 	                 
 	                 "\n\r Device will start up in 1 sec");		 	
			
		Time0=1000;  	
		Time1=200;  	  	
		while(1)
		{
			blink_booting();
			fram_watchdog_reset();
			if(Time0==0)
			{
//				spmEnableProtection;
				MCUCR=0X01;
				MCUCR=0X00;
				key=0;
				((void (*)())0x0000)();
			}
			if(Time1==0)
			{
				sprintf(outtxt,".");		 	
				wait_con_free();
				Time1=200;  	  	
			}
			if(UCSR0A & (1<<RXC0))  
			{
				ctmp=UDR0;
				if(ctmp==27)	
				{
					sprintf(outtxt,"\n\r");strcpy(outtxt,envitation);wait_con_free();		 	
						
					while(1)
					{
						__watchdog_reset();
						fram_watchdog_reset();
						con_handle(); 
						blink_booting();
					}   
				}
				if(ctmp==13)
				{
//					spmEnableProtection;	
					MCUCR=0X01;
					MCUCR=0X00;
					key=0;
					((void (*)())0x0000)();
				}
			}			
		}	
	}
	else
	{
		//------------------------------------	  
		sprintf(outtxt,"\n\r");strcpy(outtxt,envitation);wait_con_free();		 	
		while(1)
		{
			__watchdog_reset();
			fram_watchdog_reset();
			con_handle(); 
			blink_bad_image();     
		}
	}
}
//-----------------------------------------------------------------------------------
