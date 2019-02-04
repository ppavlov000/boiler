//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
//#define MAX_ANSWER_DELAY	200	// ms UPC_Time
//-----------------------------------------------------------------------------------
u8 first_start=1;
u8 transparent_packet=0;
//-----------------------------------------------------------------------------------
extern TPhoneRecord PhoneList[5];
extern TPassword Password;
extern u8 custom_information_update;
extern TBuff M_buff;
extern u8 M_buff_sign;
extern u8 M_SCH_Time;
//extern u8 Manual_Mode;
//extern TSeason Season;
//extern u8 Controller_Mode;
//extern s16 Preset;
//extern s16 Temperature[3];
extern TDevice_Info device_info[MAX_DEVICES_NUM];
extern u16 Fan_Speed;
extern u8 new_step;
extern TLCDPictTop Scr_0;
extern u8 Update_Work_Regs;

extern u8 Update_Work_Regs;
void regs_to_work();
void work_to_regs();
//-----------------------------------------------------------------------------------
#if __MODBUS_ENA==0
//-----------------------------------------------------------------------------------
void upc_answer_reset()
{
	tx.field.pre=0x55AA;
	
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=com_reqt_reset;	
		
	tx.field.len=0;
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);	
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;
	// Clear flag of first start	
	first_start=0;
}
//-----------------------------------------------------------------------------------
/*
void upc_answer_sys()
{
//	u8 *ptr;
			
  	exch=own_state;
	if(own_state.status & bit_new_push) UPC_Time=MAX_ANSWER_DELAY;
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=com_reqt_status;	
	tx.field.len=2;	
	
	tx.field.d[0]=MAIN_PANEL;	// Main programm is working
	FGet((u8*)&tx.field.d[1],HAPP_FLASH_START+THW_LOC,4);
	tx.field.len=8;		
	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);	
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
//	tx_mode(); lc!!!
	UPC_Time2=3;
	// !!! Clear flags of new data
//	own_state.status&=~bit_new_push;
//	upc.data_status&=~b_buttons_new;	
}
*/
void upc_answer_sys()
{
//	u8 *ptr;
	if(own_state.status & bit_new_push) UPC_Time=MAX_ANSWER_DELAY;	
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;

	tx.field.d[0]=MAIN_PANEL;	// Main programm is working
	FGet_c(HAPP_FLASH_START+THW_LOC,(u8*)&tx.field.d[1],4);
//	FGet(HAPP_FLASH_START+TSW_LOC,(u8*)&tx.field.d[5],4);
	FGet_c(HAPP_FLASH_START+TTIME_LOC,(u8*)&tx.field.d[5],7);	

	FGet_c(HPLM_FLASH_START+THW_LOC,(u8*)&tx.field.d[1+12],4);
//	FGet(HAPP_FLASH_START+TSW_LOC,(u8*)&tx.field.d[5+16],4);
	FGet_c(HPLM_FLASH_START+TTIME_LOC,(u8*)&tx.field.d[5+12],7);	
	
	//memcpy((u8*)&tx.field.d[8],&ft,sizeof(TExSTATUS));
	Status=(TExSTATUS*)&tx.field.d[30];
//	Status->Manual_Mode=Manual_Mode;
//	Status->ft=ft;
	Status->Season=MenuRegs.Season.season;
//	Status->Controller_Mode=pid[0].mode;
//	Status->Preset_Temperature=pid[0].t0;	
	Status->Preset_Speed=io.aoutput[0];	//pid[0].power;
	Status->Temperature=io.ainput[2];	
	tx.field.len=30+sizeof(TExSTATUS);			
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;
}
//-----------------------------------------------------------------------------------
void upc_set_sys()
{
//	u8 *ptr;
	Status=(TExSTATUS*)&rx.field.d[8];
//	Controller_Mode=Status->Controller_Mode;
//	Preset=Status->Preset_Temperature;	
//	Fan_Speed=Status->Preset_Speed;	
//	Temperature[2]=Status->Temperature;	

//	Status->Season=MenuRegs.Season.season;
//	pid[0].mode=Status->Controller_Mode;
//	pid[0].t0=Status->Preset_Temperature;	
//	pritochka_fan_speed=io.aoutput[0]=Status->Preset_Speed;	//pid[0].power;
//	Button_no_update_time=500;
//	new_step=100;	
	WorkInfo.type=TYPE_PRITOCHKA;
	WorkInfo.season=MenuRegs.Season.season;		// No update
	WorkInfo.mode=Status->Controller_Mode;
	WorkInfo.speed[0]=Status->Preset_Speed;;
	WorkInfo.temperature[0]=Status->Preset_Temperature;

	Update_Work_Regs=1;			
	
//	Status->Temperature=io.ainput[1];	
	
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=0;	
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(TExSTATUS);	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;
//	extern TLCDPictTop Sc
//	if(LCDTopPtr==&Scr_0)new_step=20;
}
//-----------------------------------------------------------------------------------
void upc_answer_sys_2()
{
//	u8 *ptr;
	if(own_state.status & bit_new_push) UPC_Time=MAX_ANSWER_DELAY;	
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;
/*
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
*/					
	tx.field.d[0]=device_info[0].type;	// Main programm is working
	*(u32*)&tx.field.d[1]=device_info[0].hw_sys;
	*(TTime*)&tx.field.d[5]=device_info[0].sys_time;	

	*(u32*)&tx.field.d[1]=device_info[1+12].hw_usr;
	*(TTime*)&tx.field.d[5]=device_info[5+12].usr_time;	
	
	//memcpy((u8*)&tx.field.d[8],&ft,sizeof(TExSTATUS));
	Status=(TExSTATUS*)&tx.field.d[30];
//	Status->Manual_Mode=device_info[device_found].mode;
//	Status->ft=ft;
//	Status->Season=Season.season;
	Status->Controller_Mode=device_info[0].mode;
	Status->Preset_Temperature=device_info[0].tp;	
	Status->Preset_Speed=device_info[0].power;
	Status->Temperature=device_info[0].t;	
	tx.field.len=30+sizeof(TExSTATUS);			
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;
}
//-----------------------------------------------------------------------------------

