#ifndef	DIGITAL_TUBE_H
#define DIGITAL_TUBE_H
#include <REGX52.H>
//�ɹ���ʾ���ַ�
#define PEN_CODE_LEN		18
//�м�λ�����
#define	DSPLAY_INDEX_LEN	4

//0:����	1:����
#define DIGITAL_TUBE_TYPE	1
#if DIGITAL_TUBE_TYPE
void move_display_num_CA(unsigned char num, unsigned char index ,unsigned char point_flag);
#else
void move_display_num_CC(unsigned char num, unsigned char index ,unsigned char point_flag);
#endif
#endif