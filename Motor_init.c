#include"headfile.h"


//电机初始化函数
void Motor_Init(void)
{

    gpio_init(C10, GPO, 0, GPIO_PIN_CONFIG);
    pwm_init(PWM4_CH1_B6, 10*1000, 0);

    gpio_init(C11, GPO, 0, GPIO_PIN_CONFIG);
    pwm_init(PWM4_CH2_B7, 10*1000, 0);

    gpio_init(B12, GPO, 0, GPIO_PIN_CONFIG);
    pwm_init(PWM4_CH3_B8, 10*1000, 0);

    gpio_init(A8, GPO, 0, GPIO_PIN_CONFIG);
    pwm_init(PWM4_CH4_B9, 10*1000, 0);

}
/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：PWM
返回  值：无
**************************************************************************/
//电机控制函数
void Set_Pwm(int motor_a,int motor_b,int motor_c,int motor_d)
{
    if(motor_a>=0)
    {
        gpio_set(C10,0);
        pwm_duty(PWM4_CH1_B6,motor_a);
    }
    else
    {
        gpio_set(C10,1);
        pwm_duty(PWM4_CH1_B6,-motor_a);
    }

    if(motor_b>=0)
    {
        gpio_set(C11,0);
        pwm_duty(PWM4_CH2_B7,motor_b);
    }
    else
    {
        gpio_set(C11,1);
        pwm_duty(PWM4_CH2_B7,-motor_b);
    }

    if(motor_c>=0)
    {
        gpio_set(A8,0);
        pwm_duty(PWM4_CH3_B8,motor_c);
    }
    else
    {
        gpio_set(A8,1);
        pwm_duty(PWM4_CH3_B8,-motor_c);
    }

    if(motor_d>=0)
    {
        gpio_set(B12,0);
        pwm_duty(PWM4_CH4_B9,motor_d);
    }
    else
    {
        gpio_set(B12,1);
        pwm_duty(PWM4_CH4_B9,-motor_d);
    }
}





