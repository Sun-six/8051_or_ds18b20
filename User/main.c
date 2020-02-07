#include <REGX52.H>
#include "delay.h"
#include "digital_tube.h"
#include "ds18b20.h"
void main(void)
{
    unsigned char i,ds18b20_status,temperature_data[4] = {0,0,0,0};
	unsigned short temperature_data_math;
	unsigned long count=0;
	ds18b20_status = ds18b20_init();
	for(i = 0;i < 4; i++)
	{
		temperature_data[i] = ds18b20_status?ds18b20_status:16;
	}
    while(1)
    {
        unsigned char i;
		//��ʾˢ��
		if(ds18b20_status && !(count%20))//count���ƶ�ȡ���,����count>30����������Ч������
		{
			ds18b20_conversion_start();
			ds18b20_read_status();
			temperature_data_math = ds18b20_read_temperature();
			if(temperature_data_math != 0x550 || count>=300)//��֤��һ����ʾ�ľ�Ϊ��Ч����
			{
				//���ݴ���
				temperature_data[0] = (temperature_data_math&0xf000)?16:17;//����λ��ʾ
				if(temperature_data[0] == 16)//����
				{
					temperature_data_math = (~temperature_data_math)+1;
				}
				temperature_data[1]=((temperature_data_math>>4)/10)>10?9:((temperature_data_math>>4)/10);//Խ�紦��
				temperature_data[2]=((temperature_data_math>>4)%10)>10?9:((temperature_data_math>>4)%10);//Խ�紦��
#if	0			
				//�ֲڴ���
				temperature_data[3]=((temperature_data_math&0xf)*10)/16;//С��λ����
#else
				//�������봦��
				temperature_data[3]=((temperature_data_math&0xf)*10)%16>8?((temperature_data_math&0xf)*10)/16+1:((temperature_data_math&0xf)*10)/16;//С��λ����
#endif
			}
		}
        for(i = 0; i < 4; i++)//��̬��ʾ����
        {
            move_display_num_CA(temperature_data[i], i ,i==2?1:0);
			delay_ms(10);
        }
		count++;
    }

}