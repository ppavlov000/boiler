#include "..\main.h"
//-----------------------------------------------------------------------------------
void upc_Get_Controller_Status(u8 id,u8 channel)
{
	upc_Set_Channel(channel);
	tx.field.pre=0x55AA;		
	tx.field.com.bit.id=id;
	tx.field.com.bit.req=1;
	tx.field.com.bit.com=com_get_stat;
	tx.field.len=0;
	tx.field.crc=upc_crc(&tx);
	upc.txnew=1;
	upc.txcount=0;
	upc.status=st_sending;		
	upc.rxnew=0;
	upc.rxcount=0;		
	upc.error=0;
	upc.done=0;
}
//-----------------------------------------------------------------------------------
void upc_Get_Controller_IO(u8 id,u8 channel)
{
	upc_Set_Channel(channel);
	tx.field.pre=0x55AA;	
	tx.field.com.bit.id=id;
	tx.field.com.bit.req=1;
	tx.field.com.bit.com=com_get_io;
	tx.field.len=0;
	tx.field.crc=upc_crc(&tx);
	upc.txnew=1;
	upc.txcount=0;
	upc.status=st_sending;		
	upc.rxnew=0;
	upc.rxcount=0;		
	upc.error=0;
	upc.done=0;
}
//-----------------------------------------------------------------------------------
void upc_Get_Controller_PID(u8 pid_num,u8 id,u8 channel)
{
	upc_Set_Channel(channel);
	tx.field.pre=0x55AA;		
	tx.field.com.bit.id=id;
	tx.field.com.bit.req=1;
	tx.field.com.bit.com=com_get_pid_0+pid_num;
	tx.field.len=0;
	tx.field.crc=upc_crc(&tx);
	upc.txnew=1;
	upc.txcount=0;
	upc.status=st_sending;		
	upc.rxnew=0;
	upc.rxcount=0;		
	upc.error=0;
	upc.done=0;
}
//-----------------------------------------------------------------------------------
void upc_Get_Controller_Errors(u8 id,u8 channel)
{
	upc_Set_Channel(channel);
	tx.field.pre=0x55AA;	
	tx.field.com.bit.id=id;
	tx.field.com.bit.req=1;
	tx.field.com.bit.com=com_get_errors;
	tx.field.len=0;
	tx.field.crc=upc_crc(&tx);
	upc.txnew=1;
	upc.txcount=0;
	upc.status=st_sending;		
	upc.rxnew=0;
	upc.rxcount=0;		
	upc.error=0;
	upc.done=0;
}
//-----------------------------------------------------------------------------------
void upc_Get_Controller_Time(u8 id,u8 channel)
{
	upc_Set_Channel(channel);
	tx.field.pre=0x55AA;	
	tx.field.com.bit.id=id;
	tx.field.com.bit.req=1;
	tx.field.com.bit.com=com_get_time;
	tx.field.len=0;
	tx.field.crc=upc_crc(&tx);
	upc.txnew=1;
	upc.txcount=0;
	upc.status=st_sending;		
	upc.rxnew=0;
	upc.rxcount=0;		
	upc.error=0;
	upc.done=0;
}
//-----------------------------------------------------------------------------------
void upc_Get_Controller_Time_Summ(u8 id,u8 channel)
{
	upc_Set_Channel(channel);
	tx.field.pre=0x55AA;	
	tx.field.com.bit.id=id;
	tx.field.com.bit.req=1;
	tx.field.com.bit.com=com_get_time_summ;
	tx.field.len=0;
	tx.field.crc=upc_crc(&tx);
	upc.txnew=1;
	upc.txcount=0;
	upc.status=st_sending;		
	upc.rxnew=0;
	upc.rxcount=0;		
	upc.error=0;
	upc.done=0;
}
//-----------------------------------------------------------------------------------
void upc_Get_Controller_Time_Wint(u8 id,u8 channel)
{
	upc_Set_Channel(channel);
	tx.field.pre=0x55AA;	
	tx.field.com.bit.id=id;
	tx.field.com.bit.req=1;
	tx.field.com.bit.com=com_get_time_wint;
	tx.field.len=0;
	tx.field.crc=upc_crc(&tx);
	upc.txnew=1;
	upc.txcount=0;
	upc.status=st_sending;		
	upc.rxnew=0;
	upc.rxcount=0;		
	upc.error=0;
	upc.done=0;
}
//-----------------------------------------------------------------------------------
void upc_Set_Controller_Errors(u8 id,u8 channel)
{
	upc_Set_Channel(channel);
	tx.field.pre=0x55AA;	
	tx.field.com.bit.id=id;
	tx.field.com.bit.req=1;
	tx.field.com.bit.com=com_set_errors;
	tx.field.len=sizeof(TErrors);
//	memcpy(&tx.field.d[0],&mcu.errors,sizeof(TErrors));		
	tx.field.crc=upc_crc(&tx);
	upc.txnew=1;
	upc.txcount=0;
	upc.status=st_sending;		
	upc.rxnew=0;
	upc.rxcount=0;		
	upc.error=0;
	upc.done=0;
}
//-----------------------------------------------------------------------------------
void upc_Set_Controller_IO(u8 id,u8 channel)
{
	upc_Set_Channel(channel);
}
//-----------------------------------------------------------------------------------
void upc_Set_Controller_Status(u8 id,u8 channel)
{
	upc_Set_Channel(channel);
// 	tx.field.d[1]=mcu.Season;
// 	tx.field.d[0]=0;	
//	memcpy(&tx.field.d[2],&mcu.Time,sizeof(mcu.Time));	
//	tx.field.d[2+sizeof(mcu.Time)]=mcu.Auto_Manual;		
	tx.field.pre=0x55AA;	
	tx.field.com.bit.id=id;
	tx.field.com.bit.req=1;
	tx.field.com.bit.com=com_set_stat;
	tx.field.len=sizeof(TExSTATUS);
	tx.field.crc=upc_crc(&tx);
	upc.txnew=1;
	upc.txcount=0;
	upc.status=st_sending;		
	upc.rxnew=0;
	upc.rxcount=0;		
	upc.error=0;
	upc.done=0;	
}
//-----------------------------------------------------------------------------------
void upc_Set_Controller_PID(u8 pid_num,u8 id,u8 channel)
{
	upc_Set_Channel(channel);
//	memcpy(&tx.field.d[0],&mcu.pid[pid_num],sizeof(TExPID));				
	tx.field.pre=0x55AA;	
	tx.field.com.bit.id=id;
	tx.field.com.bit.req=1;
	tx.field.com.bit.com=com_set_pid_0+pid_num;
	tx.field.len=sizeof(TExPID);
	tx.field.crc=upc_crc(&tx);
	upc.txnew=1;
	upc.txcount=0;
	upc.status=st_sending;		
	upc.rxnew=0;
	upc.rxcount=0;		
	upc.error=0;
	upc.done=0;
}
//-----------------------------------------------------------------------------------
void upc_Set_Controller_Time(u8 id,u8 channel)
{
	upc_Set_Channel(channel);
//	memcpy(&tx.field.d[0],&mcu.Time,sizeof(TTime));			
	tx.field.pre=0x55AA;	
	tx.field.com.bit.id=id;
	tx.field.com.bit.req=1;
	tx.field.com.bit.com=com_set_time;
	tx.field.len=sizeof(TTime);
	tx.field.crc=upc_crc(&tx);
	upc.txnew=1;
	upc.txcount=0;
	upc.status=st_sending;		
	upc.rxnew=0;
	upc.rxcount=0;		
	upc.error=0;
	upc.done=0;
}
//-----------------------------------------------------------------------------------
void upc_Set_Controller_Time_Summ(u8 id,u8 channel)
{
	upc_Set_Channel(channel);
//	memcpy(&tx.field.d[0],&mcu.Time_Summ,sizeof(TTime));	
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=id;
	tx.field.com.bit.req=1;
	tx.field.com.bit.com=com_set_time_summ;
	tx.field.len=sizeof(TTime);
	tx.field.crc=upc_crc(&tx);
	upc.txnew=1;
	upc.txcount=0;
	upc.status=st_sending;		
	upc.rxnew=0;
	upc.rxcount=0;		
	upc.error=0;
	upc.done=0;
}
//-----------------------------------------------------------------------------------
void upc_Set_Controller_Time_Wint(u8 id,u8 channel)
{
	upc_Set_Channel(channel);
//	memcpy(&tx.field.d[0],&mcu.Time_Wint,sizeof(TTime));	
	tx.field.pre=0x55AA;	
	tx.field.com.bit.id=id;
	tx.field.com.bit.req=1;
	tx.field.com.bit.com=com_set_time_wint;
	tx.field.len=sizeof(TTime);
	tx.field.crc=upc_crc(&tx);
	upc.txnew=1;
	upc.txcount=0;
	upc.status=st_sending;		
	upc.rxnew=0;
	upc.rxcount=0;		
	upc.error=0;
	upc.done=0;
}
//-----------------------------------------------------------------------------------
void upc_Set_Controller_In_Params(u8 id,u8 channel)
{
	upc_Set_Channel(channel);
//	memcpy(&tx.field.d[0],&mcu.Parameters[0],sizeof(mcu.Parameters));	
	tx.field.pre=0x55AA;	
	tx.field.com.bit.id=id;
	tx.field.com.bit.req=1;
	tx.field.com.bit.com=com_set_in_params;
	tx.field.len=60;
	tx.field.crc=upc_crc(&tx);
	upc.txnew=1;
	upc.txcount=0;
	upc.status=st_sending;		
	upc.rxnew=0;
	upc.rxcount=0;		
	upc.error=0;
	upc.done=0;
}
//-----------------------------------------------------------------------------------
void upc_Set_Controller_Out_Params(u8 id,u8 channel)
{
	upc_Set_Channel(channel);
//	memcpy(&tx.field.d[0],&mcu.Parameters[0],sizeof(mcu.Parameters));	
	tx.field.pre=0x55AA;	
	tx.field.com.bit.id=id;
	tx.field.com.bit.req=1;
	tx.field.com.bit.com=com_set_out_params;
	tx.field.len=60;
	tx.field.crc=upc_crc(&tx);
	upc.txnew=1;
	upc.txcount=0;
	upc.status=st_sending;		
	upc.rxnew=0;
	upc.rxcount=0;		
	upc.error=0;
	upc.done=0;
}
//-----------------------------------------------------------------------------------
void upc_Get_Controller_In_Params(u8 id,u8 channel)
{
	upc_Set_Channel(channel);
//	memcpy(&tx.field.d[0],&mcu.Parameters[0],sizeof(mcu.Parameters));	
	tx.field.pre=0x55AA;	
	tx.field.com.bit.id=id;
	tx.field.com.bit.req=1;
	tx.field.com.bit.com=com_get_in_params;
	tx.field.len=0;
	tx.field.crc=upc_crc(&tx);
	upc.txnew=1;
	upc.txcount=0;
	upc.status=st_sending;		
	upc.rxnew=0;
	upc.rxcount=0;		
	upc.error=0;
	upc.done=0;
}
//-----------------------------------------------------------------------------------
void upc_Get_Controller_Out_Params(u8 id,u8 channel)
{
	upc_Set_Channel(channel);
//	memcpy(&tx.field.d[0],&mcu.Parameters[0],sizeof(mcu.Parameters));	
	tx.field.pre=0x55AA;	
	tx.field.com.bit.id=id;
	tx.field.com.bit.req=1;
	tx.field.com.bit.com=com_get_out_params;
	tx.field.len=0;
	tx.field.crc=upc_crc(&tx);
	upc.txnew=1;
	upc.txcount=0;
	upc.status=st_sending;		
	upc.rxnew=0;
	upc.rxcount=0;		
	upc.error=0;
	upc.done=0;
}
//-----------------------------------------------------------------------------------
