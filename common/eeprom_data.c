#include "eeprom_data.h"

void read_logo_flag(void)
{
	LOGO_FLAG = AT24CXX_ReadOneByte(AD_LOGO_FLAG);
}

//void write_logo_flag(void)
//{
//  	AT24CXX_WriteOneByte(AD_LOGO_FLAG,LOGO_FLAG);
//}
//----------------------------------------------------------//
void read_sw_power(u8 parts)
{
	u8 ad;
	ad = 5*parts + AD_PARAMETER;
	SW.POWER = AT24CXX_ReadOneByte(ad);
	if(parts == PARTS_ED){
		if(SW.POWER == 0 || SW.POWER > 6){
			SW.POWER = 1;
			write_sw_power(parts);
		}
	}else{
		if(SW.POWER == 0 || SW.POWER > 10){
			SW.POWER = 1;
			write_sw_power(parts);
		}	
	}
}

void write_sw_power(u8 parts)
{
	u8 ad;
	ad = 5*parts + AD_PARAMETER;
	AT24CXX_WriteOneByte(ad,SW.POWER);	
}
//----------------------------------------------------------//
void read_sw_frequency(u8 parts)
{
	u8 ad;
	ad = 5*parts + AD_PARAMETER + 1;
	SW.FREQUENCY = AT24CXX_ReadOneByte(ad);
	if(SW.FREQUENCY == 0 || SW.FREQUENCY > 18){
		SW.FREQUENCY = 3;
		write_sw_frequency(parts);
	}
}

void write_sw_frequency(u8 parts)
{
	u8 ad;
	ad = 5*parts + AD_PARAMETER + 1;
	AT24CXX_WriteOneByte(ad,SW.FREQUENCY);	
}
//----------------------------------------------------------//
void read_sw_preload_time(u8 parts)
{
	u8 ad;
	ad = 5*parts + AD_PARAMETER + 2;
	SW.PRELOAD_TIME = AT24CXX_ReadOneByte(ad);
	SW.PRELOAD_TIME <<= 8;
	SW.PRELOAD_TIME |= AT24CXX_ReadOneByte(ad+1);
	if(SW.PRELOAD_TIME == 0 || SW.PRELOAD_TIME > 10000 || SW.PRELOAD_TIME%100 != 0){
		SW.PRELOAD_TIME = 2500;
		write_sw_preload_time(parts);	
	}
}

void write_sw_preload_time(u8 parts)
{
	u8 ad;
	ad = 5*parts + AD_PARAMETER + 2;
	AT24CXX_WriteOneByte(ad,SW.PRELOAD_TIME/256);
	AT24CXX_WriteOneByte(ad+1,SW.PRELOAD_TIME%256);	
}
//----------------------------------------------------------//
void read_sw_probe_mode(u8 parts)
{
	u8 ad;
	ad = 5*parts + AD_PARAMETER + 4;
	SW.PROBE_MODE = AT24CXX_ReadOneByte(ad);
	if(SW.PROBE_MODE > 4){
		SW.PROBE_MODE = 1;
		write_sw_probe_mode(parts);
	}
}

void write_sw_probe_mode(u8 parts)
{
	u8 ad;
	ad = 5*parts + AD_PARAMETER + 4;
	AT24CXX_WriteOneByte(ad,SW.PROBE_MODE);	
}
//----------------------------------------------------------//
void read_all_parameter(u8 parts)
{
	read_sw_power(parts);
	read_sw_frequency(parts);
	read_sw_preload_time(parts);
	read_sw_probe_mode(parts);
}
//----------------------------------------------------------//
void read_power_set_body_value(u8 num)
{
	u8 ad;
	ad = AD_POWER_SET_BODY_VALUE_START + num;
	SW.POWER_SET_BODY_VALUE[num] = AT24CXX_ReadOneByte(ad);
}

