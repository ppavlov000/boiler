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
//extern TLCDPictTop Scr_4;
extern __farflash TLCDPict_Txt _Txt_0;
extern __farflash TLCDPict_Txt _Txt_1;
extern __farflash TLCDPict_Txt _Txt_2;
extern __farflash TLCDPict_Txt _Txt_3;
extern __farflash TLCDPict_Txt _Txt_4;
//-----------------------------------------------------------------------------------
#define MAX_LINE_COL 0
#define MAX_LINE_ROW 12
//-----------------------------------------------------------------------------------
u8 Current_ID=1;
u8 Temporary_ID=0;
u8 scan_mode=0;
u8 scan_result=0;
extern u8 str[40];
extern u8 str2[20];
extern u8 step;
extern u8 new_step;
extern u8 Branch_Number;
extern u8 Start_Up_Time;
TExSTATUS *Status_Local;
u8 line_row;
u8 line_col;
u8 offset;
u8 device_found=0;
u8 device_id[MAX_DEVICES_NUM]={0};
TDevice_Info device_info[MAX_DEVICES_NUM]={0};
u8 device_ptr=0;
u8 Common_ID_Mode=0;
u8 what_to_show=0;	// 0-working regs 1-sys 2-user
//-----------------------------------------------------------------------------------
void scr44_init();
void scr44_close();
void scr44_routine();

void show_device_list();
#define	_Butt_Work Obj[8]
#define	_Butt_Sys Obj[9]
#define	_Butt_User Obj[10]
//-----------------------------------------------------------------------------------
void scr44_Scan()
{
	if(step)return;
	lcd_clear_text();
	lcd_sprintf("All devices",1,3);	
	Common_ID_Mode=1;	
	Current_ID=0;	
//	FT_Time=500;
	device_found=0;
	memset(device_id,0,sizeof(device_id));
	memset(device_info,0,sizeof(device_info));
	Temporary_ID=0;
	Current_ID=1;
	device_ptr=0;
	line_col=0;
	line_row=0;
	new_step=1;
	Switch_To_Main_Time=60;	
}
//-----------------------------------------------------------------------------------
void scr44_Up()
{
	if(step)return;
	FT_Time=0;
	Switch_To_Main_Time=60;	
	lcd_sprintf(" ",0,4+device_ptr);	
	if(device_ptr!=0){
		device_ptr--;
		if(device_id[device_ptr]==0)device_ptr++;
		Current_ID=device_id[device_ptr];
		lcd_sprintf(">",0,4+device_ptr);
	}
	else{
		Current_ID=0;
		Common_ID_Mode=1;
		lcd_sprintf(">",0,3);
	}
}
//-----------------------------------------------------------------------------------
void scr44_Down()
{
	if(step)return;	
	FT_Time=0;
	Switch_To_Main_Time=60;	
	if(Common_ID_Mode){
		Common_ID_Mode=0;
		lcd_sprintf(" ",0,3);		
		device_ptr=0;
		Current_ID=device_id[device_ptr];
		lcd_sprintf(">",0,4+device_ptr);	
	}
	else
	{
		lcd_sprintf(" ",0,4+device_ptr);
		if(device_ptr<MAX_DEVICES_NUM-1){
			device_ptr++;
			if(device_id[device_ptr]==0)device_ptr--;		
		}
		Current_ID=device_id[device_ptr];
		lcd_sprintf(">",0,4+device_ptr);
	}
}

