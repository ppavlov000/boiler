//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
#define MAX_ANSWER_DELAY	20	//70 // ms UPC_Time
#define UPC_BAUND	38400
//#define COMMUNICATION_MESSAGES
//-----------------------------------------------------------------------------------
//TExController mcu;
//-----------------------------------------------------------------------------------
u8 upc_rxd;
TBuff rx,tx;
TUpcState upc;
THistory history;
u32 LcMaxAnswerDelay;
u8 attempts;
//TExBuffer ExBuff;
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
#pragma vector=USART1_RXC_vect
__interrupt void upc_RX_IRQ()
{
	upc_RXHandler();
}
//-----------------------------------------------------------------------------------	
void upc_tx_byte(u8 byte)
{
	UDR1=byte;
}
//-----------------------------------------------------------------------------------
u8 upc_rx_byte()
{
	u8 byte;
	byte=UDR1;
	return byte;
}
//-----------------------------------------------------------------------------------
u8 upc_check_tx()
{
	if(UCSR1A & (1<<TXC1))return 1;
	else return 0;
}
//-----------------------------------------------------------------------------------
void upc_clear_tx_flag()
{
	UCSR1A|=(1<<TXC1);
}
//-----------------------------------------------------------------------------------
void tx_mode()
{
	upc_port&=~pin_mode;
	Delay_mks(2);
}
//-----------------------------------------------------------------------------------
void rx_mode()
{
	upc_port|=pin_mode;
}
//-----------------------------------------------------------------------------------
void upc_Set_Channel(u8 channel)
{
	u8 tmp=0;
	upc.channel=channel;
	switch(channel)
	{
		case 0:
			tmp=0;
		break;
		case 1:
			tmp|=pin_s0;
		break;
		case 2:
			tmp|=pin_s1;
		break;
		case 3:
			tmp|=pin_s0;
			tmp|=pin_s1;			
		break;
		case 4:
			tmp|=pin_s2;
		break;
	}
	switch_port&=~(pin_s0+pin_s1+pin_s2);
	switch_port|=tmp;
	Delay(5);
}
//-----------------------------------------------------------------------------------
void upc_hardware_init(u32 baund)
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
	upc_port_dir|=(pin_mode);
	upc_port&=~(pin_mode);
	
	switch_port_dir|=(pin_s0+pin_s1+pin_s2);
	switch_port&=~(pin_s0+pin_s1+pin_s2);
	tx_mode();
	UBRR1H = (unsigned char)(rate>>8);
	UBRR1L = (unsigned char)rate;
	/* Enable receiver and transmitter */
	UCSR1B =(1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1);
	/* Set frame format: 8data, 2stop bit */
	UCSR1C = (1<<USBS1)|(3<<UCSZ10);
	UDR1=' ';	
}
//---------------------------------------------------------------------------------
void upc_init()
{
	u8 i;
	upc_hardware_init(UPC_BAUND);
	memset((void *)&rx, 0, sizeof(rx));
	memset((void *)&tx, 0, sizeof(tx));	
	memset((void *)&upc, 0, sizeof(upc));		
	for(i=0;i<CHANNELS_NUM;i++)
		upc.channel_state[i]=50;
	upc.channel=0;

	//upc_set_max_answer_delay(0);
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
	sprintf(outtxt,"\n\r");
	for(i=0;i<len;i++)
	{
		ByteToStr(outtxt,buff,1);
		buff++;
		sprintf(outtxt," ");		
	}
}
//-----------------------------------------------------------------------------------
void upc_buff_init()
{
	memset((void *)&rx, 0, sizeof(rx));
	memset((void *)&tx, 0, sizeof(tx));	
}
//-----------------------------------------------------------------------------------
void upc_handler()
{
//	u16 i,tmp;
	upc_state_machine();
/*	if(UPC2_Time==0)
	{		
		UPC2_Time=10;	
		if(ExBuff.head.status==st_ToSend)
		{
			if((upc.status==st_none)||(upc.status==st_complete))
			{						
				upc_Set_Channel(ExBuff.head.channel);
				switch(ExBuff.head.command)
				{
					case tx_stat:upc_Set_Controller_Status();break;
					case tx_io:upc_Set_Controller_IO();break;
					case tx_pid0:upc_Set_Controller_PID(0);break;
					case tx_pid1:upc_Set_Controller_PID(1);break;
					case tx_pid2:upc_Set_Controller_PID(2);break;
					case tx_pid3:upc_Set_Controller_PID(3);break;	
					case tx_errors:upc_Set_Controller_Errors();break;		
							
					case tx_time:upc_Set_Controller_Time();break;	
					case tx_time_summ:upc_Set_Controller_Time_Summ();break;	
					case tx_time_wint:upc_Set_Controller_Time_Wint();break;
					case tx_params:
							mcu.Parameters[0]=mcu.Zaslonka[0];
							mcu.Parameters[1]=mcu.Zaslonka[1];
							mcu.Parameters[2]=mcu.Zaslonka_Mode;
							upc_Set_Controller_Params();
					break;

					case com_get_stat:upc_Get_Controller_Status();break;
					case rx_io:upc_Get_Controller_IO();break;
					case rx_pid0:upc_Get_Controller_PID(0);break;
					case rx_pid1:upc_Get_Controller_PID(1);break;
					case rx_pid2:upc_Get_Controller_PID(2);break;
					case rx_pid3:upc_Get_Controller_PID(3);break;	
					case rx_errors:upc_Get_Controller_Errors();break;																																	
										
					case rx_time:upc_Get_Controller_Time();break;	
					case rx_time_summ:upc_Get_Controller_Time_Summ();break;	
					case rx_time_wint:upc_Get_Controller_Time_Wint();break;
				}
			}
		}
	}
*/	
}
//-----------------------------------------------------------------------------------
/*
void upc_handler_old()
{
	u16 i,tmp;
	upc_state_machine();
	if(UPC2_Time==0)
	{		
		UPC2_Time=10;	
//		upc.channel=0;
		if((upc.status==st_none)||(upc.status==st_complete))
		{		
			upc.channel=0;
			upc_Set_Channel(upc.channel);
			switch(upc.channel)
			{
				case 0:
					//if(upc.txnew==0)
					if(mcu.tx_list!=0)
					{				
						// Check tx
						tmp=0;
						for(i=0;i<16;i++)
						{
							tmp=1<<i;
							if(mcu.tx_list & tmp)
							{
								switch(tmp)
								{
									case tx_stat:upc_Set_Controller_Status();break;
									case tx_io:upc_Set_Controller_IO();break;
									case tx_pid0:upc_Set_Controller_PID(0);break;
									case tx_pid1:upc_Set_Controller_PID(1);break;
									case tx_pid2:upc_Set_Controller_PID(2);break;
									case tx_pid3:upc_Set_Controller_PID(3);break;	
									case tx_errors:upc_Set_Controller_Errors();break;		
									
									case tx_time:upc_Set_Controller_Time();break;	
									case tx_time_summ:upc_Set_Controller_Time_Summ();break;	
									case tx_time_wint:upc_Set_Controller_Time_Wint();break;
									case tx_params:
										mcu.Parameters[0]=mcu.Zaslonka[0];
										mcu.Parameters[1]=mcu.Zaslonka[1];
										mcu.Parameters[2]=mcu.Zaslonka_Mode;
										upc_Set_Controller_Params();
									break;
								}
								mcu.tx_list&=~tmp;// clear flag
								return;
							}
						}	
					}
					if(mcu.update_stat!=0)
					{
						// Check RX		
						tmp=0;
						for(i=0;i<16;i++)
						{
							tmp=1<<i;
							if(mcu.update_stat & tmp)
							{
								switch(tmp)
								{
									case rx_stat:upc_Get_Controller_Status();break;
									case rx_io:upc_Get_Controller_IO();break;
									case rx_pid0:upc_Get_Controller_PID(0);break;
									case rx_pid1:upc_Get_Controller_PID(1);break;
									case rx_pid2:upc_Get_Controller_PID(2);break;
									case rx_pid3:upc_Get_Controller_PID(3);break;	
									case rx_errors:upc_Get_Controller_Errors();break;																																	
									
									case rx_time:upc_Get_Controller_Time();break;	
									case rx_time_summ:upc_Get_Controller_Time_Summ();break;	
									case rx_time_wint:upc_Get_Controller_Time_Wint();break;																																																														
								}
								mcu.update_stat&=~tmp;// clear flag
								return;
							}
						}
					}
					else
					{
						mcu.update_stat=mcu.rx_list;
//						upc.channel=1;
						upc.channel=0;
//						if(upc.channel>1)upc.channel=0;							
					}
				break;
				case 1:	
					mcu.Parameters[0]=mcu.Season;
					mcu.Parameters[1]=mcu.io.analog[mcu.io.num_ao+2];
					memcpy(&mcu.Parameters[5],m.Kotel,48);
					upc_Set_Controller_Params();
					upc.channel=0;
				break;
				
			}
		}
	}
}
*/
//-----------------------------------------------------------------------------------
void upc_RXHandler()
{
	upc_rxd=upc_rx_byte();
//	ByteToStr(outtxt,&upc_rxd,1);
//	sprintf(outtxt," ");
//	return;
//	if(upc.rxnew==1)return;	// Exit if previos not handled
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
	UPC_Time =  MAX_ANSWER_DELAY;
	if((upc.rxcount)>(rx.field.len+PACKET_HEADER_LEN-1))
	{
		upc.rxnew=1;
//		mem_dump(&rx.field.d[0],16);
	}
}
//-----------------------------------------------------------------------------------
void upc_TXHandler()
{
	// Check tx
	if(upc_check_tx())
	{
		if(upc.done==0)
		{
			upc_clear_tx_flag();
			upc_tx_byte(tx.data.d[upc.txcount]);
			upc.txcount++;			
			if((upc.txcount)>(tx.field.len+PACKET_HEADER_LEN-1))
			{
				upc.done=1;
//				sprintf(outtxt,"\n\r");
//				mem_dump(&tx.data.d[0],16);
			}
			else
				upc.done=0;
		}
		else
			upc.txnew=0;
	}
}
//-----------------------------------------------------------------------------------
u8 memcmp2(u8* str1,u8* str2,u8 len)
{
	u8 sign=0;
	u8 i;
	for(i=0;i<len;i++)
	{
		if(*str1!=*str2)sign=1;
		str1++;
		str2++;
	}
	return sign;
}
//-----------------------------------------------------------------------------------
void upc_state_machine()
{
	u16 tmp;
//	u8 i;
	adm_wd_reset; // lc

	switch(upc.status)
	{
		case st_none:
			attempts=0;
		break;
		case st_complete:
			attempts=0;
		break;		
		case st_sending:
			tx_mode();
			upc_TXHandler();	
			if(upc.txnew==0)
			{
				rx_mode(); // lc
				if(tx.field.com.bit.req)
				{
					upc.status=st_wait_answer;	
					UPC_Time =MAX_ANSWER_DELAY;
				}
				else
				{
					upc.status=st_none;
					upc.txnew=0;
					upc.txcount=0;
					upc.rxnew=0;
					upc.rxcount=0;						
				}			
			}			
			upc.error=er_none;			
		break;
		case st_wait_answer:
			rx_mode();					
			if(upc.rxnew==1)
				if(rx.field.com.bit.id==tx.field.com.bit.id)
				{					
					upc.status=st_answer_process;
				}
			if(UPC_Time==0)
			{
				// History
				if(history.timeout[upc.channel]<0xffff)
					history.timeout[upc.channel]++;
				upc.channel_state[upc.channel]++;
				if(upc.channel_state[upc.channel]>50)upc.channel_state[upc.channel]=50;				
				#ifdef COMMUNICATION_MESSAGES
					sprintf(outtxt,"\n\r Timeout " );ByteToStr(outtxt,&upc.channel,0);
					tmp=tx.field.com.bit.com;
					sprintf(outtxt," " );WordToStr(outtxt,(u16*)&tmp,0);
				#endif		
				if(attempts<3)
				{
					attempts++;
					upc.txnew=1;
					upc.txcount=0;
					upc.status=st_sending;		
					upc.rxnew=0;
					upc.rxcount=0;		
					upc.error=0;
					upc.done=0;					
				}
				else
				{
					upc.status=st_none;
					upc.error=er_no_answer;
					upc.txnew=0;
					upc.txcount=0;
					upc.rxnew=0;
					upc.rxcount=0;						
				}
			}
		break;
		case st_answer_process:
//			sprintf(outtxt,"\n\r Packet received ");
			upc.rxnew=0;
//			upc.status=st_complete;
			upc.status=st_none;			
			upc.channel_state[upc.channel]=0;
			// CRC calculation
			tmp=upc_crc(&rx);
			if(tmp!=rx.field.crc)
			{
				// History
				if(history.bad_crc[upc.channel]<0xffff)
					history.bad_crc[upc.channel]++;			
				#ifdef COMMUNICATION_MESSAGES
					sprintf(outtxt,"\n\r Bad CRC " );ByteToStr(outtxt,&upc.channel,0);
				#endif
//				WordToStr(outtxt,&tmp,1);
//				WordToStr(outtxt,&rx.field.crc,1);
				upc.error=er_bad_crc;
			}
			else
			{
				if(rx.field.com.bit.id!=tx.field.com.bit.id)
				{
					#ifdef COMMUNICATION_MESSAGES
						sprintf(outtxt,"\n\r Bad ID " );
					#endif	
					upc.error=er_bad_id;
				}
				else
				{
					upc.error=er_none;
				}
			}
		break;
	}
}
//-----------------------------------------------------------------------------------
u16 upc_crc(TBuff *buff)
{

	u16 crc;
	u8 p;
	InitCRC(&crc);
	for(p=0;p<(PACKET_HEADER_LEN-2);p++)	
	{
		CalcCRC(&(buff->data.d[p]),1,&crc);
	}
	for(p=0;p<(buff->field.len);p++)	
	{
		CalcCRC(&(buff->field.data.d[p]),1,&crc);
	}
	EndCRC(&crc);	
	return crc;
}
//-----------------------------------------------------------------------------------
