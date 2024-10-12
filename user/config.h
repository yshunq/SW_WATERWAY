#ifndef _CONFIG_H
#define _CONFIG_H

//-----数据类型定义-----//
typedef  signed    char    int8;    // 8位有符号整型数
typedef  signed    int     int16;   //16位有符号整型数
typedef  signed    long    int32;   //32位有符号整型数
typedef  unsigned  char    uint8;   // 8位无符号整型数
typedef  unsigned  int     uint16;  //16位无符号整型数
typedef  unsigned  long    uint32;  //32位无符号整型数

typedef  unsigned  char    u8;   // 8位无符号整型数
typedef  unsigned  int     u16;  //16位无符号整型数
typedef  unsigned  long    u32;  //32位无符号整型数

//-----通用头文件-----//
#include <STC8A.h>
#include <intrins.h>
#include "uart.h"
#include "timer.h"
#include "pwm.h"
#include "all_extern_ram.h"
#include "all_fonction.h"
#include "24cxx.h"
#include "ADS7843.h"
#include "display.h"
#include "eeprom_data.h"
#include "init.h"
#include "count_sw_work.h"
#include "cut_sw_work.h"
#include "dis_sw_work.h"
#include "key.h"
#include "other.h"
#include "adc.h"

#define Edition1	1
#define Edition2	0

#define ONE_SECONDS	20000

#define DIS_ALL		0
#define DIS_PART	1

#define CLEAR		0
#define PASS		1

#define PARTS_SHOULDER	0
#define PARTS_ELBOW		1
#define PARTS_HIP		2
#define PARTS_ED		3
#define PARTS_FOOT		4
#define PARTS_LUMBAR	5
#define PARTS_HAND		6
#define PARTS_FAT		7
#define PARTS_PUBIC		8
#define PARTS_KNEE		9

#define PROBE_D8		0
#define PROBE_D15		1
#define PROBE_C15		2
#define PROBE_D20		3
#define PROBE_D32		4

//-----全局运行参数定义-----//
//#define FOSC   11059200L  //系统主时钟频率，即振荡器频率÷12
#define FOSC   33177600L  	//系统主时钟频率，即振荡器频率÷12
#define	BRT1	(65536 - FOSC / 115200 / 4)
#define	BRT2	(65536 - FOSC / 9600 / 4)
#define	BRT3	(65536 - FOSC / 115200 / 4)
#define	BRT4	(65536 - FOSC / 115200 / 4)



#define  AD_LOGO_FLAG							0
#define  AD_PARAMETER							1 	//1 - 51
#define  AD_POWER_SET_BODY_VALUE_START			52	//52 - 61
#define  AD_POWER_SET_ED_VALUE_START			62	//62 - 67
#define  ADH_LL_CONSTANT						68
#define  ADL_LL_CONSTANT						69
#define  AD_LL_WARNING_FLAG						70
#define  ADH_LL_WARNING_VALUE					71
#define  ADL_LL_WARNING_VALUE					72
#define  AD_HANDLE_WARNING_FLAG					73
#define  ADH_HANDLE_WARNING_VALUE				74
#define  ADL_HANDLE_WARNING_VALUE				75
#define  AD_HANDLE_INSERT_WARNING_FLAG			76
#define  ADH_EEPROM_TOTAL_TIME					77
#define  ADM_EEPROM_TOTAL_TIME					78
#define  ADL_EEPROM_TOTAL_TIME					79


#define  PAGE_WAITING							0
#define  PAGE_LOADING							1
#define  PAGE_ADVANCED_SETTINGS					2
#define  PAGE_SW_WORK							3
#define  PAGE_GUIDE								4
#define  PAGE_PROBE_MODE						5
#define  PAGE_SETTING_POWER						6
#define  PAGE_BASIC_SETTINGS					7


#define  Pic_LOGO								1
#define  Pic_SW_WORK_START						2
#define  Pic_SW_WORK_DOWN						12
#define  Pic_SW_GUIDE_START						13
#define  Pic_SW_PROBE_START						23
#define  Pic_ADVANCED_SETTINGS					28
#define  Pic_SETTING_POWER						29
#define  Pic_BASIC_SETTINGS						30
#define  Pic_ERROR1								31
#define  Pic_ERROR2								32



#define  DD_ON					P25 = 0
#define  DD_OFF					P25 = 1
#define  XIANG1();				DD_ON;SOUND_COUNT = 80;


#define  DEPUTY_COIL_ON			P26 = 0;
#define  DEPUTY_COIL_OFF		P26 = 1;		

#define  MAIN_COIL_ON			P13 = 0;
#define  MAIN_COIL_OFF			P13 = 1;

#define  COOL_FS_ON				P37 = 1;
#define  COOL_FS_OFF			P37 = 0;

#define  FAST_CHARGING_ON		P27 = 1;
#define  FAST_CHARGING_OFF		P27 = 0;

#define  JDQ_SET_POWER_ON		P20 = 1;
#define  JDQ_SET_POWER_OFF		P20 = 0;

#define  BENG_ON				P54 = 1;
#define  BENG_OFF				P54 = 0;


//#define  		KEY										(KK & HANDLE_KEY_FLAG)

//sbit LED  = P5^5;
//sbit LED1 = P2^5;

sbit JTKEY = P2^2;
sbit HANDLE_INSERTION_KEY = P3^4;










#endif