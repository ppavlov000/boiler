//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
//#define MAX_ANSWER_DELAY	100	// ms UPC_Time
//-----------------------------------------------------------------------------------
//extern TPhoneRecord PhoneList[5];
//extern TPassword Password;
//extern u8 custom_information_init;
//extern u8 custom_information_update;

u8 upc_rxd;
TBuff rx,tx;
TUpcState upc;
TExchange exch;
TExchange own_state;
//u8 re_status=0;
TTime ft;
u16 crc;
TDimmer Dimmer;	
vu8 bad_counter=0;
//extern u8 Password_Mode;
//extern u8 Password_Downcount;
u8 update_packet=0;
extern  u32 HW;
u32 HW_in=0;
extern u8 M_buff_sign;
extern u8 Transparent_Mode;
void upc_set_sys();
//-----------------------------------------------------------------------------------
void upc_S_transparent_packet();
void upc_answer_set_register();
void upc_answer_get_register();
void upc_answer_set_work();
void upc_answer_get_work();
void upc_answer_get_prog();
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
#if __MODBUS_ENA==0
//-----------------------------------------------------------------------------------
void upc_init()
{
	upc_hardware_init(UPC_BAUND);
	memset((void *)&rx, 0, sizeof(rx));
	memset((void *)&tx, 0, sizeof(tx));	
	memset((void *)&upc, 0, sizeof(upc));	
	memset((void *)&exch, 0, sizeof(exch));		
	memset((void *)&own_state, 0, sizeof(own_state));			
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
void mem_dump(u8 *str,u8 *buff,u8 len)
{
	u8 i;
	u8 str2[8];
//	_sprintf(outtxt,"\n\r");
	*str=0;
	for(i=0;i<len;i++)
	{
		ByteToStr(str2,buff,1);
		strcat((char*)str,(char*)str2);
		strcat((char*)str," ");
		buff++;
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
	Time0=100;
//	u8 str[10];
//	u8 i,old_stat;
	upc_rxd=upc_rx_byte();
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
		if(upc_crc_data(&rx)==rx.field.crc_data)
		{
//			_sprintf(outtxt,"\n\r Good CRC");
			upc.rxnew=1;		
//			mem_dump(rx.field.d,10);
			if(Transparent_Mode)
			{
				switch(rx.field.com.bit.com)
				{
					case com_release_transp:
						if((rx.field.com.bit.id==m.Address)||(rx.field.com.bit.id==0))
						{
							if(rx.field.com.bit.req)
								upc_answer_release_transparent();
							Transparent_Mode=0;
						}
					break;													
					case com_transp:
						if(rx.field.com.bit.id==m.Address)
							upc_S_transparent_packet_2();
					break;
				}
			}
			else
			if(rx.field.com.bit.trans)
			{
				upc_S_transparent_packet();
			}
			else
				switch(rx.field.com.bit.com)
				{
					case com_reqt_status:
					case com_get_stat:
						if(rx.field.com.bit.id==m.Address)
							upc_answer_sys();
					break;				
					case com_set_stat:
						if((rx.field.com.bit.id==m.Address)||(rx.field.com.bit.id==0))
							upc_set_sys();
					break;				
					case com_reqt_reset:
						if((rx.field.com.bit.id==0)||(rx.field.com.bit.id==m.Address))
							Mod_Reset();
					break;		
					case com_reqt_res_hw:
						HW_in=*(u32*)&rx.field.d[0];
						if(HW==HW_in)
							Mod_Reset();
					break;					
					case com_reqt_sys_info:
						if(rx.field.com.bit.id==m.Address)
							upc_answer_info(1);
					break;		
					case com_reqt_menu_info:
						if(rx.field.com.bit.id==m.Address)
							upc_answer_info(3);
					break;		
					case com_reqt_sys_name:
						if(rx.field.com.bit.id==m.Address)
							upc_answer_info(2);																																		
					break;		
					case com_reqt_menu_name:
						if(rx.field.com.bit.id==m.Address)
							upc_answer_info(4);
					break;			
					case com_set_tansp:
						if(rx.field.com.bit.id==m.Address)
						{
							upc_answer_set_transparent();
							Transparent_Mode=1;
						}
					break;			
					case com_set_register:
							if((rx.field.com.bit.id==m.Address))
								upc_answer_set_register();		
						break;
					case com_get_register:
							if((rx.field.com.bit.id==m.Address))
								upc_answer_get_register();		
						break;				
	
					case com_get_work_rec:
							if((rx.field.com.bit.id==m.Address))
								upc_answer_get_work();		
						break;				
					case com_set_work_rec:
							if((rx.field.com.bit.id==m.Address)||(rx.field.com.bit.id==0))
								upc_answer_set_work();		
						break;				
					case com_get_prog_rec:
							if((rx.field.com.bit.id==m.Address))
								upc_answer_get_prog();		
						break;						
	
				}
		}
		else
		{
//			_sprintf(outtxt,"\n\r Bad crc");
		}
	}
}
//-----------------------------------------------------------------------------------
void upc_TXHandler()
{
#ifdef __RENESAS
	u16 size;
	u8 *d;
#endif

	if(UPC_Time2!=0)return;
	// Check tx	
	if(upc.done==0)
//	while(upc.done!=0)
	{
#ifdef __RENESAS
		tx_mode();	
		size = tx.field.len+PACKET_HEADER_LEN;
		d = tx.data.d;

		while (size--) {
			upc_tx_byte(*d);
			d++;
			watchdog_reset();
		}

		while (!upc_check_tx_complite())
			watchdog_reset();

		UPC_Time2 = 3;

		upc.done  = 1;
#else
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
#endif
	}
	else
	{
		upc.txnew=0;
		rx_mode();		
	}	
}

//-----------------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------------
