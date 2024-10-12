#include "config.h"
#include "all_main_ram.h"

//PnM1.x    PnM0.x    Pn.x口工作模式
//  0         0       准双向口
//  0         1       推挽输出
//  1         0       高阻输入
//  1         1       开漏输出

void main(void)
{
	P7 = 0XFF;
	P0M0 = 0x04;
	P0M1 = 0x00;
	P1M0 = 0x08;
	P1M1 = 0x05;
	P2M0 = 0xE1;
	P2M1 = 0x04;
	P3M0 = 0x80;
	P3M1 = 0x40;
	P4M0 = 0x00;
	P4M1 = 0x10;
	P5M0 = 0x10;
	P5M1 = 0x00;
	
	//-----设置外部晶振-----//
	//P_SW2 |= 0x80;
	//XOSCCR = 0xC0;
	//while (!(XOSCCR & 1));
	//CLKDIV = 0x00;
	//CKSEL = 0x01;
	//P_SW2 &= ~0x80;

	P_SW2 = 0x00;
	Timer1_Init();	//1ms
	Uart3Init();
	ADC_Init();
	INTCLKO = EX2;	//使能INT2中断
	EA = 1;			//总中断

	SW.BODY_PARTS = 0;
	SW.TOTAL_TIME = 0;
	SW.CLOCK_COUNT = 0;
	SW.RECORD_FLAG = 1;
	SW.TIME_WORK_FLAG = 1;

	COOL_FS_OFF;
	MAIN_COIL_OFF;
	DEPUTY_COIL_OFF;
	DD_OFF;
	FAST_CHARGING_OFF;
	JDQ_SET_POWER_OFF;

	XIAN_FLAG = 0;
	
	read_logo_flag();
	read_all_set_body_value();
	read_all_set_ed_value();

	read_ll_warning_flag();
	read_ll_constant();
	read_ll_warning_value();

	read_handle_warning_flag();
	read_handle_warning_value();

	read_handle_insert_warning_flag();

	read_eeprom_total_time();
	
	delay_ms(3000);

	BENG_ON;

  	while(1){
		INTERFACE = PAGE_WAITING;
		jump_interface();
	}
}

void INT2_Isr() interrupt 10
{
	LL.COUNT++;
}