//-----------------------------------------------------------------------------------
void scr44_draw_butt()
{
	switch(what_to_show)
	{
	case 0:
		if(_Butt_Work.Stat!=1){_Butt_Work.Stat=1; show_single_bmp(&_Butt_Work,0);	}
		if(_Butt_Sys.Stat!=0){_Butt_Sys.Stat=0; show_single_bmp(&_Butt_Sys,0);	}
		if(_Butt_User.Stat!=0){_Butt_User.Stat=0; show_single_bmp(&_Butt_User,0);	}
		break;
	case 1:
		if(_Butt_Work.Stat!=0){_Butt_Work.Stat=0; show_single_bmp(&_Butt_Work,0);	}
		if(_Butt_Sys.Stat!=1){_Butt_Sys.Stat=1; show_single_bmp(&_Butt_Sys,0);	}
		if(_Butt_User.Stat!=0){_Butt_User.Stat=0; show_single_bmp(&_Butt_User,0);	}
		break;
	case 2:
		if(_Butt_Work.Stat!=0){_Butt_Work.Stat=0; show_single_bmp(&_Butt_Work,0);	}
		if(_Butt_Sys.Stat!=0){_Butt_Sys.Stat=0; show_single_bmp(&_Butt_Sys,0);	}
		if(_Butt_User.Stat!=1){_Butt_User.Stat=1; show_single_bmp(&_Butt_User,0);	}
		break;
	}
}
//-----------------------------------------------------------------------------------
void scr44_Work()
{
	what_to_show=0;
	scr44_draw_butt();	
	show_device_list();
		
}
//-----------------------------------------------------------------------------------
void scr44_Sys()
{
	what_to_show=1;
	scr44_draw_butt();	
	show_device_list();
}
//-----------------------------------------------------------------------------------
void scr44_User()
{
	what_to_show=2;
	scr44_draw_butt();	
	show_device_list();
}
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_44_Scan=
{	
	26,16,35,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	scr44_Scan,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_44_Up=
{	
	26,16+48,36,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	scr44_Up,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_44_Down=
{	
	26,16+48+32,39,
	(bit_visible+bit_active),
	0,
	0,
	0,	
	scr44_Down,
	NULL,
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_44_Work=
{	
	6,117,64,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr44_Work,
	NULL,
};
//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_44_Sys=
{	
	12,117,65,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr44_Sys,
	NULL,
};

//-----------------------------------------------------------------------------------
__farflash TLCDPict _Page_44_User=
{	
	18,117,66,
	(bit_visible+bit_active+bit_trigger),
	0,
	0,
	0,	
	scr44_User,
	NULL,
};


//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
TLCDPictTop Scr_44=
{
	0,0,0,
//	(bit_visible+bit_full),
	0,
	11,
	0,	
	scr44_init,
	scr44_routine,
	scr44_close,		
};
//-----------------------------------------------------------------------------------
void scr44_init()
{
//	u8 i;
	Branch_Number=4;
	new_step=step=0;
	line_row=0;
	line_col=0;
	offset=0;
	
//	device_found=0;
//	memset(device_id,0,sizeof(device_id));
	Temporary_ID=0;
//	device_ptr=0;
	line_col=0;
	line_row=0;	
	new_step=0;
	lcd_clear_text();
	lcd_sprintf(">All devices",0,3);	
	Common_ID_Mode=1;	
	Current_ID=0;	

//	line_row=1;	
	
	Obj[0]=_Menu0;	
	Obj[1]=_Menu1;	
	Obj[2]=_Menu2;	
	Obj[3]=_Menu3;		
	Obj[4]=_Menu4;	
	
	Obj[5]=_Page_44_Scan;	
	Obj[6]=_Page_44_Up;	
	Obj[7]=_Page_44_Down;	
	
	Obj[8]=_Page_44_Work;	
	Obj[9]=_Page_44_Sys;	
	Obj[10]=_Page_44_User;		

	Obj[4].Stat=1;
	show_device_list();
	scr44_draw_butt();	
	
}
//-----------------------------------------------------------------------------------
void scr44_close()
{
	u8 i;
	for(i=0;i<Scr_44.Txt_Num;i++)
		clear_single_bmp_txt(&Txt[i]);
	clear_page();
	lcd_clear_text();
	Common_ID_Mode=0;
//	Current_ID=1;
}
//-----------------------------------------------------------------------------------
void scr44_routine()
{
//	u8 tmp,i;		
//	u16 temp;
//	u8 tmp0;//,tmp1,tmp2; lc
//	u8 old_stat;
//	s16 temperature;
	if(FT_Time!=0)return;
	FT_Time=500;
	if(page_offset!=PAGE_0_OFFSET)return;
	// Print current channel statistic
	strcpy(str,"              ");	
	lcd_sprintf(str,0,2);	
	strcpy(str,"ID ");
	ByteToStrFillZero(str2,&Current_ID,0,2,'0');
	stradd(str,str2);
	lcd_sprintf(str,0,2);	
	// Newer exit this menu until something will be connected
	if(Start_Up_Time==0)
		if(device_found==0)	Switch_To_Main_Time=60;
//	ShowPowerShort(str2,&M_history.lost[M.channel]);
//	lcd_sprintf(str2,6,2);	
}
//-----------------------------------------------------------------------------------
void show_device_info_0(u8 num)
{
	s8 i;
	if(device_info[num].id==0)
	{
		str[0]=0;
		for(i=0;i<29;i++)stradd(str," ");
		return;
	}
	switch(device_info[num].type)
	{
		case BOOT_PANEL: strcpy(str,"BP");break;
		case BOOT_CONTROLLER: strcpy(str,"BC");break;
		case MAIN_PANEL: strcpy(str,"MP");break;
		case MAIN_CONTROLLER: strcpy(str,"MC");break;
	}				
	ByteToStrFillZero(str2,&device_info[num].id,0,2,'0');
	stradd(str,str2);	
	stradd(str," ");	
/* Serial number					
//					ByteToStrFillZero(str2,&M_rx.field.d[4],1,2,'0');
//					stradd(str,str2);	
//					ByteToStrFillZero(str2,&M_rx.field.d[3],1,2,'0');
//					stradd(str,str2);	
					ByteToStrFillZero(str2,&M_rx.field.d[2],1,2,'0');
					stradd(str,str2);	
					ByteToStrFillZero(str2,&M_rx.field.d[1],1,2,'0');
					stradd(str,str2);	
*/
	stradd(str,"");
	ByteToStr(str2,&device_info[num].mode,0);
	stradd(str,str2);	

	stradd(str," ");
	if(device_info[num].t>999)device_info[num].t=999;
	ShowTemperatureShort(str2,&device_info[num].t);
	stradd(str,str2);	

	stradd(str," ");
	if(device_info[num].tp>999)device_info[num].tp=999;
	ShowTemperatureShort(str2,&device_info[num].tp);			
	stradd(str,str2);	

	stradd(str," ");
	if(device_info[num].power>999)device_info[num].power=999;
	ShowPowerShort(str2,&device_info[num].power);			
	stradd(str,str2);														
	
//	lcd_sprintf(str,1+6*line_col,4+line_row);		
	i=29-strlen2(str);
	for(;i>0;i--)stradd(str," ");	
}
//-----------------------------------------------------------------------------------
void show_device_info_1(u8 num)
{
	s8 i;
	if(device_info[num].id==0)
	{
		str[0]=0;
		for(i=0;i<29;i++)stradd(str," ");
		return;
	}
	switch(device_info[num].type)
	{
		case BOOT_PANEL: strcpy(str,"BP");break;
		case BOOT_CONTROLLER: strcpy(str,"BC");break;
		case MAIN_PANEL: strcpy(str,"MP");break;
		case MAIN_CONTROLLER: strcpy(str,"MC");break;
	}				
	ByteToStrFillZero(str2,&device_info[num].id,0,2,'0');
	stradd(str,str2);	
	stradd(str," ");	
// Serial number					
//	ByteToStrFillZero(str2,((u8*)&device_info[num].hw_sys + 3),1,2,'0');
//	stradd(str,str2);	
//	ByteToStrFillZero(str2,((u8*)&device_info[num].hw_sys + 2),1,2,'0');
//	stradd(str,str2);	
	ByteToStrFillZero(str2,((u8*)&device_info[num].hw_sys + 1),1,2,'0');
	stradd(str,str2);	
	ByteToStrFillZero(str2,((u8*)&device_info[num].hw_sys + 0),1,2,'0');
	stradd(str,str2);	
	
	stradd(str," ");	
	ByteToStrFillZero(str2,((u8*)&device_info[num].sys_time.field.Date),0,2,'0');
	stradd(str,str2);stradd(str,"/");
	ByteToStrFillZero(str2,((u8*)&device_info[num].sys_time.field.Month),0,2,'0');
	stradd(str,str2);stradd(str,"/");
	ByteToStrFillZero(str2,((u8*)&device_info[num].sys_time.field.Year),0,2,'0');
	stradd(str,str2);
	
	stradd(str," ");	
	ByteToStrFillZero(str2,((u8*)&device_info[num].sys_time.field.Hour),0,2,'0');
	stradd(str,str2);stradd(str,".");
	ByteToStrFillZero(str2,((u8*)&device_info[num].sys_time.field.Minute),0,2,'0');
	stradd(str,str2);
	
	i=29-strlen2(str);
	for(;i>0;i--)stradd(str," ");
//	if(strlen2(str)<)
//	lcd_sprintf(str,1+6*line_col,4+line_row);		
}
//-----------------------------------------------------------------------------------
void show_device_info_2(u8 num)
{
	s8 i;
	if(device_info[num].id==0)
	{
		str[0]=0;
		for(i=0;i<29;i++)stradd(str," ");
		return;
	}
	switch(device_info[num].type)
	{
		case BOOT_PANEL: strcpy(str,"BP");break;
		case BOOT_CONTROLLER: strcpy(str,"BC");break;
		case MAIN_PANEL: strcpy(str,"MP");break;
		case MAIN_CONTROLLER: strcpy(str,"MC");break;
	}				
	ByteToStrFillZero(str2,&device_info[num].id,0,2,'0');
	stradd(str,str2);	
	stradd(str," ");	
// Serial number					
//	ByteToStrFillZero(str2,((u8*)&device_info[num].hw_usr + 3),1,2,'0');
//	stradd(str,str2);	
//	ByteToStrFillZero(str2,((u8*)&device_info[num].hw_usr + 2),1,2,'0');
//	stradd(str,str2);	
	ByteToStrFillZero(str2,((u8*)&device_info[num].hw_usr + 1),1,2,'0');
	stradd(str,str2);	
	ByteToStrFillZero(str2,((u8*)&device_info[num].hw_usr + 0),1,2,'0');
	stradd(str,str2);	
	
	stradd(str," ");	
	ByteToStrFillZero(str2,((u8*)&device_info[num].usr_time.field.Date),0,2,'0');
	stradd(str,str2);stradd(str,"/");
	ByteToStrFillZero(str2,((u8*)&device_info[num].usr_time.field.Month),0,2,'0');
	stradd(str,str2);stradd(str,"/");
	ByteToStrFillZero(str2,((u8*)&device_info[num].usr_time.field.Year),0,2,'0');
	stradd(str,str2);

	stradd(str," ");	
	ByteToStrFillZero(str2,((u8*)&device_info[num].usr_time.field.Hour),0,2,'0');
	stradd(str,str2);stradd(str,".");
	ByteToStrFillZero(str2,((u8*)&device_info[num].usr_time.field.Minute),0,2,'0');
	stradd(str,str2);
	
	i=29-strlen2(str);
	for(;i>0;i--)stradd(str," ");
//	if(strlen2(str)<)
//	lcd_sprintf(str,1+6*line_col,4+line_row);		
}
//-----------------------------------------------------------------------------------
// u8 device_ptr
// u8 offset
void show_device_list()
{
	u8 i;
	for(i=0;i<MAX_LINE_ROW;i++)
	{
//		if(device_ptr+)
		switch(what_to_show)
		{
		case 0:show_device_info_0(i);break;
		case 1:show_device_info_1(i);break;
		case 2:show_device_info_2(i);break;		
		}
//		lcd_sprintf("                            ",1,4+i);		
		lcd_sprintf(str,1,4+i);
	}
}
//-----------------------------------------------------------------------------------
void Schedule_N4()
{
//	u16 i,tmp;
	u8 tmp;
	s16 ts16;
	M_state_machine();
	if((M.status==st_none)||(M.status==st_complete))
	{		
		if((M.error==0)&&(M.rxnew==1))
		{
			M.rxnew=0;
			switch(M_rx.field.com.bit.com)
			{
				case com_get_stat:		
					if(device_found!=0)
						if(device_info[device_found-1].id==M_rx.field.com.bit.id)break;					
					Status_Local=(TExSTATUS*)&M_rx.field.d[30];	
//					ft=Status->ft;									
//--------------------					
					device_info[device_found].id=M_rx.field.com.bit.id;					
					device_info[device_found].type=M_rx.field.d[0];
					device_info[device_found].hw_sys=*(u32*)&M_rx.field.d[1];
					device_info[device_found].sys_time=*(TTime*)&M_rx.field.d[5];
					
					device_info[device_found].hw_usr=*(u32*)&M_rx.field.d[1+12];
					device_info[device_found].usr_time=*(TTime*)&M_rx.field.d[5+12];					
					
					device_info[device_found].mode=Status_Local->Controller_Mode;
					device_info[device_found].t=Status_Local->Temperature;
					device_info[device_found].tp=Status_Local->Preset_Temperature;					
					device_info[device_found].power=Status_Local->Preset_Speed;					
//--------------------																
					device_id[device_found]=M_rx.field.com.bit.id;
					show_device_info_0(device_found);
/*					
					switch(M_rx.field.d[0])
					{
						case BOOT_PANEL: strcpy(str,"BP");break;
						case BOOT_CONTROLLER: strcpy(str,"BC");break;
						case MAIN_PANEL: strcpy(str,"MP");break;
						case MAIN_CONTROLLER: strcpy(str,"MC");break;
					}				
					tmp=M_rx.field.com.bit.id;
					ByteToStrFillZero(str2,&tmp,0,2,'0');
					stradd(str,str2);	
					stradd(str," ");	

					stradd(str,"");
					tmp=Status_Local->Controller_Mode;
					ByteToStr(str2,&tmp,0);
					stradd(str,str2);	

					stradd(str," ");
					ts16=Status_Local->Temperature;
					if(ts16>999)ts16=999;
					ShowTemperatureShort(str2,&ts16);
					stradd(str,str2);	

					stradd(str," ");
					ts16=Status_Local->Preset_Temperature;
					if(ts16>999)ts16=999;
					ShowTemperatureShort(str2,&ts16);			
					stradd(str,str2);	

					stradd(str," ");
					ts16=Status_Local->Preset_Speed;
					if(ts16>999)ts16=999;
					ShowPowerShort(str2,&ts16);			
					stradd(str,str2);									
					
//						Status_Local->Temperature
//						Fan_Speed=Status_Local->Preset_Speed;
//						Preset=Status_Local->Preset_Temperature;	
*/						
//					lcd_sprintf(str,1+6*line_col,4+line_row);						
//					if(device_found==0)Temporary_ID=Current_ID;
					device_found++;
//					line_row++;
//					if(line_row>MAX_LINE_ROW){
//						line_row=0;
//						if(line_col<MAX_LINE_COL-1)
//							line_col++;
//						else{
//							step=0; // Stop scan
//							Current_ID=device_id[0];
//						}
//					}
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
			if(Time0==0)
			switch(step)
			{
				case 1:
					step+=1;
					M_Get_Controller_Status(Current_ID,Current_ID);
					Current_ID++;
					if(Current_ID>=MAX_DEVICES_NUM)
					{
						step=0;
						Common_ID_Mode=1;	
						Current_ID=0;	
						lcd_sprintf(">",0,3+device_ptr);	
						if(device_found==0)
							lcd_sprintf("Nothing found!",7,8);	
						else
							show_device_list();						
					}
					M_SCH_Time=20;
				break;				
				case 2:
					step++;
//					step=1;					
					M_Get_Controller_Status(Current_ID,Current_ID);
					M_SCH_Time=20;					
				break;				
				case 3:
//					step++;
					step=1;					
					M_Get_Controller_Status(Current_ID,Current_ID);
					M_SCH_Time=20;					
				break;				
			}
		}		
	}	
}
//-----------------------------------------------------------------------------------

