#include "config.h"

const u8  code MAIN_KEY_BASIC_SET = 11;
const u16 code MAIN_BASIC_SET[]=
{
	 30,140, 15, 80,	//1	返回
	330,525,230,295,	//2 

	255,330,340,410,   	//3	报警流量--
	525,595,340,405,	//4	报警流量++

	255,330,450,520,   	//5 流量常数--
	525,595,450,520,	//6 流量常数++

	330,525,560,633,	//7 手柄插入

	755,960,230,295,	//8 温度报警

	690,760,340,410,   	//9 温度--
	955,1025,340,405,  	//10 温度++

	755,960,450,520,	//11 清零

};

void dis_basic_setting_ll_warning_flag(void);
void dis_basic_setting_ll_warning_value(u8 dis);
void dis_basic_setting_ll_constant(u8 dis);
void dis_basic_setting_handle_insert_warning_flag(void);
void dis_basic_setting_handle_temp_warning_flag(void);
void dis_basic_setting_handle_temp_warning_value(u8 dis);
void dis_basic_setting_eeprom_total_time(u8 dis);

void main_xs_basic_settings(void)
{
	u8 key,last_down;
	DIS_PICNUM(Pic_BASIC_SETTINGS);
	dis_basic_setting_ll_warning_flag();
	dis_basic_setting_ll_warning_value(DIS_ALL);
	dis_basic_setting_ll_constant(DIS_ALL);
	dis_basic_setting_handle_insert_warning_flag();
	dis_basic_setting_handle_temp_warning_flag();
	dis_basic_setting_handle_temp_warning_value(DIS_ALL);
	dis_basic_setting_eeprom_total_time(DIS_ALL);

	last_down = 0;
	do{
		if(Uart_LCD.KEY_YES!=0x00){
			ADS7843_KEY(); 
			key=KEY_FANHUI(MAIN_KEY_BASIC_SET,MAIN_BASIC_SET); 
	    	switch(key){
				case 1:
	   	      		XIANG1();
					INTERFACE = PAGE_WAITING;
					goto over_main_xs_basic_settings;
					//break;
				case 2:
	   	      		XIANG1();
					if(LL.WARNING_FLAG == 0)LL.WARNING_FLAG = 1;else{LL.WARNING_FLAG = 0;}
				    dis_basic_setting_ll_warning_flag();
					delay_ms(120);
					last_down = 2;
					Uart_LCD.KEY_YES = 0;
					break;
				case 3:
	   	      		if(LL.WARNING_VALUE > 1){
						XIANG1();
						LL.WARNING_VALUE--;
						dis_basic_setting_ll_warning_value(DIS_PART);
						delay_ms(120);
						last_down = 3;
					}else{Uart_LCD.KEY_YES = 0;}
					break;
				case 4:
	   	      		if(LL.WARNING_VALUE < 100){
						XIANG1();
						LL.WARNING_VALUE++;
						dis_basic_setting_ll_warning_value(DIS_PART);
						delay_ms(120);
						last_down = 3;
					}else{Uart_LCD.KEY_YES = 0;}
					break;
				case 5:
	   	      		if(LL.CONSTANT > 1){
						XIANG1();
						LL.CONSTANT--;
						dis_basic_setting_ll_constant(DIS_PART);
						delay_ms(120);
						last_down = 5;
					}else{Uart_LCD.KEY_YES = 0;}
					break;
				case 6:
	   	      		if(LL.CONSTANT < 9900){
						XIANG1();
						LL.CONSTANT++;
						dis_basic_setting_ll_constant(DIS_PART);
						delay_ms(120);
						last_down = 5;
					}else{Uart_LCD.KEY_YES = 0;}
					break;
				case 7:
	   	      		XIANG1();
					if(HANDLE_INSERT.WARNING_FLAG == 0)HANDLE_INSERT.WARNING_FLAG = 1;else{HANDLE_INSERT.WARNING_FLAG = 0;}
				    dis_basic_setting_handle_insert_warning_flag();
					delay_ms(120);
					last_down = 7;
					Uart_LCD.KEY_YES = 0;
					break;
				case 8:
	   	      		XIANG1();
					if(HANDLE_TMEP.WARNING_FLAG == 0)HANDLE_TMEP.WARNING_FLAG = 1;else{HANDLE_TMEP.WARNING_FLAG = 0;}
				    dis_basic_setting_handle_temp_warning_flag();
					delay_ms(120);
					last_down = 8;
					Uart_LCD.KEY_YES = 0;
					break;
				case 9:
	   	      		if(HANDLE_TMEP.WARNING_VALUE > 1){
						XIANG1();
						HANDLE_TMEP.WARNING_VALUE--;
						dis_basic_setting_handle_temp_warning_value(DIS_PART);
						delay_ms(120);
						last_down = 9;
					}else{Uart_LCD.KEY_YES = 0;}
					break;
				case 10:
	   	      		if(HANDLE_TMEP.WARNING_VALUE < 999){
						XIANG1();
						HANDLE_TMEP.WARNING_VALUE++;
						dis_basic_setting_handle_temp_warning_value(DIS_PART);
						delay_ms(120);
						last_down = 9;
					}else{Uart_LCD.KEY_YES = 0;}
					break;
				case 11:
		   	      	if(SW.EEPROM_TOTAL_TIME > 0){
						XIANG1();
						SW.EEPROM_TOTAL_TIME = 0;
						dis_basic_setting_eeprom_total_time(DIS_PART);
						write_eeprom_total_time();
						delay_ms(120);
					}
					Uart_LCD.KEY_YES = 0;
					break;





	    	}
		}else{
			switch(last_down){
				case 2:write_ll_warning_flag();break;
				case 3:write_ll_warning_value();break;
				case 5:write_ll_constant();break;
				case 7:write_handle_insert_warning_flag();break;
				case 8:write_handle_warning_flag();break;
				case 9:write_handle_warning_value();break;

			}
			last_down = 0;
		}
	}while(1);
	over_main_xs_basic_settings:
	LAST_INTERFACE = PAGE_BASIC_SETTINGS;
}

