#include "..\main.h"
//#include "..\..\Custom\Standard\TP_0\Menu_new\dimmer.h"
//-----------------------------------------------------------------------------------
#include "..\Menu_New\lcd_template.h"
//void special_buttons_handle(TLCDPict*	lcd_ptr);
//-----------------------------------------------------------------------------------
#define SCREEN_SAVER_TIME_1	60	// Seconds
#define SCREEN_SAVER_TIME_2	43200	// Seconds
//-----------------------------------------------------------------------------------
u16 bl[11]={bl_0,  bl_10,  bl_20,  bl_30,  bl_40,  bl_50,  bl_60,  bl_70,  bl_80,  bl_90,  bl_100};
//u16 bl[11]={bl_100,  bl_90,  bl_80,  bl_70,  bl_60,  bl_50,  bl_40,  bl_30,  bl_20,  bl_10,  bl_0};
u8 sleep_mode=0;
//-----------------------------------------------------------------------------------
TBMP bmp;
TBMP* fbmp;
u16 BackLit_Value=0;
u8* fbyte;
//u8 ic_stat[3]={0,0,0};
u8 time_blink=0;
u8 txt_mode=0;	//1-time, 2-temperature
u8 button_blink=0;
u8 bmp_update=0;
u8 spec[2]={0,0};
u8 enter_tech_menu=0;
u8 bar_stat[16];
u8 alarm_state=0;
u8 int_state=0;
u8 int_pos=0;
u8 update_time=0;
u8 update_time2=0;
u8 pushed=0;
TManualPush push={0,NULL};
//u8 update_temperature=0;
//u8 update_temperature2=0;
u8 enter_tech_menu2=0;
TTimeShort FiveMins={0,0};
TTimeShort int_time={0,0};
TTimeShort set_time={0,0};
u8 Dimmer_Off=0;
//-----------------------------------------------------------------------------------
TLCDPictTop*	LCDTopPtr;
TLCDPict*		LCDMenuPtr;
TLCDPict*		LCDMenu_Pushed;
TLCDPict*		LCDMenuPtr_Tmp;
TLCDPict*		LCDMenuPtr_Tmp2;
TLCDPict_Txt*	LCDMenuPtr_Tmp_Txt;
//-----------------------------------------------------------------------------------
extern TLCDPictTop Scr_0;
extern TLCDPictTop Scr_1;
extern TLCDPictTop Scr_2;
extern TLCDPictTop Scr_4;
extern TLCDPictTop Scr_11;

extern TLCDPictTop Scr_Password;
extern TLCDPictTop *Scr_Return;
extern TLCDPictTop *Scr_Enter;

//eu8  Password_State;
//void check_alarm();
//void main_button_handle(TLCDPict*	lcd_ptr);
//-----------------------------------------------------------------------------------
void init_bmp()
{
	u8 i;
	LCDTopPtr=&Scr_0;
	LCDTopPtr->Init();	
	BackLit_Value=bl[m.BackLit_Value_Max];
	for(i=0;i<16;i++)
		bar_stat[i]=0;
}
//-----------------------------------------------------------------------------------
void sleep_enable()
{
	SLEEP_Time=SCREEN_SAVER_TIME_2;
	sleep_mode=1;
	lcd_initialise(1);
}
//-----------------------------------------------------------------------------------
void sleep_disable()
{
	SLEEP_Time=SCREEN_SAVER_TIME_1;
	sleep_mode=0;
	lcd_initialise(0);
}
//-----------------------------------------------------------------------------------
void repaint_page()
{
	u8 i;
	for(i=0;i<LCDTopPtr->Obj_Num;i++)	
		show_single_bmp(&Obj[i],0);
}
//-----------------------------------------------------------------------------------
void clear_page()
{
	u8 i;
	for(i=0;i<LCDTopPtr->Obj_Num;i++)	
		clear_single_bmp(&Obj[i]);
}
//-----------------------------------------------------------------------------------
// Check pressing
void handle_page()
{
	u8 i;
	extern u8 Password_OK;
	// Tech menu
    if(enter_tech_menu>20)
    {
		LCDTopPtr->Exit();
//		if(Password_OK==0)
//		{
//			LCDTopPtr=&Scr_Password;
//			Password_Mode=PM_NONE;
//			Scr_Return=&Scr_0;		
//			Scr_Enter=&Scr_4;	
//		}
//		else
		LCDTopPtr=&Scr_1;			
		Obj[0].Flag=(bit_visible+bit_active+bit_new_page+bit_trigger);	
		Obj[1].Flag=(bit_visible+bit_active+bit_new_page+bit_trigger);	
		Obj[2].Flag=(bit_visible+bit_active+bit_new_page+bit_trigger);	
		Obj[3].Flag=(bit_visible+bit_active+bit_new_page+bit_trigger);	
		Obj[4].Flag=(bit_visible+bit_active+bit_new_page+bit_trigger);			
		LCDTopPtr->Init();
		repaint_page();
    	enter_tech_menu=0;
    }

//	check_alarm();
	
	if(LCDTopPtr->Routine!=NULL)LCDTopPtr->Routine();			
	
	for(i=0;i<LCDTopPtr->Obj_Num;i++)	
	{
		if(handle_single_bmp(&Obj[i]))
		{
			if(Obj[i].Flag & bit_new_page)
			{
				if(Obj[i].Routine!=NULL)Obj[i].Routine();	
				if(Obj[i].SubItem != NULL)
				{
					LCDTopPtr->Exit();
					LCDTopPtr=Obj[i].SubItem;
					LCDTopPtr->Init();
					repaint_page();
					return;
				}	
			}		
		}
	}
	if(time_blink & 1)
	{
		if(button_blink==0)button_blink=1;
	}
	else
	{
		if(button_blink==1)	button_blink=0;
	}
	
	/*if ((dimmer_sequence_state != 0) && (!dimmer_sequence_timeout))
	{
		dimmer_sequence_timeout = 500;
		if (dimmer_sequence_state > 0)
			dimmer_on(--dimmer_sequence_state);
		else
			dimmer_off(-(++dimmer_sequence_state));
	}*/
}

