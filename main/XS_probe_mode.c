#include "config.h"

const u8  code MAIN_KEY_PROBE_DODE = 8;
const u16 code MAIN_PROBE_DODE[]=
{
	695,782,255,341,	   //D8
	829,918,255,341,	   //D15
	964,1053,255,341,	   //C15

	695,782,400,489,	   //D20
	829,918,400,489,	   //D32


	935,1050,723,799,	   //设置
	1052,1167,723,799,	   //锁定
	1170,1279,723,799,	   //主界面
};
void cut_probe_mode(void);

void main_xs_probe_mode(void)
{
	bit lock_flag;
	u8 key;
	lock_flag = 1;
	DIS_PICNUM(Pic_SW_PROBE_START + SW.PROBE_MODE);
	do{
		if(Uart_LCD.KEY_YES!=0x00){
			ADS7843_KEY(); 
			key=KEY_FANHUI(MAIN_KEY_PROBE_DODE,MAIN_PROBE_DODE); 
	    	switch(key){
				case 1:		//D8
					if(lock_flag == 1){
						XIANG1();
						if(SW.PROBE_MODE != PROBE_D8){
							SW.PROBE_MODE = PROBE_D8;
							cut_probe_mode();
						}else{
							INTERFACE = PAGE_SW_WORK;
							if(SW.RECORD_FLAG == 0)write_sw_probe_mode(SW.BODY_PARTS);
							goto over_main_xs_probe_mode;
						}
					}
					Uart_LCD.KEY_YES = 0;
					break;
				case 2:		//D15
					if(lock_flag == 1){
						XIANG1();
						if(SW.PROBE_MODE != PROBE_D15){
							SW.PROBE_MODE = PROBE_D15;
							cut_probe_mode();
						}else{
							INTERFACE = PAGE_SW_WORK;
							if(SW.RECORD_FLAG == 0)write_sw_probe_mode(SW.BODY_PARTS);
							goto over_main_xs_probe_mode;
						}
					}
					Uart_LCD.KEY_YES = 0;
					break;
				case 3:		//C15
					if(lock_flag == 1){
						XIANG1();
						if(SW.PROBE_MODE != PROBE_C15){
							SW.PROBE_MODE = PROBE_C15;
							cut_probe_mode();
						}else{
							INTERFACE = PAGE_SW_WORK;
							if(SW.RECORD_FLAG == 0)write_sw_probe_mode(SW.BODY_PARTS);
							goto over_main_xs_probe_mode;
						}
					}
					Uart_LCD.KEY_YES = 0;
					break;
				case 4:		//D20
					if(lock_flag == 1){
						XIANG1();
						if(SW.PROBE_MODE != PROBE_D20){
							SW.PROBE_MODE = PROBE_D20;
							cut_probe_mode();
						}else{
							INTERFACE = PAGE_SW_WORK;
							if(SW.RECORD_FLAG == 0)write_sw_probe_mode(SW.BODY_PARTS);
							goto over_main_xs_probe_mode;
						}
					}
					Uart_LCD.KEY_YES = 0;
					break;
				case 5:		//D32
					if(lock_flag == 1){
						XIANG1();
						if(SW.PROBE_MODE != PROBE_D32){
							SW.PROBE_MODE = PROBE_D32;
							cut_probe_mode();
						}else{
							INTERFACE = PAGE_SW_WORK;
							if(SW.RECORD_FLAG == 0)write_sw_probe_mode(SW.BODY_PARTS);
							goto over_main_xs_probe_mode;
						}
					}
					Uart_LCD.KEY_YES = 0;
					break;
				case 6:	//设置
					if(lock_flag == 1){
						XIANG1();
						INTERFACE = PAGE_ADVANCED_SETTINGS;
						goto over_main_xs_probe_mode;
					}
					Uart_LCD.KEY_YES = 0;
					break;
				 case 7:	//锁屏幕
					XIANG1();
					if(lock_flag == 1){
						lock_flag = 0;
					}else{
					 	lock_flag = 1;
					}
					cut_sw_work_lock_flag(lock_flag);
					Uart_LCD.KEY_YES = 0;
					break;
				 case 8:	//返回LOGO
					if(lock_flag == 1){
						XIANG1();
						INTERFACE = PAGE_WAITING;
						goto over_main_xs_probe_mode;
					}
					Uart_LCD.KEY_YES = 0;
					break;
	    	}
			Uart_LCD.KEY_YES = 0;
		}
	}while(1);
	over_main_xs_probe_mode:
	LAST_INTERFACE = PAGE_PROBE_MODE;
}

void cut_probe_mode(void)
{
	DIS_DEL_DIS(Pic_SW_PROBE_START + SW.PROBE_MODE,0,0,1279,722,0,0);
	cut_sw_work_probe_mode();
}





