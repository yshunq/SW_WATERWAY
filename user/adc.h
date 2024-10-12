
#ifndef _ADC_H
#define _ADC_H

#include "config.h"

#define ADC0	0
#define ADC1	1
#define ADC2	2
#define ADC3	3
#define ADC4	4
#define ADC5	5
#define ADC6	6

void ADC_Init(void);
float get_adc_temp(u8 adc);
float get_adc_val(u8 adc);//获取电压值

#endif