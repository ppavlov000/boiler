//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
#define MAX_ANSWER_DELAY	200	// ms UPC_Time
//-----------------------------------------------------------------------------------
u8 first_start=1;
TIO *io_ptr;
TExSTATUS *Status;
//-----------------------------------------------------------------------------------
void upc_answer_sys()
{
//	u8 *ptr;
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;
//	tx.field.len=sizeof(TExSTATUS);	
//	ptr=&tx.field.d[0];
//	*ptr=0;
//	ptr+=1;
//	*ptr=MenuRegs.Season;
//	ptr+=1;
//	memcpy(ptr,&ft,sizeof(TCTime));
	tx.field.d[0]=MAIN_CONTROLLER;	// Main programm is working
	FGet(HAPP_FLASH_START+THW_LOC,(u8*)&tx.field.d[1],4);
//	FGet(HAPP_FLASH_START+TSW_LOC,(u8*)&tx.field.d[5],4);
	FGet(HAPP_FLASH_START+TTIME_LOC,(u8*)&tx.field.d[5],7);	

	FGet(HPLM_FLASH_START+THW_LOC,(u8*)&tx.field.d[1+12],4);
//	FGet(HAPP_FLASH_START+TSW_LOC,(u8*)&tx.field.d[5+16],4);
	FGet(HPLM_FLASH_START+TTIME_LOC,(u8*)&tx.field.d[5+12],7);	
	
	//memcpy((u8*)&tx.field.d[8],&ft,sizeof(TExSTATUS));
	Status=(TExSTATUS*)&tx.field.d[30];
	Status->Manual_Mode=MenuRegs.Manual_Mode;
	Status->ft=MenuRegs.Time;
	Status->Season=MenuRegs.Season.season;
#if NUM_PID
	Status->Controller_Mode=pid[0].mode;
	Status->Preset_Temperature=pid[0].t0;	
	Status->Preset_Speed=io.aoutput[0];
	Status->Temperature=io.ainput[pid[0].channel];	
#endif
	tx.field.len=30+sizeof(TExSTATUS);			
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;
}
//-----------------------------------------------------------------------------------
void upc_answer_io()
{
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(TIO);	
	memcpy(&tx.field.d[0],&io,sizeof(TIO));	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;
}

