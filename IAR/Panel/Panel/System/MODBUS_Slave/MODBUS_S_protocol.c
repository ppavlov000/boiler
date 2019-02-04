//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
#define MODBUS_DEBUG_ENA 	1
//-----------------------------------------------------------------------------------
#if __MODBUS_ENA
//-----------------------------------------------------------------------------------
vu8 mod_rxd;
vu8 mod_tx[MOD_TX_BUF_LEN]={'1','2','3','4','5','6','7','8','9','0'};
vu8 mod_rx[MOD_RX_BUF_LEN];
vu8 mod_rx_packet[MOD_RX_BUF_LEN];
vu8 mod_tx_packet[MOD_RX_BUF_LEN];
vu8	mod_rx_packet_len;
vu8	mod_tx_packet_len;
vu8 mod_tx_ptr;
vu8 mod_rx_ptr_end;
vu8 mod_rx_ptr_start;
vu8 mod_tx_ptr_end;
vu8 mod_tx_ptr_start;

vu16 mod_rx_timout=0;
vu8 mod_rx_new=0;
//vu8 mod_rx_start;
//vu8 mod_rx_stop;
//vu8 mod_tx_start;
//vu8 mod_tx_stop;
//-----------------------------------------------------------------------------------
void modbus_s_init()
{
	mod_hardware_init(UPC_BAUND);
	rx_mode();		
	mod_rx_ptr_end = mod_rx_ptr_start=0;
	mod_tx_ptr_end = mod_tx_ptr_start=0;	
}
//-----------------------------------------------------------------------------------
void mem_dump(u8 *buff,u8 len)
{
//	u8 i;
//	_sprintf(outtxt,"\n\r");
//	for(i=0;i<len;i++)
//	{
//		ByteToStr(outtxt,buff,1);
//		buff++;
//		_sprintf(outtxt," ");		
//	}
}
//-----------------------------------------------------------------------------------
u8 modbus_s_Check_New_Packet()
{	
	u8 start;
	u8 i;
	u8 str[5];
	if(mod_rx_ptr_end!=mod_rx_ptr_start)	
		if(mod_rx_timout==0)
		{
			// Reply back
			start=mod_rx_ptr_start;
			i=0;
			while(start!=mod_rx_ptr_end)		
			{		
				
				mod_rx_packet[i]=mod_rx[start];
				i++;
				start++;
				if(start>=MOD_RX_BUF_LEN)start-=MOD_RX_BUF_LEN;
			}
			mod_rx_new=1;
			mod_rx_packet_len=i;
			mod_rx_ptr_end=mod_rx_ptr_start=0;	// Reset input biffer
			return 1;
		}
	return 0;
}
//-----------------------------------------------------------------------------------
void modbus_s_PacketHandler()
{
	u16 	in_crc;
	u16 	real_crc;	
	u8 		word[10];
	u16 	addr;
	u16		num;
	u8 i;
	
//	addr=get_reg_addr((u8*)&fan[0].T);
//	WordToStr(word,&addr,1);
//	lcd_sprintf(word,0,0);		

	if(modbus_s_Check_New_Packet())
	{
		if(mod_rx_packet[0]==m.Address)
		{
			in_crc	=	(mod_rx_packet[mod_rx_packet_len-1]);			
			in_crc	=	in_crc<<8;
			in_crc |=	(mod_rx_packet[mod_rx_packet_len-2]);			
			real_crc=CRC16 ((u8*)mod_rx_packet,mod_rx_packet_len-2);
			if(in_crc==real_crc)
			{
//				WordToStr(word,&in_crc,1);
//				lcd_sprintf(word,0,0);	
//				WordToStr(word,&real_crc,1);
//				lcd_sprintf(word,0,1);	
//				ByteToStr(word,(u8*)&mod_rx_packet_len,1);
//				lcd_sprintf(word,5,0);	
				switch(mod_rx_packet[1])
				{
				case 23:// Reading resistors
					
					// Writing
					addr	=	(mod_rx_packet[2+4]);			
					addr	=	addr<<8;
					addr 	|=	(mod_rx_packet[3+4]);			
					num		=	(mod_rx_packet[4+4]);			
					num		=	num<<8;
					num 	|=	(mod_rx_packet[5+4]);	
					
					for(i=0;i<num;i++)
					{
//						reg_data[addr+i*2]=mod_tx_packet[i*2+11];
//						reg_data[addr+i*2+1]=mod_tx_packet[i*2+12];
						reg_data[addr+i*2]=(mod_rx_packet[12+i*2]);
						reg_data[addr+1+i*2]=(mod_rx_packet[11+i*2]);						
					}
//				WordToStr(word,&addr,1);
//				lcd_sprintf(word,0,0);	
//				WordToStr(word,&num,1);
//				lcd_sprintf(word,0,1);	
//					num		=	(mod_rx_packet[11]);			
//					num		=	num<<8;
//					num 	|=	(mod_rx_packet[12]);	
//				WordToStr(word,&num,1);
//				lcd_sprintf(word,5,1);	
//				reg_data[addr]=(mod_rx_packet[12]);
//				reg_data[addr+1]=(mod_rx_packet[11]);
					
//				ByteToStr(word,(u8*)&mod_tx_packet_len,1);
//				lcd_sprintf(word,5,0);								
					// Reading
					addr	=	(mod_rx_packet[2]);			
					addr	=	addr<<8;
					addr 	|=	(mod_rx_packet[3]);			
					num		=	(mod_rx_packet[4]);			
					num		=	num<<8;
					num 	|=	(mod_rx_packet[5]);	
					
					mod_tx_packet[0]=m.Address;
					mod_tx_packet[1]=23;
					mod_tx_packet[2]=num;
	
					for(i=0;i<num;i++)
					{
						mod_tx_packet[i*2+4]=reg_data[addr+i*2];
						mod_tx_packet[i*2+3]=reg_data[addr+i*2+1];
					}
					mod_tx_packet_len=num*2+5;

//				WordToStr(word,&addr,1);
//				lcd_sprintf(word,0,0);	
//				WordToStr(word,&num,1);
//				lcd_sprintf(word,0,1);	
//				ByteToStr(word,(u8*)&mod_tx_packet_len,1);
//				lcd_sprintf(word,5,0);					
				
					real_crc=CRC16 ((u8*)mod_tx_packet,mod_tx_packet_len-2);
					mod_tx_packet[num*2+3]=real_crc & 0x00ff;
					mod_tx_packet[num*2+4]=real_crc >>8;	
					
					memcpy((void*)mod_tx,(void*)mod_tx_packet,mod_tx_packet_len);
					mod_tx_ptr_end=mod_tx_packet_len;
					mod_tx_ptr_start=0;					
					modbus_s_TXHandler();
					break;
				}
			}
			else
			{
//				lcd_sprintf("CRC Bad",0,1);					
			}
		}
		mod_rx_ptr_end=mod_rx_ptr_start=0;	// Reset input biffer
		mod_rx_packet_len=0;
	}
}
//-----------------------------------------------------------------------------------
void modbus_s_RXHandler()
{	
	u8 stop;
	mod_rx_timout=MODBUS_SILENCE;
	mod_rxd=mod_rx_byte();
	stop=mod_rx_ptr_end + 1;
	if(stop>=MOD_RX_BUF_LEN)stop-=MOD_RX_BUF_LEN;
	if(stop!=mod_rx_ptr_start)
	{
		mod_rx[mod_rx_ptr_end]=mod_rxd;
		mod_rx_ptr_end=stop;
	}
}

