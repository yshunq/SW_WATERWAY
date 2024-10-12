#include "display.h"

void LCD_OUT_OVER(void) //帧结束符
{  	
	UartSend_LCD(0xCC);
 	UartSend_LCD(0x33);
 	UartSend_LCD(0xC3);
 	UartSend_LCD(0x3C);
}

//显示保存在终端的全屏图片
//picnum为显示图片的索引号
void DIS_PICNUM(u8 picnum)
{
  	UartSend_LCD(0xAA);
	UartSend_LCD(0x70);
	UartSend_LCD(picnum);
	LCD_OUT_OVER(); //帧结束符
}

//将Flash中的索引号为picnum的图片分割显示在x,y
void DIS_DEL_DIS(u8 picnum,u16 xs,u16 ys,u16 xe,u16 ye,u16 x,u16 y)
{
	UartSend_LCD(0xAA);
	UartSend_LCD(0x71);
	UartSend_LCD(picnum);
	UartSend_LCD(xs>>8);
	UartSend_LCD(xs);
	UartSend_LCD(ys>>8);
	UartSend_LCD(ys);
	UartSend_LCD(xe>>8);
	UartSend_LCD(xe);
	UartSend_LCD(ye>>8);
	UartSend_LCD(ye);
	UartSend_LCD(x>>8);
	UartSend_LCD(x);
	UartSend_LCD(y>>8);
	UartSend_LCD(y);
	LCD_OUT_OVER(); //帧结束符
}

//----------------------下面是可以选择颜色的全部函数-------------------------------------//
//color  颜色  红色：color1=0x08 color2=0x00     白色：color1=0xFF color2=0xFF   黑色：color1=0x00 color2=0x00
//gs 发送个数
//C_dots 字体的大小  (0x00 - 6*12) (0x01 - 8*16) (0x02 - 12*24) (0x03 - 16*32) (0x04 - 20*40) (0x05 - 24*48) (0x06 - 28*56) (0x07 - 32*64)
//x  x轴坐标
//y  y轴坐标
//*buf  字符
void DIS_FONT_C(u8 color1,u8 color2,u8 gs,u8 C_dots,u16 x,u16 y,u8 *buf) //显示字符  颜色  个数  大小  xy 字符
{
  uint8 loop;
	UartSend_LCD(0xAA);
	UartSend_LCD(0x98);
	UartSend_LCD(x>>8);
	UartSend_LCD(x);
	UartSend_LCD(y>>8);
	UartSend_LCD(y);
	UartSend_LCD(0x00);//字库
	UartSend_LCD(0x81);
	UartSend_LCD(C_dots);//字体大小
	UartSend_LCD(color1);
	UartSend_LCD(color2);//显示出文字颜色 (F800 红 FFFF白)
	UartSend_LCD(0x00);
	UartSend_LCD(0x00);
	for(loop=0x00;loop<gs;loop++)
	{
		UartSend_LCD(*buf);
		buf++;
	}
	LCD_OUT_OVER(); //帧结束符
}

//color  颜色  红色：color1=0x08 color2=0x00     白色：color1=0xFF color2=0xFF   黑色：color1=0x00 color2=0x00
//data 显示数据
//C_dots 显示大小
//x  x轴坐标
//y  y轴坐标
void DIS_FONT_NUMBER_C(u8 color1,u8 color2,u8 datat,u8 C_dots,u16 x,u16 y)//显示一个数字  颜色  数据  大小  x  y
{
	switch(datat)
	{
	  case  0:DIS_FONT_C(color1,color2,1,C_dots,x,y,"0");break;//0
		case  1:DIS_FONT_C(color1,color2,1,C_dots,x,y,"1");break;//1
		case  2:DIS_FONT_C(color1,color2,1,C_dots,x,y,"2");break;//2
	  case  3:DIS_FONT_C(color1,color2,1,C_dots,x,y,"3");break;//3
	  case  4:DIS_FONT_C(color1,color2,1,C_dots,x,y,"4");break;//4
	  case  5:DIS_FONT_C(color1,color2,1,C_dots,x,y,"5");break;//5
	  case  6:DIS_FONT_C(color1,color2,1,C_dots,x,y,"6");break;//6
	  case  7:DIS_FONT_C(color1,color2,1,C_dots,x,y,"7");break;//7
	  case  8:DIS_FONT_C(color1,color2,1,C_dots,x,y,"8");break;//8
	  case  9:DIS_FONT_C(color1,color2,1,C_dots,x,y,"9");break;//9
	  case 10:DIS_FONT_C(color1,color2,1,C_dots,x,y,".");break;//.
	  case 11:DIS_FONT_C(color1,color2,1,C_dots,x,y,"V");break;//V
	  case 12:DIS_FONT_C(color1,color2,1,C_dots,x,y,"A");break;//A
	  case 13:DIS_FONT_C(color1,color2,1,C_dots,x,y,"B");break;//B
	  case 14:DIS_FONT_C(color1,color2,1,C_dots,x,y," ");break;//空格
  }
}

