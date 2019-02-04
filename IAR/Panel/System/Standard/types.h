#ifndef __TYPES
#define __TYPES
//-----------------------------------------------------------------------------------
#define c8  char
#define s8  signed char
#define s16 signed short
#define s32 signed long
#define u8  unsigned char
#define u16 unsigned short
#define u32 unsigned long
#define f32  float
#define d64  double

#define vs8  volatile signed char
#define vs16 volatile signed short
#define vs32 volatile signed long
#define vu8  volatile unsigned char
#define vu16 volatile unsigned short
#define vu32 volatile unsigned long
#define vf32 volatile float
#define vd64 volatile double

#define es8  extern signed char
#define es16 extern signed short
#define es32 extern signed long
#define eu8  extern unsigned char
#define eu16 extern unsigned short
#define eu32 extern unsigned long
#define ef32 extern float
#define ed64 extern double

#define evs8  extern volatile signed char
#define evs16 extern volatile signed short
#define evs32 extern volatile signed long
#define evu8  extern volatile unsigned char
#define evu16 extern volatile unsigned short
#define evu32 extern volatile unsigned long
#define evf32 extern volatile float
#define evd64 extern volatile double

#define bool u8
#define true 1
#define false 0

#ifndef NULL
#define NULL    ((void*)0)    
#endif

typedef unsigned char           uchar;
typedef signed   short          sint;
typedef unsigned short          usint;
typedef signed   long           lint;
typedef unsigned long           ulint;

//-----------------------------------------------------------------------------------
#undef   max
#define  max(a,b)       (((a) > (b)) ? (a) : (b))
#undef   min
#define  min(a,b)       (((a) < (b)) ? (a) : (b))

//-----------------------------------------------------------------------------------
#ifdef __RENESAS
	#define __flash			const
	#define __farflash		const
	#define __hugeflash		const
	#define APPFLASH 		const
#endif

#endif
