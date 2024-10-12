#include "other.h"

u16 get_sw_work_handle_temp(void)
{
	float temp;
	temp = get_adc_temp(ADC2);
	return (u16)(temp*10);
}