//-----------------------------------------------------------------------------------
void upc_answer_pid(u8 pid_num)
{
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(TPID);	
#if 	NUM_PID		
	if(pid_num<NUM_PID)	
		memcpy(&tx.field.d[0],&pid[pid_num],sizeof(TPID));	
	else
		memset(&tx.field.d[0],0,sizeof(TPID));	
#else
	memset(&tx.field.d[0],0,sizeof(TPID));	
#endif	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;;
}
//-----------------------------------------------------------------------------------
void upc_answer_fan(u8 fan_num)
{
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(TPID);	
#if 	MAX_FANCOIL_NUMBER	
	if(fan_num<MAX_FANCOIL_NUMBER)	
		memcpy(&tx.field.d[0],&fan[fan_num],sizeof(TFanCoil));	
	else
		memset(&tx.field.d[0],0,sizeof(TFanCoil));	
#else
	memset(&tx.field.d[0],0,sizeof(TFanCoil));	
#endif	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;;
}
//-----------------------------------------------------------------------------------
void upc_answer_kotel(u8 kot_num)
{
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=19;	
#if 	MAX_KOTEL_NUMBER	
	memcpy(&tx.field.d[0],&kotel,19);	
#else
	memset(&tx.field.d[0],0,19);	
#endif	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;;
}
//-----------------------------------------------------------------------------------
void upc_answer_kotel_params(u8 kot_num)
{
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(TKotelModeRec);	
#if 	MAX_KOTEL_NUMBER	
	memcpy(&tx.field.d[0],&kotel.p[0][rx.field.d[2]],sizeof(TKotelModeRec));	
#else
	memset(&tx.field.d[0],0,sizeof(TKotelModeRec));	
#endif	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;;
}
//-----------------------------------------------------------------------------------
void upc_answer_errors()
{
//	u8 *ptr;
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;	
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(TErrors);	
	memcpy(&tx.field.d[0],&errors,sizeof(TErrors));
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;;
}
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void upc_set_sys()
{
//	u8 *ptr;
//	memcpy(&ft,&rx.field.d[1],sizeof(TCTime));	
	Status=(TExSTATUS*)&rx.field.d[8];
	MenuRegs.Manual_Mode=Status->Manual_Mode;
//	Status->ft=MenuRegs.Time;
	MenuRegs.Season.season=Status->Season;	
#if NUM_PID
	pid[0].mode=Status->Controller_Mode;
	pid[0].t0=Status->Preset_Temperature;	
#endif
	io.aoutput[0]=Status->Preset_Speed;	
	Time_To_Store=3;	
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;	
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(TExSTATUS);	
//	ptr=&tx.field.d[0];
//	*ptr=0;
//	ptr+=1;
//	memcpy(ptr,&ft,sizeof(TCTime));
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;;
}
//-----------------------------------------------------------------------------------
void upc_set_io()
{
	u8 i;
//	memcpy(&io,&rx.field.d[0],sizeof(TExIO));		
//	if()
	io_ptr=(TIO*)&rx.field.d[0];
	io.dout=io_ptr->dout;
//	if(io.num_ao==io_ptr->num_ao)
	for(i=0;i<io.num_ao;i++)
		io.aoutput[i]=io_ptr->aoutput[i];
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;	
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=0;	
//	memcpy(&tx.field.d[0],&io,sizeof(TExIO));	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;;
}