void upc_Set_Panel_Time()
{
/*
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=com_reqt_time;	
	tx.field.len=sizeof(m.ft);	
	memcpy(&tx.field.d[0],&m.ft,sizeof(m.ft));
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);	
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
//	tx_mode(); lc!!!
	UPC_Time2=3;
	upc.data_status&=~b_time_new;
*/	
}
//-----------------------------------------------------------------------------------
void upc_Set_Panel_Temperature()
{
/*
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=com_reqt_fan;	
	tx.field.len=sizeof(m.fan);	
	memcpy(&tx.field.d[0],&m.fan,sizeof(m.fan));
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);	
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
//	tx_mode(); lc!!!
	UPC_Time2=3;	
	upc.data_status&=~b_fancoil_new;
*/	
}
//-----------------------------------------------------------------------------------
void upc_answer_info(u8 what)
{
//	u8 *ptr;
	THeadShort info;
	memset(&info,0,sizeof(TPanelInfo));
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=1;
	
	tx.field.len=0;	
	switch(what)
	{
		case 1:
			tx.field.com.bit.com=com_reqt_sys_info;
			info.present=1;
			FGet((u8*)&info.HW_Version,HAPP_FLASH_START+THW_LOC,4);
			FGet((u8*)&info.SW_Version,HAPP_FLASH_START+TSW_LOC,4);
			FGet((u8*)&info.Time,HAPP_FLASH_START+TTIME_LOC,sizeof(TTime));
			memcpy(&tx.field.d[0],&info,sizeof(info));	
			tx.field.len=sizeof(info);		
		break;
		case 2:
			tx.field.com.bit.com=com_reqt_sys_name;
			FGet((u8*)&tx.field.d[0],HAPP_FLASH_START+TNAME_LOC,TNAME_WIDTH);
			tx.field.len=TNAME_WIDTH;
		break;		
		case 3:
			tx.field.com.bit.com=com_reqt_menu_info;
			info.present=1;
			FGet((u8*)&info.HW_Version,HPLM_FLASH_START+THW_LOC,4);
			FGet((u8*)&info.SW_Version,HPLM_FLASH_START+TSW_LOC,4);
			FGet((u8*)&info.Time,HPLM_FLASH_START+TTIME_LOC,sizeof(TTime));
			memcpy(&tx.field.d[0],&info,sizeof(info));	
			tx.field.len=sizeof(info);
		break;					
		case 4:
			tx.field.com.bit.com=com_reqt_menu_name;
			FGet((u8*)&tx.field.d[0],HPLM_FLASH_START+TNAME_LOC,TNAME_WIDTH);
			tx.field.len=TNAME_WIDTH;
		break;		
		
	}	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);	
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
//	tx_mode(); lc!!!
	UPC_Time2=3;
