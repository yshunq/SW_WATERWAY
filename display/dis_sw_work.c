#include "dis_sw_work.h"



void dis_sw_work_body_parts(void)
{
	DIS_DEL_DIS(Pic_SW_WORK_START + SW.BODY_PARTS,468,0,1279,722,468,0);
	cut_sw_work_probe_mode();
	dis_sw_work_power(DIS_PART);
	dis_sw_work_frequency(DIS_PART);
	dis_sw_work_preload_time(DIS_PART);
	dis_sw_work_total_time(DIS_PART);	
}

void dis_sw_work_power(u8 dis)
{	
	static u8 buff = 0;
	u8 temp,pic;
	pic = Pic_SW_WORK_START + SW.BODY_PARTS;
	if(SW.BODY_PARTS == PARTS_ED){
		switch(SW.POWER){
			case 1:temp = 5;break;
			case 2:temp = 10;break;
			case 3:temp = 15;break;
			case 4:temp = 20;break;
			case 5:temp = 25;break;
			case 6:temp = 30;break;
		}
	}else{
		switch(SW.POWER){
			case 1:temp = 50;break;
			case 2:temp = 60;break;
			case 3:temp = 70;break;
			case 4:temp = 80;break;
			case 5:temp = 90;break;
			case 6:temp = 100;break;
			case 7:temp = 130;break;
			case 8:temp = 150;break;
			case 9:temp = 180;break;
			case 10:temp = 200;break;
		}
	}
	DIS_FONT_WEI_VALUE(pic,1,0x00,0x00,0x06,3,dis,temp,buff,225,123);
	buff = temp;
}

void dis_sw_work_frequency(u8 dis)
{	
	static u8 buff;
	u8 pic;
	pic = Pic_SW_WORK_START + SW.BODY_PARTS;
	DIS_FONT_WEI_VALUE(pic,1,0x00,0x00,0x06,3,dis,SW.FREQUENCY,buff,225,243);
	buff = SW.FREQUENCY;
}

void dis_sw_work_preload_time(u8 dis)
{
	static u32 buff;
	u8 pic;
	pic = Pic_SW_WORK_START + SW.BODY_PARTS;
	DIS_FONT_WEI_VALUE(pic,1,0x00,0x00,0x06,5,dis,SW.PRELOAD_TIME,buff,197,361);
	buff = SW.PRELOAD_TIME;
}

void dis_sw_work_total_time(u8 dis)
{
	static u32 buff;
	u8 pic;
	pic = Pic_SW_WORK_START + SW.BODY_PARTS;
	DIS_FONT_WEI_VALUE(pic,1,0x00,0x00,0x06,5,dis,SW.TOTAL_TIME,buff,197,483);
	buff = SW.TOTAL_TIME;
}

void dis_sw_work_ll_value(u8 dis)
{	
	static u16 buff;
	u8 pic;
	pic = Pic_SW_WORK_START + SW.BODY_PARTS;
	DIS_FONT_ONE_POINT_VALUE(pic,1,0xf8,0x00,0x01,3,dis,LL.VALUE,buff,5*8 + 10,10);
	//DIS_FONT_WEI_VALUE(pic,1,0xf8,0x00,0x01,4,dis,LL.VALUE,buff,5*8 + 10,10);
	buff = LL.VALUE;
}

void dis_sw_work_time(u8 dis)
{
	static u8 buff_shi,buff_fen,buff_miao;
	u8 pic,shi,fen,miao;
	u32 temp;
	pic = Pic_SW_WORK_START + SW.BODY_PARTS;
	temp = SW.CLOCK_COUNT;
	shi = temp/1000/3600;
	fen = temp/1000%3600/60;
	miao = temp/1000%60;
	DIS_FONT_WEI_CLOCK(pic,0xff,0xff,0x03,dis,shi,fen,miao,buff_shi,buff_fen,buff_miao,270,748);
	buff_shi = shi;
	buff_fen = fen;
	buff_miao = miao;
}

void dis_sw_work_handle_temp(u8 dis,u16 temp)
{
	static u16 buff;
	u8 pic;
	pic = Pic_SW_WORK_START + SW.BODY_PARTS;
	DIS_FONT_WEI_TEMP(pic,0xf8,0x00,0x01,dis,temp,buff,5*8+150,10);
	buff = temp;
}









