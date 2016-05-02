#include "include_all.h"
u8 Motor_Step = 1;
u8 Motor_NextStep = 1;
u16 Motor_duty = 0;

void PWM_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE); 

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = FET_AH_PIN;
	GPIO_Init(FET_AH_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = FET_BH_PIN;
	GPIO_Init(FET_BH_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = FET_CH_PIN;
	GPIO_Init(FET_CH_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = FET_AL_PIN;
	GPIO_Init(FET_AL_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = FET_BL_PIN;
	GPIO_Init(FET_BL_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = FET_CL_PIN;
	GPIO_Init(FET_CL_PORT, &GPIO_InitStructure); 

	FET_A_H_OFF;
	FET_B_H_OFF;
	FET_C_H_OFF;
	FET_A_L_OFF;
	FET_B_L_OFF;
	FET_C_L_OFF; 

	TIM_DeInit(FET_H_TIMER);
	TIM_DeInit(FET_L_TIMER);
	TIM_TimeBaseStructure.TIM_Prescaler = 2;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 1000;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(FET_H_TIMER, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(FET_L_TIMER, &TIM_TimeBaseStructure);

	//设置主定时器触发信号
	TIM_SelectMasterSlaveMode(FET_H_TIMER, TIM_MasterSlaveMode_Enable);
	TIM_SelectOutputTrigger(FET_H_TIMER, TIM_TRGOSource_Update);
	//设置从定时器
	TIM_SelectSlaveMode(FET_L_TIMER, TIM_SlaveMode_Reset);
	TIM_SelectInputTrigger(FET_L_TIMER, TIM_TS_ITR3);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(FET_H_TIMER, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(FET_H_TIMER, TIM_OCPreload_Enable);
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(FET_H_TIMER, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(FET_H_TIMER, TIM_OCPreload_Enable);
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init(FET_H_TIMER, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(FET_H_TIMER, TIM_OCPreload_Enable);

	TIM_OCInitStructure.TIM_Pulse = 800;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC4Init(FET_H_TIMER, &TIM_OCInitStructure);

	TIM_OC4PreloadConfig(FET_H_TIMER, TIM_OCPreload_Enable); 
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_Cmd(FET_H_TIMER, ENABLE);
	TIM_CtrlPWMOutputs(FET_H_TIMER, ENABLE);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
#if BREAK
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
#else
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
#endif

	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(FET_L_TIMER, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(FET_L_TIMER, TIM_OCPreload_Enable);
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init(FET_L_TIMER, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(FET_L_TIMER, TIM_OCPreload_Enable);
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC4Init(FET_L_TIMER, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(FET_L_TIMER, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(FET_L_TIMER, ENABLE);
	TIM_Cmd(FET_L_TIMER, ENABLE);
	TIM_CtrlPWMOutputs(FET_L_TIMER, ENABLE);
}
void PWM_OnePulse_Config()
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = FET_AH_PIN;
	GPIO_Init(FET_AH_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = FET_BH_PIN;
	GPIO_Init(FET_BH_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = FET_CH_PIN;
	GPIO_Init(FET_CH_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = FET_AL_PIN;
	GPIO_Init(FET_AL_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = FET_BL_PIN;
	GPIO_Init(FET_BL_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = FET_CL_PIN;
	GPIO_Init(FET_CL_PORT, &GPIO_InitStructure);

	FET_A_H_OFF;
	FET_B_H_OFF;
	FET_C_H_OFF;
	FET_A_L_OFF;
	FET_B_L_OFF;
	FET_C_L_OFF;

	TIM_DeInit(FET_H_TIMER);

	TIM_TimeBaseStructure.TIM_Prescaler = 2;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
	TIM_TimeBaseStructure.TIM_Period = 1000;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(FET_H_TIMER, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(FET_L_TIMER, &TIM_TimeBaseStructure);

	//设置主定时器触发信号
	TIM_SelectMasterSlaveMode(FET_H_TIMER, TIM_MasterSlaveMode_Enable);
	TIM_SelectOutputTrigger(FET_H_TIMER, TIM_TRGOSource_Update);
	//设置从定时器
	TIM_SelectSlaveMode(FET_L_TIMER, TIM_SlaveMode_Reset);
	TIM_SelectInputTrigger(FET_L_TIMER, TIM_TS_ITR3);


	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(FET_H_TIMER, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(FET_H_TIMER, TIM_OCPreload_Enable);
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(FET_H_TIMER, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(FET_H_TIMER, TIM_OCPreload_Enable);
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init(FET_H_TIMER, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(FET_H_TIMER, TIM_OCPreload_Enable);
	TIM_OCInitStructure.TIM_Pulse = 100;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC4Init(FET_H_TIMER, &TIM_OCInitStructure);
	TIM_CtrlPWMOutputs(FET_H_TIMER, ENABLE); 
	TIM_ARRPreloadConfig(FET_H_TIMER, ENABLE); 

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(FET_L_TIMER, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(FET_L_TIMER, TIM_OCPreload_Enable);
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init(FET_L_TIMER, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(FET_L_TIMER, TIM_OCPreload_Enable);
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC4Init(FET_L_TIMER, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(FET_L_TIMER, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(FET_L_TIMER, ENABLE);
	TIM_CtrlPWMOutputs(FET_L_TIMER, ENABLE);

	TIM_SelectOnePulseMode(FET_H_TIMER, TIM_OPMode_Single);
	TIM_SelectOnePulseMode(FET_L_TIMER, TIM_OPMode_Single); 


	//TIM_Cmd(FET_L_TIMER, ENABLE);
	//TIM_Cmd(FET_H_TIMER, ENABLE);
}
//参数为1的时候打开pwm输出,0的时候为GPIO输出
void PWM_Mode_Switch(char Switch)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	if (Switch==1)
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Pin = FET_AH_PIN;
		GPIO_Init(FET_AH_PORT, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = FET_BH_PIN;
		GPIO_Init(FET_BH_PORT, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = FET_CH_PIN;
		GPIO_Init(FET_CH_PORT, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = FET_AL_PIN;
		GPIO_Init(FET_AL_PORT, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = FET_BL_PIN;
		GPIO_Init(FET_BL_PORT, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = FET_CL_PIN;
		GPIO_Init(FET_CL_PORT, &GPIO_InitStructure);
		TIM_CtrlPWMOutputs(FET_H_TIMER, ENABLE); 

	}
	else
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

		GPIO_InitStructure.GPIO_Pin = FET_AH_PIN;
		GPIO_Init(FET_AH_PORT, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = FET_BH_PIN;
		GPIO_Init(FET_BH_PORT, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = FET_CH_PIN;
		GPIO_Init(FET_CH_PORT, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = FET_AL_PIN;
		GPIO_Init(FET_AL_PORT, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = FET_BL_PIN;
		GPIO_Init(FET_BL_PORT, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = FET_CL_PIN;
		GPIO_Init(FET_CL_PORT, &GPIO_InitStructure);
		FET_A_H_OFF;
		FET_B_H_OFF;
		FET_C_H_OFF;
		FET_A_L_OFF;
		FET_B_L_OFF;
		FET_C_L_OFF; 
		TIM_CtrlPWMOutputs(FET_H_TIMER, DISABLE);
	}

}
void Motor_Setduty(uint16_t duty)
{
	if (Motor_Status==Stop)
	{
		TIM_SetCompare1(FET_H_TIMER, 0);
		TIM_SetCompare2(FET_H_TIMER, 0);
		TIM_SetCompare3(FET_H_TIMER, 0);
		TIM_SetCompare2(FET_L_TIMER, 0);
		TIM_SetCompare3(FET_L_TIMER, 0);
		TIM_SetCompare4(FET_L_TIMER, 0);
	}
	else
	{
		TIM_SetCompare1(FET_H_TIMER, duty);
		TIM_SetCompare2(FET_H_TIMER, duty);
		TIM_SetCompare3(FET_H_TIMER, duty);
		TIM_SetCompare2(FET_L_TIMER, duty);
		TIM_SetCompare3(FET_L_TIMER, duty);
		TIM_SetCompare4(FET_L_TIMER, duty);
#if BREAK
		if (duty <= 300)
		{
			TIM_SetCompare4(FET_H_TIMER, 750);
		}
		else
		{
			TIM_SetCompare4(FET_H_TIMER, 100); 
		}
#else
		TIM_SetCompare4(FET_H_TIMER, 20);
#endif
	}
}
/*************************************************************/
//-----------------------------------------------
//| Step1 | Step2 | Step3 | Step4 | Step5 | Step6 |
//----------------------------------------------------------
//| A_H      |   1   |   0   |   0   |   0   |   0   |   1   |
//----------------------------------------------------------
//| A_L      |   0   |   0   |   1   |   1   |   0   |   0   |
//----------------------------------------------------------
//| B_H      |   0   |   0   |   0   |   1   |   1   |   0   |
//----------------------------------------------------------
//| B_L      |   1   |   1   |   0   |   0   |   0   |   0   |
//----------------------------------------------------------
//| C_H      |   0   |   1   |   1   |   0   |   0   |   0   |
//----------------------------------------------------------
//| C_L      |   0   |   0   |   0   |   0   |   1   |   1   |
//----------------------------------------------------------
/************************************************************/
void Motor_Switch_Step(u8 Step)
{
	if (Motor_Status == Running)
	{
		//TIM2_Set_Commutation_Bad(Motor_Config.Commutation_Time_us * 2);
		TIM2_Set_Commutation_Bad(10000); 
	}
	switch (Step)
	{
#if BREAK
		case 0:
			FET_A_H_PWM_OFF;
			FET_B_H_PWM_OFF;
			FET_C_H_PWM_OFF;
			FET_A_L_PWM_OFF;
			FET_B_L_PWM_OFF;
			FET_C_L_PWM_OFF;
			FET_A_L_OFF;
			FET_B_L_OFF;
			FET_C_L_OFF;
			Motor_Config.Step = 0;
			Motor_Config.Next_Step = 0;
			break;
		case 1:
			FET_A_H_PWM_ON;
			FET_B_H_PWM_OFF;
			FET_C_H_PWM_OFF;
			FET_A_L_PWM_ON;
			FET_B_L_PWM_OFF;
			FET_C_L_PWM_OFF;
			FET_A_L_ON;
			FET_B_L_ON;
			FET_C_L_OFF;
			Motor_Config.Step = 1;
			Motor_Config.Next_Step = 2;
			break;
		case 2:
			FET_A_H_PWM_OFF;
			FET_B_H_PWM_OFF;
			FET_C_H_PWM_ON;
			FET_A_L_PWM_OFF;
			FET_B_L_PWM_OFF;
			FET_C_L_PWM_ON;
			FET_A_L_OFF;
			FET_B_L_ON;
			FET_C_L_ON;
			Motor_Config.Step = 2;
			Motor_Config.Next_Step = 3;
			break;
		case 3:
			FET_A_H_PWM_OFF;
			FET_B_H_PWM_OFF;
			FET_C_H_PWM_ON;
			FET_A_L_PWM_OFF;
			FET_B_L_PWM_OFF;
			FET_C_L_PWM_ON;
			FET_A_L_ON;
			FET_B_L_OFF;
			FET_C_L_ON;
			Motor_Config.Step = 3;
			Motor_Config.Next_Step = 4;
			break;
		case 4:
			FET_A_H_PWM_OFF;
			FET_B_H_PWM_ON;
			FET_C_H_PWM_OFF;
			FET_A_L_PWM_OFF;
			FET_B_L_PWM_ON;
			FET_C_L_PWM_OFF;
			FET_A_L_ON;
			FET_B_L_ON;
			FET_C_L_OFF;
			Motor_Config.Step = 4;
			Motor_Config.Next_Step = 5;
			break;
		case 5:
			FET_A_H_PWM_OFF;
			FET_B_H_PWM_ON;
			FET_C_H_PWM_OFF;
			FET_A_L_PWM_OFF;
			FET_B_L_PWM_ON;
			FET_C_L_PWM_OFF;
			FET_A_L_OFF;
			FET_B_L_ON;
			FET_C_L_ON;
			Motor_Config.Step = 5;
			Motor_Config.Next_Step = 6;
			break;
		case 6:
			FET_A_H_PWM_ON;
			FET_B_H_PWM_OFF;
			FET_C_H_PWM_OFF;
			FET_A_L_PWM_ON;
			FET_B_L_PWM_OFF;
			FET_C_L_PWM_OFF; 
			FET_A_L_ON;
			FET_B_L_OFF;
			FET_C_L_ON;
			Motor_Config.Step = 6;
			Motor_Config.Next_Step = 1;
			break;
#else
		case 0:
			FET_A_H_PWM_OFF;
			FET_B_H_PWM_OFF;
			FET_C_H_PWM_OFF;
			FET_A_L_PWM_OFF;
			FET_B_L_PWM_OFF;
			FET_C_L_PWM_OFF;
			FET_A_H_OFF;
			FET_B_H_OFF;
			FET_C_H_OFF;
			FET_A_L_OFF;
			FET_B_L_OFF;
			FET_C_L_OFF;
			Motor_Config.Step = 0;
			Motor_Config.Next_Step = 0;
			break;
		case 1:
			FET_A_H_PWM_ON;
			FET_B_H_PWM_OFF;
			FET_C_H_PWM_OFF;
			FET_A_L_PWM_OFF;
			FET_B_L_PWM_ON;
			FET_C_L_PWM_OFF;
			FET_A_H_OFF;
			FET_B_H_ON;
			FET_C_H_OFF; 
			FET_A_L_OFF;
			FET_B_L_OFF;
			FET_C_L_OFF;
			Motor_Config.Step = 1;
			Motor_Config.Next_Step = 2;
			break;
		case 2:
			FET_A_H_PWM_OFF;
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
			Motor_Config.Step = 2;
			Motor_Config.Next_Step = 3;
			break;
		case 3:
			FET_A_H_PWM_OFF;
			FET_B_H_PWM_OFF;
			FET_C_H_PWM_ON;
			FET_A_L_PWM_ON;
			FET_B_L_PWM_OFF;
			FET_C_L_PWM_OFF;
			FET_A_H_ON;
			FET_B_H_OFF;
			FET_C_H_OFF;
			FET_A_L_OFF;
			FET_B_L_OFF;
			FET_C_L_OFF;
			Motor_Config.Step = 3;
			Motor_Config.Next_Step = 4;
			break;
		case 4:
			FET_A_H_PWM_OFF;
			FET_B_H_PWM_ON;
			FET_C_H_PWM_OFF;
			FET_A_L_PWM_ON;
			FET_B_L_PWM_OFF;
			FET_C_L_PWM_OFF;
			FET_A_H_OFF;
			FET_B_H_OFF;
			FET_C_H_OFF; 
			FET_A_L_ON;
			FET_B_L_OFF;
			FET_C_L_OFF;
			Motor_Config.Step = 4;
			Motor_Config.Next_Step = 5;
			break;
		case 5:
			FET_A_H_PWM_OFF;
			FET_B_H_PWM_ON;
			FET_C_H_PWM_OFF;
			FET_A_L_PWM_OFF;
			FET_B_L_PWM_OFF;
			FET_C_L_PWM_ON;
			FET_A_H_OFF;
			FET_B_H_OFF;
			FET_C_H_OFF; 
			FET_A_L_OFF;
			FET_B_L_OFF;
			FET_C_L_ON;
			Motor_Config.Step = 5;
			Motor_Config.Next_Step = 6;
			break;
		case 6:
			FET_A_H_PWM_ON;
			FET_B_H_PWM_OFF;
			FET_C_H_PWM_OFF;
			FET_A_L_PWM_OFF;
			FET_B_L_PWM_OFF;
			FET_C_L_PWM_ON;
			FET_A_H_OFF;
			FET_B_H_OFF;
			FET_C_H_OFF;
			FET_A_L_OFF;
			FET_B_L_OFF;
			FET_C_L_ON;
			Motor_Config.Step = 6;
			Motor_Config.Next_Step = 1;
			break;
#endif
	}

	Demagnetic_Delay_Cnt = Demagnetic_Time / 10;
	if (Time_Flag==1)
	{
		
	}
	Commutation_Flag = 1;
	#if STEP_LED
	LED_Alert_Tongle();
	#endif
}

