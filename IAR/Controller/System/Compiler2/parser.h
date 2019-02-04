//---------------------------------------------------------------------------
#ifndef __ParserH
#define __ParserH
//---------------------------------------------------------------------------
#include "..\System\Misc\types.h"
//---------------------------------------------------------------------------
#define   DIC_WORD_LEN	20
#define   DIC_WORD_NUM	37
#define   OP_WORD_LEN	10
#define   OP_WORD_NUM	19
#define   L_WORD_LEN	40
#define   L_WORD_NUM	100
#define   PROGRAM_LINES_NUM	1000
//---------------------------------------------------------------------------
const s8 operands[DIC_WORD_NUM][DIC_WORD_LEN]=
{
	"none",             // 0
	"ai",               // 1
	"ao",    			// 2
	"di",               // 3
	"do",				// 4
	"reg",				// 5
	"digit",			// 6
	"timer",			// 7
	"beep",				// 8
	"goto", 			// 9
	"go_rel", 			// A
	"pass_if_true",		// B
	"pass_if_false",	// C
    "pid.i",            // D
    "pid.p",            // E
    "pid.d",            // F
    "pid.ti",           // 10
    "pid.t0",           // 11
    "pid.enable",       // 12
    "pid.power",        // 13
    "pid.pow_min",      // 14
    "pid.pow_max",      // 15
    "call",             // 16
    "ret",             	// 17
    "end",             	// 18
    "mode",            	// 19
    "error",           	// 1A
    "pid.t3max",        // 1B
    "pid.open",      	// 1C
    "pid.close",     	// 1D
    "pid.p3",     		// 1E
    "season",     		// 1F
    "pid.channel", 		// 20
    "in_param", 		// 21
    "out_param", 		// 22
    "pid.slow", 		// 23
    "pid.fast", 		// 24
};
//---------------------------------------------------------------------------
const s8 operators[OP_WORD_NUM][OP_WORD_LEN]=
{
	"none",    			// 0
	"=",    			// 1
	"==",    			// 2
	">",    			// 3
	"<",    			// 4
	">=",    			// 5
	"<=",    			// 6
	"!=",    			// 7
	"&&",    			// 8
	"||",    			// 9
	"and",    			// 10
	"or",    			// 11
	"xor",    			// 12
	"not",    			// 13
   	"~",    			// 14
   	":",    			// 15
	"+",    			// 16
   	"-",    			// 17
   	"*",    			// 18    
};
//---------------------------------------------------------------------------
typedef struct
{
	s8 word[5][DIC_WORD_LEN];
	u16 index[5];
}TStrLine;
//---------------------------------------------------------------------------
//extern TStrLine strline;
//---------------------------------------------------------------------------
//void Int_Line_PreParser(s8 *in,TStrLine *out);
//void Int_Line_Parser(TStrLine *in,TProgLine *out);
//---------------------------------------------------------------------------
#endif
