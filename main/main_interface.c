#include "config.h"

void jump_interface(void)
{
	while(1){
		Uart_LCD.KEY_YES = 0;
		switch(INTERFACE){
			case  PAGE_SW_WORK:
				main_xs_sw_work();
				break;
			case  PAGE_WAITING:
				main_xs_waiting();
				break;
			case  PAGE_BASIC_SETTINGS:
				main_xs_basic_settings();
				break;
			case  PAGE_ADVANCED_SETTINGS:
				main_xs_advanced_settings();
				break;
			case  PAGE_GUIDE:
				main_xs_guide();
				break;
			case  PAGE_PROBE_MODE:
				main_xs_probe_mode();
				break;
			case  PAGE_SETTING_POWER:
				main_xs_setting_power();
				break;
			default:
		     break; 
		} 
	}
}
				
			
			  
