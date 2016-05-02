#include "include_all.h"
int main()
{
	SystemInit();
	SysTick_Init();
	Variable_Init(); 
	LED_GPIO_Config();
	USART_Config();
	ADC_Mode_Config();
	PWM_Config();
	TIM2_Config();
	USART_Config();
	PWMInput_Init();
	IWDG_Init();
	while (1)
	{
		if (Motor_Beep_Flag==1)
		{
			Motor_Beep(MOTOR_TONE_8, 200);
			Motor_Beep_Flag = 0;
		}
		if (Motor_Status==Start)
		{
			Motor_Start();
		}
		printf("%d", Voltage.Current);
	}
}
