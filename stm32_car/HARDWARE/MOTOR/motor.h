#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

#define PB0 PBout(0)// PB0
#define PB1 PBout(1)// PB1
 

void Motor_Init(void);
//ֹͣ
void Stop(void);
//ǰ��
void Run(u16 speed);//ռ�ձ�Ϊspeed/1000
//ԭ����ת
void Left(u16 speed);//ռ�ձ�Ϊspeed/1000
//ԭ����ת
void Right(u16 speed);//ռ�ձ�Ϊspeed/1000

#endif
