#include "include_all.h"
int PWM_CCR1,PWM_CCR2;
//取消通道1,比较中断
void TIM2_IRQ1_OFF(void)
{
	TIM2->DIER &= (uint16_t)~TIM_IT_CC1;
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
}
//取消通道2,比较中断
void TIM2_IRQ2_OFF(void)
{
	TIM2->DIER &= (uint16_t)~TIM_IT_CC2;
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);
}
void TIM2_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	// Enable the TIM2 global Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	// Time base configuration
	TIM_TimeBaseStructure.TIM_Prescaler = (72 ) - 1;   //分频
	TIM_TimeBaseStructure.TIM_Period = 1000;                   //自动重载寄存器
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                 //分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	//取消1 2 3路 比较中断
	TIM2_IRQ1_OFF();
	TIM2_IRQ2_OFF();

	// Output Compare for IRQ
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);

	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Disable);

	TIM_ARRPreloadConfig(TIM2, ENABLE); //ARR有缓冲器
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM2, ENABLE); //开启计数器
}
//
void TIM2_Set_Commutation_Good(int us)
{
	if (us<=20)
	{
		TIM2->DIER &= (uint16_t)~TIM_IT_CC1;
		Motor_Switch_Step(Motor_Config.NextStep_Detect);
	}
	else if ((us+TIM_GetCounter(TIM2))<=999)
	{
		TIM2->CCR1 = TIM_GetCounter(TIM2) + us; //设备捕获比较中断寄存器
		//TIM2->SR = (uint16_t)~TIM_IT_CC1;
		TIM2->DIER |= TIM_IT_CC1; //开中断
	}
	else
	{
		TIM2->DIER &= (uint16_t)~TIM_IT_CC1; 
		Time_Delay1_us = us + TIM_GetCounter(TIM2);
		Time_Delay1_Switch = 1;
	}
	
}
//被fet.c使用 电调的主要控制逻辑部分
void TIM2_Set_Commutation_Bad(int us)
{
	if (us <= 20)
	{
		TIM2->DIER &= (uint16_t)~TIM_IT_CC2;
		TIM2->SR = (uint16_t)~TIM_IT_CC2;
		Motor_Switch_Step(Motor_Config.Next_Step);
		Motor_Config.BadStep_Cnt++;
	}
	else if ((us + TIM_GetCounter(TIM2)) <= 999)
	{
		TIM2->CCR2 = TIM_GetCounter(TIM2) + us; //设备捕获比较中断寄存器
		//TIM2->SR = (uint16_t)~TIM_IT_CC2;
		TIM2->DIER |= TIM_IT_CC2;
	}
	else
	{
		TIM2->DIER &= (uint16_t)~TIM_IT_CC2;
		TIM2->SR = (uint16_t)~TIM_IT_CC2;
		Time_Delay2_us = us + TIM_GetCounter(TIM2); 
		Time_Delay2_Switch = 1;
	}
}
void TIM2_IRQHandler()
{
	static uint16_t Motor_Beep_Cnt = 0;
	static int Motor_Speed_Cnt = 0;
	static int No_Signal_Cnt=0;
	static char No_Signal_Flag=1;
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
	{
		TIM2->SR = (uint16_t)~TIM_IT_CC1;
		TIM2->DIER &= (uint16_t)~TIM_IT_CC1;
		Time_Delay1_Switch = 0;
		Motor_Switch_Step(Motor_Config.NextStep_Detect);
	}
	else if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
	{
		TIM2->SR = (uint16_t)~TIM_IT_CC2;
		TIM2->DIER &= (uint16_t)~TIM_IT_CC2;
		Time_Delay2_Switch = 0;
		Motor_Switch_Step(Motor_Config.Next_Step);
		Motor_Config.BadStep_Cnt++;
	}
	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		TIM_ClearFlag(TIM2, TIM_FLAG_Update);
		IWDG_ReloadCounter();//喂狗
		if (Time_Delay1_Switch == 1)
		{
			Time_Delay1_us -= 999; 
			if (Time_Delay1_us <= 20)
			{
				Motor_Switch_Step(Motor_Config.NextStep_Detect);
				TIM2->SR = (uint16_t)~TIM_IT_CC1;
				TIM2->DIER &= (uint16_t)~TIM_IT_CC1;
				Time_Delay1_Switch = 0;
			}
			else if (Time_Delay1_us <= 999)
			{
				TIM2->CCR1 = Time_Delay1_us; //设备捕获比较中断寄存器
				//TIM2->SR = (uint16_t)~TIM_IT_CC1;
				TIM2->DIER |= TIM_IT_CC1; //开中断
			}
		}
		if (Time_Delay2_Switch == 1)
		{
			Time_Delay2_us -= 999;
			if (Time_Delay2_us <= 20)
			{
				Motor_Switch_Step(Motor_Config.Next_Step);
				Motor_Config.BadStep_Cnt++;
				TIM2->SR = (uint16_t)~TIM_IT_CC2;
				TIM2->DIER &= (uint16_t)~TIM_IT_CC2;
				Time_Delay2_Switch = 0;
			}
			else if (Time_Delay2_us <= 999)
			{
				TIM2->CCR2 = Time_Delay2_us; //设备捕获比较中断寄存器
				//TIM2->SR = (uint16_t)~TIM_IT_CC2;
				TIM2->DIER |= TIM_IT_CC2; //开中断
			}
		}
		//判定有没有输入信号
        if (TIM_GetITStatus(TIM1, TIM_IT_CC2)==0)
		{
			if(No_Signal_Flag==0) No_Signal_Cnt++;
            if (No_Signal_Cnt>=500)
				No_Signal_Flag=1;
        }
		else
		{
			No_Signal_Flag=0;
			No_Signal_Cnt=0;
			PPM_Signal=TIM_GetCapture2(TIM1);
		}
		//根据有无信号执行
		if (No_Signal_Flag == 0)
		{

			switch (Motor_Status)
			{
				case Running:
					if (PPM_Signal >= 1000)
					{
						Motor_Config.Duty = PPM_Signal - 1000;
						if (Motor_Config.Duty >= 999) Motor_Config.Duty = 999;
						else if (Motor_Config.Duty <= 5) Motor_Config.Duty = 5;
					}
					else
					{
						Motor_Status = Stop;
						Motor_Config.Duty = 0;
						Motor_Setduty(0);
					}
					break;
				case Standby: //就绪状态 等待油门大于0
					if (PPM_Signal >= 1000) Motor_Status = Start;
					break;
				case Stop:
				case Error: //停止或者出错 等待油门归0进入standby
					if (PPM_Signal < 1000)
					{
						Motor_Status = Standby;
					}
					Motor_Beep_Cnt++;
					if (Motor_Beep_Cnt == 4000)
					{
						Motor_Beep_Flag = 1;
						Motor_Beep_Cnt = 0;
					}
					break;

			}
		}
		else
		{
			if (Motor_Status!=Stop)
			{
				Motor_Status = Stop;
				Motor_Config.Duty = 0;
				Motor_Setduty(0);
			}
			else
			Motor_Beep_Cnt++;
			if (Motor_Beep_Cnt == 4000)
			{
				Motor_Beep_Flag = 1;
				Motor_Beep_Cnt = 0;
			}
		}
		if ((Motor_Status == Running) || (Motor_Status == Start))
		{
			Motor_Speed_Cnt++;
			if (Motor_Speed_Cnt == 10)
			{
				Time_Flag = 1;
				//PID_Calc(&Speed_PID, Motor_Config.Set_Speed, Motor_Config.Speed);
				//if (Speed_PID.Out < 10) Speed_PID.Out = 10;
				//Motor_Config.Duty = Speed_PID.Out;
				//Motor_Setduty(100);
				Motor_Speed_Cnt = 0;
			}
			if (Motor_Config.BadStep_Cnt >= 50)
			{
				Motor_Status = Error;
				Motor_Error_Reason = Commutation_Error;
				Motor_Config.Duty = 0;
				Motor_Setduty(0);
				Motor_Config.BadStep_Cnt = 0;
			}
		}
		Time_Cnt_ms++;
		TIM_ClearITPendingBit(TIM1,TIM_IT_CC2);
		if ((Motor_Status == Running) || (Motor_Status == Start))
		{
			Motor_Setduty(Motor_Config.Duty); 
		}
	}
}
void Get_Time()
{
	Motor_Config.Commutation_Time_us = Time_Cnt_ms * 1000 + TIM_GetCounter(TIM2) - Time_Cnt_us;
	if (Motor_Config.Commutation_Time_us>=500000)
	{
		Motor_Config.Commutation_Time_us = 500000;
	}
	Motor_Config.Speed = Motor_Config.GoodStep_Cnt  * 1000000 / Motor_Config.Commutation_Time_us;
	Motor_Config.GoodStep_Cnt = 0; 
	Time_Flag = 0;
	Time_Cnt_ms = 0;
	Time_Cnt_us = TIM_GetCounter(TIM2);
}

void PWMInput_Init()
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_DeInit(TIM1);

	TIM_TimeBaseStructure.TIM_Prescaler = (72) - 1;   //分频
	TIM_TimeBaseStructure.TIM_Period = 10000;                   //自动重载寄存器
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                 //分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);


	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0;
	TIM_PWMIConfig(TIM1, &TIM_ICInitStructure);
	TIM_SelectInputTrigger(TIM1, TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);
	TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);

	TIM_ITConfig(TIM1, TIM_IT_CC2, ENABLE);

	TIM_Cmd(TIM1, ENABLE);
}
