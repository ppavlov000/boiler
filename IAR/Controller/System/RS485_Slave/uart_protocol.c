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
			return;
		}
	if((upc.rxcount)>(rx.field.len+PACKET_HEADER_LEN-1))	
	{

		upc.rxcount=0;	
#ifdef _TEST_BAD_COMMUNICATION		
		//  !!!!!!!!!!!! TEsting lost packets !!!!!!!!!!!!!!!!!!!!!!
		if(bad_counter==4)
		{
			rx.field.crc=0;
			bad_counter=0;
		}
		bad_counter++;
#endif		
		if(upc_crc_data(&rx)==rx.field.crc_data)
		{
#ifdef	COMMUNICATION_MESSAGES
			_sprintf(outtxt,"\n\r Good CRC");
#endif			
//			if((rx.field.com.bit.id==MenuRegs.id)||(rx.field.com.bit.id==0))
			if((rx.field.com.bit.id==MenuRegs.id))			
			{
				upc.rxnew=1;		
	//			mem_dump(rx.field.d,10);
				switch(rx.field.com.bit.com)
				{
					case com_none:
						__sprintf(outtxt,"\n\r Empty packet received");
					break;
					case com_get_stat:
	//					if(rx.field.com.bit.id==m_Address)
						upc_answer_sys();	
					break;
					case com_get_io:
	//					if(rx.field.com.bit.id==m_Address)
						upc_answer_io();	
					break;
					case com_get_pid_0:
	//					if(rx.field.com.bit.id==m_Address)
						upc_answer_pid(0);	
					break;		
					case com_get_pid_1:
	//					if(rx.field.com.bit.id==m_Address)
						upc_answer_pid(1);	
					break;	
					case com_get_pid_2:
	//					if(rx.field.com.bit.id==m_Address)
						upc_answer_pid(2);	
					break;	
					case com_get_pid_3:
	//					if(rx.field.com.bit.id==m_Address)
						upc_answer_pid(3);	
					break;		
					case com_get_errors:
	//					if(rx.field.com.bit.id==m_Address)
						upc_answer_errors();
					break;		
	
					case com_set_stat:
	//					if(rx.field.com.bit.id==m_Address)
						upc_set_sys();	
					break;
					case com_set_io:
	//					if(rx.field.com.bit.id==m_Address)
						upc_set_io();	
					break;
					case com_set_pid_0:
	//					if(rx.field.com.bit.id==m_Address)
						upc_set_pid(0);	
					break;		
					case com_set_pid_1:
	//					if(rx.field.com.bit.id==m_Address)
						upc_set_pid(1);	
					break;	
					case com_set_pid_2:
	//					if(rx.field.com.bit.id==m_Address)
						upc_set_pid(2);	
					break;	
					case com_set_pid_3:
	//					if(rx.field.com.bit.id==m_Address)
						upc_set_pid(3);	
					break;		
					case com_set_errors:
	//					if(rx.field.com.bit.id==m_Address)
						upc_set_errors();
					break;		
					// Time			
					case com_get_time:
	//					if(rx.field.com.bit.id==m_Address)
						upc_answer_time();	
					break;	
					case com_get_time_summ:
	//					if(rx.field.com.bit.id==m_Address)
						upc_answer_time_summ();	
					break;		
					case com_get_time_wint:
	//					if(rx.field.com.bit.id==m_Address)
						upc_answer_time_wint();	
					break;		
					case com_set_time:
	//					if(rx.field.com.bit.id==m_Address)
						upc_set_time();	
					break;	
					case com_set_time_summ:
	//					if(rx.field.com.bit.id==m_Address)
						upc_set_time_summ();	
					break;		
					case com_set_time_wint:
	//					if(rx.field.com.bit.id==m_Address)
						upc_set_time_wint();		
					break;		
					case com_set_in_params:
						upc_set_in_parameters();		
					break;				
					case com_set_out_params:
						upc_set_out_parameters();		
					break;				
					case com_get_in_params:
						upc_answer_in_parameters();		
					break;				
					case com_get_out_params:
						upc_answer_out_parameters();		
					break;				
					default:				
					break;
	
				}
			}
		}
		else
		{
#ifdef	COMMUNICATION_MESSAGES
			_sprintf(outtxt,"\n\r Bad crc");
#endif				
		}
	}
//	rx_mode(); lc!!!
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
