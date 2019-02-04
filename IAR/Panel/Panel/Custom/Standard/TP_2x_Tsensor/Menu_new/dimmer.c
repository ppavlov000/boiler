//-----------------------------------------------------------------------------------
#include "..\..\..\..\System\Main.h"
#include "..\..\..\..\System\Menu_New\lcd_template.h"
#include "..\..\..\..\System\Menu_New\lcd_calibrate.h"
#include "..\..\..\..\System\Menu_New\lcd_alarm.h"
#include "..\..\..\..\System\Menu_New\lcd_alarm_snooze.h"
#include "..\..\..\..\System\Menu_New\lcd_ac_menu.h"
#include "..\..\..\..\System\Menu_New\lcd_tech_menu.h"
#include "..\..\..\..\System\Menu_New\lcd_set_time.h"
#include "..\..\..\..\System\Menu_New\lcd_tech_contrast.h"
#include "..\..\..\..\System\Menu_New\lcd_tech_temperature.h"
//-----------------------------------------------------------------------------------
#define But_Dimmer_0			Obj[15]
#define But_Dimmer_1			Obj[15]
#define But_Dimmer_2			Obj[15]
#define But_Dimmer_3			Obj[15]
#define But_Dimmer_4			Obj[15]
#define But_Dimmer_5			Obj[15]
#define But_Dimmer_6			Obj[15]
#define But_Dimmer_7			Obj[15]
//-----------------------------------------------------------------------------------
u8 Dimmer_Dir[8]={0};	//0=+ 1=-
u8 dimmer_slope[8]={0};
u8 dimmer_new_press=0;
s8 dimmer_sequence_state = 0;
u16 dimmer_sequence_timeout = 0;
//-----------------------------------------------------------------------------------
void dimmer_handle_0();
void dimmer_handle_1();
void dimmer_handle_2();
void dimmer_handle_3();
void dimmer_handle_4();
void dimmer_handle_5();
void dimmer_handle_6();
void dimmer_handle_7();

void dimmer_handle_alt_0();

void dimmer_plus(u8 num);
void dimmer_minus(u8 num);
void dimmer_off(u8 num);
void dimmer_on(u8 num);

u8 dimmer_stat=0;
u8 dimmer_rise=0;
u8 dimmer_fall=0;
u8 dimmer_edge=0;
u8 mask=0;
eu16 Dimmer_Time3;
//-----------------------------------------------------------------------------------
void dimmer_handle_custom()
{
//	u8 mask=1<<0;
	u8 i;	
	if(Dimmer_Time3==0)
	{	
		Dimmer_Time3=80;		
		for(i=0;i<8;i++)
		{
			if((dimmer_edge & (1<<i))!=0)
				dimmer_plus(i);	
		}
/*
		if((dimmer_rise & mask)!=0)
		{
			Dimmer_Dir[0]=1;
			dimmer_plus(0);	
		}		
*/		
	}	
	
}
//-----------------------------------------------------------------------------------
void dimmer_handle_alt(u8 num)
{
	u8 mask=1<<num;
	if((R0_Time!=0))
	{
		BUZZ_Time=10;
		if((dimmer_edge & mask)==0)
			dimmer_edge |= mask;
		else
		{
			dimmer_edge &=~ mask;
//			if(Dimmer_Dir[num])Dimmer_Dir[num]=0;
//			else Dimmer_Dir[num]=1;
		}
	}
	else dimmer_plus(num);	
}
//-----------------------------------------------------------------------------------
void dimmer_handle_alt_0()
{
	dimmer_handle_alt(0);
}
//-----------------------------------------------------------------------------------
void dimmer_handle_0()
{
  	if(But_Dimmer_0.Stat==0)dimmer_off(0);	
	else dimmer_plus(0);	
}
//-----------------------------------------------------------------------------------
void dimmer_handle_1()
{
  	if(But_Dimmer_1.Stat==0)dimmer_off(1);	
	else dimmer_plus(1);
}
//-----------------------------------------------------------------------------------
void dimmer_handle_2()
{
  	if(But_Dimmer_2.Stat==0)dimmer_off(2);	
	else dimmer_plus(2);
}

//-----------------------------------------------------------------------------------
void dimmer_handle_3()
{
  	if(But_Dimmer_3.Stat==0)dimmer_off(3);	
	else dimmer_plus(3);
}

