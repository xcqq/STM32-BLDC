#include "include_all.h"
void Motor_Init()
{
	int ADC_TempValue[4];
	ADC_SoftwareStartInjectedConvCmd(ADC1, ENABLE);
	Delay_ms(10);
	ADC_TempValue[0] = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1) * 0.8058;
	ADC_TempValue[1] = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_2) * 0.8058;
	ADC_TempValue[2] = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_3) * 0.8058;
	ADC_TempValue[3] = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_4) * 0.8058;
	Voltage.Battery = (ADC_TempValue[0] + ADC_TempValue[1]) / 2;
	Voltage.Current_Offset = (ADC_TempValue[2] + ADC_TempValue[3]) / 2;
}
/*
static void Motor_Onepulse(char Step)
{
	Motor_Setduty(200);
	ADC_SetDetTime(180);
	//PWM_Mode_Switch(0);
	switch (Step)
	{
		case 0:
			FET_A_PWM_OFF;
			FET_B_PWM_OFF;
			FET_C_PWM_OFF;
			FET_A_L_OFF;
			FET_B_L_OFF;
			FET_C_L_OFF;
			break;
		case 1:
			FET_A_PWM_ON;
			FET_B_PWM_OFF;
			FET_C_PWM_OFF;
			FET_A_L_OFF;
			FET_B_L_ON;
			FET_C_L_ON;
			break;
		case 2:
			FET_A_PWM_OFF;
			FET_B_PWM_ON;
			FET_C_PWM_ON;
			FET_A_L_ON;
			FET_B_L_OFF;
			FET_C_L_OFF;
			break;
		case 3:
			FET_A_PWM_OFF;
			FET_B_PWM_ON;
			FET_C_PWM_OFF;
			FET_A_L_ON;
			FET_B_L_OFF;
			break;
		case 4:
			FET_A_PWM_ON;
			FET_B_PWM_OFF;
			FET_C_PWM_ON;
			FET_A_L_OFF;
			FET_B_L_ON;
			FET_C_L_OFF;
			break;
		case 5:
			FET_A_PWM_OFF;
			FET_B_PWM_OFF;
			FET_C_PWM_ON;
			FET_A_L_ON;
			FET_B_L_ON;
			FET_C_L_OFF;
			break;
		case 6:
			FET_A_PWM_ON;
			FET_B_PWM_ON;
			FET_C_PWM_OFF;
			FET_A_L_OFF;
			FET_B_L_OFF;
			FET_C_L_ON;
			break;
	}

	TIM_SelectOnePulseMode(FET_H_TIMER, TIM_OPMode_Single);
	TIM_SelectOnePulseMode(FET_L_TIMER, TIM_OPMode_Single);
	TIM_Cmd(FET_L_TIMER, ENABLE);
	TIM_Cmd(FET_H_TIMER, ENABLE);
	Delay_ms(1);
} 

void Motor_GetPosition()
{
	int Temp_Position[3]; //用来记录三次检测的结果 用1和-1表示
	Motor_Status = Phase_Detect;
	PWM_OnePulse_Config();
	ADC_PhaseDectectMode_Config();
	Motor_Onepulse(1);
	Motor_Onepulse(1);
	Motor_PhaseDet_Curr[0] = ADC_GetConversionValue(ADC1);
	Motor_Onepulse(2);
	Motor_PhaseDet_Curr[1] = ADC_GetConversionValue(ADC1);
	Motor_Onepulse(3);
	Motor_PhaseDet_Curr[2] = ADC_GetConversionValue(ADC1);
	Motor_Onepulse(4);
	Motor_PhaseDet_Curr[3] = ADC_GetConversionValue(ADC1);
	Motor_Onepulse(5);
	Motor_PhaseDet_Curr[4] = ADC_GetConversionValue(ADC1);
	Motor_Onepulse(6);
	Motor_PhaseDet_Curr[5] = ADC_GetConversionValue(ADC1);
	Delay_ms(10);
	Motor_Setduty(0);
	if (Motor_PhaseDet_Curr[0] >= Motor_PhaseDet_Curr[1])
	{
		if ((Motor_PhaseDet_Curr[0] - Motor_PhaseDet_Curr[1]) >= 100)
		{
			if (Motor_PhaseDet_Curr[3] >= Motor_PhaseDet_Curr[2])
			{
				if ((Motor_PhaseDet_Curr[3] - Motor_PhaseDet_Curr[2]) >= 100) Motor_Config.Step = 1;
				else Motor_Config.Step = 6;
			}
			else Motor_Config.Step = 0;
		}
		else
		{
			if (Motor_PhaseDet_Curr[2] < Motor_PhaseDet_Curr[3]) Motor_Config.Step = 2;
			else Motor_Config.Step = 5;
		}
	}
	else
	{
		if ((Motor_PhaseDet_Curr[4] - Motor_PhaseDet_Curr[5]) >= 100) Motor_Config.Step = 3;
		else Motor_Config.Step = 4;
	}
	
	if (Motor_PhaseDet_Curr[0] - Motor_PhaseDet_Curr[1]) Temp_Position += 4;
	else Temp_Position += 0;
	if (Motor_PhaseDet_Curr[2] - Motor_PhaseDet_Curr[3]) Temp_Position += 2;
	else Temp_Position += 0;
	if (Motor_PhaseDet_Curr[4] - Motor_PhaseDet_Curr[5]) Temp_Position += 1;
	else Temp_Position += 0;
	switch (Temp_Position)
	{
		case 0:
			Motor_Config.Step = 1;
			break;
		case 5:
			Motor_Config.Step = 2;
			break;
		case 1:
			Motor_Config.Step = 3;
			break;
		case 2:
			Motor_Config.Step = 4;
			break;
		case 6:
			Motor_Config.Step = 5;
			break;
		case 4:
			Motor_Config.Step = 6;
			break;
	}
	
	Delay_ms(10);

}
*/
void Motor_Selftest()
{
}
void Motor_Start()
{
	int duty = 0;
	//首先定位
	LED_ALERT_ON;
	Motor_Status = Start;
	Motor_Config.Commutation_Time = 0;
	Motor_Config.Commutation_Time_Pre = 0;
	Demagnetic_Cnt = 0;
	Commutation_Bad_Flag = 0;
	Motor_Switch_Step(Motor_Config.Step);
	for (duty = 10; duty <= 100; duty++)
	{
		//Motor_Setduty(duty);
		Get_Time(); 
		Delay_us(1000);
	}
	//然后开始加电压开环启动
	//最开始的占空比为1%也就是1.2v
	/*
	for (duty = 10; duty <= 150; duty++)
	{
		Motor_Setduty(duty);
		Motor_Switch_Step(Motor_Config.Next_Step);
		Delay_ms(140 / duty);
		Get_Time();
	}
	*/
	//Motor_Setduty(200);
	Motor_Status = Running;
	Motor_Switch_Step(Motor_Config.Next_Step);
	Get_Time(); 
	Motor_Config.NextStep_Detect = Motor_Config.Next_Step;
	
	LED_ALERT_OFF;
}
void Motor_Stop()
{
	Motor_Status = Stop;

}
void Motor_Error()
{

}
void Motor_Beep(uint16_t freq, uint16_t duration)
{
	int period, t_h, t_l;
	period = 1000000 / freq;
	t_h = period / 20;
	t_l = period - t_h;
	TIM_SetAutoreload(FET_H_TIMER, 24 * period);
	TIM_SetAutoreload(FET_L_TIMER, 24 * period);
	TIM_SetCompare1(FET_H_TIMER, t_h * 12);
	TIM_SetCompare2(FET_H_TIMER, t_h * 12);
	TIM_SetCompare3(FET_H_TIMER, t_h * 12);
	TIM_SetCompare2(FET_L_TIMER, t_h * 12);
	TIM_SetCompare3(FET_L_TIMER, t_h * 12);
	TIM_SetCompare4(FET_L_TIMER, t_h * 12);
	FET_A_H_PWM_ON;
	FET_B_H_PWM_OFF;
	FET_C_H_PWM_ON;
	FET_A_L_PWM_OFF;
	FET_B_L_PWM_ON;
	FET_C_L_PWM_OFF;
	FET_A_H_OFF;
	FET_B_H_ON;
	FET_C_H_OFF;
	FET_A_L_OFF;
	FET_B_L_OFF;
	FET_C_L_OFF;
	Delay_ms(duration);
	FET_A_H_PWM_OFF;
	FET_B_H_PWM_OFF;
	FET_C_H_PWM_OFF;
	FET_A_L_PWM_OFF;
	FET_B_L_PWM_OFF;
	FET_C_L_PWM_OFF; 

	FET_A_L_OFF;
	FET_B_L_OFF;
	FET_C_L_OFF;
	TIM_SetAutoreload(FET_H_TIMER, 1000);
	TIM_SetAutoreload(FET_L_TIMER, 1000);
	TIM_SetCompare1(FET_H_TIMER, 0);
	TIM_SetCompare2(FET_H_TIMER, 0);
	TIM_SetCompare3(FET_H_TIMER, 0);
	TIM_SetCompare2(FET_L_TIMER, 0);
	TIM_SetCompare3(FET_L_TIMER, 0);
	TIM_SetCompare4(FET_L_TIMER, 0);
}
void Commutation_Detected_PWM_Off()
{
	switch (Motor_Config.Step)
	{
		case 1:
			if ((Voltage.Phase_C > BackEMF_Threshold_H) && Commutation_Flag == 1)
			{
					Motor_Config.NextStep_Detect = 2;
					Commutation_Flag = 0;
					#if DEMAGNETIC
					Demagnetic_Time = Demagnetic_Cnt;
					Demagnetic_Cnt = 0;
					#endif
					
#if COMMUTATION_PID
					Motor_Config.Commutation_Time_Pre = Motor_Config.Commutation_Time_us; 
					Get_Time(); 
					PID_Calc(&Commutation_PID, Motor_Config.Commutation_Time_Pre, Motor_Config.Commutation_Time_us);
					Motor_Config.Commutation_Time_us += Commutation_PID.Out;
#else
					Get_Time(); 
#endif
					TIM2_Set_Commutation_Good(Motor_Config.Commutation_Time_us / 2);
#if COMMUTATION_LED
					LED_Alert_Tongle();
#endif
					Motor_Config.GoodStep_Cnt++;
			}
			break;
		case 4:
			if ((Voltage.Phase_C < BackEMF_Threshold_L) && Commutation_Flag == 1)
			{
					Motor_Config.NextStep_Detect = 5;
					Commutation_Flag = 0; 
#if DEMAGNETIC
					Demagnetic_Time = Demagnetic_Cnt;
					Demagnetic_Cnt = 0;
#endif
#if COMMUTATION_PID
					Motor_Config.Commutation_Time_Pre = Motor_Config.Commutation_Time_us;
					Get_Time();
					PID_Calc(&Commutation_PID, Motor_Config.Commutation_Time_Pre, Motor_Config.Commutation_Time_us);
					Motor_Config.Commutation_Time_us += Commutation_PID.Out;
#else
					Get_Time();
#endif
					TIM2_Set_Commutation_Good(Motor_Config.Commutation_Time_us / 2);
#if COMMUTATION_LED
					LED_Alert_Tongle();
#endif
					Motor_Config.GoodStep_Cnt++; 
			}
			break;
		case 2:
			if ((Voltage.Phase_A < BackEMF_Threshold_L) && Commutation_Flag == 1)
			{
					Motor_Config.NextStep_Detect = 3;
					Commutation_Flag = 0;
#if DEMAGNETIC
					Demagnetic_Time = Demagnetic_Cnt;
					Demagnetic_Cnt = 0;
#endif
#if COMMUTATION_PID
					Motor_Config.Commutation_Time_Pre = Motor_Config.Commutation_Time_us;
					Get_Time();
					PID_Calc(&Commutation_PID, Motor_Config.Commutation_Time_Pre, Motor_Config.Commutation_Time_us);
					Motor_Config.Commutation_Time_us += Commutation_PID.Out;
#else
					Get_Time();
#endif
					TIM2_Set_Commutation_Good(Motor_Config.Commutation_Time_us / 2);
#if COMMUTATION_LED
					LED_Alert_Tongle();
#endif
					Motor_Config.GoodStep_Cnt++; 
			}
			break;
		case 5:
			if ((Voltage.Phase_A > BackEMF_Threshold_H) && Commutation_Flag == 1)
			{
					Motor_Config.NextStep_Detect = 6;
					Commutation_Flag = 0;
#if DEMAGNETIC
					Demagnetic_Time = Demagnetic_Cnt;
					Demagnetic_Cnt = 0;
#endif
#if COMMUTATION_PID
					Motor_Config.Commutation_Time_Pre = Motor_Config.Commutation_Time_us;
					Get_Time();
					PID_Calc(&Commutation_PID, Motor_Config.Commutation_Time_Pre, Motor_Config.Commutation_Time_us);
					Motor_Config.Commutation_Time_us += Commutation_PID.Out;
#else
					Get_Time();
#endif
					TIM2_Set_Commutation_Good(Motor_Config.Commutation_Time_us / 2);
#if COMMUTATION_LED
					LED_Alert_Tongle();
#endif
					Motor_Config.GoodStep_Cnt++; 
			}
			break;
		case 3:
			if ((Voltage.Phase_B > BackEMF_Threshold_L) && Commutation_Flag == 1)
			{
					Motor_Config.NextStep_Detect = 4;
					Commutation_Flag = 0;
#if DEMAGNETIC
					Demagnetic_Time = Demagnetic_Cnt;
					Demagnetic_Cnt = 0;
#endif
#if COMMUTATION_PID
					Motor_Config.Commutation_Time_Pre = Motor_Config.Commutation_Time_us;
					Get_Time();
					PID_Calc(&Commutation_PID, Motor_Config.Commutation_Time_Pre, Motor_Config.Commutation_Time_us);
					Motor_Config.Commutation_Time_us += Commutation_PID.Out;
#else
					Get_Time();
#endif
					TIM2_Set_Commutation_Good(Motor_Config.Commutation_Time_us / 2);
#if COMMUTATION_LED
					LED_Alert_Tongle();
#endif
					Motor_Config.GoodStep_Cnt++; 
			}
			break;
		case 6:
			if ((Voltage.Phase_B < BackEMF_Threshold_H) && Commutation_Flag == 1)
			{
					Motor_Config.NextStep_Detect = 1;
					Commutation_Flag = 0;
#if DEMAGNETIC
					Demagnetic_Time = Demagnetic_Cnt;
					Demagnetic_Cnt = 0;
#endif
#if COMMUTATION_PID
					Motor_Config.Commutation_Time_Pre = Motor_Config.Commutation_Time_us;
					Get_Time();
					PID_Calc(&Commutation_PID, Motor_Config.Commutation_Time_Pre, Motor_Config.Commutation_Time_us);
					Motor_Config.Commutation_Time_us += Commutation_PID.Out;
#else
					Get_Time();
#endif
					TIM2_Set_Commutation_Good(Motor_Config.Commutation_Time_us / 2);
#if COMMUTATION_LED
					LED_Alert_Tongle();
#endif
					Motor_Config.GoodStep_Cnt++; 
			}
			break;
	}
	if (Motor_Config.GoodStep_Cnt >= 20)
	{
		Motor_Config.BadStep_Cnt = 0;
	}
}
void Commutation_Detected_PWM_On()
{
	switch (Motor_Config.Step)
	{
		case 1:
			if ((Voltage.Phase_C - BackEMF_Threshold_L > (Voltage.Phase_A + Voltage.Phase_B) >> 1) && Commutation_Flag == 1)
			{
				Motor_Config.NextStep_Detect = 2;
				Commutation_Flag = 0;
#if DEMAGNETIC
				Demagnetic_Time = Demagnetic_Cnt;
				Demagnetic_Cnt = 0;
#endif
#if COMMUTATION_PID
				Motor_Config.Commutation_Time_Pre = Motor_Config.Commutation_Time_us;
				Get_Time();
				PID_Calc(&Commutation_PID, Motor_Config.Commutation_Time_Pre, Motor_Config.Commutation_Time_us);
				Motor_Config.Commutation_Time_us += Commutation_PID.Out;
#else
				Get_Time();
#endif
				TIM2_Set_Commutation_Good(Motor_Config.Commutation_Time_us / 2);
#if COMMUTATION_LED
				LED_Alert_Tongle();
#endif
				Motor_Config.GoodStep_Cnt++; 
			}
			break;
		case 4:
			if ((Voltage.Phase_C - BackEMF_Threshold_H < (Voltage.Phase_A + Voltage.Phase_B) >> 1) && Commutation_Flag == 1)
			{
				Motor_Config.NextStep_Detect = 5;
				Commutation_Flag = 0;
#if DEMAGNETIC
				Demagnetic_Time = Demagnetic_Cnt;
				Demagnetic_Cnt = 0;
#endif
#if COMMUTATION_PID
				Motor_Config.Commutation_Time_Pre = Motor_Config.Commutation_Time_us;
				Get_Time();
				PID_Calc(&Commutation_PID, Motor_Config.Commutation_Time_Pre, Motor_Config.Commutation_Time_us);
				Motor_Config.Commutation_Time_us += Commutation_PID.Out;
#else
				Get_Time();
#endif
				TIM2_Set_Commutation_Good(Motor_Config.Commutation_Time_us / 2);
#if COMMUTATION_LED
				LED_Alert_Tongle();
#endif
				Motor_Config.GoodStep_Cnt++; 
			}
			break;
		case 2:
			if ((Voltage.Phase_A - BackEMF_Threshold_H < (Voltage.Phase_B + Voltage.Phase_C) >> 1) && Commutation_Flag == 1)
			{
				Motor_Config.NextStep_Detect = 3;
				Commutation_Flag = 0;
#if DEMAGNETIC
				Demagnetic_Time = Demagnetic_Cnt;
				Demagnetic_Cnt = 0;
#endif
#if COMMUTATION_PID
				Motor_Config.Commutation_Time_Pre = Motor_Config.Commutation_Time_us;
				Get_Time();
				PID_Calc(&Commutation_PID, Motor_Config.Commutation_Time_Pre, Motor_Config.Commutation_Time_us);
				Motor_Config.Commutation_Time_us += Commutation_PID.Out;
#else
				Get_Time();
#endif
				TIM2_Set_Commutation_Good(Motor_Config.Commutation_Time_us / 2);
#if COMMUTATION_LED
				LED_Alert_Tongle();
#endif
				Motor_Config.GoodStep_Cnt++; 
			}
			break;
		case 5:
			if ((Voltage.Phase_A - BackEMF_Threshold_L > (Voltage.Phase_B + Voltage.Phase_C) >> 1) && Commutation_Flag == 1)
			{
				Motor_Config.NextStep_Detect = 6;
				Commutation_Flag = 0;
#if DEMAGNETIC
				Demagnetic_Time = Demagnetic_Cnt;
				Demagnetic_Cnt = 0;
#endif
#if COMMUTATION_PID
				Motor_Config.Commutation_Time_Pre = Motor_Config.Commutation_Time_us;
				Get_Time();
				PID_Calc(&Commutation_PID, Motor_Config.Commutation_Time_Pre, Motor_Config.Commutation_Time_us);
				Motor_Config.Commutation_Time_us += Commutation_PID.Out;
#else
				Get_Time();
#endif
				TIM2_Set_Commutation_Good(Motor_Config.Commutation_Time_us / 2);
#if COMMUTATION_LED
				LED_Alert_Tongle();
#endif
				Motor_Config.GoodStep_Cnt++; 
			}
			break;
		case 3:
			if ((Voltage.Phase_B - BackEMF_Threshold_L > (Voltage.Phase_A + Voltage.Phase_C) >> 1) && Commutation_Flag == 1)
			{
				Motor_Config.NextStep_Detect = 4;
				Commutation_Flag = 0;
#if DEMAGNETIC
				Demagnetic_Time = Demagnetic_Cnt;
				Demagnetic_Cnt = 0;
#endif
#if COMMUTATION_PID
				Motor_Config.Commutation_Time_Pre = Motor_Config.Commutation_Time_us;
				Get_Time();
				PID_Calc(&Commutation_PID, Motor_Config.Commutation_Time_Pre, Motor_Config.Commutation_Time_us);
				Motor_Config.Commutation_Time_us += Commutation_PID.Out;
#else
				Get_Time();
#endif
				TIM2_Set_Commutation_Good(Motor_Config.Commutation_Time_us / 2);
#if COMMUTATION_LED
				LED_Alert_Tongle();
#endif
				Motor_Config.GoodStep_Cnt++; 
			}
			break;
		case 6:
			if ((Voltage.Phase_B - BackEMF_Threshold_H < (Voltage.Phase_A + Voltage.Phase_C) >> 1) && Commutation_Flag == 1)
			{
				Motor_Config.NextStep_Detect = 1;
				Commutation_Flag = 0;
#if DEMAGNETIC
				Demagnetic_Time = Demagnetic_Cnt;
				Demagnetic_Cnt = 0;
#endif
#if COMMUTATION_PID
				Motor_Config.Commutation_Time_Pre = Motor_Config.Commutation_Time_us;
				Get_Time();
				PID_Calc(&Commutation_PID, Motor_Config.Commutation_Time_Pre, Motor_Config.Commutation_Time_us);
				Motor_Config.Commutation_Time_us += Commutation_PID.Out;
#else
				Get_Time();
#endif
				TIM2_Set_Commutation_Good(Motor_Config.Commutation_Time_us / 2);
#if COMMUTATION_LED
				LED_Alert_Tongle();
#endif
				Motor_Config.GoodStep_Cnt++; 
			}
			break;
	}
	if (Motor_Config.GoodStep_Cnt>=20)
	{
		Motor_Config.BadStep_Cnt = 0;
	}
}
void PID_Calc(PID_struct *PID, int Set, int In)
{
	PID->Error_Pre = PID->Error;
	PID->Error = Set - In;
	PID->Sum += PID->Error;
	if (PID->Sum > PID->Sum_Max) PID->Sum = PID->Sum_Max;
	if (PID->Sum < (-PID->Sum_Max)) PID->Sum = (-PID->Sum_Max); 
	PID->Out = (PID->P_Index * PID->Error + PID->D_Index * (PID->Error - PID->Error_Pre) + PID->I_Index * PID->Sum) / 100;
	if (PID->Out > PID->Out_Max) PID->Out = PID->Out_Max;
	if (PID->Out < (-PID->Out_Max)) PID->Out = (-PID->Out_Max);
}

