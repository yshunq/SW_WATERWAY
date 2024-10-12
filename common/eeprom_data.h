#ifndef __EEPROM_DATA_H
#define __EEPROM_DATA_H
#include "config.h"

void read_logo_flag(void);
void write_logo_flag(void);

void read_sw_power(u8 parts);
void write_sw_power(u8 parts);

void read_sw_frequency(u8 parts);
void write_sw_frequency(u8 parts);

void read_sw_preload_time(u8 parts);
void write_sw_preload_time(u8 parts);

void read_sw_probe_mode(u8 parts);
void write_sw_probe_mode(u8 parts);
void read_all_parameter(u8 parts);

void read_power_set_body_value(u8 num);
void write_power_set_body_value(u8 num);
void read_all_set_body_value(void);

void read_power_set_ed_value(u8 num);
void write_power_set_ed_value(u8 num);
void read_all_set_ed_value(void);

void read_ll_constant(void);
void write_ll_constant(void);

void read_ll_warning_flag(void);
void write_ll_warning_flag(void);

void read_ll_warning_value(void);
void write_ll_warning_value(void);

void read_handle_warning_flag(void);
void write_handle_warning_flag(void);

void read_handle_warning_value(void);
void write_handle_warning_value(void);

void read_handle_insert_warning_flag(void);
void write_handle_insert_warning_flag(void);

void read_eeprom_total_time(void);
void write_eeprom_total_time(void);

	
#endif
















