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
//extern TLCDPictTop Scr_0;
extern TLCDPictTop Scr_4;
extern __farflash TLCDPict_Txt _Txt_0;
extern __farflash TLCDPict_Txt _Txt_1;
extern __farflash TLCDPict_Txt _Txt_2;
extern __farflash TLCDPict_Txt _Txt_3;
extern __farflash TLCDPict_Txt _Txt_4;
extern u8 Branch_Number;
extern u8 step;
extern u8 new_step;
extern u8 Current_ID;
s16 Minimal_Protok=0;
extern TPID pid;
//-----------------------------------------------------------------------------------
void scr10_init();
void scr10_close();
void scr10_routine();

void Protok_Plus()
{
	Minimal_Protok=Minimal_Protok+10;
	if(Minimal_Protok>=999)	Minimal_Protok=999;	
	Button_no_update_time=500;
	new_step=1;	
	FT_Time=0;
}
void Protok_Minus()
{
	if(Minimal_Protok<=10)	
		Minimal_Protok=0;	
	else
		Minimal_Protok=Minimal_Protok-10;
	Button_no_update_time=500;
	new_step=1;	
	FT_Time=0;
}
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_10_Plus=
{
	4,59,14,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Protok_Plus,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_10_Minus=
{
	22,59,15,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Protok_Minus,
	NULL,
};
//-----------------------------------------------------------------------------------
//--------------------------------------------
//--------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _Min_Protok_txt_4=
{
	19,59,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Min_Protok_txt_3=
{
	17,59,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Min_Protok_txt_2=
{
	15,59,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Min_Protok_txt_1=
{
	13,59,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Min_Protok_txt_0=
{
	11,59,53,
	(bit_visible+bit_txt_1),
	0,
};
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_10=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	7,
	5,	
	scr10_init,
	scr10_routine,
	scr10_close,		
};
//-----------------------------------------------------------------------------------
void scr10_init()
{
	u8 i;
	Branch_Number=6;
	new_step=step=0;
	
	Obj[0]=_Menu0;	
	Obj[1]=_Menu1;	
	Obj[2]=_Menu2;	
	Obj[3]=_Menu3;		
	Obj[4]=_Menu4;		
	Obj[5]=_Page_10_Plus;	
	Obj[6]=_Page_10_Minus;	
	
	Txt[0]=_Min_Protok_txt_0;	
	Txt[1]=_Min_Protok_txt_1;	
	Txt[2]=_Min_Protok_txt_2;	
	Txt[3]=_Min_Protok_txt_3;	
	Txt[4]=_Min_Protok_txt_4;	
	
	Obj[1].Stat=1;
	
	for(i=0;i<Scr_10.Txt_Num;i++)
		Txt[i].Stat=10;	
}
//-----------------------------------------------------------------------------------
void scr10_close()
{
	u8 i;
	for(i=0;i<Scr_10.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
	lcd_clear_text();
}
//-----------------------------------------------------------------------------------
void scr10_routine()
{
//	u8 tmp,i;		
	u16 temp;
	u8 tmp0;//,tmp1,tmp2; lc
//	u8 old_stat;
	u8 old_stat;
	s16 temperature;
	
	if(FT_Time!=0)return;
	FT_Time=500;
	if(page_offset!=PAGE_0_OFFSET)return;
	// Min Protok
	temperature=Minimal_Protok;		
	temp=temperature;
	LCDMenuPtr_Tmp_Txt=&Txt[0];					
	tmp0=temp/100;
	temp-=tmp0*100;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
	LCDMenuPtr_Tmp_Txt=&Txt[1];			
	tmp0=temp/10;
	temp-=tmp0*10;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[2];	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=12;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[3];				
	tmp0=temp/1;
	temp-=tmp0*1;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[4];	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;			
	LCDMenuPtr_Tmp_Txt->Stat=14;			
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
}
//-----------------------------------------------------------------------------------
void Schedule_N6()
{
//	u16 i,tmp;
	M_state_machine();
	if((M.status==st_none)||(M.status==st_complete))
	{		
		if((M.error==0)&&(M.rxnew==1))
		{
			M.rxnew=0;
			switch(M_rx.field.com.bit.com)
			{
				case com_get_pid_0:		
//					Season=rx.field.data.st.Season;
					memcpy(&pid,&M_rx.field.d[0],M_rx.field.len);					
					if(Button_no_update_time==0)
						Minimal_Protok=pid.power_min;	
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
			switch(step)
			{
				case 0:
					step=0;
					M_Get_Controller_PID(0,Current_ID,Current_ID);
					M_SCH_Time=10;
				break;				
				case 1:
					step=0;
					pid.power_min=Minimal_Protok;	
//					M_tx=M_rx;
					M_Set_Controller_PID(0,Current_ID,&pid);
					M_SCH_Time=10;					
				break;

			}
		}
		
	}
	
}
//-----------------------------------------------------------------------------------

