#include "SEEKFREE_FONT.h"
#include "headfile.h"

#define KEY1    C8
#define KEY2    C9
#define KEY3    B2


//开关状态变量
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;


//上一次开关状态变量
uint8 key1_last_status;
uint8 key2_last_status;
uint8 key3_last_status;


//开关标志位
uint8 key1_flag;
uint8 key2_flag;
uint8 key3_flag;


float test1=-1.85;
float test2=-0.08;
float test3;
float test4;

void key_init(void)
{

    gpio_init(KEY1, GPI, 0, GPIO_INT_CONFIG);
    gpio_init(KEY2, GPI, 0, GPIO_INT_CONFIG);
    gpio_init(KEY3, GPI, 0, GPIO_INT_CONFIG);
}
void key(void)
{




    //使用此方法优点在于，不需要使用while(1) 等待，避免处理器资源浪费
    //保存按键状态
    key1_last_status = key1_status;
    key2_last_status = key2_status;
    key3_last_status = key3_status;

    //读取当前按键状态
    key1_status = gpio_get(KEY1);
    key2_status = gpio_get(KEY2);
    key3_status = gpio_get(KEY3);


    //检测到按键按下之后  并放开置位标志位
    if(key1_status && !key1_last_status)    key1_flag = 1;
    if(key2_status && !key2_last_status)    key2_flag = 1;
    if(key3_status && !key3_last_status)    key3_flag = 1;


    //标志位置位之后，可以使用标志位执行自己想要做的事件
    if(key1_flag)
    {
        key1_flag = 0;//使用按键之后，应该清除标志位
        if(test3==0)
        {
            test1+=0.01;
        }
        else
        {
            test1-=0.01;
        }
    }

    if(key2_flag)
    {
        key2_flag = 0;//使用按键之后，应该清除标志位
        if(test3==0)
        {
            test2+=0.01;
        }
        else
        {
            test2-=0.01;
        }
    }

    if(key3_flag)
    {
        key3_flag = 0;//使用按键之后，应该清除标志位
        if(test3==0)
        {
            test3=1;
        }
        else
        {
            test3=0;
        }
    }

    //在TFT上显示测试变量
    //ips114_showstr(0,2,"+:0 -:1");  ips114_showint16(12*8,2,slave_position);
    ips114_showstr(0,3,"che:");  ips114_showfloat(12*8,3,test1,2,3);
       ips114_showstr(0,4,"zhuan:");  ips114_showfloat(12*8,4,test2,2,3);
       ips114_showstr(0,5,"zf:");  ips114_showfloat(12*8,5,test3,2,3);
    systick_delay_ms(10);//延时，按键程序应该保证调用时间不小于10ms

    }
