#ifndef __DISPLAY_H
#define __DISPLAY_H
#include "config.h"

void LCD_OUT_OVER(void);
void DIS_PICNUM(u8 picnum);
void DIS_DEL_DIS(u8 picnum,u16 xs,u16 ys,u16 xe,u16 ye,u16 x,u16 y);
void DIS_FONT_C(u8 color1,u8 color2,u8 gs,u8 C_dots,u16 x,u16 y,u8 *buf);
void DIS_FONT_NUMBER_C(u8 color1,u8 color2,u8 datat,u8 C_dots,u16 x,u16 y);
void DIS_FONT_WEI_NUMBER_CM(u8 pic,u8 duiqi,u8 color1,u8 color2,u8 C_dots,u32 datat,u8 wei,u16 x,u16 y);
void DIS_FONT_WEI_VALUE(u8 pic,u8 duiqi,u8 color1,u8 color2,u8 C_dots,u8 wei,u8 flag,u32 value,u32 buff,u16 x,u16 y);
void DIS_FONT_WEI_CLOCK(u8 pic,u8 color1,u8 color2,u8 C_dots,u8 flag,u8 shi,u8 fen,u8 miao,u8 buff_shi,u8 buff_fen,u8 buff_miao,u16 x,u16 y);
void DIS_FONT_WEI_TEMP(u8 pic,u8 color1,u8 color2,u8 C_dots,u8 dis,u16 value,u16 buff,u16 x,u16 y);	
void DIS_FONT_ONE_POINT_VALUE(u8 pic,u8 duiqi,u8 color1,u8 color2,u8 C_dots,u8 wei,u8 dis,u16 value,u16 buff,u16 x,u16 y);
#endif
















