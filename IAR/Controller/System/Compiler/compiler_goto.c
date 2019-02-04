//-----------------------------------------------------------------------------------
#ifndef __COMPILER2
//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
void Intr_Program_Line_Handle_GoTo()
{
//	s32 tmp32_1;			
//	s32 tmp32_2;		
	s32 tmp32;	
	// Stop programm when End operation is executing;
	if(pline.fields.res.type==op_end_prog)
	{
		intr.status=int_Stop;
		return;
	}
	// Result depended commands
	switch(pline.fields.res.type)
	{
		//--- Call     ---------------------------------------------------		
		case op_call:
			if(intr.stack_ptr<STACK_DEPTH)
			{
				intr.stack[intr.stack_ptr]=intr.addr;				
				intr.stack_ptr++;			
				intr.addr=CODE_START_ADDR+CODE_LINE_LEN*pline.fields.res.body.u16d;				
			}
		return;
		//---------------------------------------------------------------------		
		//--- Return     ---------------------------------------------------		
		case op_ret:
			if(intr.stack_ptr!=0)
			{
				intr.stack_ptr--;			
				intr.addr=intr.stack[intr.stack_ptr];
			}
		return;
		//---------------------------------------------------------------------		
		//--- Goto abs ---------------------------------------------------
		case op_go_abs:		
			intr.addr=CODE_START_ADDR+CODE_LINE_LEN*pline.fields.res.body.u16d;
//			LongToStr(outtxt,(u32*)&intr.addr,1);
		return;			
		//---------------------------------------------------------------------
		//--- Goto rel ---------------------------------------------------
		case op_go_rel:		
			intr.addr=intr.addr+CODE_LINE_LEN*(pline.fields.res.body.s16d-1);
		return;			
		//---------------------------------------------------------------------
		//--- Goto if true ---------------------------------------------------		
		case op_pass_if_true:
			tmp32=get_operand(pline.fields.op1);
			if(tmp32!=0)
			{
				intr.addr=intr.addr+CODE_LINE_LEN;
			}
		return;
		//---------------------------------------------------------------------		
		//--- Goto if flase ---------------------------------------------------		
		case op_pass_if_false:
			tmp32=0;	
			tmp32=get_operand(pline.fields.op1);
			if(tmp32==0)
			{
				intr.addr=intr.addr+CODE_LINE_LEN;		
			}
		return;
		//---------------------------------------------------------------------		
	}
}
//-----------------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------------
