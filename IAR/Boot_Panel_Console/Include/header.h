#ifndef __HEADER
#define __HEADER
//---------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------
typedef struct
{
	u8	Second;
	u8	Minute;	
	u8	Hour;	
	u8	Day;	
	u8	Date;	
	u8 	Month;	
	u8	Year;	
}TTimeFullFields;

typedef union
{
	TTimeFullFields field;
	u8	data[7];
}TTimeFull;
//-------------------------------------------------------------------------------------------
typedef struct
{
  u8  		Name[103];
  u32		HW_Version;
  u32		SW_Version;
  TTimeFull Time;
  u8  		WH_Update;
  u8  		Flag;
  u32 		Length;
  u16 		CRC_D;	// CRC of data
  u16 		CRC_H;	// CRC of header
}THead;
//-------------------------------------------------------------------------------------------
#endif

