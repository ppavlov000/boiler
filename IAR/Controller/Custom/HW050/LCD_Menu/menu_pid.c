//-----------------------------------------------------------------------------------
#include "..\..\..\System\main.h"
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
in_flash u8	eng_mode_of_operation_str_full[OPERATION_MODES_NUM][16]=
{
	"AUTOMAT",				//0
	"STOP",					//1	
	"MANUAL",				//2
	"ERROR",				//3	
	"WARNING",					//4	
};
in_flash u8	eng_mode_of_operation_str[OPERATION_MODES_NUM][8]=
{
	"AUTO",				//0
	"STOP",				//1	
	"MANL",				//2
	"EROR",				//3	
	"WARN",				//4		
};
in_flash u8	eng_mode_of_controller_str[3][8]=
{
	"AUT",				//0
	"SUM",				//1
	"WIN",				//2
};
in_flash u8	eng_mode_of_controller_str_full[3][8]=
{
	"AUTO",				//0
	"SUMMER",			//1
	"WINTER",			//2
};
in_flash u8	empty_str[17]={"                "};

//-----------------------------------------------------------------------------------
in_flash u8	ru_mode_of_operation_str_full[OPERATION_MODES_NUM][16]=
{
	"ÀÂÒÎÌÀÒ",				//0
	"ÑÒÎÏ",					//1	
	"ÐÓ×ÍÎÉ",				//2
	"ÀÂÀÐÑÒ",				//3	
	"ÀÂÀÐÈß",				//4	
};
in_flash u8	ru_mode_of_operation_str[OPERATION_MODES_NUM][8]=
{
	"ÀÂÒÎ",				//0
	"ÑÒÎÏ",				//1	
	"ÐÓ×Í",				//2
	"ÀÂÑÒ",				//3	
	"ÀÂÀÐ",				//4		
};
in_flash u8	ru_mode_of_controller_str[3][8]=
{
	"ÀÂÒ",				//0
	"ËÅÒ",				//1
	"ÇÈÌ",				//2
};
in_flash u8	ru_mode_of_controller_str_full[3][8]=
{
	"ÀÂÒÎ",				//0
	"ËÅÒÎ",			//1
	"ÇÈÌÀ",			//2
};
/*
in_flash u8	ru_errors_str[ERRORS_NUM][32]=
{
	"Íåò",					//0
	"Ðàçìîðîçêà",			//1
	"Äàò÷èê",				//2
	"Îøèáêà 2",				//3
	"Îøèáêà 3",				//4
};
*/
//-----------------------------------------------------------------------------------
in_flash TMenuRecodr	eng_pid_params_full[PID_PARAMETERS_NUM]=
{
	"Enable=",	1,	//0	
	"Tmp T0=",	1,	//1
	"Curr P=",	2,	//2						
	"Prop P=",	2,	//3	
	"Int  I=",	2,	//4
	"Diff D=",	2,	//5	
	"Int TI=",	2,	//6	
	"Max  P=",	2,	//7			
	"Min  P=",	2,	//8				
};
//-----------------------------------------------------------------------------------
in_flash TMenuRecodr ru_pid_params_full[PID_PARAMETERS_NUM]=
{
	"Âêë   =",	1,	//0
	"Òåìï T=",	1,	//1
	"Òåê  P=",	2,	//2						
	"Ïðîï P=",	2,	//3	
	"Èíò  I=",	2,	//4
	"Äèôô D=",	2,	//5	
	"Èíòã T=",	2,	//6	
	"Ìàêñ P=",	2,	//7			
	"Ìèí  P=",	2,	//8				
};
//-----------------------------------------------------------------------------------
extern u8 LCD_Cur_Pos;
extern s8 LCD_Shw_Pos;
extern u8 Active_Item;
extern u8 Active_PID;
extern u8 Active_PID_Item;

