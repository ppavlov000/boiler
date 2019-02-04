//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
eu8 Flash_Checked;
//-----------------------------------------------------------------------------------
void upc_answer_status()
{
	tx.field.pre=0x55AA;	
	tx.field.com.bit.id=m_Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.trans=rx.field.com.bit.trans;	
	tx.field.com.bit.com=com_reqt_status;	
	tx.field.d[0]=BOOT_CONTROLLER;
	FGet((u8*)&tx.field.d[1],HAPP_FLASH_START+THW_LOC,4);	
	tx.field.d[5]=stat;
	tx.field.d[6]=Flash_Checked;
	tx.field.d[7]=0;	
	tx.field.len=8;
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);	
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
//	tx_mode(); lc!!!
	UPC_Time2=3;
}
//-----------------------------------------------------------------------------------
void upc_answer_boot_mode()
{
	tx.field.pre=0x55AA;	
	tx.field.com.bit.id=m_Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=com_reqt_boot;	
	tx.field.com.bit.trans=rx.field.com.bit.trans;		
//	tx.field.d[0]=stat;
	tx.field.len=0;
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);	
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
//	tx_mode(); lc!!!
	UPC_Time2=3;
}
//-----------------------------------------------------------------------------------
void upc_answer_set_id()
{
	tx.field.pre=0x55AA;	
	tx.field.com.bit.id=rx.field.com.bit.id;
	tx.field.com.bit.trans=rx.field.com.bit.trans;		
	tx.field.com.bit.req=0;
	tx.field.com.bit.com=com_reqt_set_id;	
	tx.field.len=0;
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);	
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
//	tx_mode(); lc!!!
	UPC_Time2=3;
}
//-----------------------------------------------------------------------------------
void upc_answer_info(u8 what)
{
//	u8 *ptr;
	TPanelInfo info;
//	u32 Addr;
	memset(&info,0,sizeof(TPanelInfo));
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m_Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.trans=rx.field.com.bit.trans;	
	
	tx.field.len=0;	
	switch(what)
	{
		case 1:
			tx.field.com.bit.com=com_reqt_sys_info;
			info.present=1;
			FGet((u8*)&info.HW_Version,HAPP_FLASH_START+THW_LOC,4);
			FGet((u8*)&info.SW_Version,HAPP_FLASH_START+TSW_LOC,4);
			FGet((u8*)&info.Time,HAPP_FLASH_START+TTIME_LOC,sizeof(TTime));
			if(stat & 0x01)
			{
				memset(&info,0,sizeof(TPanelInfo));
			}
			memcpy(&tx.field.d[0],&info,sizeof(info));	
			tx.field.len=sizeof(info);		
		break;
		case 2:
			tx.field.com.bit.com=com_reqt_sys_name;
			FGet((u8*)&tx.field.d[0],HAPP_FLASH_START+TNAME_LOC,TNAME_WIDTH);
			if(stat & 0x01)
			{
				strcpy((char *)&tx.field.d[0],"No software");
			}	
			tx.field.len=TNAME_WIDTH;
		break;		
		case 3:
			tx.field.com.bit.com=com_reqt_menu_info;
			info.present=1;
			FGet((u8*)&info.HW_Version,HPLM_FLASH_START+THW_LOC,4);
			FGet((u8*)&info.SW_Version,HPLM_FLASH_START+TSW_LOC,4);
			FGet((u8*)&info.Time,HPLM_FLASH_START+TTIME_LOC,sizeof(TTime));
			if(stat & 0x02)
			{
				memset(&info,0,sizeof(TPanelInfo));
			}			
			memcpy(&tx.field.d[0],&info,sizeof(info));	
			tx.field.len=sizeof(info);
		break;					
		case 4:
			tx.field.com.bit.com=com_reqt_menu_name;
			FGet((u8*)&tx.field.d[0],HPLM_FLASH_START+TNAME_LOC,TNAME_WIDTH);
			if(stat & 0x02)
			{
				strcpy((char *)&tx.field.d[0],"No software");
			}
			tx.field.len=TNAME_WIDTH;
		break;		
		
	}	
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);	
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
//	tx_mode(); lc!!!
	UPC_Time2=3;
//	sprintf(outtxt,"\n\r ");
//	mem_dump(&tx.field.d[0],sizeof(info));	
}
//-----------------------------------------------------------------------------------
void upc_answer_prog(u8 what)
{
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m_Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.trans=rx.field.com.bit.trans;		
	tx.field.len=0;	
	tx.field.com.bit.com=com_reqt_prog;
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);	

	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
//	tx_mode(); lc!!!
	UPC_Time2=3;
}
//-----------------------------------------------------------------------------------
void upc_answer_flash_read(u32 address)
{
	tx.field.pre=0x55AA;
	tx.field.com.bit.id=m_Address;
	tx.field.com.bit.req=0;
	tx.field.com.bit.trans=rx.field.com.bit.trans;		
	FGet((u8*)&tx.field.d[0],address,128);
	tx.field.len=128;	
	tx.field.com.bit.com=com_reqt_flash_read;
	tx.field.crc_data=upc_crc_data(&tx);
	tx.field.crc_head=upc_crc_head(&tx);	
	upc.txnew=1;
	upc.txcount=0;	
	upc.done=0;	
//	tx_mode(); lc!!!
	UPC_Time2=3;
}
