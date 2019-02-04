//-----------------------------------------------------------------------------------
#ifdef __COMPILER2
//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
/*
RW_00="for"
RW_01="while"
RW_02="if"
RW_03="else"
RW_04="switch"
RW_05="return"
RW_06="case"
RW_07="default"
RW_08="break"
RW_09="goto"
RW_10="call"
RW_11="ret"
*/
void Intr_Program_Line_Handle_GoTo()
{
	s32 tmp32;
	// Result depended commands
	switch(pline.fields.d)
	{
		//--- Call     ---------------------------------------------------		
		case OPERATION_WORD+10:
			if(intr.stack_ptr<STACK_DEPTH)
			{
				intr.stack[intr.stack_ptr]=intr.addr;				
				intr.stack_ptr++;			
				intr.addr=CODE_START_ADDR+CODE_LINE_LEN*pline.fields.op1.body.u32d;
			}
		return;
		//---------------------------------------------------------------------
		//--- Ret     ---------------------------------------------------		
		case OPERATION_WORD+11:
			if(intr.stack_ptr!=0)
			{
				intr.stack_ptr--;			
				intr.addr=intr.stack[intr.stack_ptr];
			}
		return;
		//---------------------------------------------------------------------
		//--- Goto ---------------------------------------------------
		case OPERATION_WORD+9:
			intr.addr=CODE_START_ADDR+CODE_LINE_LEN*(pline.fields.op1.body.u32d);
		return;			
		//---------------------------------------------------------------------
		//--- if ---------------------------------------------------
		case OPERATION_WORD+2:
        	tmp32=get_operand(pline.fields.op1);
            if(tmp32)return;
			intr.addr+=CODE_LINE_LEN;
		return;
		//---------------------------------------------------------------------
	}
}
//-----------------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------------
