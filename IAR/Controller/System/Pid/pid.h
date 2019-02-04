//------------------------------------------------------------------------------
#ifndef __PID_H
#define __PID_H
//------------------------------------------------------------------------------
#include "..\define.h"
//------------------------------------------------------------------------------
#if NUM_PID
extern volatile u16 PID_P3_Time[NUM_PID];
extern f32 acc2[NUM_PID];
extern f32 acc[NUM_PID];
es16 diff;
es16 tsum[NUM_PID];
es16 pii[NUM_PID];
es16 ppp[NUM_PID];
es16 pdd[NUM_PID];
#endif
//------------------------------------------------------------------------------
void pid_init(void);
void pid_handle(void);
void Set_Pid_Temperature();
void Set_Pid_Mode();
void Set_Pid_Power_Min();
void Set_Pid_Power_Max();
void Set_Pid_Power();
void Set_Pid_Diff();
void Set_Pid_Int();
void Set_Pid_Prop();
void Set_Pid_Channel();
void Set_Pid_Slow();
void Set_Pid_Fast();
//-----------------------------------------------------
#endif
