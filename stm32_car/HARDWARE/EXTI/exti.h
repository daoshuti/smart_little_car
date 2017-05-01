#ifndef __EXTI_H
#define __EXIT_H

#include "sys.h"

#define KEY0  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键0
//#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)//读取按键1
#define KEY2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)//读取按键2
#define KEY3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)//读取按键3

void EXTIX_Init(void);//外部中断初始化		 					    

#endif

