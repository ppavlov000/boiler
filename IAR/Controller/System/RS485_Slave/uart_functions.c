//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
#define MAX_ANSWER_DELAY	200	// ms UPC_Time
//-----------------------------------------------------------------------------------
u8 first_start=1;
//-----------------------------------------------------------------------------------
void upc_answer_sys()
{
	u8 *ptr;
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=MenuRegs.id;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(TExSTATUS);	
	ptr=&tx.field.d[0];
	*ptr=0;
	ptr+=1;
	*ptr=MenuRegs.Season;
	ptr+=1;
	memcpy(ptr,&ft,sizeof(TCTime));
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;;
}
//-----------------------------------------------------------------------------------
void upc_answer_io()
{
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=MenuRegs.id;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(TExIO);	
	memcpy(&tx.field.d[0],&io,sizeof(TExIO));	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;;
}
//-----------------------------------------------------------------------------------
void upc_answer_pid(u8 pid_num)
{
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=MenuRegs.id;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(TExPID);	
	memcpy(&tx.field.d[0],&pid[pid_num],sizeof(TExPID));	
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
	tx.field.com.bit.id=MenuRegs.id;
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

	u8 *ptr;
	memcpy(&ft,&rx.field.d[1],sizeof(TCTime));	
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=MenuRegs.id;
	tx.field.com.bit.req=0;	
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(TExSTATUS);	
	ptr=&tx.field.d[0];
	*ptr=0;
	ptr+=1;
	memcpy(ptr,&ft,sizeof(TCTime));
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
	memcpy(&io,&rx.field.d[0],sizeof(TExIO));		
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=MenuRegs.id;
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
void upc_set_pid(u8 pid_num)
{
	if(pid_num<NUM_PID)
		memcpy(&pid[pid_num],&rx.field.d[0],sizeof(TExPID));	
//	params_store();
	st_param=1;	// Sign to store parameters
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=MenuRegs.id;
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
void upc_set_errors()
{
//	u8 *ptr;
	memcpy(&errors,&rx.field.d[0],sizeof(TErrors));	
//	params_store();
	st_param=1;	// Sign to store parameters	
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=MenuRegs.id;
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
//-----------------------------------------------------------------------------------
void upc_answer_time()
{
//	u8 *ptr;
	tx.field.pre=0x55AA;
	tx.field.com=rx.field.com;
	tx.field.com.bit.id=MenuRegs.id;
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
//-----------------------------------------------------------------------------------
void upc_answer_time_summ()
{
//	u8 *ptr;
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=MenuRegs.id;
	tx.field.com.bit.req=0;	
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(TCTime);	
	memcpy(&tx.field.d[0],&MenuRegs.Time_Summ,sizeof(TCTime));	
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
	tx.field.com.bit.id=MenuRegs.id;
	tx.field.com.bit.req=0;	
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(TCTime);	
	memcpy(&tx.field.d[0],&MenuRegs.Time_Wint,sizeof(TCTime));	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;;
}
//-----------------------------------------------------------------------------------
void upc_set_time()
{	
//	u8 *ptr;
	memcpy(&MenuRegs.Time,&rx.field.d[0],sizeof(TCTime));	
	fram_set_time(MenuRegs.Time.field.Hour,MenuRegs.Time.field.Minute,0);
	fram_set_date(MenuRegs.Time.field.Year,MenuRegs.Time.field.Month,MenuRegs.Time.field.Date,MenuRegs.Time.field.Day);
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=MenuRegs.id;
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
void upc_set_time_summ()
{
//	u8 *ptr;
	memcpy(&MenuRegs.Time_Summ,&rx.field.d[0],sizeof(TCTime));	
//	params_store();	
	st_param=1;
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=MenuRegs.id;
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
	memcpy(&MenuRegs.Time_Wint,&rx.field.d[0],sizeof(TCTime));	
//	params_store();	
	st_param=1;
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=MenuRegs.id;
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
void upc_set_in_parameters()
{
//	u8 *ptr;
	memcpy(&intr.in_params[0],&rx.field.d[0],sizeof(intr.in_params));	
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=MenuRegs.id;
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
void upc_set_out_parameters()
{
//	u8 *ptr;
	memcpy(&intr.out_params[0],&rx.field.d[0],sizeof(intr.out_params));	
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=MenuRegs.id;
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
void upc_answer_in_parameters()
{
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=MenuRegs.id;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(intr.in_params);	
	memcpy(&tx.field.d[0],&intr.in_params[0],sizeof(intr.in_params));	
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
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=MenuRegs.id;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=rx.field.com.bit.com;
	tx.field.len=sizeof(intr.out_params);	
	memcpy(&tx.field.d[0],&intr.out_params[0],sizeof(intr.out_params));	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
	UPC_Time2=3;
}
//-----------------------------------------------------------------------------------
