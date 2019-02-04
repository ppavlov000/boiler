//-----------------------------------------------------------------------------------
#include "..\main.h" 
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
	"¿¬“ŒÃ¿“",				//0
	"—“Œœ",					//1	
	"–”◊ÕŒ…",				//2
	"¿¬¿–—“",				//3	
	"¿¬¿–»ﬂ",				//4	
};
in_flash u8	ru_mode_of_operation_str[OPERATION_MODES_NUM][8]=
{ 
	"¿¬“Œ",				//0
	"—“Œœ",				//1	
	"–”◊Õ",				//2
	"¿¬—“",				//3	
	"¿¬¿–",				//4		
};
in_flash u8	ru_mode_of_controller_str[3][8]=
{ 
	"¿¬“",				//0
	"À≈“",				//1
	"«»Ã",				//2
};
in_flash u8	ru_mode_of_controller_str_full[3][8]=
{ 
	"¿¬“Œ",				//0
	"À≈“Œ",			//1
	"«»Ã¿",			//2
};
/*
in_flash u8	ru_errors_str[ERRORS_NUM][32]=
{ 
	"ÕÂÚ",					//0
	"–‡ÁÏÓÓÁÍ‡",			//1
	"ƒ‡Ú˜ËÍ",				//2
	"Œ¯Ë·Í‡ 2",				//3
	"Œ¯Ë·Í‡ 3",				//4
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
	"¬ÍÎ   =",	1,	//0
	"“ÂÏÔ T=",	1,	//1
	"“ÂÍ  P=",	2,	//2						
	"œÓÔ P=",	2,	//3	
	"»ÌÚ  I=",	2,	//4
	"ƒËÙÙ D=",	2,	//5	
	"»ÌÚ„ T=",	2,	//6	
	"Ã‡ÍÒ P=",	2,	//7			
	"ÃËÌ  P=",	2,	//8				
};
//-----------------------------------------------------------------------------------
void lcd_menu_choose_pid_parameter()
{
//	s16 tmp;
	u8 i,j,pos_old;
	u8 cline;
	u8 edit_pos_tmp;	
	u8 show_pos=0;
	if(newmenuitem)
	{
		if(MenuRegs.lang==0) 
			menu_str=&eng_pid_params_full[0];
		if(MenuRegs.lang==1)
			menu_str=&ru_pid_params_full[0];
			
		for(i=pos;i<(PID_PARAMETERS_NUM-2);i++)
			if(menu_str[i].lvl<=password_lvl)
			{
				pos=i;
				break;
			}								
		LCD_Time=1000;	
		lcd_clear();
		memset(lcd_txt, 0, sizeof(lcd_txt));	
		show_pos=pos & 0xfe;
		for(i=show_pos;i<show_pos+2;i++)					
		{
			cline=i-show_pos;
			lcd_set_pos(cline,1);
			if(i<PID_PARAMETERS_NUM)	
			{						
				if(menu_str[i].lvl>password_lvl)
				{
					pos_old=i;
					for(j=i+1;j<(PID_PARAMETERS_NUM);j++)
						if(menu_str[j].lvl<=password_lvl)
						{
							i=j;
							break;
						}
				}	
				if(menu_str[i].lvl<=password_lvl)
				{				
					__sprintf_P(lcd_txt,menu_str[i].str);					
					lcd_printf(lcd_txt);	
					lcd_set_pos(cline,8);	
					switch(i)
					{
						case 0:					
							if(MenuRegs.lang==0)
							{
								if(pid[current_pid].mode==PID_MODE_STOP)
									__sprintf_P(lcd_txt,eng_mode_of_operation_str[1]);
								if(pid[current_pid].mode==PID_MODE_AUTO)
									__sprintf_P(lcd_txt,eng_mode_of_operation_str[0]);						
								if(pid[current_pid].mode==PID_MODE_ERROR)
									__sprintf_P(lcd_txt,eng_mode_of_operation_str[3]);
								if(pid[current_pid].mode==PID_MODE_WARNING)
									__sprintf_P(lcd_txt,eng_mode_of_operation_str[4]);									
							}
							if(MenuRegs.lang==1)
							{
								if(pid[current_pid].mode==PID_MODE_STOP)
									__sprintf_P(lcd_txt,ru_mode_of_operation_str[1]);
								if(pid[current_pid].mode==PID_MODE_AUTO)
									__sprintf_P(lcd_txt,ru_mode_of_operation_str[0]);						
								if(pid[current_pid].mode==PID_MODE_ERROR)
									__sprintf_P(lcd_txt,ru_mode_of_operation_str[3]);		
								if(pid[current_pid].mode==PID_MODE_WARNING)
									__sprintf_P(lcd_txt,ru_mode_of_operation_str[4]);														
							}
						break;								
						case 1:ShowTemperature(lcd_txt,&pid[current_pid].t0);break;
						case 2:ShowPowerShort(lcd_txt,&pid[current_pid].power);break;			
						case 3:WordToStrSigned(lcd_txt,&pid[current_pid].p);break;
						case 4:WordToStrSigned(lcd_txt,&pid[current_pid].i);break;									
						case 5:WordToStrSigned(lcd_txt,&pid[current_pid].d);;break;
						case 6:WordToStr(lcd_txt,&pid[current_pid].ti,0);break;
						case 7:ShowPowerShort(lcd_txt,&pid[current_pid].power_max);break;
						case 8:ShowPowerShort(lcd_txt,&pid[current_pid].power_min);break;				
					}
					lcd_printf(lcd_txt);
				}
				else
				{
					__sprintf_P(lcd_txt,empty_str);				
					lcd_printf(lcd_txt);			
				}	
			}
			else
			{
				__sprintf_P(lcd_txt,empty_str);				
				lcd_printf(lcd_txt);			
			}			
		}			
		edit_pos_tmp=pos & 0x01;		
		lcd_set_pos(0,0);lcd_printf(" ");
		lcd_set_pos(1,0);lcd_printf(" ");
		switch(edit_pos_tmp)
		{
			case 0:lcd_set_pos(0,0);lcd_printf(">");break;
			case 1:lcd_set_pos(1,0);lcd_printf(">");break;
		}		
	}
	newmenuitem=0;	
	if(LCD_Time==0)
		newmenuitem=1;		
		// -------- Keys --------------//
		// Up arrow
		if(key0==1)
		{
			pos_old=pos;
			if(pos!=0)pos--;
			for(i=pos;i!=0;i--)
				if(menu_str[i].lvl<=password_lvl)
				{
					pos=i;
					break;
				}
			if(menu_str[pos].lvl>password_lvl)pos=pos_old;
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{
			pos_old=pos;
			if(pos<(PID_PARAMETERS_NUM-1))pos++;
			for(i=pos;i<(PID_PARAMETERS_NUM-1);i++)
				if(menu_str[i].lvl<=password_lvl)
				{
					pos=i;
					break;
				}
			if(menu_str[pos].lvl>password_lvl)pos=pos_old;			
			newmenuitem=1;
			key1=2;
		}
		// Esc
		if(key2==1)
		{
			if(LCDMenuPtr->UpItem!=NULL)
			{
				LCDMenuPtr=(TLCDMenuItem*)LCDMenuPtr->UpItem;
//				LCDMenuPtr=Previos_LCDMenuPtr;
				newmenuitem=1;		
				pos=0;				
			}	
			newmenuitem=1;				
			key2=2;			
		}
		// Enter		
		if(key3==1)
		{
//			if(password_lvl)
			if(pos==0)
			{
				if(pid[current_pid].mode==PID_MODE_STOP)pid[current_pid].mode=PID_MODE_AUTO;
				else pid[current_pid].mode=PID_MODE_STOP;
				newmenuitem=1;	
			}
			else
			if(LCDMenuPtr->SubItem!=NULL)
			{	
				LCDMenuPtr=(TLCDMenuItem*)LCDMenuPtr->SubItem;
				newmenuitem=1;									
			}	
			key3=2;			
		}	
}
//-----------------------------------------------------------------------------------
void lcd_menu_edit_pid_parameter()
{
//	s16 tmp;
	u8 show_pos;
	u8 edit_pos_tmp,i,j,cline;	
	if(newmenuitem)
	{
		if(MenuRegs.lang==0) 
			menu_str=&eng_pid_params_full[0];
		if(MenuRegs.lang==1)
			menu_str=&ru_pid_params_full[0];
		for(i=pos;i<(PID_PARAMETERS_NUM-2);i++)
			if(menu_str[i].lvl<=password_lvl)
			{
				pos=i;
				break;
			}					
		LCD_Time=1000;	
		lcd_clear();
		memset(lcd_txt, 0, sizeof(lcd_txt));	
		show_pos=pos & 0xfe;
		for(i=show_pos;i<show_pos+2;i++)					
		{
			cline=i-show_pos;
			lcd_set_pos(cline,1);
			if(i<PID_PARAMETERS_NUM)	
			{						
				if(menu_str[i].lvl>password_lvl)
				{
//					pos_old=i;
					for(j=i+1;j<(PID_PARAMETERS_NUM);j++)
						if(menu_str[j].lvl<=password_lvl)
						{
							i=j;
							break;
						}
				}	
				if(menu_str[i].lvl<=password_lvl)
				{				
					__sprintf_P(lcd_txt,menu_str[i].str);					
					lcd_printf(lcd_txt);	
					lcd_set_pos(cline,8);	
					switch(i)
					{
						case 0:					
							if(MenuRegs.lang==0)
							{
								if(pid[current_pid].mode==PID_MODE_STOP)
									__sprintf_P(lcd_txt,eng_mode_of_operation_str[1]);
								if(pid[current_pid].mode==PID_MODE_AUTO)
									__sprintf_P(lcd_txt,eng_mode_of_operation_str[0]);						
								if(pid[current_pid].mode==PID_MODE_ERROR)
									__sprintf_P(lcd_txt,eng_mode_of_operation_str[3]);
								if(pid[current_pid].mode==PID_MODE_WARNING)
									__sprintf_P(lcd_txt,eng_mode_of_operation_str[4]);									
							}
							if(MenuRegs.lang==1)
							{
								if(pid[current_pid].mode==PID_MODE_STOP)
									__sprintf_P(lcd_txt,ru_mode_of_operation_str[1]);
								if(pid[current_pid].mode==PID_MODE_AUTO)
									__sprintf_P(lcd_txt,ru_mode_of_operation_str[0]);						
								if(pid[current_pid].mode==PID_MODE_ERROR)
									__sprintf_P(lcd_txt,ru_mode_of_operation_str[3]);		
								if(pid[current_pid].mode==PID_MODE_WARNING)
									__sprintf_P(lcd_txt,ru_mode_of_operation_str[4]);														
							}
						break;								
						case 1:ShowTemperature(lcd_txt,&pid[current_pid].t0);break;
						case 2:ShowPowerShort(lcd_txt,&pid[current_pid].power);break;			
						case 3:WordToStrSigned(lcd_txt,&pid[current_pid].p);break;
						case 4:WordToStrSigned(lcd_txt,&pid[current_pid].i);break;									
						case 5:WordToStrSigned(lcd_txt,&pid[current_pid].d);;break;
						case 6:WordToStr(lcd_txt,&pid[current_pid].ti,0);break;
						case 7:ShowPowerShort(lcd_txt,&pid[current_pid].power_max);break;
						case 8:ShowPowerShort(lcd_txt,&pid[current_pid].power_min);break;				
					}
					lcd_printf(lcd_txt);
				}
				else
				{
					__sprintf_P(lcd_txt,empty_str);				
					lcd_printf(lcd_txt);			
				}	
			}
			else
			{
				__sprintf_P(lcd_txt,empty_str);				
				lcd_printf(lcd_txt);			
			}			
		}					
		write_command(0x0D);		
		Delay_mks(1);
		edit_pos_tmp=pos & 0x01;		
		lcd_set_pos(0,0);lcd_printf(" ");
		lcd_set_pos(1,0);lcd_printf(" ");
		switch(edit_pos_tmp)
		{
			case 0:lcd_set_pos(0,0);lcd_printf(">");lcd_set_pos(0,0);break;
			case 1:lcd_set_pos(1,0);lcd_printf(">");lcd_set_pos(1,0);break;
		}		
	}
	newmenuitem=0;	
		// -------- Keys --------------//
		// Up arrow
		if(key0==1)
		{
			switch(pos)		
			{
				case 0:pid[current_pid].mode=1;break;					
				case 1:if(pid[current_pid].t0<1500)pid[current_pid].t0+=5;break;
				case 2:if(pid[current_pid].power<990)pid[current_pid].power+=10;break;						
				case 3:if(pid[current_pid].p<30000)pid[current_pid].p+=5;break;
				case 4:if(pid[current_pid].i<30000)pid[current_pid].i+=5;break;									
				case 5:if(pid[current_pid].d<30000)pid[current_pid].d+=5;break;
				case 6:if(pid[current_pid].ti<240)pid[current_pid].ti+=1;break;
				case 7:if(pid[current_pid].power_max<990)pid[current_pid].power_max+=10;break;
				case 8:if(pid[current_pid].power_min<990)pid[current_pid].power_min+=10;break;
			}
			newmenuitem=1;
			key0=2;			
		}
		// Down arrow		
		if(key1==1)
		{
			switch(pos)		
			{
				case 0:pid[current_pid].mode=0;break;			
				case 1:if(pid[current_pid].t0>5)pid[current_pid].t0-=5;else pid[current_pid].t0=0;break;
				case 2:if(pid[current_pid].power>-990)pid[current_pid].power-=10;break;								
				case 3:if(pid[current_pid].p>-30000)pid[current_pid].p-=5;break;
				case 4:if(pid[current_pid].i>-30000)pid[current_pid].i-=5;break;									
				case 5:if(pid[current_pid].d>-30000)pid[current_pid].d-=5;break;
				case 6:if(pid[current_pid].ti>0)pid[current_pid].ti-=1;break;
				case 7:if(pid[current_pid].power_max>-990)pid[current_pid].power_max-=10;break;
				case 8:if(pid[current_pid].power_min>-990)pid[current_pid].power_min-=10;break;
			}
			newmenuitem=1;
			key1=2;
		}
		// Esc
		if(key2==1)
		{
			if(LCDMenuPtr->UpItem!=NULL)
			{
				LCDMenuPtr=(TLCDMenuItem*)LCDMenuPtr->UpItem;
//				LCDMenuPtr=Previos_LCDMenuPtr;
				newmenuitem=1;		
				pos=0;				
			}	
			write_command(0x0c);		
			Delay_mks(1);				
			newmenuitem=1;				
			key2=2;			
		}
		// Enter		
		if(key3==1)
		{
			write_command(0x0c);		
			Delay_mks(1);							
			if(LCDMenuPtr->UpItem!=NULL)
			{
				LCDMenuPtr=(TLCDMenuItem*)LCDMenuPtr->UpItem;													
				newmenuitem=1;		
				params_store();								
			}	
			key3=2;			
		}	
}
//-----------------------------------------------------------------------------------
