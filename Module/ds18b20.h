#ifndef DS18B20_H
#define DS18B20_H
#include <REGX52.H>
#include "delay.h"
//��ȡ�¶�
unsigned short ds18b20_read_temperature(void);
//��ʼת�� 0������ʧ��	1�������ɹ�
unsigned char ds18b20_conversion_start(void);
//��ȡ״̬ 1:no 0:ok
unsigned char ds18b20_read_status(void);
//ģ���ʼ�� 1:ģ����� 0��ģ�鲻����
unsigned char ds18b20_init(void);
#endif