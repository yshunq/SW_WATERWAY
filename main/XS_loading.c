//#include "config.h"
//
//const u8  code MAIN_KEY_WAITING = 1;
//const u16 code MAIN_WAITING[]=
//{
//	0,799,0,599,
//};
//
////void dis_loading(u8 value);
//
//void main_xs_loading(void)
//{
//	DIS_PICNUM(Pic_LOGO);
//	do{
//		delay_ms(1);
//		if(KEY_YES!=0x00){
//			ADS7843_KEY(); 
//			key=KEY_FANHUI(MAIN_KEY_SET_ID,MAIN_SET_ID); 
//	    	switch(key){
//				case 1:
//	   	      		XIANG1();
//					INTERFACE = PAGE_LOADING;
//					goto over_main_xs_set_id;
//					break;
//				case 2:
//	   	      		XIANG1();
//					adv_psw[0] = 0;
//	 				adv_psw[1] = 0;
//	 				adv_psw[2] = 0;
//	 				wei = 0;
//					val = count_id_val(wei,adv_psw);
//					dis_enter_id(val);
//					break;
//				case 3:
//	   	      		XIANG1();
//					if(wei < 3){
//						adv_psw[wei] = 1;
//						wei++;
//					}
//					val = count_id_val(wei,adv_psw);
//					dis_enter_id(val);
//					break;
//				case 4:
//	   	      		XIANG1();
//					if(wei < 3){
//						adv_psw[wei] = 2;
//						wei++;
//					}
//					val = count_id_val(wei,adv_psw);
//					dis_enter_id(val);
//					break;
//				
//	    	}
//			KEY_YES = 0;
//		}
//	}while(1);
//	over_main_xs_set_id:
//	_nop_();
//}

//void dis_loading(u8 value)
//{
//	static u8 buff;
//	DIS_FONT_WEI_VALUE(1,1,0xff,0xff,0x05,5,DIS_PART,value,buff,0,0);
//	buff = value;
//}

 