//#include "pwm.h"
//
////���ڼ��㷽���� 1/����Ƶ��*�������� = 1/33177600*0xff = 
//
//void hf_pwm_init(void)
//{
//  	PWMSET |= 0x08;		//ʹ��PWM3ģ��
//	P_SW2 = 0x80;	
//  	PWM3CKS = 0x00;		//PWM3ʱ��Ϊϵͳʱ��
//	PWM3CH = 0x10;		//����PWM1����Ϊ7FFFH��PWMʱ��
//	PWM3CL = 0x00;		//15λ
//	PWM32T1H = 0x00;	//��ֵ��PWM32T1ʱΪ�͵�ƽ
//	PWM32T1L = 0x10;
//  	PWM32T2H = 0x01;	//��ֵ��PWM32T2ʱΪ�ߵ�ƽ
//	PWM32T2L = 0x00;
//  	PWM32CR= 0x80;		//ʹ��PWM32���
//  	P_SW2 = 0x00;
//	PWMCFG23 = 0x00;
//	P32 = 1;
//}
//
//void open_hf_pwm(u16 temp)//1500ʱ���12V  �����0x1000 �� 4096   1700ʱ���16V    1950ʱ���20V		 2200ʱΪ25V     2450ʱΪ30V		2700ʱΪ35V
//{
//	if(temp > 0x1000)temp = 0x1000;
//	
//	P_SW2 = 0x80;
//	PWM32T2H = temp/256;
//	PWM32T2L = temp%256;
//	P_SW2 = 0x00;
//	PWMCFG23 = 0x10;		//ʹ��PWM1ģ��
//}
//
//void close_hf_pwm(void)
//{
//	PWMCFG23 = 0x00;
//	P32 = 1;
//}
////--------------------------------------------------------------------------------------------//
//void rf_pwm_init(void)
//{
//  	PWMSET |= 0x01;		//ʹ��PWM2ģ��
//	P_SW2 = 0x80;	
//  	PWM0CKS = 0x00;		//PWM2ʱ��Ϊϵͳʱ��
//	PWM0CH = 0x10;		//����PWM2����Ϊ7FFFH��PWMʱ��
//	PWM0CL = 0x00;		//15λ
//	PWM00T1H = 0x00;	//��ֵ��PWM32T1ʱΪ�͵�ƽ
//	PWM00T1L = 0x10;
//  	PWM00T2H = 0x00;	//��ֵ��PWM32T2ʱΪ�ߵ�ƽ
//	PWM00T2L = 0x01;
//  	PWM00CR= 0x80;		//ʹ��PWM32���
//  	P_SW2 = 0x00;
//	PWMCFG01 = 0x00;
//	P00 = 0;
//}
//
//void open_rf_pwm(u16 temp)//600ʱ4V  1200ʱ11V
//{
//	if(temp > 0x1000)temp = 0x1000;
//	P_SW2 = 0x80;
//	PWM00T1H = temp/256;
//	PWM00T1L = temp%256;
//	P_SW2 = 0x00;
//	PWMCFG01 = 0x01;		//ʹ��PWM1ģ��
//}
//
//void close_rf_pwm(void)
//{
//	PWMCFG01 = 0x00;
//	P00 = 0;
//}
//
//
//