void write_power_set_body_value(u8 num)
{
	u8 ad;
	ad = AD_POWER_SET_BODY_VALUE_START + num;
	AT24CXX_WriteOneByte(ad,SW.POWER_SET_BODY_VALUE[num]);	
}
//----------------------------------------------------------//
void read_all_set_body_value(void)
{
	u8 i,flag;
	flag = 0;
	for(i=0;i<10;i++){
		read_power_set_body_value(i);
		if(i==0){
			if(SW.POWER_SET_BODY_VALUE[i] == 0){
				flag = 1;
				break;
			}	
		}else if(i < 9){
			if(SW.POWER_SET_BODY_VALUE[i-1] > SW.POWER_SET_BODY_VALUE[i]){
				flag = 1;
				break;
			}	
		}else if(i==9){
			if(SW.POWER_SET_BODY_VALUE[i] > 25){
				flag = 1;
				break;
			}
		}
	}
	if(flag == 1){
		SW.POWER_SET_BODY_VALUE[0] = 3;
		SW.POWER_SET_BODY_VALUE[1] = 4;
		SW.POWER_SET_BODY_VALUE[2] = 5;
		SW.POWER_SET_BODY_VALUE[3] = 6;
		SW.POWER_SET_BODY_VALUE[4] = 7;
		SW.POWER_SET_BODY_VALUE[5] = 8;
		SW.POWER_SET_BODY_VALUE[6] = 9;
		SW.POWER_SET_BODY_VALUE[7] = 10;
		SW.POWER_SET_BODY_VALUE[8] = 11;
		SW.POWER_SET_BODY_VALUE[9] = 12;
		for(i=0;i<10;i++)write_power_set_body_value(i);	
	}
}
//----------------------------------------------------------//
void read_power_set_ed_value(u8 num)
{
	u8 ad;
	ad = AD_POWER_SET_ED_VALUE_START + num;
	SW.POWER_SET_ED_VALUE[num] = AT24CXX_ReadOneByte(ad);
}

void write_power_set_ed_value(u8 num)
{
	u8 ad;
	ad = AD_POWER_SET_ED_VALUE_START + num;
	AT24CXX_WriteOneByte(ad,SW.POWER_SET_ED_VALUE[num]);	
}
//----------------------------------------------------------//
void read_all_set_ed_value(void)
{
	u8 i,flag;
	flag = 0;
	for(i=0;i<6;i++){
		read_power_set_ed_value(i);
		if(i==0){
			if(SW.POWER_SET_ED_VALUE[i] == 0){
				flag = 1;
				break;
			}	
		}else if(i < 5){
			if(SW.POWER_SET_ED_VALUE[i-1] > SW.POWER_SET_ED_VALUE[i]){
				flag = 1;
				break;
			}	
		}else if(i==5){
			if(SW.POWER_SET_ED_VALUE[i] > 25){
				flag = 1;
				break;
			}
		}
	}
	if(flag == 1){
		SW.POWER_SET_ED_VALUE[0] = 3;
		SW.POWER_SET_ED_VALUE[1] = 4;
		SW.POWER_SET_ED_VALUE[2] = 5;
		SW.POWER_SET_ED_VALUE[3] = 6;
		SW.POWER_SET_ED_VALUE[4] = 7;
		SW.POWER_SET_ED_VALUE[5] = 8;
		for(i=0;i<6;i++)write_power_set_ed_value(i);	
	}
}
//----------------------------------------------------------//
void read_ll_constant(void)
{
	LL.CONSTANT = AT24CXX_ReadOneByte(ADH_LL_CONSTANT);
	LL.CONSTANT <<= 8;
	LL.CONSTANT |= AT24CXX_ReadOneByte(ADL_LL_CONSTANT);
	if(LL.CONSTANT == 0 || LL.CONSTANT > 9900){
		LL.CONSTANT = 1390;
		write_ll_constant();
	}
}

void write_ll_constant(void)
{
	AT24CXX_WriteOneByte(ADH_LL_CONSTANT,LL.CONSTANT/256);
	AT24CXX_WriteOneByte(ADL_LL_CONSTANT,LL.CONSTANT%256);	
}
//----------------------------------------------------------//
void read_ll_warning_flag(void)
{
	LL.WARNING_FLAG = AT24CXX_ReadOneByte(AD_LL_WARNING_FLAG);
	if(LL.WARNING_FLAG > 1){
		LL.WARNING_FLAG = 0;
		write_ll_warning_flag();
	}
}

