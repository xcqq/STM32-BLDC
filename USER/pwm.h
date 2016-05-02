#ifndef __PWM_H
#define	__PWM_H

#include "stm32f10x.h"

//PWM输出管教定义
#define  FET_AH_PIN      GPIO_Pin_6  
#define  FET_AH_PORT     GPIOB

#define  FET_BH_PIN      GPIO_Pin_7
#define  FET_BH_PORT     GPIOB

#define  FET_CH_PIN      GPIO_Pin_8
#define  FET_CH_PORT     GPIOB

#define  FET_AL_PIN      GPIO_Pin_7
#define  FET_AL_PORT     GPIOA

#define  FET_BL_PIN      GPIO_Pin_0
#define  FET_BL_PORT     GPIOB

#define  FET_CL_PIN      GPIO_Pin_1
#define  FET_CL_PORT     GPIOB

//GPIO 模式  设置为输出0
#define FET_A_L_OFF GPIO_SetBits(FET_AL_PORT, FET_AL_PIN)//GPIO AL OFF
#define FET_B_L_OFF GPIO_SetBits(FET_BL_PORT, FET_BL_PIN)//GPIO BL OFF
#define FET_C_L_OFF GPIO_SetBits(FET_CL_PORT, FET_CL_PIN)//GPIO CL OFF
#define FET_A_H_OFF GPIO_ResetBits(FET_AH_PORT, FET_AH_PIN)//GPIO AH OFF
#define FET_B_H_OFF GPIO_ResetBits(FET_BH_PORT, FET_BH_PIN)//GPIO BH OFF
#define FET_C_H_OFF GPIO_ResetBits(FET_CH_PORT, FET_CH_PIN)//GPIO CH OFF
//GPIO 模式  设置为输出1
#define FET_A_L_ON GPIO_ResetBits(FET_AL_PORT, FET_AL_PIN)//GPIO AL ON
#define FET_B_L_ON GPIO_ResetBits(FET_BL_PORT, FET_BL_PIN)//GPIO BL ON
#define FET_C_L_ON GPIO_ResetBits(FET_CL_PORT, FET_CL_PIN)//GPIO CL ON
#define FET_A_H_ON GPIO_SetBits(FET_AH_PORT, FET_AH_PIN)//GPIO AH ON
#define FET_B_H_ON GPIO_SetBits(FET_BH_PORT, FET_BH_PIN)//GPIO BH ON
#define FET_C_H_ON GPIO_SetBits(FET_CH_PORT, FET_CH_PIN)//GPIO CH ON


#define FET_A_H_PWM_OFF TIM_CCxCmd(FET_H_TIMER, TIM_Channel_1, TIM_CCx_Disable);GPIOA->CRL&=0x0FFFFFFF;
#define FET_B_H_PWM_OFF TIM_CCxCmd(FET_H_TIMER, TIM_Channel_2, TIM_CCx_Disable);GPIOB->CRL&=0xFFFFFFF0;
#define FET_C_H_PWM_OFF TIM_CCxCmd(FET_H_TIMER, TIM_Channel_3, TIM_CCx_Disable);GPIOB->CRL&=0xFFFFFF0F;
#define FET_A_H_PWM_ON TIM_CCxCmd(FET_H_TIMER, TIM_Channel_1, TIM_CCx_Enable);GPIOA->CRL&=0x0FFFFFFF;
#define FET_B_H_PWM_ON TIM_CCxCmd(FET_H_TIMER, TIM_Channel_2, TIM_CCx_Enable);GPIOB->CRL&=0xFFFFFFF0;
#define FET_C_H_PWM_ON TIM_CCxCmd(FET_H_TIMER, TIM_Channel_3, TIM_CCx_Enable);GPIOB->CRL&=0xFFFFFF0F;
#define FET_A_L_PWM_OFF TIM_CCxCmd(FET_L_TIMER, TIM_Channel_2, TIM_CCx_Disable);GPIOA->CRL|=0x30000000;
#define FET_B_L_PWM_OFF TIM_CCxCmd(FET_L_TIMER, TIM_Channel_3, TIM_CCx_Disable);GPIOB->CRL|=0x00000003;
#define FET_C_L_PWM_OFF TIM_CCxCmd(FET_L_TIMER, TIM_Channel_4, TIM_CCx_Disable);GPIOB->CRL|=0x00000030;
#define FET_A_L_PWM_ON TIM_CCxCmd(FET_L_TIMER, TIM_Channel_2, TIM_CCx_Enable);GPIOA->CRL|=0xB0000000;
#define FET_B_L_PWM_ON TIM_CCxCmd(FET_L_TIMER, TIM_Channel_3, TIM_CCx_Enable);GPIOB->CRL|=0x0000000B;
#define FET_C_L_PWM_ON TIM_CCxCmd(FET_L_TIMER, TIM_Channel_4, TIM_CCx_Enable);GPIOB->CRL|=0x000000B0;

#define FET_H_TIMER        TIM4
#define FET_L_TIMER     TIM3

void PWM_Config(void);
void PWM_OnePulse_Config();
void PWM_Mode_Switch(char Switch);
void Motor_Setduty(uint16_t duty);
void Motor_Switch_Step(u8 step);
#endif /* __PWM_H */

