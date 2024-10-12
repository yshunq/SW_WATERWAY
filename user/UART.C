#include "uart.h"

struct Uart_TypeDef Uart_LCD;

void Uart3Init(void)
{
	P0M1 &= ~(1 << 1);	//P01推挽输出
  	P0M0 |= (1 << 1);
	P_SW2 &= ~0x02;            //S3_S0=0 (P0.0/RxD3, P0.1/TxD3)
	//P_SW2 |= 0x02;           //S3_S0=1 (P5.0/RxD3_2, P5.1/TxD3_2)
	S3CON |= 0x50;
	T3L = BRT3;
	T3H = BRT3 >> 8;
	T4T3M |= 0x0a;
	Uart_LCD.UART_BUSY = 0;
	Uart_LCD.RX_RAM=10;
	IE2 |= 0x08;
}

void UartSend_LCD(u8 dat)
{
	Uart3Send(dat);	
}

void Uart3Send(u8 dat)
{
	while (Uart_LCD.UART_BUSY);
	Uart_LCD.UART_BUSY = 1;
	S3BUF = dat;
}

void Uart3Isr() interrupt 17
{
	static u8 flag = 0;
	u8 dat;
	if (S3CON & 0x02){
		S3CON &= ~0x02;
		Uart_LCD.UART_BUSY = 0;
	}
	if (S3CON & 0x01){
		S3CON &= ~0x01;
		dat = S3BUF;
		switch(Uart_LCD.RX_RAM){
			case 10:if(dat==0xAA)Uart_LCD.RX_RAM--;else{Uart_LCD.RX_RAM=10;flag=0x00;}break;
			case  9:
				switch(dat){
					case 0x73:flag=0xff;break; //有按键	
					case 0x72:flag=0x00;Uart_LCD.KEY_YES=flag;break; //没按键
				}Uart_LCD.RX_RAM--;break; 
				case  8:Uart_LCD.KEY_XH=dat; Uart_LCD.RX_RAM--; break;
				case  7:Uart_LCD.KEY_XL=dat; Uart_LCD.RX_RAM--; break;
				case  6:Uart_LCD.KEY_YH=dat; Uart_LCD.RX_RAM--; break;
				case  5:Uart_LCD.KEY_YL=dat; Uart_LCD.RX_RAM--; Uart_LCD.KEY_YES = flag; break;
				case  4:Uart_LCD.RX_RAM--; break;
				case  3:Uart_LCD.RX_RAM--; break;
				case  2:Uart_LCD.RX_RAM--; break;
				case  1:Uart_LCD.RX_RAM=10;break;
				default:Uart_LCD.RX_RAM=10;flag=0x00;break; 		   		   		        
		}
	}
}













