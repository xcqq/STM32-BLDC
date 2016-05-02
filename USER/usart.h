#ifndef __USART_H
#define	__USART_H





#define USART1_DR_Base  0x40013804
#define SENDBUFF_SIZE 100
#define RECIVEBUFF_SIZE 100

void USART_Config(void);
int fputc(int ch, FILE *f);


#endif /* __USART_H */