u8 get_prev_menu();
u8 get_next_menu();
u8 get_sub_menu();
u8 get_up_menu();
//-----------------------------------------------------------------------------------
// PID
//-----------------------------------------------------------------------------------
void rp03()
{
#if NUM_PID
	s16 tmp;
//	u8 show_pos_tmp;
//	u8 i=0;
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");	
		lcd_set_pos(LCD_Shw_Pos,6);
		tmp=io.ainput[pid[Active_PID].channel];
		if(tmp>999)tmp=999;
		ShowTemperatureShort(lcd_txt,&tmp);
		lcd_printf(lcd_txt);			
													
		lcd_set_pos(LCD_Shw_Pos,1);
		memset(lcd_txt, 0, sizeof(lcd_txt));
		if(MenuRegs.lang==0)
		{
			if(pid[Active_PID].mode==PID_MODE_STOP)
				__sprintf_P(lcd_txt,eng_mode_of_operation_str[1]);
			if(pid[Active_PID].mode==PID_MODE_AUTO)
				__sprintf_P(lcd_txt,eng_mode_of_operation_str[0]);						
			if(pid[Active_PID].mode==PID_MODE_ERROR)
				__sprintf_P(lcd_txt,eng_mode_of_operation_str[3]);
			if(pid[Active_PID].mode==PID_MODE_WARNING)
				__sprintf_P(lcd_txt,eng_mode_of_operation_str[4]);									
		}
		if(MenuRegs.lang==1)
		{
			if(pid[Active_PID].mode==PID_MODE_STOP)
				__sprintf_P(lcd_txt,ru_mode_of_operation_str[1]);
			if(pid[Active_PID].mode==PID_MODE_AUTO)
				__sprintf_P(lcd_txt,ru_mode_of_operation_str[0]);						
			if(pid[Active_PID].mode==PID_MODE_ERROR)
				__sprintf_P(lcd_txt,ru_mode_of_operation_str[3]);		
			if(pid[Active_PID].mode==PID_MODE_WARNING)
				__sprintf_P(lcd_txt,ru_mode_of_operation_str[4]);														
		}
		lcd_printf(lcd_txt);									
		lcd_set_pos(LCD_Shw_Pos,12);
		ShowTemperatureShort2(lcd_txt,&pid[Active_PID].t0);					
		lcd_printf(lcd_txt);
	}
	rp_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void rp_pid_0()
{
	Active_PID=0;
	rp03();
}
//-----------------------------------------------------------------------------------
void rp_pid_1()
{
	Active_PID=1;	
	rp03();
}
//-----------------------------------------------------------------------------------
// PID MENU SHOW
//-----------------------------------------------------------------------------------
void rp_PID_MODE()
{
#if NUM_PID
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		if(MenuRegs.lang==0)
		{
			if(pid[Active_PID].mode==PID_MODE_STOP)
				__sprintf_P(lcd_txt,eng_mode_of_operation_str[1]);
			if(pid[Active_PID].mode==PID_MODE_AUTO)
				__sprintf_P(lcd_txt,eng_mode_of_operation_str[0]);						
			if(pid[Active_PID].mode==PID_MODE_ERROR)
				__sprintf_P(lcd_txt,eng_mode_of_operation_str[3]);
			if(pid[Active_PID].mode==PID_MODE_WARNING)
				__sprintf_P(lcd_txt,eng_mode_of_operation_str[4]);									
		}
		if(MenuRegs.lang==1)
		{
			if(pid[Active_PID].mode==PID_MODE_STOP)
				__sprintf_P(lcd_txt,ru_mode_of_operation_str[1]);
			if(pid[Active_PID].mode==PID_MODE_AUTO)
				__sprintf_P(lcd_txt,ru_mode_of_operation_str[0]);						
			if(pid[Active_PID].mode==PID_MODE_ERROR)
				__sprintf_P(lcd_txt,ru_mode_of_operation_str[3]);		
			if(pid[Active_PID].mode==PID_MODE_WARNING)
				__sprintf_P(lcd_txt,ru_mode_of_operation_str[4]);														
		}
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	if(Active_Item)
	{
		newmenuitem=0;		
		if(LCD_Time==0)
			newmenuitem=1;		
		// -------- Keys --------------//
		// Up arrow
		if(key0==1)
		{			
			//Menu_Pos=Menu_Pos+Menu[Menu_Pos].PreviosItem;
			if(get_prev_menu())
				if(LCD_Cur_Pos>0)LCD_Cur_Pos--;				
			LCD_Time=0;
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{			
			//Menu_Pos=Menu_Pos+Menu[Menu_Pos].NextItem;
			if(get_next_menu())
				if(LCD_Cur_Pos<(LCD_MAX_LINES-1))LCD_Cur_Pos++;		
			LCD_Time=0;		
			newmenuitem=1;
			key1=2;
		}	
		// Esc
		if(key2==1)
		{
//			if(Menu[Menu_Pos].UpItem != 0)
			if(get_up_menu() != 0)			
			{
				//Menu_Pos=Menu_Pos+Menu[Menu_Pos].UpItem;
//				get_up_menu();
				LCD_Cur_Pos=0;
				lcd_clear();
			}
			LCD_Time=0;	
			newmenuitem=1;
			key2=2;			
		}
		// Enter		
		if(key3==1)
		{
			if(pid[Active_PID].mode==PID_MODE_STOP)pid[Active_PID].mode=PID_MODE_AUTO;
			else pid[Active_PID].mode=PID_MODE_STOP;
			params_store();
			newmenuitem=1;			
			key3=2;			
		}
	}	
#endif
}
//-----------------------------------------------------------------------------------
void rp_PID_T()
{
#if NUM_PID
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		ShowTemperature(lcd_txt,&pid[Active_PID].t0);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	rp_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void rp_PID_POWER()
{
#if NUM_PID
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		ShowPowerShort(lcd_txt,&pid[Active_PID].power);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	rp_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void rp_PID_P()
{
#if NUM_PID
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		WordToStrSigned(lcd_txt,&pid[Active_PID].p);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	rp_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void rp_PID_D()
{
#if NUM_PID
  if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		WordToStrSigned(lcd_txt,&pid[Active_PID].d);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	rp_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void rp_PID_I()
{
#if NUM_PID
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		WordToStrSigned(lcd_txt,&pid[Active_PID].i);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	rp_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void rp_PID_PMAX()
{
#if NUM_PID
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		ShowPowerShort(lcd_txt,&pid[Active_PID].power_max);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	rp_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void rp_PID_PMIN()
{
#if NUM_PID
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		ShowPowerShort(lcd_txt,&pid[Active_PID].power_min);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	rp_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void rp_PID_FAST()
{
#if NUM_PID
	u16 sp;
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		sp=pid[Active_PID].PID_POWER_STEP[1]*1000;
		WordToStr(lcd_txt,&sp,0);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	rp_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void rp_PID_SLOW()
{
#if NUM_PID
	u16 sp;
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		sp=pid[Active_PID].PID_POWER_STEP[0]*1000;
		WordToStr(lcd_txt,&sp,0);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	rp_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void rp_PID_SSUM()
{
#if NUM_PID
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		WordToStrSigned(lcd_txt,&tsum[Active_PID]);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	rp_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void rp_PID_ZEROB()
{
#if NUM_PID
	u16 sp;
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		sp=pid[Active_PID].PID_POWER_LIMIT[0];
		WordToStr(lcd_txt,&sp,0);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	rp_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void rp_PID_LOWB()
{
#if NUM_PID
	u16 sp;
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		sp=pid[Active_PID].PID_POWER_LIMIT[1];
		WordToStr(lcd_txt,&sp,0);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	rp_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void rp_PID_T3()
{
#if NUM_PID
	u16 sp;
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		sp=pid[Active_PID].t3max;
		WordToStr(lcd_txt,&sp,0);
		lcd_printf_pos(LCD_Shw_Pos,10,lcd_txt);
	}	
	rp_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
// PID MENU SHOW
//-----------------------------------------------------------------------------------
void ed_simple_action()
{
#if NUM_PID
	if(Active_Item)
	{
		write_command(0x0D);		
		Delay_mks(1);		
		lcd_set_pos(0,0);
		newmenuitem=0;		
		if(LCD_Time==0)
			newmenuitem=1;		
		// -------- Keys --------------//
		// Up arrow
		if(key0==1)
		{					
			switch(Active_PID_Item)
			{
				case 0:pid[Active_PID].mode=1;break;					
				case 1:if(pid[Active_PID].t0<1500)pid[Active_PID].t0+=5;break;
				case 2:if(pid[Active_PID].power<990)pid[Active_PID].power+=10;break;						
				case 3:if(pid[Active_PID].p<30000)pid[Active_PID].p+=5;break;
				case 4:if(pid[Active_PID].i<30000)pid[Active_PID].i+=5;break;									
				case 5:if(pid[Active_PID].d<30000)pid[Active_PID].d+=5;break;
				case 6:if(pid[Active_PID].ti<240)pid[Active_PID].ti+=1;break;
				case 7:if(pid[Active_PID].power_max<990)pid[Active_PID].power_max+=10;break;
				case 8:if(pid[Active_PID].power_min<990)pid[Active_PID].power_min+=10;break;				
				case 9 :if(pid[Active_PID].PID_POWER_STEP[0]<0.1)pid[Active_PID].PID_POWER_STEP[0]+=0.001;break;
				case 10:if(pid[Active_PID].PID_POWER_STEP[1]<0.4)pid[Active_PID].PID_POWER_STEP[1]+=0.002;break;								
				case 11 :if(pid[Active_PID].PID_POWER_LIMIT[0]<100)pid[Active_PID].PID_POWER_LIMIT[0]+=1;break;
				case 12:if(pid[Active_PID].PID_POWER_LIMIT[1]<400)pid[Active_PID].PID_POWER_LIMIT[1]+=5;break;								
				case 13:if(pid[Active_PID].t3max<400)pid[Active_PID].t3max+=1;break;	
			}
			LCD_Time=0;
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{			
			switch(Active_PID_Item)		
			{
				case 0:pid[Active_PID].mode=0;break;			
				case 1:if(pid[Active_PID].t0>5)pid[Active_PID].t0-=5;else pid[Active_PID].t0=0;break;
				case 2:if(pid[Active_PID].power>-990)pid[Active_PID].power-=10;break;								
				case 3:if(pid[Active_PID].p>5)pid[Active_PID].p-=5;else pid[Active_PID].p=0; break;
				case 4:if(pid[Active_PID].i>5)pid[Active_PID].i-=5;else pid[Active_PID].i=0;break;									
				case 5:if(pid[Active_PID].d>5)pid[Active_PID].d-=5;else pid[Active_PID].d=0;break;
				case 6:if(pid[Active_PID].ti>0)pid[Active_PID].ti-=1;break;
				case 7:if(pid[Active_PID].power_max>10)pid[Active_PID].power_max-=10;else pid[Active_PID].power_max=0;break;
				case 8:if(pid[Active_PID].power_min>10)pid[Active_PID].power_min-=10;else pid[Active_PID].power_min=0;break;
				case 9 :if(pid[Active_PID].PID_POWER_STEP[0]>0)pid[Active_PID].PID_POWER_STEP[0]-=0.001;break;
				case 10:if(pid[Active_PID].PID_POWER_STEP[1]>0.002)pid[Active_PID].PID_POWER_STEP[1]-=0.002;break;								
				case 11 :if(pid[Active_PID].PID_POWER_LIMIT[0]>0)pid[Active_PID].PID_POWER_LIMIT[0]-=1;break;
				case 12:if(pid[Active_PID].PID_POWER_LIMIT[1]>5)pid[Active_PID].PID_POWER_LIMIT[1]-=5;break;
				case 13:if(pid[Active_PID].t3max>0)pid[Active_PID].t3max-=1;break;
			}
			newmenuitem=1;
			key1=2;
		}	
		// Esc
		if(key2==1)
		{
			if(get_up_menu() != 0)			
			{
				LCD_Cur_Pos=0;
				lcd_clear();
			}
			write_command(0x0c);		
			Delay_mks(1);				
			LCD_Time=0;	
			newmenuitem=1;
			key2=2;			
		}
		// Enter		
		if(key3==1)
		{
			if(get_up_menu() != 0)						
			{
				LCD_Cur_Pos=0;
				lcd_clear();
				params_store();	
			}
			write_command(0x0c);		
			Delay_mks(1);				
			LCD_Time=0;		
			newmenuitem=1;			
			key3=2;			
		}
	}	
#endif
}
//-----------------------------------------------------------------------------------
void ed_PID_T()
{
#if NUM_PID
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		ShowTemperature(lcd_txt,&pid[Active_PID].t0);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	Active_PID_Item=1;
	ed_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void ed_PID_POWER()
{
#if NUM_PID
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		ShowPowerShort(lcd_txt,&pid[Active_PID].power);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	Active_PID_Item=1;
	ed_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void ed_PID_P()
{
#if NUM_PID
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		WordToStrSigned(lcd_txt,&pid[Active_PID].p);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	Active_PID_Item=3;
	ed_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void ed_PID_D()
{
#if NUM_PID
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		WordToStrSigned(lcd_txt,&pid[Active_PID].d);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	Active_PID_Item=5;
	ed_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void ed_PID_I()
{
#if NUM_PID
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		WordToStrSigned(lcd_txt,&pid[Active_PID].i);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	Active_PID_Item=4;
	ed_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void ed_PID_PMAX()
{
#if NUM_PID
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		ShowPowerShort(lcd_txt,&pid[Active_PID].power_max);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	Active_PID_Item=7;
	ed_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void ed_PID_PMIN()
{
#if NUM_PID
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		ShowPowerShort(lcd_txt,&pid[Active_PID].power_min);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	Active_PID_Item=8;
	ed_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void ed_PID_FAST()
{
#if NUM_PID
	u16 sp;
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		sp=pid[Active_PID].PID_POWER_STEP[1]*1000;
		WordToStr(lcd_txt,&sp,0);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	Active_PID_Item=10;
	ed_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void ed_PID_SLOW()
{
#if NUM_PID
	u16 sp;
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		sp=pid[Active_PID].PID_POWER_STEP[0]*1000;
		WordToStr(lcd_txt,&sp,0);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	Active_PID_Item=9;
	ed_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void ed_PID_SSUM()
{
#if NUM_PID
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		WordToStrSigned(lcd_txt,&tsum[Active_PID]);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	Active_PID_Item=1;
	ed_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void ed_PID_ZEROB()
{
#if NUM_PID
	u16 sp;
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		sp=pid[Active_PID].PID_POWER_LIMIT[0];
		WordToStr(lcd_txt,&sp,0);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	Active_PID_Item=11;
	ed_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void ed_PID_LOWB()
{
#if NUM_PID
	u16 sp;
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		sp=pid[Active_PID].PID_POWER_LIMIT[1];
		WordToStr(lcd_txt,&sp,0);
		lcd_printf_pos(LCD_Shw_Pos,8,lcd_txt);
	}	
	Active_PID_Item=12;
	ed_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
void ed_PID_T3()
{
#if NUM_PID
	u16 sp;
	if(newmenuitem)
	{
		LCD_Time=1000;	
		lcd_clear_pos(LCD_Shw_Pos);
		lcd_printf_pos(LCD_Cur_Pos,0,">");		
		lcd_printf_P_pos(LCD_Shw_Pos,1,Menu[Menu_Pos].str[MenuRegs.lang]);
		sp=pid[Active_PID].t3max;
		WordToStr(lcd_txt,&sp,0);
		lcd_printf_pos(LCD_Shw_Pos,10,lcd_txt);
	}	
	Active_PID_Item=13;
	ed_simple_action();
#endif
}
//-----------------------------------------------------------------------------------
