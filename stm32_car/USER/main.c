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
	LED_Init();			     //LED端口初始化	
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 //串口初始化为9600
	TIM2_Int_Init(10-1,72-1);//10Khz的计数频率，计数到10为10us=0.01ms 
	TIM3_PWM_Init(1000-1,72-1);	 //不分频。PWM频率=72000000/72/1000=1Khz
	EXTIX_Init();				//外部中断初始化
	Motor_Init();				//电机控制初始化
	
	//开机时车停止
	TIM_SetCompare1(TIM3,1000-0);//初始占空比0.0%
	TIM_SetCompare2(TIM3,1000-0);//初始占空比0.0%
	
	//舵机上电校准
	set_cmp(50);//偏移到原点
	delay_ms(500);
	set_cmp(150);//回到90度位置
	
//	//串口开机提示
//	printf("\r\nhello World! I am car！\r\n");
	while(1) 
	{
		if(USART_RX_STA&0x8000) //如果收到数据
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度

			//对收到的数据进行处理
			if(USART_RX_BUF[0] == 'U')//判断帧头
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

//小车移动控制
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

