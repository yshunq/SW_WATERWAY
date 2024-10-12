#include "timer.h"

xdata unsigned long SYSTEM_CC;

u8 count_time_1ms(u8 clear)//��ʱ  ������
{
	static u32 buff = 0;
	if(clear == 0)buff = SYSTEM_CC;
	
	if((SYSTEM_CC - buff) >= 1){
		return 0;
	}
	return 1;
}

u8 count_time_100ms(u8 clear)//��ʱ  ������
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
  	AUXR &= 0x7F;														//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;														//���ö�ʱ��ģʽ
	TH1=(65536-(FOSC/12/1000))/256;
  	TL1=(65536-(FOSC/12/1000))%256;
	TF1 = 0;																//���TF0��־
	TR1 = 1;                                //������ʱ��
	ET1 = 1;                                //ʹ�ܶ�ʱ���ж�
}

void TM1_Isr() interrupt 3
{
	SYSTEM_CC++;

	if(SOUND_COUNT > 0){//������
		SOUND_COUNT--;
		if(SOUND_COUNT == 0)DD_OFF;
	}

	if(LL.TIME_COUNT >= 1000){//��������
    	LL.TIME_COUNT = 0;
		LL.CYCLE = LL.COUNT;
		LL.COUNT = 0;
	}else{
		LL.TIME_COUNT++;
	}

	if(SW.TIME_WORK_FLAG == 0){//���������   ����Ȧ��5ms  ֹͣ17ms  ����Ȧ��
		SW.CLOCK_COUNT++;//ʱ���ʱ	
		
		SW.WORK_COUNT++;
		if(SW.WORK_COUNT == 1){//�򿪸���Ȧ
			DEPUTY_COIL_ON;
		}else if(SW.WORK_COUNT == 6){//�رո���Ȧ
			DEPUTY_COIL_OFF;
		}else if(SW.WORK_COUNT == 23){//������Ȧ
			MAIN_COIL_ON;	
		}else if(SW.WORK_COUNT == (SW.SET_TIME + 23)){//�ر�����Ȧ
			MAIN_COIL_OFF;
			if(SW.TOTAL_TIME < SW.PRELOAD_TIME)SW.TOTAL_TIME++;
			if(SW.EEPROM_TOTAL_TIME < 2000000)SW.EEPROM_TOTAL_TIME++;
		}else if(SW.WORK_COUNT >= SW.CYCLE_TIME){
			SW.WORK_COUNT = 0;
		}	
	}
}



