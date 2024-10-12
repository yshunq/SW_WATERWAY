#include "config.h"

const u8  MAIN_KEY_SETTING_POWER = 33;
const u16 MAIN_SETTING_POWER[]=
{
	95,175,180,250,	   		//50-
	365,435,185,250,	   	//50+
	95,175,265,335,	   		//60-
	365,435,265,335,	   //60+
	95,175,355,420,	   		//70-
	365,435,355,420,	   //70+
	95,175,435,505,	   //80-
	365,435,435,505,	   //80+
	95,175,520,585,	   //90-
	365,435,520,585,	   //90+

	470,575,180,250,	   //100-
	740,810,185,250,	   //100+
	470,575,265,335,	   //130-
	740,810,265,335,	   //130+
	470,575,355,420,	   //150-
	740,810,355,420,	   //150+
	470,575,435,505,	   //180-
	740,810,435,505,	   //180+
	470,575,520,585,	   //200-
	740,810,520,585,	   //200+

	845,915,180,250,	   //5-
	1110,1180,185,250,	   //5+
	845,915,265,335,	   //10-
	1110,1180,265,335,	   //10+
	845,915,355,420,	   //15-
	1110,1180,355,420,	   //15+
	845,915,435,505,	   //20-
	1110,1180,435,505,	   //20+
	845,915,520,585,	   //25-
	1110,1180,520,585,	   //25+
	845,915,605,665,		//30-
	1110,1180,605,665,		//30+
	
	30,140,15,80,	   //·µ»Ø	
};

void dis_setting_power_body_value(u8 num,u8 dis);
void dis_setting_power_ed_value(u8 num,u8 dis);

void main_xs_setting_power(void)
{
	u8 key,i,num;
	DIS_PICNUM(Pic_SETTING_POWER);
	for(i=0;i<10;i++)dis_setting_power_body_value(i,DIS_ALL);
	for(i=0;i<6;i++)dis_setting_power_ed_value(i,DIS_ALL);
	do{
		if(Uart_LCD.KEY_YES!=0x00){
			ADS7843_KEY(); //É¨Ãè°´¼ü
			key=KEY_FANHUI(MAIN_KEY_SETTING_POWER,MAIN_SETTING_POWER); 
			if(key > 0 && key <= 20){
				num = (key-1)/2;
				if(key%2 == 1){//--
					if(num == 0){
						if(SW.POWER_SET_BODY_VALUE[num] > 1){
							XIANG1();
							SW.POWER_SET_BODY_VALUE[num]--;
							dis_setting_power_body_value(num,DIS_PART);
							write_power_set_body_value(num);	
							delay_ms(120);
						}
					}else{
						if(SW.POWER_SET_BODY_VALUE[num] > SW.POWER_SET_BODY_VALUE[num-1]){
							XIANG1();
							SW.POWER_SET_BODY_VALUE[num]--;
							dis_setting_power_body_value(num,DIS_PART);
							write_power_set_body_value(num);
							delay_ms(120);
						}
					}
				}else{//++
					if(num == 9){
						if(SW.POWER_SET_BODY_VALUE[num] < 25){
							XIANG1();
							SW.POWER_SET_BODY_VALUE[num]++;
							dis_setting_power_body_value(num,DIS_PART);
							write_power_set_body_value(num);
							delay_ms(120);
						}
					}else{
						if(SW.POWER_SET_BODY_VALUE[num] < SW.POWER_SET_BODY_VALUE[num+1]){
							XIANG1();
							SW.POWER_SET_BODY_VALUE[num]++;
							dis_setting_power_body_value(num,DIS_PART);
							write_power_set_body_value(num);
							delay_ms(120);
						}
					}
				}
				//Uart_LCD.KEY_YES = 0x00;
			}else if(key > 20 && key <= 32){
				num = (key-21)/2;
				if(key%2 == 1){//--
					if(num == 0){
						if(SW.POWER_SET_ED_VALUE[num] > 1){
							XIANG1();
							SW.POWER_SET_ED_VALUE[num]--;
							dis_setting_power_ed_value(num,DIS_PART);
							write_power_set_ed_value(num);	
							delay_ms(120);
						}
					}else{
						if(SW.POWER_SET_ED_VALUE[num] > SW.POWER_SET_ED_VALUE[num-1]){
							XIANG1();
							SW.POWER_SET_ED_VALUE[num]--;
							dis_setting_power_ed_value(num,DIS_PART);
							write_power_set_ed_value(num);
							delay_ms(120);
						}
					}		
				}else{//++
					if(num == 5){
						if(SW.POWER_SET_ED_VALUE[num] < 25){
							XIANG1();
							SW.POWER_SET_ED_VALUE[num]++;
							dis_setting_power_ed_value(num,DIS_PART);
							write_power_set_ed_value(num);
							delay_ms(120);
						}
					}else{
						if(SW.POWER_SET_ED_VALUE[num] < SW.POWER_SET_ED_VALUE[num+1]){
							XIANG1();
							SW.POWER_SET_ED_VALUE[num]++;
							dis_setting_power_ed_value(num,DIS_PART);
							write_power_set_ed_value(num);
							delay_ms(120);
						}
					}
				}
				//Uart_LCD.KEY_YES = 0x00;
			}else if(key == 33){//·µ»Ø
				XIANG1();
				INTERFACE = PAGE_WAITING;
				goto over_main_xs_setting_power;
			} 
		}
	}while(1);
	over_main_xs_setting_power:
	LAST_INTERFACE = PAGE_SETTING_POWER;
}

void dis_setting_power_body_value(u8 num,u8 dis)
{
	static u8 buff[10];
	u16 x,y;
	switch(num){
		case 0:x = 280;y = 202;break;
		case 1:x = 280;y = 286;break;
		case 2:x = 280;y = 370;break;
		case 3:x = 280;y = 454;break;
		case 4:x = 280;y = 538;break;
		case 5:x = 658;y = 202;break;
		case 6:x = 658;y = 286;break;
		case 7:x = 658;y = 370;break;
		case 8:x = 658;y = 454;break;
		case 9:x = 658;y = 538;break;
	}
	DIS_FONT_WEI_VALUE(Pic_SETTING_POWER,1,0x00,0x00,0x03,3,dis,SW.POWER_SET_BODY_VALUE[num],buff[num],x,y);
	buff[num] = SW.POWER_SET_BODY_VALUE[num];
}

void dis_setting_power_ed_value(u8 num,u8 dis)
{
	static u8 buff[6];
	u16 x,y;
	switch(num){
		case 0:x = 1018;y = 202;break;
		case 1:x = 1018;y = 286;break;
		case 2:x = 1018;y = 370;break;
		case 3:x = 1018;y = 454;break;
		case 4:x = 1018;y = 538;break;
		case 5:x = 1018;y = 622;break;
	}
	DIS_FONT_WEI_VALUE(Pic_SETTING_POWER,1,0x00,0x00,0x03,3,dis,SW.POWER_SET_ED_VALUE[num],buff[num],x,y);
	buff[num] = SW.POWER_SET_ED_VALUE[num];
}
















