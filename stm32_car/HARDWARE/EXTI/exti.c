#include "exti.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "motor.h"

u8 static Go=0,L=0,R=0;

#define EDEBUG 1

//外部中断0服务程序
void EXTIX_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

     	
		//初始化GPIOA.0.2.3  下拉输入
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);//使能PORTA时钟，复用功能时钟

		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3;//PA0 2 3
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成下拉输入
		GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA0,2,3
	
#if EDEBUG  	
	
	/***************************************************************************************/
	
		//中断线以及中断初始化配置
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断模式
		//EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//上升沿
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
		EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
//  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);
		EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//KEY2
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

		//GPIOA.3	  中断线以及中断初始化配置 下降沿触发 //KEY3
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

	/***************************************************************************************/

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

//    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键KEY1所在的外部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

		NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY3所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
#endif

}

#if EDEBUG
//外部中断0服务程序 
void EXTI0_IRQHandler(void)
{
//	printf("\r\nexit0\r\n");
//	printf("\r\nKEY0=%d KEY2=%d KEY3=%d\r\n",KEY0,KEY2,KEY3);
	delay_ms(10);//消抖
	if(KEY0==1)	 	 //WK_UP按键
	{				 
		L=~L;
		LED=L;
		if(L)Left(500);
		else Stop();
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
}
////外部中断1服务程序
//void EXTI1_IRQHandler(void)
//{
//	printf("\r\nexit1\r\n");
//	printf("\r\nKEY0=%d KEY1=%d KEY2=%d KEY3=%d\r\n",KEY0,KEY1,KEY2,KEY3);
//	delay_ms(10);//消抖
//	if(KEY1==1)	 //按键KEY0
//	{
//		LED=!LED; 
//	}		 
//	EXTI_ClearITPendingBit(EXTI_Line4);  //清除LINE4上的中断标志位  
//}
//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
//	printf("\r\nexit2\r\n");
//	printf("\r\nKEY0=%d KEY2=%d KEY3=%d\r\n",KEY0,KEY2,KEY3);
	delay_ms(10);//消抖
	if(KEY2==1)	  //按键KEY2
	{
		R=~R;
		LED=R;
		if(R)Right(500);
		else Stop();
	}		 
	EXTI_ClearITPendingBit(EXTI_Line2);  //清除LINE2上的中断标志位  
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
//	printf("\r\nexit3\r\n");
//	printf("\r\nKEY0=%d KEY2=%d KEY3=%d\r\n",KEY0,KEY2,KEY3);
	delay_ms(10);//消抖
	if(KEY3==1)	 //按键KEY1
	{				 
		Go = ~Go;
		LED=Go;
		if(Go)Run(500);
		else Stop();
	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
}

#endif
