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
extern __farflash TLCDPict _Menu0;
extern __farflash TLCDPict _Menu1;
extern __farflash TLCDPict _Menu2;
extern __farflash TLCDPict _Menu3;
extern __farflash TLCDPict _Menu4;
//-----------------------------------------------------------------------------------
extern TLCDPictTop Scr_12;
extern TLCDPictTop Scr_4;
extern TLCDPictTop Scr_10;
extern TLCDPictTop Scr_11;
//extern TLCDPictTop Scr_12;
extern __farflash TLCDPict_Txt _Txt_0;
extern __farflash TLCDPict_Txt _Txt_1;
extern __farflash TLCDPict_Txt _Txt_2;
extern __farflash TLCDPict_Txt _Txt_3;
extern __farflash TLCDPict_Txt _Txt_4;
//-----------------------------------------------------------------------------------
void scr1_init();
void scr1_close();
void scr1_routine();
//-----------------------------------------------------------------------------------
extern u8 Branch_Number;
extern u8 step;
extern u8 new_step;
extern u8 Common_ID_Mode;
extern u8 Current_ID;
//BMP_22=H:\Ura\Projects\20090914_Shevchenko\Iar\Panel\Panel\System\Pictures\EL\Scr_1\set_tech.bmp
//BMP_23=H:\Ura\Projects\20090914_Shevchenko\Iar\Panel\Panel\System\Pictures\EL\Scr_1\set_protok.bmp
//BMP_24=H:\Ura\Projects\20090914_Shevchenko\Iar\Panel\Panel\System\Pictures\EL\Scr_1\set_Season.bmp
//BMP_25=H:\Ura\Projects\20090914_Shevchenko\Iar\Panel\Panel\System\Pictures\EL\Scr_1\set_Day_Night.bmp
void M_Save_Controller_Params(u8 id);
//-----------------------------------------------------------------------------------
void Send_Save_command()
{
	M_Save_Controller_Params(Current_ID);
	M_SCH_Time=10;
}
//-----------------------------------------------------------------------------------
void Send_Init_command()
{
//	s16 steps[4]={5,10,20,2};
	fan[0].TLow=5;
	fan[0].TMedium=10;
	fan[0].THigh=20;
	fan[0].Hysteresis=2;	
	M_Set_Controller_Register(0,&fan[0].TLow,8);					
	M_SCH_Time=10;
}
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_1_Tech=
{	
	0,16,22,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,	
	NULL,
	&Scr_4,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_1_Protok=
{	
	0,16+27,23,
//	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,
	0,	
	NULL,
	&Scr_10,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_1_Season=
{	
	0,16+2*27,24,
	0,
//	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,	
	NULL,
	NULL,
//	&Scr_12,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_1_Day=
{	
	0,16+1*27,25,
//	(bit_visible+bit_active+bit_new_page),
	0,
	0,
	0,
	0,	
	NULL,
	&Scr_11,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_1_Init=
{	
	0,16+1*27,91,
	(bit_visible+bit_active),
//	0,
	0,
	0,
	0,	
	Send_Init_command,
	&Scr_11,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_1_Adjust=
{	
	0,16+2*27,90,
	(bit_visible+bit_active+bit_new_page),
//	0,
	0,
	0,
	0,	
	NULL,
	&Scr_12,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_1_Save=
{	
	0,16+3*27,56,
	(bit_visible+bit_active),
//	0,
	0,
	0,
	0,	
	Send_Save_command,
	&Scr_11,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_1=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	5+6,
	0,	
	scr1_init,
	scr1_routine,
	scr1_close,		
};
//-----------------------------------------------------------------------------------
void scr1_init()
{
//	u8 i;
	Branch_Number=0;
	new_step=step=0;
	Obj[0]=_Menu0;	
	Obj[1]=_Menu1;	
	Obj[2]=_Menu2;	
	Obj[3]=_Menu3;		
	Obj[4]=_Menu4;	
	
	Obj[5]=_Page_1_Tech;	
	Obj[6]=_Page_1_Protok;	
	Obj[7]=_Page_1_Season;	
	Obj[8]=_Page_1_Init;	
	Obj[9]=_Page_1_Adjust;	
	Obj[10]=_Page_1_Save;	

	Obj[1].Stat=1;
}
//-----------------------------------------------------------------------------------
void scr1_close()
{
	u8 i;
	for(i=0;i<Scr_1.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
}
//-----------------------------------------------------------------------------------
void scr1_routine()
{
//	u8 tmp;		
//	u16 temp;
//	u8 tmp0;//,tmp1,tmp2; lc
//	u8 old_stat;
//	s16 temperature;
	if(FT_Time!=0)return;
	FT_Time=500;
	if(page_offset!=PAGE_0_OFFSET)return;
}
//-----------------------------------------------------------------------------------
void Schedule_N7()
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
				case com_get_season:		
					if(Button_no_update_time==0)
						memcpy(&reg_season,&M_rx.field.d[0],sizeof(TSeason));	
				break;		
				case com_get_register:		
					if(Button_no_update_time==0)
					{
						memcpy(&addr,&M_rx.field.d[0],2);		
						len=M_rx.field.d[2];
						memcpy(&reg_data[addr],&M_rx.field.d[3],len);							
					}
				break;					
				
				case com_set_season:		
				break;				
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
//				case 0:
//					step++;
//					M_Get_Controller_Status(Current_ID,Current_ID);
					//upc_Get_Controller_Time(1,1);
//					M_SCH_Time=100;
//				break;				
				case 0:
//					M_Get_Season(Current_ID);
					// Season
					M_Get_Controller_Register(Current_ID,&MenuRegs.Season,sizeof(TSeason));										
					step=0;					
					M_SCH_Time=100;	
				break;
				case 2:
//					 M_Set_Season(Current_ID,&reg_season);
					M_Set_Controller_Register(Current_ID,&MenuRegs.Season,sizeof(TSeason));										
					step=0;					
					M_SCH_Time=50;	
				break;
			default:
					step=0;									
				break;
			}
		}		
	}	
}
//-----------------------------------------------------------------------------------

