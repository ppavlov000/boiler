#ifndef __MEMORY
#define __MEMORY
//--------------------------------------------------------------------------------------------------------
#include "..\System\Misc\types.h"

//--------------------------------------------------------------------------------------------------------
// Flash partitions
//--------------------------------------------------------------------------------------------------------
//	#define SECTOR_SIZEB 0x80 // 128

#define APPL_FLASH_START	0xC0000
//	#define APPL_FLASH_END		0xDffff
#define HAPP_FLASH_START	0xDFF80


#define PICTURE_FLASH_START	0xE0000
//	#define PLM_FLASH_END		0xF7FFF
#define HPLM_FLASH_START	0xF7F80

//	#define HAPP_FLASH_START   0xFC000
//	#define HAPP_FLASH_END     0xFDFFF

//	#define HPLM_FLASH_START   0xFE000
//	#define HPLM_FLASH_END     0xFEFFF

//#define BOOT_FLASH_START		 0x1E000	
// Main software
//#define MAIN_FLASH_START		 0x00000	
//#define PICTURE_FLASH_START		 0xE0000	// 0x10000	
// Pictures
//#define PLM_FLASH_START   0x10000
//#define PLM_FLASH_END     0x1DDFF
//--------------------------------------------------------------------------------------------------------
// Headers
// Main software
//#define HAPP_FLASH_START   (PICTURE_FLASH_START + 0x0DE00)
//#define HAPP_FLASH_END     (PICTURE_FLASH_START + 0x0DEFF)
// Pictures
//#define HPLM_FLASH_START   (PICTURE_FLASH_START + 0x0DF00)
//#define HPLM_FLASH_END     (PICTURE_FLASH_START + 0x0DFFF)

#define THEAD_WIDTH 	128
#define TNAME_WIDTH 	103

#define TNAME_LOC 		0
#define THW_LOC 		103
#define TSW_LOC 		107
#define TTIME_LOC 		111
#define THWF_LOC 		118
#define TF_LOC 			119
#define LENGTH_LOC 		120
#define CRC_D_LOC 		124
#define CRC_H_LOC 		126
//--------------------------------------------------------------------------------------------------------
#endif
