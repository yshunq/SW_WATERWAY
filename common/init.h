#ifndef __INIT_H
#define __INIT_H
#include "config.h"

struct SW_TypeDef{	//磁动冲击波功能
	u8 TIME_WORK_FLAG;	//定时器工作标志位
	u8 RECORD_FLAG;	//记录标志位
	u8 POWER;		//能量档位	   			
	u8 FREQUENCY;	//频率
	u8 PROBE_MODE;	//探头
	u8 BODY_PARTS; 	//身体部位
	u8 MAX_POWER;	//能量档位最大值
	u8 POWER_SET_BODY_VALUE[10];	//身体后台设置输出值
	u8 POWER_SET_ED_VALUE[6];		//ED后台设置输出值
	u16 PRELOAD_TIME;	//预设目标次数
	u16 TOTAL_TIME;		//治疗次数
	u32 CLOCK_COUNT;	//时间计算数据
	u32 WORK_COUNT;		//工作的计时
	u32 SET_TIME;		//输出时间
	u32 CYCLE_TIME;		//周期时间
	u32 EEPROM_TOTAL_TIME;
};

struct LL_TypeDef{	//流量传感器功能
	u8 WARNING_FLAG;	//报警标志位
	u16 WARNING_VALUE;	//报警值
	u16 CONSTANT;	//流量常数X10
	u16 VALUE;		//流量值X100
	u32 COUNT;		//中断中计数
	u32 CYCLE;		//计算1秒的脉冲周期
	u32 TIME_COUNT;  //定时器里面的计时
};

struct Warning_TypeDef{	//温度
	u8 WARNING_FLAG;	//报警标志位
	u16 WARNING_VALUE;	//报警值
};





extern struct SW_TypeDef SW;

extern struct LL_TypeDef LL;

extern struct Warning_TypeDef HANDLE_TMEP;
extern struct Warning_TypeDef HANDLE_INSERTION;
extern struct Warning_TypeDef HANDLE_INSERT;







#endif
