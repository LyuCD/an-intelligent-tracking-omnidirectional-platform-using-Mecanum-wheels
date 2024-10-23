#include "Recognition.h"

uint8 mid_max;			//������ߵ�
uint8 side_max;			//������ߵ�
uint8 right_b = 2;		//������ʼ��					(��һ�б�����Ч����������ߵ㣬���ӵڶ���Ϊ��ʼ��)
uint8 left_b = 2;		//������ʼ��
uint8 piancha=0;
float angular_c = 0;	//ת��

void Image_Seek(uint8(*image)[COL], uint8(*side_line)[col], uint8* mide_line)
{
    uint8 hunt_mark = 0;
    uint8 ds = 0;

    //uart_putstr(UART_1, (uint8 *)"000 ");

    //systick_delay_ms(1);
    //��ʱ�˳�����
    ds = delay_mark(image, side_line);
    if (ds)
    {
        flip(image, side_line, mide_line);
        piancha = ds;
    }
    else
    {
        binarization(image);
        hunt_mark = line_hunting(image, side_line);
        if (hunt_mark == 0)                     //Ѱ��ʧ�ܣ�����֮ǰ��ƫ����
        {
            flip(image, side_line, mide_line);
            piancha = 66;
        }
        else
        {
            //���
            if (sta_in)
            {
                ds = comestorages(side_line);
                flip(image, side_line, mide_line);
                piancha = 30 + ds;
            }
            else
                {
                    ds = destination(side_line, image, A_des - 1);
                    if (ds)
                    {
                        sta_mark = 1;
                        flip(image, side_line, mide_line);
                        piancha = 30 + ds;
                    }
                    else
                    {
                        ds = destination(side_line, image, A_des);
                        if (ds)
                        {
                            sta_mark = 1;
                            flip(image, side_line, mide_line);
                            piancha = 30 + ds;
                        }
                        else
                        {
                            ds = destination(side_line, image, A_des + 1);
                            if (ds)
                            {
                                sta_mark = 1;
                                flip(image, side_line, mide_line);
                                piancha = 30 + ds;
                            }
                        }
                    }
                }
        }
    }
}

void Image_Seeks(uint8(*image)[COL], uint8(*side_line)[col], uint8* mide_line)
{

   // round_out=1;
    int8 lose_mark;                             //��ʧ���
    uint8 el = 0;
    lose_mark = lose_test(side_line);
    if (Round_D == -1)
    {
        if (round_in && lose_mark == 3 && !round_out_delay)
        {
            angular_c = Round_angular_s;
        }
    }
    else
    {
        if (round_in && lose_mark == 2 && !round_out_delay)
        {
            angular_c = Round_angular_s;
        }
    }

    if (sta_begain_delay && lose_mark == 2)
    {
        angular_c = Begain_angular;
    }
    else
    {
        //uart_putstr(UART_1, (uint8 *)"6 ");
        //cout << "lose_mark=" << lose_mark << endl;
        //�Զ�ʧ�����б����з���92Ϊδ��ʧ�������迼��

        if (lose_mark)
        {
            flip(image, side_line, mide_line);
            piancha = 10 + lose_mark;
        }
        else
        {
            //һ���������������к�������

            //uart_putstr(UART_1, (uint8 *)"6 ");
            el = element_seeks(side_line, image, mide_line);
            //uart_putstr(UART_1, (uint8 *)"7 ");

            if (el!=4)
            {
                flip(image, side_line, mide_line);
                piancha = el + 20;
            }
            else
            {
                    //cout << "ƫ�������" << endl;
                    el = mid_value(mide_line, side_line);
                    piancha=el;
                    flip(image, side_line, mide_line);
            }
        }
    }
}
