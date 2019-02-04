//-----------------------------------------------------------------------------------
#ifndef __COMPILER2
//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
void Intr_Program_Line_Handle_Logic()
{
	s32 tmp32_1;			
	s32 tmp32_2;		
	s32 tmp32_3;
	// Stop programm when End operation is executing;
	if(pline.fields.res.type==op_end_prog)
	{
		intr.status=int_Stop;
		return;
	}	
	switch(pline.fields.d)
	{
		case do_logical_more:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);	
			tmp32_3=tmp32_1 > tmp32_2;
			set_operand(pline.fields.res,tmp32_3);	
		break;

		case do_logical_less:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);			
			tmp32_3=tmp32_1 < tmp32_2;
			set_operand(pline.fields.res,tmp32_3);	
		break;		
		
		case do_logical_equal:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);			
			tmp32_3=tmp32_1 == tmp32_2;
			set_operand(pline.fields.res,tmp32_3);				
		break;	
		
		case do_logical_equal_or_more:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);			
			tmp32_3=tmp32_1 >= tmp32_2;
			set_operand(pline.fields.res,tmp32_3);				
		break;		

		case do_logical_equal_or_less:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);			
			tmp32_3=tmp32_1 <= tmp32_2;
			set_operand(pline.fields.res,tmp32_3);				
		break;			
	}
}
//-----------------------------------------------------------------------------------
/*
void Intr_Program_Line_Handle_Logic()
{
	s32 tmp32_1;			
	s32 tmp32_2;		
	// Stop programm when End operation is executing;
	if(pline.fields.res.type==op_end_prog)
	{
		intr.status=int_Stop;
		return;
	}	
	switch(pline.fields.d)
	{
		case do_logical_more:	// Set result operand equal to logical result of comparation
			switch(pline.fields.res.type)
			{
				case op_reg:
				//--- Registers ---------------------------------------------------
					tmp32_1=0;
					tmp32_2=0;
					tmp32_1=get_operand(pline.fields.op1);					
					tmp32_2=get_operand(pline.fields.op2);
					if(tmp32_1>tmp32_2)
						intr.reg[pline.fields.res.body.u16d]=1;
					else
						intr.reg[pline.fields.res.body.u16d]=0;											
				//---------------------------------------------------------------------
				break;	
			}					
		break;
		case do_logical_less:	// Set result operand equal to logical result of comparation
			switch(pline.fields.res.type)
			{
				case op_reg:
				//--- Registers ---------------------------------------------------
					tmp32_1=0;
					tmp32_2=0;
					tmp32_1=get_operand(pline.fields.op1);					
					tmp32_2=get_operand(pline.fields.op2);
//					__sprintf(outtxt,"\n\rOP1=");LongToStr(outtxt,(u32*)&(tmp32_1),0);			
//					__sprintf(outtxt," OP2=");LongToStr(outtxt,(u32*)&(tmp32_2),0);								
					if(tmp32_1<tmp32_2)
					{
						intr.reg[pline.fields.res.body.u8d]=1;
					}
					else
					{
						intr.reg[pline.fields.res.body.u8d]=0;											
					}
//					__sprintf(outtxt," RES=");LongToStr(outtxt,(u32*)&(intr.reg[pline.fields.res.body.u8d]),0);
//					__sprintf(outtxt," RES=");LongToStr(outtxt,(u32*)&(intr.reg[10]),0);
				//---------------------------------------------------------------------
				break;	
			}					
		break;
		case do_logical_equal:	// Set result operand equal to logical result of comparation
			switch(pline.fields.res.type)
			{
				case op_reg:
				//--- Registers ---------------------------------------------------
					tmp32_1=0;
					tmp32_2=0;
					tmp32_1=get_operand(pline.fields.op1);					
					tmp32_2=get_operand(pline.fields.op2);
//					__sprintf(outtxt,"Reg=");ByteToStr(outtxt,(u8*)&(intr.r16[pline.fields.op1.body.u8d]),1);					
//					LongToStr(outtxt,&tmp32_1,1);__sprintf(outtxt," ");LongToStr(outtxt,&tmp32_2,1);__sprintf(outtxt," ");
					if(tmp32_1==tmp32_2)
						intr.reg[pline.fields.res.body.u8d]=1;
					else
						intr.reg[pline.fields.res.body.u8d]=0;											
				//---------------------------------------------------------------------
				break;	
			}	
		break;				
		case do_logical_equal_or_more:	// Set result operand equal to logical result of comparation
			switch(pline.fields.res.type)
			{
				case op_reg:
				//--- Registers ---------------------------------------------------
					tmp32_1=0;
					tmp32_2=0;
					tmp32_1=get_operand(pline.fields.op1);					
					tmp32_2=get_operand(pline.fields.op2);	
//					__sprintf(outtxt,"Reg=");ByteToStr(outtxt,(u8*)&(intr.r16[pline.fields.op1.body.u8d]),1);					
//					LongToStr(outtxt,&tmp32_1,1);__sprintf(outtxt," ");LongToStr(outtxt,&tmp32_2,1);__sprintf(outtxt," ");
					if(tmp32_1>=tmp32_2)
						intr.reg[pline.fields.res.body.u8d]=1;
					else
						intr.reg[pline.fields.res.body.u8d]=0;											
				//---------------------------------------------------------------------
				break;	
			}			
		break;
	}
}
*/
//-----------------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------------
