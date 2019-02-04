#include "..\main.h"
//-----------------------------------------------------------------------------------
#include "..\Menu\lcd_page0_bad_side_r.h"
#include "..\Menu\lcd_calibrate.h"
#include "..\Menu\lcd_tech_menu.h"
#include "..\Menu\lcd_tech_contrast.h"
#include "..\Menu\lcd_tech_time2.h"
#include "..\Menu\lcd_tech_temperature.h"
#include "..\Menu\lcd_ac_menu.h"
#include "..\Menu\lcd_alarm.h"
#include "..\Menu\lcd_alarm_snooze.h"

//-----------------------------------------------------------------------------------
#define TSC_REQUEST_TIME 50
//-----------------------------------------------------------------------------------
__farflash u8	BMP_Dict[38][80]=
{ 
	"\n\r Resetting...",					//0
	"\n\r Parameters stored ",				//1
	"\n\r Test...\n\r",						//2
	"Current state ",					//3
	"Controller configuration",		//4	
	"Digital inputs  ",	//5		
	"Digital outputs ",//6		
	"Analog inputs   ",	//7		
	"Analog outputs  ",	//8		
	"Temperature settings",			//9		
	"     Desired temperature ",		//10		
	"     Mode of operation ",			//11		
	"\n\r   Program is ",					//12		
	"RUN",									//13
	"STOPED",								//14
	"\n\r   Pid settings",					//15
	"\n\r     Desired temperature ",		//16
	"\n\r     Mode of operation ",			//17
	"\n\r     Temperature channel AI[",		//18
	"\n\r     Prop cofficient     ",		//19
	"\n\r     Diff cofficient     ",		//20
	"\n\r     Integral cofficient ",		//21
	"\n\r     Integration time    ",		//22						
	"\n\r Ready for downloading program image...",	//23						
	"\n\r Download is successful complete...",		//24						
	"\n\r Download error!",							//25						
	"\n\r No valid user program found\n\r Download new bin please ...",		//26						
	"\n\r User program image corrupted\n\r Download new bin please...",		//27						
	"\n\r Valid user program found\n\r ",		//28						
	"\n\r     Min power ",						//29
	"\n\r     Max power ",						//30
	"\n\r     Power     ",						//31
	"\n\r Power supply voltage ",				//32
	"\n\r     Servoprivod full cycle time c ",	//33
	"\n\r     3 points server power ",			//34
	"\n\r     Open  line ",					//35
	"\n\r     Close line ",					//36		
	"\n\r     Current temperature ",		//37
//	txt,		//33
};
//u8 UControl0=0;
//u8 UControl1=0;
//u8 buff[1024];
//u16 addr;
u16 bl[11]={bl_0,  bl_10,  bl_20,  bl_30,  bl_40,  bl_50,  bl_60,  bl_70,  bl_80,  bl_90,  bl_100};

TBMP bmp;
TBMP* fbmp;
u16 BackLit_Value=0;
u8* fbyte;
//u8 ic_stat[3]={0,0,0};
u8 time_blink=0;
u8 txt_mode=0;	//1-time, 2-temperature
u8 update_screen=0;	//1 - screen was changed, update it
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
u8 update_temperature=0;
u8 update_temperature2=0;
u8 enter_tech_menu2=0;
u8 txt_update=254;
TTimeShort FiveMins={0,0};
TTimeShort int_time={0,0};
TTimeShort set_time={0,0};

