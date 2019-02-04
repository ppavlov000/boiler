#ifndef __LCD_TEMPLATE
#define __LCD_TEMPLATE
//-----------------------------------------------------------------------------------
#ifndef __RENESAS
  #include "inavr.h"
#endif
#include "..\Bmp\bmp.h"
//-----------------------------------------------------------------------------------
//extern TRoutine RList[10];
extern TLCDPict _Logo;
extern TLCDPict _Null;
extern TLCDPictTop Scr;
extern TLCDPict Obj[20];
extern TLCDPict Alarm;
extern TLCDPict_Txt Txt[30];

void Set_Int_State(u8 data);
void Reset_Int_State(u8 data);
void Set_Int_State_0();
void Set_Int_State_1();
void Set_Int_State_2();
void Set_Int_State_3();
void Set_Int_State_4();
void Set_Int_State_5();
void Set_Int_State_6();
void Set_Int_State_7();
//-----------------------------------------------------------------------------------
#endif
