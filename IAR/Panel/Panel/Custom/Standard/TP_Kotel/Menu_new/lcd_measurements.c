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
#define KOT_OFF_X		0
#define KOT_OFF_Y		2
//-----------------------------------------------------------------------------------
void scr0_3_init();
void scr0_3_routine();
void scr0_3_close();
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
__farflash u8	eng_kot_meash_str[][25]=
{
	"T out    ",						//0
	"T in     ",						//1
	"T smoke  ",						//2
	"T ext    ",						//3
	"T fuel   ",						//4	
	"Low  pr  ",						//5	
	"High pr  ",						//6	
	"T 110c   ",						//7	
	"Tpk open ",						//8
	"TS GOR   ",						//9	
	"ALO      ",						//10	
	"Bun open ",						//11	
	"Fuel low ",						//12	
	"TK 1     ",						//13	
	"TK 2     ",						//14	
	"TK 3     ",						//15	
	"TK 4     ",						//16		
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

extern s16 	t_ext;
extern u16  params[3];
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_0_3=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	5,
	0,	
	scr0_3_init,
	scr0_3_routine,
	scr0_3_close,		
};
//-----------------------------------------------------------------------------------
void scr0_3_init()
{
	u8 i;
	Branch_Number=0;
	new_step=step=0;
	Switch_To_Main_Time=60;
	
	Obj[0]=Tab_Menu0;	
	Obj[1]=Tab_Menu1;	
	Obj[2]=Tab_Menu2;	
	Obj[3]=Tab_Menu3;		
	Obj[4]=Tab_Menu4;	
	
	Obj[3].Stat=1;
		
	Obj[0].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[1].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[2].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[3].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	Obj[4].Flag=(bit_visible+bit_active+bit_trigger+bit_new_page);	
	
}
//-----------------------------------------------------------------------------------
void scr0_3_close()
{
	u8 i;
	for(i=0;i<Scr_0_3.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
	lcd_clear_text();
}
//-----------------------------------------------------------------------------------
void scr0_3_routine()
{
	u8 tmp,tmp2;		
	u16 temp;
	u8 tmp0;//,tmp1,tmp2; lc
	u8 old_stat;
	s16 temperature;
	if(FT_Time!=0)return;
	FT_Time=500;
	if(page_offset!=PAGE_0_OFFSET)return;
	
	// T out
	str[0]=0;		
	strcat2(str,(u8*)eng_kot_meash_str[0]);
	ShowTemperature(str2,&io.ainput[kotel.channel]);
	strcat((char*)str,(char*)str2);
	lcd_sprintf(str,KOT_OFF_X+0,KOT_OFF_Y+0);

	// T in
	str[0]=0;		
	strcat2(str,(u8*)eng_kot_meash_str[1]);
	ShowTemperature(str2,&t_in);
	strcat((char*)str,(char*)str2);
	lcd_sprintf(str,KOT_OFF_X+0,KOT_OFF_Y+1);

	// T smoke
	str[0]=0;		
	strcat2(str,(u8*)eng_kot_meash_str[2]);
	ShowTemperature(str2,&t_smoke);
	strcat((char*)str,(char*)str2);
	lcd_sprintf(str,KOT_OFF_X+0,KOT_OFF_Y+2);


	// T external
	str[0]=0;		
	strcat2(str,(u8*)eng_kot_meash_str[3]);
	ShowTemperature(str2,&t_ext);
	strcat((char*)str,(char*)str2);
	lcd_sprintf(str,KOT_OFF_X+0,KOT_OFF_Y+3);

	// T fuel
	str[0]=0;		
	strcat2(str,(u8*)eng_kot_meash_str[4]);
	ShowTemperature(str2,&t_fuel);
	strcat((char*)str,(char*)str2);
	lcd_sprintf(str,KOT_OFF_X+0,KOT_OFF_Y+4);

	// DI
	
	// preasure low
	str[0]=0;		
	strcat2(str,(u8*)eng_kot_meash_str[5]);
	if(di_PL)
		strcat((char*)str,"1");
	else
		strcat((char*)str,"0");
	lcd_sprintf(str,KOT_OFF_X+0,KOT_OFF_Y+5);

	// preasure high
	str[0]=0;		
	strcat2(str,(u8*)eng_kot_meash_str[6]);
	if(di_PH)
		strcat((char*)str,"1");
	else
		strcat((char*)str,"0");
	lcd_sprintf(str,KOT_OFF_X+0,KOT_OFF_Y+6);

	// DI 110
	str[0]=0;		
	strcat2(str,(u8*)eng_kot_meash_str[7]);
	if(di_T110)
		strcat((char*)str,"1");
	else
		strcat((char*)str,"0");
	lcd_sprintf(str,KOT_OFF_X+0,KOT_OFF_Y+7);

	// di_TOP_O
	str[0]=0;		
	strcat2(str,(u8*)eng_kot_meash_str[8]);
	if(di_TOP_O==0)
		strcat((char*)str,"1");
	else
		strcat((char*)str,"0");
	lcd_sprintf(str,KOT_OFF_X+0,KOT_OFF_Y+8);

	// di_TS_GOR
	str[0]=0;		
	strcat2(str,(u8*)eng_kot_meash_str[9]);
	if(di_TS_GOR)
		strcat((char*)str,"1");
	else
		strcat((char*)str,"0");
	lcd_sprintf(str,KOT_OFF_X+0,KOT_OFF_Y+9);


	// di_ALO
	str[0]=0;		
	strcat2(str,(u8*)eng_kot_meash_str[10]);
	if(di_ALO)
		strcat((char*)str,"1");
	else
		strcat((char*)str,"0");
	lcd_sprintf(str,KOT_OFF_X+0,KOT_OFF_Y+10);


	// di_BUN_O
	str[0]=0;		
	strcat2(str,(u8*)eng_kot_meash_str[11]);
	if(di_BUN_O)
		strcat((char*)str,"1");
	else
		strcat((char*)str,"0");
	lcd_sprintf(str,KOT_OFF_X+0,KOT_OFF_Y+11);

	// di_Fuel_L
	str[0]=0;		
	strcat2(str,(u8*)eng_kot_meash_str[12]);
	if(di_BUN_O)
		strcat((char*)str,"1");
	else
		strcat((char*)str,"0");
	lcd_sprintf(str,KOT_OFF_X+18,KOT_OFF_Y+0);


	// di_TK1
	str[0]=0;		
	strcat2(str,(u8*)eng_kot_meash_str[13]);
	if(di_TK1)
		strcat((char*)str,"1");
	else
		strcat((char*)str,"0");
	lcd_sprintf(str,KOT_OFF_X+18,KOT_OFF_Y+1);

	// di_TK2
	str[0]=0;		
	strcat2(str,(u8*)eng_kot_meash_str[14]);
	if(di_TK2)
		strcat((char*)str,"1");
	else
		strcat((char*)str,"0");
	lcd_sprintf(str,KOT_OFF_X+18,KOT_OFF_Y+2);

	// di_TK3
	str[0]=0;		
	strcat2(str,(u8*)eng_kot_meash_str[15]);
	if(di_TK3)
		strcat((char*)str,"1");
	else
		strcat((char*)str,"0");
	lcd_sprintf(str,KOT_OFF_X+18,KOT_OFF_Y+3);

	// di_TK4
	str[0]=0;		
	strcat2(str,(u8*)eng_kot_meash_str[16]);
	if(di_TK4)
		strcat((char*)str,"1");
	else
		strcat((char*)str,"0");
	lcd_sprintf(str,KOT_OFF_X+18,KOT_OFF_Y+4);
}
//-----------------------------------------------------------------------------------