//-----------------------------------------------------------------------------------
u8 bit_swap(u8 byte)
{
//	u8 i;
//	u8 j=1;
	u8 res=0;
	if(byte & 0x01)res|=0x80;
	if(byte & 0x02)res|=0x40;
	if(byte & 0x04)res|=0x20;
	if(byte & 0x08)res|=0x10;
	if(byte & 0x10)res|=0x08;
	if(byte & 0x20)res|=0x04;
	if(byte & 0x40)res|=0x02;
	if(byte & 0x80)res|=0x01;
	return res;
}
//-----------------------------------------------------------------------------------
void show_single_bmp(TLCDPict*	lcd_ptr,u8 inverted)
{
	u16 z,r,x,y;
	u16 k,l;
	u16 width,heigh;
	u8 pixel;
	u32 address;
	u32 addr,tmp32;	
	u32 bmp_addr;	

	if(lcd_ptr->Flag==0)return;		
//	BUZZ_Time=10;	// Test
	FGet((u8*)&bmp_addr,PICTURE_FLASH_START+4*lcd_ptr->pict_num,4);
		
	FGet((u8*)&bmp,PICTURE_FLASH_START+4*MAX_BMP_NUM+bmp_addr,sizeof(bmp));
    width=bmp.bmih.biWidth;
    heigh=bmp.bmih.biHeight;	    	
	addr=PICTURE_FLASH_START+bmp_addr+bmp.bmfh.bfOffBits+4*MAX_BMP_NUM;

    z=width/8;
    if((width-z*8)!=0)z+=1;
	r=z/4;
	r*=4;
	r=z-r;
	if(r!=0)
		r=4-r;
	addr+=(heigh-1)*(z+r);	
	if(!(lcd_ptr->Flag & bit_txt_1))
	{
		switch(lcd_ptr->Stat)
		{
			case 0:k=0;l=z/2;break;
			case 1:k=z/2;l=z;break;		
		}	
	}
	if((lcd_ptr->Flag & bit_txt_1))
	{

		k=lcd_ptr->Stat*2;
		l=k+2;		
	}
	if((lcd_ptr->Flag & bit_txt_2))
	{
		k=lcd_ptr->Stat;
		l=k+1;		
	}
	if(lcd_ptr->Flag & bit_full)
	{	
		k=0;
		l=z;			
	}
	if(m.image_position==0)
	{
		for(y=0;y<heigh;y++)
		{
			tmp32=addr;
			for(x=k;x<l;x++)
			{
				FGet((u8*)&pixel,addr+x,1);
				address = lcd_graphics_home+(x-k)+lcd_ptr->x;
				address+=(y+lcd_ptr->y)*LCD_GRAPHICS_AREA;
				lcd_write_data(address & 0xff);
				lcd_write_data(address >> 0x08);
				lcd_write_command(LCD_ADDRESS_POINTER_SET);			
				/* Write modified data */
				if(inverted==0)
					lcd_write_data(pixel);
				else
					lcd_write_data(~pixel);
				lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
			}
			addr=tmp32-(z+r);
		}		
	}
	else
	{
		for(y=0;y<heigh;y++)
		{
			tmp32=addr;
			for(x=k;x<l;x++)
			{
				FGet((u8*)&pixel,addr+x,1);
				pixel=bit_swap(pixel);
				address = lcd_graphics_home+239-((x-k)+lcd_ptr->x);
				address+=(127-y-lcd_ptr->y)*LCD_GRAPHICS_AREA;
				lcd_write_data(address & 0xff);
				lcd_write_data(address >> 0x08);
				lcd_write_command(LCD_ADDRESS_POINTER_SET);			
				/* Write modified data */
				if(inverted==0)
					lcd_write_data(pixel);
				else
					lcd_write_data(~pixel);
				lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
			}
			addr=tmp32-(z+r);
		}		
	}
}
//-----------------------------------------------------------------------------------
void show_single_bmp_txt(TLCDPict_Txt*	lcd_ptr)
{
	u16 z,r,x,y;
	u16 k,l;
	u16 width,heigh;
	u8 pixel;
	u32 address;
	u32 addr,tmp32;	
	u32 bmp_addr;	

	if(lcd_ptr->Flag==0)return;			
	FGet((u8*)&bmp_addr,PICTURE_FLASH_START+4*lcd_ptr->pict_num,4);
	
	FGet((u8*)&bmp,PICTURE_FLASH_START+4*MAX_BMP_NUM+bmp_addr,sizeof(bmp));
    width=bmp.bmih.biWidth;
    heigh=bmp.bmih.biHeight;	    	
	addr=PICTURE_FLASH_START+bmp_addr+bmp.bmfh.bfOffBits+4*MAX_BMP_NUM;
    z=width/8;
    if((width-z*8)!=0)z+=1;
	r=z/4;
	r*=4;
	r=z-r;
	if(r!=0)
		r=4-r;
	addr+=(heigh-1)*(z+r);	
	if(!(lcd_ptr->Flag & bit_txt_1))
	{
		switch(lcd_ptr->Stat)
		{
			case 0:k=0;l=z/2;break;
			case 1:k=z/2;l=z;break;		
		}	
	}
	if((lcd_ptr->Flag & bit_txt_1))
	{
		k=lcd_ptr->Stat*2;
		l=k+2;		
	}
	if((lcd_ptr->Flag & bit_txt_2))
	{
		k=lcd_ptr->Stat;
		l=k+1;		
	}
	if(lcd_ptr->Flag & bit_full)
	{	
		k=0;
		l=z;			
	}
	if(m.image_position==0)	
	{
		for(y=0;y<heigh;y++)
		{
			tmp32=addr;
			for(x=k;x<l;x++)
			{
				FGet((u8*)&pixel,addr+x,1);
				address = lcd_graphics_home+(x-k)+lcd_ptr->x;
				address+=(y+lcd_ptr->y)*LCD_GRAPHICS_AREA;
				lcd_write_data(address & 0xff);
				lcd_write_data(address >> 0x08);
				lcd_write_command(LCD_ADDRESS_POINTER_SET);			
				/* Write modified data */
				lcd_write_data(pixel);
				lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
			}
			addr=tmp32-(z+r);
		}	
	}
	else
	{
		for(y=0;y<heigh;y++)
		{
			tmp32=addr;
			for(x=k;x<l;x++)
			{
				FGet((u8*)&pixel,addr+x,1);
				pixel=bit_swap(pixel);
				address = lcd_graphics_home+239-((x-k)+lcd_ptr->x);
				address+=(127-y-lcd_ptr->y)*LCD_GRAPHICS_AREA;				
				lcd_write_data(address & 0xff);
				lcd_write_data(address >> 0x08);
				lcd_write_command(LCD_ADDRESS_POINTER_SET);			
				/* Write modified data */
				lcd_write_data(pixel);
				lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
			}
			addr=tmp32-(z+r);
		}	
	}
		
}
//-----------------------------------------------------------------------------------
void clear_single_bmp(TLCDPict*	lcd_ptr)
{
	u16 z,r,x,y;
	u16 k,l;
	u16 width,heigh;
	u8 pixel;
	u32 address;
	u32 addr,tmp32;	
//	u8 i,j,tmp;
	u32 bmp_addr;	

	if(lcd_ptr->Flag==0)return;		
//	BUZZ_Time=10;	
	FGet((u8*)&bmp_addr,PICTURE_FLASH_START+4*lcd_ptr->pict_num,4);
		
	FGet((u8*)&bmp,PICTURE_FLASH_START+4*MAX_BMP_NUM+bmp_addr,sizeof(bmp));
    width=bmp.bmih.biWidth;
    heigh=bmp.bmih.biHeight;	    	
	addr=PICTURE_FLASH_START+bmp_addr+bmp.bmfh.bfOffBits+4*MAX_BMP_NUM;
//   	tmp=lcd_ptr->Stat;

    z=width/8;
    if((width-z*8)!=0)z+=1;
	r=z/4;
	r*=4;
	r=z-r;
	r=4-r;
	addr+=(heigh-1)*(z+r);	
	if(!(lcd_ptr->Flag & bit_txt_1))
	{
		switch(lcd_ptr->Stat)
		{
			case 0:k=0;l=z/2;break;
			case 1:k=z/2;l=z;break;		
		}	
	}
	else
	{
		k=lcd_ptr->Stat*2;
		l=k+2;		
	}
	if(lcd_ptr->Flag & bit_full)
	{	
		k=0;
		l=z;			
	}
	if(m.image_position==0)	
	{
		for(y=0;y<heigh;y++)
		{
			tmp32=addr;
			for(x=k;x<l;x++)
			{
	//			FGet((u8*)&pixel,addr+x,1);
				pixel=0;
				address = lcd_graphics_home+(x-k)+lcd_ptr->x;
				address+=(y+lcd_ptr->y)*LCD_GRAPHICS_AREA;
				lcd_write_data(address & 0xff);
				lcd_write_data(address >> 0x08);
				lcd_write_command(LCD_ADDRESS_POINTER_SET);			
				/* Write modified data */
				lcd_write_data(pixel);
				lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);	
			}
			addr=tmp32-(z+r);
		}	
	}
	else
	{
		for(y=0;y<heigh;y++)
		{
			tmp32=addr;
			for(x=k;x<l;x++)
			{
	//			FGet((u8*)&pixel,addr+x,1);
				pixel=0;
				address = lcd_graphics_home+239-((x-k)+lcd_ptr->x);
				address+=(127-y-lcd_ptr->y)*LCD_GRAPHICS_AREA;
				lcd_write_data(address & 0xff);
				lcd_write_data(address >> 0x08);
				lcd_write_command(LCD_ADDRESS_POINTER_SET);			
				/* Write modified data */
				lcd_write_data(pixel);
				lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);	
			}
			addr=tmp32-(z+r);
		}	
	}
}
//-----------------------------------------------------------------------------------
void clear_single_bmp_txt(TLCDPict_Txt*	lcd_ptr)
{
	u16 z,r,x,y;
	u16 k,l;
	u16 width,heigh;
	u8 pixel;
	u32 address;
	u32 addr,tmp32;	
//	u8 i,j,tmp;
	u32 bmp_addr;	

	if(lcd_ptr->Flag==0)return;			
	FGet((u8*)&bmp_addr,PICTURE_FLASH_START+4*lcd_ptr->pict_num,4);
		
	FGet((u8*)&bmp,PICTURE_FLASH_START+4*MAX_BMP_NUM+bmp_addr,sizeof(bmp));
    width=bmp.bmih.biWidth;
    heigh=bmp.bmih.biHeight;	    	
	addr=PICTURE_FLASH_START+bmp_addr+bmp.bmfh.bfOffBits+4*MAX_BMP_NUM;
//   	tmp=lcd_ptr->Stat;

    z=width/8;
    if((width-z*8)!=0)z+=1;
	r=z/4;
	r*=4;
	r=z-r;
	r=4-r;
	addr+=(heigh-1)*(z+r);	
	if(!(lcd_ptr->Flag & bit_txt_1))
	{
		switch(lcd_ptr->Stat)
		{
			case 0:k=0;l=z/2;break;
			case 1:k=z/2;l=z;break;		
		}	
	}
	else
	{
		k=lcd_ptr->Stat*2;
		l=k+2;		
	}
	if(lcd_ptr->Flag & bit_full)
	{	
		k=0;
		l=z;			
	}
	if(m.image_position==0)
	{
		for(y=0;y<heigh;y++)
		{
			tmp32=addr;
			for(x=k;x<l;x++)
			{
	//			FGet((u8*)&pixel,addr+x,1);
				pixel=0;
				address = lcd_graphics_home+(x-k)+lcd_ptr->x;
				address+=(y+lcd_ptr->y)*LCD_GRAPHICS_AREA;
				lcd_write_data(address & 0xff);
				lcd_write_data(address >> 0x08);
				lcd_write_command(LCD_ADDRESS_POINTER_SET);			
				/* Write modified data */
				lcd_write_data(pixel);
				lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
	//			upc_TXHandler();		
			}
			addr=tmp32-(z+r);
		}	
	}
	else
	{
		for(y=0;y<heigh;y++)
		{
			tmp32=addr;
			for(x=k;x<l;x++)
			{
	//			FGet((u8*)&pixel,addr+x,1);
				pixel=0;
				address = lcd_graphics_home+239-((x-k)+lcd_ptr->x);
				address+=(127-y-lcd_ptr->y)*LCD_GRAPHICS_AREA;
				lcd_write_data(address & 0xff);
				lcd_write_data(address >> 0x08);
				lcd_write_command(LCD_ADDRESS_POINTER_SET);			
				/* Write modified data */
				lcd_write_data(pixel);
				lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
	//			upc_TXHandler();		
			}
			addr=tmp32-(z+r);
		}	
	}
}
//-----------------------------------------------------------------------------------
u8  handle_single_bmp(TLCDPict*	lcd_ptr)
{
//	u16 x;
//	u16 k,l;
//	u8 tmp;
	u16 width,height;
	u8 pressed=0;
	u32 bmp_addr;	
	u8 old_stat;
//	u32 tmp32;
	u8	xx[2];
	u8	yy[2];	
	old_stat=lcd_ptr->Stat;		
	if((push.status!=0)&&(push.LCDMenuPtr==lcd_ptr))
		tsc_n=1;
	
	// Only from main screen device can enter sleep mode
	
	// Enable or disable sleep mode
	// Now is allways ON
//	if(LCDTopPtr!=&Scr_0)
	{
		SLEEP_Time=SCREEN_SAVER_TIME_1;
		sleep_mode=0;
//		lcd_initialise(0);	
	}
	if(sleep_mode==0)
	{
		if(BackLit_Value<bl[m.BackLit_Value_Max])
		{
			if(SLEEP_Time==0)
			{
				lcd_initialise(1);			
				sleep_mode=1;
				SLEEP_Time=SCREEN_SAVER_TIME_2;
			}
		}
	}	
	else
	{
		if(SLEEP_Time==0)
		{
			lcd_initialise(0);			
			sleep_mode=0;
			SLEEP_Time=SCREEN_SAVER_TIME_1;
		}		
		if(tsc_n)
		{
			lcd_initialise(0);
			sleep_mode=0;
		}
		return 0;
	}
	
	
	if(SI_Time!=0)return 0; // Silense period
	if(tsc_n)
	{
		SLEEP_Time=SCREEN_SAVER_TIME_1;
		BL_Time=m.Sleep_Time;	
		BL_Time*=1000;
		if(BackLit_Value<bl[m.BackLit_Value_Max])
		{
			BackLit_Value=bl[m.BackLit_Value_Max];
			SI_Time=500;
			return 0;
		}
		if((lcd_ptr->Flag & bit_visible)==0)return 0;			
	
		FGet((u8*)&bmp_addr,PICTURE_FLASH_START+4*lcd_ptr->pict_num,4);
		FGet((u8*)&bmp,PICTURE_FLASH_START+4*MAX_BMP_NUM+bmp_addr,sizeof(bmp));
    	width=bmp.bmih.biWidth;
		if((lcd_ptr->Flag & bit_full)==0)				
			width/=2;
	    height=bmp.bmih.biHeight;
		if(m.image_position==0)	
		{
			xx[0]=lcd_ptr->x*8;
			yy[0]=lcd_ptr->y;
			xx[1]=width+xx[0];
			yy[1]=height+yy[0];
		}
		else
		{
			xx[0]=239-lcd_ptr->x*8;
			yy[0]=127-lcd_ptr->y;
			xx[1]=239-width-xx[0];
			yy[1]=127-height-yy[0];
		}
		// Push button
		if(pushed==0)
		if((tsc_x > xx[0])&&(tsc_x < xx[1])&&(tsc_y > yy[0])&&(tsc_y < yy[1]))    		
		{
			lcd_ptr->Counter++;
			if(lcd_ptr->Counter>131)lcd_ptr->Counter=131;
		}
		// Release button
		if(!((tsc_x > xx[0])&&(tsc_x < xx[1])&&(tsc_y > yy[0])&&(tsc_y < yy[1])))
		{
			if(lcd_ptr->Counter>130)lcd_ptr->Counter--;
			else lcd_ptr->Counter=0;
		}
		
		if((push.status!=0)&&(push.LCDMenuPtr==lcd_ptr))
		{
			lcd_ptr->Counter=4;
			push.status=0;
		}
		if(lcd_ptr->Counter>3)
		{
			if(lcd_ptr->Counter<127)
			{
				pushed=1;
				//----- !!! Button is pressed !!!----------------------
				lcd_ptr->Counter|=0x80;
				LCDMenu_Pushed=lcd_ptr;
				//--- Triggering --------------------------------------
//				if(((lcd_ptr->Flag & bit_trigger)!=0))//||((lcd_ptr->Flag & bit_dimmer)!=0))
				// Dimmer
				if((lcd_ptr->Flag & bit_dimmer)!=0)
				{
					if(lcd_ptr->Stat==0)
					{
						lcd_ptr->Stat=1;
						Dimmer_Off=1;
						Dimmer_Time=600;
					}					
					else lcd_ptr->Stat=0;
				}
				else // Other buttons
				if(((lcd_ptr->Flag & bit_trigger)!=0))				
				{
					if(lcd_ptr->Stat==0)
					{
						lcd_ptr->Stat=1;
						if((lcd_ptr->Flag & bit_blinking)!=0)
						{
							BMP_Time=1000;
						}						
					}
					else
					{
							lcd_ptr->Stat=0;
					}						
				}
				else
				{
					{
						if(LCDTopPtr==&Scr_0)
						{
							if((lcd_ptr==&Obj[0]))		
							{				
								if(Obj[1].Stat==0)						
								{
									lcd_ptr->Stat=1;
									spec[0]=1;
									spec[1]=0;							
								}
							}
							else
								if((lcd_ptr==&Obj[1]))
								{
									if(Obj[0].Stat==0)							
									{
										lcd_ptr->Stat=1;
										spec[1]=1;
										spec[0]=0;
									}
								}
								else lcd_ptr->Stat=1;
						}
						else lcd_ptr->Stat=1;
					}						
				}			
				//----------------------------------------------------		
					
				if((lcd_ptr->Flag & bit_static)==0)						
				if((lcd_ptr->Flag & bit_active)!=0)		
				{		
					show_single_bmp(lcd_ptr,0);
				}				
				pressed=1;		
				if((lcd_ptr->Flag & bit_dimmer)==0)
					if(lcd_ptr->Routine!=NULL)
						lcd_ptr->Routine();						
				//----------------------------------------				
//				special_buttons_handle(lcd_ptr);
				//----------------------------------------				
			}		
			else
			{
				if((lcd_ptr->Flag & bit_active)!=0)	
				if((lcd_ptr->Flag & bit_new_page)==0)	
				{
					if(((lcd_ptr->Flag & bit_trigger)==0))						
					{
						if(R0_Time==0)
						{
							if(R1_Time==0)
							{
								R1_Time=80;
								if(lcd_ptr->Routine!=NULL)
									lcd_ptr->Routine();
							}
						}			
					}
					if(((lcd_ptr->Flag & bit_dimmer)!=0))						
					{
						if(R0_Time==0)
						{
							if(R1_Time==0)
							{
								R1_Time=80;
								if(lcd_ptr->Routine!=NULL)
									lcd_ptr->Routine();
							}
						}			
					}					
				}					
					
			}
		}
		else
		{
			if((lcd_ptr->Flag & bit_active)!=0)	
			if((lcd_ptr->Flag & bit_txt_1)==0)	
			{
				//------ NOT triggering ----------------			
				if((lcd_ptr->Flag & bit_new_page)==0)
				if((lcd_ptr->Flag & bit_trigger)==0)
				{		
							old_stat=lcd_ptr->Stat;
							if(lcd_ptr->Stat!=0)
							{
								lcd_ptr->Stat=0;	
								if(LCDTopPtr==&Scr_0)
								{					
									if(lcd_ptr==&Obj[0])
									{
										if(spec[0]==2)
											lcd_ptr->Stat=1;
										else
											spec[0]=0;
									}
									if(lcd_ptr==&Obj[1])
									{
										if(spec[1]==2)
											lcd_ptr->Stat=1;
										else
											spec[1]=0;
									}
								}
								if((lcd_ptr->Flag & bit_static)==0)	
								if(lcd_ptr->Stat!=old_stat)
									show_single_bmp(lcd_ptr,0);			
							}	
				}
				//--------------------------------------			
				//------ Blinking ----------------------
				if((lcd_ptr->Flag & bit_trigger)!=0)
				{				
					if(lcd_ptr->Stat==1)
					{
						if((lcd_ptr->Flag & bit_blinking)!=0)
						{
							if(time_blink & 1)
							{
								if(button_blink==0)
								{
//									button_blink=1;
									show_single_bmp(lcd_ptr,0);
								}
							}
							else
							{
								if(button_blink==1)
								{
//									button_blink=0;
									clear_single_bmp(lcd_ptr);
								}
							}

						}
					}
				}
				//--------------------------------------							
			}//*/
		}
							
	}
	else
	{
		pushed=0;	
			// Dimmer buttons
		  	if(lcd_ptr==LCDMenu_Pushed)
			{
				if((lcd_ptr->Flag & bit_dimmer)!=0)
					if(Dimmer_Off!=0)
					{
						if(Dimmer_Time!=0)
						{
							lcd_ptr->Stat=0;
							if(lcd_ptr->Routine!=NULL)
								lcd_ptr->Routine();
							show_single_bmp(lcd_ptr,0);							
						}
						LCDMenu_Pushed=NULL;
						Dimmer_Off=0;						
					}
				
			}
		
			if((lcd_ptr->Flag & bit_active)!=0)	
			if((lcd_ptr->Flag & bit_txt_1)==0)	
			{
				//------ NOT triggering ----------------			
				if((lcd_ptr->Flag & bit_new_page)==0)
				if((lcd_ptr->Flag & bit_trigger)==0)
				{		
							old_stat=lcd_ptr->Stat;
							if(lcd_ptr->Stat!=0)
							{
								lcd_ptr->Stat=0;	
								if(LCDTopPtr==&Scr_0)
								{					
									if(lcd_ptr==&Obj[0])
									{
										if(spec[0]==2)
											lcd_ptr->Stat=1;
										else
											spec[0]=0;
									}
									if(lcd_ptr==&Obj[1])
									{
										if(spec[1]==2)
											lcd_ptr->Stat=1;
										else
											spec[1]=0;
									}
								}
								if((lcd_ptr->Flag & bit_static)==0)	
								if(lcd_ptr->Stat!=old_stat)
									show_single_bmp(lcd_ptr,0);			
							}	
				}
				//--------------------------------------
				//------ Blinking ----------------------
				if((lcd_ptr->Flag & bit_trigger)!=0)
				{				
					if(lcd_ptr->Stat==1)
					{
						if((lcd_ptr->Flag & bit_blinking)!=0)
						{
							if(time_blink & 1)
							{
								if(button_blink==0)
								{
//									button_blink=1;
									show_single_bmp(lcd_ptr,0);
								}
							}
							else
							{
								if(button_blink==1)
								{
//									button_blink=0;
									clear_single_bmp(lcd_ptr);
								}
							}

						}
					}
				}
				//--------------------------------------			
			}	
		if(lcd_ptr->Counter>0)lcd_ptr->Counter--;		
		lcd_ptr->Counter&=~0x80;				
		//----------------------------------------------------
	}
	//----- Prepare flag of buttons pressed --------------
	if((lcd_ptr->Flag & bit_active)!=0)		
	if(!(lcd_ptr->Flag & bit_txt_1))							
	{	
		if(old_stat!=lcd_ptr->Stat)
		{
			{
				if(lcd_ptr->Stat==1)
				{
					own_state.bst|=lcd_ptr->Action;	
					own_state.status|=bit_new_push;									
				}
				else
				{
					own_state.bst&=~lcd_ptr->Action;
					own_state.status|=bit_new_push;						
				}														
			}
		}
	}	
	return pressed;
}
//-----------------------------------------------------------------------------------
void show_byte(u8 *out,u8 in,u8 offset)
{
	u8 str2[10];
	ByteToStr(str2,&in,0);
	if(in>9)
	{
		out[offset]=str2[0];
		out[offset+1]=str2[1];
	}
	else
	{
		out[offset]='0';
		out[offset+1]=str2[0];
	}	
	out[offset+2]=0;
}
//-----------------------------------------------------------------------------------
void show_data(u8 *out,u8 separator,u32 addr,u8 a0,u8 a1, u8 a2)
{
	u8 str[20];
		watchdog_reset();
		FGet((u8*)&ctmp,addr+TTIME_LOC+a0,1);	
		show_byte(str,ctmp,0);			
		str[2]=separator;
		FGet((u8*)&ctmp,addr+TTIME_LOC+a1,1);	
		show_byte(str,ctmp,3);		
		str[5]=separator;
		FGet((u8*)&ctmp,addr+TTIME_LOC+a2,1);	
		show_byte(str,ctmp,6);	
		str[8]=0;	
		strcpy((char*)out,(char const*)str);	
}
//-----------------------------------------------------------------------------------
void show_header(u32 addr)
{
		u8 lcd_str[40];
		// HW Version
		watchdog_reset();
//		_sprintf(lcd_str,"HW Version ");	
		lcd_sprintf("HW Version ",0,3);
		FGet((u8*)&ltmp,addr+THW_LOC,4);	
		LongToStr(lcd_str,&ltmp,1);
		lcd_sprintf(lcd_str,11,3);
		// SW Version
//		_sprintf(lcd_str,"SW Version ");	
		lcd_sprintf("SW Version ",0,4);
		FGet((u8*)&ltmp,addr+TSW_LOC,4);	
		LongToStr(lcd_str,&ltmp,1);
		lcd_sprintf(lcd_str,11,4);
		
/*		// Date of creation
		sprintf(lcd_str,"Date of creation  ");
		lcd_sprintf(lcd_str,0,5);
		show_data(lcd_str,'/',addr,4,5,6);	
		lcd_sprintf(lcd_str,0,6);
		// Time of creation
		show_data(lcd_str,':',addr,2,1,0);
		lcd_sprintf(lcd_str,10,6);	
		FGet((u8*)lcd_str,addr+TNAME_LOC,TNAME_WIDTH);
		lcd_sprintf(lcd_str,0,7);	
*/		
}
//-----------------------------------------------------------------------------------
void startup()
{
	u8 tmp;
//	u8 str[20];
//	f32 fl;
//	u8 press_stat,press_count;
	u16 pressed=0;	
	lcd_reset();
	lcd_initialise(0);	
	lcd_clear_all();
    lcd_write_command(LCD_DISPLAY_MODES_GRAPHICS_ON | LCD_DISPLAY_MODES_TEXT_ON);    	
//	lcd_initialise(2);		
	lcd_set_page(1);
	show_single_bmp(&_Logo,0);
//	lcd_clear_graphics();	
//	lcd_clear_text();	
	lcd_initialise(0);		
//	lcd_clear_graphics();	
//	lcd_clear_text();	
#ifdef _TEST_TOUCH	
	while(1)
	{
		watchdog_reset();
		Ext_IRQ0();
		con_handle();
		BL_Time=10;
		BackLit_Value=bl[m.BackLit_Value_Max];
		
		if(tsc_n!=0)
		{
//					sprintf(outtxt,"\n\r ");LongToStr(outtxt,&tsc_rx,0);sprintf(outtxt," ");LongToStr(outtxt,&tsc_ry,0);
			lcd_sprintf("                    ",5,2);lcd_sprintf("X =",5,2);WordToStr(str,&tsc_rx,0);lcd_sprintf(str,8,2);
			lcd_sprintf("                    ",5,3);lcd_sprintf("Y =",5,3);WordToStr(str,&tsc_ry,0);lcd_sprintf(str,8,3);
			lcd_sprintf("                    ",5,4);lcd_sprintf("R =",5,4);WordToStr(str,&tsc_r,0);lcd_sprintf(str,8,4);			
//			lcd_sprintf("                    ",5,5);lcd_sprintf("Z2=",5,5);WordToStr(str,&tsc_rz2,0);lcd_sprintf(str,8,5);
//			lcd_sprintf("                    ",5,6);lcd_sprintf("R =",5,6);WordToStr(str,&tsc_rz2,0);lcd_sprintf(str,8,6);			
			tsc_n=0;
		}
	
	}
#endif
	// check pressed at default	
	Ext_IRQ0();
	if(tsc_n!=0)
	{
		lcd_sprintf_P(Main_Dict[10],9,0);
		Ext_IRQ0();
		while(tsc_n!=0)
		{
			Ext_IRQ0();
			watchdog_reset();
		}
	}
	lcd_clear_text();
//	_sprintf((u8*)outtxt,"\n\r>");										
	lcd_sprintf_P(Main_Dict[4],0,0);	
	lcd_sprintf_P(Main_Dict[5],0,1);	
	lcd_sprintf_P(Main_Dict[6],0,2);	
	show_header(HAPP_FLASH_START);
	lcd_sprintf("Address ",0,5);
	ByteToStr(lcd_txt,&m.Address,0);
	lcd_sprintf(lcd_txt,9,5);
	FGet((u8*)lcd_txt,HAPP_FLASH_START+TNAME_LOC,TNAME_WIDTH);
	lcd_sprintf(lcd_txt,0,6);
//	show_header(HPLM_FLASH_START);
	// Check calibration
	Time2=2000;
	Time1=100;
	tmp=0;		
	while(Time2!=0)	
	{			
		watchdog_reset();
		if(Time1==0)
		{
			Time1=100;
			watchdog_reset();
			lcd_sprintf(".",tmp,7);
			Ext_IRQ0();
			if(tsc_n)
			{
				pressed++;
			}
			if(pressed>=10)
			{
				Time2=0;
				Time1=0;
				lcd_clear_text();
				calibrate_bmp();
			}
			tmp+=1;			
		}
	}
	lcd_clear_graphics();
	lcd_clear_text();	
	LED_Time=500;
	BL_Time=m.Sleep_Time;
	BL_Time*=1000;
	Time1=0;
	//-----------------------------
//	LCDTopPtr=&Scr_0;	
//	LCDTopPtr->Init();
//	repaint_page();	
	SLEEP_Time=SCREEN_SAVER_TIME_1;
}
//-----------------------------------------------------------------------------------
