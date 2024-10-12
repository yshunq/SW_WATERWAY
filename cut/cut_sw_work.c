#include "cut_sw_work.h"


void cut_sw_work_lock_flag(u8 flag)
{
	u8 pic;
	pic = Pic_SW_WORK_START + SW.BODY_PARTS;
	if(flag == 0){
		DIS_DEL_DIS(Pic_SW_WORK_DOWN,1052,723,1167,799,1052,723);
	}else{
		DIS_DEL_DIS(pic,1052,723,1167,799,1052,723);
	}	
}


void cut_sw_work_start_stop_flag(u8 flag)
{
	u8 pic;
	pic = Pic_SW_WORK_START + SW.BODY_PARTS;
	if(flag == 0){
		DIS_DEL_DIS(Pic_SW_WORK_DOWN,75,620,430,695,75,620);
	}else{
		DIS_DEL_DIS(pic,75,620,430,695,75,620);
	}	
}

void cut_sw_work_probe_mode(void)
{
	u8 pic;
	pic = Pic_SW_PROBE_START + SW.PROBE_MODE;
	switch(SW.PROBE_MODE){
		case PROBE_D8: DIS_DEL_DIS(pic,469,723,620,799,469,723);break;
		case PROBE_D15:DIS_DEL_DIS(pic,469,723,620,799,469,723);break;
		case PROBE_C15:DIS_DEL_DIS(pic,469,723,620,799,469,723);break;
		case PROBE_D20:DIS_DEL_DIS(pic,469,723,620,799,469,723);break;
		case PROBE_D32:DIS_DEL_DIS(pic,469,723,620,799,469,723);break;
	}
}

void cut_sw_work_flow_warning(void)
{
	DIS_DEL_DIS(Pic_ERROR1,1,1,500,350,390,225);
}

void cut_sw_work_handle_temp_high(void)
{
	DIS_DEL_DIS(Pic_ERROR1,502,352,1001,701,390,225);
}

void cut_sw_work_handle_temp_short(void)
{
	DIS_DEL_DIS(Pic_ERROR1,502,1,1001,350,390,225);
}

void cut_sw_work_handle_temp_open(void)
{
	DIS_DEL_DIS(Pic_ERROR1,1,352,500,701,390,225);
}

void cut_sw_work_handle_insert_warning(void)
{
	DIS_DEL_DIS(Pic_ERROR2,1,1,500,350,390,225);
}

void cut_sw_work_preset_value_varning(void)
{
	DIS_DEL_DIS(Pic_ERROR2,1,352,500,701,390,225);
	//DIS_DEL_DIS(Pic_ERROR2,502,1,1001,350,390,225);
}

void cut_sw_work_internal_power_varning(void)
{
	DIS_DEL_DIS(Pic_ERROR2,502,1,1001,350,390,225);
}







