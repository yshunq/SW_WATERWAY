#ifndef __UART_H
#define __UART_H
#include "config.h"

struct Uart_TypeDef{
	u8 RX_RAM;
	u8 KEY_YES;
	u8 UART_BUSY;
	u16 ADS7843_X;
	u16 ADS7843_Y;
	u8 KEY_XH;
	u8 KEY_XL;
	u8 KEY_YH;
	u8 KEY_YL;
};
extern struct Uart_TypeDef Uart_LCD;

void Uart3Init(void);
void UartSend_LCD(u8 dat);
void Uart3Send(u8 dat);

#endif
