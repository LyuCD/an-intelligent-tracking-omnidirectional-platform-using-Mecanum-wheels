#include "Recognition.h"

uint8 ramp_wide = 0;
uint8 ramp_dec = 0;
uint8 ramp_wide_keep = 0;   //坡道判断宽度

uint8 round_out = 0;    //环岛出环标记,用以消除
uint8 round_in = 0;     //环岛入环标记
uint8 round_use = 0;    //环岛有效标记
uint8 sta_mark = 0;     //终点标记
uint8 sta_in = 0;       //终点入库标记
uint8 sta_end=0;
uint8 sta_begain = 0;   //出库标记
uint8 ramp = 0;

uint8 sta_begain_lock = 0;  //出库锁，为一时出库成功
uint8 sta_in_lock = 0;

int sta_mark_delay = 0;     //终点滤除标记
int round_in_delay = 0;     //环岛出环滤除标记
int round_out_delay = 0;        //环岛入环滤除标记
int round_use_delay = 0;
int sta_begain_delay = 0;

uint8 delay_mark(uint8(*p)[COL], uint8(*side_line)[col])
{

    //sta_begain= 1;
    //sta_in_lock = 1;


    uint8 i, j;
    //延迟触发解锁,sta_begain_lock为一结束

    if(sta_end)
    {
        angular_c=0;
        return 33;
    }


    if (sta_begain == 0)
    {
        sta_begain_delay = Sta_begain_delay;
        binarization(p);
        line_hunting(p, side_line);
        for (i = row - 2; side_line[i][1] != 2 && i; i--);
        for (j = row - 2; side_line[i][row - 2] != 2 && j; j--);

        if (i < StaBmax && j < StaBmax)
        {
            sta_begain = 1;
            return 35;
        }
        else
        {
            angular_c = 0;
            return 35;
        }
    }
    else
    {
         ips114_showstr(0,5,"sta_begain_delay");
          ips114_showint16(8*13,5,sta_begain_delay);
        if (sta_begain_delay)
            sta_begain_delay--;
    }
    //出发后两形态，第一阶段为继续运行，保持一定的继续运行，防止终点干扰；第二阶段延迟后入库；触发条件为出现sta_mark有效

    if (sta_mark)
    {
        if (sta_in_lock == 0)
        {
            sta_mark_delay--;
            if (sta_mark_delay < 0)
            {
                sta_mark_delay = Sta_mark_delay;
                angular_c = End_angular;
                return 88;
            }
            else
                if (sta_mark_delay == 0)
                {
                    sta_in_lock = 1;
                    sta_mark_delay = 0;
                    sta_mark = 0;
                }
            uint8 ds=0;
            ds=destination(side_line, p, 2);
            if(ds)
            {
                angular_c = 0;
                return 36;
            }
            else
            {
                ds=destination(side_line, p,4);
                if(ds)
                {
                    angular_c = 0;
                    return 36;
                }
            }

            lose_test(side_line);
            return 36;

        }
        else
        {
            sta_mark_delay--;
            if (sta_mark_delay < 0)
            {
                sta_mark_delay = Sta_in_delay;
            }
            else
                if (sta_mark_delay == 0)
                {
                    sta_mark = 0;
                    sta_in = 1;
                    sta_mark_delay = 0;
                }
                else
                {
                    angular_c = 0;
                    return 37;
                }
        }
    }

    //round_out触发
    if (round_out_delay && round_out == 0)
    {
        round_out_delay--;
        if (round_out_delay == 0)
        {
            round_out = 1;
            round_out_delay = Round_out_delay;
        }
    }
    //round_out消除
    if (round_out)
    {
        round_out_delay--;
        if (round_out_delay == 0)
            round_out = 0;
    }

    //round_in触发
    if (round_in_delay && round_in == 0)
    {
        round_in_delay--;
        if (round_in_delay == 0)
        {
            round_in = 1;
        }
    }
    //round_in消除
    if (round_out)
    {
        round_in = 0;
    }
    return 0;
}

