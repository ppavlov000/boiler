//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Unit1.h"
#include "Parser.h"
/*
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
*/
//---------------------------------------------------------------------------
s8 operands[DIC_WORD_NUM][DIC_WORD_LEN]=
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
	"pass_if_false",	// B
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
s8 operators[OP_WORD_NUM][OP_WORD_LEN]=
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
	s8 str[L_WORD_LEN];
    u16 pos;
}TMyLabel;
TMyLabel labels[L_WORD_NUM];
u16 lptr;
TProgLine prog[PROGRAM_LINES_NUM];
u16 pptr;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/*
AnsiString	eplName;
u8 label[100];
u8 lptr;
int stg_ptr;
FILE *bin_prog;
s8	l[80];
*/
u8 Status=0;
//---------------------------------------------------------------------------
TStrLine strline;
TProgLineFieldsParser parsing_pl;
AnsiString a;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void Int_Line_PreParser(s8 *in,TStrLine *out)
{
	s8 word[DIC_WORD_LEN];
	s8 index[DIC_WORD_LEN];
    u8 i=0,j=0;
    u8 type=0;
    if(Status!=0)return;
	memset(word,0,sizeof(word));
	memset(out,0,sizeof(TStrLine));
    if(*in==0)
    {
    	Status=1;
        return;
    }
	while(*in!=0)
    {
    	switch(*in)
        {
        	case ' ':
            	if((type==0)||(type==1))	// operand
                {
					strcpy((s8*)out->word[j],word);
                    j++;
                    i=0;
					memset(word,0,sizeof(word));
                }
            break;
        	case '[':
            	if(type==0)	// operand
                {
					strcpy((s8*)out->word[j],word);
                    i=0;
                    type=2;
					memset(index,0,sizeof(index));
                    break;
                }
                else
                	MessageBox(NULL,"Error","Error in code",MB_OK);
            break;
        	case ']':
				if(type==2)
                {
                	a=AnsiString(index);
                    out->index[j]=a.ToInt();
                    j++;
					memset(word,0,sizeof(word));
                    i=0;
				}
                else
                	MessageBox(NULL,"Error","Error in code",MB_OK);
            break;
        	case '=':
        	case '+':
        	case '-':
        	case '*':                                    
        	case '!':
        	case '>':
        	case '<':
        	case '|':
        	case '&':
            	if(type==0)	// operand
                {
					strcpy((s8*)out->word[j],word);
                    i=0;
					memset(word,0,sizeof(word));
                    j++;
                }
            	type=1;
                word[i]=*in;i++;
                word[i]=0;
            break;
        	case ':':
				strcpy((s8*)out->word[j],word);
				memset(word,0,sizeof(word));
                word[0]=*in;
                j++;
				strcpy((s8*)out->word[j],word);
                return;
            break;

        	case ';':
        	case 13:
            	if(type!=2)
	            	strcpy((s8*)out->word[j],word);
                return;
            break;
            default:
				if(type==1)
                {
					strcpy((s8*)out->word[j],word);
                    i=0;
					memset(word,0,sizeof(word));
                    j++;
					type=0;
                }
				if(type==0)
                {
	            	word[i]=*in;
    	            i++;
                }
				if(type==2)
                {
	            	index[i]+=*in;
    	            i++;
				}
            break;
        }
    	in++;
    }
}
//---------------------------------------------------------------------------
int Int_Search_Operand(s8 *in)
{
	int i,j,s;
    s8 *ptr;
    if(Status!=0)return -1;
	for(i=0;i<DIC_WORD_NUM;i++)
    {
        if(strcmp(in,operands[i])==0)
        	return i;
    }
    a=AnsiString(in);
    s=a.ToIntDef(0xffffffff);
    if(s!=0xffffffff)
    {
   		return op_digit;
    }
    else
		return -1;
}
//---------------------------------------------------------------------------
int Int_Search_Operator(s8 *in)
{
	int i,j,s;
    s8 *ptr;
    if(Status!=0)return -1;
	for(i=0;i<OP_WORD_NUM;i++)
    {
    	s=1;
        if(strcmp(in,operators[i])==0)
        	return i;
    }
	return -1;
}
//---------------------------------------------------------------------------
bool Int_Line_Label_Search(TStrLine *in,s8 *out)
{
	int i;
    int res;
    AnsiString err;
    if(Status!=0)return false;
    //---------- Operator 1 ----------------
    res=Int_Search_Operator((s8*)in->word[1]);
    if(res==do_label)
    {
    	strcpy(out,(s8*)in->word[0]);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
void Int_Line_Parser(TStrLine *in,TProgLineFieldsParser *out)
{
	int i;
    int res;
    AnsiString err;
    if(Status!=0)return;
    memset(out,0,sizeof(TProgLineFieldsParser));
    //---------- Result ----------------
    err="Error in line parsing\n\rSearching result operand\n\r> "+AnsiString((s8*)in->word[0]);
    res=Int_Search_Operand((s8*)in->word[0]);
    if(res==-1)
    {
    	MessageBox(NULL,err.c_str(),"Error",MB_OK);
        Status=1;
        return;
    }
   	out->res.type=res;
    out->res.body.u32d=in->index[0];
    switch(res)
    {
    	case op_go_abs:
    	case op_call:
        	strcpy(out->label,(s8*)in->word[1]);
        return;

    	case op_ret:
    	case op_end_prog:
       	return;

    	case op_go_rel:
		    //---------- Op1 ----------------
		    err="Error in line parsing\n\rSearching pass case\n\r> "+AnsiString((s8*)in->word[0]);
		    res=Int_Search_Operand((s8*)in->word[1]);
		    if(res==-1)
		    {
		    	MessageBox(NULL,err.c_str(),"Error",MB_OK);
		        Status=1;
		        return;
		    }
		   	out->op1.type=res;
		    out->op1.body.u32d=in->index[1];
		    if(res==op_digit)
		    {
			    a=AnsiString((s8*)in->word[1]);
				out->op1.body.s32d=a.ToInt();
		    }
       	return;
        
    	case op_pass_if_true:
    	case op_pass_if_false:
		    //---------- Op1 ----------------
		    err="Error in line parsing\n\rSearching pass case\n\r> "+AnsiString((s8*)in->word[0]);
		    res=Int_Search_Operand((s8*)in->word[1]);
		    if(res==-1)
		    {
		    	MessageBox(NULL,err.c_str(),"Error",MB_OK);
		        Status=1;
		        return;
		    }
		   	out->op1.type=res;
		    out->op1.body.u32d=in->index[1];
		    if(res==op_digit)
		    {
			    a=AnsiString((s8*)in->word[1]);
				out->op1.body.s32d=a.ToInt();
		    }
        return;
    }
    //---------- Operator 1 ----------------
    err="Error in line parsing\n\rSearching operator 1\n\r> "+AnsiString((s8*)in->word[0]);
    res=Int_Search_Operator((s8*)in->word[1]);
    if(res==-1)
    {
    	MessageBox(NULL,err.c_str(),"Error",MB_OK);
        Status=1;
        return;
    }
   	out->d0=res;
    //---------- Op1 ----------------
    err="Error in line parsing\n\rSearching operand 1\n\r> "+AnsiString((s8*)in->word[0]);
    res=Int_Search_Operand((s8*)in->word[2]);
    if(res==-1)
    {
    	MessageBox(NULL,err.c_str(),"Error",MB_OK);
        Status=1;
        return;
    }
   	out->op1.type=res;
    out->op1.body.u32d=in->index[2];
    if(res==op_digit)
    {
	    a=AnsiString((s8*)in->word[2]);
		out->op1.body.s32d=a.ToInt();
    }
    //---------- Operator 2 ----------------
    err="Error in line parsing\n\rSearching operator 2\n\r> "+AnsiString((s8*)in->word[0]);
    res=Int_Search_Operator((s8*)in->word[3]);
    if(res==-1)
    {
//    	MessageBox(NULL,err.c_str(),"Error",MB_OK);
//        Status=1;
//        return;
    }
    else
    {
	   	out->d1=res;
    }
    //---------- Op2 ----------------
    err="Error in line parsing\n\rSearching operand 2\n\r> "+AnsiString((s8*)in->word[0]);
    res=Int_Search_Operand((s8*)in->word[4]);
    if(res==-1)
    {
//    	MessageBox(NULL,err.c_str(),"Error",MB_OK);
//        Status=1;
//        return;
    }
    else
    {
	   	out->op2.type=res;
    	out->op2.body.u32d=in->index[4];
	    if(res==op_digit)
    	{
		    a=AnsiString((s8*)in->word[4]);
			out->op2.body.s32d=a.ToInt();
	    }
    }
}
//---------------------------------------------------------------------------
int Int_Get_Label(s8 *in)
{
    int res;
	int i,j,s;
    s8 *ptr;
    if(Status!=0)return -1;
	for(i=0;i<PROGRAM_LINES_NUM;i++)
    {
        if(strcmp(in,labels[i].str)==0)
        	return labels[i].pos;
    }
	return -1;    
}
//---------------------------------------------------------------------------
void Int_Line_Interpreter(TProgLineFieldsParser *in, TProgLine  *out)
{
	int i;
    int res;
    AnsiString err;
    if(Status!=0)return;
    out->fields.res=in->res;
    out->fields.op1=in->op1;
    out->fields.op2=in->op2;
    if(in->d1!=do_none)
    	out->fields.d=in->d1;
    else
    	out->fields.d=in->d0;
    switch(in->res.type)
    {
    	case op_go_abs:
    	case op_call:        
        	out->fields.res.body.s32d=Int_Get_Label(in->label);
        break;
    }
}
//---------------------------------------------------------------------------
void Int_Init()
{
	memset(labels,0,sizeof(labels));
	memset(prog,0,sizeof(prog));
	lptr=pptr=0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


