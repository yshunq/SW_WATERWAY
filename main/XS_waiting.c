#include "config.h"

const u8  code MAIN_KEY_WAITING = 1;
const u16 code MAIN_WAITING[]=
{
	0,1279,0,799,
};

void main_xs_waiting(void)
{
	static u8 flag = 0;
	u8 key,i;
	u32 stop_beng_count;
	float temp;
	DIS_PICNUM(Pic_LOGO);
	
	if(flag == 0){
		u16 x,y,buff,j;
		x = 10;
		y = 785;
		i = 0;
		j = 0;
		DIS_FONT_C(0x00,0x00,8,0x01,x,y,"LOADING ");
		temp = get_adc_val(ADC0);//充电中。。。
		buff = (u16)temp;
		//DIS_FONT_ONE_POINT_VALUE(Pic_LOGO,1,0x00,0x00,0x01,3,DIS_ALL,(u16)(10*temp),0,10,10);
		while(temp < 2.5){//大约40V时  跳出
			delay_ms(250);
			temp = get_adc_val(ADC0);
			if(j == 80)DIS_FONT_ONE_POINT_VALUE(Pic_LOGO,1,0x00,0x00,0x01,3,DIS_ALL,(u16)(10*temp),buff,10,10);
			else if(j > 80 && j < 240)DIS_FONT_ONE_POINT_VALUE(Pic_LOGO,1,0x00,0x00,0x01,3,DIS_PART,(u16)(10*temp),buff,10,10);
			else if(j == 240){
				cut_sw_work_internal_power_varning();
				BENG_OFF;
				while(1){
					XIANG1();
					delay_ms(500);
				}
			}
			buff = (u16)temp;
			i++;if(j < 240)j++;//20秒都没充满就显示数值
			if(i == 1)DIS_FONT_C(0x00,0x00,6,0x01,x + 8*8,y,".      ");
			else if(i == 2)DIS_FONT_C(0x00,0x00,6,0x01,x + 8*8,y," .    ");
			else if(i == 3)DIS_FONT_C(0x00,0x00,6,0x01,x + 8*8,y,"  .   ");
			else if(i == 4)DIS_FONT_C(0x00,0x00,6,0x01,x + 8*8,y,"   .  ");
			else if(i == 5)DIS_FONT_C(0x00,0x00,6,0x01,x + 8*8,y,"    . ");
			else if(i == 6)DIS_FONT_C(0x00,0x00,6,0x01,x + 8*8,y,"     .");
			else if(i == 7){
				DIS_DEL_DIS(Pic_LOGO,x + 8*8,y,x + 8*14,y + 16,x + 8*8,y);
				i = 0;
			}
		}
		DIS_PICNUM(Pic_LOGO);
		XIANG1();
		flag = 1;
	}
    
	stop_beng_count = 0;
	do{
		delay_ms(1);
		if(Uart_LCD.KEY_YES!=0x00){
			ADS7843_KEY(); 
			key=KEY_FANHUI(MAIN_KEY_WAITING,MAIN_WAITING); 
	    	switch(key){
				case 1:
	   	      		XIANG1();
					INTERFACE = PAGE_SW_WORK;
					goto over_main_xs_waiting;
					//break;
	    	}
			Uart_LCD.KEY_YES = 0;
		}
		if(stop_beng_count < 60000)stop_beng_count++;else{BENG_OFF;}
	}while(1);
	over_main_xs_waiting:
	LAST_INTERFACE = PAGE_ADVANCED_SETTINGS;
	BENG_ON;
}
