
#ifndef _CUT_SW_WORK_H
#define _CUT_SW_WORK_H

#include "config.h"

void cut_sw_work_probe_mode(void);
void cut_sw_work_start_stop_flag(u8 flag);
void cut_sw_work_lock_flag(u8 flag);
void cut_sw_work_flow_warning(void);
void cut_sw_work_handle_temp_high(void);
void cut_sw_work_handle_temp_short(void);
void cut_sw_work_handle_temp_open(void);
void cut_sw_work_handle_insert_warning(void);
void cut_sw_work_preset_value_varning(void);
void cut_sw_work_internal_power_varning(void);

#endif