//-----------------------------------------------------------------------------------
void modbus_s_TXHandler()
{
	u8 start;	
	start=mod_tx_ptr_start;
//	mod_tx_stop=mod_tx_ptr_end;	

//	if(mod_check_tx())
	if(start!=mod_tx_ptr_end)		
	{		
//		mod_clear_tx_flag();
		tx_mode();			
		mod_tx_byte(mod_tx[start]);		
		start++;
		if(start>=MOD_TX_BUF_LEN)start-=MOD_TX_BUF_LEN;
		mod_tx_ptr_start=start;			
	}
	else	
		rx_mode();
}
//-----------------------------------------------------------------------------------
void modbus_TxPacket(u8 *str, u8 len)
{
	u8 stop;
	stop=mod_tx_ptr_end;	
	while(len!=0)
	{
		stop++;
		if(stop>=MOD_TX_BUF_LEN)stop-=MOD_TX_BUF_LEN;
		if(stop!=mod_tx_ptr_start)
		{
			mod_tx[stop]=*str;
			str++;
			mod_tx_ptr_end=stop;				
		}	
		len--;
	}
	modbus_s_TXHandler();
}
//-----------------------------------------------------------------------------------
u8	modbus_RxPacket(u8 *str)
{
	u8 tmp;
	u8 i=0;
	u8 start,stop;
	u8 sign=0;
	u8 number[14];
	u8 s[4]=" \n\r";//{26,10,13,0};
	s[0]=26;
	u8 j;
						
	start=mod_rx_ptr_start;
	stop=mod_rx_ptr_end;
	while(start!=stop)
	{
			tmp=start + 1;
			if(tmp>=MOD_RX_BUF_LEN)tmp-=MOD_RX_BUF_LEN;
			start=tmp;
			mod_rx_ptr_start=start;
			if((mod_rx[start]==0))
			{				
//				gsm.word[i]=gsm_rx[start];
//				data[data_cnt]=gsm.word[i];
//				i++;
//				gsm.word[i]=0;
			}
//			else
//			{
//				if(i!=0)
//				{
//					sign=1;
//#if DEBUG_ENA					
//					__sprintf(outtxt,"\n\r>>");
//					__sprintf(outtxt,gsm.word);					
//#endif					
//					break;
//				}
//			}
	}
}
//-----------------------------------------------------------------------------------
#endif
