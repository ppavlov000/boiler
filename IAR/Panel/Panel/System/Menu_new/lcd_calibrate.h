#ifndef __CALIBRATE
#define __CALIBRATE
//-----------------------------------------------------------------------------------
#ifndef __RENESAS
  #include "inavr.h"
#endif
#include "..\Bmp\bmp.h"
//-----------------------------------------------------------------------------------
extern TLCDPict _Point_1;
extern TLCDPict _Point_0;
void calibrate_bmp();
//-----------------------------------------------------------------------------------
#endif
