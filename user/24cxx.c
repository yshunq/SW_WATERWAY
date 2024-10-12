#include "24cxx.h"

//--------------33177600L-----------//

//产生IIC起始信号
void IIC_Start(void)
{
	//SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	//IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}

//产生IIC停止信号
void IIC_Stop(void)
{
	//SDA_OUT();//sda线输出
	IIC_SCL=1;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();						   	
}	

//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
	u8 t;   
	//SDA_OUT(); 	    
	IIC_SCL=0;//拉低时钟开始数据传输
	for(t=0;t<8;t++){              
		IIC_SDA=(txd&0x80)>>7;
		txd<<=1; 	  
		_nop_();_nop_();_nop_();
		IIC_SCL=1;
		_nop_();_nop_();_nop_();
		IIC_SCL=0;	
		_nop_();_nop_();_nop_();
  }	 
} 

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	//SDA_IN();      //SDA设置为输入  
	IIC_SDA=1;_nop_();_nop_();_nop_();_nop_();	   
	IIC_SCL=1;_nop_();_nop_();_nop_();_nop_();
	while(IIC_SDA){
		ucErrTime++;
		if(ucErrTime>250){
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 

//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	//SDA_IN();//SDA设置为输入
  	for(i=0;i<8;i++ ){
    	IIC_SCL=0; 
    	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		IIC_SCL=1;
		_nop_();_nop_();_nop_();_nop_();
    	receive<<=1;
        if(IIC_SDA)receive++;   
		_nop_();_nop_();_nop_();_nop_();_nop_(); 
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}

//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL=0;
	//SDA_OUT();
	IIC_SDA=0;
	_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();
	IIC_SCL=1;
	_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();
	IIC_SCL=0;
}

//不产生ACK应答		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	//SDA_OUT();
	IIC_SDA=1;
	_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();
	IIC_SCL=1;
	_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();
	IIC_SCL=0;
}	

//在AT24CXX指定地址读出一个数据
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
  	IIC_Start();  
	if(EE_TYPE>AT24C16){
//		IIC_Send_Byte(0xA0);	   //发送写命令
//		IIC_Wait_Ack();
//		IIC_Send_Byte(ReadAddr>>8);//发送高地址
//		IIC_Wait_Ack();		 
	}else IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //发送器件地址0XA0,写数据 	 

	IIC_Wait_Ack(); 
  	IIC_Send_Byte(ReadAddr%256);   //发送低地址
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //进入接收模式			   
	IIC_Wait_Ack();	 
  	temp=IIC_Read_Byte(0);		   
  	IIC_Stop();//产生一个停止条件	    
	return temp;
}

//在AT24CXX指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16){
//		IIC_Send_Byte(0xA0);	    //发送写命令
//		IIC_Wait_Ack();
//		IIC_Send_Byte(WriteAddr>>8);//发送高地址
 	}else{
		IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //发送器件地址0XA0,写数据 
	}	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr%256);   //发送低地址
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //发送字节							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//产生一个停止条件 
	delay_ms(10);	 
}









