//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
#define MAX_ANSWER_DELAY	100	// ms UPC_Time
#define UPC_RATE 38400
//#define COMMUNICATION_MESSAGES
//u8 m_Address=0;
//-----------------------------------------------------------------------------------
u8 upc_rxd;
TBuff rx,tx;
TUpcState upc;
u16 crc;
vu8 bad_counter=0;
extern  u32 HW;
u32 HW_in=0;
//-----------------------------------------------------------------------------------
void upc_answer_store_parameters();
void upc_answer_set_id();
void upc_answer_fan(u8 fan_num);
void upc_answer_kotel(u8 kot_num);
void upc_answer_pid(u8 pid_num);
void upc_answer_packet_timeout();

void upc_set_pid();
void upc_set_fan();
void upc_set_kotel();
void upc_answer_kotel_params(u8 kot_num);
void upc_set_kotel_params();
void upc_answer_errors();
//-----------------------------------------------------------------------------------
// RS485 section
//-----------------------------------------------------------------------------------
void upc_init()
{
	upc_hardware_init(UPC_RATE);
	memset((void *)&rx, 0, sizeof(rx));
	memset((void *)&tx, 0, sizeof(tx));	
	memset((void *)&upc, 0, sizeof(upc));	
	rx_mode();	
}
//-----------------------------------------------------------------------------------
u8 cs_calculate(u8* buff,u8 len)
{
	u8 i,cs=0;
	for(i=0;i<len;i++)
	{
		cs+=*buff;
		buff++;
	}
	return cs;
}
//-----------------------------------------------------------------------------------
void mem_dump(u8 *buff,u8 len)
{
	u8 i;
//	_sprintf(outtxt,"\n\r");
	for(i=0;i<len;i++)
	{
		ByteToStr(outtxt,buff,1);
		buff++;
		__sprintf(outtxt," ");		
	}
}
//-----------------------------------------------------------------------------------
void upc_buff_init()
{
	memset((void *)&rx, 0, sizeof(rx));
	memset((void *)&tx, 0, sizeof(tx));	
}
//-----------------------------------------------------------------------------------
void upc_RXHandler()
{	
//	u8 ltmp;
//	u8 i,old_stat;
	upc_rxd=upc_rx_byte();
//	UDR0=upc_rxd;	
	switch(upc.rxcount)
	{
		case 0:
			if(upc_rxd!=PREAMBULA_LOW)
			{
				upc.rxcount=0;	
				return;
			}
		break;
		case 1:
			if(upc_rxd!=PREAMBULA_HIGH)
			{
				upc.rxcount=0;	
				return;
			}
		break;		
	}
	rx.data.d[upc.rxcount]=upc_rxd;
	upc.rxcount++;		
	if((upc.rxcount)==(PACKET_HEADER_LEN))	
		if(upc_crc_head(&rx)!=rx.field.crc_head)
		{
			upc.rxcount=0;	
//			LED_Time=50;
			return;
		}
	if((upc.rxcount)>(rx.field.len+PACKET_HEADER_LEN-1))	
	{

		upc.rxcount=0;	
		if(upc_crc_data(&rx)==rx.field.crc_data)
		{
//			if((rx.field.com.bit.id==ID)||(rx.field.com.bit.id==0))
//			if((rx.field.com.bit.id==ID))			
			{
				upc.rxnew=1;		
	//			mem_dump(rx.field.d,10);
				switch(rx.field.com.bit.com)
				{
					case com_reqt_status:
						if(rx.field.com.bit.id==ID)
							upc_answer_sys();	
					break;
					case com_get_stat:
						if(rx.field.com.bit.id==ID)
							upc_answer_sys();	
					break;
					case com_reqt_reset:
						if((rx.field.com.bit.id==ID)||(rx.field.com.bit.id==0))
							reset();
					break;					
					case com_reqt_res_hw:
						HW_in=*(u32*)&rx.field.d[0];
						if(HW==HW_in)
							reset();
					break;					
					
					case com_get_io:
						if(rx.field.com.bit.id==ID)
							upc_answer_io();	
					break;

					case com_get_pid:
						if(rx.field.com.bit.id==ID)						
							upc_answer_pid(rx.field.d[0]);	
					break;		
					
					case com_get_fan:
						if(rx.field.com.bit.id==ID)						
							upc_answer_fan(rx.field.d[0]);	
					break;		

					case com_get_kotel:
						if(rx.field.com.bit.id==ID)						
							upc_answer_kotel(rx.field.d[0]);	
					break;		
					case com_get_kotel_params:
						if(rx.field.com.bit.id==ID)						
							upc_answer_kotel_params(rx.field.d[0]);	
					break;		
					
					case com_get_errors:
						if(rx.field.com.bit.id==ID)
							upc_answer_errors();
					break;		

					case com_set_stat:
						if((rx.field.com.bit.id==ID)||(rx.field.com.bit.id==0))
							upc_set_sys();	
					break;
					case com_set_io:
						if((rx.field.com.bit.id==ID)||(rx.field.com.bit.id==0))
							upc_set_io();	
					break;

					case com_set_pid:
						if((rx.field.com.bit.id==ID)||(rx.field.com.bit.id==0))
							upc_set_pid();	
					break;		
					
					case com_set_fan:
						if((rx.field.com.bit.id==ID)||(rx.field.com.bit.id==0))
							upc_set_fan();	
					break;	
					
					case com_set_kotel:
						if((rx.field.com.bit.id==ID)||(rx.field.com.bit.id==0))
							upc_set_kotel();	
					break;	
					
					case com_set_kotel_params:
						if((rx.field.com.bit.id==ID)||(rx.field.com.bit.id==0))
							upc_set_kotel_params();	
					break;	

					// Time			
					case com_get_time:
						if(rx.field.com.bit.id==ID)
							upc_answer_time();	
					break;	

					case com_set_time:
						if((rx.field.com.bit.id==ID)||(rx.field.com.bit.id==0))
							upc_set_time();	
					break;	

					case com_set_in_params:
						if((rx.field.com.bit.id==ID)||(rx.field.com.bit.id==0))
							upc_set_in_parameters();		
					break;				
					case com_get_out_params:
						if(rx.field.com.bit.id==ID)
							upc_answer_out_parameters();		
					break;				
					case com_store_params:
						if((rx.field.com.bit.id==ID)||(rx.field.com.bit.id==0))
							upc_answer_store_parameters();		
					break;				
					case com_set_manual:
						if((rx.field.com.bit.id==ID)||(rx.field.com.bit.id==0))
							upc_answer_set_manual();	
					break;
/*
					case com_set_season:
						if((rx.field.com.bit.id==ID)||(rx.field.com.bit.id==0))
							upc_answer_set_season();		
					case com_get_season:
						if((rx.field.com.bit.id==ID)||(rx.field.com.bit.id==0))
							upc_answer_get_season();	
*/
					case com_set_register:
						if((rx.field.com.bit.id==ID)||(rx.field.com.bit.id==0))
							upc_answer_set_register();		
					case com_get_register:
						if((rx.field.com.bit.id==ID)||(rx.field.com.bit.id==0))
							upc_answer_get_register();		
					break;				
					case com_set_id:
						if((rx.field.com.bit.id==ID))
							upc_answer_set_id();		
					break;				
					default:				
					break;
	
				}
			}
		}
		else
		{
			// BAD CRC
			__sprintf(outtxt,"\n\r Bad CRC!");
//			LED_Time=50;
		}
	}
}
//-----------------------------------------------------------------------------------
void upc_TXHandler()
{
	if(UPC_Time2!=0)return;
	// Check tx	
	if(upc.done==0)
//	while(upc.done!=0)
	{
		if(upc_check_tx())
		{		
			tx_mode();	
			upc_clear_tx_flag();		
			upc_tx_byte(tx.data.d[upc.txcount]);
//			UPC_Time2=1;
			upc.txcount++;
			if((upc.txcount)>(tx.field.len+PACKET_HEADER_LEN-1))
			{
				upc.done=1;
//					_sprintf(outtxt," ch");											
			}
		}
	}
	else
	{
		upc.txnew=0;
		rx_mode();		
	}	
}
//-----------------------------------------------------------------------------------
u16 upc_crc_data(TBuff *buff)
{
	u16 crc;
	u8 p;
	InitCRC(&crc);
	for(p=0;p<(buff->field.len);p++)	
	{
		CalcCRC(&(buff->field.d[p]),1,&crc);
	}
	EndCRC(&crc);	
	return crc;
}
//-----------------------------------------------------------------------------------
u16 upc_crc_head(TBuff *buff)
{
	u16 crc;
	u8 p;
	InitCRC(&crc);
	for(p=0;p<(PACKET_HEADER_LEN-2);p++)	
	{
		CalcCRC(&(buff->data.d[p]),1,&crc);
	}
	EndCRC(&crc);	
	return crc;
}
//-----------------------------------------------------------------------------------
