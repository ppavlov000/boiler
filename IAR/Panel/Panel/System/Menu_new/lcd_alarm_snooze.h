#ifndef __LCD_ALARM_SNOOZE
#define __LCD_ALARM_SNOOZE
//-----------------------------------------------------------------------------------
#ifndef __RENESAS
  #include "inavr.h"
#endif
#include "..\Bmp\bmp.h"
//-----------------------------------------------------------------------------------
extern TLCDPictTop Scr_2;
void show_time_snooze();
//-----------------------------------------------------------------------------------
#endif
