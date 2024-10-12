#include "config.h"

const u8  MAIN_KEY_SW_WORK = 23;
const u16 MAIN_SW_WORK[]=
{	 	 
	30,150,100,210,			//energy -  
	380,465,100,210,		//energy +
	30,150,230,325,			//frequency -
	380,465,230,325,		//frequency +
	30,150,240,430,			//preload	 -
	380,465,240,430,		//preload	 +

	30,150,480,560,			 //清零

	75,430,620,695,			 //开始停止

	486,690,172,245,	   //shoulder
	543,711,275,338,	   //elbow
	610,735,382,440,	   //hip
	645,760,480,545,	   //ed
	565,790,575,641,	   //foot/ankle

	940,1194,100,165,	   //lumbar region
	970,1180,211,260,	   //hand/wrist
	995,1255,316,373,	   //fat accumulate
	1013,1275,418,485,	   //pubic symphysis
	1042,1185,523,586,	   //knee

	935,1050,723,799,	   //设置
	1052,1167,723,799,	   //锁定
	1170,1279,723,799,	   //主界面

	872,1279,0,67,		   //GUIDEINE

	469,620,723,799	       //model
};

void main_xs_sw_work(void)
{
	static u8 last_down;
	bit start_stop_flag,lock_flag,insertion_flag;
	u8 key,pic,beng_warning_count,jtkey,temp;
	u16 touch_count,total,handle_temp;
	u32 eeprom_times;

	start_stop_flag = 1;
	lock_flag = 1;
	beng_warning_count = 100;//进入后，10秒后才流量报警
	SW.TIME_WORK_FLAG = 1;
	SW.TOTAL_TIME = 0;
	eeprom_times = SW.EEPROM_TOTAL_TIME;

	read_sw_power(SW.BODY_PARTS);
	read_sw_frequency(SW.BODY_PARTS);
	read_sw_preload_time(SW.BODY_PARTS);
	if(LAST_INTERFACE != PAGE_PROBE_MODE)read_sw_probe_mode(SW.BODY_PARTS);

	count_sw_work_max_power();
	pic = Pic_SW_WORK_START + SW.BODY_PARTS;
	DIS_PICNUM(pic);
	cut_sw_work_probe_mode();
	dis_sw_work_power(DIS_ALL);
	dis_sw_work_frequency(DIS_ALL);
	dis_sw_work_preload_time(DIS_ALL);
	dis_sw_work_total_time(DIS_ALL);
	dis_sw_work_time(DIS_ALL);

	cut_sw_work_start_stop_flag(start_stop_flag);
	cut_sw_work_lock_flag(lock_flag);

	if(SW.RECORD_FLAG == 0)DIS_FONT_C(0xf8,0x00,9,0x01,10,783,"RECORD...");

	count_ll_value();
	temp = read_start_jtkey();
	handle_temp = get_sw_work_handle_temp();

	insertion_flag = read_start_insertion();
	
	if(XIAN_FLAG){
		DIS_FONT_C(0xf8,0x00,5,0x01,10,10,"FLOW:");
		dis_sw_work_ll_value(DIS_ALL);

		DIS_FONT_C(0xf8,0x00,8,0x01,10,10+16,"WARNING:");
		if(LL.WARNING_FLAG == 0)DIS_FONT_C(0xf8,0x00,2,0x01,8*8+10,10+16,"ON");
		else{DIS_FONT_C(0xf8,0x00,3,0x01,8*8+10,10+16,"OFF");}
		
		DIS_FONT_C(0xf8,0x00,6,0x01,10,10+32,"VALUE:");
		//DIS_FONT_WEI_NUMBER_CM(pic,1,0xf8,0x00,0x01,LL.WARNING_VALUE,4,8*6+10,10+32);
		DIS_FONT_ONE_POINT_VALUE(pic,1,0xf8,0x00,0x01,3,DIS_ALL,LL.WARNING_VALUE,0,8*6+10,10+32);

		DIS_FONT_C(0xf8,0x00,9,0x01,10,10+48,"CONSTANT:");
		DIS_FONT_WEI_NUMBER_CM(pic,1,0xf8,0x00,0x01,LL.CONSTANT,4,8*9+10,10+48);
		//--------------------------------------------------------------------------------//
		DIS_FONT_C(0xf8,0x00,5,0x01,150,10,"TEMP:");
		dis_sw_work_handle_temp(DIS_ALL,handle_temp);

		DIS_FONT_C(0xf8,0x00,8,0x01,150,10+16,"WARNING:");
		if(HANDLE_TMEP.WARNING_FLAG == 0)DIS_FONT_C(0xf8,0x00,2,0x01,8*8+150,10+16,"ON");
		else{DIS_FONT_C(0xf8,0x00,3,0x01,8*8+150,10+16,"OFF");}

		DIS_FONT_C(0xf8,0x00,6,0x01,150,10+32,"VALUE:");
		//DIS_FONT_WEI_NUMBER_CM(pic,1,0xf8,0x00,0x01,HANDLE.WARNING_VALUE,4,8*6+150,10+32);
		DIS_FONT_WEI_TEMP(pic,0xf8,0x00,0x01,DIS_ALL,HANDLE_TMEP.WARNING_VALUE,0,8*6+150,10+32);
		//--------------------------------------------------------------------------------//
		DIS_FONT_C(0xf8,0x00,7,0x01,300,10,"INSERT:");
		if(HANDLE_TMEP.WARNING_FLAG == 0)DIS_FONT_C(0xf8,0x00,2,0x01,7*8+300,10,"ON");
		else{DIS_FONT_C(0xf8,0x00,3,0x01,7*8+300,10,"OFF");}
			
	}
	COOL_FS_ON;
	touch_count = 0;
	do{
		if(Uart_LCD.KEY_YES!=0x00 && touch_count == 0){
			ADS7843_KEY(); //扫描按键
			key=KEY_FANHUI(MAIN_KEY_SW_WORK,MAIN_SW_WORK); 
			switch(key){
				case 1:	//能量减减
					if(SW.POWER > 1 && lock_flag == 1 && SW.TIME_WORK_FLAG == 1){
						DIS_DEL_DIS(Pic_SW_WORK_DOWN,76,118,138,181,76,118);
						XIANG1();
						SW.POWER--;
						dis_sw_work_power(DIS_PART);
						last_down = 1;
						touch_count = 120;
					}else{Uart_LCD.KEY_YES = 0;}
					break;
				case 2:	//能量加加
					if(SW.POWER < SW.MAX_POWER && lock_flag == 1 && SW.TIME_WORK_FLAG == 1){
						DIS_DEL_DIS(Pic_SW_WORK_DOWN,386,118,449,181,386,118);
						XIANG1();
						SW.POWER++;
						dis_sw_work_power(DIS_PART);
						last_down = 2;
						touch_count = 120;
					}else{Uart_LCD.KEY_YES = 0;}
					break;
				case 3:	//频率减减
					if(SW.FREQUENCY > 1 && lock_flag == 1 && SW.TIME_WORK_FLAG == 1){
						DIS_DEL_DIS(Pic_SW_WORK_DOWN,76,237,138,299,76,237);
						XIANG1();
						SW.FREQUENCY--;
						dis_sw_work_frequency(DIS_PART);
						last_down = 3;
						touch_count = 120;
					}else{Uart_LCD.KEY_YES = 0;}
					break;
				case 4:	//频率加加
					if(SW.FREQUENCY < 18 && lock_flag == 1 && SW.TIME_WORK_FLAG == 1){
						DIS_DEL_DIS(Pic_SW_WORK_DOWN,386,237,449,299,386,237);
						XIANG1();
						SW.FREQUENCY++;
						dis_sw_work_frequency(DIS_PART);
						last_down = 4;
						touch_count = 120;
					}else{Uart_LCD.KEY_YES = 0;}
					break;
				case 5:	//预设值减减
					if(SW.PRELOAD_TIME > 100 && lock_flag == 1){
						DIS_DEL_DIS(Pic_SW_WORK_DOWN,76,353,138,416,76,353);
						XIANG1();
						SW.PRELOAD_TIME -= 100;
						dis_sw_work_preload_time(DIS_PART);
						last_down = 5;
						touch_count = 120;
					}else{Uart_LCD.KEY_YES = 0;}
					break;
				case 6:	//预设值加加
					if(SW.PRELOAD_TIME < 10000 && lock_flag == 1){
						DIS_DEL_DIS(Pic_SW_WORK_DOWN,386,353,449,416,386,353);
						XIANG1();
						SW.PRELOAD_TIME += 100;
						dis_sw_work_preload_time(DIS_PART);
						last_down = 6;
						touch_count = 120;
					}else{Uart_LCD.KEY_YES = 0;}
					break;
				case 7:	//清零
					if(SW.TOTAL_TIME > 0 && lock_flag == 1){
						DIS_DEL_DIS(Pic_SW_WORK_DOWN,70,470,140,550,70,470);
						XIANG1();
						SW.TOTAL_TIME = 0;
						dis_sw_work_total_time(DIS_PART);
						last_down = 7;
						touch_count = 120;
					}else{Uart_LCD.KEY_YES = 0;}
					break;
				case 8:	//启动停止
					if(lock_flag == 1 && SW.TIME_WORK_FLAG == 1){
						XIANG1();
						if(start_stop_flag == 0){
							start_stop_flag = 1;
							JDQ_SET_POWER_OFF;
						}else{
							start_stop_flag = 0;
							JDQ_SET_POWER_ON;
						}
						cut_sw_work_start_stop_flag(start_stop_flag);
					}Uart_LCD.KEY_YES = 0;
					break;
				case 9:		//SHOULDER
					if(SW.BODY_PARTS != PARTS_SHOULDER && lock_flag == 1 && SW.TIME_WORK_FLAG == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_SHOULDER;
					   	read_all_parameter(SW.BODY_PARTS);
						count_sw_work_max_power();
						SW.TOTAL_TIME = 0;
					   	dis_sw_work_body_parts();
					}
					Uart_LCD.KEY_YES = 0;
					break;
				case 10:	//ELBOW
					if(SW.BODY_PARTS != PARTS_ELBOW && lock_flag == 1 && SW.TIME_WORK_FLAG == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_ELBOW;
					   	read_all_parameter(SW.BODY_PARTS);
						count_sw_work_max_power();
						SW.TOTAL_TIME = 0;
					   	dis_sw_work_body_parts();
					}
					Uart_LCD.KEY_YES = 0;
					break;
				 case 11:	//HIP
					if(SW.BODY_PARTS != PARTS_HIP && lock_flag == 1 && SW.TIME_WORK_FLAG == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_HIP;
					   	read_all_parameter(SW.BODY_PARTS);
						count_sw_work_max_power();
						SW.TOTAL_TIME = 0;
					   	dis_sw_work_body_parts();
					}
					Uart_LCD.KEY_YES = 0;
					break;
				 case 12:	//ED
					if(SW.BODY_PARTS != PARTS_ED && lock_flag == 1 && SW.TIME_WORK_FLAG == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_ED;
					   	read_all_parameter(SW.BODY_PARTS);
						count_sw_work_max_power();
						SW.TOTAL_TIME = 0;
					   	dis_sw_work_body_parts();
					}
					Uart_LCD.KEY_YES = 0;
					break;
				 case 13:	//FOOT
					if(SW.BODY_PARTS != PARTS_FOOT && lock_flag == 1 && SW.TIME_WORK_FLAG == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_FOOT;
					   	read_all_parameter(SW.BODY_PARTS);
						count_sw_work_max_power();
						SW.TOTAL_TIME = 0;
					   	dis_sw_work_body_parts();
					}
					Uart_LCD.KEY_YES = 0;
					break;
				 case 14:	//LUMBAR
					if(SW.BODY_PARTS != PARTS_LUMBAR && lock_flag == 1 && SW.TIME_WORK_FLAG == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_LUMBAR;
					   	read_all_parameter(SW.BODY_PARTS);
						count_sw_work_max_power();
						SW.TOTAL_TIME = 0;
					   	dis_sw_work_body_parts();
					}
					Uart_LCD.KEY_YES = 0;
					break;
				 case 15:	//HAND
					if(SW.BODY_PARTS != PARTS_HAND && lock_flag == 1 && SW.TIME_WORK_FLAG == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_HAND;
					   	read_all_parameter(SW.BODY_PARTS);
						count_sw_work_max_power();
						SW.TOTAL_TIME = 0;
					   	dis_sw_work_body_parts();
					}
					Uart_LCD.KEY_YES = 0;
					break;
				 case 16:	//FAT
					if(SW.BODY_PARTS != PARTS_FAT && lock_flag == 1 && SW.TIME_WORK_FLAG == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_FAT;
					   	read_all_parameter(SW.BODY_PARTS);
						count_sw_work_max_power();
						SW.TOTAL_TIME = 0;
					   	dis_sw_work_body_parts();
					}
					Uart_LCD.KEY_YES = 0;
					break;
				 case 17:	//PUBIC
					if(SW.BODY_PARTS != PARTS_PUBIC && lock_flag == 1 && SW.TIME_WORK_FLAG == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_PUBIC;
					   	read_all_parameter(SW.BODY_PARTS);
						count_sw_work_max_power();
						SW.TOTAL_TIME = 0;
					   	dis_sw_work_body_parts();
					}
					Uart_LCD.KEY_YES = 0;
					break;
				 case 18:	//KNEE
					if(SW.BODY_PARTS != PARTS_KNEE && lock_flag == 1 && SW.TIME_WORK_FLAG == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_KNEE;
					   	read_all_parameter(SW.BODY_PARTS);
						count_sw_work_max_power();
						SW.TOTAL_TIME = 0;
					   	dis_sw_work_body_parts();
					}
					Uart_LCD.KEY_YES = 0;
					break;
				 case 19:	//设置
					if(start_stop_flag == 1 && lock_flag == 1 && SW.TIME_WORK_FLAG == 1){
						XIANG1();
						INTERFACE = PAGE_ADVANCED_SETTINGS;
						goto over_main_xs_sw_work;
					}
					Uart_LCD.KEY_YES = 0;
					break;
				 case 20:	//锁屏幕
					XIANG1();
					if(lock_flag == 1){
						lock_flag = 0;
					}else{
					 	lock_flag = 1;
					}
					cut_sw_work_lock_flag(lock_flag);
					Uart_LCD.KEY_YES = 0;
					break;
				 case 21:	//返回LOGO
					if(start_stop_flag == 1 && lock_flag == 1){
						XIANG1();
						INTERFACE = PAGE_WAITING;
						goto over_main_xs_sw_work;
					}
					Uart_LCD.KEY_YES = 0;
					break;
				 case 22:	//指引界面
					if(start_stop_flag == 1 && lock_flag == 1 && SW.TIME_WORK_FLAG == 1){
						XIANG1();
						INTERFACE = PAGE_GUIDE;
						goto over_main_xs_sw_work;
					}
					Uart_LCD.KEY_YES = 0;
					break;
				 case 23:	//探头界面
					if(start_stop_flag == 1 && lock_flag == 1 && SW.TIME_WORK_FLAG == 1){
						XIANG1();
						INTERFACE = PAGE_PROBE_MODE;
						goto over_main_xs_sw_work;
					}
					Uart_LCD.KEY_YES = 0;
					break;
			}
		}else if(Uart_LCD.KEY_YES == 0 && touch_count == 0){
			switch(last_down){
				case 1:
					if(SW.RECORD_FLAG == 0)write_sw_power(SW.BODY_PARTS);
					DIS_DEL_DIS(pic,76,118,138,181,76,118);
					break;
				case 2:
					if(SW.RECORD_FLAG == 0)write_sw_power(SW.BODY_PARTS);
					DIS_DEL_DIS(pic,386,118,449,181,386,118);
					break;
				case 3:
					if(SW.RECORD_FLAG == 0)write_sw_frequency(SW.BODY_PARTS);
					DIS_DEL_DIS(pic,76,237,138,299,76,237);
					break;
				case 4:
					if(SW.RECORD_FLAG == 0)write_sw_frequency(SW.BODY_PARTS);
					DIS_DEL_DIS(pic,386,237,449,299,386,237);
					break;
				case 5:
					if(SW.RECORD_FLAG == 0)write_sw_preload_time(SW.BODY_PARTS);
					DIS_DEL_DIS(pic,76,353,138,416,76,353);
					break;
				case 6:
					if(SW.RECORD_FLAG == 0)write_sw_preload_time(SW.BODY_PARTS);
					DIS_DEL_DIS(pic,386,353,449,416,386,353);
					break;
				case 7:DIS_DEL_DIS(pic,70,470,140,550,70,470);break;
			}
			last_down = 0;
		}

		if(count_time_1ms(PASS) == 0){count_time_1ms(CLEAR);if(touch_count > 0)touch_count--;}//1ms 不精准

		
		if(count_time_100ms(PASS) == 0){//100ms
			count_time_100ms(CLEAR);
			if(beng_warning_count > 0)beng_warning_count--;
			count_ll_value();
			if(XIAN_FLAG)dis_sw_work_ll_value(DIS_PART);

			insertion_flag = read_start_insertion();//手柄插进入检测
			if(insertion_flag == 1 && HANDLE_INSERT.WARNING_FLAG == 0){
				XIANG1();
				SW.TIME_WORK_FLAG = 1;
				DEPUTY_COIL_OFF;
				MAIN_COIL_OFF;
				JDQ_SET_POWER_OFF;
				start_stop_flag = 1;
				cut_sw_work_start_stop_flag(start_stop_flag);
				cut_sw_work_handle_insert_warning();
				if(eeprom_times != SW.EEPROM_TOTAL_TIME){
					eeprom_times = SW.EEPROM_TOTAL_TIME;
					write_eeprom_total_time();
				}
				while(Uart_LCD.KEY_YES == 0);
				XIANG1();
				INTERFACE = PAGE_WAITING;
				goto over_main_xs_sw_work; 	
			}

			if(LL.VALUE <= LL.WARNING_VALUE && LL.WARNING_FLAG == 0 && beng_warning_count == 0){//检测水流量
				XIANG1();
				SW.TIME_WORK_FLAG = 1;
				DEPUTY_COIL_OFF;
				MAIN_COIL_OFF;
				JDQ_SET_POWER_OFF;
				start_stop_flag = 1;
				cut_sw_work_start_stop_flag(start_stop_flag);
				cut_sw_work_flow_warning();
				if(eeprom_times != SW.EEPROM_TOTAL_TIME){
					eeprom_times = SW.EEPROM_TOTAL_TIME;
					write_eeprom_total_time();
				}
				dis_sw_work_ll_value(DIS_ALL);
				while(Uart_LCD.KEY_YES == 0){
					temp++;
					if(temp > 200){
						count_ll_value();
						dis_sw_work_ll_value(DIS_PART);
						temp = 0;
					}
					delay_ms(1);
				}
				XIANG1();
				INTERFACE = PAGE_WAITING;
				goto over_main_xs_sw_work; 
			}

			handle_temp = get_sw_work_handle_temp();
			if(XIAN_FLAG)dis_sw_work_handle_temp(DIS_PART,handle_temp);
			if(handle_temp >= HANDLE_TMEP.WARNING_VALUE && HANDLE_TMEP.WARNING_FLAG == 0){//检测手柄温度
				XIANG1();
				SW.TIME_WORK_FLAG = 1;
				DEPUTY_COIL_OFF;
				MAIN_COIL_OFF;
				JDQ_SET_POWER_OFF;
				start_stop_flag = 1;
				cut_sw_work_start_stop_flag(start_stop_flag);
				if(handle_temp == 1249){//开路
					cut_sw_work_handle_temp_open();
				}else if(handle_temp == 1248){//短路
					cut_sw_work_handle_temp_short();
				}else{//温度过高
					cut_sw_work_handle_temp_high();
				}
				if(eeprom_times != SW.EEPROM_TOTAL_TIME){
					eeprom_times = SW.EEPROM_TOTAL_TIME;
					write_eeprom_total_time();
				}
				dis_sw_work_handle_temp(DIS_ALL,handle_temp);
				while(Uart_LCD.KEY_YES == 0){
					temp++;
					if(temp > 200){
						handle_temp = get_sw_work_handle_temp();
						dis_sw_work_handle_temp(DIS_PART,handle_temp);
						temp = 0;
					}
					delay_ms(1);
				}
				XIANG1();
				INTERFACE = PAGE_WAITING;
				goto over_main_xs_sw_work; 
			}
		}

		temp = read_start_jtkey(); //脚踏检测
		if(jtkey != temp){
			jtkey = temp;
			if(jtkey == 0){
				if(start_stop_flag == 0){
					total = SW.TOTAL_TIME;
					SW.WORK_COUNT = 0;	
					SW.CYCLE_TIME = 1000/SW.FREQUENCY;
					if(SW.BODY_PARTS == PARTS_ED)SW.SET_TIME = SW.POWER_SET_ED_VALUE[SW.POWER];
					else{SW.SET_TIME = SW.POWER_SET_BODY_VALUE[SW.POWER];}
					SW.TIME_WORK_FLAG = 0;
					XIANG1();
				}	
			}else{
				SW.TIME_WORK_FLAG = 1;
				DEPUTY_COIL_OFF;
				MAIN_COIL_OFF;
				if(eeprom_times != SW.EEPROM_TOTAL_TIME){
					eeprom_times = SW.EEPROM_TOTAL_TIME;
					write_eeprom_total_time();
				}
			}
		}

		if(SW.TIME_WORK_FLAG == 0){	//工作后进入
			dis_sw_work_time(DIS_PART);
			if(total != SW.TOTAL_TIME){
				total = SW.TOTAL_TIME;
				dis_sw_work_total_time(DIS_PART);
				if(SW.TOTAL_TIME >= SW.PRELOAD_TIME){
					XIANG1();
					SW.TIME_WORK_FLAG = 1;
					DEPUTY_COIL_OFF;
					MAIN_COIL_OFF;
					JDQ_SET_POWER_OFF;
					start_stop_flag = 1;
					cut_sw_work_start_stop_flag(start_stop_flag);
					cut_sw_work_preset_value_varning();
					if(eeprom_times != SW.EEPROM_TOTAL_TIME){
						eeprom_times = SW.EEPROM_TOTAL_TIME;
						write_eeprom_total_time();
					}
					while(Uart_LCD.KEY_YES == 0);
					XIANG1();
					//INTERFACE = PAGE_WAITING;
					goto over_main_xs_sw_work; 	
				}
			}
		}





	}while(1);
	over_main_xs_sw_work:
	LAST_INTERFACE = PAGE_SW_WORK;
	COOL_FS_OFF;
	_nop_();
}













 
 