//color  颜色  红色：color1=0x08 color2=0x00     白色：color1=0xFF color2=0xFF   黑色：color1=0x00 color2=0x00
//C_dots 显示大小
//data 表示显示的数据
//wei 表示显示的位数
//x  x轴坐标
//y  y轴坐标
void DIS_FONT_WEI_NUMBER_CM(u8 pic,u8 duiqi,u8 color1,u8 color2,u8 C_dots,u32 datat,u8 wei,u16 x,u16 y)//剪切图片 左0中1右2 颜色1 颜色2 字体大小 显示数值 位数 x坐标 y坐标
{
  uint8 xian[8];
	uint8 x_add,y_add,i;
	uint16 xs,ys;
	uint32 temp;
	i = 0;
	xian[0] = (uint8)(datat%10);
	xian[1] = (uint8)((datat/10)%10);
	xian[2] = (uint8)((datat/100)%10);
	xian[3] = (uint8)((datat/1000)%10);
	xian[4] = (uint8)((datat/10000)%10);
	xian[5] = (uint8)((datat/100000)%10);
	xian[6] = (uint8)((datat/1000000)%10);
	xian[7] = (uint8)((datat/10000000)%10);
	switch(C_dots)//显示的位数
	{
		case  0x00: x_add = 6;y_add = 12;break;
		case  0x01: x_add = 8;y_add = 16;break;
		case  0x02: x_add = 12;y_add = 24;break;
		case  0x03: x_add = 16;y_add = 32;break;
		case  0x04: x_add = 20;y_add = 40;break;
		case  0x05: x_add = 24;y_add = 48;break;
		case  0x06: x_add = 28;y_add = 56;break;
		case  0x07: x_add = 32;y_add = 64;break;
	}
	if(pic < 255)DIS_DEL_DIS(pic,x,y,x+(wei*x_add),y+y_add,x,y);
	temp = datat;
	do{
	   i++;
	   temp/=10;
	}while(temp>0);
	
	if(i > wei)i = wei;
	if(duiqi == 0)xs = x;//左对齐
	else if(duiqi == 1)xs = (wei - i)*(x_add/2)+x;//居中
	else{xs = (wei - i)*x_add+x;}//右对齐
	ys = y;
	do{
		i--;
		DIS_FONT_NUMBER_C(color1,color2,xian[i],C_dots,xs,ys);//显示一个数字
		xs = xs + x_add;
		_nop_();
		_nop_();
	}while(i>0);
}


