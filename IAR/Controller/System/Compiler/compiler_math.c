//-----------------------------------------------------------------------------------
#ifndef __COMPILER2
//-----------------------------------------------------------------------------------
#include "..\main.h"
//-----------------------------------------------------------------------------------
void Intr_Program_Line_Handle_Math()
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
		//----------------------------------------------------------------------
		case do_equal:					
			switch(pline.fields.res.type)
			{
				//--- Error of controller --------------------------------------								
				case op_error:
					switch(pline.fields.op1.type)
					{
						case op_digit:	
							error_insert(pline.fields.op1.body.s16d);
						break;
					}									
				break;				
				//--------------------------------------------------------------
				default:
					tmp32_1=get_operand(pline.fields.op1);
					set_operand(pline.fields.res,tmp32_1);
				break;
			}
		break;
		
		case do_summ:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);			
			tmp32_3=tmp32_1 + tmp32_2;
			set_operand(pline.fields.res,tmp32_3);
		break;
		
		case do_sub:	
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);			
			tmp32_3=tmp32_1 - tmp32_2;
			set_operand(pline.fields.res,tmp32_3);
		break;
		
	}
}
//-----------------------------------------------------------------------------------
/*
void Intr_Program_Line_Handle_Math_old()
{
	u8 tmp;
	u16 tmp16;	
	s32 tmp32_1;			
	s32 tmp32_2;		
	if(pline.fields.res.type==op_end_prog)
	{
		intr.status=program_stop;
		return;
	}
	switch(pline.fields.d)
	{
		case do_equal:	// Set result operand equal to operand 1
			switch(pline.fields.res.type)
			{
				case op_mode:
				//--- Mode of controller ----------------------------------------------				
					switch(pline.fields.op1.type)
					{
						case op_digit:	MenuRegs.mode_of_operation=pline.fields.op1.body.u32d; newmenuitem=1; break;
					}									
				//---------------------------------------------------------------------				
				break;
				case op_error:
				//--- Error of controller ----------------------------------------------				
					switch(pline.fields.op1.type)
					{
						case op_digit:	
							error_insert(pline.fields.op1.body.s16d);
						break;
					}									
				//---------------------------------------------------------------------				
				break;
				case op_reg:
				//--- Registers ---------------------------------------------------
					tmp16=0;
					intr.reg[pline.fields.res.body.u16d]=get_operand(pline.fields.op1);
				//---------------------------------------------------------------------
				break;				
				case op_time_delay:
				//--- time delay ms ---------------------------------------------------
//					tmp32=0;
					switch(pline.fields.op1.type)
					{
						case op_digit:	intr.t32[pline.fields.res.body.u16d]=pline.fields.op1.body.u32d;break;
						case op_reg:	intr.t32[pline.fields.res.body.u16d]=intr.reg[pline.fields.op1.body.u16d]; break;						
					}
				//---------------------------------------------------------------------
				break;				
				case op_time_beep:
				//--- time delay ms ---------------------------------------------------
//					tmp32=0;
					switch(pline.fields.op1.type)
					{
						case op_digit:	BuzzerTime=pline.fields.op1.body.u16d; break;
						case op_reg:	BuzzerTime=intr.reg[pline.fields.op1.body.u16d];break;												
					}
				//---------------------------------------------------------------------
				break;				
				case op_ao:
				//--- Analog output ---------------------------------------------------
					tmp16=0;
					tmp16=get_operand(pline.fields.op1);
					io.aoutput[pline.fields.res.body.u8d]=tmp16;
				//---------------------------------------------------------------------
				break;				
				case op_do:
				//--- Digital output ---------------------------------------------------				
					tmp=0;
					switch(pline.fields.op1.type)
					{
						case op_digit: 	tmp=pline.fields.op1.body.u8d & 1;break;
						case op_di: 	tmp=(io.din>>pline.fields.op1.body.u8d) & 1;break;
						case op_reg:	tmp=intr.reg[pline.fields.op1.body.u16d]& 1;break;
						case op_pid_open:	tmp=pid[pline.fields.op1.body.u16d].open;break;						
						case op_pid_close:	tmp=pid[pline.fields.op1.body.u16d].close;break;												
					}				
					tmp16=1<<pline.fields.res.body.u8d;					
					if(tmp!=0)
						io.dout|=tmp16;
					else
						io.dout&=~tmp16;
				//---------------------------------------------------------------------						
				break;		
				case op_pid_p:
				//--- time delay ms ---------------------------------------------------
					switch(pline.fields.op1.type)
					{
						case op_digit:	pid[pline.fields.res.body.u8d].p=pline.fields.op1.body.s32d; break;
					}
				//---------------------------------------------------------------------
				break;						
				case op_pid_i:
				//--- time delay ms ---------------------------------------------------
					switch(pline.fields.op1.type)
					{
						case op_digit:	pid[pline.fields.res.body.u8d].i=pline.fields.op1.body.s32d; break;
					}
				//---------------------------------------------------------------------
				break;		
				case op_pid_d:
				//--- time delay ms -------------	--------------------------------------
					switch(pline.fields.op1.type)
					{
						case op_digit:	pid[pline.fields.res.body.u8d].d=pline.fields.op1.body.s32d; break;
					}
				//---------------------------------------------------------------------
				break;		
				case op_pid_ti:
				//--- time delay ms ---------------------------------------------------
					switch(pline.fields.op1.type)
					{
						case op_digit:	pid[pline.fields.res.body.u8d].ti=pline.fields.op1.body.u32d; break;
					}
				//---------------------------------------------------------------------
				break;		
				case op_pid_t0:
				//--- time delay ms ---------------------------------------------------
					switch(pline.fields.op1.type)
					{
						case op_digit:	
						  pid[pline.fields.res.body.u8d].t0=pline.fields.op1.body.u32d;
//						  MenuRegs.t0=pline.fields.op1.body.u32d;
						break;
					}
				//---------------------------------------------------------------------
				break;		
				case op_pid_ena:
				//--- time delay ms ---------------------------------------------------
					switch(pline.fields.op1.type)
					{
						case op_digit:	pid[pline.fields.res.body.u8d].mode=pline.fields.op1.body.u8d; break;
					}
				//---------------------------------------------------------------------
				break;		
				case op_pid_pow_min:
				//--- time delay ms ---------------------------------------------------
					switch(pline.fields.op1.type)
					{
						case op_digit:	pid[pline.fields.res.body.u8d].power_min=pline.fields.op1.body.s32d; break;
					}
				//---------------------------------------------------------------------
				break;		
				case op_pid_pow_max:
				//--- time delay ms ---------------------------------------------------
					switch(pline.fields.op1.type)
					{
						case op_digit:	pid[pline.fields.res.body.u8d].power_max=pline.fields.op1.body.s32d; break;
					}
				//---------------------------------------------------------------------
				break;						
				case op_pid_t3max:
				//--- time delay ms ---------------------------------------------------
					switch(pline.fields.op1.type)
					{
						case op_digit:	pid[pline.fields.res.body.u8d].t3max=pline.fields.op1.body.u16d; break;
					}
				//---------------------------------------------------------------------
				break;			
				case op_pid_p3:
				//--- time delay ms ---------------------------------------------------
					switch(pline.fields.op1.type)
					{
						case op_digit:	pid[pline.fields.res.body.u8d].p3=pline.fields.op1.body.s16d; break;
					}
				//---------------------------------------------------------------------
				break;			
				case op_pid_pow:
				//--- time delay ms ---------------------------------------------------
					switch(pline.fields.op1.type)
					{
						case op_digit:	
							pid[pline.fields.res.body.u8d].power=pline.fields.op1.body.s32d;
//							acc2[pline.fields.res.body.u8d]=pline.fields.op1.body.s32d;
						break;
					}
				//---------------------------------------------------------------------
				break;							
				case op_pid_channel:
				//--- time delay ms ---------------------------------------------------
					switch(pline.fields.op1.type)
					{
						case op_digit:	pid[pline.fields.res.body.u8d].channel=pline.fields.op1.body.u8d; break;
					}
				//---------------------------------------------------------------------
				break;			
				case op_season:
				//--- 0-Summer 1 Winter ---------------------------------------------------
				MenuRegs.Season=get_operand(pline.fields.op1);
				//---------------------------------------------------------------------
				break;												
			}
		break;
		case do_summ:	// Set result operand equal to operand 1
			switch(pline.fields.res.type)
			{
				case op_reg:
				//--- Registers ---------------------------------------------------
					tmp32_1=0;
					tmp32_2=0;			
					tmp32_1=get_operand(pline.fields.op1);
					tmp32_2=get_operand(pline.fields.op2);
					tmp32_1+=tmp32_2;
					intr.reg[pline.fields.res.body.u16d]=tmp32_1;
				//---------------------------------------------------------------------
				break;	
			}	
		break;
		case do_sub:	// Set result operand equal to operand 1
			switch(pline.fields.res.type)
			{
				case op_reg:
				//--- Registers ---------------------------------------------------
					tmp32_1=0;
					tmp32_2=0;			
//					WordToStr(outtxt,(u16*)&intr.r16[pline.fields.res.body.u16d],1);__sprintf(outtxt," ");					
					tmp32_1=get_operand(pline.fields.op1);
					tmp32_2=get_operand(pline.fields.op2);					
//					LongToStr(outtxt,&tmp32_1,1);__sprintf(outtxt," ");LongToStr(outtxt,&tmp32_2,1);__sprintf(outtxt," ");					
					tmp32_1-=tmp32_2;
//					LongToStr(outtxt,&tmp32_1,1);__sprintf(outtxt," ");ByteToStr(outtxt,&pline.fields.res.body.u8d,1);__sprintf(outtxt," ");										
					intr.reg[pline.fields.res.body.u16d]=tmp32_1;
//					WordToStr(outtxt,(u16*)&intr.r16[pline.fields.res.body.u8d],1);__sprintf(outtxt," ");						
				//---------------------------------------------------------------------
				break;	
			}			
		break;
		case do_mul:	// Set result operand equal to operand 1
			switch(pline.fields.res.type)
			{
				case op_reg:
				//--- Registers ---------------------------------------------------
					tmp32_1=0;
					tmp32_2=0;			
//					WordToStr(outtxt,(u16*)&intr.r16[pline.fields.res.body.u16d],1);__sprintf(outtxt," ");					
					tmp32_1=get_operand(pline.fields.op1);
					tmp32_2=get_operand(pline.fields.op2);					
					intr.reg[pline.fields.res.body.u16d]=tmp32_1*tmp32_2;
//					WordToStr(outtxt,(u16*)&intr.r16[pline.fields.res.body.u16d],1);__sprintf(outtxt," ");
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
