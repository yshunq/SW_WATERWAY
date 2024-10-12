//#include "pwm.h"
//
////周期计算方法， 1/晶体频率*计数周期 = 1/33177600*0xff = 
//
//void hf_pwm_init(void)
//{
//  	PWMSET |= 0x08;		//使能PWM3模块
//	P_SW2 = 0x80;	
//  	PWM3CKS = 0x00;		//PWM3时钟为系统时钟
//	PWM3CH = 0x10;		//设置PWM1周期为7FFFH个PWM时钟
//	PWM3CL = 0x00;		//15位
//	PWM32T1H = 0x00;	//数值在PWM32T1时为低电平
//	PWM32T1L = 0x10;
//  	PWM32T2H = 0x01;	//数值在PWM32T2时为高电平
//	PWM32T2L = 0x00;
//  	PWM32CR= 0x80;		//使能PWM32输出
//  	P_SW2 = 0x00;
//	PWMCFG23 = 0x00;
//	P32 = 1;
//}
//
//void open_hf_pwm(u16 temp)//1500时输出12V  最大是0x1000 即 4096   1700时输出16V    1950时输出20V		 2200时为25V     2450时为30V		2700时为35V
//{
//	if(temp > 0x1000)temp = 0x1000;
//	
//	P_SW2 = 0x80;
//	PWM32T2H = temp/256;
//	PWM32T2L = temp%256;
//	P_SW2 = 0x00;
//	PWMCFG23 = 0x10;		//使能PWM1模块
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
//  	PWMSET |= 0x01;		//使能PWM2模块
//	P_SW2 = 0x80;	
//  	PWM0CKS = 0x00;		//PWM2时钟为系统时钟
//	PWM0CH = 0x10;		//设置PWM2周期为7FFFH个PWM时钟
//	PWM0CL = 0x00;		//15位
//	PWM00T1H = 0x00;	//数值在PWM32T1时为低电平
//	PWM00T1L = 0x10;
//  	PWM00T2H = 0x00;	//数值在PWM32T2时为高电平
//	PWM00T2L = 0x01;
//  	PWM00CR= 0x80;		//使能PWM32输出
//  	P_SW2 = 0x00;
//	PWMCFG01 = 0x00;
//	P00 = 0;
//}
//
//void open_rf_pwm(u16 temp)//600时4V  1200时11V
//{
//	if(temp > 0x1000)temp = 0x1000;
//	P_SW2 = 0x80;
//	PWM00T1H = temp/256;
//	PWM00T1L = temp%256;
//	P_SW2 = 0x00;
//	PWMCFG01 = 0x01;		//使能PWM1模块
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
