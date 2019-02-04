#ifndef __EXTFLASH
#define __EXTFLASH
//-----------------------------------------------------------------------------------
#include <iom128.h>
#include "Include\types.h"
#include "spm.h"
//-----------------------------------------------------------------------------------
#define APP_FLASH_END 0x1E0000 // end of ext flash mem
#define SECTOR_SIZEB 0x100 // 256
#define SECTOR_SIZEW 0x80 // 256
// Mem partitions
// Application
#define APPL_FLASH_START   0x00000
#define APPL_FLASH_END     0x0ffff
// PLM
#define PLM_FLASH_START   0x10000
#define PLM_FLASH_END     0x1DDFF
// Headers
// App
#define HAPP_FLASH_START   0x1DE00
#define HAPP_FLASH_END     0x1DEFF
// Plm
#define HPLM_FLASH_START   0x1DF00
#define HPLM_FLASH_END     0x1DFFF

extern u8 APPFLASH *fptr;
extern u8 header;	
//-----------------------------------------------------------------------------------
//extern u32 ee_plm_flash_end;
//-----------------------------------------------------------------------------------
u8 Flash_Read(u32 Addr);
void Flash_Start_Write(u32 Addr);
u8 Flash_Write(u8 *Data,u8 Size);
void Flash_End_Write();
u32 CheckCRC(u8 who);
void FGet(u8 *Data,u32 Addr,u8 Len);
void Flash_Write_Sector(u32 Addr,u8 *Data,u8 Size);
//-----------------------------------------------------------------------------------
#endif
