#ifndef __EXTFLASH
#define __EXTFLASH
//-----------------------------------------------------------------------------------
#include <iom128.h>
#include "types.h"
//-----------------------------------------------------------------------------------
#define FLASH_END 0x40000 // end of ext flash mem
#define SECTOR_SIZE 0x100 // 256
// Mem partitions
#define PLM_FLASH_START 0x2000
#define PLM_FLASH_MAX_LEN 100*1024
// Pins descriptions
#define MA16  PD4
#define MA17  PD5
#define MA18  PD6
#define MA19  PD7

#define b_MA16  0x10
#define b_MA17  0x20
#define b_MA18  0x40
#define b_MA19  0x80

#define nb_MA16  0xef
#define nb_MA17  0xdf
#define nb_MA18  0xbf
#define nb_MA19  0x7f

//-----------------------------------------------------------------------------------
//extern u32 ee_plm_flash_end;
//-----------------------------------------------------------------------------------
void ExtBus_Init();
u8 Flash_Read(u32 Addr);
void Flash_Start_Write(u32 Addr);
u8 Flash_Write(u8 *Data,u8 Size);
void Flash_End_Write();
void Flash_Set_HAddr(u32 Addr);
void Flash_Select();
void Flash_Deselect();
u32 CheckCRC(u32 Addr);
void FGet(u8 *Data,u16 Addr,u8 Len);
//-----------------------------------------------------------------------------------
#endif
