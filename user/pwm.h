
#ifndef _PWM_H
#define _PWM_H

#include "config.h"

void hf_pwm_init(void);
void open_hf_pwm(u16 temp);
void close_hf_pwm(void);

void rf_pwm_init(void);
void open_rf_pwm(u16 temp);
void close_rf_pwm(void);

#endif