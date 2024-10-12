#include "adc.h"

code float TEMP_DATA[]={
	132284,98185,73626,55744,42592,32814,25497,19958,15742,12504, //-25 -20 -15 -10 -5 0 5 10 15 20
	 10000, 8049, 6520, 5313, 4354, 3588, 2973, 2476, 2072, 1742, //25 30 35 40 45 50 55 60 65 70
	  1472, 1249, 1065,  911,  783,  675,  585,  508,  443,  388, //75 80 85 90 95 100 105 110 115 120
};

void ADC_Init(void)//P1.0  P1.1
{
  //P1M0 = 0x00;                              //设置P1.0为ADC口 高阻输入
  //P1M1 = 0x01;
  ADCCFG = 0x2f;                              //设置ADC时钟为系统时钟/2/16/16 转换结果右对齐
  ADC_CONTR = 0x80;                           //使能ADC模块 打开ADC_POWER
}

float get_adc_temp(u8 adc)
{
	u16 i;
	float temp,buff,adc_val,lg1,rval;
	ADC_CONTR &=~0x80;
	_nop_();_nop_();
	ADC_CONTR = 0x80;                       //使能ADC模块 打开ADC_POWER
	_nop_();_nop_();
	ADC_CONTR |= (0x40 + adc);              //启动AD转换  ADC_START = 1	 ADC2
	_nop_();_nop_();
	while (!(ADC_CONTR & 0x20));            //查询ADC完成标志
	ADC_CONTR &= ~0x20;                     //清完成标志

	buff = (ADC_RES<<8)|ADC_RESL;						//取转换结果
	//adc_val = 5000*buff/1024;							//计算出电压值
	//adc_val = 625*buff/128;							//计算出电压值
	adc_val = 5*buff/1023;
//	DIS_FONT_WEI_NUMBER_CM(1,1,0xf8,0x00,0x01,adc_val*1000,5,500,150);

	if(adc_val>4.7){//拔掉NTC
	    temp = 124.9;
		goto over_water_temp;
	}else if(adc_val < 0.3){//NTC短路
		temp = 124.8;
		goto over_water_temp;
	}
	
	lg1 = (5 - adc_val)/10000;					//电流流过10K电流
	rval = adc_val/lg1;						//电压除以电流等于电阻

//	DIS_FONT_WEI_NUMBER_CM(1,1,0xf8,0x00,0x01,lg1*1000,5,500,50);
//	DIS_FONT_WEI_NUMBER_CM(1,1,0xf8,0x00,0x01,rval,5,500,100);

	if(rval >= 132284){ //小于-25度时显示-25℃
		temp = 0;
		goto over_water_temp;
	}
	
	if(rval <= 911){ 	//大于90度时显示90℃
		temp = 115;
		goto over_water_temp;
	}
	
	for(i=0;i<24;i++){ //对比组织表
		buff=(float)TEMP_DATA[i];
		if(rval>=buff)
		break;
	}
	//(TEMP_DATA[i+1] - TEMP_DATA[i])/((5*(i+1)-(5*i)) = (rval - TEMP_DATA[i])/ ?  
	temp = (rval - TEMP_DATA[i])*5/(TEMP_DATA[i+1] - TEMP_DATA[i]) + 5*i;
	over_water_temp:
	_nop_();
	return temp;
}

float get_adc_val(u8 adc)//获取电压值
{
	float buff,adc_val;
	ADC_CONTR &=~0x80;
	_nop_();_nop_();
	ADC_CONTR = 0x80;                       //使能ADC模块 打开ADC_POWER
	_nop_();_nop_();
	ADC_CONTR |= (0x40 + adc);              //启动AD转换  ADC_START = 1	 ADC2
	_nop_();_nop_();
	while (!(ADC_CONTR & 0x20));            //查询ADC完成标志
	ADC_CONTR &= ~0x20;                     //清完成标志

	buff = (ADC_RES<<8)|ADC_RESL;						//取转换结果
	//adc_val = 5000*buff/1024;							//计算出电压值
	//adc_val = 625*buff/128;							//计算出电压值
	adc_val = 5*buff/1023;

	return adc_val;
}






