//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
#include "..\Menu_New\lcd_template.h"
#include "..\Menu_New\lcd_calibrate.h"
#include "..\Menu_New\lcd_alarm.h"
#include "..\Menu_New\lcd_alarm_snooze.h"
#include "..\Menu_New\lcd_ac_menu.h"
#include "..\Menu_New\lcd_tech_menu.h"
#include "..\Menu_New\lcd_set_time.h"
#include "..\Menu_New\lcd_tech_contrast.h"
#include "..\Menu_New\lcd_tech_temperature.h"
//-----------------------------------------------------------------------------------
extern TLCDPictTop Scr_0;
extern __farflash TLCDPict_Txt _Txt_0;
extern __farflash TLCDPict_Txt _Txt_1;
extern __farflash TLCDPict_Txt _Txt_2;
extern __farflash TLCDPict_Txt _Txt_3;
extern __farflash TLCDPict_Txt _Txt_4;
//-----------------------------------------------------------------------------------

void scr7_init();
void scr7_close();
void scr7_routine();
//-----------------------------------------------------------------------------------
void Choose_Sens_0()
{
	u8 tmp;
	m.TMP441_Channel=0;

	tmp=Obj[1].Stat;
	Obj[1].Stat=0;
	if(tmp!=Obj[1].Stat)show_single_bmp(&Obj[1],0);
	
	if(Obj[2].Stat==0)
	{
		Obj[2].Stat=1;
		show_single_bmp(&Obj[2],0);
	}
}
//-----------------------------------------------------------------------------------
void Choose_Sens_1()
{
	u8 tmp;
	m.TMP441_Channel=1;

	tmp=Obj[2].Stat;
	Obj[2].Stat=0;
	if(tmp!=Obj[2].Stat)show_single_bmp(&Obj[2],0);
	
	if(Obj[1].Stat==0)
	{
		Obj[1].Stat=1;
		show_single_bmp(&Obj[1],0);
	}
}
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Tech_Temperature_Exit=
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
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Tech_Temperature=
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
__farflash TLCDPict _Tech_Sens_0=
{
	// Exit
	0,34,97,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,	
	0,	
	Choose_Sens_0,
	NULL,	
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Tech_Sens_1=
{
	// Exit
	0,60,98,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,	
	0,	
	Choose_Sens_1,
	NULL,	
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _Tech_Temperature2_txt_5=
{
	19+4,30,53,
	(bit_visible+bit_txt_1),
	15,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Tech_Temperature2_txt_4=
{
	17+4,30,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Tech_Temperature2_txt_3=
{
	13+4,30,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Tech_Temperature2_txt_2=
{
	15+4,30,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Tech_Temperature2_txt_1=
{
	11+4,30,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Tech_Temperature2_txt_0=
{
	9+4,30,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Tech_Temperature2_txt_Sign=
{
	7+4,30,53,
	(bit_visible+bit_txt_1),
	0,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//--------------------------------------------
__farflash TLCDPict_Txt _Tech_Temperature_txt_5=
{
	19+4,60,53,
	(bit_visible+bit_txt_1),
	15,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Tech_Temperature_txt_4=
{
	17+4,60,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Tech_Temperature_txt_3=
{
	13+4,60,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Tech_Temperature_txt_2=
{
	15+4,60,53,
	(bit_visible+bit_txt_1),
	12,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Tech_Temperature_txt_1=
{
	11+4,60,53,
	(bit_visible+bit_txt_1),
	1,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Tech_Temperature_txt_0=
{
	9+4,60,53,
	(bit_visible+bit_txt_1),
	0,
};
//--------------------------------------------
__farflash TLCDPict_Txt _Tech_Temperature_txt_Sign=
{
	7+4,60,53,
	(bit_visible+bit_txt_1),
	0,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_7=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	3,
	14,	
	scr7_init,
	scr7_routine,
	scr7_close,		
};
//-----------------------------------------------------------------------------------
void scr7_init()
{
	u8 i;
	Obj[0]=_Tech_Temperature_Exit;
	Obj[1]=_Tech_Sens_0;
	Obj[2]=_Tech_Sens_1;	
	
	Txt[0]=_Tech_Temperature_txt_Sign;	
	Txt[1]=_Tech_Temperature_txt_0;	
	Txt[2]=_Tech_Temperature_txt_1;	
	Txt[3]=_Tech_Temperature_txt_2;	
	Txt[4]=_Tech_Temperature_txt_3;	
	Txt[5]=_Tech_Temperature_txt_4;	
	Txt[6]=_Tech_Temperature_txt_5;	
	
	Txt[7]=_Tech_Temperature2_txt_Sign;	
	Txt[8]=_Tech_Temperature2_txt_0;	
	Txt[9]=_Tech_Temperature2_txt_1;	
	Txt[10]=_Tech_Temperature2_txt_2;	
	Txt[11]=_Tech_Temperature2_txt_3;	
	Txt[12]=_Tech_Temperature2_txt_4;	
	Txt[13]=_Tech_Temperature2_txt_5;
	
	FT_Time=100;
	for(i=0;i<Scr_7.Txt_Num;i++)
		Txt[i].Stat=10;
}
//-----------------------------------------------------------------------------------
void scr7_close()
{
	u8 i;
	for(i=0;i<Scr_7.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
	params_store();
}
//-----------------------------------------------------------------------------------
void scr7_routine()
{
//	u8 tmp;		
//	u16 temp;
	u8 tmp0;//,tmp1,tmp2; lc
	u8 old_stat;
	s16 temperature;
	s16 t[2]={0};
//	u8 i=0;
	s8 stmp;
	u8 utmp;
	s16 temp;
	f32 ftmp;
	
	if(FT_Time!=0)return;
	FT_Time=1000;
//	if(page_offset!=PAGE_0_OFFSET)return;
	if(m.TMP441_Channel==0)
	{
		if(Obj[1].Stat==1)
		{
			Obj[1].Stat=0;
			show_single_bmp(&Obj[1],0);
		}		
		if(Obj[2].Stat==0)
		{
			Obj[2].Stat=1;
			show_single_bmp(&Obj[2],0);
		}		
	}	
	if(m.TMP441_Channel==1)
	{
		if(Obj[1].Stat==0)
		{
			Obj[1].Stat=1;
			show_single_bmp(&Obj[1],0);
		}		
		if(Obj[2].Stat==1)
		{
			Obj[2].Stat=0;
			show_single_bmp(&Obj[2],0);
		}		
	}	
	//-----------------------------------------------	
#if TMP441_ENABLE		
	{
				TMP441_read(TMP441_reg_Remote0_T_H,(u8*)&stmp,1);
				temp=stmp;
				temp*=10;
				TMP441_read(TMP441_reg_Remote0_T_L,&utmp,1);			
				utmp>>=4;
				ftmp=utmp*0.0625*10;
				if(temp<0) 	temp-=ftmp;
				else		temp+=ftmp;
				t[1]=temp;				

				TMP441_read(TMP441_reg_Local_T_H,(u8*)&stmp,1);
				temp=stmp;
				temp*=10;
				TMP441_read(TMP441_reg_Local_T_L,&utmp,1);			
				utmp>>=4;
				ftmp=utmp*0.0625*10;
				if(temp<0) 	temp-=ftmp;
				else		temp+=ftmp;
				t[0]=temp;				
			}
#endif	
	temperature=t[0];
	if(temperature>600)temperature=0;
	LCDMenuPtr_Tmp_Txt=&Txt[0];
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;		
	if(temperature<0)
	{
		LCDMenuPtr_Tmp_Txt->Stat=10;
		temp=-temperature;
	}
	else
	{
		LCDMenuPtr_Tmp_Txt->Stat=11;	
		temp=temperature;		
	}
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
	
	LCDMenuPtr_Tmp_Txt=&Txt[1];					
	tmp0=temp/1000;
	temp-=tmp0*1000;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(tmp0==0)
		LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
	
	LCDMenuPtr_Tmp_Txt=&Txt[2];			
	tmp0=temp/100;
	temp-=tmp0*100;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[3];	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=12;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
				
	LCDMenuPtr_Tmp_Txt=&Txt[4];				
	tmp0=temp/10;
	temp-=tmp0*10;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[5];
	tmp0=temp;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[6];	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;			
	LCDMenuPtr_Tmp_Txt->Stat=15;			
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	//-----------------------------------------------	
	temperature=t[1];
	if(temperature>600)temperature=0;
	LCDMenuPtr_Tmp_Txt=&Txt[7];
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;		
	if(temperature<0)
	{
		LCDMenuPtr_Tmp_Txt->Stat=10;
		temp=-temperature;
	}
	else
	{
		LCDMenuPtr_Tmp_Txt->Stat=11;	
		temp=temperature;		
	}
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
	
	LCDMenuPtr_Tmp_Txt=&Txt[8];					
	tmp0=temp/1000;
	temp-=tmp0*1000;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(tmp0==0)
		LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
	
	LCDMenuPtr_Tmp_Txt=&Txt[9];			
	tmp0=temp/100;
	temp-=tmp0*100;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[10];	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=12;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
				
	LCDMenuPtr_Tmp_Txt=&Txt[11];				
	tmp0=temp/10;
	temp-=tmp0*10;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[12];
	tmp0=temp;
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);

	LCDMenuPtr_Tmp_Txt=&Txt[13];	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;			
	LCDMenuPtr_Tmp_Txt->Stat=15;			
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
}
//-----------------------------------------------------------------------------------

