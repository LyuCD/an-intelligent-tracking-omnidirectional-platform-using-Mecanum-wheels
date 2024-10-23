#include"headfile.h"
//编码器初始化函数
int16 Encoder_A,Encoder_B,Encoder_C,Encoder_D;//左前速度，右前轮速度，左后轮速度，右后轮速度

void Qtimer_Init(void)
{
    timer_quad_init(TIMER_2, TIMER2_CHA_A15, TIMER2_CHB_B3);
    timer_quad_init(TIMER_3, TIMER3_CHA_B4, TIMER3_CHB_B5);
}
//速度采集函数需放在定时器内运行
//编码器A读数函数
void QtimerC_read (void)
{
     Encoder_C=timer_quad_get(TIMER_2);
    timer_quad_clear(TIMER_2);
}
//编码器B读数函数
void QtimerD_read (void)
{
    Encoder_D=timer_quad_get(TIMER_3);
    timer_quad_clear(TIMER_3);
}
void QtimerA_read (void)
{
     Encoder_A=slave_encoder_left;;

}
//编码器B读数函数
void QtimerB_read (void)
{
    Encoder_B=slave_encoder_right;

}
