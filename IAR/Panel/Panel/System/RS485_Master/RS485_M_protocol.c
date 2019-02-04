//-----------------------------------------------------------------------------------
#include "..\main.h"
#include "inavr.h"
#include <iom128.h>
//-----------------------------------------------------------------------------------
#define M_BAUND				38400
//#define MAX_ANSWER_DELAY	20	// ms UPC_Time
//-----------------------------------------------------------------------------------
u8 M_rxd;
TBuff M_rx,M_tx;

TBuff M_buff;
u8 M_buff_sign=0;
u8 Transparent_Mode=0;

TMState M;
TMHistory M_history;
u32 LcMaxAnswerDelay;
u8 attempts;
extern u16 M_Time;
//TExBuffer ExBuff;
//-----------------------------------------------------------------------------------
void upc_M_transparent_packet();
//-----------------------------------------------------------------------------------
void Delay_mks(u16 val)// value in 10mks
{
	u8 i;
	while(val!=0)
	{
		for(i=0;i<5;i++)__no_operation();
		val--;
	}
}
//-----------------------------------------------------------------------------------	
#pragma vector=USART0_RXC_vect
__interrupt void M_RX_IRQ()
{
	M_RXHandler();
}
//-----------------------------------------------------------------------------------	
void M_tx_byte(u8 byte)
{
	UDR0=byte;
}
//-----------------------------------------------------------------------------------
u8 M_rx_byte()
{
	u8 byte;
	byte=UDR0;
	return byte;
}
//-----------------------------------------------------------------------------------
u8 M_check_tx()
{
	if(UCSR0A & (1<<TXC0))return 1;
	else return 0;
}
//-----------------------------------------------------------------------------------
void M_clear_tx_flag()
{
	UCSR0A|=(1<<TXC0);
}
//-----------------------------------------------------------------------------------
void M_tx_mode()
{
	M_port|=M_pin_mode;
	Delay_mks(2);
}
//-----------------------------------------------------------------------------------
void M_rx_mode()
{
	M_port&=~M_pin_mode;
}
//-----------------------------------------------------------------------------------
void M_Set_Channel(u8 channel)
{
//	u8 tmp=0;
	M.channel=channel;
}
//-----------------------------------------------------------------------------------
void M_hardware_init(u32 baund)
{
	u16 rate=0;
	switch(baund)
	{
		case 115200: rate=5; break;
		case 57600: rate=11; break;
		case 38400: rate=17; break;
		case 28800: rate=23; break;
		case 19200: rate=35; break;
		case 14400: rate=47; break;		
		case 9600: rate=71; break;
		case 4800: rate=143; break;
		case 2400: rate=287; break;
	}
	M_port_dir|=(M_pin_mode);
	M_port&=~(M_pin_mode);
	
	M_tx_mode();
	UBRR0H = (unsigned char)(rate>>8);
	UBRR0L = (unsigned char)rate;
	/* Enable receiver and transmitter */
	UCSR0B =(1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
	UDR0=' ';	
}
//---------------------------------------------------------------------------------
void M_init()
{
	u8 i;
	M_hardware_init(M_BAUND);
	memset((void *)&M_rx, 0, sizeof(M_rx));
	memset((void *)&M_tx, 0, sizeof(M_tx));	
	memset((void *)&M, 0, sizeof(M));		
	for(i=0;i<CHANNELS_NUM;i++)
		M.channel_state[i]=50;
	M.channel=0;

	//M_set_max_answer_delay(0);
}
//-----------------------------------------------------------------------------------
void M_buff_init()
{
	memset((void *)&M_rx, 0, sizeof(M_rx));
	memset((void *)&M_tx, 0, sizeof(M_tx));	
}
//-----------------------------------------------------------------------------------
void M_handler()
{
//	u16 i,tmp;
	M_state_machine();
/*	if(M2_Time==0)
	{		
		M2_Time=10;	
		if(ExBuff.head.status==st_ToSend)
		{
			if((M.status==st_none)||(M.status==st_complete))
			{						
				M_Set_Channel(ExBuff.head.channel);
				switch(ExBuff.head.command)
				{
					case tx_stat:M_Set_Controller_Status();break;
					case tx_io:M_Set_Controller_IO();break;
					case tx_pid0:M_Set_Controller_PID(0);break;
					case tx_pid1:M_Set_Controller_PID(1);break;
					case tx_pid2:M_Set_Controller_PID(2);break;
					case tx_pid3:M_Set_Controller_PID(3);break;	
					case tx_errors:M_Set_Controller_Errors();break;		
							
					case tx_time:M_Set_Controller_Time();break;	
					case tx_time_summ:M_Set_Controller_Time_Summ();break;	
					case tx_time_wint:M_Set_Controller_Time_Wint();break;
					case tx_params:
							mcu.Parameters[0]=mcu.Zaslonka[0];
							mcu.Parameters[1]=mcu.Zaslonka[1];
							mcu.Parameters[2]=mcu.Zaslonka_Mode;
							M_Set_Controller_Params();
					break;

					case com_get_stat:M_Get_Controller_Status();break;
					case rx_io:M_Get_Controller_IO();break;
					case rx_pid0:M_Get_Controller_PID(0);break;
					case rx_pid1:M_Get_Controller_PID(1);break;
					case rx_pid2:M_Get_Controller_PID(2);break;
					case rx_pid3:M_Get_Controller_PID(3);break;	
					case rx_errors:M_Get_Controller_Errors();break;																																	
										
					case rx_time:M_Get_Controller_Time();break;	
					case rx_time_summ:M_Get_Controller_Time_Summ();break;	
					case rx_time_wint:M_Get_Controller_Time_Wint();break;
				}
			}
		}
	}
*/	
}
//-----------------------------------------------------------------------------------
void M_RXHandler()
{
	M_rxd=M_rx_byte();
//	ByteToStr(outtxt,&M_rxd,1);
//	sprintf(outtxt," ");
//	return;
//	if(M.rxnew==1)return;	// Exit if previos not handled
	switch(M.rxcount)
	{
		case 0:
			if(M_rxd!=PREAMBULA_LOW)
			{
				M.rxcount=0;
				return;
			}
		break;
		case 1:
			if(M_rxd!=PREAMBULA_HIGH)
			{
				M.rxcount=0;
				return;
			}
		break; 		
	}
	M_rx.data.d[M.rxcount]=M_rxd;
	M.rxcount++;	
	M_Time =  MAX_ANSWER_DELAY;
	if((M.rxcount)>(M_rx.field.len+PACKET_HEADER_LEN-1))
	{
		M.rxnew=1;
//		mem_dump(&M_rx.field.d[0],16);
	}
}
//-----------------------------------------------------------------------------------
void M_TXHandler()
{
	// Check M_tx
	if(M_check_tx())
	{
		if(M.done==0)
		{
			M_clear_tx_flag();
			M_tx_byte(M_tx.data.d[M.txcount]);
			M.txcount++;			
			if((M.txcount)>(M_tx.field.len+PACKET_HEADER_LEN-1))
			{
				M.done=1;
//				sprintf(outtxt,"\n\r");
//				mem_dump(&M_tx.data.d[0],16);
			}
			else
				M.done=0;
		}
		else
			M.txnew=0;
	}
}
//-----------------------------------------------------------------------------------
void M_state_machine()
{
	u16 tmp;
//	u8 i;
	switch(M.status)
	{
		case st_none:
			attempts=0;
		break;
		case st_complete:
			attempts=0;
		break;		
		case st_sending:
			M_tx_mode();
			M_TXHandler();	
			if(M.txnew==0)
			{
				M_rx_mode(); // lc
				if(M_tx.field.com.bit.req)
				{
					M.status=st_wait_answer;	
					M_Time =MAX_ANSWER_DELAY;
//					if(M_history.packets[M.channel]<0xffff)
					M_history.packets[M.channel]++;					
					if(M_history.packets[M.channel]>=100)
					{
						M_history.lost[M.channel]=(M_history.timeout[M.channel]);
						M_history.packets[M.channel]=0;
						M_history.timeout[M.channel]=0;
					}
				}
				else
				{
					M.status=st_none;
					M.txnew=0;
					M.txcount=0;
					M.rxnew=0;
					M.rxcount=0;						
				}			
			}			
			M.error=er_none;			
		break;
		case st_wait_answer:
			M_rx_mode();					
			if(M.rxnew==1)
				if(M_rx.field.com.bit.id==M_tx.field.com.bit.id)
				{					
					M.status=st_answer_process;
				}
			if(M_Time==0)
			{
				// History
//				if(M_history.timeout[M.channel]<0xffff)
//				M_history.timeout[M.channel]++;
				M.channel_state[M.channel]++;
				if(M.channel_state[M.channel]>50)M.channel_state[M.channel]=50;
				M_history.timeout[M.channel]++;				
				if(attempts<3)
				{
					attempts++;
					M.txnew=1;
					M.txcount=0;
					M.status=st_sending;		
					M.rxnew=0;
					M.rxcount=0;		
					M.error=0;
					M.done=0;					
				}
				else
				
				{
					M.status=st_none;
					M.error=er_no_answer;
					M.txnew=0;
					M.txcount=0;
					M.rxnew=0;
					M.rxcount=0;		
					M_history.timeout[M.channel]++;
				}
			}
		break;
		case st_answer_process:
//			sprintf(outtxt,"\n\r Packet received ");
//			M.rxnew=0;
//			M.status=st_complete;
			M.status=st_none;			
			M.channel_state[M.channel]=0;
			// CRC calculation
			tmp=upc_crc_head(&M_rx);
			if(tmp!=M_rx.field.crc_head)
			{
				// History
//				if(M_history.bad_crc[M.channel]<0xffff)
//					M_history.bad_crc[M.channel]++;			
//				WordToStr(outtxt,&tmp,1);
//				WordToStr(outtxt,&M_rx.field.crc,1);
				M.error=er_bad_crc;
			}
			else
			{
				if(M_rx.field.com.bit.id!=M_tx.field.com.bit.id)
				{
					M.error=er_bad_id;
				}
				else
				{
					M.error=er_none;
					
				}
			}
		break;
	}
}
//-----------------------------------------------------------------------------------
