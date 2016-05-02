#ifndef __ADC_H
#define	__ADC_H

void ADC_GPIO_Config(void);
void ADC_Mode_Config(void);
void ADC_PhaseDectectMode_Config();
void ADC_SetDetTime(int time);
extern volatile u16 ADC_Running_ConvertedValue[4];


#endif /* __ADC_H */

