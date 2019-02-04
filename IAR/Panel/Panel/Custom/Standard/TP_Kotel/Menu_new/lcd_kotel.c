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
void scr0_1_init();
void scr0_1_routine();
void scr0_1_close();
//-----------------------------------------------------------------------------------
#define KOT_OFF_X		0
#define KOT_OFF_Y		2
//-----------------------------------------------------------------------------------
extern __farflash TLCDPict _Menu0;
extern __farflash TLCDPict _Menu1;
extern __farflash TLCDPict _Menu2;
extern __farflash TLCDPict _Menu3;
extern __farflash TLCDPict _Menu4;

extern __farflash TLCDPict Tab_Menu0;
extern __farflash TLCDPict Tab_Menu1;
extern __farflash TLCDPict Tab_Menu2;
extern __farflash TLCDPict Tab_Menu3;
extern __farflash TLCDPict Tab_Menu4;
//-----------------------------------------------------------------------------------
extern TLCDPictTop Scr_13;
extern __farflash TLCDPict_Txt _Txt_0;
extern __farflash TLCDPict_Txt _Txt_1;
extern __farflash TLCDPict_Txt _Txt_2;
extern __farflash TLCDPict_Txt _Txt_3;
extern __farflash TLCDPict_Txt _Txt_4;
//-----------------------------------------------------------------------------------
__farflash u8	eng_kot_str[][25]=
{
	"Fuel  ",				//0
	"Mode  ",				//1
	"Smoke ",				//2
	"FAN 0",				//3
	"FAN 1",				//4
	"Speed ",				//5
	"ON  s ",				//6	
	"OFF s ",				//7	
	"Screw 0",				//8
	"Screw 1",				//9
	"Ena   ",				//10	
	"<<",					//11
	"   ",					//12
	"T ", 					//13
};
//-----------------------------------------------------------------------------------
void M_Get_Controller_Work(u8 id);
void upc_Set_Controller_In_Params(u8 id,u8 addr,u8* value,u8 len);
void regs_to_work();
void work_to_regs();

