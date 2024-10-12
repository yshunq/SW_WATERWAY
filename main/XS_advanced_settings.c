#include "config.h"

const unsigned char MAIN_KEY_ADIN1 = 14;
const unsigned int 	MAIN_ADIN1[]=
{
	438,516,344,425,
	518,596,344,425,
	598,675,344,425,
	677,754,344,425,
	756,842,344,425, 
	438,516,434,510,
	518,596,434,510,
	598,675,434,510,
	677,754,434,510,
	756,842,434,510,

	500,779,254,328, //11 清零
	518,620,519,586, //12 返回
	  0,  1,  0,  1, //13 删除
	657,764,519,586, //14 确认
};

void dis_adv_password(u8 wei);
u8 comparison_password(u8 wei,u8 *buf);

void main_xs_advanced_settings(void)
{
	u8 key,wei,adv_psw[6];
	DIS_PICNUM(Pic_ADVANCED_SETTINGS);
	adv_psw[0] = 0;
	adv_psw[1] = 0;
	adv_psw[2] = 0;
	adv_psw[3] = 0;
	adv_psw[4] = 0;
	adv_psw[5] = 0;
	wei = 0;
	
	DIS_FONT_C(0x00,0x00,4,0x01,10,783,"V1.0");
	
	do{
		if(Uart_LCD.KEY_YES!=0x00){
			ADS7843_KEY();
		  	key=KEY_FANHUI(MAIN_KEY_ADIN1,MAIN_ADIN1); 
	 	  	switch(key){
				case  1:if(wei < 6){XIANG1();adv_psw[wei] = 1;wei++;dis_adv_password(wei);}break;
        		case  2:if(wei < 6){XIANG1();adv_psw[wei] = 2;wei++;dis_adv_password(wei);}break;
        		case  3:if(wei < 6){XIANG1();adv_psw[wei] = 3;wei++;dis_adv_password(wei);}break;
				case  4:if(wei < 6){XIANG1();adv_psw[wei] = 4;wei++;dis_adv_password(wei);}break;
				case  5:if(wei < 6){XIANG1();adv_psw[wei] = 5;wei++;dis_adv_password(wei);}break;
				case  6:if(wei < 6){XIANG1();adv_psw[wei] = 6;wei++;dis_adv_password(wei);}break;
				case  7:if(wei < 6){XIANG1();adv_psw[wei] = 7;wei++;dis_adv_password(wei);}break;
				case  8:if(wei < 6){XIANG1();adv_psw[wei] = 8;wei++;dis_adv_password(wei);}break;
				case  9:if(wei < 6){XIANG1();adv_psw[wei] = 9;wei++;dis_adv_password(wei);}break;
				case 10:if(wei < 6){XIANG1();adv_psw[wei] = 0;wei++;dis_adv_password(wei);}break;
				case 11:
					XIANG1();
					adv_psw[0] = 0;
	   				adv_psw[1] = 0;
	   				adv_psw[2] = 0;
	   				adv_psw[3] = 0;
	   				adv_psw[4] = 0;
	   				adv_psw[5] = 0;
	   				wei = 0;
					dis_adv_password(wei);
					break;
				case 12:
					XIANG1();
					INTERFACE = LAST_INTERFACE;
					goto over_main_xs_advanced_settings;
				case 13:
					XIANG1();
					adv_psw[wei] = 0;
					if(wei > 0)wei--;
					dis_adv_password(wei);
					break;
				case 14:
					XIANG1();
					comparison_password(wei,adv_psw);
					goto over_main_xs_advanced_settings;
			}
			Uart_LCD.KEY_YES = 0;
		}
	}while(1);
	over_main_xs_advanced_settings:
	LAST_INTERFACE = PAGE_ADVANCED_SETTINGS;
}

void dis_adv_password(u8 wei)
{
  	u16 x,y;
	u8 add,i;
	x = 660;
	y = 273;
	add = 20;
	DIS_DEL_DIS(Pic_ADVANCED_SETTINGS,500,254,779,328,500,254);
	
	if(wei > 0 && wei <= 6){
		for(i=0;i<wei;i++){
			DIS_FONT_C(0xff,0xff,1,0x04,x,y,"*");
			x -= add;
		}
	}
}


u8 comparison_password(u8 wei,u8 *buf)
{
	if(wei == 6){
		if(buf[0] == 1 && buf[1] == 7 && buf[2] == 1 && buf[3] == 2 && buf[4] == 1 && buf[5] == 2){
			if(SW.RECORD_FLAG == 1)SW.RECORD_FLAG = 0;else{SW.RECORD_FLAG = 1;}//进入后记录参数
			INTERFACE = PAGE_WAITING;
			return 0; 
		}
		if(buf[0] == 1 && buf[1] == 5 && buf[2] == 0 && buf[3] == 8 && buf[4] == 2 && buf[5] == 4){
			INTERFACE = PAGE_SETTING_POWER;
			return 0; 
		}
		if(buf[0] == 1 && buf[1] == 2 && buf[2] == 3 && buf[3] == 3 && buf[4] == 2 && buf[5] == 1){
			if(XIAN_FLAG == 1)XIAN_FLAG = 0;else{XIAN_FLAG = 1;}
			INTERFACE = PAGE_WAITING;
			return 0; 
		}
		if(buf[0] == 1 && buf[1] == 5 && buf[2] == 0 && buf[3] == 2 && buf[4] == 2 && buf[5] == 4){
			INTERFACE = PAGE_BASIC_SETTINGS;
			return 0; 
		}

		


		buf[0] = 0;
		buf[1] = 0;
		buf[2] = 0;
		buf[3] = 0;
		buf[4] = 0;
		buf[5] = 0;
		wei = 0;
		dis_adv_password(wei);
  	}else{
		buf[0] = 0;
	 	buf[1] = 0;
		buf[2] = 0;
		buf[3] = 0;
		buf[4] = 0;
		buf[5] = 0;
		wei = 0;
		dis_adv_password(wei);
  	}
	return 1; 
}







 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

