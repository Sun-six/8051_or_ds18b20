#include "delay.h"

//void delay_us(unsigned long count)
//{
////    unsigned long timer_count;
////    //��ʱ����ֵ����
////    timer_count = count;
////	//��ʼ����ʱ��0
////	TMOD = 0x01;          //ʹ�ö�ʱ��T0��ģʽ1
////	TF0 = 0;

////	while(timer_count)
////	{
////		unsigned long temp_count = timer_count>65536?65536:timer_count;
////		TH0 = (65536 - temp_count) / 256; //��ʱ��T0�ĸ�8λ����ֵ
////		TL0 = (65536 - temp_count) % 256; //��ʱ��T0�ĵ�8λ����ֵ
////		TR0 = 1;              //������ʱ��T0
////		//�ȴ���ʱ������
////		while(TF0 == 0);
////		TF0 = 0;
////		timer_count -= temp_count;
////	}
////		#pragma asm
////	RET_DELAY:
////		DJNZ	R7,$;
////		DJNZ	R6,$;
////		DJNZ	R5,$;
////		DJNZ	R4,$;
////		RET
////		#pragma endasm
//}
//��ʱn����
void delay_ms(unsigned long n)
{
    unsigned long i=0,j=0;
    for(i=0;i<n;i++)
        for(j=0;j<2;j++);
}