#include "SEEKFREE_FONT.h"
#include "headfile.h"

#define KEY1    C8
#define KEY2    C9
#define KEY3    B2


//����״̬����
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;


//��һ�ο���״̬����
uint8 key1_last_status;
uint8 key2_last_status;
uint8 key3_last_status;


//���ر�־λ
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




    //ʹ�ô˷����ŵ����ڣ�����Ҫʹ��while(1) �ȴ������⴦������Դ�˷�
    //���水��״̬
    key1_last_status = key1_status;
    key2_last_status = key2_status;
    key3_last_status = key3_status;

    //��ȡ��ǰ����״̬
    key1_status = gpio_get(KEY1);
    key2_status = gpio_get(KEY2);
    key3_status = gpio_get(KEY3);


    //��⵽��������֮��  ���ſ���λ��־λ
    if(key1_status && !key1_last_status)    key1_flag = 1;
    if(key2_status && !key2_last_status)    key2_flag = 1;
    if(key3_status && !key3_last_status)    key3_flag = 1;


    //��־λ��λ֮�󣬿���ʹ�ñ�־λִ���Լ���Ҫ�����¼�
    if(key1_flag)
    {
        key1_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
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
        key2_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
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
        key3_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
        if(test3==0)
        {
            test3=1;
        }
        else
        {
            test3=0;
        }
    }

    //��TFT����ʾ���Ա���
    //ips114_showstr(0,2,"+:0 -:1");  ips114_showint16(12*8,2,slave_position);
    ips114_showstr(0,3,"che:");  ips114_showfloat(12*8,3,test1,2,3);
       ips114_showstr(0,4,"zhuan:");  ips114_showfloat(12*8,4,test2,2,3);
       ips114_showstr(0,5,"zf:");  ips114_showfloat(12*8,5,test3,2,3);
    systick_delay_ms(10);//��ʱ����������Ӧ�ñ�֤����ʱ�䲻С��10ms

    }
