#ifndef __INIT_H
#define __INIT_H
#include "config.h"

struct SW_TypeDef{	//�Ŷ����������
	u8 TIME_WORK_FLAG;	//��ʱ��������־λ
	u8 RECORD_FLAG;	//��¼��־λ
	u8 POWER;		//������λ	   			
	u8 FREQUENCY;	//Ƶ��
	u8 PROBE_MODE;	//̽ͷ
	u8 BODY_PARTS; 	//���岿λ
	u8 MAX_POWER;	//������λ���ֵ
	u8 POWER_SET_BODY_VALUE[10];	//�����̨�������ֵ
	u8 POWER_SET_ED_VALUE[6];		//ED��̨�������ֵ
	u16 PRELOAD_TIME;	//Ԥ��Ŀ�����
	u16 TOTAL_TIME;		//���ƴ���
	u32 CLOCK_COUNT;	//ʱ���������
	u32 WORK_COUNT;		//�����ļ�ʱ
	u32 SET_TIME;		//���ʱ��
	u32 CYCLE_TIME;		//����ʱ��
	u32 EEPROM_TOTAL_TIME;
};

struct LL_TypeDef{	//��������������
	u8 WARNING_FLAG;	//������־λ
	u16 WARNING_VALUE;	//����ֵ
	u16 CONSTANT;	//��������X10
	u16 VALUE;		//����ֵX100
	u32 COUNT;		//�ж��м���
	u32 CYCLE;		//����1�����������
	u32 TIME_COUNT;  //��ʱ������ļ�ʱ
};

struct Warning_TypeDef{	//�¶�
	u8 WARNING_FLAG;	//������־λ
	u16 WARNING_VALUE;	//����ֵ
};





extern struct SW_TypeDef SW;

extern struct LL_TypeDef LL;

extern struct Warning_TypeDef HANDLE_TMEP;
extern struct Warning_TypeDef HANDLE_INSERTION;
extern struct Warning_TypeDef HANDLE_INSERT;







#endif
