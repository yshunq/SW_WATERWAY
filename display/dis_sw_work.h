#ifndef _DIS_SW_WORK_H
#define _DIS_SW_WORK_H
#include "config.h"

void dis_sw_work_power(u8 dis);
void dis_sw_work_frequency(u8 dis);
void dis_sw_work_preload_time(u8 dis);
void dis_sw_work_total_time(u8 dis);
void dis_sw_work_body_parts(void);
void dis_sw_work_ll_value(u8 dis);
void dis_sw_work_time(u8 dis);
void dis_sw_work_handle_temp(u8 dis,u16 temp);

#endif