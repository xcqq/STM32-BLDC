#include "include_all.h"
#include "stm32f10x_iwdg.h"
void IWDG_Init()
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(1);
	IWDG_SetReload(50);
	IWDG_ReloadCounter();
	IWDG_Enable();
}
