#include "..\main.h"
#include "tsc2046.h"
//-----------------------------------------------------------------------------------
#define TSC_MIN_LVL		1000	// Minimal Z level to determine touch
//-----------------------------------------------------------------------------------
u16 tsc_y,tsc_x,tsc_z,tsc_r;		// Calculated parameters
u16 tsc_ry,tsc_rx,tsc_rz,tsc_rz2;	// RAW parameters
u16 i_y,i_x,i_z;
s32 m_y,m_x;
s32 d_y,d_x;
u16 yy[4],xx[4];
vu8 tsc_n=0;
u8 tsc_up_down=0;
f32 fx,fy,fz;
extern u8 enter_tech_menu;
extern u8 dimmer_new_press;
extern TLCDPictTop Scr_0;
extern u8 Switch_To_ID_1;
//-----------------------------------------------------------------------------------
void Ext_IRQ0()
{
//	u8 i;
//	EIMSK=0x00;
	f32 fl;
	i_x=0;i_y=0;i_z=0;
	tsc_rx = TSC_Transfer(0x50,0x10);
	tsc_ry = TSC_Transfer(0x10,0x30);
	tsc_rz = TSC_Transfer(0x30,0x40);		
	tsc_rz2 = TSC_Transfer(0x40,0x50);
	i_x = tsc_rx;
	i_y = tsc_ry;
	i_z = tsc_rz;

	if(tsc_rz==0)tsc_rz=1;
	fl=(f32)tsc_rz2/tsc_rz;
	fl-=1;
	fl*=tsc_rx;
	fl/=4096;
	tsc_r=fl*1000;
	
	if (i_x > m.coff.ox[0]) i_x -= m.coff.ox[0]; else i_x = 0;
	if (i_y > m.coff.oy[0]) i_y -= m.coff.oy[0]; else i_y = 0;
	i_x = (float)i_x * m.coff.x;
	i_y = (float)i_y * m.coff.y;
	if (i_x > 240) i_x = 240;
	if (i_y > 128) i_y = 128;
			
	if((tsc_r<=TSC_MIN_LVL)&&(tsc_r>100)&&(tsc_rx>100)&&(tsc_ry>100)&&(tsc_rx<3800))
//	if(1)
	{
//		tsc_up_down=1;// Down;
		tsc_x=i_x;
		tsc_y=i_y;
		tsc_z=i_z;
		tsc_n=1;		
		if((i_x>90)&&(i_x<150)&&(i_y>48)&&(i_y<80))
			enter_tech_menu++;
		if((LCDTopPtr!=&Scr_0))Switch_To_Main_Time=60;		
		Switch_To_ID_1=60;

//		sprintf(outtxt,"\n\r ");LongToStr(outtxt,&tsc_rx,0);sprintf(outtxt," ");LongToStr(outtxt,&tsc_ry,0);
/*		lcd_sprintf("                      ",0,3);		
		lcd_sprintf("                      ",0,4);		
		WordToStr(lcd_txt,&tsc_rx,0);lcd_sprintf(lcd_txt,0,3);
		WordToStr(lcd_txt,&tsc_ry,0);lcd_sprintf(lcd_txt,0,4);	
*/		
	}		
	else
	{
		tsc_n=0;
//		dimmer_new_press=0;
		enter_tech_menu=0;		
		R0_Time=600;
//		R0_Time=600;
	}
}
//-----------------------------------------------------------------------------------
