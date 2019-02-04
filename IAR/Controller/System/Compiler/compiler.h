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
#define CODE_LINE_LEN	sizeof(TProgLineFields)
#define CODE_ADDR	PLM_FLASH_START
#define CODE_START_ADDR	CODE_ADDR
//-----------------------------------------------------------------------------------
#define CODE_MAIN_ADDR	CODE_ADDR
#define CODE_IRQ0_ADDR	CODE_MAIN_ADDR+CODE_LINE_LEN
#define CODE_IRQ1_ADDR	CODE_MAIN_ADDR+2*CODE_LINE_LEN
#define CODE_IRQ2_ADDR	CODE_MAIN_ADDR+3*CODE_LINE_LEN
#define CODE_IRQ3_ADDR	CODE_MAIN_ADDR+4*CODE_LINE_LEN
//-----------------------------------------------------------------------------------
#define STACK_DEPTH			20
#define REGISTERS_MAX		20
#define TIMERS_MAX			8
//-----------------------------------------------------------------------------------
#define program_run		0x01
#define program_stop	0x00
//-----------------------------------------------------------------------------------
// Operand types
#define	op_none			0x00	// No operand at all
#define	op_ai			0x01  	// "AIxx"
#define	op_ao			0x02    // "AOxx"
#define	op_di			0x03    // "DIxx"
#define	op_do			0x04    // "DOxx"
#define	op_reg			0x05    // "Rxx"
#define	op_digit		0x06

#define	op_time_delay	0x07      // mseconds
#define	op_time_beep	0x08     // mseconds of beep signal

#define	op_go_abs		0x09
#define	op_go_rel		0x0a
#define	op_pass_if_true 	0x0b
#define op_pass_if_false 	0x0c

#define op_pid_i	 	0x0d
#define op_pid_p	 	0x0e
#define op_pid_d	 	0x0f
#define op_pid_ti	 	0x10
#define op_pid_t0	 	0x11
#define op_pid_ena	 	0x12
#define op_pid_pow	 	0x13
#define op_pid_pow_min 	0x14
#define op_pid_pow_max 	0x15
#define	op_call			0x16
#define	op_ret			0x17
#define	op_end_prog		0x18
#define	op_mode			0x19
#define	op_error		0x1a

#define op_pid_t3max 	0x1b
#define op_pid_open	 	0x1c
#define op_pid_close 	0x1d
#define op_pid_p3	 	0x1e
#define op_season	 	0x1f
#define op_pid_channel 	0x20
#define op_in_parameters 	0x21
#define op_out_parameters 	0x22
#define op_pid_slow 	0x23
#define op_pid_fast 	0x24

#define op_pid_hc	 	0x25
#define op_pid_reserve 	0x26

#define op_fan_channel 	0x27
#define op_fan_t0		0x28
#define op_fan_mode		0x29
#define op_fan_lvl		0x2A
#define op_fan_low		0x2B
#define op_fan_medium	0x2C
#define op_fan_high		0x2D
#define op_fan_hyst		0x2E
#define op_fan_time		0x2F
#define op_fan_day		0x30
/*
    "pid.hc", 			// 25
    "pid.reserve",		// 26

    "fan.channel",		// 27
    "fan.t0",			// 28
    "fan.mode",			// 29
    "fan.lvl",			// 2A
    "fan.low",			// 2B
    "fan.medium",		// 2C
    "fan.high",			// 2D
    "fan.hysteresis",	// 2E
    "fan.time",			// 2F
    "fan.day_night",	// 30
*/	
// Operations types
#define	do_none						0x00	// No operation at all
#define	do_equal					0x01	// =
#define	do_logical_equal	  		0x02	// =
#define	do_logical_more				0x03	// >
#define	do_logical_less				0x04	// <
#define	do_logical_equal_or_more	0x05	// >=
#define	do_logical_equal_or_less	0x06	// <=
#define	do_logical_not_equal		0x07	// <=
#define	do_logical_and				0x08	// &&
#define	do_logical_or				0x09	// ||
#define	do_and						0x0a	// and
#define	do_or						0x0b	// or
#define	do_xor						0x0c	// xor
#define	do_not						0x0d	// not
#define	do_inv						0x0e	// ~
#define	do_label					0x0f	// :
#define	do_summ						0x10	// +
#define	do_sub						0x11	// -
#define	do_mul						0x12	// *
//-----------------------------------------------------------------------------------
// Code line type
// operator;op1;op2;op3;
// Operand type;body;
typedef union
{
	u8	data[4];
	u8	u8d;
	u16	u16d;
	u32	u32d;		
	s8	s8d;
	s16	s16d;
	s32	s32d;			
}TBody;
//-------------------------------------
typedef struct
{
	u8		type;
	TBody	body;
}TOperandFields;
//-------------------------------------
typedef struct
{
	u8	d;
	TOperandFields	op1;	
	TOperandFields	op2;	
	TOperandFields	res;
}TProgLineFields;
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
	s16	in_params[PARAMETERS_MAX];	
	s16	out_params[PARAMETERS_MAX];	
	s32	reg[REGISTERS_MAX];
	u32	t32[TIMERS_MAX];		
	u32	stack[STACK_DEPTH];	
	u8 stack_ptr;
	u32 addr;
	INT_STATUS status;
	TBody int_var;
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
s32 get_operand(TOperandFields op);
void set_operand(TOperandFields op,s32 value);
//-----------------------------------------------------------------------------------
#endif
