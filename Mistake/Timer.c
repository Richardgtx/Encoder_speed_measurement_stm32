#include "stm32f10x.h"                  // Device header
uint16_t Num;
void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	TIM_ETRClockMode1Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0);
	TIM_TimeBaseInitTypeDef Sa;
	Sa.TIM_CounterMode=TIM_CounterMode_Up;
	Sa.TIM_Prescaler=1-1;
	Sa.TIM_RepetitionCounter=0x10;
	Sa.TIM_ClockDivision=TIM_CKD_DIV1;
	Sa.TIM_Period=10-1;
	TIM_TimeBaseInit(TIM2,&Sa);
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_EventSource_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	TIM_Cmd(TIM2,ENABLE);
	TIM_ARRPreloadConfig(TIM2,ENABLE);
}
uint16_t Timer_get(void)
{
	return Num;
}
//void TIM2_IRQHandler(void)
//{
//	//if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
//	//{
//		Num++;
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	//}
//}
