//-----------------------------------------------------------------------------------
#ifdef __COMPILER2
//-----------------------------------------------------------------------------------
#include "..\main.h"
//#include "stdio.h"
//-----------------------------------------------------------------------------------
/*
M_00="+"
M_01="-"
M_02="/"
M_03="*"
M_04="="
M_05="^"
M_06="&"
M_07="|"
M_08="~"
M_09="!"
M_10="||"
M_11="&&"
M_12="=="
M_13="!="
M_14=">"
M_15="<"
M_16=">="
M_17="<="
M_18="++"
M_19="--"
M_20=">>"
M_21="<<"
*/
void Intr_Program_Line_Handle_Math()
{
	s32 tmp32_1;			
	s32 tmp32_2;
	s32 tmp32_3;
//	sprintf(outtxt,"\n%d",pline.fields.d);
	switch(pline.fields.d)
	{
		//----------------------------------------------------------------------
		case 4:
			switch(pline.fields.res.type)
			{
				//--- Error of controller --------------------------------------								
				case TYPE_REG+8:
					switch(pline.fields.op1.type)
					{
						case TYPE_S8+0:
						case TYPE_S8+1:
						case TYPE_S8+2:
						case TYPE_S8+3:
						case TYPE_S8+4:
						case TYPE_S8+5:
						case TYPE_S8+6:
						case TYPE_S8+7:
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
		
		case 0:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);			
			tmp32_3=tmp32_1 + tmp32_2;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 1:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
			tmp32_3=tmp32_1 - tmp32_2;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 2:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
			tmp32_3=tmp32_1 / tmp32_2;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 3:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
			tmp32_3=tmp32_1 * tmp32_2;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 5:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
			tmp32_3=tmp32_1 ^ tmp32_2;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 6:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
			tmp32_3=tmp32_1 & tmp32_2;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 7:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
			tmp32_3=tmp32_1 | tmp32_2;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 8:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
			tmp32_3=~tmp32_1;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 9:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
			tmp32_3=!tmp32_1;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 10:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
			tmp32_3=tmp32_1 || tmp32_2;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 11:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
			tmp32_3=tmp32_1 && tmp32_2;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 12:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
			tmp32_3=tmp32_1 == tmp32_2;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 13:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
			tmp32_3=tmp32_1 != tmp32_2;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 14:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
			tmp32_3=tmp32_1 > tmp32_2;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 15:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
			tmp32_3=tmp32_1 < tmp32_2;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 16:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
			tmp32_3=tmp32_1 >= tmp32_2;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 17:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
			tmp32_3=tmp32_1 <= tmp32_2;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 18:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
            tmp32_1++;
			tmp32_3=tmp32_1;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 19:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
            tmp32_1--;
			tmp32_3=tmp32_1;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 20:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
            tmp32_1=tmp32_1>>tmp32_2;
			tmp32_3=tmp32_1;
			set_operand(pline.fields.res,tmp32_3);
		break;
		case 21:
			tmp32_1=get_operand(pline.fields.op1);
			tmp32_2=get_operand(pline.fields.op2);
            tmp32_1=tmp32_1<<tmp32_2;
			tmp32_3=tmp32_1;
			set_operand(pline.fields.res,tmp32_3);
		break;		
	}
}
//-----------------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------------
