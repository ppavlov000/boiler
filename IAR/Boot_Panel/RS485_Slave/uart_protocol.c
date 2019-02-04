//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
#define MAX_ANSWER_DELAY	20	// ms UPC_Time
//-----------------------------------------------------------------------------------
u8 upc_rxd;
TBuff rx,tx;
TUpcState upc;
//u8 re_status=0;
TTime ft;
u16 crc;
vu8 bad_counter=0;
u8 programm_state=0;
u8 LcUpcEn;
eu8 Enter_Boot_Mode;
u32 HW;
u32 HW_in=0;
u8 HW_programming_mode=0;
//-----------------------------------------------------------------------------------
void upc_init()
{
	upc_hardware_init(UPC_RATE);
	memset((void *)&rx, 0, sizeof(rx));
	memset((void *)&tx, 0, sizeof(tx));	
	memset((void *)&upc, 0, sizeof(upc));	
	upc_en(0);
	rx_mode();	
}

//-----------------------------------------------------------------------------------
void upc_en(u8 en)
{
	LcUpcEn = en;
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
//	sprintf(outtxt,"\n\r");
	for(i=0;i<len;i++)
	{
//		ByteToStr(outtxt,buff,1);
		buff++;
//		sprintf(outtxt," ");		
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
	u32 ltmp;
//	u8 i,old_stat;
	upc_rxd=upc_rx_byte();
	UPC_Time=MAX_ANSWER_DELAY;		
	switch(upc.rxcount)
	{
		case 0:
			if(upc_rxd!=PREAMBULA_LOW)
			{
				upc.rxcount=0;	
//				UPC_Time=MAX_ANSWER_DELAY;	
				return;
			}
		break;
		case 1:
			if(upc_rxd!=PREAMBULA_HIGH)
			{
				upc.rxcount=0;	
//				UPC_Time=MAX_ANSWER_DELAY;	
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
			upc.rxnew=1;		
//			mem_dump((u8*)&rx,4);
			switch(rx.field.com.bit.com)
			{
				//******************* SYS *******************
				//----------------------------------
				case com_reqt_status:
					if((rx.field.com.bit.id==m_Address))
						upc_answer_status();
				break;							
				//----------------------------------
				case com_reqt_reset:
					if((rx.field.com.bit.id==0)||(rx.field.com.bit.id==m_Address))
					{
						start_boot();
					}					
				break;		
				//----------------------------------	
				case com_reqt_start:
					if((rx.field.com.bit.id==0)||(rx.field.com.bit.id==m_Address))
						if(stat==0)
						{
							Enter_Boot_Mode=0;
							start_main();
						}
				break;	
				//----------------------------------																		
				case com_reqt_boot:
					if(rx.field.com.bit.id==m_Address)
					{
						upc_answer_boot_mode();		
						Enter_Boot_Mode=1;
//						Time0=5000;
					}
				break;
				//----------------------------------																		
				case com_reqt_boot_hw:
					FGet((u8*)&HW,HAPP_FLASH_START+THW_LOC,4);
					HW_in=*(u32*)&rx.field.d[0];
					if(HW==HW_in)					
					{
//						upc_answer_boot_mode();		
						Enter_Boot_Mode=1;
					}
				break;				
				//********************************************	
				//******************* PROG *******************			
				//----------------------------------					
				case com_reqt_sys_info:
					if(rx.field.com.bit.id==m_Address)
					{
						upc_answer_info(1);
//						Time0=5000;
					}
				break;	
				//----------------------------------	
				case com_reqt_menu_info:
					if(rx.field.com.bit.id==m_Address)
					{
						upc_answer_info(3);
//						Time0=5000;
					}
				break;	
				//----------------------------------	
				case com_reqt_sys_name:
					if(rx.field.com.bit.id==m_Address)
					{
						upc_answer_info(2);																																		
//						Time0=5000;
					}
				break;	
				//----------------------------------	
				case com_reqt_menu_name:
					if(rx.field.com.bit.id==m_Address)
					{
						upc_answer_info(4);
//						Time0=5000;						
					}
				break;								
				//----------------------------------
				case com_reqt_prog_start_sys:
					if(rx.field.com.bit.id==m_Address)
					{
						upc_answer_prog(1);
						HW_programming_mode=0;
						xmod_status=1;
						header=1;
						data_packet_number_old=0;
						data_status=0;
						key|=0x00007700;						
						Flash_Start_Write(APPL_FLASH_START);
//						Time0=5000;
//						Time6=100;
					}
				break;
				//----------------------------------
				case com_reqt_prog_start_menu:
					if(rx.field.com.bit.id==m_Address)
					{
						upc_answer_prog(1);
						HW_programming_mode=0;
						xmod_status=2;
						header=2;
						data_packet_number_old=0;
						data_status=0;
						key|=0x00007700;
						Flash_Start_Write(PLM_FLASH_START);
//						Time0=5000;						
					}
				break;
				//----------------------------------
				// Multipy devices programming
				//----------------------------------
				case com_reqt_prog_start_sys_hw:
					FGet((u8*)&HW,HAPP_FLASH_START+THW_LOC,4);
					HW_in=*(u32*)&rx.field.d[0];
					if(Enter_Boot_Mode==1)
					if(HW==HW_in)	
//					if(HW_programming_step==0)
					{
//						upc_answer_prog(1);
						HW_programming_mode=1;
						xmod_status=1;
						header=1;
						data_packet_number_old=0;
						data_status=0;
						key|=0x00007700;						
						Flash_Start_Write(APPL_FLASH_START);
//						Time0=5000;
//						Time6=100;
//						Beep_Time=50;
//						HW_programming_step=1;
					}
				break;
				//----------------------------------
				case com_reqt_prog_start_menu_hw:
					FGet((u8*)&HW,HAPP_FLASH_START+THW_LOC,4);
					HW_in=*(u32*)&rx.field.d[0];
					if(Enter_Boot_Mode==1)
					if(HW==HW_in)	
//					if(HW_programming_step==0)
					{
//						upc_answer_prog(1);
						HW_programming_mode=1;
						xmod_status=2;
						header=2;
						data_packet_number_old=0;
						data_status=0;
						key|=0x00007700;
						Flash_Start_Write(PLM_FLASH_START);
//						Time0=5000;		
//						HW_programming_step=1;
					}
				break;
				//----------------------------------
				case com_reqt_prog:
					if((rx.field.com.bit.id==m_Address)||(HW_programming_mode!=0))
					{
						adm_wd_reset();
						if(HW_programming_mode==0)
							upc_answer_prog(1);
						Ready_for_programming=1;
						data_len=rx.field.len-2;
						memcpy((u8*)&data_packet_number,&rx.field.d[0],2);
						memcpy((u8*)data,&rx.field.d[2],data_len);	
						key|=0x00000033;	
//						Time0=5000;						
//						Time6=100;
					}
				break;		
				//----------------------------------
				case com_reqt_prog_stop:
					if((rx.field.com.bit.id==m_Address)||(HW_programming_mode!=0))
					{
						if(HW_programming_mode==0)						
							upc_answer_prog(1);
						Flash_End_Write();
						Programming_Finished=1;	
//						Time0=5000;
//						HW_programming_step=0;
					}
				break;				
				//----------------------------------
				case com_reqt_flash_read:
					if(rx.field.com.bit.id==m_Address)
					{
						memcpy(&ltmp,&rx.field.d[0],4);
						upc_answer_flash_read(ltmp);	
					}			
				break;
				//----------------------------------
			}
		}
		else
		{
			//sprintf(outtxt,"\n\r Bad crc");
			Time6=100;
		}
	}
//	rx_mode(); lc!!!	
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
			adm_wd_reset();
		}

		while (!upc_check_tx_complite())
			adm_wd_reset();

		UPC_Time2 = 2;

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
//					sprintf(outtxt," ch");											
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
u16 upc_crc_(TBuff *buff)
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
		CalcCRC(&(buff->field.d[p]),1,&crc);
	}
	EndCRC(&crc);	
	return crc;
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


