#include "stm32f10x.h"                  // Device header

uint16_t  Num;

void Timer_Init(void)
{
	//ONE  OPEN TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); 
	
	//TWO Internal Clock
	TIM_InternalClockConfig(TIM2);
	
	//THREE Timer Init
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 7200 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1000 - 1; 
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	
	//FOUR  For EXTI TIM_ItConfig
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	//FIVE For NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	//SIX RUN 
	TIM_Cmd(TIM2,ENABLE);
}

//ÖÐ¶Ï
void TIM2_IRQHandler(void)
{
	if( TIM_GetITStatus(TIM2,TIM_IT_Update) == SET){
		Num ++;
		if(Num >= 200 ){
			Num = 0;
		}
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}