//
//
//bit UART4_BUSY;
//unsigned char RX4_RAM;
//unsigned char KEY_YES;
//unsigned int  ADS7843_X,ADS7843_Y;
//unsigned char KEY_XH,KEY_XL;
//unsigned char KEY_YH,KEY_YL; 
//
//bit UART2_BUSY;
//unsigned char RX2_RAM;
//unsigned char RX2_GS;
//unsigned char RX2_LENGTH;
//unsigned char RX2_DATA[20];
//
////----------------------------------------------------------------------------//
//// 函数名称：uart2Init 
//// 输入参数：无 
//// 输出参数：无 
//// 函数功能：设置好定时器2的工作模式 
////----------------------------------------------------------------------------//
//void Uart2Init(void)
//{
//	P_SW2 &= ~0x01;			//RXD/P1.0, TXD/P1.1
//	
//	S2CON |= 0x50;
//	T2L = BRT2;
//	T2H = BRT2 >> 8;
//	AUXR |= 0x14;
//	UART2_BUSY = 0;
//	RX2_RAM=100;
//	RX2_GS=0x00;
//	IE2 |= 0x01;
//}
//
////----------------------------------------------------------------------------//
//// 函数名称：uartSendData 
//// 输入参数：ucData: 发送字节 
//// 输出参数：无 
//// 函数功能：使用串口发送一个字节数据 
////----------------------------------------------------------------------------//
////void Uart2Send(u8 dat)
////{
////    while (UART2_BUSY);
////    UART2_BUSY = 1;
////    S2BUF = dat;
////}
//
////void tx2_out_3(u8 dat1,u8 dat2,u8 dat3)
////{
////	u8 temp;
////	temp = 0xAA + 0xAA +0x05 + dat1 + dat2 + dat3;
////	Uart2Send(0xAA);
////	Uart2Send(0xAA);
////	Uart2Send(0x05);
////	Uart2Send(dat1);
////	Uart2Send(dat2);
////	Uart2Send(dat3);
////	Uart2Send(temp);
////	Uart2Send(0xFE);
////}
////
////void tx2_out_4(u8 dat1,u8 dat2,u8 dat3,u8 dat4)
////{
////	u8 temp;
////	temp = 0xAA + 0xAA +0x06 + dat1 + dat2 + dat3 + dat4;
////	Uart2Send(0xAA);
////	Uart2Send(0xAA);
////	Uart2Send(0x06);
////	Uart2Send(dat1);
////	Uart2Send(dat2);
////	Uart2Send(dat3);
////	Uart2Send(dat4);
////	Uart2Send(temp);
////	Uart2Send(0xFE);
////}
//
////void tx2_out_5(u8 dat1,u8 dat2,u8 dat3,u8 dat4,u8 dat5)
////{
////	u8 temp;
////	temp = 0xAA + 0xAA +0x07 + dat1 + dat2 + dat3 + dat4 + dat5;
////	Uart2Send(0xAA);
////	Uart2Send(0xAA);
////	Uart2Send(0x07);
////	Uart2Send(dat1);
////	Uart2Send(dat2);
////	Uart2Send(dat3);
////	Uart2Send(dat4);
////	Uart2Send(dat5);
////	Uart2Send(temp);
////	Uart2Send(0xFE);
////}
////
////void tx2_out_6(u8 dat1,u8 dat2,u8 dat3,u8 dat4,u8 dat5,u8 dat6)
////{
////	u8 temp;
////	temp = 0xAA + 0xAA +0x08 + dat1 + dat2 + dat3 + dat4 + dat5 + dat6;
////	Uart2Send(0xAA);
////	Uart2Send(0xAA);
////	Uart2Send(0x08);
////	Uart2Send(dat1);
////	Uart2Send(dat2);
////	Uart2Send(dat3);
////	Uart2Send(dat4);
////	Uart2Send(dat5);
////	Uart2Send(dat6);
////	Uart2Send(temp);
////	Uart2Send(0xFE);
////}
////----------------------------------------------------------------------------//
//// 函数名称： 
//// 输入参数：无 
//// 输出参数：无 
//// 函数功能：串口0服务函数 
////----------------------------------------------------------------------------//
//void Uart2Isr() interrupt 8
//{
//	u8 dat,db;
//	if (S2CON & S2TI)
//	{
//		S2CON &= ~S2TI;	//清除S2TI位
//		UART2_BUSY = 0;
//	}
//	if (S2CON & S2RI)
//	{
//		S2CON &= ~S2RI;         //清除S2RI位
//		dat = S2BUF;
//		switch(RX2_RAM)
//    {
//			case 100:if(dat==0xAA)RX2_RAM--;else{RX2_RAM=100;RX2_GS=0x00;}break;
//			case  99:if(dat==0xAA)RX2_RAM--;else{RX2_RAM=100;RX2_GS=0x00;}break;
//			case  98:if(dat < 20){RX2_LENGTH=dat;RX2_RAM=dat;RX2_RAM--;}else{RX2_RAM=100;RX2_GS=0x00;}break;	
//			default:
//				if(RX2_RAM==0x00)//接收完成
//     	  {
//					RX2_DATA[RX2_GS]=dat;
//					switch(RX2_DATA[0])
//					{
//						
//						case 0xC1://版本
//							if(CHOOS_HANDLE == XDRF_DEVICE_TYPE)
//							{
//								db = 0xAA + 0xAA + RX2_LENGTH + RX2_DATA[0] + RX2_DATA[1] + RX2_DATA[2] + RX2_DATA[3] + RX2_DATA[4] + RX2_DATA[5];
//								if(RX2_DATA[1] == XDRF_DEVICE_TYPE && RX2_DATA[6] == db && RX2_DATA[7] == 0xFE)
//								{
////									XDRF_EDITION[0] = RX2_DATA[2];
////									XDRF_EDITION[1] = RX2_DATA[3];
////									XDRF_EDITION[2] = RX2_DATA[4];
////									XDRF_EDITION[3] = RX2_DATA[5];
//								}
//							}
//							break;
//						
//          }
//					RX2_RAM=100;
//					RX2_GS =0x00;
//				}
//				else
//				{
//					RX2_DATA[RX2_GS]=dat;
//					RX2_RAM--;
//					RX2_GS++;
//				}
//				break; 	   		   		        
//    }
//	}
//}
//
//void Uart4Init(void)
//{
//	S4CON = 0x50;
//  T4L = BRT4;
//  T4H = BRT4 >> 8;
//  T4T3M = 0xa0;
//	UART4_BUSY = 0;
//	RX4_RAM=10;
//	IE2 |= 0x10;
//}
//
//void Uart4Send(u8 dat)
//{
//	while (UART4_BUSY);
//	UART4_BUSY = 1;
//	S4BUF = dat;
//}
//
//void UART4_Isr() interrupt 18
//{
//	static u8 flag = 0;
//	u8 dat;
//	if (S4CON & 0x02)
//	{
//		S4CON &= ~0x02;
//		UART4_BUSY = 0;
//	}
//	if (S4CON & 0x01)
//	{
//		S4CON &= ~0x01;
//		dat = S4BUF;
//		switch(RX4_RAM)
//    {
//			case 10:if(dat==0xAA)RX4_RAM--;else{RX4_RAM=10;flag=0x00;}break;
//			case  9:
//				switch(dat)
//				{
//					case 0x73:flag=0xff; //有按键
//						break;
//					case 0x72:flag=0x00; //没按键
//						KEY_YES=flag;
//						break;
//	      }
//				RX4_RAM--;
//				break; 
//			case  8:KEY_XH=dat; RX4_RAM--; break;
//			case  7:KEY_XL=dat; RX4_RAM--; break;
//			case  6:KEY_YH=dat; RX4_RAM--; break;
//			case  5:KEY_YL=dat; RX4_RAM--; KEY_YES = flag; break;
//			case  4:RX4_RAM--; break;
//			case  3:RX4_RAM--; break;
//			case  2:RX4_RAM--; break;
//			case  1:RX4_RAM=10;break;
//			default:RX4_RAM=10;flag=0x00;break; 		   		   		        
//    }
//	}
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
