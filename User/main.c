#include "stm32f10x.h"  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Encoder.h"
int16_t Speed;
int main(void)
{
	OLED_Init();
	OLED_ShowString(1,1,"Speed:");
	Encoder_Init();
	Timer_Init();
	
	
	while(1)
	{
//		OLED_ShowNum(1,5,Timer_get(),5);
		
		OLED_ShowSignedNum(1,8,Speed,5);
		
	}
}
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		Speed=Encoder_Get();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
