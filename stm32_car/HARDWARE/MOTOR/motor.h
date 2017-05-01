#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

#define PB0 PBout(0)// PB0
#define PB1 PBout(1)// PB1
 

void Motor_Init(void);
//停止
void Stop(void);
//前进
void Run(u16 speed);//占空比为speed/1000
//原地左转
void Left(u16 speed);//占空比为speed/1000
//原地右转
void Right(u16 speed);//占空比为speed/1000

#endif
