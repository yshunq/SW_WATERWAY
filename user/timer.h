
#ifndef _TIMER_H
#define _TIMER_H

#include "config.h"

extern xdata unsigned long SYSTEM_CC;

u8 count_time_1ms(u8 clear);
u8 count_time_100ms(u8 clear);
void delay_ms(unsigned long ms);
void Timer1_Init(void);

#endif