void write_ll_warning_flag(void)
{
	AT24CXX_WriteOneByte(AD_LL_WARNING_FLAG,LL.WARNING_FLAG);	
}
//----------------------------------------------------------//
void read_ll_warning_value(void)
{
	LL.WARNING_VALUE = AT24CXX_ReadOneByte(ADH_LL_WARNING_VALUE);
	LL.WARNING_VALUE <<= 8;
	LL.WARNING_VALUE |= AT24CXX_ReadOneByte(ADL_LL_WARNING_VALUE);
	if(LL.WARNING_VALUE == 0 || LL.WARNING_VALUE >= 100){
		LL.WARNING_VALUE = 30;
		write_ll_warning_value();
	}
}

void write_ll_warning_value(void)
{
	AT24CXX_WriteOneByte(ADH_LL_WARNING_VALUE,LL.WARNING_VALUE/256);
	AT24CXX_WriteOneByte(ADL_LL_WARNING_VALUE,LL.WARNING_VALUE%256);	
}
//----------------------------------------------------------//
void read_handle_warning_flag(void)
{
	HANDLE_TMEP.WARNING_FLAG = AT24CXX_ReadOneByte(AD_HANDLE_WARNING_FLAG);
	if(HANDLE_TMEP.WARNING_FLAG > 1){
		HANDLE_TMEP.WARNING_FLAG = 0;
		write_handle_warning_flag();
	}	
}
void write_handle_warning_flag(void)
{
	AT24CXX_WriteOneByte(AD_HANDLE_WARNING_FLAG,HANDLE_TMEP.WARNING_FLAG);
}
//----------------------------------------------------------//
void read_handle_warning_value(void)
{
	HANDLE_TMEP.WARNING_VALUE = AT24CXX_ReadOneByte(ADH_HANDLE_WARNING_VALUE);
	HANDLE_TMEP.WARNING_VALUE <<= 8;
	HANDLE_TMEP.WARNING_VALUE |= AT24CXX_ReadOneByte(ADL_HANDLE_WARNING_VALUE);
	if(HANDLE_TMEP.WARNING_VALUE == 0 || HANDLE_TMEP.WARNING_VALUE >= 950){
		HANDLE_TMEP.WARNING_VALUE = 800;
		write_handle_warning_value();
	}
}

void write_handle_warning_value(void)
{
	AT24CXX_WriteOneByte(ADH_HANDLE_WARNING_VALUE,HANDLE_TMEP.WARNING_VALUE/256);
	AT24CXX_WriteOneByte(ADL_HANDLE_WARNING_VALUE,HANDLE_TMEP.WARNING_VALUE%256);	
}
//----------------------------------------------------------//
void read_handle_insert_warning_flag(void)
{
	HANDLE_INSERT.WARNING_FLAG = AT24CXX_ReadOneByte(AD_HANDLE_INSERT_WARNING_FLAG);
	if(HANDLE_INSERT.WARNING_FLAG > 1){
		HANDLE_INSERT.WARNING_FLAG = 0;
		write_handle_insert_warning_flag();
	}	
}
void write_handle_insert_warning_flag(void)
{
	AT24CXX_WriteOneByte(AD_HANDLE_INSERT_WARNING_FLAG,HANDLE_INSERT.WARNING_FLAG);
}
//----------------------------------------------------------//
void read_eeprom_total_time(void)
{
	SW.EEPROM_TOTAL_TIME = AT24CXX_ReadOneByte(ADH_EEPROM_TOTAL_TIME);
    SW.EEPROM_TOTAL_TIME <<= 8;
	SW.EEPROM_TOTAL_TIME |= AT24CXX_ReadOneByte(ADM_EEPROM_TOTAL_TIME);
	SW.EEPROM_TOTAL_TIME <<= 8;
	SW.EEPROM_TOTAL_TIME |= AT24CXX_ReadOneByte(ADL_EEPROM_TOTAL_TIME);

	if(SW.EEPROM_TOTAL_TIME > 2000000){
		SW.EEPROM_TOTAL_TIME = 2000000;
		write_eeprom_total_time();
	}	
}
void write_eeprom_total_time(void)
{
	AT24CXX_WriteOneByte(ADH_EEPROM_TOTAL_TIME,SW.EEPROM_TOTAL_TIME/65536);
	AT24CXX_WriteOneByte(ADM_EEPROM_TOTAL_TIME,SW.EEPROM_TOTAL_TIME%65536/256);
	AT24CXX_WriteOneByte(ADL_EEPROM_TOTAL_TIME,SW.EEPROM_TOTAL_TIME%256);
}
//----------------------------------------------------------//

 

