#include "motor.h"

//PB0 PB1初始化
void Motor_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PC端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;				 //B0 B1 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB0 B1
	GPIO_ResetBits(GPIOB,GPIO_Pin_0 | GPIO_Pin_1);						 //PB0,B1 输出高
}

//停止
void Stop(void)
{
	TIM_SetCompare1(TIM3,1000-0);//占空比为0.0%
	PB0 = 0;
	TIM_SetCompare2(TIM3,1000-0);//占空比为0.0%
	PB1 = 0;
}
//前进
void Run(u16 speed)//占空比为speed/1000
{
	if(speed > 1000) speed = 1000;
	TIM_SetCompare1(TIM3,1000-speed);//占空比为speed/1000
	PB0 = 0;
	TIM_SetCompare2(TIM3,1000-speed);//占空比为speed/1000
	PB1 = 0;
}

//原地左转
void Left(u16 speed)//占空比为speed/1000
{
	if(speed > 1000) speed = 1000;
	TIM_SetCompare1(TIM3,1000-0);//占空比为0.0%
	PB0 = 0;
	TIM_SetCompare2(TIM3,1000-speed);//占空比为speed/1000
	PB1 = 0;
}

//原地右转
void Right(u16 speed)//占空比为speed/1000
{
	if(speed > 1000) speed = 1000;
	TIM_SetCompare1(TIM3,1000-speed);//占空比为speed/1000
	PB0 = 0;
	TIM_SetCompare2(TIM3,1000-0);//占空比为0.0%
	PB1 = 0;
}
