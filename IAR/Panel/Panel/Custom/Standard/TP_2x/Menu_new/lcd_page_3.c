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
#define in_flash  __farflash
__farflash u8	pdic_alt[27][20]=
{
	"DI ",			//0		
	"DO ",			//1
	"AI ",			//2		
	"AO ",			//3		
	
	"AI[",			//4			
	"Mode ",		//5			
	"Preset T=",	//6			
	" ",			//7			
	"Power P=",		//8			
	"Prop =",		//9
	"Diff =",		//10				
	"Pow MIN =",	//11	
	"Pow MAX =",	//12		
	"Valve  =",		//13		
	"Valve t=",		//14		
	"Slow =",		//15			
	"Fast =",		//16			
	"Lim S=",		//17			
	"Lim F=",		//18			

	"Low  T ",		//19
	"Med  T ",		//20			
	"High T ",		//21			
	"Hysteresis ",	//22			
	"Day/Night ",	//23			
	"Fan lvl ",		//24
	"Fan time ",	//25
	
	"H/C ",			//26	
};
//-----------------------------------------------------------------------------------
#define _scr3_offset	2	
//-----------------------------------------------------------------------------------
extern __farflash TLCDPict _Menu0;
extern __farflash TLCDPict _Menu1;
extern __farflash TLCDPict _Menu2;
extern __farflash TLCDPict _Menu3;
extern __farflash TLCDPict _Menu4;
//-----------------------------------------------------------------------------------
//extern TLCDPictTop Scr_0;
extern TLCDPictTop Scr_4;

