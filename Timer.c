#include "stm32f10x.h"                  // Device header


void Timer_Init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	//开启位于APB1的TIM2外设。一
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //A端口
	
	GPIO_InitTypeDef  GPIO_InitStruvture;   //A端口初始化
	GPIO_InitStruvture.GPIO_Mode = GPIO_Mode_IPU;  //不选浮空，选上拉稳定。
	GPIO_InitStruvture.GPIO_Pin = GPIO_Pin_0;  //A口0脚
	GPIO_InitStruvture.GPIO_Speed = GPIO_Speed_50MHz;  //A
	GPIO_Init(GPIOA,&GPIO_InitStruvture);   //A端口0脚初始化。
	
	
	
//	TIM_InternalClockConfig(TIM2);  //TIM2的驱动时钟由内部时钟驱动。二
	TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x00);//二步内部改为外部的PA0，不分频，不反向，不滤波。返回配置GPIO
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 	//这个是采样时的分频，是单片机为了提高准确度的参数，任选1.
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;  //选择向上计数模式。
	TIM_TimeBaseInitStruct.TIM_Period = 10 - 1;//周期，是ARR的值。改了
	TIM_TimeBaseInitStruct.TIM_Prescaler = 1-1;//是预分频器的值。
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;//重复次数计数器，高级计数器才有的，2号不用设。
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);		//初始化时基单元。三
	
	TIM_ClearFlag(TIM2,TIM_IT_Update); //在初始化之后，手动清除设置时置位的中断标志位防止手动调用。八
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //使能定时器中断，中断到NVIC通路，意思是中断到来时定时器是进中断还是进事件之类的，我们选择更新中断。四
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //优先级分组，2 bit pre-emption  2bit subpriority。五
	
	NVIC_InitTypeDef  NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //也需要选择下通道是TIM2_IRQn
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //开启这个通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //配合前面优先级设置小数字2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //配合前面优先级设置小数字1
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC这个模块。六
	
	TIM_Cmd(TIM2,ENABLE); //启动定时器。七
}


uint16_t Timer_GetCounter(void){
	return  TIM_GetCounter(TIM2);
}

/*
void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET ){
		Num ++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
*/











































