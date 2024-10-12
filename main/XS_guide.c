#include "config.h"

const u8  code MAIN_KEY_GUIDE = 14;
const u16 code MAIN_GUIDE[]=
{
	475,660,140,200,				//shoulder
	475,660,250,310,
	475,660,360,420,
	475,660,470,530,
	475,660,570,640,
								
	1065,1220,140,200,							//lumbar region
	1065,1220,250,310,
	1065,1220,360,420,
	1065,1220,470,530,
	1065,1220,570,640,


	935,1050,723,799,	   //设置
	1052,1167,723,799,	   //锁定
	1170,1279,723,799,	   //主界面

	468,871,0,67,		   //BODY_PARTS
};

void main_xs_guide(void)
{
	bit lock_flag;
	u8 key;
	lock_flag = 1;
	DIS_PICNUM(Pic_SW_GUIDE_START + SW.BODY_PARTS);
	do{
		if(Uart_LCD.KEY_YES!=0x00){
			ADS7843_KEY(); 
			key=KEY_FANHUI(MAIN_KEY_GUIDE,MAIN_GUIDE); 
	    	switch(key){
				case 1:		//SHOULDER
					if(SW.BODY_PARTS != PARTS_SHOULDER && lock_flag == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_SHOULDER;
						goto over_main_xs_guide;
					}
					Uart_LCD.KEY_YES = 0;
					break;
				case 2:		//ELBOW
					if(SW.BODY_PARTS != PARTS_ELBOW && lock_flag == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_ELBOW;
						goto over_main_xs_guide;
					}
					Uart_LCD.KEY_YES = 0;
					break;
				case 3:		//HIP
					if(SW.BODY_PARTS != PARTS_HIP && lock_flag == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_HIP;
						goto over_main_xs_guide;
					}
					Uart_LCD.KEY_YES = 0;
					break;
				case 4:		//ED
					if(SW.BODY_PARTS != PARTS_ED && lock_flag == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_ED;
						goto over_main_xs_guide;
					}
					Uart_LCD.KEY_YES = 0;
					break;
				case 5:		//FOOT
					if(SW.BODY_PARTS != PARTS_FOOT && lock_flag == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_FOOT;
						goto over_main_xs_guide;
					}
					Uart_LCD.KEY_YES = 0;
					break;
				case 6:		//LUMBAR
					if(SW.BODY_PARTS != PARTS_LUMBAR && lock_flag == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_LUMBAR;
						goto over_main_xs_guide;
					}
					Uart_LCD.KEY_YES = 0;
					break;
				case 7:		//HAND
					if(SW.BODY_PARTS != PARTS_HAND && lock_flag == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_HAND;
						goto over_main_xs_guide;
					}
					Uart_LCD.KEY_YES = 0;
					break;
				case 8:		//FAT
					if(SW.BODY_PARTS != PARTS_FAT && lock_flag == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_FAT;
						goto over_main_xs_guide;
					}
					Uart_LCD.KEY_YES = 0;
					break;
				case 9:		//PUBIC
					if(SW.BODY_PARTS != PARTS_PUBIC && lock_flag == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_PUBIC;
						goto over_main_xs_guide;
					}
					Uart_LCD.KEY_YES = 0;
					break;
				case 10:		//KNEE
					if(SW.BODY_PARTS != PARTS_KNEE && lock_flag == 1){
						XIANG1();
						SW.BODY_PARTS = PARTS_KNEE;
						goto over_main_xs_guide;
					}
					Uart_LCD.KEY_YES = 0;
					break;
				case 11:	//设置
					if(lock_flag == 1){
						XIANG1();
						INTERFACE = PAGE_ADVANCED_SETTINGS;
						goto over_main_xs_guide;
					}
					Uart_LCD.KEY_YES = 0;
					break;
				 case 12:	//锁屏幕
					XIANG1();
					if(lock_flag == 1){
						lock_flag = 0;
					}else{
					 	lock_flag = 1;
					}
					cut_sw_work_lock_flag(lock_flag);
					Uart_LCD.KEY_YES = 0;
					break;
				 case 13:	//返回LOGO
					if(lock_flag == 1){
						XIANG1();
						INTERFACE = PAGE_WAITING;
						goto over_main_xs_guide;
					}
					Uart_LCD.KEY_YES = 0;
					break;
				 case 14:	//工作界面
					if(lock_flag == 1){
						XIANG1();
						INTERFACE = PAGE_SW_WORK;
						goto over_main_xs_guide;
					}
					Uart_LCD.KEY_YES = 0;
					break;
	    	}
			Uart_LCD.KEY_YES = 0;
		}
	}while(1);
	over_main_xs_guide:
	LAST_INTERFACE = PAGE_GUIDE;
}
