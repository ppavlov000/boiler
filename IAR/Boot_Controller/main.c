//-----------------------------------------------------------------------------------
#include "main.h"
//-----------------------------------------------------------------------------------
u8 m_Address=0;
u8 stat=0;
u8 Enter_Boot_Mode=0;
u8 ID_Changed=0;
u8 Flash_Checked=0;
u16 CRC;
u8 blink_count=0;
u8 envitation[20];
u32 key=0;
//-----------------------------------------------------------------------------------
void init()
{
	//beep_init;
	panel_hardware_init();
	I2C_Init();
	fram_init();
	fram_watchdog_reset();	
	Timer_Init();
	upc_init();
	key=0x55000000;
	get_address();	
	enable_interrupt();
	beep_init();
	Delay(10);	
}
//-----------------------------------------------------------------------------------
void blink_booting()
{
	fram_watchdog_reset();
	if(Time4==0)
	{
		Time4=100;
		Time6=50;
	}
}
//-----------------------------------------------------------------------------------
void blink_bad_image()
{
	fram_watchdog_reset();
	if(Time4==0)
	{
//		Time4=200;
//		led_toggle();
		switch(blink_count)	
		{
			case 0: Time4=400;Time6=200; break;
			case 1: Time4=400;Time6=200; break;
			case 2: Time4=800;Time6=200; break;
			
			case 3: Time4=800;Time6=400; break;
			case 4: Time4=800;Time6=400; break;
			case 5: Time4=1000;Time6=400; break;
			
			case 6: Time4=400;Time6=200; break;
			case 7: Time4=400;Time6=200; break;
			case 8: Time4=1800;Time6=200;blink_count=0;return;
			
		};
		blink_count++;
	}
}
//-----------------------------------------------------------------------------------
void blink_good_image()
{
	fram_watchdog_reset();
	if(Time4==0)
	{
		Time4=200;
		Time6=100;
	}
}
//-----------------------------------------------------------------------------------
void get_address()
{
//	u8 i;
	u8 tmp=1;
//	u8 count;
//	m_Address=1;	
	{
		read_addr_pins();
		if(tmp==0)
		{
			// Beep on
			beep_init();
			beep_on();
		}
		else
		{
			// Beep off
			beep_off();
		}	
	}
}
//-----------------------------------------------------------------------------------
u8 check_flash_images()
{
	u8 images_stat=0;
	FGet((u8*)&wtmp,HAPP_FLASH_START+CRC_H_LOC,2);	
 	CRC=wtmp;
	wtmp=CheckCRC(3);
	if(wtmp==CRC)
	{
		FGet((u8*)&wtmp,HAPP_FLASH_START+CRC_D_LOC,2);	
		CRC=wtmp;
		wtmp=CheckCRC(1);
		if(wtmp!=CRC)
			images_stat|=0x01;
	}
	else
	{
		images_stat|=0x01;
	}

	// Picture part	
	FGet((u8*)&wtmp,HPLM_FLASH_START+THEAD_WIDTH-2,2);	
	CRC=wtmp;
	wtmp=CheckCRC(4);
	if(wtmp==CRC)
	{
		FGet((u8*)&wtmp,HPLM_FLASH_START+THEAD_WIDTH-4,2);	
		CRC=wtmp;
		wtmp=CheckCRC(2);
		if(wtmp!=CRC)
			images_stat|=0x02;
	}
	else
		images_stat|=0x02;
		
    return images_stat;
}
//-----------------------------------------------------------------------------------
void main()
{
	init();

	get_address();
	stat=check_flash_images();
	Flash_Checked=1;
  //------------------------------------ 	
  	key|=0x00AA0000;
  	led_off();
	get_address();	
	upc_en(1);
	while(1)
	{		
		if(stat==0)
		{
			// Images are correct
			Time0=5000;
			while(1)
			{
				fram_watchdog_reset();
				blink_good_image();
				Flash_Downloader();
				if(Enter_Boot_Mode==0)
					if(Time0==0)start_main();
//				if(ID_Changed){
//					fram_mem_write(ID_LOCATION,(u8*)&rx.field.d[0],1);							
//					ID_Changed=0;
//				}

			}
		}
		else
		{
			// Images are corrupted
			while(1)
			{
				fram_watchdog_reset();
				blink_bad_image();
				Flash_Downloader();
				Enter_Boot_Mode=1;
				if(stat==0)break;
//				if(ID_Changed){
//					fram_mem_write(ID_LOCATION,(u8*)&rx.field.d[0],1);							
//					ID_Changed=0;
//				}
			}
		}
	}
}
//-----------------------------------------------------------------------------------
