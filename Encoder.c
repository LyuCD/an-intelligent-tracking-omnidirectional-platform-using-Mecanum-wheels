#include"headfile.h"
//��������ʼ������
int16 Encoder_A,Encoder_B,Encoder_C,Encoder_D;//��ǰ�ٶȣ���ǰ���ٶȣ�������ٶȣ��Һ����ٶ�

void Qtimer_Init(void)
{
    timer_quad_init(TIMER_2, TIMER2_CHA_A15, TIMER2_CHB_B3);
    timer_quad_init(TIMER_3, TIMER3_CHA_B4, TIMER3_CHB_B5);
}
//�ٶȲɼ���������ڶ�ʱ��������
//������A��������
void QtimerC_read (void)
{
     Encoder_C=timer_quad_get(TIMER_2);
    timer_quad_clear(TIMER_2);
}
//������B��������
void QtimerD_read (void)
{
    Encoder_D=timer_quad_get(TIMER_3);
    timer_quad_clear(TIMER_3);
}
void QtimerA_read (void)
{
     Encoder_A=slave_encoder_left;;

}
//������B��������
void QtimerB_read (void)
{
    Encoder_B=slave_encoder_right;

}
