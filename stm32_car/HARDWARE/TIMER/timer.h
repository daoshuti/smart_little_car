#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

void set_cmp(u32 val);
void TIM2_Int_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);
#endif
