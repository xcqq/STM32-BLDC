#ifndef TIMER_H
#define TIMER_H

void TIM2_Config(void);
void TIM2_Set_Commutation_Good(int us);
void TIM2_Set_Commutation_Bad(int us);
void PWMInput_Init();
void Get_Time();

#endif	/* TIME_TEST_H */
