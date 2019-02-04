//-----------------------------------------------------------------------------------
#include "..\Main.h"
#include "..\Tsc2046\tsc2046.h"
//-----------------------------------------------------------------------------------
#include "..\Menu_New\lcd_template.h"
#include "..\Menu_New\lcd_calibrate.h"
#include "..\Menu_New\lcd_alarm.h"
#include "..\Menu_New\lcd_alarm_snooze.h"
//-----------------------------------------------------------------------------------
extern TLCDPictTop Scr_0;
extern __farflash TLCDPict_Txt _Txt_0;
extern __farflash TLCDPict_Txt _Txt_1;
extern __farflash TLCDPict_Txt _Txt_2;
extern __farflash TLCDPict_Txt _Txt_3;
extern __farflash TLCDPict_Txt _Txt_4;
//-----------------------------------------------------------------------------------
TLCDPict _Point_1=
{
	1,8,30,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	NULL,
	NULL,	
};
//--------------------------------------------
TLCDPict _Point_0=
{
	28,112,30,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,	
	0,
	NULL,
	NULL,	
};
//-----------------------------------------------------------------------------------
void calibrate_bmp()
{
//	u8 tmp;	
//	u8 stat=0;
	u16 x[2];
	u16 y[2];
//	u8 s[2]={0,0};
	u8 str[20];
	u8 count;
	f32 fx,fy;
	
	// check pressed at default	
	tsc_n=0;
	Ext_IRQ0();
	if(tsc_n!=0)
	{
		lcd_sprintf_P(Main_Dict[10],9,0);
		Ext_IRQ0();
		while(tsc_n!=0)
		{
			Ext_IRQ0();
			watchdog_reset();
//			tsc_n=0;
		}
	}
	lcd_clear_text();
	Delay(100);
	watchdog_reset();
	clear_page();
	lcd_clear_text();	
//	LCDMenuPtr=&_Calibrate;		
	lcd_sprintf_P(Main_Dict[7],3,0);
	lcd_sprintf_P(Main_Dict[8],3,1);
	
	show_single_bmp(&_Point_1,0);	
//	handle_page();
//	repaint_page();
	tsc_n=0;
	TSC_Time=TSC_REQUEST_TIME;
	count=0;
	fx=fy=0;
	watchdog_reset();
	while(count<10)
	{
		watchdog_reset();
//		if(TSC_Time==0)
//		{
//			TSC_Time=TSC_REQUEST_TIME;
			Ext_IRQ0();
			if(tsc_n)
			{
				fx+=tsc_rx;
				fy+=tsc_ry;	
				count++;	
//				tsc_n=0;
			}
//		}
	}
	x[0]=fx/10;
	y[0]=fy/10;			
//	s[0]=1;
	watchdog_reset();
	lcd_sprintf("X=",5,2);WordToStr(str,(u16*)&x[0],0);lcd_sprintf(str,7,2);
	lcd_sprintf("Y=",5,3);WordToStr(str,(u16*)&y[0],0);lcd_sprintf(str,7,3);
	
	show_single_bmp(&_Point_0,0);		
	lcd_sprintf_P(Main_Dict[9],3,4);	
	Delay(1000);
	TSC_Time=TSC_REQUEST_TIME;
	count=0;
	fx=fy=0;
	while(count<10)
	{
		watchdog_reset();
//		if(TSC_Time==0)
//		{
//			TSC_Time=TSC_REQUEST_TIME;
			Ext_IRQ0();
			if(tsc_n)
			{
				fx+=tsc_rx;
				fy+=tsc_ry;	
				count++;			
//				tsc_n=0;
//				Delay(10);
			}
//		}
	}
	x[1]=fx/10;
	y[1]=fy/10;			
//	s[1]=1;
	lcd_sprintf("X=",5,5);WordToStr(str,(u16*)&x[1],0);lcd_sprintf(str,7,5);
	lcd_sprintf("Y=",5,6);WordToStr(str,(u16*)&y[1],0);lcd_sprintf(str,7,6);
	// Proportions
	fx=x[1]-x[0];
	fx=216/fx;
	m.coff.x=fx;
	fy=y[1]-y[0];
	fy=104/fy;
	m.coff.x=fx;
	m.coff.y=fy;
	// Offsets	
	fx=11/m.coff.x;
	fx=x[0]-fx;
	m.coff.ox[0]=fx;

	fy=11/m.coff.y;
	fy=y[0]-fy;
	m.coff.oy[0]=fy;
	
	Delay(2000);
	params_store();
	lcd_clear_text();
	clear_single_bmp(&_Point_0);
	clear_single_bmp(&_Point_1);	
//	repaint_page();
}
//-----------------------------------------------------------------------------------
