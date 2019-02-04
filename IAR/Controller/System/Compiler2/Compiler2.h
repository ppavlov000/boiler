#ifndef __INTERPRETATOR
#define __INTERPRETATOR
//-----------------------------------------------------------------------------------
#include "..\Misc\types.h"
#include "..\Misc\header.h"
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
//-----------------------------------------------------------------------------------
#define CODE_LINE_LEN		sizeof(TProgLineFields)
#define CODE_ADDR	PLM_FLASH_START
#define CODE_START_ADDR	PLM_FLASH_START + 100*sizeof(TVarBin)
#define DATA_START_ADDR	PLM_FLASH_START
//-----------------------------------------------------------------------------------
#define OPERATION_MATH	0
#define OPERATION_WORD	100
//-----------------------------------------------------------------------------------
#define STACK_DEPTH			20
#define REGISTERS_MAX		20
#define TIMERS_MAX			8
#define MEMORY_MAX			100
//-----------------------------------------------------------------------------------
#define program_run		0x01
#define program_stop	0x00
//-----------------------------------------------------------------------------------
// Data types
#define TYPE_NOTKNOWN     0
// Digits
#define TYPE_S8           1
#define TYPE_U8           2
#define TYPE_S16          3
#define TYPE_U16          4
#define TYPE_S32          5
#define TYPE_U32          6
#define TYPE_F32          7
// Variables
#define TYPE_VAR          10
// Sys registers
#define TYPE_REG          20
#define TYPE_AI
#define TYPE_AO
#define TYPE_DI
#define TYPE_DO
#define TYPE_TIMER
#define TYPE_IN_PARAM
#define TYPE_OUT_PARAM
#define TYPE_FAN
#define TYPE_PID
//-----------------------------------------------------------------------------------
typedef union
{
	u8		data[4];
	u8		u8d;
	u16		u16d;
	u32		u32d;
	s8		s8d;
	s16		s16d;
	s32		s32d;
	f32		f32d;
}TBody32;
//-------------------------------------
typedef struct
{
	u8		type;
	u8		index;
	TBody32	body;
}TOperandFields32;
//-------------------------------------
typedef struct
{
	u32					line;
	u8					d;
	TOperandFields32	op1;
	TOperandFields32	op2;
	TOperandFields32	res;
}TProgLineFields;
//-------------------------------------
//#define TDBGProgLine TProgLineFields
//----------------------------------------
typedef struct
{
	TBody32 value;      // initial value
    u8 	type[2];		// [0] - char... [1] - signed unsigned
    u16 offset;			// Offset in local memory
}TVarBin;
//-------------------------------------
typedef union
{
	TProgLineFields	fields;
	u8	data[CODE_LINE_LEN];
}TProgLine;
//-------------------------------------
typedef enum {
  int_Stop,
  int_Run,
  int_Warning,
  int_Brakedown,
  int_Bad_Prog,	
}INT_STATUS;
//-------------------------------------

typedef struct
{
	u8	mem[MEMORY_MAX];
	s16	in_params[PARAMETERS_MAX];
	s16	out_params[PARAMETERS_MAX];
	s32	reg[REGISTERS_MAX];
	s32	acc;
	u32	t32[TIMERS_MAX];
	u32	stack[STACK_DEPTH];
	u8 stack_ptr;
	u32 addr;
	INT_STATUS status;
	TVarBin int_var[2];
}TInterpretatorRegisters;
//-----------------------------------------------------------------------------------
extern TProgLine pline;
extern u8 Program_Valid;
//-----------------------------------------------------------------------------------
void Intr_Init();
void Intr_Handle();
void Intr_Program_Line_Handle();
void Intr_Program_Start();
void Intr_Program_Stop();
void Intr_Program_Line_Handle_GoTo();
void Intr_Program_Line_Handle_Math();
void Intr_Program_Line_Handle_Logic();
void Intr_Program_Line_Handle_Misc();
void Intr_IRQ0_Start();
void Intr_IRQ1_Start();
void Intr_IRQ2_Start();
void Intr_IRQ3_Start();
s32 get_operand(TOperandFields32 op);
void set_operand(TOperandFields32 op,s32 value);
//-----------------------------------------------------------------------------------
#endif
