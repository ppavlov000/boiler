#include "..\main.h"
//-----------------------------------------------------------------------------------
extern TBuff M_buff;
extern u8 M_buff_sign;
u8 step=0;
u8 new_step=0;
extern u8 M_SCH_Time;
extern u8 Transparent_Mode;
//extern s16 Temperature[3];
//extern s16 Preset;
//TExData *ExData=(TExData*)&M_rx.field.d[0];
TExSTATUS *Status;
//extern u8 Controller_Mode;
extern u8 New_Controller_Mode;
//extern TSeason Season;
extern u16 Fan_Speed;
extern s16 New_Preset;
extern u16 New_Fan_Speed;
//extern TErrors errors;
extern u8 scan_mode;
extern u8 scan_result;
extern u8 Current_ID;
//extern TPID pid;
u8 Branch_Number=0;
//-----------------------------------------------------------------------------------
void M_Get_Controller_Status(u8 id,u8 channel)
{
	if(id==0)return;
	M_Set_Channel(channel);
	M_tx.field.pre=0x55AA;		
	M_tx.field.com.bit.id=id;	
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_get_stat;
	M_tx.field.len=0;
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;
}
//-----------------------------------------------------------------------------------
void M_Get_Controller_IO(u8 id,u8 channel)
{
	if(id==0)return;
	M_Set_Channel(channel);
	M_tx.field.pre=0x55AA;	
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_get_io;
	M_tx.field.len=0;
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;
}
//-----------------------------------------------------------------------------------
void M_Get_Controller_PID(u8 pid_num,u8 id,u8 channel)
{
	if(id==0)return;	
	M_Set_Channel(channel);
	M_tx.field.pre=0x55AA;		
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_get_pid_0+pid_num;
	M_tx.field.len=0;
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;
}
//-----------------------------------------------------------------------------------
void M_Get_Controller_Errors(u8 id,u8 channel)
{
	if(id==0)return;
	M_Set_Channel(channel);
	M_tx.field.pre=0x55AA;	
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_get_errors;
	M_tx.field.len=0;
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;
}
//-----------------------------------------------------------------------------------
void M_Get_Controller_Time(u8 id,u8 channel)
{
	if(id==0)return;
	M_Set_Channel(channel);
	M_tx.field.pre=0x55AA;	
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_get_time;
	M_tx.field.len=0;
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;
//	BUZZ_Time=50;
}
//-----------------------------------------------------------------------------------
void M_Get_Controller_Time_Summ(u8 id,u8 channel)
{
	if(id==0)return;
	M_Set_Channel(channel);
	M_tx.field.pre=0x55AA;	
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_get_time_summ;
	M_tx.field.len=0;
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;
}
//-----------------------------------------------------------------------------------
void M_Get_Controller_Time_Wint(u8 id,u8 channel)
{
	if(id==0)return;
	M_Set_Channel(channel);
	M_tx.field.pre=0x55AA;	
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_get_time_wint;
	M_tx.field.len=0;
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;
}
//-----------------------------------------------------------------------------------
void M_Set_Controller_Errors(u8 id,u8 channel)
{
	M_Set_Channel(channel);
	M_tx.field.pre=0x55AA;	
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_set_errors;
	M_tx.field.len=sizeof(TErrors);
	memcpy(&M_tx.field.d[0],&errors,sizeof(TErrors));		
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;
}
//-----------------------------------------------------------------------------------
void M_Set_Controller_IO(u8 id,TIO *pio)
{
	M_Set_Channel(id);
	*(TIO*)&M_tx.field.d[0]=*pio;	
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_set_io;
	M_tx.field.len=sizeof(TIO);
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;		
}
//-----------------------------------------------------------------------------------
void M_Set_Controller_Status(u8 id,u8 channel)
{
	M_Set_Channel(channel);
	Status=(TExSTATUS*)&M_tx.field.d[8];	
//	Status->Controller_Mode=Controller_Mode;
	Status->Preset_Speed=Fan_Speed;
//	Status->Preset_Temperature=Preset;	
//	Status->Season=Season.season;
	M_tx.field.pre=0x55AA;	
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_set_stat;
	M_tx.field.len=8+sizeof(TExSTATUS);
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;	
}
//-----------------------------------------------------------------------------------
void M_Set_Controller_PID(u8 pid_num,u8 id, TPID *ppid)
{
	M_Set_Channel(id);
	memcpy(&M_tx.field.d[0],ppid,sizeof(TPID));				
	M_tx.field.pre=0x55AA;	
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_set_pid_0+pid_num;
	M_tx.field.len=sizeof(TPID);
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;
}
//-----------------------------------------------------------------------------------
void M_Set_Controller_Time(u8 id,u8 channel)
{
	M_Set_Channel(channel);
	memcpy(&M_tx.field.d[0],&MenuRegs.Time,sizeof(TTime));			
	M_tx.field.pre=0x55AA;	
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_set_time;
	M_tx.field.len=sizeof(TTime);
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;
}
//-----------------------------------------------------------------------------------
void M_Set_Controller_Time_Summ(u8 id,u8 channel)
{
	M_Set_Channel(channel);
//	memcpy(&M_tx.field.d[0],&mcu.Time_Summ,sizeof(TTime));	
	M_tx.field.pre=0x55AA;
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_set_time_summ;
	M_tx.field.len=sizeof(TTime);
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;
}
//-----------------------------------------------------------------------------------
void M_Set_Controller_Time_Wint(u8 id,u8 channel)
{
	M_Set_Channel(channel);
//	memcpy(&M_tx.field.d[0],&mcu.Time_Wint,sizeof(TTime));	
	M_tx.field.pre=0x55AA;	
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_set_time_wint;
	M_tx.field.len=sizeof(TTime);
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;
}
//-----------------------------------------------------------------------------------
void upc_Set_Controller_In_Params(u8 id,u8 addr,u8* value,u8 len)
{
//	ptr=rx.field.d[0];
//	len=rx.field.d[1];
	
	M_tx.field.d[0]=addr;
	M_tx.field.d[1]=len;	
	memcpy(&M_tx.field.d[2],value,len*2);	
	
	M_tx.field.pre=0x55AA;	
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_set_in_params;
	M_tx.field.len=len*2+2;
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;
}
//-----------------------------------------------------------------------------------
void upc_Get_Controller_Out_Params(u8 id,u8 address,u8 length)
{
//	if(id==0)return;
	M_Set_Channel(id);
	M_tx.field.d[0]=address;
	M_tx.field.d[1]=length;		
	M_tx.field.pre=0x55AA;	
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_get_out_params;
	M_tx.field.len=2;
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;
}
//-----------------------------------------------------------------------------------
void M_Save_Controller_Params(u8 id)
{
	M_Set_Channel(id);
	M_tx.field.pre=0x55AA;	
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_store_params;
	M_tx.field.len=0;
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;
}
//-----------------------------------------------------------------------------------
void M_Set_Manual_Mode(u8 id,u8 mode)
{
	M_tx.field.d[0]=mode;
		
	M_Set_Channel(id);
	M_tx.field.pre=0x55AA;	
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_set_manual;
	M_tx.field.len=1;
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;
}
//-----------------------------------------------------------------------------------
void M_Set_Season(u8 id,TSeason *season)
{
	memcpy(&M_tx.field.d[0],season,sizeof(TSeason));	
	M_Set_Channel(id);
	M_tx.field.pre=0x55AA;	
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_set_season;
	M_tx.field.len=sizeof(TSeason);
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;
}
//-----------------------------------------------------------------------------------
void M_Get_Season(u8 id)
{
	if(id==0)return;
	M_Set_Channel(id);
	M_tx.field.pre=0x55AA;	
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_get_season;
	M_tx.field.len=0;
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;
}
//-----------------------------------------------------------------------------------
void M_Set_Controller_Register(u8 id,void *reg_addr,u8 len)
{
	u16 addr=get_reg_addr(reg_addr);
	memcpy(&M_tx.field.d[0],&addr,2);	
	M_tx.field.d[2]=len;	
	memcpy(&M_tx.field.d[3],&reg_data[addr],len);
	M_Set_Channel(id);
	M_tx.field.pre=0x55AA;	
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_set_register;
	M_tx.field.len=len+3;	
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;	
}
//-----------------------------------------------------------------------------------
void M_Get_Controller_Register(u8 id,void *reg_addr,u8 len)
{
	u16 addr=get_reg_addr(reg_addr);
	if(id==0)return;
	memcpy(&M_tx.field.d[0],&addr,2);	
	M_tx.field.d[2]=len;	
	M_Set_Channel(id);
	M_tx.field.pre=0x55AA;	
	M_tx.field.com.bit.id=id;
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_get_register;
	M_tx.field.len=3;	
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;	
}
//-----------------------------------------------------------------------------------
void M_Get_Controller_Work(u8 id)
{
	if(id==0)return;
	M_tx.field.pre=0x55AA;		
	M_tx.field.com.bit.id=id;	
	M_tx.field.com.bit.req=1;
	if(id==0)M_tx.field.com.bit.req=0;
	M_tx.field.com.bit.com=com_get_work_rec;
	M_tx.field.len=0;
	M_tx.field.crc_data=upc_crc_data(&M_tx);
	M_tx.field.crc_head=upc_crc_head(&M_tx);
	M.txnew=1;
	M.txcount=0;
	M.status=st_sending;		
	M.rxnew=0;
	M.rxcount=0;		
	M.error=0;
	M.done=0;
}
//-----------------------------------------------------------------------------------
void Schedule_N0();
void Schedule_N2();
void Schedule_N3();
void Schedule_N4();
void Schedule_N5();
//void Schedule_N6();
void Schedule_N7();
//-----------------------------------------------------------------------------------
void M_Schedule()
{
	switch(Branch_Number)
	{
	case 0:Schedule_N0();break;
//	case 1:void Schedule_N1();break;
	case 2:Schedule_N2();break;
	case 3:Schedule_N3();break;
	case 4:Schedule_N4();break;
	case 5:Schedule_N5();break;
//	case 6:Schedule_N6();break;
	case 7:Schedule_N7();break;	
	}
}
//-----------------------------------------------------------------------------------
/*
void M_Schedule_old()
{
//	u16 i,tmp;
	M_state_machine();
	if((M.status==st_none)||(M.status==st_complete))
	{		
		if((M.error==0)&&(M.rxnew==1))
		{
			M.rxnew=0;
//			if(Transparent_Mode)
//			{
//				BUZZ_Time=50;
//				upc_S_return_transparent_packet();
//			}
//			else
			switch(M_rx.field.com.bit.com)
			{
				case com_get_time:		
//					Season=rx.field.data.st.Season;
					ft=*(TTime*)&M_rx.field.d[0];	
				break;
				case com_get_stat:		
//					Season=rx.field.data.st.Season;
					Status=(TExSTATUS*)&M_rx.field.d[30];	
					ft=Status->ft;
					if(Button_no_update_time==0){
						Controller_Mode=Status->Controller_Mode;
						Fan_Speed=Status->Preset_Speed;
						Preset=Status->Preset_Temperature;	
					}
				break;
				case com_get_errors:		
					errors=*(TErrors*)&M_rx.field.d[0];	
				break;									
				case com_get_io:		
					Temperature[0]=ExData->io.analog[ExData->io.num_ao+0];
					Temperature[1]=ExData->io.analog[ExData->io.num_ao+1];
					Temperature[2]=ExData->io.analog[ExData->io.num_ao+2];
					Fan_Speed=ExData->io.analog[0];
//					Tkanal=rx.field.data.io.analog[rx.field.data.io.num_ao+1];
//					Tvnesh=rx.field.data.io.analog[rx.field.data.io.num_ao+2];
//					aout[0]=rx.field.data.io.analog[0];
//					aout[1]=rx.field.data.io.analog[1];						
				break;
				case com_get_out_params:		
	//				Time_Wint=rx.field.data.Time;								
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
			switch(step)
			{
				case 0:
					step++;
					M_Get_Controller_Status(Current_ID,1);
					//upc_Get_Controller_Time(1,1);
					M_SCH_Time=10;
				break;				
				case 1:
					step++;
					M_Get_Controller_IO(Current_ID,1);
					M_SCH_Time=10;					
				break;
				case 2:
					step++;
					M_Get_Controller_Errors(Current_ID,1);
//					upc_Get_Controller_Out_Params(1,1);
//					M_Set_Controller_Status(1,1);
					step=0;					
					M_SCH_Time=10;					
				break;
				// Update status information
				case 20:
					step++;
					M_Get_Controller_Status(Current_ID,1);
					//upc_Get_Controller_Time(1,1);
					M_SCH_Time=10;
				break;								
				case 21:
					step++;
//					upc_Get_Controller_Out_Params(1,1);
					M_Set_Controller_Status(Current_ID,1);					
					step=0;					
					M_SCH_Time=10;	
				break;
				case 22:
					step++;
					memset(&errors,0,sizeof(TErrors));
					M_Set_Controller_Errors(Current_ID,1);					
					step=0;					
					M_SCH_Time=10;	
				break;
				//

				
			}
		}
		
	}
	
}
*/
//-----------------------------------------------------------------------------------
