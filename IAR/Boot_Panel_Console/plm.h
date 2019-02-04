#ifndef _PLM
#define _PLM
//-----------------------------------------------------------------------------------
#include <iom128.h>
#include "Include\types.h"
//-----------------------------------------------------------------------------------
#define data0 PE3
#define nconf PE4
#define dclk  PE5
#define confd PE6
#define nstat PE7
//-----------------------------------------------------------------------------------
#define b_data0 0x08
#define b_nconf 0x10
#define b_dclk  0x20
#define b_confd 0x40
#define b_nstat 0x80

#define nb_data0 0xF7
#define nb_nconf 0xEF
#define nb_dclk  0xDF
#define nb_confd 0xBF
#define nb_nstat 0x7F
//-----------------------------------------------------------------------------------
void plm_reset();
void plm_config(u32 plm_addr);
u8 Plm_Read(u32 Addr);
void Plm_Select();
void Plm_Deselect();

//-----------------------------------------------------------------------------------
#endif