//-----------------------------------------------------------------------------------
void dimmer_handle_4()
{
  	if(But_Dimmer_4.Stat==0)dimmer_off(4);	
	else dimmer_plus(4);
}
//-----------------------------------------------------------------------------------
void dimmer_handle_5()
{
  	if(But_Dimmer_5.Stat==0)dimmer_off(5);	
	else dimmer_plus(5);
}
//-----------------------------------------------------------------------------------
void dimmer_handle_6()
{
  	if(But_Dimmer_6.Stat==0)dimmer_off(6);	
	else dimmer_plus(6);
}
//-----------------------------------------------------------------------------------
void dimmer_handle_7()
{
  	if(But_Dimmer_7.Stat==0)dimmer_off(7);	
	else dimmer_plus(7);
}
//-----------------------------------------------------------------------------------
void dimmer_plus(u8 num)
{
	u8 mask=1<<num;
	//BUZZ_Time=10;
  	if(Dimmer_Time2==0)
	{
/*		if(dimmer_new_press==0)
		{
			dimmer_slope[num]++;
			dimmer_new_press=1;
			if(dimmer_slope[num] & 1)
				Dimmer_Dir[num]=0;
			else
				Dimmer_Dir[num]=1;
		}
*/		
		if(Dimmer_Dir[num]==0)
		{
//			if(R0_Time==0)
			m.Dimmer.Power[num]+=2;
			if(m.Dimmer.Power[num]>=99)
			{
				m.Dimmer.Power[num]=99;	
				dimmer_edge &=~ mask;
				Dimmer_Dir[num]=1;
	//			Dimmer_Time2=1000;
	//			Dimmer_Dir[num]=1;
			}
		}
		else
		{
			if(m.Dimmer.Power[num]>=2)
			{
				m.Dimmer.Power[num]-=2;
			}
			else
			{
				m.Dimmer.Power[num]=0;	
				dimmer_edge &=~ mask;
				m.Dimmer.State &=~ mask;
				Dimmer_Dir[num]=0;
//				Dimmer_Dir[num]=0;		
//				Dimmer_Time2=2000;
			}
		}
	}
	own_state.status|=bit_new_push;	
	own_state.ds.Power=m.Dimmer.Power[num];
	own_state.ds.Channel=num;	
	m.Dimmer.State|=(1<<num);			
	own_state.ds.State=m.Dimmer.State;
}

//-----------------------------------------------------------------------------------
void dimmer_off(u8 num)
{
//	m.Dimmer.Power[num]=0;	
	
	own_state.status|=bit_new_push;	
	own_state.ds.Power=m.Dimmer.Power[num];
	own_state.ds.Channel=num;	
	m.Dimmer.State&=~(1<<num);				
	own_state.ds.State=m.Dimmer.State;
}

void dimmer_on(u8 num)
{
//	m.Dimmer.Power[num]=0;	
	
	own_state.status|=bit_new_push;	
	own_state.ds.Power=m.Dimmer.Power[num];
	own_state.ds.Channel=num;	
	m.Dimmer.State |= (1<<num);				
	own_state.ds.State=m.Dimmer.State;
}

//-----------------------------------------------------------------------------------
void update_dimmers()
{
	u8 old_stat;
	u32 tmp;
//	u8 i;
	{
		tmp=1<<0;
		old_stat=But_Dimmer_0.Stat;			
		if(m.Dimmer.State & tmp)
			But_Dimmer_0.Stat=1;
		else
			But_Dimmer_0.Stat=0;				
		if(old_stat!=But_Dimmer_0.Stat)
			show_single_bmp(&But_Dimmer_0,0);			

		tmp=1<<1;
		old_stat=But_Dimmer_1.Stat;			
		if(m.Dimmer.State & tmp)
			But_Dimmer_1.Stat=1;
		else
			But_Dimmer_1.Stat=0;				
		if(old_stat!=But_Dimmer_1.Stat)
			show_single_bmp(&But_Dimmer_1,0);			

		tmp=1<<2;
		old_stat=But_Dimmer_2.Stat;			
		if(m.Dimmer.State & tmp)
			But_Dimmer_2.Stat=1;
		else
			But_Dimmer_2.Stat=0;				
		if(old_stat!=But_Dimmer_2.Stat)
			show_single_bmp(&But_Dimmer_2,0);			

		tmp=1<<3;
		old_stat=But_Dimmer_3.Stat;			
		if(m.Dimmer.State & tmp)
			But_Dimmer_3.Stat=1;
		else
			But_Dimmer_3.Stat=0;				
		if(old_stat!=But_Dimmer_3.Stat)
			show_single_bmp(&But_Dimmer_3,0);			

		tmp=1<<4;
		old_stat=But_Dimmer_4.Stat;			
		if(m.Dimmer.State & tmp)
			But_Dimmer_4.Stat=1;
		else
			But_Dimmer_4.Stat=0;				
		if(old_stat!=But_Dimmer_4.Stat)
			show_single_bmp(&But_Dimmer_4,0);			

		tmp=1<<5;
		old_stat=But_Dimmer_5.Stat;			
		if(m.Dimmer.State & tmp)
			But_Dimmer_5.Stat=1;
		else
			But_Dimmer_5.Stat=0;				
		if(old_stat!=But_Dimmer_5.Stat)
			show_single_bmp(&But_Dimmer_5,0);			

		tmp=1<<6;
		old_stat=But_Dimmer_6.Stat;			
		if(m.Dimmer.State & tmp)
			But_Dimmer_6.Stat=1;
		else
			But_Dimmer_6.Stat=0;				
		if(old_stat!=But_Dimmer_6.Stat)
			show_single_bmp(&But_Dimmer_6,0);			

		tmp=1<<7;
		old_stat=But_Dimmer_7.Stat;			
		if(m.Dimmer.State & tmp)
			But_Dimmer_7.Stat=1;
		else
			But_Dimmer_7.Stat=0;				
		if(old_stat!=But_Dimmer_7.Stat)
			show_single_bmp(&But_Dimmer_7,0);	
	}
}
//-----------------------------------------------------------------------------------
