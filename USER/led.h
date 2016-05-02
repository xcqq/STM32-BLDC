#ifndef __LED_H
#define	__LED_H

#define LED_POWER_PORT GPIOB
#define LED_ALERT_PORT GPIOB
#define LED_POWER_PIN GPIO_Pin_5
#define LED_ALERT_PIN GPIO_Pin_9

#define LED_ALERT_OFF GPIO_SetBits(LED_ALERT_PORT,LED_ALERT_PIN)
#define LED_ALERT_ON GPIO_ResetBits(LED_ALERT_PORT,LED_ALERT_PIN)
#define LED_POWER_OFF GPIO_SetBits(LED_POWER_PORT,LED_POWER_PIN)
#define LED_POWER_ON GPIO_ResetBits(LED_POWER_PORT,LED_POWER_PIN)

void LED_GPIO_Config(void);
void LED_Power_Tongle();
void LED_Alert_Tongle();
#endif /* __LED_H */