extern __farflash TLCDPict_Txt _Txt_0;
extern __farflash TLCDPict_Txt _Txt_1;
extern __farflash TLCDPict_Txt _Txt_2;
extern __farflash TLCDPict_Txt _Txt_3;
extern __farflash TLCDPict_Txt _Txt_4;
extern u8 step;
extern u8 new_step;
extern u8 str[40];
extern u8 str2[20];
//-----------------------------------------------------------------------------------
extern u8 Branch_Number;
extern u8 Current_ID;
extern u8 Common_ID_Mode;
u8 current_pid_num;
u8 current_fan_num;
u8 old_step;
//-----------------------------------------------------------------------------------
typedef struct
{
	u8 x;
	u8 y;
}TPos;
//TPos io_txt[14]
//-----------------------------------------------------------------------------------
TExSTATUS st;
u8 scr3_buff[8]={0};
//TTime Time;
//TExIO io;
//TExPID pid;
u8 sc3_what_to_show=0; // 0-io 1-PID 4-PROG
//TPID pid;
//u8 Manual_Mode=0;
#define Obj_Page_3_Edit Obj[14]	
u8 pos=0;
u8 edit_pos=0;
//-----------------------------------------------------------------------------------
void scr3_init();
void scr3_close();
void scr3_routine();
//-----------------------------------------------------------------------------------
void scr3_show_io()
{
	u8 j;
	u32 t;
	u8 tmp;
	s16 stmp;
	//-----------------------------------------------	
	// IO state
	//-----------------------------------------------	
	lcd_sprintf_P(pdic_alt[0],0,_scr3_offset);
	str[0]=0;
	for(j=0;j<io.num_di;j++)
	{
		t=1<<j;			
		if(io.din & t) stradd(str,"1 ");
		else stradd(str,"0 ");
	}
	lcd_sprintf(str,3,_scr3_offset);
	// POS 0
	lcd_sprintf_P(pdic_alt[1],0,_scr3_offset+1);
	str[0]=0;					
	for(j=0;j<io.num_do;j++)
	{
		t=1<<j;			
		if(io.dout & t) stradd(str,"1 ");
		else stradd(str,"0 ");
		if(pos == j)lcd_set_cursor(3+strlen(str)-2,_scr3_offset+1);
	}
	lcd_sprintf(str,3,_scr3_offset+1);
	//	
	lcd_sprintf_P(pdic_alt[2],0,_scr3_offset+2);
	str[0]=0;
	for(j=0;j<io.num_ai;j++)
	{
		stmp=io.aoutput[j+io.num_ao];//io.ainput[j];
		if(stmp>999)stmp=999;
		ShowTemperature(str2,(s16*)&stmp);				
		stradd(str,str2);
		stradd(str," ");
	}
	lcd_sprintf(str,3,_scr3_offset+2);			
	
	lcd_sprintf_P(pdic_alt[3],0,_scr3_offset+3);
	str[0]=0;
	for(j=0;j<io.num_ao;j++)
	{
		ShowPowerShort(str2,(s16*)&io.aoutput[j]);
		stradd(str,str2);
		if(pos == (io.num_do+j))lcd_set_cursor(3+strlen(str)-1,_scr3_offset+3);					
		stradd(str," ");				
	}		
	lcd_sprintf(str,3,_scr3_offset+3);			
	if(pos>(io.num_do+io.num_ao))pos=io.num_do+io.num_ao-1;
}
//-----------------------------------------------------------------------------------
void scr3_show_pid(u8 num)
{
	u8 j;
	u32 t;
	u8 tmp;
	if(num>=NUM_PID)return;
	//-----------------------------------------------	
	// PID state
	//-----------------------------------------------	
	str[0]=0;
	stradd_P(str,pdic_alt[4]);
	ByteToStr(str2,&pid[num].channel,0);
	stradd(str,str2);	
	stradd(str,"]=");	
	ShowTemperature(str2,&io.aoutput[pid[num].channel+io.num_ao]);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset);
	if(pos == 0)lcd_set_cursor(3,_scr3_offset);		
	
	str[0]=0;
	stradd_P(str,pdic_alt[5]);
	ByteToStr(str2,&pid[num].mode,0);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+1);
	if(pos == 1)lcd_set_cursor(5,_scr3_offset+1);		

	
	str[0]=0;
	stradd_P(str,pdic_alt[6]);
	ShowTemperature(str2,&pid[num].t0);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+2);
	if(pos == 2)lcd_set_cursor(strlen(str),_scr3_offset+2);		

	str[0]=0;
	stradd_P(str,pdic_alt[8]);
	ShowPowerShort(str2,&pid[num].power);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+3);
	if(pos == 3)lcd_set_cursor(strlen(str),_scr3_offset+3);		
	
	str[0]=0;
	stradd_P(str,pdic_alt[9]);
	WordToStr(str2,&pid[num].p,0);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+4);
	if(pos == 4)lcd_set_cursor(strlen(str),_scr3_offset+4);		

	str[0]=0;
	stradd_P(str,pdic_alt[26]);
	ByteToStr(str2,&pid[num].heating_cooling,0);
	stradd(str,str2);	
	lcd_sprintf(str,16,_scr3_offset+4);
	
	str[0]=0;
	stradd_P(str,pdic_alt[10]);
	WordToStr(str2,&pid[num].d,0);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+5);
	if(pos == 5)lcd_set_cursor(strlen(str),_scr3_offset+5);		
	
	str[0]=0;
	stradd_P(str,pdic_alt[11]);
	ShowPowerShort(str2,&pid[num].power_min);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+6);
	if(pos == 6)lcd_set_cursor(strlen(str),_scr3_offset+6);		
	
	str[0]=0;
	stradd_P(str,pdic_alt[12]);
	ShowPowerShort(str2,&pid[num].power_max);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+7);
	if(pos == 7)lcd_set_cursor(strlen(str),_scr3_offset+7);		
	
	str[0]=0;
	stradd_P(str,pdic_alt[13]);
	ShowPowerShort(str2,&pid[num].p3);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+8);
	if(pos == 8)lcd_set_cursor(strlen(str),_scr3_offset+8);		
	
	str[0]=0;
	stradd_P(str,pdic_alt[14]);
	WordToStr(str2,&pid[num].t3max,0);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+9);
	if(pos == 9)lcd_set_cursor(strlen(str),_scr3_offset+9);		

	u16 tmp16;
	
	tmp16=pid[num].PID_POWER_STEP[0]*1000;
	str[0]=0;
	stradd_P(str,pdic_alt[15]);
	WordToStr(str2,&tmp16,0);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+10);
	if(pos == 10)lcd_set_cursor(strlen(str),_scr3_offset+10);		
	
	tmp16=pid[num].PID_POWER_STEP[1]*1000;
	str[0]=0;
	stradd_P(str,pdic_alt[16]);
	WordToStr(str2,&tmp16,0);
	stradd(str,str2);	
	lcd_sprintf(str,12,_scr3_offset+10);
	if(pos == 11)lcd_set_cursor(strlen(str)+12,_scr3_offset+10);		

	tmp16=pid[num].PID_POWER_LIMIT[0];
	str[0]=0;
	stradd_P(str,pdic_alt[17]);
	WordToStr(str2,&tmp16,0);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+11);
	if(pos == 12)lcd_set_cursor(strlen(str),_scr3_offset+11);		

	
	tmp16=pid[num].PID_POWER_LIMIT[1];
	str[0]=0;
	stradd_P(str,pdic_alt[18]);
	WordToStr(str2,&tmp16,0);
	stradd(str,str2);	
	lcd_sprintf(str,12,_scr3_offset+11);
	if(pos == 13)lcd_set_cursor(strlen(str)+12,_scr3_offset+11);		
	
	if(pos>13)pos=13;
}
//-----------------------------------------------------------------------------------
void scr3_show_fan(u8 num)
{
	u8 j;
	u32 t;
	u8 tmp;
	if(num>=MAX_FANCOIL_NUMBER)return;	
	//-----------------------------------------------	
	// FAN state
	//-----------------------------------------------	
	str[0]=0;
	stradd_P(str,pdic_alt[4]);
	ByteToStr(str2,&fan[num].Channel,0);
	stradd(str,str2);	
	stradd(str,"]=");	
	ShowTemperature(str2,&io.ainput[fan[num].Channel]);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset);
	if(pos == 0)lcd_set_cursor(3,_scr3_offset);		
	
	str[0]=0;
	stradd_P(str,pdic_alt[5]);
	ByteToStr(str2,&fan[num].Fan_Mode,0);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+1);
	if(pos == 1)lcd_set_cursor(5,_scr3_offset+1);		

	
	str[0]=0;
	stradd_P(str,pdic_alt[6]);
	ShowTemperature(str2,&fan[num].T);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+2);
	if(pos == 2)lcd_set_cursor(strlen(str),_scr3_offset+2);		

	str[0]=0;
	stradd_P(str,pdic_alt[24]);
	ByteToStr(str2,&fan[num].Fan_Lvl,0);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+3);
	if(pos == 3)lcd_set_cursor(strlen(str),_scr3_offset+3);		
	
	str[0]=0;
	stradd_P(str,pdic_alt[19]);
	ShowTemperature(str2,&fan[num].TLow);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+4);
	if(pos == 4)lcd_set_cursor(strlen(str),_scr3_offset+4);		
	
	str[0]=0;
	stradd_P(str,pdic_alt[20]);
	ShowTemperature(str2,&fan[num].TMedium);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+5);
	if(pos == 5)lcd_set_cursor(strlen(str),_scr3_offset+5);		
	
	str[0]=0;
	stradd_P(str,pdic_alt[21]);
	ShowTemperature(str2,&fan[num].THigh);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+6);
	if(pos == 6)lcd_set_cursor(strlen(str),_scr3_offset+6);		
	
	str[0]=0;
	stradd_P(str,pdic_alt[22]);
	ShowTemperature(str2,&fan[num].Hysteresis);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+7);
	if(pos == 7)lcd_set_cursor(strlen(str),_scr3_offset+7);		
	
	str[0]=0;
	stradd_P(str,pdic_alt[25]);
	WordToStr(str2,&fan[num].Fan_Time,0);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+8);
	if(pos == 8)lcd_set_cursor(strlen(str),_scr3_offset+8);		

	str[0]=0;
	stradd_P(str,pdic_alt[23]);
	ByteToStr(str2,&fan[num].Day_Night,0);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+9);
	if(pos == 9)lcd_set_cursor(strlen(str),_scr3_offset+9);		
