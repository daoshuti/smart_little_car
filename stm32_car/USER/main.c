#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include "exti.h"
#include "motor.h"

void car_move(void);

int main(void)
{
	u16 len;
	LED_Init();			     //LED�˿ڳ�ʼ��	
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
	TIM2_Int_Init(10-1,72-1);//10Khz�ļ���Ƶ�ʣ�������10Ϊ10us=0.01ms 
	TIM3_PWM_Init(1000-1,72-1);	 //����Ƶ��PWMƵ��=72000000/72/1000=1Khz
	EXTIX_Init();				//�ⲿ�жϳ�ʼ��
	Motor_Init();				//������Ƴ�ʼ��
	
	//����ʱ��ֹͣ
	TIM_SetCompare1(TIM3,1000-0);//��ʼռ�ձ�0.0%
	TIM_SetCompare2(TIM3,1000-0);//��ʼռ�ձ�0.0%
	
	//����ϵ�У׼
	set_cmp(50);//ƫ�Ƶ�ԭ��
	delay_ms(500);
	set_cmp(150);//�ص�90��λ��
	
//	//���ڿ�����ʾ
//	printf("\r\nhello World! I am car��\r\n");
	while(1) 
	{
		if(USART_RX_STA&0x8000) //����յ�����
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���

			//���յ������ݽ��д���
			if(USART_RX_BUF[0] == 'U')//�ж�֡ͷ
			{
				switch(USART_RX_BUF[1])
				{
					case 't':
						break;
					case 'h':
						break;
					case 'm':
						car_move();
						break;
					default:
						break;
				}

			}
			USART_RX_STA=0;
		}
	}	  
	
}

//С���ƶ�����
void car_move(void)
{
	if(USART_RX_BUF[2] == 'w')
	{
		switch(USART_RX_BUF[3])
		{
			case 'w':
				Run(500);
				printf("Dmrw\r\n");
				break;
			case 's':
				Stop();
				printf("Dmrs\r\n");
				break;
			case 'a':
				Left(500);
				printf("Dmra\r\n");
				break;
			case 'd':
				Right(500);
				printf("Dmrd\r\n");
				break;
			default:
				break;
		}
	}
}