//-----------------------------------------------------------------------------------
void upc_set_pid()
{
	u8 pid_num=rx.field.d[0];
#if NUM_PID	
	if(pid_num<NUM_PID)	memcpy(&pid[pid_num],&rx.field.d[1],rx.field.len-1);	
	Time_To_Store=3;	// Sign to store parameters	
#endif	
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
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
void upc_set_fan()
{
	u8 fan_num=rx.field.d[0];
#if MAX_FANCOIL_NUMBER		
	if(fan_num<MAX_FANCOIL_NUMBER)	memcpy(&fan[fan_num],&rx.field.d[1],rx.field.len-1);	
	Time_To_Store=3;	// Sign to store parameters
#endif
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
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
void upc_set_kotel()
{
	u8 kotel_num=rx.field.d[0];
#if MAX_KOTEL_NUMBER	
	if(kotel_num<MAX_KOTEL_NUMBER) memcpy(&kotel,&rx.field.d[1],rx.field.len-1);	
	Time_To_Store=3;	// Sign to store parameters
#endif
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
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
void upc_set_kotel_params()
{
	u8 kotel_num=rx.field.d[0];
#if MAX_KOTEL_NUMBER	
	if(kotel_num<MAX_KOTEL_NUMBER) memcpy(&kotel.p[0][rx.field.d[2]],&rx.field.d[3],rx.field.len-3);	
	Time_To_Store=3;	// Sign to store parameters
#endif
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
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
/*
//-----------------------------------------------------------------------------------
void upc_set_errors()
{
//	u8 *ptr;
//	memcpy(&errors,&rx.field.d[0],sizeof(TErrors));	
	memset(&errors,0,sizeof(TErrors));	
	Time_To_Store=3;		// Sign to store parameters	
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;	
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=0;
//	memcpy(&tx.field.d[0],&errors,sizeof(TErrors));
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;;
}
*/
//-----------------------------------------------------------------------------------
void upc_answer_time()
{
//	u8 *ptr;
	tx.field.pre=0x55AA;
	tx.field.com=rx.field.com;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;	
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(TCTime);	
	memcpy(&tx.field.d[0],&MenuRegs.Time,sizeof(TCTime));	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;;
}
/*
//-----------------------------------------------------------------------------------
void upc_answer_time_summ()
{
//	u8 *ptr;
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;	
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(TCTime);	
	memcpy(&tx.field.d[0],&MenuRegs.Season.date[0],sizeof(MenuRegs.Season.date[0]));	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;;
}
//-----------------------------------------------------------------------------------
void upc_answer_time_wint()
{
//	u8 *ptr;
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;	
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(TCTime);	
	memcpy(&tx.field.d[0],&MenuRegs.Season.date[1],sizeof(MenuRegs.Season.date[1]));	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;;
}
*/
//-----------------------------------------------------------------------------------
void upc_set_time()
{	
//	u8 *ptr;
	memcpy(&MenuRegs.Time,&rx.field.d[0],sizeof(TCTime));	
	fram_set_time(MenuRegs.Time.field.Hour,MenuRegs.Time.field.Minute,0);
	fram_set_date(MenuRegs.Time.field.Year,MenuRegs.Time.field.Month,MenuRegs.Time.field.Date,MenuRegs.Time.field.Day);
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;	
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=0;	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;;
}
/*
//-----------------------------------------------------------------------------------
void upc_set_time_summ()
{
//&MenuRegs.Season.date[0],sizeof(MenuRegs.Season.date[0]));		
//	u8 *ptr;
	memcpy(&MenuRegs.Season.date[0],&rx.field.d[0],sizeof(MenuRegs.Season.date[0]));	
	Time_To_Store=3;	
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;	
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=0;	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;;
}
//-----------------------------------------------------------------------------------
void upc_set_time_wint()
{
//	u8 *ptr;
	memcpy(&MenuRegs.Season.date[1],&rx.field.d[0],sizeof(MenuRegs.Season.date[0]));
	Time_To_Store=3;	
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;	
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=0;	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;;
}
*/
//-----------------------------------------------------------------------------------
void upc_set_in_parameters()
{
//	u8 *ptr;
	u8 ptr;
	u8 len;
	ptr=rx.field.d[0];
	len=rx.field.d[1];
	if(ptr<PARAMETERS_MAX)
		memcpy(&intr.in_params[ptr],&rx.field.d[2],len*2);	
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
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
void upc_answer_out_parameters()
{
	u8 ptr=rx.field.d[0];
	u8 len=rx.field.d[1];
//	BuzzerTime=50;
//	ByteToStr(outtxt,&len,0);		
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=len*2;	
//	memcpy(&tx.field.d[0],&intr.params[0],sizeof(intr.params));	
	if(ptr<PARAMETERS_MAX)
		memcpy(&tx.field.d[0],&intr.out_params[ptr],len*2);		
	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;
}
//-----------------------------------------------------------------------------------
void upc_answer_store_parameters()
{
	Time_To_Store=3;
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
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
void upc_answer_set_manual()
{
	MenuRegs.Manual_Mode=rx.field.d[0];
	tx.field.d[0]=MenuRegs.Manual_Mode;
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=com_set_manual;
	tx.field.len=1;	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;		
}
//-----------------------------------------------------------------------------------
void upc_answer_get_season()
{
	memcpy(&tx.field.d[0],&MenuRegs.Season,sizeof(TSeason));
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(TSeason);	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;		
}
//-----------------------------------------------------------------------------------
void upc_answer_set_season()
{
	memcpy(&MenuRegs.Season,&rx.field.d[0],sizeof(TSeason));
	memcpy(&tx.field.d[0],&MenuRegs.Season,sizeof(TSeason));
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(TSeason);	
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
	tx.field.com.bit.id=ID;
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
	tx.field.com.bit.id=ID;
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
void upc_answer_set_id()
{
	tx.field.com.bit.id=ID;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=0;	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;	
	ID=rx.field.d[0];
	id_store();
}
//-----------------------------------------------------------------------------------
