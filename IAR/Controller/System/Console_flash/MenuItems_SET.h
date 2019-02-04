#ifndef __SET
#define __SET
//-----------------------------------------------------------------------------------
#include "..\main.h"
#include "MenuItems_SERVICE.h"
//-----------------------------------------------------------------------------------
extern in_flash TCMenuItem _Set;
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Set_ID_NUMBER=
{
	&Slovar[10][0],NULL,4,
	Set_ID,		
	NULL,
	NULL,		
	NULL,
};
in_flash TCMenuItem _Set_ID=
{
	&Slovar[57][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_ID_NUMBER,
	NULL,
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Set_PID_Fast_Value=
{
	&Slovar[10][0],NULL,4,
	Set_Pid_Fast,		
	NULL,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Set_PID_Fast=
{
	&Slovar[56][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_PID_Fast_Value,	
	NULL,	
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Set_PID_Slow_Value=
{
	&Slovar[10][0],NULL,4,
	Set_Pid_Slow,		
	NULL,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Set_PID_Slow=
{
	&Slovar[55][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_PID_Slow_Value,	
	&_Set_PID_Fast,	
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Set_PID_Channel_Value=
{
	&Slovar[10][0],NULL,4,
	Set_Pid_Channel,		
	NULL,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Set_PID_Channel=
{
	&Slovar[42][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_PID_Channel_Value,	
	&_Set_PID_Slow,	
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Set_PID_Power_Mode_Value=
{
	&Slovar[10][0],NULL,4,
	Set_Pid_Mode,		
	NULL,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Set_PID_Power_Mode=
{
	&Slovar[48][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_PID_Power_Mode_Value,	
	&_Set_PID_Channel,	
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Set_PID_Power_Min_Value=
{
	&Slovar[10][0],NULL,4,
	Set_Pid_Power_Min,		
	NULL,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Set_PID_Power_Min=
{
	&Slovar[47][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_PID_Power_Min_Value,	
	&_Set_PID_Power_Mode,	
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Set_PID_Power_Value=
{
	&Slovar[10][0],NULL,4,
	Set_Pid_Power,		
	NULL,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Set_PID_Power=
{
	&Slovar[46][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_PID_Power_Value,	
	&_Set_PID_Power_Min,	
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Set_PID_Diff_Value=
{
	&Slovar[10][0],NULL,4,
	Set_Pid_Diff,		
	NULL,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Set_PID_Diff=
{
	&Slovar[45][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_PID_Diff_Value,	
	&_Set_PID_Power,	
};
//------------------------------------
in_flash TCMenuItem _Set_PID_Int_Value=
{
	&Slovar[10][0],NULL,4,
	Set_Pid_Int,		
	NULL,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Set_PID_Int=
{
	&Slovar[44][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_PID_Int_Value,	
	&_Set_PID_Diff,	
};
//------------------------------------
in_flash TCMenuItem _Set_PID_Prop_Value=
{
	&Slovar[10][0],NULL,4,
	Set_Pid_Prop,		
	NULL,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Set_PID_Prop=
{
	&Slovar[43][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_PID_Prop_Value,	
	&_Set_PID_Int,	
};
//------------------------------------
in_flash TCMenuItem _Set_PID_Temperature_Value=
{
	&Slovar[10][0],NULL,4,
	Set_Pid_Temperature,		
	NULL,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Set_PID_Temperature=
{
	&Slovar[37][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_PID_Temperature_Value,	
	&_Set_PID_Prop,	
};
//------------------------------------
in_flash TCMenuItem _Set_PID_NUMBER=
{
	&Slovar[10][0],NULL,4,
	NULL,		
	NULL,
	&_Set_PID_Temperature,		
	NULL,
};
in_flash TCMenuItem _Set_PID=
{
	&Slovar[38][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_PID_NUMBER,
	&_Set_ID,
};
//------------------------------------
in_flash TCMenuItem _Set_Password_Admin_Parameter=
{
	&Slovar[4][0],NULL,4,
	Set_Password_Admin,		
	NULL,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Set_Password_Admin=
{
	&Slovar[53][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_Password_Admin_Parameter,
	NULL,
};
in_flash TCMenuItem _Set_Password_User_Parameter=
{
	&Slovar[4][0],NULL,4,
	Set_Password_User,		
	NULL,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Set_Password_User=
{
	&Slovar[52][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_Password_User_Parameter,
	&_Set_Password_Admin,
};
in_flash TCMenuItem _Set_Password_Off=
{
	&Slovar[23][0],NULL,0,
	Set_Password_Off,		
	NULL,	
	NULL,
	&_Set_Password_User,
};
in_flash TCMenuItem _Set_Password_On=
{
	&Slovar[22][0],NULL,0,
	Set_Password_On,		
	NULL,	
	NULL,
	&_Set_Password_Off,
};
in_flash TCMenuItem _Set_Password=
{
	&Slovar[51][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_Password_On,
	&_Set_PID,
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Set_AI_10V_Value=
{
	&Slovar[42][0],NULL,4,
	Set_AI_10V,		
	NULL,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Set_AI_10V=
{
	&Slovar[41][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_AI_10V_Value,
	&_Set_Password,
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Set_Temperature_Value=
{
	&Slovar[4][0],NULL,4,
	Set_Desired_Temperature,		
	NULL,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Set_Temperature=
{
	&Slovar[37][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_Temperature_Value,
	&_Set_AI_10V,
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Set_Point_Temperature=
{
	&Slovar[4][0],NULL,4,
	Set_Point,		
	NULL,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Set_Point_Number=
{
	&Slovar[4][0],NULL,4,
	NULL,		
	NULL,	
	&_Set_Point_Temperature,
	NULL,
};
in_flash TCMenuItem _Set_Point=
{
	&Slovar[36][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_Point_Number,
	&_Set_Temperature,
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Set_Date_Year=
{
	&Slovar[23][0],NULL,4,
	Set_Date,		
	NULL,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Set_Date_Month=
{
	&Slovar[22][0],NULL,4,
	NULL,		
	NULL,	
	&_Set_Date_Year,
	NULL,
};
in_flash TCMenuItem _Set_Date_Date=
{
	&Slovar[4][0],NULL,4,
	NULL,		
	NULL,	
	&_Set_Date_Month,
	NULL,	
};
in_flash TCMenuItem _Set_Date_Day=
{
	&Slovar[4][0],NULL,4,
	NULL,		
	NULL,	
	&_Set_Date_Date,
	NULL,	
};
in_flash TCMenuItem _Set_Date=
{
	&Slovar[29][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_Date_Day,
	&_Set_Point,	
};
//-----------------------------------------------------------------------------------
in_flash TCMenuItem _Set_Time_Second=
{
	&Slovar[23][0],NULL,4,
	Set_Time,		
	NULL,	
	NULL,
	NULL,
};
in_flash TCMenuItem _Set_Time_Minute=
{
	&Slovar[22][0],NULL,4,
	NULL,		
	NULL,	
	&_Set_Time_Second,
	NULL,
};
in_flash TCMenuItem _Set_Time_Hour=
{
	&Slovar[4][0],NULL,4,
	NULL,		
	NULL,	
	&_Set_Time_Minute,
	NULL,	
};
in_flash TCMenuItem _Set_Time=
{
	&Slovar[30][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_Time_Hour,
	&_Set_Date,
};
//-------------------- Set -------------------------------
in_flash TCMenuItem _Set=
{
	&Slovar[0][0],NULL,0,
	NULL,		
	NULL,	
	&_Set_Time,
	&_Reset,
};
//-----------------------------------------------------------------------------------
#endif