void dis_basic_setting_ll_warning_flag(void)
{
	u16 x,y;
	x = 400;
	y = 248;
	DIS_DEL_DIS(Pic_BASIC_SETTINGS,x,y,16*3+x,32+y,x,y);
	if(LL.WARNING_FLAG == 0){
		DIS_FONT_C(0x00,0x00,2,0x03,x+8,y,"ON");	
	}else{
		DIS_FONT_C(0x00,0x00,3,0x03,x,y,"OFF");	
	}
}

void dis_basic_setting_ll_warning_value(u8 dis)
{
	static u16 temp;
	u16 x,y;
	x = 392;
	y = 358;
    DIS_FONT_ONE_POINT_VALUE(Pic_BASIC_SETTINGS,1,0x00,0x00,0x03,3,dis,LL.WARNING_VALUE,temp,x,y);
	temp = LL.WARNING_VALUE;
}

void dis_basic_setting_ll_constant(u8 dis)
{
	static u16 temp;
	u16 x,y;
	x = 386;
	y = 470;
    DIS_FONT_ONE_POINT_VALUE(Pic_BASIC_SETTINGS,1,0x00,0x00,0x03,4,dis,LL.CONSTANT,temp,x,y);
	temp = LL.CONSTANT;
}

void dis_basic_setting_handle_insert_warning_flag(void)
{
	u16 x,y;
	x = 400;
	y = 580;
	DIS_DEL_DIS(Pic_BASIC_SETTINGS,x,y,16*3+x,32+y,x,y);
	if(HANDLE_INSERT.WARNING_FLAG == 0){
		DIS_FONT_C(0x00,0x00,2,0x03,x+8,y,"ON");	
	}else{
		DIS_FONT_C(0x00,0x00,3,0x03,x,y,"OFF");	
	}
}

void dis_basic_setting_handle_temp_warning_flag(void)
{
	u16 x,y;
	x = 831;
	y = 248;
	DIS_DEL_DIS(Pic_BASIC_SETTINGS,x,y,16*3+x,32+y,x,y);
	if(HANDLE_TMEP.WARNING_FLAG == 0){
		DIS_FONT_C(0x00,0x00,2,0x03,x+8,y,"ON");	
	}else{
		DIS_FONT_C(0x00,0x00,3,0x03,x,y,"OFF");	
	}
}

void dis_basic_setting_handle_temp_warning_value(u8 dis)
{
	static u16 temp;
	u16 x,y;
	x = 815;
	y = 358;
    //DIS_FONT_ONE_POINT_VALUE(Pic_BASIC_SETTINGS,1,0x00,0x00,0x03,3,dis,HANDLE_TMEP.WARNING_VALUE,temp,x,y);
	DIS_FONT_WEI_TEMP(Pic_BASIC_SETTINGS,0x00,0x00,0x03,dis,HANDLE_TMEP.WARNING_VALUE,temp,x,y);
	temp = HANDLE_TMEP.WARNING_VALUE;
}

void dis_basic_setting_eeprom_total_time(u8 dis)
{
	static u16 temp;
	u16 x,y;
	x = 799;
	y = 470;
    DIS_FONT_WEI_VALUE(Pic_BASIC_SETTINGS,1,0x00,0x00,0x03,7,dis,SW.EEPROM_TOTAL_TIME,temp,x,y);
	temp = SW.EEPROM_TOTAL_TIME;
}





