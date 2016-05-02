#include"include_all.h"
struct Motor_Config_struct Motor_Config;
struct Voltage_struct Voltage;
PID_struct Commutation_PID;
PID_struct Speed_PID;
char Motor_Status;
char Motor_Error_Reason;
char Motor_Beep_Flag=0;
int Motor_PhaseDet_Curr[6];
unsigned int Time_Delay1_us=0;
char Time_Delay1_Switch=0;
unsigned int Time_Delay2_us=0;
char Time_Delay2_Switch=0;
int Time_Cnt_ms;
int Time_Cnt_us;
char Commutation_Flag=0;
char Commutation_Bad_Flag = 0;
int PPM_Signal=0;
void Variable_Init()
{
	Motor_Status = Stop;
	Motor_Error_Reason = None;


	Motor_Config.Next_Step = 2;
	Motor_Config.Step = 1;
	Motor_Config.Duty = 100;
	Motor_Config.Set_Speed = 4000;
	Commutation_PID.Error = 0;
	Commutation_PID.Error_Pre = 0;
	Commutation_PID.Sum = 0;
	Commutation_PID.Sum_Max = 100;
	Commutation_PID.Out_Max = 5000;
	Commutation_PID.P_Index = 10;
	Commutation_PID.I_Index = 0;
	Commutation_PID.D_Index = 0;
	Commutation_PID.Out=0;
	Speed_PID.Error = 0;
	Speed_PID.Error_Pre = 0;
	Speed_PID.Sum = 0;
	Speed_PID.Sum_Max = 50000;
	Speed_PID.P_Index = 15;
	Speed_PID.I_Index = 2;
	Speed_PID.D_Index = -5;
	Speed_PID.Out = 0;
	Speed_PID.Out_Max = 800;
}
int Demagnetic_Cnt = 0;
int Demagnetic_Time = 0; 
int Demagnetic_Delay_Cnt = 0;
int Commutation_Delay_Cnt = 0;
int Commutation_Bad_Delay_Cnt = -1;

char Time_Flag = 0;