u8 Active_Screen=0;
//-----------------------------------------------------------------------------------
TLCDPict*		LCDMenuPtr;
TLCDPict*		LCDMenuPtr_Tmp;
TLCDPict*		LCDMenuPtr_Tmp2;
TLCDPict*		LCDMenuPtr_Tmp3;
TLCDPict_Txt*	LCDMenuPtr_Tmp_Txt;
//-----------------------------------------------------------------------------------
void init_bmp()
{
	u8 i;
	LCDMenuPtr=&_Page0;
	BackLit_Value=bl[m.BackLit_Value_Max]; 
}
//-----------------------------------------------------------------------------------
// Repaints page and return pointer to Page
void repaint_page()
{
	u8 i;
//	LCDMenuPtr_Tmp3=LCDMenuPtr;	
	switch(Active_Screen)
	{
		case 0:LCDMenuPtr_Tmp3=&_Page0;break;
		case 1:LCDMenuPtr_Tmp3=&_Page1;break;
		case 2:LCDMenuPtr_Tmp3=&_Page2;break;
		case 3:LCDMenuPtr_Tmp3=&_Page3;break;
		case 4:LCDMenuPtr_Tmp3=&_Page4;break;		
	}
	for(i=0;i<2;i++)
	{
		if(i==0)
			LCDMenuPtr=&_Menu_Page;		
		else
			LCDMenuPtr=LCDMenuPtr_Tmp3->UpItem;	
			
		if(LCDMenuPtr->Routine!=NULL)LCDMenuPtr->Routine();	
		if(LCDMenuPtr!=NULL)show_single_bmp(LCDMenuPtr);
		if(LCDMenuPtr->SubItem!=NULL)
		{
			LCDMenuPtr=LCDMenuPtr->SubItem;
			if(LCDMenuPtr!=NULL)show_single_bmp(LCDMenuPtr);	
		}
		while(LCDMenuPtr->NextItem!=NULL)	
		{
			LCDMenuPtr=LCDMenuPtr->NextItem;			
			show_single_bmp(LCDMenuPtr);
			adm_wd_reset;
		}
	}
}
//-----------------------------------------------------------------------------------
// Clear page and return pointer to Page
void clear_page()
{
	u8 i;
// 	Menu handling
//	LCDMenuPtr_Tmp3=LCDMenuPtr;	
/*	switch(Active_Screen)
	{
		case 0:LCDMenuPtr_Tmp3=&_Page0;break;
		case 4:LCDMenuPtr_Tmp3=&_Page4;break;		
	}
*/	
//	LCDMenuPtr=LCDMenuPtr_Tmp3;	
		LCDMenuPtr=LCDMenuPtr->UpItem;	
			
		if(LCDMenuPtr!=NULL)clear_single_bmp(LCDMenuPtr);
		if(LCDMenuPtr->SubItem!=NULL)
		{		
			LCDMenuPtr=LCDMenuPtr->SubItem;		
			if(LCDMenuPtr!=NULL)clear_single_bmp(LCDMenuPtr);
		}
		while(LCDMenuPtr->NextItem!=NULL)	
		{
			LCDMenuPtr=LCDMenuPtr->NextItem;			
			clear_single_bmp(LCDMenuPtr);
			adm_wd_reset;
		}
//	}
}
//-----------------------------------------------------------------------------------
// Check pressing
void handle_page()
{
	u8 i;
	//LCDMenuPtr_Tmp3=LCDMenuPtr;	
	switch(Active_Screen)
	{
		case 0:LCDMenuPtr_Tmp3=&_Page0;break;
		case 1:LCDMenuPtr_Tmp3=&_Page1;break;
		case 2:LCDMenuPtr_Tmp3=&_Page2;break;
		case 3:LCDMenuPtr_Tmp3=&_Page3;break;
		case 4:LCDMenuPtr_Tmp3=&_Page4;break;		
	}	
	for(i=0;i<2;i++)
	{
		if(i==0)
			LCDMenuPtr=&_Menu_Page;		
		else
			LCDMenuPtr=LCDMenuPtr_Tmp3->UpItem;	
		if(LCDMenuPtr->Routine!=NULL)LCDMenuPtr->Routine();		
		if(LCDMenuPtr->SubItem==NULL)return;	
		LCDMenuPtr=LCDMenuPtr->SubItem;		
		if(handle_single_bmp(LCDMenuPtr))
		{
			if(LCDMenuPtr->Flag & bit_new_page)
				if(LCDMenuPtr->SubItem != NULL)
				{
					LCDMenuPtr_Tmp=LCDMenuPtr->SubItem;
					clear_page();
					LCDMenuPtr=LCDMenuPtr_Tmp;
					repaint_page();
					return;
				}			
		}
		while(LCDMenuPtr->NextItem!=NULL)	
		{
			LCDMenuPtr=LCDMenuPtr->NextItem;			
			if(handle_single_bmp(LCDMenuPtr))
			{
	
				if(LCDMenuPtr->Flag & bit_new_page)
					if(LCDMenuPtr->SubItem != NULL)
					{
						LCDMenuPtr_Tmp=LCDMenuPtr->SubItem;
						clear_page();
						LCDMenuPtr=LCDMenuPtr_Tmp;
						repaint_page();
						return;
					}
			}
		}	
	}
}
//-----------------------------------------------------------------------------------
// Check pressing
void update_page()
{
	u8 old_stat,i;
	u32 ltmp;
	if(bmp_update)
	{
//***********************************************************************************
		//---------------------------------------------------------------------------
/*			if(LCDMenuPtr->UpItem==&_Page0)
			{
				ltmp=1;		
				LCDMenuPtr_Tmp2=&_DO_0;
				for(i=0;i<20;i++)
				{
					old_stat=LCDMenuPtr_Tmp2->Stat;
					// Process buttons depending on own_state.bst
					if(own_state.bst & ltmp)
						LCDMenuPtr_Tmp2->Stat=1;
					else
						LCDMenuPtr_Tmp2->Stat=0;
					if(LCDMenuPtr_Tmp2!=NULL)
						if(old_stat!=LCDMenuPtr_Tmp2->Stat)
							show_single_bmp(LCDMenuPtr_Tmp2);
					if(LCDMenuPtr_Tmp2->NextItem!=NULL)
						LCDMenuPtr_Tmp2=LCDMenuPtr_Tmp2->NextItem;
					ltmp=ltmp<<1;
				}
			}			
		//---------------------------------------------------------------------------
		//---------------------------------------------------------------------------
			if(LCDMenuPtr->UpItem==&_Page1) 
			{
				ltmp=1;		
				LCDMenuPtr_Tmp2=&_DI_0;
				for(i=0;i<8;i++)
				{
					old_stat=LCDMenuPtr_Tmp2->Stat;
					// Process buttons depending on own_state.bst
					if(mcu.io.din & ltmp)
						LCDMenuPtr_Tmp2->Stat=1;
					else
						LCDMenuPtr_Tmp2->Stat=0;
						
					if(LCDMenuPtr_Tmp2!=NULL)
						if(old_stat!=LCDMenuPtr_Tmp2->Stat)
							show_single_bmp(LCDMenuPtr_Tmp2);
					if(LCDMenuPtr_Tmp2->NextItem!=NULL)
						LCDMenuPtr_Tmp2=LCDMenuPtr_Tmp2->NextItem;
					ltmp=ltmp<<1;
				}
			}					
		//---------------------------------------------------------------------------
//***********************************************************************************
*/
	}
	bmp_update=0;
}
//-----------------------------------------------------------------------------------
void show_single_bmp(TLCDPict*	lcd_ptr)
{
	u16 z,r,x,y;
	u16 k,l;
	u16 width,heigh;
	u8 pixel;
	u32 address;
	u32 addr,tmp32;	
//	u8 i,j,tmp;
//	u8 tmp;
	u32 bmp_addr;	

//	_sprintf(outtxt,"\n\r 00");
	if(lcd_ptr->Flag==0)return;			
	FGet((u8*)&bmp_addr,PICTURE_FLASH_START+4*lcd_ptr->pict_num,4);
	
//	_sprintf(outtxt,"\n\r ");	
//	LongToStr(outtxt,&bmp_addr,1);
//	_sprintf(outtxt,"\n\r 01");	   
	
	FGet((u8*)&bmp,PICTURE_FLASH_START+4*MAX_BMP_NUM+bmp_addr,sizeof(bmp));
    width=bmp.bmih.biWidth;
    heigh=bmp.bmih.biHeight;	    	
	addr=PICTURE_FLASH_START+bmp_addr+bmp.bmfh.bfOffBits+4*MAX_BMP_NUM;

//	_sprintf(outtxt,"\n\r 02");	   
	
/*	if(lcd_ptr==&_T_Button_1)
	{
	    _sprintf(outtxt,"\n\r "); 
    	WordToStr(outtxt,&width,0);

	    _sprintf(outtxt,"\n\r "); 
    	WordToStr(outtxt,&heigh,0);

	    _sprintf(outtxt,"\n\r "); 
    	LongToStr(outtxt,&addr,1);	
    }
*/   
//   	tmp=lcd_ptr->Stat;
//    _sprintf(outtxt,"\n\r "); 
//    ByteToStr(outtxt,&tmp,0);
   
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
//		switch(lcd_ptr->Stat)
//		{
//			case 0:k=0;l=2;break;
//			case 1:k=2;l=4;break;		
//		}	
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
/*	_sprintf(outtxt,"\n\r 03");	   
	    _sprintf(outtxt,"\n\r "); 
    	WordToStr(outtxt,&width,0);

	    _sprintf(outtxt,"\n\r "); 
    	WordToStr(outtxt,&heigh,0);

	    _sprintf(outtxt,"\n\r "); 
    	WordToStr(outtxt,&l,0);

	    _sprintf(outtxt,"\n\r "); 
    	WordToStr(outtxt,&k,0);
*/	
    for(y=0;y<heigh;y++)
    {    
    	tmp32=addr;
		for(x=k;x<l;x++)
		{
			FGet((u8*)&pixel,addr+x,1);
		    address = LCD_GRAPHICS_HOME+(x-k)+lcd_ptr->x;
		    address+=(y+lcd_ptr->y)*LCD_GRAPHICS_AREA;
		    lcd_write_data(address & 0xff);
    		lcd_write_data(address >> 0x08);
		    lcd_write_command(LCD_ADDRESS_POINTER_SET);			    
		    /* Write modified data */
		    lcd_write_data(pixel);
		    lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
		    
		    adm_wd_reset;
		}
		addr=tmp32-(z+r);
	}	
//	_sprintf(outtxt,"\n\r 04");	   
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
//	u8 i,j,tmp;
//	u8 tmp;
	u32 bmp_addr;	

	if(lcd_ptr->Flag==0)return;			
	FGet((u8*)&bmp_addr,PICTURE_FLASH_START+4*lcd_ptr->pict_num,4);
	
//	_sprintf(outtxt,"\n\r ");	
//	LongToStr(outtxt,&bmp_addr,1);
		
	FGet((u8*)&bmp,PICTURE_FLASH_START+4*MAX_BMP_NUM+bmp_addr,sizeof(bmp));
    width=bmp.bmih.biWidth;
    heigh=bmp.bmih.biHeight;	    	
	addr=PICTURE_FLASH_START+bmp_addr+bmp.bmfh.bfOffBits+4*MAX_BMP_NUM;
		
/*	if(lcd_ptr==&_T_Button_1)
	{
	    _sprintf(outtxt,"\n\r "); 
    	WordToStr(outtxt,&width,0);

	    _sprintf(outtxt,"\n\r "); 
    	WordToStr(outtxt,&heigh,0);

	    _sprintf(outtxt,"\n\r "); 
    	LongToStr(outtxt,&addr,1);	
    }
*/   
//   	tmp=lcd_ptr->Stat;
//    _sprintf(outtxt,"\n\r "); 
//    ByteToStr(outtxt,&tmp,0);
   
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
//		switch(lcd_ptr->Stat)
//		{
//			case 0:k=0;l=2;break;
//			case 1:k=2;l=4;break;		
//		}	
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
	
    for(y=0;y<heigh;y++)
    {    
    	tmp32=addr;
		for(x=k;x<l;x++)
		{
			FGet((u8*)&pixel,addr+x,1);
		    address = LCD_GRAPHICS_HOME+(x-k)+lcd_ptr->x;
		    address+=(y+lcd_ptr->y)*LCD_GRAPHICS_AREA;
		    lcd_write_data(address & 0xff);
    		lcd_write_data(address >> 0x08);
		    lcd_write_command(LCD_ADDRESS_POINTER_SET);			    
		    /* Write modified data */
		    lcd_write_data(pixel);
		    lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
		    
		    adm_wd_reset;
		}
		addr=tmp32-(z+r);
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
//		switch(lcd_ptr->Stat)
//		{
//			case 0:k=0;l=2;break;
//			case 1:k=2;l=4;break;		
//		}	
		k=lcd_ptr->Stat*2;
		l=k+2;		
	}
	if(lcd_ptr->Flag & bit_full)
	{	
		k=0;
		l=z;			
	}
    for(y=0;y<heigh;y++)
    {    
    	tmp32=addr;
		for(x=k;x<l;x++)
		{
//			FGet((u8*)&pixel,addr+x,1);
			pixel=0;
		    address = LCD_GRAPHICS_HOME+(x-k)+lcd_ptr->x;
		    address+=(y+lcd_ptr->y)*LCD_GRAPHICS_AREA;
		    lcd_write_data(address & 0xff);
    		lcd_write_data(address >> 0x08);
		    lcd_write_command(LCD_ADDRESS_POINTER_SET);			    
		    /* Write modified data */
		    lcd_write_data(pixel);
		    lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
		    
		    adm_wd_reset;
		}
		addr=tmp32-(z+r);
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
//		switch(lcd_ptr->Stat)
//		{
//			case 0:k=0;l=2;break;
//			case 1:k=2;l=4;break;		
//		}	
		k=lcd_ptr->Stat*2;
		l=k+2;		
	}
	if(lcd_ptr->Flag & bit_full)
	{	
		k=0;
		l=z;			
	}
    for(y=0;y<heigh;y++)
    {    
    	tmp32=addr;
		for(x=k;x<l;x++)
		{
//			FGet((u8*)&pixel,addr+x,1);
			pixel=0;
		    address = LCD_GRAPHICS_HOME+(x-k)+lcd_ptr->x;
		    address+=(y+lcd_ptr->y)*LCD_GRAPHICS_AREA;
		    lcd_write_data(address & 0xff);
    		lcd_write_data(address >> 0x08);
		    lcd_write_command(LCD_ADDRESS_POINTER_SET);			    
		    /* Write modified data */
		    lcd_write_data(pixel);
		    lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
		    
		    adm_wd_reset;
		}
		addr=tmp32-(z+r);
	}	
   
}
//-----------------------------------------------------------------------------------
u8  handle_single_bmp(TLCDPict*	lcd_ptr)
{
	u16 x;
//	u16 k,l;
	u16 width,height;
//	u8 pixel;
//	u32 address;
//	u32 addr,tmp32;	
	u8 i,pressed=0;
	u32 bmp_addr;	
	u8 old_stat;
	u32 tmp32;

	
	if(SI_Time!=0)return pressed; // Silense period 
//	if((lcd_ptr->Flag & bit_active)==0)return pressed;	
	old_stat=lcd_ptr->Stat;		
	
	if(tsc_n)
	{
		BL_Time=m.Sleep_Time;	
		BL_Time*=1000;
		if(BackLit_Value<bl[m.BackLit_Value_Max])
		{
//			BackLit_Value=1023;
			BackLit_Value=bl[m.BackLit_Value_Max];
			SI_Time=500;
			return;
		}
		if((lcd_ptr->Flag & bit_visible)==0)return 0;			
//		if((lcd_ptr->Flag & bit_active)==0)return 0;			
		FGet((u8*)&bmp_addr,PICTURE_FLASH_START+4*lcd_ptr->pict_num,4);
		FGet((u8*)&bmp,PICTURE_FLASH_START+4*MAX_BMP_NUM+bmp_addr,sizeof(bmp));
    	width=bmp.bmih.biWidth;
		if((lcd_ptr->Flag & bit_full)==0)				
			width/=2;
	    height=bmp.bmih.biHeight;
		x=lcd_ptr->x*8;

		if((tsc_x>x)&&(tsc_x<(x+width))&&(tsc_y>lcd_ptr->y)&&(tsc_y<(lcd_ptr->y+height)))    		
		{
			lcd_ptr->Counter++;
			if(lcd_ptr->Counter>250)lcd_ptr->Counter=250;
//			enter_tech_menu=0;
		}
		if(lcd_ptr->Counter>=4)
		{
			if(lcd_ptr->Counter<127)
			{
				//----- !!! Button is pressed !!!----------------------
				lcd_ptr->Counter|=0x80;
	//			FT_Time=500;
				//--- Triggering --------------------------------------
				if((lcd_ptr->Flag & bit_trigger)!=0)
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
					if((lcd_ptr->Flag & bit_new_page)==0)	
						lcd_ptr->Stat=1;
						
//						BMP_Time=MAX_TIME_PRESSING;
				}			
				//----------------------------------------------------			
				if((lcd_ptr->Flag & bit_active)!=0)		
				if((lcd_ptr->Flag & bit_new_page)==0)	
				{		
					show_single_bmp(lcd_ptr);
				}				
				pressed=1;		
				if((lcd_ptr->Action & but_Int_Mask)!=0)	
					int_state|=lcd_ptr->Action >> 24;								
				if(lcd_ptr->Routine!=NULL)
					lcd_ptr->Routine();						
				BUZZ_Time=100;		
				//----------------------------------------				
			}		
			else
			{
				if((lcd_ptr->Flag & bit_active)!=0)	
				if((lcd_ptr->Flag & bit_new_page)==0)	
					if((lcd_ptr->Flag & bit_trigger)==0)						
					{
						if(R0_Time==0)
						{
							if(R1_Time==0)
							{
								R1_Time=100;
								BUZZ_Time=100;
								if((lcd_ptr->Action & but_Int_Mask)!=0)	
									int_state|=lcd_ptr->Action >> 24;				
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
		if(!(lcd_ptr->Flag & bit_txt_1))	
		{
			//------ NOT triggering ----------------			
			if((lcd_ptr->Flag & bit_new_page)==0)
			if((lcd_ptr->Flag & bit_trigger)==0)
			{
//				if((lcd_ptr==&_Button_0)&&(spec[1]==0))
//				if(lcd_ptr==&_Button_1)
//						if(spec[0]!=0)
//							lcd_ptr->Stat=1;
//				if((lcd_ptr!=&_Button_0)&&(lcd_ptr!=&_Button_1))
//				if(!((lcd_ptr==&_Button_0)&&(spec[1]!=0)))
//					if(!((lcd_ptr==&_Button_1)&&(spec[0]!=0)))				
						if(lcd_ptr->Stat!=0)
						{
							lcd_ptr->Stat=0;						
							show_single_bmp(lcd_ptr);			
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
						if(BMP_Time==0)
						{
							button_blink++;
							BMP_Time=1000;
							if(button_blink & 1)
								lcd_ptr->Stat=0;
							show_single_bmp(lcd_ptr);
							lcd_ptr->Stat=1;
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
			if((lcd_ptr->Action & but_Int_Mask)==0)	
			{
				if(lcd_ptr->Stat==1)
				{
//					own_state.bst|=lcd_ptr->Action;	
//					own_state.status|=bit_new_push;	
	//				_sprintf(outtxt,"\n\r ");
	//				LongToStr(outtxt,&own_state.bst,1);									
				}
				else
				{
//					own_state.bst&=~lcd_ptr->Action;
//					own_state.status|=bit_new_push;						
				}														
			}
			else
			{				
				int_state|=lcd_ptr->Action >> 24;
			}
		}
	}	
	return pressed;
}
//-----------------------------------------------------------------------------------
void show_bmp()
{
	u16 z,r,x,y;
	u16 width,heigh;
	u8 pixel;
	u16 address;
	u8 i,j;

//	memcpy(&bmp,&buff[0],sizeof(bmp));
    width=bmp.bmih.biWidth;
    heigh=bmp.bmih.biHeight;	    
	addr=bmp.bmfh.bfOffBits;
    z=width/8;
    if((width-z*8)!=0)z+=1;
	r=z/4;
	r*=4;
	r=z-r;
	r=4-r;
	
    for(y=0;y<heigh;y++)
    {    
		for(x=0;x<z;x++)
		{
//			pixel=fgetc(picture);
//			pixel=buff[addr];
			addr++;
/*			for(b=0;b<8;b++)
			{
				Image1->Canvas->Pixels[x*8+b][heigh-y]=clBlack;
				if((pixel & 0x80)!=0)
					Image1->Canvas->Pixels[x*8+b][heigh-y]=clWhite;
				pixel<<=1;
			}
*/		
	    address = LCD_GRAPHICS_HOME+(heigh-y)*LCD_GRAPHICS_AREA+x;
	    lcd_write_data(address & 0xff);
    	lcd_write_data(address >> 0x08);
	    lcd_write_command(LCD_ADDRESS_POINTER_SET);
			    
		    /* Write modified data */
		    lcd_write_data(pixel);
		    lcd_write_command(LCD_DATA_WRITE_AUTO_INCREMENT);
		}
		for(x=0;x<r;x++)
		{
//			pixel=fgetc(picture);
			addr++;
		}
		
	}
}
//-----------------------------------------------------------------------------------
// Images should be 40x40 pixels
void show_button(u16 x8, u16 y8,u8 pnum,u8 pmode)
{
	u16 z,r,x,y;
	u16 k,l;
	u16 width,heigh;
	u8 pixel;
	u32 address;
	u32 addr,tmp32;	
	u8 i,j;

	FGet((u8*)&bmp,PICTURE_FLASH_START,sizeof(bmp));
    width=bmp.bmih.biWidth;
    heigh=bmp.bmih.biHeight;	    	
//	FGet((u8*)&addr,HPLM_FLASH_START+200,4);    
	addr=PICTURE_FLASH_START+bmp.bmfh.bfOffBits;	
/*	
    _sprintf(outtxt,"\n\r "); 
    WordToStr(outtxt,&width,0);

    _sprintf(outtxt,"\n\r "); 
    WordToStr(outtxt,&heigh,0);

    _sprintf(outtxt,"\n\r "); 
    LongToStr(outtxt,&addr,0);
*/
    z=width/8;
    if((width-z*8)!=0)z+=1;
	r=z/4;
	r*=4;
	r=z-r;
	r=4-r;
	addr+=(heigh-1-pnum*40)*(z+r);	
	switch(pmode)
	{
		case 0:k=0;l=z/2;break;
		case 1:k=z/2;l=z;break;		
	}	
    for(y=0;y<40;y++)
    {    
    	tmp32=addr;
		for(x=k;x<l;x++)
		{
			FGet((u8*)&pixel,addr+x,1);
		    address = LCD_GRAPHICS_HOME+(x-k)+x8;
		    address+=(y+y8)*LCD_GRAPHICS_AREA;
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
//-----------------------------------------------------------------------------------
void show_sys_page()
{
	u8 tmp;	
	u8 i,j,t;
	u8 offset=0;
//	FT_Time=500;
	if(txt_update!=4)
	{
		mcu.rx_list=0;
		mcu.rx_list|=rx_io;	
		txt_update=4;
		FT_Time=100;
//		lcd_clear_text();
		return;		
	}	
	if(FT_Time==0)
	{
		FT_Time=500;
//		lcd_sprintf_P(BMP_Dict[4],0,0);	
	//Mod_Show_Full_Time();

/*	mcu.io.num_di=10;
	mcu.io.num_do=10;
	mcu.io.num_ai=6;
	mcu.io.num_ao=6;
*/	
//		lcd_clear_text();
		lcd_sprintf_P(BMP_Dict[3],0,3);
		// IO state
		lcd_sprintf_P(BMP_Dict[4],0,4);	
		lcd_sprintf_P(BMP_Dict[5],0,5);		
		for(j=0;j<mcu.io.num_di;j++)
		{
			t=1<<j;			
			if(mcu.io.din & t) lcd_sprintf("1",j,6);
			else lcd_sprintf("0",j,6);
		}
		lcd_sprintf_P(BMP_Dict[6],0,7);
		for(j=0;j<mcu.io.num_do;j++)
		{
			t=1<<j;			
			if(mcu.io.dout & t) lcd_sprintf("1",j,8);
			else lcd_sprintf("0",j,8);
		}
		
		lcd_sprintf_P(BMP_Dict[7],0,9);	
		if(mcu.io.num_ai>3)
		{
			offset=1;
			for(j=0;j<3;j++)
			{
				ShowTemperature(lcd_txt,&mcu.io.analog[mcu.io.num_ao+j]);lcd_sprintf(lcd_txt,j*7,10);					
			}
			for(j=0;j<(mcu.io.num_ai-3);j++)
			{
				ShowTemperature(lcd_txt,&mcu.io.analog[mcu.io.num_ao+j+3]);lcd_sprintf(lcd_txt,j*7,11);					
			}			
		}
		else
			for(j=0;j<(mcu.io.num_ai);j++)
			{
				ShowTemperature(lcd_txt,&mcu.io.analog[mcu.io.num_ao+j]);lcd_sprintf(lcd_txt,j*7,10);					
			}		
		
		lcd_sprintf_P(BMP_Dict[8],0,11+offset);	
		if(mcu.io.num_ao>3)		
		{
			for(j=0;j<3;j++)
			{
				ShowPowerShort(lcd_txt,(s16*)&mcu.io.analog[j]);lcd_sprintf(lcd_txt,j*7,12+offset);
				
			}	
			for(j=0;j<(mcu.io.num_ao-3);j++)
			{
				ShowPowerShort(lcd_txt,(s16*)&mcu.io.analog[j+3]);lcd_sprintf(lcd_txt,j*7,13+offset);
				
			}				
		}	
		else
			for(j=0;j<(mcu.io.num_ao);j++)
			{
				ShowPowerShort(lcd_txt,(s16*)&mcu.io.analog[j]);lcd_sprintf(lcd_txt,j*7,12+offset);
				
			}				
	}
}
//-----------------------------------------------------------------------------------
void show_time_bmp()
{
	u8 tmp;	
	
//	FT_Time=500;
	if(txt_mode!=1)
	{
		txt_mode=1;	
		FT_Time=100;
		_Txt_0.Stat=10;
		_Txt_1.Stat=10;
		_Txt_3.Stat=10;
		_Txt_4.Stat=10;								
		return;
	}	
/*	if(int_state & but_Int1s)
	{
		int_state&=~but_Int1s;	
//		enter_tech_menu2++;
//		if(enter_tech_menu2>20)
		{
		enter_tech_menu2=0;
	    txt_mode=0;
	    clear_page();
	    LCDMenuPtr=&_Page0;
	    clear_page();	    
    	LCDMenuPtr=&_Tech_Menu;	
    	_Tech_Menu_Clock.Stat=0;
    	_Tech_Menu_Contrast.Stat=0;
    	_Tech_Menu_Temperature.Stat=0;
    	_Tech_Menu_Tech.Stat=0;    	    	    	
    	enter_tech_menu=0;
    	repaint_page();			
    	return;
		}
	}
*/
	
	if(FT_Time!=0)return;	
	
	if(int_state & but_Int3s)
	{
		int_state&=~but_Int3s;	
		if(time_blink & 1)
			show_single_bmp_txt(&_Txt_2);
		else
			clear_single_bmp_txt(&_Txt_2);		

		LCDMenuPtr_Tmp_Txt=&_Txt_0;		
		tmp=ft.field.Hour/10;
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}
	
		LCDMenuPtr_Tmp_Txt=&_Txt_1;			
		tmp=ft.field.Hour-tmp*10;
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}
						
		LCDMenuPtr_Tmp_Txt=&_Txt_3;			
		tmp=ft.field.Minute/10;
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}

		LCDMenuPtr_Tmp_Txt=&_Txt_4;			
		tmp=ft.field.Minute-tmp*10;
		if(LCDMenuPtr_Tmp_Txt->Stat!=tmp)
		{
			LCDMenuPtr_Tmp_Txt->Stat=tmp;
			show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		}
	}
}
//-----------------------------------------------------------------------------------
void show_info_page()
{

	u8 tmp;		
	u16 temp;
	u8 tmp0,tmp1,tmp2;
	s16 temperature;
	u8 old_stat=0;
	
	mcu.rx_list=0;
	mcu.rx_list|=rx_io;		
	if(txt_update!=0)
	{
		txt_update=0;
		FT_Time=100;
		_Info_Te_0.Stat=10;
		_Info_Te_1.Stat=10;
		_Info_Te_2.Stat=10;
		_Info_Te_3.Stat=10;	
		
		_Info_To_0.Stat=10;
		_Info_To_1.Stat=10;
		_Info_To_2.Stat=10;

		_Info_Tk_0.Stat=10;
		_Info_Tk_1.Stat=10;
		_Info_Tk_2.Stat=10;
		
		_Info_V_0.Stat=10;
		_Info_V_1.Stat=10;
		_Info_V_2.Stat=10;

		_Info_K_0.Stat=10;
		_Info_K_1.Stat=10;
		_Info_K_2.Stat=10;						
		return;
	}	
	
	if(FT_Time!=0)return;
	FT_Time=1000;
	
	temperature=mcu.io.analog[mcu.io.num_ao];
	if(temperature>999)temperature=999;
	LCDMenuPtr_Tmp_Txt=&_Info_Te_0;		
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
	
	LCDMenuPtr_Tmp_Txt=&_Info_Te_1;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;
	tmp0=temp/100;
	temp-=tmp0*100;
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(tmp0==0)
		LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
	LCDMenuPtr_Tmp_Txt=&_Info_Te_2;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;
	tmp0=temp/10;
	temp-=tmp0*10;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		
	LCDMenuPtr_Tmp_Txt=&_Info_Te_3;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;
	tmp0=temp;
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);		
	
	//-------------------------------------------------------------------------------
	temperature=mcu.io.analog[mcu.io.num_ao+1];
	if(temperature<0)temp=-temperature;
	else temp=temperature;
	if(temp>999)temp=999;
	
	LCDMenuPtr_Tmp_Txt=&_Info_To_0;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;
	tmp0=temp/100;
	temp-=tmp0*100;
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(tmp0==0)
		LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
	LCDMenuPtr_Tmp_Txt=&_Info_To_1;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;
	tmp0=temp/10;
	temp-=tmp0*10;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		
	LCDMenuPtr_Tmp_Txt=&_Info_To_2;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;
	tmp0=temp;
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);		
	//-------------------------------------------------------------------------------	
	//-------------------------------------------------------------------------------
	temperature=mcu.io.analog[mcu.io.num_ao+2];
	if(temperature<0)temp=-temperature;
	else temp=temperature;
	if(temp>999)temp=999;
	
	LCDMenuPtr_Tmp_Txt=&_Info_Tk_0;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;
	tmp0=temp/100;
	temp-=tmp0*100;
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(tmp0==0)
		LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
	LCDMenuPtr_Tmp_Txt=&_Info_Tk_1;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;
	tmp0=temp/10;
	temp-=tmp0*10;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		
	LCDMenuPtr_Tmp_Txt=&_Info_Tk_2;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;
	tmp0=temp;
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);		
	//-------------------------------------------------------------------------------	
	//-------------------------------------------------------------------------------
	temperature=mcu.io.analog[mcu.io.num_ao+3];
	if(temperature<0)temp=-temperature;
	else temp=temperature;
	if(temp>999)temp=999;
	
	LCDMenuPtr_Tmp_Txt=&_Info_V_0;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;
	tmp0=temp/100;
	temp-=tmp0*100;
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(tmp0==0)
		LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
	LCDMenuPtr_Tmp_Txt=&_Info_V_1;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;
	tmp0=temp/10;
	temp-=tmp0*10;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		
	LCDMenuPtr_Tmp_Txt=&_Info_V_2;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;
	tmp0=temp;
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);		
	//-------------------------------------------------------------------------------	
	//-------------------------------------------------------------------------------
	temperature=mcu.io.analog[mcu.io.num_ao+4];
	if(temperature<0)temp=-temperature;
	else temp=temperature;
	if(temp>999)temp=999;
	
	LCDMenuPtr_Tmp_Txt=&_Info_K_0;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;
	tmp0=temp/100;
	temp-=tmp0*100;
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(tmp0==0)
		LCDMenuPtr_Tmp_Txt->Stat=16;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
	
	LCDMenuPtr_Tmp_Txt=&_Info_K_1;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;
	tmp0=temp/10;
	temp-=tmp0*10;	
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);
		
	LCDMenuPtr_Tmp_Txt=&_Info_K_2;	
	old_stat=LCDMenuPtr_Tmp_Txt->Stat;
	tmp0=temp;
	LCDMenuPtr_Tmp_Txt->Stat=tmp0;		
	if(old_stat!=LCDMenuPtr_Tmp_Txt->Stat)show_single_bmp_txt(LCDMenuPtr_Tmp_Txt);		
	//-------------------------------------------------------------------------------	
}
//-----------------------------------------------------------------------------------
void show_error_page()
{
	u8 tmp;	
	u8 i,j,t;
	u8 offset=0;
//	FT_Time=500;
	if(txt_update!=3)
	{
		txt_update=3;
		mcu.rx_list=0;
		mcu.rx_list|=rx_errors;
		FT_Time=100;
	}	
	if(FT_Time!=0)return;
	FT_Time=1000;
//	lcd_clear_text();	
	for(i=0;i<MAX_ERRORS_NUM;i++) 
	{
		if(mcu.errors.item[i].code!=0)
		{		
			// Date
			ByteToStrFillZero(lcd_txt,&mcu.errors.item[i].time.field.Date,0,2,'0');
			lcd_txt[2]='/';lcd_txt[3]=0;
			lcd_sprintf(lcd_txt,0,3+(i*2));
			ByteToStrFillZero(lcd_txt,&mcu.errors.item[i].time.field.Month,0,2,'0');
			lcd_txt[2]='/';lcd_txt[3]=0;
			lcd_sprintf(lcd_txt,3,3+(i*2));
			ByteToStrFillZero(lcd_txt,&mcu.errors.item[i].time.field.Year,0,2,'0');
			lcd_sprintf(lcd_txt,6,3+(i*2));	
			// Time
			ByteToStrFillZero(lcd_txt,&mcu.errors.item[i].time.field.Hour,0,2,'0');
			lcd_txt[2]=':';lcd_txt[3]=0;
			lcd_sprintf(lcd_txt,9,3+(i*2));
			ByteToStrFillZero(lcd_txt,&mcu.errors.item[i].time.field.Minute,0,2,'0');
			lcd_txt[2]=':';lcd_txt[3]=0;
			lcd_sprintf(lcd_txt,12,3+(i*2));
			ByteToStrFillZero(lcd_txt,&mcu.errors.item[i].time.field.Second,0,2,'0');
			lcd_sprintf(lcd_txt,15,3+(i*2));				

			tmp=mcu.errors.item[i].code>>8;
			ByteToStrFillZero(lcd_txt,&tmp,0,2,'0');
			lcd_sprintf(lcd_txt,18,3+(i*2));				
			tmp=mcu.errors.item[i].code;
			ByteToStrFillZero(lcd_txt,&tmp,0,2,'0');
			lcd_sprintf(lcd_txt,21,3+(i*2));				

//			WordToStrFillZero(lcd_txt,&mcu.errors.item[i].code,0,2,'0',0);
//			lcd_sprintf(lcd_txt,18,3+(i*2));				
			lcd_sprintf_P(eng_errors_str[mcu.errors.item[i].code>>8],0,3+2*i+1);			
		}		
		if(mcu.errors.item[i].code==0)return;
	}		
}
//-----------------------------------------------------------------------------------
void Page3_clear_errors()
{
	memset((void *)&mcu.errors, 0, sizeof(TErrors));	
	mcu.tx_list|=tx_errors;
	lcd_clear_text();	
}
//-----------------------------------------------------------------------------------
void update_menu()
{
	u8 i;
	u8 old_stat;
	u8 Old_Active_Screen;
	{
		ltmp=1;		
		LCDMenuPtr_Tmp2=&_Menu0;
		Old_Active_Screen=Active_Screen;
		for(i=0;i<5;i++)
		{
			old_stat=LCDMenuPtr_Tmp2->Stat;
			LCDMenuPtr_Tmp2->Stat=0;
			if(LCDMenuPtr==LCDMenuPtr_Tmp2)
			{
				LCDMenuPtr_Tmp2->Stat=1;
				Active_Screen=i;
			}
			// Process buttons depending on own_state.bst
			if(LCDMenuPtr_Tmp2!=NULL) 
				if(old_stat!=LCDMenuPtr_Tmp2->Stat)
				{
					show_single_bmp(LCDMenuPtr_Tmp2);
				}
			if(LCDMenuPtr_Tmp2->NextItem!=NULL)
				LCDMenuPtr_Tmp2=LCDMenuPtr_Tmp2->NextItem;
		}
		update_screen=1;	
		if(Old_Active_Screen!=Active_Screen)
		{		
			lcd_clear_text();	
			switch(Old_Active_Screen)
			{
				case 0:LCDMenuPtr=&_Page0;clear_page();break;
				case 1:LCDMenuPtr=&_Page1;clear_page();break;
				case 2:LCDMenuPtr=&_Page2;clear_page();break;
				case 3:LCDMenuPtr=&_Page3;clear_page();break;
				case 4:LCDMenuPtr=&_Page4;clear_page();break;		
			}	
			switch(Active_Screen)
			{
				case 0:LCDMenuPtr=&_Page0;repaint_page();break;
				case 1:LCDMenuPtr=&_Page1;repaint_page();break;
				case 2:LCDMenuPtr=&_Page2;repaint_page();break;
				case 3:LCDMenuPtr=&_Page3;repaint_page();break;
				case 4:LCDMenuPtr=&_Page4;repaint_page();break;		
			}			
		}	
	}		
}
//-----------------------------------------------------------------------------------
void calibrate_bmp()
{
	u8 tmp;	
	u8 stat=0;
	u16 x[2];
	u16 y[2];
	u8 s[2]={0,0};
	u8 str[20];
	u8 count;
	f32 fx,fy;
	clear_page();
	lcd_clear_text();	
	LCDMenuPtr=_Calibrate.SubItem;		
	lcd_sprintf("Calibration routine ",3,0);
	lcd_sprintf("1 Press left uper point",3,1);	
	_sprintf(outtxt,"\n\r !");		
	show_single_bmp(&_Point_0);
	_sprintf(outtxt,"\n\r !!");	
	show_single_bmp(&_Point_1);	
	_sprintf(outtxt,"\n\r !!!");
//	handle_page();
//	repaint_page();
	tsc_n=0;
	TSC_Time=TSC_REQUEST_TIME;
	count=0;
	fx=fy=0;
	while(count<20)
	{
		if(TSC_Time==0)
		{
			TSC_Time=TSC_REQUEST_TIME;
			Ext_IRQ0();
			adm_wd_reset;
			if(tsc_n)
			{
				fx+=tsc_rx;
				fy+=tsc_ry;	
				count++;			
			}
		}
	}
	x[0]=fx/20;
	y[0]=fy/20;			
	s[0]=1;
	lcd_sprintf("X=",5,2);WordToStr(str,(u16*)&tsc_x,0);lcd_sprintf(str,7,2);
	lcd_sprintf("Y=",5,3);WordToStr(str,(u16*)&tsc_y,0);lcd_sprintf(str,7,3);

	lcd_sprintf("2 Press right down point",3,4);	
	Delay(1000);
	TSC_Time=TSC_REQUEST_TIME;
	count=0;
	fx=fy=0;
	while(count<20)
	{
		if(TSC_Time==0)
		{
			TSC_Time=TSC_REQUEST_TIME;
			Ext_IRQ0();
			adm_wd_reset;
			if(tsc_n)
			{
				fx+=tsc_rx;
				fy+=tsc_ry;	
				count++;			
			}
		}
	}
	x[1]=fx/20;
	y[1]=fy/20;			
	s[1]=1;
	lcd_sprintf("X=",5,5);WordToStr(str,(u16*)&tsc_x,0);lcd_sprintf(str,7,5);
	lcd_sprintf("Y=",5,6);WordToStr(str,(u16*)&tsc_y,0);lcd_sprintf(str,7,6);
	// Proportions
	fx=x[1]-x[0];
	fx=216/fx;
	m.coff.x=fx;
	fy=y[1]-y[0];
	fy=104/fy;
	m.coff.x=fx;
	m.coff.y=fy;
	// Offsets	
	fx=11/m.coff.x;
	fx=x[0]-fx;
	m.coff.ox[0]=fx;

	fy=11/m.coff.y;
	fy=y[0]-fy;
	m.coff.oy[0]=fy;
	
	Delay(2000);
	params_store();
	lcd_clear_text();
	clear_single_bmp(&_Point_0);
	clear_single_bmp(&_Point_1);	
//	repaint_page();
__no_operation();
}
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
