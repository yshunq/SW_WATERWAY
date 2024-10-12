#ifndef __24CXX_H
#define __24CXX_H
#include "config.h"
//Mini STM32������
//24CXX��������(�ʺ�24C01~24C16,24C32~256δ��������!�д���֤!)
//����ԭ��@ALIENTEK
//2010/6/10
//V1.2
#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	  8191
#define AT24C128	16383
#define AT24C256	32767  
//Mini STM32������ʹ�õ���24c02�����Զ���EE_TYPEΪAT24C02
#define EE_TYPE AT24C02

sbit IIC_SCL = P1^5;
sbit IIC_SDA = P1^4;

void IIC_Start(void);
void IIC_Send_Byte(unsigned char txd);
u8 IIC_Wait_Ack(void);
void IIC_Stop(void);
u8 AT24CXX_ReadOneByte(u16 ReadAddr);
void IIC_NAck(void);
u8 IIC_Read_Byte(unsigned char ack);
void IIC_Ack(void);
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite);

#endif
















