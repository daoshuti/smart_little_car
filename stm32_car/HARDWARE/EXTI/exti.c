#include "exti.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "motor.h"

u8 static Go=0,L=0,R=0;

#define EDEBUG 1

//�ⲿ�ж�0�������
void EXTIX_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

     	
		//��ʼ��GPIOA.0.2.3  ��������
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);//ʹ��PORTAʱ�ӣ����ù���ʱ��

		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3;//PA0 2 3
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
		GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA0,2,3
	
#if EDEBUG  	
	
	/***************************************************************************************/
	
		//�ж����Լ��жϳ�ʼ������
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж�ģʽ
		//EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½���
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//������
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
		EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
//  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);
		EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//KEY2
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

		//GPIOA.3	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY3
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

	/***************************************************************************************/

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

//    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�2
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
//  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

		NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܰ���KEY3���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
#endif

}

#if EDEBUG
//�ⲿ�ж�0������� 
void EXTI0_IRQHandler(void)
{
//	printf("\r\nexit0\r\n");
//	printf("\r\nKEY0=%d KEY2=%d KEY3=%d\r\n",KEY0,KEY2,KEY3);
	delay_ms(10);//����
	if(KEY0==1)	 	 //WK_UP����
	{				 
		L=~L;
		LED=L;
		if(L)Left(500);
		else Stop();
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
}
////�ⲿ�ж�1�������
//void EXTI1_IRQHandler(void)
//{
//	printf("\r\nexit1\r\n");
//	printf("\r\nKEY0=%d KEY1=%d KEY2=%d KEY3=%d\r\n",KEY0,KEY1,KEY2,KEY3);
//	delay_ms(10);//����
//	if(KEY1==1)	 //����KEY0
//	{
//		LED=!LED; 
//	}		 
//	EXTI_ClearITPendingBit(EXTI_Line4);  //���LINE4�ϵ��жϱ�־λ  
//}
//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
//	printf("\r\nexit2\r\n");
//	printf("\r\nKEY0=%d KEY2=%d KEY3=%d\r\n",KEY0,KEY2,KEY3);
	delay_ms(10);//����
	if(KEY2==1)	  //����KEY2
	{
		R=~R;
		LED=R;
		if(R)Right(500);
		else Stop();
	}		 
	EXTI_ClearITPendingBit(EXTI_Line2);  //���LINE2�ϵ��жϱ�־λ  
}
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
//	printf("\r\nexit3\r\n");
//	printf("\r\nKEY0=%d KEY2=%d KEY3=%d\r\n",KEY0,KEY2,KEY3);
	delay_ms(10);//����
	if(KEY3==1)	 //����KEY1
	{				 
		Go = ~Go;
		LED=Go;
		if(Go)Run(500);
		else Stop();
	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}

#endif
