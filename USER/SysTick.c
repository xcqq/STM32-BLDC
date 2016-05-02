#include "SysTick.h"


static __IO u32 TimingDelay;


void SysTick_Init(void)
{
    /* SystemFrequency / 1000    1ms中断一次
     * SystemFrequency / 100000	 10us中断一次
     * SystemFrequency / 1000000 1us中断一次
     */
    if (SysTick_Config(SystemCoreClock / 1000000))	// ST3.5.0库版本
    {
        while (1);	
    }
    SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;// 关闭滴答定时器
}

void Delay_us(__IO u32 nTime)
{
    TimingDelay = nTime;
    SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;// 使能滴答定时器
    while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
	
{
    if(TimingDelay != 0x00)
    {
        TimingDelay--;
    }
}
