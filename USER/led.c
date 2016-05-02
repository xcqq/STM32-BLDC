#include "include_all.h"

void LED_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin = LED_ALERT_PIN;
    GPIO_Init(LED_ALERT_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = LED_POWER_PIN;
    GPIO_Init(LED_POWER_PORT, &GPIO_InitStructure);

    GPIO_SetBits(LED_ALERT_PORT, LED_ALERT_PIN);
    GPIO_SetBits(LED_POWER_PORT, LED_POWER_PIN);
}
void LED_Power_Tongle()
{
    if (GPIO_ReadOutputDataBit(LED_POWER_PORT,LED_POWER_PIN))
    {
        GPIO_ResetBits(LED_POWER_PORT,LED_POWER_PIN);
    }
    else
    {
        GPIO_SetBits(LED_POWER_PORT,LED_POWER_PIN);
    }
}
void LED_Alert_Tongle()
{
    if (GPIO_ReadOutputDataBit(LED_ALERT_PORT,LED_ALERT_PIN))
    {
        GPIO_ResetBits(LED_ALERT_PORT,LED_ALERT_PIN);
    }
    else
    {
        GPIO_SetBits(LED_ALERT_PORT,LED_ALERT_PIN);
    }
}