//	_sprintf(outtxt,"\n\r ");
//	mem_dump(&tx.field.d[0],sizeof(info));	
}
//-----------------------------------------------------------------------------------
void upc_answer_alarm()
{
/*	
	if(rx.field.len>=3)
	{
		m.Alarm_Status=rx.field.d[0];
		m.Alarm.field.Hour=rx.field.d[1];
		m.Alarm.field.Minute=rx.field.d[2];
		int_state|=but_Int0s;
	}
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=1;
	tx.field.com.bit.com=com_reqt_alarm;
	tx.field.d[0]=m.Alarm_Status;
	tx.field.d[1]=m.Alarm.field.Hour;
	tx.field.d[2]=m.Alarm.field.Minute;
	tx.field.len=3;		
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);	
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;
*/	
}
//-----------------------------------------------------------------------------------
void upc_answer_set_alarm()
{
/*
	m.Alarm_Status=rx.field.d[0];
	m.Alarm.field.Hour=rx.field.d[1];
	m.Alarm.field.Minute=rx.field.d[2];
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=1;
	tx.field.com.bit.com=com_answ_set_alarm;
	tx.field.d[0]=m.Alarm_Status;
	tx.field.d[1]=m.Alarm.field.Hour;
	tx.field.d[2]=m.Alarm.field.Minute;
	tx.field.len=3;		
	tx.field.crc=upc_crc(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;
*/
}
//-----------------------------------------------------------------------------------
void upc_Answer_Custom_Info()
{
/*
	tx.field.pre=0x55AA;		
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=com_reqt_alarm;
	tx.field.len=0;	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);	
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
//	tx_mode(); lc!!!
	UPC_Time2=3;	
*/	
}
//-----------------------------------------------------------------------------------
void upc_Set_Custom_Info()
{
/*	
	tx.field.pre=0x55AA;		
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=com_reqt_set_alarm;
	memcpy(&tx.field.d[0],&Password,sizeof(TPassword));
	memcpy(&tx.field.d[sizeof(TPassword)],&PhoneList,5*sizeof(TPhoneRecord));
	tx.field.len=sizeof(TCustomInfo);	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);	
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
//	tx_mode(); lc!!!
	UPC_Time2=3;	
	if(custom_information_update!=0)custom_information_update--;
*/	
}
//-----------------------------------------------------------------------------------
void upc_answer_set_transparent()
{
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=com_set_tansp;	
	tx.field.len=0;
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);	
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;
}
//-----------------------------------------------------------------------------------
void upc_answer_release_transparent()
{
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=com_release_transp;	
	tx.field.len=0;
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);	
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;
}
//-----------------------------------------------------------------------------------
void upc_S_transparent_packet()
{
//	if(M_buff_sign){
//		BUZZ_Time=50;
//		return;
//	}
	M_buff=rx;
	M_buff_sign=1;
	M_SCH_Time=2;
//	memcpy(&M_tx,&rx,sizeof(M_tx));
//	BUZZ_Time=50;
//	M.txnew=1;
//	M.txcount=0;
//	M.status=st_sending;		
//	M.rxnew=0;
//	M.rxcount=0;		
//	M.error=0;
//	M.done=0;
}
//-----------------------------------------------------------------------------------
void upc_S_transparent_packet_2()
{
	M_buff_sign=1;
	memcpy(&M_buff,&rx.field.d[0] ,rx.field.len+PACKET_HEADER_LEN);
	M_SCH_Time=2;
//	BUZZ_Time=50;
//	M.txnew=1;
//	M.txcount=0;
//	M.status=st_sending;		
//	M.rxnew=0;
//	M.rxcount=0;		
//	M.error=0;
//	M.done=0;
}
//-----------------------------------------------------------------------------------
void upc_S_return_transparent_packet()
{
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=com_transp;	
	tx.field.len=M_rx.field.len+PACKET_HEADER_LEN;
	memcpy(&tx.field.d[0],&M_rx ,M_rx.field.len+PACKET_HEADER_LEN);
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);	
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;
}
//-----------------------------------------------------------------------------------
void upc_answer_set_register()
{
//	rx.field.d[0] - address
//	rx.field.d[1] - number of bytes
//	rx.field.d[0] - data itself
	u16 addr;
	u8 len;
	memcpy(&addr,&rx.field.d[0],2);		
	len=rx.field.d[2];
	memcpy(&reg_data[addr],&rx.field.d[3],len);	
/*
	__sprintf(outtxt," ");
	WordToStr(outtxt,&addr,0);
	__sprintf(outtxt," ");
	ByteToStr(outtxt,&len,0);
	__sprintf(outtxt," ");
	ByteToStr(outtxt,&reg_data[addr],0);
	__sprintf(outtxt," ");
*/
//	if(reg_data[addr]==0)BuzzerTime=50;
//	if(reg_data[addr]==1)BuzzerTime=5;	
//	BuzzerTime=10;
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=0;	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;		
}
//-----------------------------------------------------------------------------------
void upc_answer_get_register()
{
	u16 addr;
	u8 len;
	memcpy(&addr,&rx.field.d[0],2);		
	len=rx.field.d[2];
	memcpy(&tx.field.d[3],&reg_data[addr],len);
	memcpy(&tx.field.d[0],&addr,2);	
	tx.field.d[2]=len;
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=len+3;	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;		
}
//-----------------------------------------------------------------------------------
void upc_answer_get_prog()
{
//	u8 *ptr;
	TProgramInfo *prog_info=(TProgramInfo*)&tx.field.d[0];
	
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;

	prog_info->identificator=MAIN_PANEL;	// Main programm is working
	FGet_c(HAPP_FLASH_START+THW_LOC,(u8*)&prog_info->prog[0].serial,4);
	FGet_c(HAPP_FLASH_START+TTIME_LOC,(u8*)&prog_info->prog[0].time,7);	

	FGet_c(HPLM_FLASH_START+THW_LOC,(u8*)&prog_info->prog[0].serial,4);
	FGet_c(HPLM_FLASH_START+TTIME_LOC,(u8*)&prog_info->prog[0].time,7);	
	
	tx.field.len=sizeof(TProgramInfo);			
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;
}
//-----------------------------------------------------------------------------------
void upc_answer_get_work()
{
	regs_to_work();	
	memcpy(&tx.field.d[0],&WorkInfo,sizeof(WorkInfo));

	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(TWorkInfo);			
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;
}
//-----------------------------------------------------------------------------------
void upc_answer_set_work()
{
	memcpy(&WorkInfo,&rx.field.d[0],sizeof(WorkInfo));
	Update_Work_Regs=1;		
	
	if(rx.field.com.bit.id==0)return;
		
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m.Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;		
	tx.field.len=sizeof(TWorkInfo);			
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;
}
//-----------------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------------
