#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"
#include "Timer.h"
#include "OLED.h"
extern uint16_t Num;  //自用，在Timer中的，此处extern是 勤恳的去找。

int main(){
//自用	
#define LED_0SET GPIO_SetBits(GPIOC,GPIO_Pin_13)
#define LED_0RESET GPIO_ResetBits(GPIOC,GPIO_Pin_13)
#define LED_1SET GPIO_SetBits(GPIOA,GPIO_Pin_12)
#define LED_1RESET GPIO_ResetBits(GPIOA,GPIO_Pin_12)
	Timer_Init();	LED_Init();		OLED_Init();
	while(Num <= 40){
		if   (   ( (Num-1) % 6) < 3 ){	LED_0SET;	LED_1RESET;
		} else {	LED_0RESET;	LED_1SET;		}
	}	LED_0RESET;	LED_1SET;
	OLED_ShowString(4,12,"Hello");
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,DISABLE); //省电，关闭Timer 。
//正式	
	
	while(1){
		
	} //This is while
} //This is main