//显示前后对比数据
void DIS_FONT_WEI_VALUE(u8 pic,u8 duiqi,u8 color1,u8 color2,u8 C_dots,u8 wei,u8 flag,u32 value,u32 buff,u16 x,u16 y)
{
	u8 i,wei1,wei2,pic_buff;
	u16 x_add,y_add,xs,ys;
	u32 temp,buff_temp;
	switch(C_dots){//显示的位数
		case  0x00: x_add =  6;y_add = 12;break;
		case  0x01: x_add =  8;y_add = 16;break;
		case  0x02: x_add = 12;y_add = 24;break;
		case  0x03: x_add = 16;y_add = 32;break;
		case  0x04: x_add = 20;y_add = 40;break;
		case  0x05: x_add = 24;y_add = 48;break;
		case  0x06: x_add = 28;y_add = 56;break;
		case  0x07: x_add = 32;y_add = 64;break;
		case  0x08: x_add = 40;y_add = 80;break;
		case  0x09: x_add = 48;y_add = 96;break;
		case  0x0A: x_add = 56;y_add = 112;break;
	}	 	
	
	temp = value;
	i = 0;
	do{
	   i++;
	   temp/=10;
	}while(temp>0);
	wei1 = i;
	if(i > wei)wei1 = wei;

	temp = buff;
	i = 0;
	do{
	   i++;
	   temp/=10;
	}while(temp>0);
	wei2 = i;
	if(i > wei)wei2 = wei;
	
	if(wei1 != wei2 || flag == DIS_ALL){
		temp = wei;
		DIS_DEL_DIS(pic,x,y,temp*x_add+x,y_add+y,x,y);
	}

	i = wei1;

	if(duiqi == 0)xs = (i - 1)*x_add + x;
	else if(duiqi == 1)xs = (wei - i)*(x_add/2) + x + ((i - 1)*x_add);
	else{xs = (wei - 1)*x_add + x;}
	ys = y;
	
	temp = value;
	buff_temp = buff;
	do{
		i--;
		if(wei1 != wei2 || flag == DIS_ALL)pic_buff = 255;
		else{pic_buff = pic;}
		if(wei1 != wei2 || flag == DIS_ALL || temp%10 != buff_temp%10){
			DIS_FONT_WEI_NUMBER_CM(pic_buff,duiqi,color1,color2,C_dots,temp%10,1,xs,ys);	
		}
		temp = temp/10;
		buff_temp = buff_temp/10;
		xs = xs - x_add;
		_nop_();
		_nop_();
	}while(i>0);
}

//显示 00:00:00
void DIS_FONT_WEI_CLOCK(u8 pic,u8 color1,u8 color2,u8 C_dots,u8 flag,u8 shi,u8 fen,u8 miao,u8 buff_shi,u8 buff_fen,u8 buff_miao,u16 x,u16 y)
{
	u16 x_add,y_add,xs,ys;
	xs = x;
	ys = y;
	switch(C_dots){//显示的位数
		case  0x00: x_add =  6;y_add = 12;break;
		case  0x01: x_add =  8;y_add = 16;break;
		case  0x02: x_add = 12;y_add = 24;break;
		case  0x03: x_add = 16;y_add = 32;break;
		case  0x04: x_add = 20;y_add = 40;break;
		case  0x05: x_add = 24;y_add = 48;break;
		case  0x06: x_add = 28;y_add = 56;break;
		case  0x07: x_add = 32;y_add = 64;break;
		case  0x08: x_add = 40;y_add = 80;break;
		case  0x09: x_add = 48;y_add = 96;break;
		case  0x0A: x_add = 56;y_add = 112;break;
	}
	if(flag == DIS_ALL || shi/10 != buff_shi/10){
		DIS_FONT_WEI_NUMBER_CM(pic,1,color1,color2,C_dots,shi/10,1,xs,ys);	
	}
	xs += x_add;
	if(flag == DIS_ALL || shi%10 != buff_shi%10){
		DIS_FONT_WEI_NUMBER_CM(pic,1,color1,color2,C_dots,shi%10,1,xs,ys);	
	}
	xs += x_add;
	if(flag == DIS_ALL){
		DIS_FONT_C(color1,color2,1,C_dots,xs,ys-3,":");
	}
	xs += x_add;
	if(flag == DIS_ALL || fen/10 != buff_fen/10){
		DIS_FONT_WEI_NUMBER_CM(pic,1,color1,color2,C_dots,fen/10,1,xs,ys);	
	}
	xs += x_add;
	if(flag == DIS_ALL || fen%10 != buff_fen%10){
		DIS_FONT_WEI_NUMBER_CM(pic,1,color1,color2,C_dots,fen%10,1,xs,ys);	
	}
	xs += x_add;
	if(flag == DIS_ALL){
		DIS_FONT_C(color1,color2,1,C_dots,xs,ys-3,":");
	}
	xs += x_add;
	if(flag == DIS_ALL || miao/10 != buff_miao/10){
		DIS_FONT_WEI_NUMBER_CM(pic,1,color1,color2,C_dots,miao/10,1,xs,ys);	
	}
	xs += x_add;
	if(flag == DIS_ALL || miao%10 != buff_miao%10){
		DIS_FONT_WEI_NUMBER_CM(pic,1,color1,color2,C_dots,miao%10,1,xs,ys);	
	}	
}

