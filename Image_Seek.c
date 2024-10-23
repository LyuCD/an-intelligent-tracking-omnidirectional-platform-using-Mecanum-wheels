#include "Recognition.h"

uint8 mid_max;			//中线最高点
uint8 side_max;			//边线最高点
uint8 right_b = 2;		//右线起始点					(第一行边线无效，不存在最边点，即从第二行为起始点)
uint8 left_b = 2;		//左线起始点
uint8 piancha=0;
float angular_c = 0;	//转角

void Image_Seek(uint8(*image)[COL], uint8(*side_line)[col], uint8* mide_line)
{
    uint8 hunt_mark = 0;
    uint8 ds = 0;

    //uart_putstr(UART_1, (uint8 *)"000 ");

    //systick_delay_ms(1);
    //延时滤除部分
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
        if (hunt_mark == 0)                     //寻线失败，返回之前的偏移量
        {
            flip(image, side_line, mide_line);
            piancha = 66;
        }
        else
        {
            //入库
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
    int8 lose_mark;                             //丢失标记
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
        //对丢失进行判别，其中返回92为未丢失，即不予考虑

        if (lose_mark)
        {
            flip(image, side_line, mide_line);
            piancha = 10 + lose_mark;
        }
        else
        {
            //一切正常，继续进行后续处理

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
                    //cout << "偏移量检测" << endl;
                    el = mid_value(mide_line, side_line);
                    piancha=el;
                    flip(image, side_line, mide_line);
            }
        }
    }
}
