#include "ds18b20.h"

#define DS18B20_PIN	P1_0
#define DS18B20_1US		_nop_()
#define DS18B20_2US		DS18B20_1US;DS18B20_1US
#define DS18B20_3US		DS18B20_1US;DS18B20_2US
#define DS18B20_4US		DS18B20_1US;DS18B20_3US
#define DS18B20_5US		DS18B20_1US;DS18B20_4US
#define DS18B20_6US		DS18B20_1US;DS18B20_5US
#define DS18B20_7US		DS18B20_1US;DS18B20_6US
#define DS18B20_8US		DS18B20_1US;DS18B20_7US
#define DS18B20_9US		DS18B20_1US;DS18B20_8US
#define DS18B20_10US	DS18B20_1US;DS18B20_9US
#define DS18B20_50US	DS18B20_10US;DS18B20_10US;DS18B20_10US;DS18B20_10US;DS18B20_10US
#define DS18B20_100US	DS18B20_50US;DS18B20_50US
#define DS18B20_500US	DS18B20_100US;DS18B20_100US;DS18B20_100US;DS18B20_100US;DS18B20_100US
#define DS18B20_1000US	DS18B20_500US;DS18B20_500US
//��ȡһ���ֽ�
unsigned char ds18b20_read_byte(void)
{
    unsigned char i, t_data = 0;

    for(i = 0; i < 8; i++)
    {
        DS18B20_PIN = 0; //������ʱ���϶(����ʼ)
        DS18B20_2US;
        DS18B20_PIN = 1; //�ͷ�����
        DS18B20_8US;    //�ȴ�DS18B20���������
        t_data >>= 1;    //��λ��0��Ĭ����0Ϊ׼

        if(DS18B20_PIN) t_data |= 0x80;

        DS18B20_50US;
        DS18B20_10US;
        DS18B20_PIN = 1; //�ͷ�����,�ȴ���ȡ��һλ����
    }

    return t_data;
}
//д��һ���ֽ�
void ds18b20_write_byte(unsigned char cmd)
{
    unsigned char i;

    for(i = 0; i < 8; i++)
    {
        DS18B20_PIN = 0;
        DS18B20_1US;
        DS18B20_PIN = cmd & 0x01; //����ʵ�ʵ�����λ
        DS18B20_50US;
        DS18B20_10US; //�ȴ�д���
        DS18B20_PIN = 1; //�ͷ����ߣ�׼����һ�η���
        cmd >>= 1;
    }
}
//ģ���ʼ�� 1:ģ����� 0��ģ�鲻����
unsigned char ds18b20_init(void)
{
    DS18B20_PIN = 1;
    DS18B20_10US;

    if(ds18b20_read_status())
    {
        return 0;
    }

    return 1;
}
//��ȡ״̬ 1:no 0:ok
unsigned char ds18b20_read_status(void)
{
    unsigned char cnt = 0;
    DS18B20_PIN = 0;
    DS18B20_100US;
    DS18B20_100US;
    DS18B20_100US;
    DS18B20_100US;
    DS18B20_100US;
    DS18B20_100US;
    DS18B20_100US;
    DS18B20_50US;
    DS18B20_PIN = 1;
    DS18B20_10US;
    DS18B20_5US;      //�ȴ�DS18B20��Ӧ

    while(DS18B20_PIN && cnt < 200)
    {
        cnt++;
    }

    if(cnt >= 200) return 1;

    cnt = 0;

    while(!DS18B20_PIN && cnt < 240)
    {
        cnt++;
    }

    if(cnt >= 240) return 1;

    return 0;
}
//��ʼת�� 0������ʧ��	1�������ɹ�
unsigned char ds18b20_conversion_start(void)
{
    if(ds18b20_read_status())
    {
        return 0;
    }

    ds18b20_write_byte(0xCC); //����ROM���м��
    ds18b20_write_byte(0x44); //����һ���¶�ת��
    return 1;
}

//��ȡ�¶�
unsigned short ds18b20_read_temperature(void)
{
    unsigned char temp_H, temp_L, ret;

    ret = ds18b20_init();

    ds18b20_write_byte(0xCC); //����ROM���м��
    ds18b20_write_byte(0x44); //����һ���¶�ת��

    if(ds18b20_read_status())
    {
        return 0;
    }

    ds18b20_write_byte(0xCC); //����ROM���м��
    ds18b20_write_byte(0xBE); //��ȡ�¶�
    temp_L = ds18b20_read_byte(); //��ȡ���¶ȵ�λ����
    temp_H = ds18b20_read_byte(); //��ȡ���¶ȸ�λ����
    return temp_L | (temp_H << 8); //�ϳ��¶�
}

