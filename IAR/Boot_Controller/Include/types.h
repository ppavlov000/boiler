#ifndef __TYPES
#define __TYPES
//-----------------------------------------------------------------------------------
#define c8  char
#define s8  char
#define s16 short
#define s32 long
#define u8  unsigned char
#define u16 unsigned short
#define u32 unsigned long
#define f32  float
#define d64  double

#define vs8  volatile char
#define vs16 volatile short
#define vs32 volatile long
#define vu8  volatile unsigned char
#define vu16 volatile unsigned short
#define vu32 volatile unsigned long
#define vf32 volatile float
#define vd64 volatile double

#define es8  extern char
#define es16 extern short
#define es32 extern long
#define eu8  extern unsigned char
#define eu16 extern unsigned short
#define eu32 extern unsigned long
#define ef32 extern float
#define ed64 extern double

#define evs8  extern volatile char
#define evs16 extern volatile short
#define evs32 extern volatile long
#define evu8  extern volatile unsigned char
#define evu16 extern volatile unsigned short
#define evu32 extern volatile unsigned long
#define evf32 extern volatile float
#define evd64 extern volatile double

#define bool u8
#define true 1
#define false 0
//-----------------------------------------------------------------------------------

#ifdef __RENESAS
	#define __flash			const
	#define __farflash		const
	#define __hugeflash		const
	#define APPFLASH 		const
#endif

#endif
