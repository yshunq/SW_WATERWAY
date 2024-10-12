#include "key.h"

KeyState jt_state = WAIT_PRESS; 
//KeyState insertion_state = WAIT_PRESS; 

u8 read_jtkey(void)
{
	return JTKEY;
}

u8 read_insertion(void)
{
	return HANDLE_INSERTION_KEY;
}

u8 read_start_insertion(void)//长按去抖
{
	return read_insertion();
//	static u16 record_time = 0; 
//	switch(insertion_state){
//		case WAIT_PRESS:
//			if(read_insertion() == 0){
//				record_time = SYSTEM_CC;
//				insertion_state = DEBOUNCE;
//			}
//			break;
//		case DEBOUNCE:
//			if((SYSTEM_CC - record_time) > 20){
//				if(read_insertion() == 0){
//					insertion_state = KEY_PRESSED;
//				}else{
//					insertion_state = WAIT_PRESS;
//				}
//			}else{
//				if(read_insertion() == 1)insertion_state = WAIT_PRESS;
//			}
//			break;
//		case KEY_PRESSED:
//			if(read_insertion() == 0){
//				return 0;
//			}else{
//				insertion_state = WAIT_PRESS;
//			}
//			break;
//	}
//	return 1;	
}

u8 read_start_jtkey(void)//长按去抖
{
	static u16 record_time = 0; 
	switch(jt_state){
		case WAIT_PRESS:
			if(read_jtkey() == 0){
				record_time = SYSTEM_CC;
				jt_state = DEBOUNCE;
			}
			break;
		case DEBOUNCE:
			if((SYSTEM_CC - record_time) > 20){
				if(read_jtkey() == 0){
					jt_state = KEY_PRESSED;
				}else{
					jt_state = WAIT_PRESS;
				}
			}else{
				if(read_jtkey() == 1)jt_state = WAIT_PRESS;
			}
			break;
		case KEY_PRESSED:
			if(read_jtkey() == 0){
				return 0;
			}else{
				jt_state = WAIT_PRESS;
			}
			break;
	}
	return 1;	
}








