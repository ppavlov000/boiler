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
//-----------------------------------------------------------------------------------
extern TLCDPictTop Scr_0;
extern __farflash TLCDPict_Txt _Txt_0;
extern __farflash TLCDPict_Txt _Txt_1;
extern __farflash TLCDPict_Txt _Txt_2;
extern __farflash TLCDPict_Txt _Txt_3;
extern __farflash TLCDPict_Txt _Txt_4;
//-----------------------------------------------------------------------------------
void scr6_init();
void scr6_close();
void scr6_routine();

void Mod_BackLit_Max_Up();
void Mod_BackLit_Max_Down();
void Mod_BackLit_Min_Up();
void Mod_BackLit_Min_Down();
void Mod_Sleep_Up();
void Mod_Sleep_Down();
//--------------------------------------------
void Mod_Inverse()
{
	u8 i;
	for(i=0;i<Scr_6.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();	
	if(	m.image_position)
		m.image_position=0;
	else
		m.image_position=1;	
	repaint_page();	
}
//--------------------------------------------
__farflash TLCDPict _Tech_Contrast_Exit=
{
	// Exit
	27,0,27,
	(bit_visible+bit_active+bit_new_page),
	0,
	0,	
	0,	
	NULL,	
	&Scr_4,
};
//--------------------------------------------
__farflash TLCDPict _Tech_Label_Sleep=
{
	0,94-16*2,61,
	(bit_visible+bit_full),
	0,
	0,
	0,	
	NULL,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Tech_Label_CMin=
{
	0,52-16*1,60,
	(bit_visible+bit_full),
	0,
	0,
	0,	
	NULL,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Tech_Label_CMax=
{
	0,8,59,
	(bit_visible+bit_full),
	0,
	0,
	0,	
	NULL,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Tech_Sleep_Down=
{
	7,88-16*2,26,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Mod_Sleep_Down,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Tech_Sleep_Up=
{
	21,88-16*2,28,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Mod_Sleep_Up,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Tech_Contast_Min_Down=
{
	7,44-16*1,26,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Mod_BackLit_Min_Down,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Tech_Contast_Min_Up=
{
	21,44-16*1,28,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Mod_BackLit_Min_Up,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Tech_Contast_Max_Down=
{
	7,0,26,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Mod_BackLit_Max_Down,
	NULL,	
};
//--------------------------------------------
__farflash TLCDPict _Tech_Contast_Max_Up=
{
	21,0,28,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	Mod_BackLit_Max_Up,
	NULL,	
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Tech_Contrast=
{
	0,0,0,
	0,
	0,
	0,
	0,	
	NULL,
	NULL,
};
//--------------------------------------------
__farflash TLCDPict _Tech_Inverse=
{
	0,88,63,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	Mod_Inverse,
	NULL,	
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _Contast_Min_txt_3=
{
	18,52-16*1,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Contast_Min_txt_2=
{
	16,52-16*1,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Contast_Min_txt_1=
{
	14,52-16*1,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Contast_Min_txt_0=
{
	12,52-16*1,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
//--------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _Contast_Max_txt_3=
{
	18,8,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Contast_Max_txt_2=
{
	16,8,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Contast_Max_txt_1=
{
	14,8,53,
	(bit_visible+bit_txt_1),
	10,

};
//--------------------------------------------
__farflash TLCDPict_Txt _Contast_Max_txt_0=
{
	12,8,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
//--------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _Sleep_txt_2=
{
	18,94-16*2,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Sleep_txt_1=
{
	16,94-16*2,53,
	(bit_visible+bit_txt_1),
	10,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Sleep_txt_0=
{
	14,94-16*2,53,
	(bit_visible+bit_txt_1),
	10,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_6=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	11,
	11,	
	scr6_init,
	scr6_routine,
	scr6_close,		
};
//-----------------------------------------------------------------------------------
void scr6_init()
{
	Obj[0]=_Tech_Contast_Max_Up;
	Obj[1]=_Tech_Contast_Max_Down;	
	Obj[2]=_Tech_Contast_Min_Up;
	Obj[3]=_Tech_Contast_Min_Down;
	Obj[4]=_Tech_Sleep_Up;
	Obj[5]=_Tech_Sleep_Down;
	Obj[6]=_Tech_Label_CMax;
	Obj[7]=_Tech_Label_CMin;
	Obj[8]=_Tech_Label_Sleep;
	Obj[9]=_Tech_Contrast_Exit;
	Obj[10]=_Tech_Inverse;
	
	
	Txt[0]=_Sleep_txt_0;	
	Txt[1]=_Sleep_txt_1;	
	Txt[2]=_Sleep_txt_2;	
	
	Txt[3]=_Contast_Max_txt_0;	
	Txt[4]=_Contast_Max_txt_1;	
	Txt[5]=_Contast_Max_txt_2;		
	Txt[6]=_Contast_Max_txt_3;		
	
	Txt[7]=_Contast_Min_txt_0;		
	Txt[8]=_Contast_Min_txt_1;		
	Txt[9]=_Contast_Min_txt_2;					
	Txt[10]=_Contast_Min_txt_3;		
		
/*	Txt[0].Stat=10;
	Txt[1].Stat=10;
	Txt[3].Stat=10;
	Txt[4].Stat=10;	
	Txt[5].Stat=10;
	Txt[6].Stat=10;
	Txt[7].Stat=10;
	Txt[8].Stat=10;
	Txt[9].Stat=10;
	Txt[10].Stat=10;
*/	
	FT_Time=100;								
}
//-----------------------------------------------------------------------------------
void scr6_close()
{
	u8 i;
	for(i=0;i<Scr_6.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
	params_store();	
}
//-----------------------------------------------------------------------------------
void scr6_routine()
{
	u16 tmp,tmp0,tmp1;	
	s16 temp;
	u8 old_stat;
	if(FT_Time!=0)return;
//	if(page_offset!=PAGE_0_OFFSET)return;
		temp=m.BackLit_Value_Max;	
		tmp0=temp/10;

		LCDMenuPtr_Tmp_Txt=&Txt[3];				
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;
		if(tmp0==0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[4];		
		tmp1=temp-tmp0*10;
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;
		LCDMenuPtr_Tmp_Txt->Stat=tmp1;		
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
				
		LCDMenuPtr_Tmp_Txt=&Txt[5];		
		tmp=0;
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;
		LCDMenuPtr_Tmp_Txt->Stat=tmp;		
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[6];		
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;
		LCDMenuPtr_Tmp_Txt->Stat=14;			
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	//------------------------------
	//------------------------------		
	//------------------------------
		temp=m.BackLit_Value_Min;	
		tmp0=temp/10;

		LCDMenuPtr_Tmp_Txt=&Txt[7];				
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;
		LCDMenuPtr_Tmp_Txt->Stat=tmp0;
		if(tmp0==0)LCDMenuPtr_Tmp_Txt->Stat=16;
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[8];		
		tmp1=temp-tmp0*10;
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;
		LCDMenuPtr_Tmp_Txt->Stat=tmp1;		
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
				
		LCDMenuPtr_Tmp_Txt=&Txt[9];		
		tmp=0;
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;
		LCDMenuPtr_Tmp_Txt->Stat=tmp;		
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
		LCDMenuPtr_Tmp_Txt=&Txt[10];		
		old_stat=LCDMenuPtr_Tmp_Txt->Stat;
		LCDMenuPtr_Tmp_Txt->Stat=14;			
		if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);	
	//------------------------------
		// Sleep time
		temp=m.Sleep_Time;	
		tmp1=temp/10;
		old_stat=Txt[0].Stat;
		Txt[0].Stat=tmp1;		
		if(old_stat!=Txt[0].Stat)show_single_bmp_txt(&Txt[0]);	
				
		tmp=temp-tmp1*10;
		old_stat=Txt[1].Stat;
		Txt[1].Stat=tmp;		
		if(old_stat!=Txt[1].Stat)show_single_bmp_txt(&Txt[1]);	
}
//-----------------------------------------------------------------------------------
void Mod_BackLit_Max_Up()
{
	if(m.BackLit_Value_Max<10)m.BackLit_Value_Max+=1;
	BackLit_Value=bl[m.BackLit_Value_Max];	
	scr6_routine();
}
//-----------------------------------------------------------------------------------
void Mod_BackLit_Max_Down()
{
	if(m.BackLit_Value_Max>m.BackLit_Value_Min)m.BackLit_Value_Max-=1;
	BackLit_Value=bl[m.BackLit_Value_Max];
	scr6_routine();
}
//-----------------------------------------------------------------------------------
void Mod_BackLit_Min_Up()
{
	if(m.BackLit_Value_Min<m.BackLit_Value_Max)m.BackLit_Value_Min+=1;
	scr6_routine();
}
//-----------------------------------------------------------------------------------
void Mod_BackLit_Min_Down()
{
	if(m.BackLit_Value_Min>0)m.BackLit_Value_Min-=1;
	scr6_routine();
}
//-----------------------------------------------------------------------------------
void Mod_Sleep_Up()
{
	if(m.Sleep_Time<30)m.Sleep_Time+=1;
	else m.Sleep_Time=30;
	scr6_routine();
}
//-----------------------------------------------------------------------------------
void Mod_Sleep_Down()
{
	if(m.Sleep_Time>0)m.Sleep_Time-=1;
	else m.Sleep_Time=0;
	scr6_routine();
}
//-----------------------------------------------------------------------------------
