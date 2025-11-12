#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void Key_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);    //B区口的1
	GPIO_InitTypeDef  GPIO_InitStructure3;		
	GPIO_InitStructure3.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure3.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure3.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure3);
}

//利用函数读取口的值
uint8_t Key_GetNum(void){
	uint8_t KeyNum = 0;
	if( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0){
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0); 
		Delay_ms(20);
		KeyNum = 1;
	}
	return KeyNum;
}