extern u8 str[40];
extern u8 str2[20];
extern u8 Common_ID_Mode;
extern u8 Switch_To_ID_1;
extern u8 step;
extern u8 new_step;
extern u8 Current_ID;
extern u8 Branch_Number;
extern  u16 Store_Time;
extern u8 device_ptr;
extern u8 device_id[MAX_DEVICES_NUM];
extern u8 Start_Up_Time;
//-----------------------------------------------------------------------------------
eu8 pos;
u8 kotel_mode=1;
u8 kotel_fuel=0;
//-----------------------------------------------------------------------------------
void scr0_1_show()
{
	lcd_clear_text();
	// Fuel
	str[0]=0;		
	strcat2(str,(u8*)eng_kot_str[0]);
	ByteToStr(str2,&kotel.fuel,0);
	strcat((char*)str,(char*)str2);
	if(pos==0)strcat2(str,(u8*)eng_kot_str[11]);else strcat2(str,(u8*)eng_kot_str[12]);// Cursor
	lcd_sprintf(str,KOT_OFF_X,KOT_OFF_Y+0);
	// Mode
	str[0]=0;		
	strcat2(str,(u8*)eng_kot_str[1]);
	ByteToStr(str2,&kotel_mode,0);
	strcat((char*)str,(char*)str2);
	if(pos==1)strcat2(str,(u8*)eng_kot_str[11]);else strcat2(str,(u8*)eng_kot_str[12]);// Cursor
		lcd_sprintf(str,KOT_OFF_X,KOT_OFF_Y+1);
		
	if((kotel_mode>=1)&&(kotel_mode<5))
	{
		// T
		str[0]=0;		
		strcat2(str,(u8*)eng_kot_str[13]);
		ShowTemperature(str2,&kotel.p[kotel.fuel][kotel_mode-1].t);
		strcat((char*)str,(char*)str2);
		if(pos==2)strcat2(str,(u8*)eng_kot_str[11]);else strcat2(str,(u8*)eng_kot_str[12]);// Cursor
		lcd_sprintf(str,KOT_OFF_X+12,KOT_OFF_Y+0);
	
		// Smoke
		str[0]=0;		
		strcat2(str,(u8*)eng_kot_str[2]);
		ByteToStr(str2,&kotel.p[kotel.fuel][kotel_mode-1].smoke_speed,0);
		strcat((char*)str,(char*)str2);
		if(pos==3)strcat2(str,(u8*)eng_kot_str[11]);else strcat2(str,(u8*)eng_kot_str[12]);// Cursor
		lcd_sprintf(str,KOT_OFF_X+12,KOT_OFF_Y+1);
	
		// FAN Number 1
		lcd_sprintf_P(eng_kot_str[3],KOT_OFF_X,KOT_OFF_Y+3);
		// FAN Speed
		str[0]=0;		
		strcat2(str,(u8*)eng_kot_str[5]);
		ByteToStr(str2,&kotel.p[kotel.fuel][kotel_mode-1].fan_speed[0],0);
		strcat((char*)str,(char*)str2);
		if(pos==4)strcat2(str,(u8*)eng_kot_str[11]);else strcat2(str,(u8*)eng_kot_str[12]);// Cursor
		lcd_sprintf(str,KOT_OFF_X,KOT_OFF_Y+4);
		// FAN ON
		str[0]=0;		
		strcat2(str,(u8*)eng_kot_str[6]);
		ByteToStr(str2,&kotel.p[kotel.fuel][kotel_mode-1].fan_on[0],0);
		strcat((char*)str,(char*)str2);
		if(pos==5)strcat2(str,(u8*)eng_kot_str[11]);else strcat2(str,(u8*)eng_kot_str[12]);// Cursor
		lcd_sprintf(str,KOT_OFF_X,KOT_OFF_Y+5);
		// FAN OFF
		str[0]=0;		
		strcat2(str,(u8*)eng_kot_str[7]);
		ByteToStr(str2,&kotel.p[kotel.fuel][kotel_mode-1].fan_off[0],0);
		strcat((char*)str,(char*)str2);
		if(pos==6)strcat2(str,(u8*)eng_kot_str[11]);else strcat2(str,(u8*)eng_kot_str[12]);// Cursor
		lcd_sprintf(str,KOT_OFF_X,KOT_OFF_Y+6);
		
		// FAN Number 2
		lcd_sprintf_P(eng_kot_str[4],KOT_OFF_X,KOT_OFF_Y+8);
		// FAN Speed
		str[0]=0;		
		strcat2(str,(u8*)eng_kot_str[5]);
		ByteToStr(str2,&kotel.p[kotel.fuel][kotel_mode-1].fan_speed[1],0);
		strcat((char*)str,(char*)str2);
		if(pos==7)strcat2(str,(u8*)eng_kot_str[11]);else strcat2(str,(u8*)eng_kot_str[12]);// Cursor
		lcd_sprintf(str,KOT_OFF_X,KOT_OFF_Y+9);
		// FAN ON
		str[0]=0;		
		strcat2(str,(u8*)eng_kot_str[6]);
		ByteToStr(str2,&kotel.p[kotel.fuel][kotel_mode-1].fan_on[1],0);
		strcat((char*)str,(char*)str2);
		if(pos==8)strcat2(str,(u8*)eng_kot_str[11]);else strcat2(str,(u8*)eng_kot_str[12]);// Cursor
		lcd_sprintf(str,KOT_OFF_X,KOT_OFF_Y+10);
		// FAN OFF
		str[0]=0;		
		strcat2(str,(u8*)eng_kot_str[7]);
		ByteToStr(str2,&kotel.p[kotel.fuel][kotel_mode-1].fan_off[1],0);
		strcat((char*)str,(char*)str2);
		if(pos==9)strcat2(str,(u8*)eng_kot_str[11]);else strcat2(str,(u8*)eng_kot_str[12]);// Cursor
		lcd_sprintf(str,KOT_OFF_X,KOT_OFF_Y+11);
		
		// Screw Number 1
		lcd_sprintf_P(eng_kot_str[8],KOT_OFF_X+12,KOT_OFF_Y+3);
		// Screw Enable
		str[0]=0;		
		strcat2(str,(u8*)eng_kot_str[10]);
		ByteToStr(str2,&kotel.p[kotel.fuel][kotel_mode-1].shnek_ena[0],0);
		strcat((char*)str,(char*)str2);
		if(pos==10)strcat2(str,(u8*)eng_kot_str[11]);else strcat2(str,(u8*)eng_kot_str[12]);// Cursor
		lcd_sprintf(str,KOT_OFF_X+12,KOT_OFF_Y+4);
		// Screw ON
		str[0]=0;		
		strcat2(str,(u8*)eng_kot_str[6]);
		ByteToStr(str2,&kotel.p[kotel.fuel][kotel_mode-1].shnek_on[0],0);
		strcat((char*)str,(char*)str2);
		if(pos==11)strcat2(str,(u8*)eng_kot_str[11]);else strcat2(str,(u8*)eng_kot_str[12]);// Cursor
		lcd_sprintf(str,KOT_OFF_X+12,KOT_OFF_Y+5);
		// Screw OFF
		str[0]=0;		
		strcat2(str,(u8*)eng_kot_str[7]);
		ByteToStr(str2,&kotel.p[kotel.fuel][kotel_mode-1].shnek_off[0],0);
		strcat((char*)str,(char*)str2);
		if(pos==12)strcat2(str,(u8*)eng_kot_str[11]);else strcat2(str,(u8*)eng_kot_str[12]);// Cursor
		lcd_sprintf(str,KOT_OFF_X+12,KOT_OFF_Y+6);	
		
		// Screw Number 2
		lcd_sprintf_P(eng_kot_str[9],KOT_OFF_X+12,KOT_OFF_Y+8);
		// Screw Enable
		str[0]=0;		
		strcat2(str,(u8*)eng_kot_str[10]);
		ByteToStr(str2,&kotel.p[kotel.fuel][kotel_mode-1].shnek_ena[1],0);
		strcat((char*)str,(char*)str2);
		if(pos==13)strcat2(str,(u8*)eng_kot_str[11]);else strcat2(str,(u8*)eng_kot_str[12]);// Cursor
		lcd_sprintf(str,KOT_OFF_X+12,KOT_OFF_Y+9);
		// Screw ON
		str[0]=0;		
		strcat2(str,(u8*)eng_kot_str[6]);
		ByteToStr(str2,&kotel.p[kotel.fuel][kotel_mode-1].shnek_on[1],0);
		strcat((char*)str,(char*)str2);
		if(pos==14)strcat2(str,(u8*)eng_kot_str[11]);else strcat2(str,(u8*)eng_kot_str[12]);// Cursor
		lcd_sprintf(str,KOT_OFF_X+12,KOT_OFF_Y+10);
		// Screw OFF
		str[0]=0;		
		strcat2(str,(u8*)eng_kot_str[7]);
		ByteToStr(str2,&kotel.p[kotel.fuel][kotel_mode-1].shnek_off[1],0);
		strcat((char*)str,(char*)str2);
		if(pos==15)strcat2(str,(u8*)eng_kot_str[11]);else strcat2(str,(u8*)eng_kot_str[12]);// Cursor
		lcd_sprintf(str,KOT_OFF_X+12,KOT_OFF_Y+11);		
	}
	if((kotel_mode==5))
	{
		// Smoke
		str[0]=0;		
		strcat2(str,(u8*)eng_kot_str[2]);
		ByteToStr(str2,&kotel.smoke_speed[kotel.fuel],0);
		strcat((char*)str,(char*)str2);
		if(pos==2)strcat2(str,(u8*)eng_kot_str[11]);else strcat2(str,(u8*)eng_kot_str[12]);// Cursor
		lcd_sprintf(str,KOT_OFF_X+0,KOT_OFF_Y+2);
	}	
}
//-----------------------------------------------------------------------------------
void scr0_1_up()
{
	if(pos!=0)pos--;	
	scr0_1_show();
}
//-----------------------------------------------------------------------------------
void scr0_1_down()
{
	if((kotel_mode>=1)&&(kotel_mode<5))
	{
		if(pos<15)pos++;	
		scr0_1_show();
	}
	if((kotel_mode==5))
	{
		if(pos<2)pos++;	
		scr0_1_show();
	}
}
//-----------------------------------------------------------------------------------
#define	obj_mode_1 Obj[9]	
#define	obj_mode_2 Obj[10]
#define	obj_mode_3 Obj[11]
#define	obj_mode_4 Obj[12]
#define	obj_mode_5 Obj[13]
//-----------------------------------------------------------------------------------
void scr0_1_set_mode(u8 mode)
{
	u8 old;
	kotel_mode=mode;	
	old=obj_mode_1.Stat; obj_mode_1.Stat=0;	if(kotel_mode==1)obj_mode_1.Stat=1;	if(obj_mode_1.Stat!=old)show_single_bmp(&obj_mode_1,0);
	old=obj_mode_2.Stat; obj_mode_2.Stat=0;	if(kotel_mode==2)obj_mode_2.Stat=1;	if(obj_mode_2.Stat!=old)show_single_bmp(&obj_mode_2,0);
	old=obj_mode_3.Stat; obj_mode_3.Stat=0;	if(kotel_mode==3)obj_mode_3.Stat=1;	if(obj_mode_3.Stat!=old)show_single_bmp(&obj_mode_3,0);
	old=obj_mode_4.Stat; obj_mode_4.Stat=0;	if(kotel_mode==4)obj_mode_4.Stat=1;	if(obj_mode_4.Stat!=old)show_single_bmp(&obj_mode_4,0);
	old=obj_mode_5.Stat; obj_mode_5.Stat=0;	if(kotel_mode==5)obj_mode_5.Stat=1;	if(obj_mode_5.Stat!=old)show_single_bmp(&obj_mode_5,0);	
}
//-----------------------------------------------------------------------------------
void scr0_1_plus()
{
	if((kotel_mode>=1)&&(kotel_mode<5))
	{
		switch(pos)
		{
		case 0:if(kotel.fuel<(MAX_KOTEL_FUELS-1))kotel.fuel++;break;
		case 1:if(kotel_mode<4)kotel_mode++;scr0_1_set_mode(kotel_mode);break;
		case 2:if(kotel.p[kotel.fuel][kotel_mode-1].t<400)kotel.p[kotel.fuel][kotel_mode-1].t+=10;break;
		case 3:if(kotel.p[kotel.fuel][kotel_mode-1].smoke_speed<100)kotel.p[kotel.fuel][kotel_mode-1].smoke_speed++;break;
	
		case 4:if(kotel.p[kotel.fuel][kotel_mode-1].fan_speed[0]<100)kotel.p[kotel.fuel][kotel_mode-1].fan_speed[0]++;break;
		case 5:if(kotel.p[kotel.fuel][kotel_mode-1].fan_on[0]<255)kotel.p[kotel.fuel][kotel_mode-1].fan_on[0]++;break;
		case 6:if(kotel.p[kotel.fuel][kotel_mode-1].fan_off[0]<255)kotel.p[kotel.fuel][kotel_mode-1].fan_off[0]++;break;
	
		case 7:if(kotel.p[kotel.fuel][kotel_mode-1].fan_speed[1]<100)kotel.p[kotel.fuel][kotel_mode-1].fan_speed[1]++;break;
		case 8:if(kotel.p[kotel.fuel][kotel_mode-1].fan_on[1]<255)kotel.p[kotel.fuel][kotel_mode-1].fan_on[1]++;break;
		case 9:if(kotel.p[kotel.fuel][kotel_mode-1].fan_off[1]<255)kotel.p[kotel.fuel][kotel_mode-1].fan_off[1]++;break;
	
		case 10:if(kotel.p[kotel.fuel][kotel_mode-1].shnek_ena[0]<1)kotel.p[kotel.fuel][kotel_mode-1].shnek_ena[0]=1;break;
		case 11:if(kotel.p[kotel.fuel][kotel_mode-1].shnek_on[0]<255)kotel.p[kotel.fuel][kotel_mode-1].shnek_on[0]++;break;
		case 12:if(kotel.p[kotel.fuel][kotel_mode-1].shnek_off[0]<255)kotel.p[kotel.fuel][kotel_mode-1].shnek_off[0]++;break;
	
		case 13:if(kotel.p[kotel.fuel][kotel_mode-1].shnek_ena[1]<1)kotel.p[kotel.fuel][kotel_mode-1].shnek_ena[1]=1;break;
		case 14:if(kotel.p[kotel.fuel][kotel_mode-1].shnek_on[1]<255)kotel.p[kotel.fuel][kotel_mode-1].shnek_on[1]++;break;
		case 15:if(kotel.p[kotel.fuel][kotel_mode-1].shnek_off[1]<255)kotel.p[kotel.fuel][kotel_mode-1].shnek_off[1]++;break;
	
		}
	}
	if((kotel_mode==5))
	{
		switch(pos)
		{
		case 0:if(kotel.fuel<(MAX_KOTEL_FUELS-1))kotel.fuel++;break;
		case 1:if(kotel_mode<4)kotel_mode++;scr0_1_set_mode(kotel_mode);break;
		case 2:if(kotel.smoke_speed[kotel.fuel]<100)kotel.smoke_speed[kotel.fuel]++;break;
		}
	}
	new_step=70+kotel.fuel+kotel_mode-1;					
	Button_no_update_time=200;
	scr0_1_show();
}
//-----------------------------------------------------------------------------------
void scr0_1_minus()
{
	if((kotel_mode>=1)&&(kotel_mode<5))
	{
		switch(pos)
		{
		case 0:if(kotel.fuel!=0)kotel.fuel--;break;
		case 1:if(kotel_mode>1)kotel_mode--; scr0_1_set_mode(kotel_mode);break;
		case 2:if(kotel.p[kotel.fuel][kotel_mode-1].t>-400)kotel.p[kotel.fuel][kotel_mode-1].t-=10;break;
		case 3:if(kotel.p[kotel.fuel][kotel_mode-1].smoke_speed!=0)kotel.p[kotel.fuel][kotel_mode-1].smoke_speed--;break;
	
		case 4:if(kotel.p[kotel.fuel][kotel_mode-1].fan_speed[0]!=0)kotel.p[kotel.fuel][kotel_mode-1].fan_speed[0]--;break;
		case 5:if(kotel.p[kotel.fuel][kotel_mode-1].fan_on[0]!=0)kotel.p[kotel.fuel][kotel_mode-1].fan_on[0]--;break;
		case 6:if(kotel.p[kotel.fuel][kotel_mode-1].fan_off[0]!=0)kotel.p[kotel.fuel][kotel_mode-1].fan_off[0]--;break;
	
		case 7:if(kotel.p[kotel.fuel][kotel_mode-1].fan_speed[1]!=0)kotel.p[kotel.fuel][kotel_mode-1].fan_speed[1]--;break;
		case 8:if(kotel.p[kotel.fuel][kotel_mode-1].fan_on[1]!=0)kotel.p[kotel.fuel][kotel_mode-1].fan_on[1]--;break;
		case 9:if(kotel.p[kotel.fuel][kotel_mode-1].fan_off[1]!=0)kotel.p[kotel.fuel][kotel_mode-1].fan_off[1]--;break;
	
		case 10:if(kotel.p[kotel.fuel][kotel_mode-1].shnek_ena[0]!=0)kotel.p[kotel.fuel][kotel_mode-1].shnek_ena[0]=0;break;
		case 11:if(kotel.p[kotel.fuel][kotel_mode-1].shnek_on[0]!=0)kotel.p[kotel.fuel][kotel_mode-1].shnek_on[0]--;break;
		case 12:if(kotel.p[kotel.fuel][kotel_mode-1].shnek_off[0]!=0)kotel.p[kotel.fuel][kotel_mode-1].shnek_off[0]--;break;
	
		case 13:if(kotel.p[kotel.fuel][kotel_mode-1].shnek_ena[1]!=0)kotel.p[kotel.fuel][kotel_mode-1].shnek_ena[1]=0;break;
		case 14:if(kotel.p[kotel.fuel][kotel_mode-1].shnek_on[1]!=0)kotel.p[kotel.fuel][kotel_mode-1].shnek_on[1]--;break;
		case 15:if(kotel.p[kotel.fuel][kotel_mode-1].shnek_off[1]!=0)kotel.p[kotel.fuel][kotel_mode-1].shnek_off[1]--;break;
		}
	}
	if((kotel_mode==5))
	{
		switch(pos)
		{
		case 0:if(kotel.fuel!=0)kotel.fuel--;break;
		case 1:if(kotel_mode>1)kotel_mode--; scr0_1_set_mode(kotel_mode);break;
		case 2:if(kotel.smoke_speed[kotel.fuel]!=0)kotel.smoke_speed[kotel.fuel]--;break;
		}
	}
	new_step=70+kotel.fuel+kotel_mode-1;					
	Button_no_update_time=200;			
	scr0_1_show();
}
//-----------------------------------------------------------------------------------
void scr0_1_set_mode_1()
{
	scr0_1_set_mode(1);
}
//-----------------------------------------------------------------------------------
void scr0_1_set_mode_2()
{
	scr0_1_set_mode(2);
}
//-----------------------------------------------------------------------------------
void scr0_1_set_mode_3()
{
	scr0_1_set_mode(3);
}
//-----------------------------------------------------------------------------------
void scr0_1_set_mode_4()
{
	scr0_1_set_mode(4);
}
//-----------------------------------------------------------------------------------
void scr0_1_set_mode_5()
{
	pos=0;
	scr0_1_set_mode(5);
}
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_0_1_Up=
{	
	25,56+16+0,42,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	scr0_1_up,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_0_1_Down=
{	
	25,76+16+0,43,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	scr0_1_down,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_0_1_Plus=
{	
	25,16+8,44,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	scr0_1_plus,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_0_1_Minus=
{	
	25,36+8,45,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	scr0_1_minus,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _0_1_Mode_1=
{	
	0,117,76,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr0_1_set_mode_1,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _0_1_Mode_2=
{	
	6,117,77,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr0_1_set_mode_2,
	NULL,
};

//-----------------------------------------------------------------------------------
__farflash TLCDPict _0_1_Mode_3=
{	
	12,117,78,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr0_1_set_mode_3,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _0_1_Mode_4=
{	
	18,117,79,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr0_1_set_mode_4,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _0_1_Mode_5=
{	
	24,117,80,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr0_1_set_mode_5,
	NULL,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_0_1=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	5+4+5,
	0,	
	scr0_1_init,
	scr0_1_routine,
	scr0_1_close,		
};
//-----------------------------------------------------------------------------------
void scr0_1_init()
{
//	u8 i;
	Branch_Number=0;
	new_step=60;
	Switch_To_Main_Time=60;
	
	Obj[0]=Tab_Menu0;	
	Obj[1]=Tab_Menu1;	
	Obj[2]=Tab_Menu2;	
	Obj[3]=Tab_Menu3;		
	Obj[4]=Tab_Menu4;	
	
	Obj[1].Stat=1;
		
	Obj[0].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[1].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[2].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[3].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[4].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	

	Obj[5]=_Page_0_1_Plus;	
	Obj[6]=_Page_0_1_Minus;	
	Obj[7]=_Page_0_1_Up;		
	Obj[8]=_Page_0_1_Down;		

	Obj[9]=_0_1_Mode_1;	
	Obj[10]=_0_1_Mode_2;	
	Obj[11]=_0_1_Mode_3;		
	Obj[12]=_0_1_Mode_4;		
	Obj[13]=_0_1_Mode_5;			
	
	obj_mode_1.Stat=1;
	pos=0;
	kotel_mode=1;
}
//-----------------------------------------------------------------------------------
void scr0_1_close()
{
	u8 i;
	for(i=0;i<Scr_0_1.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
	lcd_clear_text();
	new_step=0;
}
//-----------------------------------------------------------------------------------
void scr0_1_routine()
{
	
	if(FT_Time!=0)return;
	FT_Time=500;
	if(page_offset!=PAGE_0_OFFSET)return;
	scr0_1_show();
}
//-----------------------------------------------------------------------------------

