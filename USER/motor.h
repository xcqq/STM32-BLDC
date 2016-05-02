#ifndef MOTOR_H
#define MOTOR_H

#define MOTOR_TONE_1 2600/2
#define MOTOR_TONE_2 2924/2
#define MOTOR_TONE_3 3250/2
#define MOTOR_TONE_4 3466/2
#define MOTOR_TONE_5 3900/2
#define MOTOR_TONE_6 4332/2
#define MOTOR_TONE_7 4874/2
#define MOTOR_TONE_8 5200/2
void Motor_Init();
void Motor_Selftest();
void Motor_Start();
void Motor_Beep(uint16_t freq, uint16_t duration);
void Commutation_Detected_PWM_Off();
void Commutation_Detected_PWM_On();
void PID_Calc(PID_struct *PID, int Set, int In);
#endif	/* TIME_TEST_H */
