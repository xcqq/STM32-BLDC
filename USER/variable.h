#define BackEMF_Threshold_H 10
#define BackEMF_Threshold_L 5
#define Current_Limit 1000
//#define COMMUTATION_PID 1
//#define COMMUTATION_LED 1
//#define DEMAGNETIC 1
#define BREAK 0
#define STEP_LED 1
enum Motor_Status_enum
{
    Stop,
    Standby,
    Start,
    Error,
    Running,
    Phase_Detect
};
enum Motor_Error_Reason_enum
{
	Low_Power,
	Start_Fail,
	Over_Current,
	Commutation_Error,
	None
};
struct Voltage_struct
{
	int Current_Offset;
    int Battery;
    int Current;
    int Phase_A;
    int Phase_B;
    int Phase_C;
};
struct Motor_Config_struct
{
	int MaxDuty; //最大pwm占空比
	int Duty; //pwm占空比
	int Period; //pwm周期
	int Step_Cnt;
	int BadStep_Cnt;
	int GoodStep_Cnt;
	int Speed;
	int Set_Speed;
	int Commutation_Time;
	int Commutation_Time_Pre;
	int Commutation_Bad_Time;
	int Commutation_Time_us;
	char Step; //当前相位
	char Next_Step; //根据查表得出的下一相
	volatile char NextStep_Detect; //AD检测到的下一相
	char Initial_Step;
};
typedef struct 
{
	int P_Index;
	int I_Index;
	int D_Index;
	int Error;
	int Error_Pre;
	int Out;
	int Out_Max;
	int Sum;
	int Sum_Max;
}PID_struct;
extern struct Motor_Config_struct Motor_Config;
extern struct Voltage_struct Voltage;
extern PID_struct Commutation_PID; 
extern PID_struct Speed_PID; 
extern char Motor_Status;
extern char Motor_Error_Reason;
extern char Motor_Beep_Flag;
extern int Motor_PhaseDet_Curr[6];
extern unsigned int Time_Delay1_us; 
extern char Time_Delay1_Switch;
extern unsigned int Time_Delay2_us;
extern char Time_Delay2_Switch; 
extern int Time_Cnt_ms;
extern int Time_Cnt_us; 
extern char Commutation_Flag;
extern char Commutation_Bad_Flag;
extern int Demagnetic_Cnt;
extern int Demagnetic_Time;
extern int Demagnetic_Delay_Cnt;
extern int Commutation_Delay_Cnt; 
extern int Commutation_Bad_Delay_Cnt;
extern char Time_Flag; 
extern int PPM_Signal;
