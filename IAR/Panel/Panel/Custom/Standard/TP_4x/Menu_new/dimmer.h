#ifndef __DIMMER
#define __DIMMER
//-----------------------------------------------------------------------------------
#include "..\..\..\..\System\Main.h"
//-----------------------------------------------------------------------------------
#define But_Dimmer_0			Obj[7]
#define But_Dimmer_1			Obj[0]
#define But_Dimmer_2			Obj[5]
#define But_Dimmer_3			Obj[1]
#define But_Dimmer_4			Obj[4]
#define But_Dimmer_5			Obj[15]
#define But_Dimmer_6			Obj[9]
#define But_Dimmer_7			Obj[8]
//-----------------------------------------------------------------------------------
eu8 Dimmer_Dir[8];
eu8 dimmer_slope[8];
eu8 dimmer_new_press;
es8 dimmer_sequence_state;
eu16 dimmer_sequence_timeout;
//-----------------------------------------------------------------------------------
void dimmer_handle_0();
void dimmer_handle_1();
void dimmer_handle_2();
void dimmer_handle_3();
void dimmer_handle_4();
void dimmer_handle_5();
void dimmer_handle_6();
void dimmer_handle_7();

void dimmer_plus(u8 num);
void dimmer_minus(u8 num);
void dimmer_off(u8 num);
void dimmer_on(u8 num);

void update_dimmers();
//-----------------------------------------------------------------------------------
#endif