//显示温度  小数点一位 -25.0 ~ 99.0℃
void DIS_FONT_WEI_TEMP(u8 pic,u8 color1,u8 color2,u8 C_dots,u8 dis,u16 value,u16 buff,u16 x,u16 y)
{
	u8 i,wei[2],sign_flag[2];
	u16 x_add,y_add,xs,ys,temp,dat[2];
	switch(C_dots){//显示的位数
		case  0x00: x_add =  6;y_add = 12;break;
		case  0x01: x_add =  8;y_add = 16;break;
		case  0x02: x_add = 12;y_add = 24;break;
		case  0x03: x_add = 16;y_add = 32;break;
		case  0x04: x_add = 20;y_add = 40;break;
		case  0x05: x_add = 24;y_add = 48;break;
		case  0x06: x_add = 28;y_add = 56;break;
		case  0x07: x_add = 32;y_add = 64;break;
		case  0x08: x_add = 40;y_add = 80;break;
		case  0x09: x_add = 48;y_add = 96;break;
		case  0x0A: x_add = 56;y_add = 112;break;
	}
	//求value位数
	if(value < 250){//小于0度
		sign_flag[0] = 0;
		temp = 250 - value;
	}else{//大于0度
		sign_flag[0] = 1;
		temp = value - 250;
	}
	dat[0] = temp;
	i = 0;
	do{
	   i++;
	   temp/=10;
	}while(temp>0);
	wei[0] = i;
	if(i > 3)wei[0] = 3;


	//求buff位数
	if(buff < 250){//小于0度
		sign_flag[1] = 0;
		temp = 250 - buff;
	}else{//大于0度
		sign_flag[1] = 1;
		temp = buff - 250;
	}
	dat[1] = temp;
	i = 0;
	do{
	   i++;
	   temp/=10;
	}while(temp>0);
	wei[1] = i;
	if(i > 3)wei[1] = 3;
	
	if(dis == DIS_ALL || sign_flag[0] != sign_flag[1] || wei[0] != wei[1]){//全覆盖
		DIS_DEL_DIS(pic,x,y,5*x_add+x,y_add+y,x,y);	
	}
	//计算初始x，y坐标
	if(sign_flag[0] == 0){//负数
		if(wei[0] == 3)xs = x;else{xs = x_add/2 + x;}		
	}else{//正数
		if(wei[0] == 3)xs = x_add/2 + x;else{xs = x_add + x;}
	}
	ys = y;

	if(sign_flag[0] == 0){//负数
		if(dis == DIS_ALL || sign_flag[0] != sign_flag[1] || wei[0] != wei[1]){
			DIS_FONT_C(color1,color2,1,C_dots,xs,ys,"-");	
		}
		xs += x_add;
	}

	if(wei[0] >= 3){
		if(dis == DIS_ALL || sign_flag[0] != sign_flag[1] || wei[0] != wei[1] || dat[0]/100 != dat[1]/100){
			DIS_FONT_WEI_NUMBER_CM(pic,1,color1,color2,C_dots,dat[0]/100,1,xs,ys);			
		}
		xs += x_add;
	}

	if(dis == DIS_ALL || sign_flag[0] != sign_flag[1] || wei[0] != wei[1] || dat[0]%100/10 != dat[1]%100/10){
		DIS_FONT_WEI_NUMBER_CM(pic,1,color1,color2,C_dots,dat[0]%100/10,1,xs,ys);			
	}
	xs += x_add;

	if(dis == DIS_ALL || sign_flag[0] != sign_flag[1] || wei[0] != wei[1]){
		DIS_FONT_C(color1,color2,1,C_dots,xs,ys,".");	
	}
	xs += x_add;
	
	if(dis == DIS_ALL || sign_flag[0] != sign_flag[1] || wei[0] != wei[1] || dat[0]%10 != dat[1]%10){
		DIS_FONT_WEI_NUMBER_CM(pic,1,color1,color2,C_dots,dat[0]%10,1,xs,ys);			
	}	
}

