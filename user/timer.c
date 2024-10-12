#include "timer.h"

xdata unsigned long SYSTEM_CC;

u8 count_time_1ms(u8 clear)//计时  不卡主
{
	static u32 buff = 0;
	if(clear == 0)buff = SYSTEM_CC;
	
	if((SYSTEM_CC - buff) >= 1){
		return 0;
	}
	return 1;
}

u8 count_time_100ms(u8 clear)//计时  不卡主
{
	static u32 buff = 0;
	if(clear == 0)buff = SYSTEM_CC;
	
	if((SYSTEM_CC - buff) >= 100){
		return 0;
	}
	return 1;
}




void delay_ms(unsigned long ms)
{
	static u32 temp;
	temp = SYSTEM_CC;
	while((SYSTEM_CC - temp) < ms);
}

void Timer1_Init(void)
{
  	AUXR &= 0x7F;														//定时器时钟12T模式
	TMOD &= 0xF0;														//设置定时器模式
	TH1=(65536-(FOSC/12/1000))/256;
  	TL1=(65536-(FOSC/12/1000))%256;
	TF1 = 0;																//清除TF0标志
	TR1 = 1;                                //启动定时器
	ET1 = 1;                                //使能定时器中断
}

void TM1_Isr() interrupt 3
{
	SYSTEM_CC++;

	if(SOUND_COUNT > 0){//蜂鸣器
		SOUND_COUNT--;
		if(SOUND_COUNT == 0)DD_OFF;
	}

	if(LL.TIME_COUNT >= 1000){//流量传感
    	LL.TIME_COUNT = 0;
		LL.CYCLE = LL.COUNT;
		LL.COUNT = 0;
	}else{
		LL.TIME_COUNT++;
	}

	if(SW.TIME_WORK_FLAG == 0){//冲击波工作   副线圈打开5ms  停止17ms  主线圈打开
		SW.CLOCK_COUNT++;//时间计时	
		
		SW.WORK_COUNT++;
		if(SW.WORK_COUNT == 1){//打开副线圈
			DEPUTY_COIL_ON;
		}else if(SW.WORK_COUNT == 6){//关闭副线圈
			DEPUTY_COIL_OFF;
		}else if(SW.WORK_COUNT == 23){//打开主线圈
			MAIN_COIL_ON;	
		}else if(SW.WORK_COUNT == (SW.SET_TIME + 23)){//关闭主线圈
			MAIN_COIL_OFF;
			if(SW.TOTAL_TIME < SW.PRELOAD_TIME)SW.TOTAL_TIME++;
			if(SW.EEPROM_TOTAL_TIME < 2000000)SW.EEPROM_TOTAL_TIME++;
		}else if(SW.WORK_COUNT >= SW.CYCLE_TIME){
			SW.WORK_COUNT = 0;
		}	
	}
}



