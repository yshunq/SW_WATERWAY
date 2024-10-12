#include "count_sw_work.h"

void count_ll_value(void)
{
	LL.VALUE = (u8)(100*LL.CYCLE/LL.CONSTANT);
}

void count_sw_work_max_power(void)
{
	if(SW.BODY_PARTS == PARTS_ED){
		SW.MAX_POWER = 6;
	}else{
		SW.MAX_POWER = 10;
	}
	if(SW.POWER > SW.MAX_POWER)SW.POWER = SW.MAX_POWER;
}
