//---------------------------------------------------------------------------------------------------//
//显示温度  小数点一位 0.0 ~ 99.9℃
//pic:页面
//color1,color2:颜色
//C_dots:大小
//wei：位数 2位以上
//dis：显示部分或全部
//value：真实数值
//buff：对比数值
//x,y:坐标
void DIS_FONT_ONE_POINT_VALUE(u8 pic,u8 duiqi,u8 color1,u8 color2,u8 C_dots,u8 wei,u8 dis,u16 value,u16 buff,u16 x,u16 y)
{
	u8 i,weishu[2],bwei;
	u16 x_add,y_add,xs,ys,temp,multiple;
	switch(C_dots){//显示的位数
		case  0x00: x_add =  6;y_add = 12;break;
		case  0x01: x_add =  8;y_add = 16;break;
		case  0x02: x_add = 12;y_add = 24;break;
		case  0x03: x_add = 16;y_add = 32;break;
		case  0x04: x_add = 20;y_add = 40;break;
		case  0x05: x_add = 24;y_add = 48;break;
		case  0x06: x_add = 28;y_add = 56;break;
		case  0x07: x_add = 32;y_add = 64;break;
		case  0x08: x_add = 40;y_add = 80;break;
		case  0x09: x_add = 48;y_add = 96;break;
		case  0x0A: x_add = 56;y_add = 112;break;
	}
	if(wei < 2)wei = 2;
	wei++;
	//求value位数
	temp = value;
	i = 0;
	do{
	   i++;
	   temp/=10;
	}while(temp>0);
	weishu[0] = i;
	if(weishu[0] > wei)weishu[0] = wei;else if(weishu[0] <= 2)weishu[0] = 2;
	weishu[0]++;

	//求buff位数
	temp = buff;
	i = 0;
	do{
	   i++;
	   temp/=10;
	}while(temp>0);
	weishu[1] = i;
	if(weishu[1] > wei)weishu[1] = wei;else if(weishu[1] <= 2)weishu[1] = 2;
	weishu[1]++;
	
	if(dis == DIS_ALL || weishu[0] != weishu[1]){//全覆盖
		DIS_DEL_DIS(pic,x,y,wei*x_add+x,y_add+y,x,y);	
	}
	
	//计算初始坐标x,y
	if(duiqi == 0){//左对齐
		xs = x;
	}else if(duiqi == 1){//中间对齐
		xs = (wei - weishu[0])*(x_add/2)+x;    
	}else{//右对齐
		xs = (wei - weishu[0])*x_add+x;
	}
	ys = y;

	multiple = 1;
	for(i=(weishu[0]-1);i>1;i--){
		multiple *= 10;	
	}

	bwei = weishu[0];
	while(bwei > 2){
		if(dis == DIS_ALL || weishu[0] != weishu[1] || value/multiple%10 != buff/multiple%10){
			DIS_FONT_WEI_NUMBER_CM(pic,1,color1,color2,C_dots,value/multiple%10,1,xs,ys);	
		}
		multiple /= 10;
		xs += x_add;
		bwei--;
	}
   	if(dis == DIS_ALL || weishu[0] != weishu[1]){
		DIS_FONT_C(color1,color2,1,C_dots,xs,ys,".");	
	}
	xs += x_add;
	if(dis == DIS_ALL || weishu[0] != weishu[1] || value%10 != buff%10){
		DIS_FONT_WEI_NUMBER_CM(pic,1,color1,color2,C_dots,value%10,1,xs,ys);	
	}
}









