#include "motor.h"

//PB0 PB1��ʼ��
void Motor_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PC�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;				 //B0 B1 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB0 B1
	GPIO_ResetBits(GPIOB,GPIO_Pin_0 | GPIO_Pin_1);						 //PB0,B1 �����
}

//ֹͣ
void Stop(void)
{
	TIM_SetCompare1(TIM3,1000-0);//ռ�ձ�Ϊ0.0%
	PB0 = 0;
	TIM_SetCompare2(TIM3,1000-0);//ռ�ձ�Ϊ0.0%
	PB1 = 0;
}
//ǰ��
void Run(u16 speed)//ռ�ձ�Ϊspeed/1000
{
	if(speed > 1000) speed = 1000;
	TIM_SetCompare1(TIM3,1000-speed);//ռ�ձ�Ϊspeed/1000
	PB0 = 0;
	TIM_SetCompare2(TIM3,1000-speed);//ռ�ձ�Ϊspeed/1000
	PB1 = 0;
}

//ԭ����ת
void Left(u16 speed)//ռ�ձ�Ϊspeed/1000
{
	if(speed > 1000) speed = 1000;
	TIM_SetCompare1(TIM3,1000-0);//ռ�ձ�Ϊ0.0%
	PB0 = 0;
	TIM_SetCompare2(TIM3,1000-speed);//ռ�ձ�Ϊspeed/1000
	PB1 = 0;
}

//ԭ����ת
void Right(u16 speed)//ռ�ձ�Ϊspeed/1000
{
	if(speed > 1000) speed = 1000;
	TIM_SetCompare1(TIM3,1000-speed);//ռ�ձ�Ϊspeed/1000
	PB0 = 0;
	TIM_SetCompare2(TIM3,1000-0);//ռ�ձ�Ϊ0.0%
	PB1 = 0;
}
