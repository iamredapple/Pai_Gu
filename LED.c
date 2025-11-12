#include "stm32f10x.h"                  // Device header

void LED_Init(void){	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    //A12
	GPIO_InitTypeDef  GPIO_InitStructure2;
	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure2);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //C区口的13，代表板载检测灯。
	GPIO_InitTypeDef  GPIO_InitStructure4;
	GPIO_InitStructure4.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure4.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure4.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure4);
}

//板载检测灯
//用这个LED0为例子。想让它亮，那么让它输出0.也说明LED0的另外一个脚是在+3.3V上。
void LED0_ON(void){
	GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET);
}
void LED0_OFF(void){
	GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET);
}



