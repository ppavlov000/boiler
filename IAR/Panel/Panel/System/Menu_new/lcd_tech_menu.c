//-----------------------------------------------------------------------------------
#include "..\Main.h"
//-----------------------------------------------------------------------------------
#include "..\Menu_New\lcd_template.h"
#include "..\Menu_New\lcd_calibrate.h"
#include "..\Menu_New\lcd_alarm.h"
#include "..\Menu_New\lcd_alarm_snooze.h"
#include "..\Menu_New\lcd_ac_menu.h"
#include "..\Menu_New\lcd_tech_menu.h"
#include "..\Menu_New\lcd_set_time.h"
#include "..\Menu_New\lcd_tech_contrast.h"
//#include "..\Menu_New\lcd_tech_temperature.h"
//-----------------------------------------------------------------------------------
extern TLCDPictTop Scr_0;
extern TLCDPictTop Scr_1;
extern TLCDPictTop Scr_7;
extern __farflash TLCDPict_Txt _Txt_0;
extern __farflash TLCDPict_Txt _Txt_1;
extern __farflash TLCDPict_Txt _Txt_2;
extern __farflash TLCDPict_Txt _Txt_3;
extern __farflash TLCDPict_Txt _Txt_4;

//extern TLCDPictTop Scr_11;

__farflash TLCDPict _Tech_Menu;

extern TLCDPictTop *Scr_Return;
extern TLCDPictTop *Scr_Enter;
extern TLCDPictTop Scr_Password;

__farflash char scr4_msg[]={"ID        "};
//-----------------------------------------------------------------------------------
void scr4_init();
void scr4_close();
void scr4_routine();
//-----------------------------------------------------------------------------------
void Enter_New_Pass()
{
	own_state.Password_Mode=PM_NEW_PASSWORD;
	own_state.Password_Downcount=30;
	own_state.status |= bit_new_push;	
	
	Scr_Return=&Scr_4;
	Scr_Enter=&Scr_4;	
	LCDTopPtr->Exit();
	LCDTopPtr=&Scr_Password;
	LCDTopPtr->Init();
	repaint_page();		
}
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Tech_Menu_Exit=
{
	// Exit
	27,0,27,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,	
	0,	
	NULL,
	&Scr_1,
};
/*
//--------------------------------------------
__farflash TLCDPict _Tech_Menu_Cell=
{
	11,60,64,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,		
	NULL,
	&Scr_10,
};

//--------------------------------------------
__farflash TLCDPict _Tech_Menu_Password=
{
	22,60,5,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,		
	Enter_New_Pass,
	&Scr_10,
};
*/
//--------------------------------------------
__farflash TLCDPict _Tech_Menu_Temperature=
{
	16,0,33,
	(bit_visible+bit_active+bit_new_page),
//	0,
	0,
	0,
	0,		
	NULL,
	&Scr_7,
//	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Tech_Menu_Contrast=
{
	8,0,32,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,	
	NULL,
	&Scr_6,
//	&_Tech_Contrast,	
};
//--------------------------------------------
__farflash TLCDPict _Tech_Menu_Clock=
{
	0,0,31,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,	
	NULL,
	&Scr_5,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Tech_Menu=
{
	0,0,0,
	0,
	0,
	0,
	0,	
	NULL,
	NULL,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_4=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	4,
	0,	
	scr4_init,
	scr4_routine,
	scr4_close,		
};
//-----------------------------------------------------------------------------------
void scr4_init()
{
//	memset(Obj,0,16*sizeof(TLCDPict));
//	memset(Txt,0,20*sizeof(TLCDPict_Txt));	
//	_sprintf(outtxt,"\n\r Init");
	Obj[0]=_Tech_Menu_Clock;
	Obj[1]=_Tech_Menu_Contrast;	
	Obj[2]=_Tech_Menu_Temperature;
	Obj[3]=_Tech_Menu_Exit;
//	Obj[4]=_Tech_Menu_Cell;	
//	Obj[5]=_Tech_Menu_Password;		
	FT_Time=100;
}
//-----------------------------------------------------------------------------------
void scr4_close()
{
//	u8 i;
	clear_page();
	lcd_clear_text();
}
//-----------------------------------------------------------------------------------
void scr4_routine()
{
//	if(page_offset!=PAGE_0_OFFSET)return;
	if(FT_Time!=0)return;	
	FT_Time=1000;
	lcd_sprintf_P(scr4_msg,0,14);
	ByteToStr(lcd_txt,&m.Address,0);
	lcd_sprintf(lcd_txt,3,14);	
	FGet((u8*)lcd_txt,HAPP_FLASH_START+TNAME_LOC,TNAME_WIDTH);
	lcd_sprintf(lcd_txt,0,15);	
}
//-----------------------------------------------------------------------------------