/*	
	str[0]=0;
	stradd_P(str,pdic_alt[14]);
	WordToStr(str2,&fan[num].Fan_Time,0);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+9);
	if(pos == 9)lcd_set_cursor(strlen(str),_scr3_offset+9);		

	u16 tmp16;
	
	tmp16=pid[num].PID_POWER_STEP[0]*1000;
	str[0]=0;
	stradd_P(str,pdic_alt[15]);
	WordToStr(str2,&tmp16,0);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+10);
	if(pos == 10)lcd_set_cursor(strlen(str),_scr3_offset+10);		
	
	tmp16=pid[num].PID_POWER_STEP[1]*1000;
	str[0]=0;
	stradd_P(str,pdic_alt[16]);
	WordToStr(str2,&tmp16,0);
	stradd(str,str2);	
	lcd_sprintf(str,12,_scr3_offset+10);
	if(pos == 11)lcd_set_cursor(strlen(str)+12,_scr3_offset+10);		

	tmp16=pid[num].PID_POWER_LIMIT[0];
	str[0]=0;
	stradd_P(str,pdic_alt[17]);
	WordToStr(str2,&tmp16,0);
	stradd(str,str2);	
	lcd_sprintf(str,0,_scr3_offset+11);
	if(pos == 12)lcd_set_cursor(strlen(str),_scr3_offset+11);		

	
	tmp16=pid[num].PID_POWER_LIMIT[1];
	str[0]=0;
	stradd_P(str,pdic_alt[18]);
	WordToStr(str2,&tmp16,0);
	stradd(str,str2);	
	lcd_sprintf(str,12,_scr3_offset+11);
	if(pos == 13)lcd_set_cursor(strlen(str)+12,_scr3_offset+11);		
*/	
	if(pos>8)pos=8;
}
//-----------------------------------------------------------------------------------
void scr3_show_prog()
{}
//-----------------------------------------------------------------------------------
void scr3_show()
{
	switch(sc3_what_to_show)
	{
	case 0:scr3_show_io();break;
	case 1:current_pid_num=0;scr3_show_pid(0);break;
	case 2:current_pid_num=1;scr3_show_pid(1);break;
	case 3:current_fan_num=0;scr3_show_fan(0);break;
	case 4:current_fan_num=1;scr3_show_fan(1);break;	
	}
}
//-----------------------------------------------------------------------------------
void scr3_show_sub_menu()
{
//	Obj[5]=_Page_3_IO;	
//	Obj[6]=_Page_3_PID_0;	
//	Obj[7]=_Page_3_PID_1;	
//	Obj[8]=_Page_3_PID_2;	
//	Obj[9]=_Page_3_PROG;		
	switch(sc3_what_to_show)
	{
	case 0:
		new_step=1;
		if(Obj[5].Stat!=1){Obj[5].Stat=1; show_single_bmp(&Obj[5],0);	}		
		if(Obj[6].Stat!=0){Obj[6].Stat=0; show_single_bmp(&Obj[6],0);	}		
		if(Obj[7].Stat!=0){Obj[7].Stat=0; show_single_bmp(&Obj[7],0);	}		
		if(Obj[8].Stat!=0){Obj[8].Stat=0; show_single_bmp(&Obj[8],0);	}		
		if(Obj[9].Stat!=0){Obj[9].Stat=0; show_single_bmp(&Obj[9],0);	}		
		break;
	case 1:
		new_step=2;
		current_pid_num=0;		
		if(Obj[5].Stat!=0){Obj[5].Stat=0; show_single_bmp(&Obj[5],0);	}		
		if(Obj[6].Stat!=1){Obj[6].Stat=1; show_single_bmp(&Obj[6],0);	}		
		if(Obj[7].Stat!=0){Obj[7].Stat=0; show_single_bmp(&Obj[7],0);	}		
		if(Obj[8].Stat!=0){Obj[8].Stat=0; show_single_bmp(&Obj[8],0);	}		
		if(Obj[9].Stat!=0){Obj[9].Stat=0; show_single_bmp(&Obj[9],0);	}		
		break;
	case 2:
		new_step=3;
		current_pid_num=1;		
		if(Obj[5].Stat!=0){Obj[5].Stat=0; show_single_bmp(&Obj[5],0);	}		
		if(Obj[6].Stat!=0){Obj[6].Stat=0; show_single_bmp(&Obj[6],0);	}		
		if(Obj[7].Stat!=1){Obj[7].Stat=1; show_single_bmp(&Obj[7],0);	}		
		if(Obj[8].Stat!=0){Obj[8].Stat=0; show_single_bmp(&Obj[8],0);	}		
		if(Obj[9].Stat!=0){Obj[9].Stat=0; show_single_bmp(&Obj[9],0);	}		
		break;
	case 3:
		new_step=4;
		current_fan_num=0;	
		if(Obj[5].Stat!=0){Obj[5].Stat=0; show_single_bmp(&Obj[5],0);	}		
		if(Obj[6].Stat!=0){Obj[6].Stat=0; show_single_bmp(&Obj[6],0);	}		
		if(Obj[7].Stat!=0){Obj[7].Stat=0; show_single_bmp(&Obj[7],0);	}		
		if(Obj[8].Stat!=1){Obj[8].Stat=1; show_single_bmp(&Obj[8],0);	}		
		if(Obj[9].Stat!=0){Obj[9].Stat=0; show_single_bmp(&Obj[9],0);	}		
		break;
	case 4:
		new_step=5;
		current_fan_num=1;
		if(Obj[5].Stat!=0){Obj[5].Stat=0; show_single_bmp(&Obj[5],0);	}		
		if(Obj[6].Stat!=0){Obj[6].Stat=0; show_single_bmp(&Obj[6],0);	}		
		if(Obj[7].Stat!=0){Obj[7].Stat=0; show_single_bmp(&Obj[7],0);	}		
		if(Obj[8].Stat!=0){Obj[8].Stat=0; show_single_bmp(&Obj[8],0);	}		
		if(Obj[9].Stat!=1){Obj[9].Stat=1; show_single_bmp(&Obj[9],0);	}		
		break;
	}
}
//-----------------------------------------------------------------------------------
void scr3_IO()
{
	sc3_what_to_show=0;
	memset(&io,0,sizeof(io));
	scr3_show_sub_menu();
	pos=0;
	edit_pos=0;	
}
//-----------------------------------------------------------------------------------
void scr3_PID_0()
{
	sc3_what_to_show=1;
//	memset(&pid,0,sizeof(pid));	
	scr3_show_sub_menu();
}
//-----------------------------------------------------------------------------------
void scr3_PID_1()
{
	sc3_what_to_show=2;
//	memset(&pid,0,sizeof(pid));	
	scr3_show_sub_menu();
}
//-----------------------------------------------------------------------------------
void scr3_PID_2()
{
	sc3_what_to_show=3;
//	memset(&pid,0,sizeof(pid));	
	scr3_show_sub_menu();
}
//-----------------------------------------------------------------------------------
void scr3_PROG()
{
	sc3_what_to_show=4;
//	memset(&pid,0,sizeof(pid));	
	scr3_show_sub_menu();
}
//-----------------------------------------------------------------------------------
void scr3_up()
{
	if(pos!=0)pos--;	
	if(MenuRegs.Manual_Mode)scr3_show();
}
//-----------------------------------------------------------------------------------
void scr3_down()
{
	if(pos<100)pos++;	
	if(MenuRegs.Manual_Mode)scr3_show();
}
//-----------------------------------------------------------------------------------
void scr3_plus()
{
	u32 tmp;
//	u8 i;
	if(MenuRegs.Manual_Mode)
	{
		// IO
		switch(sc3_what_to_show)
		{
		case 0:
			if(pos<(io.num_do))
			{
				tmp=1<<pos;
				io.dout^=tmp;			
				old_step=step;
				new_step=10;	
				Button_no_update_time=200;	
			}
			else
			{
				if(pos==(io.num_do))
				{
					if(io.aoutput[0]<990)io.aoutput[0]+=10;
					else io.aoutput[0]=999;
					old_step=step;
					new_step=11;			
					Button_no_update_time=200;	
				}
			}
			break;
			
		case 1:
		case 2:			
			current_pid_num=sc3_what_to_show-1;
			switch(pos)
			{
			case 0:if(pid[current_pid_num].channel<2)pid[current_pid_num].channel++;break;
			case 1:if(pid[current_pid_num].mode!=1)pid[current_pid_num].mode=1;break;
			case 2:if(pid[current_pid_num].t0<500)pid[current_pid_num].t0+=1;else pid[current_pid_num].t0=500; break;			
			case 3:if(pid[current_pid_num].power<990)pid[current_pid_num].power+=10; else pid[current_pid_num].power=999;break;			
			case 4:if(pid[current_pid_num].p<990)pid[current_pid_num].p+=10; else pid[current_pid_num].p=999;break;			
			case 5:if(pid[current_pid_num].d<990)pid[current_pid_num].d+=10; else pid[current_pid_num].d=999;break;			
			case 6:if(pid[current_pid_num].power_min<990)pid[current_pid_num].power_min+=10; else pid[current_pid_num].power_min=999;break;			
			case 7:if(pid[current_pid_num].power_max<990)pid[current_pid_num].power_max+=10; else pid[current_pid_num].power_max=999;break;						
			case 8:if(pid[current_pid_num].p3<990)pid[current_pid_num].p3+=10; else pid[current_pid_num].p3=999;break;						
			case 9:if(pid[current_pid_num].t3max<500)pid[current_pid_num].t3max+=1; else pid[current_pid_num].t3max=500;break;						
			case 10:if(pid[current_pid_num].PID_POWER_STEP[0]<0.9)pid[current_pid_num].PID_POWER_STEP[0]+=0.001; else pid[current_pid_num].PID_POWER_STEP[0]=0.9;break;						
			case 11:if(pid[current_pid_num].PID_POWER_STEP[1]<0.9)pid[current_pid_num].PID_POWER_STEP[1]+=0.001; else pid[current_pid_num].PID_POWER_STEP[1]=0.9;break;						
			case 12:if(pid[current_pid_num].PID_POWER_LIMIT[0]<999)pid[current_pid_num].PID_POWER_LIMIT[0]+=1; else pid[current_pid_num].PID_POWER_LIMIT[0]=999;break;						
			case 13:if(pid[current_pid_num].PID_POWER_LIMIT[1]<999)pid[current_pid_num].PID_POWER_LIMIT[1]+=1; else pid[current_pid_num].PID_POWER_LIMIT[1]=999;break;									
			}
			old_step=step;
			new_step=20;						
			Button_no_update_time=200;
			break;
		case 3:			
			current_fan_num=0;
			switch(pos)
			{
			case 0:if(fan[current_fan_num].Channel<2)fan[current_fan_num].Channel++;break;
			case 1:if(fan[current_fan_num].Fan_Mode!=1)fan[current_fan_num].Fan_Mode=1;break;
			case 2:if(fan[current_fan_num].T<500)fan[current_fan_num].T+=1;else fan[current_fan_num].T=500; break;			
			case 3:if(fan[current_fan_num].Fan_Lvl<3)fan[current_fan_num].Fan_Lvl+=1; else fan[current_fan_num].Fan_Lvl=3;break;			
			case 4:if(fan[current_fan_num].TLow<500)fan[current_fan_num].TLow+=1; else fan[current_fan_num].TLow=500;break;			
			case 5:if(fan[current_fan_num].TMedium<500)fan[current_fan_num].TMedium+=1; else fan[current_fan_num].TMedium=500;break;			
			case 6:if(fan[current_fan_num].THigh<500)fan[current_fan_num].THigh+=1; else fan[current_fan_num].THigh=500;break;			
			case 7:if(fan[current_fan_num].Hysteresis<500)fan[current_fan_num].Hysteresis+=1; else fan[current_fan_num].Hysteresis=500;break;						
			case 8:if(fan[current_fan_num].Fan_Time<10)fan[current_fan_num].Fan_Time+=1; else fan[current_fan_num].Fan_Time=10;break;						
			case 9:if(fan[current_fan_num].Day_Night!=1)fan[current_fan_num].Day_Night=1;break;						
			}
			old_step=step;
			new_step=21;						
			Button_no_update_time=200;			
			break;
		}
		scr3_show();
	}
}
//-----------------------------------------------------------------------------------
void scr3_minus()
{
	u32 tmp;
//	u8 i;
	if(MenuRegs.Manual_Mode)
	{
		switch(sc3_what_to_show)
		{
			// IO
		case 0:
			if(pos<(io.num_do))
			{
				tmp=1<<pos;
				io.dout^=tmp;
				old_step=step;
				new_step=10;
				Button_no_update_time=200;	
			}
			else
			{
				if(pos==(io.num_do))
				{
					if(io.aoutput[0]>=10)io.aoutput[0]-=10;
					else io.aoutput[0]=0;
					old_step=step;			
					new_step=11;	
					Button_no_update_time=200;	
				}
			}
			break;
		case 1:
		case 2:			
			current_pid_num=sc3_what_to_show-1;
			switch(pos)
			{
			case 0:if(pid[current_pid_num].channel!=0)pid[current_pid_num].channel--;break;
			case 1:if(pid[current_pid_num].mode!=0)pid[current_pid_num].mode=0;break;
			case 2:if(pid[current_pid_num].t0>140)pid[current_pid_num].t0-=1;else pid[current_pid_num].t0=140; break;			
			case 3:if(pid[current_pid_num].power>10)pid[current_pid_num].power-=10; else pid[current_pid_num].power=0;break;			
			case 4:if(pid[current_pid_num].p>10)pid[current_pid_num].p-=10; else pid[current_pid_num].p=10;break;			
			case 5:if(pid[current_pid_num].d>10)pid[current_pid_num].d-=10; else pid[current_pid_num].d=10;break;			
			case 6:if(pid[current_pid_num].power_min>10)pid[current_pid_num].power_min-=10; else pid[current_pid_num].power_min=10;break;			
			case 7:if(pid[current_pid_num].power_max>10)pid[current_pid_num].power_max-=10; else pid[current_pid_num].power_max=10;break;						
			case 8:if(pid[current_pid_num].p3>10)pid[current_pid_num].p3-=10; else pid[current_pid_num].p3=10;break;						
			case 9:if(pid[current_pid_num].t3max>1)pid[current_pid_num].t3max-=1; else pid[current_pid_num].t3max=0;break;						
			case 10:if(pid[current_pid_num].PID_POWER_STEP[0]>0.001)pid[current_pid_num].PID_POWER_STEP[0]-=0.001; else pid[current_pid_num].PID_POWER_STEP[0]=0;break;						
			case 11:if(pid[current_pid_num].PID_POWER_STEP[1]>0.001)pid[current_pid_num].PID_POWER_STEP[1]-=0.001; else pid[current_pid_num].PID_POWER_STEP[1]=0;break;						
			case 12:if(pid[current_pid_num].PID_POWER_LIMIT[0]>1)pid[current_pid_num].PID_POWER_LIMIT[0]-=1; else pid[current_pid_num].PID_POWER_LIMIT[0]=0;break;						
			case 13:if(pid[current_pid_num].PID_POWER_LIMIT[1]>1)pid[current_pid_num].PID_POWER_LIMIT[1]-=1; else pid[current_pid_num].PID_POWER_LIMIT[1]=0;break;									
			}
			old_step=step;
			new_step=20;						
			Button_no_update_time=200;
			break;
		case 3:			
			current_fan_num=0;
			switch(pos)
			{
			case 0:if(fan[current_fan_num].Channel>0)fan[current_fan_num].Channel--;break;
			case 1:if(fan[current_fan_num].Fan_Mode!=0)fan[current_fan_num].Fan_Mode=0;break;
			case 2:if(fan[current_fan_num].T>0)fan[current_fan_num].T-=1;else fan[current_fan_num].T=0; break;			
			case 3:if(fan[current_fan_num].Fan_Lvl>0)fan[current_fan_num].Fan_Lvl-=1; else fan[current_fan_num].Fan_Lvl=0;break;			
			case 4:if(fan[current_fan_num].TLow>0)fan[current_fan_num].TLow-=1; else fan[current_fan_num].TLow=0;break;			
			case 5:if(fan[current_fan_num].TMedium>0)fan[current_fan_num].TMedium-=1; else fan[current_fan_num].TMedium=0;break;			
			case 6:if(fan[current_fan_num].THigh>0)fan[current_fan_num].THigh-=1; else fan[current_fan_num].THigh=0;break;			
			case 7:if(fan[current_fan_num].Hysteresis>0)fan[current_fan_num].Hysteresis-=1; else fan[current_fan_num].Hysteresis=0;break;						
			case 8:if(fan[current_fan_num].Fan_Time>0)fan[current_fan_num].Fan_Time-=1; else fan[current_fan_num].Fan_Time=0;break;						
			case 9:if(fan[current_fan_num].Day_Night!=0)fan[current_fan_num].Day_Night=0;break;
			}
			old_step=step;
			new_step=21;						
			Button_no_update_time=200;			
			break;
		}
		scr3_show();
	}	
}
//-----------------------------------------------------------------------------------
void scr3_edit_update()
{
	if((MenuRegs.Manual_Mode)&&(Obj_Page_3_Edit.Stat!=1)){Obj_Page_3_Edit.Stat=1;show_single_bmp(&Obj_Page_3_Edit,0);}
	if((MenuRegs.Manual_Mode==0)&&(Obj_Page_3_Edit.Stat!=0)){Obj_Page_3_Edit.Stat=0;show_single_bmp(&Obj_Page_3_Edit,0);}
	if(MenuRegs.Manual_Mode)
	{						
		 lcd_write_command(0x9F); // 10011111
		 lcd_write_command(0xA7); // 10100111		
	}
	else
	{
		lcd_write_command(0x9c); // 10011111
	}
	scr3_show_sub_menu();	
}
//-----------------------------------------------------------------------------------
void scr3_edit()
{
	if(MenuRegs.Manual_Mode)MenuRegs.Manual_Mode=0;
	else MenuRegs.Manual_Mode=1;
	scr3_edit_update();
	old_step=step;		
	new_step=6;	
	Button_no_update_time=200;	
}
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_3_IO=
{	
	0,117,67,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr3_IO,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_3_PID_0=
{	
	6,117,68,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr3_PID_0,
	NULL,
};

//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_3_PID_1=
{	
	12,117,69,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr3_PID_1,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_3_PID_2=
{	
	18,117,70,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr3_PID_2,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_3_PROG=
{	
	24,117,71,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr3_PROG,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_3_Up=
{	
	25,56,42,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	scr3_up,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_3_Down=
{	
	25,76,43,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	scr3_down,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_3_Plus=
{	
	25,16,44,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	scr3_plus,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_3_Minus=
{	
	25,36,45,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	scr3_minus,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_3_Edit=
{	
	25,96,72,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr3_edit,
	NULL,
};

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_3=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	15,
	0,	
	scr3_init,
	scr3_routine,
	scr3_close,		
};
//-----------------------------------------------------------------------------------
void scr3_init()
{
//	u8 i;
	Branch_Number=3;
	new_step=step=0;
	Obj[0]=_Menu0;	
	Obj[1]=_Menu1;	
	Obj[2]=_Menu2;	
	Obj[3]=_Menu3;		
	Obj[4]=_Menu4;	
	
	Obj[5]=_Page_3_IO;	
	Obj[6]=_Page_3_PID_0;	
	Obj[7]=_Page_3_PID_1;	
	Obj[8]=_Page_3_PID_2;	
	Obj[9]=_Page_3_PROG;	

	Obj[10]=_Page_3_Up;	
	Obj[11]=_Page_3_Down;	
	Obj[12]=_Page_3_Plus;	
	Obj[13]=_Page_3_Minus;	
	Obj[14]=_Page_3_Edit;	
	
	Obj[3].Stat=1;
	scr3_edit_update();
	scr3_show_sub_menu();
//	MenuRegs.Manual_Mode=0;
}
//-----------------------------------------------------------------------------------
void scr3_close()
{
	u8 i;
	lcd_write_command(0x9c); // 10011100
	for(i=0;i<Scr_1.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
	lcd_clear_text();
}
//-----------------------------------------------------------------------------------
void scr3_routine()
{
//	u8 tmp,i;		
//	u16 temp;
//	u8 tmp0;//,tmp1,tmp2; lc
//	u8 old_stat;
//	s16 temperature;
//	u8 i,j;
//	u32 t;
//	u8 tmp;
	
	if(FT_Time!=0)return;
	FT_Time=500;
	if(page_offset!=PAGE_0_OFFSET)return;
	if(Common_ID_Mode)return; // Exit if common mode selected
	lcd_clear_text();		
	//-----------------------------------------------	
	scr3_show();
	//-----------------------------------------------			
}
//-----------------------------------------------------------------------------------
void Schedule_N3()
{
//	u16 i,tmp;
	u8 len;
	M_state_machine();
	if((M.status==st_none)||(M.status==st_complete))
	{		
		if((M.error==0)&&(M.rxnew==1))
		{
			M.rxnew=0;
			switch(M_rx.field.com.bit.com)
			{
				case com_get_register:		
					if(Button_no_update_time==0)
					{
						memcpy(&addr,&M_rx.field.d[0],2);		
						len=M_rx.field.d[2];
						memcpy(&reg_data[addr],&M_rx.field.d[3],len);	
					}
				break;				
/*				
				case com_get_stat:		
//					Status=(TExSTATUS*)&M_rx.field.d[8];	
					memcpy(&scr3_buff,&M_rx.field.d[0],sizeof(scr3_buff));
					ft=Status->ft;
				break;				
				case com_get_io:			
					memcpy(&io,&M_rx.field.d[0],M_rx.field.len);
				break;
				case com_get_pid_0:			
					memcpy(&pid[0],&M_rx.field.d[0],M_rx.field.len);
				break;
				case com_get_pid_1:			
					memcpy(&pid[1],&M_rx.field.d[0],M_rx.field.len);
				break;
				case com_set_manual:			
					MenuRegs.Manual_Mode=M_rx.field.d[0];
					scr3_edit_update();
				break;				
*/				
				
			}
		}
		// TX section
		if(M_SCH_Time==0)
		{			
			if(new_step!=0){
				step=new_step;
				new_step=0;
			}
			if(M_buff_sign)
			{
				M_buff_sign=0;
				M_tx=M_buff;
			//	memcpy(&M_tx,&rx,sizeof(M_tx));
//				BUZZ_Time=50;
				M.txnew=1;
				M.txcount=0;
				M.status=st_sending;		
				M.rxnew=0;
				M.rxcount=0;		
				M.error=0;
				M.done=0;				
			}
			else
				if(Time0==0)
				switch(step)
				{
					// Data update functions
					case 0:
						M_Get_Controller_Register(Current_ID,&MenuRegs.Manual_Mode,1);						
						M_SCH_Time=200;					
					break;
					case 1:
						M_Get_Controller_Register(Current_ID,&io,sizeof(io));						
						M_SCH_Time=200;					
					break;
					case 2:
						M_Get_Controller_Register(Current_ID,&pid[0],sizeof(pid[0]));
						M_SCH_Time=200;					
					break;
					case 3:
						M_Get_Controller_Register(Current_ID,&pid[1],sizeof(pid[1]));
						M_SCH_Time=200;					
					break;
					case 4:
						M_Get_Controller_Register(Current_ID,&fan[0],sizeof(fan[0]));						
						M_SCH_Time=200;					
					break;
/*					
					case 5:
//						step++;
//						M_Get_Controller_PID(2,Current_ID,Current_ID);	
//						M_Set_Controller_Register(Current_ID,&io,sizeof(io)));						
//						step=0;					
						M_SCH_Time=100;					
					break;
*/					
					case 6:
						M_Set_Controller_Register(Current_ID,&MenuRegs.Manual_Mode,1);
						step=old_step;					
						M_SCH_Time=100;					
					break;

					// Dout					
					case 10:
						M_Set_Controller_Register(Current_ID,&io.dout,sizeof(io.dout));
						step=old_step;
						M_SCH_Time=100;					
					break;					
					// Aout					
					case 11:
						M_Set_Controller_Register(Current_ID,&io.aoutput[0],2*io.num_ao);
						step=old_step;
						M_SCH_Time=100;					
					break;					
					//----------------------------------------------------------
					// PID
					//----------------------------------------------------------
					case 20:
						M_Set_Controller_Register(Current_ID,&pid[current_pid_num],sizeof(pid[current_pid_num]));
						step=old_step;
						M_SCH_Time=100;					
					break;					
					//----------------------------------------------------------
					// FAN
					//----------------------------------------------------------
					case 21:
						M_Set_Controller_Register(Current_ID,&fan[0],sizeof(fan[0]));
						step=old_step;
						M_SCH_Time=100;					
					break;					
/*
					case 11:
						switch(sc3_what_to_show)
						{
						case 1:M_Set_Controller_Register(Current_ID,&pid[0],sizeof(pid[0])); break;
						case 2:M_Set_Controller_Register(Current_ID,&pid[1],sizeof(pid[1])); break;
//						case 3:M_Set_Controller_PID(2,Current_ID,&pid[0]);break;
						}												
						step=0;					
						M_SCH_Time=100;					
					break;				
*/					
				default:
					step=0;
					break;
				}
		}
		
	}
	
}

//-----------------------------------------------------------------------------------

