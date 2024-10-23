#include "math.h"
#include"common.h"
#include"headfile.h"


#define PI  3.1415926       //圆周率

#define ROW MT9V03X_H
#define COL MT9V03X_W

#define row ROW/2               //逻辑图片行数(增加宽度为2的外框)
#define col COL/2               //逻辑图片列数

#define Grey_Max    250     //最高灰度


#define Round_D     -1      //左环为-1，右环为1
#define Sta_BD      -1     //左出库为-1，右出库为1
#define Sta_ED      -1      //左入库为-1，右入库为1


#define Round_in_delay  50 //环岛入环延时滤除
#define Round_out_delay 100 //环岛出环延时滤除
#define Round_use_delay 20
#define Sta_mark_delay  8 //终点延时滤除
#define Sta_in_delay    2  //终点入库延迟
#define Sta_begain_delay    20   //出库延时

#define Round_in_unuse_delay    20   //入环无效延迟，用以消除过环跳变入环问题
#define Round_out_use_delay     30  //入环转出库延迟，入库后一定时间后输出出库
#define End_lock_delay  1000


#define Begain_angular      20*Sta_BD     //出库固定角
#define Round_angular       20*Round_D    //出环固定角
#define Round_angular_s     10*Round_D    //入环预判角
#define Round_in_angular    20*Round_D    //入环丢失固定角
#define Round_out_angular   -10*Round_D    //出环修正角
#define End_angular         -5*Sta_ED    //车库防入角
#define END_angulars        20*Sta_ED
#define END_angularss       20*Sta_ED


#define MN          4       //中点闭环最小数量

#define Mid_Deal    2       //中线接受的拟合摆动宽度
#define RLS     8           //左右边线反向摇摆最大置信宽度
#define RLS_M   2           //反圆环摇摆宽度
#define MLS     2           //中线摇摆最大宽度（多用于处理不合理跳变）
#define Lose_dec    5

#define Stasway 2       //入库边线跳变最大可信值
#define Stacode 4       //入库检测方框
#define StaEmax 8       //入库结束时要求的最低点，过此后停车
#define Staside 3       //入库阶段二边线确定条件，出现低于该数值的边线有效点，视为无效
#define Staes1  1       //入库阶段一放大倍数
#define Staes2  0.8       //入库阶段二放大倍数
#define Stasw   1       //入库阶段二两边线线摆
#define Stajp   3       //入库跳变最大值
#define StaImax 15      //入库阶段一最高触发条件
#define StaAmax 15      //入库阶段二最高拟合角度
#define StaBmax 16       //出库最高触发点

#define RJW     5           //环岛判断宽度，以此拟合
#define RJA     60          //环岛判断角度（角度值）

#define ITJ     5           //三岔路口判断长度，角点上寻行数
#define RATJ    100         //三岔路口最大点数，理论上不超过ITJ的四倍
#define TriW    15          //三岔口判断边宽
#define TriMH   15          //三岔口低点最高触发高度

#define TriA_max 170        //三岔口最大角度
#define TriA_min 90        //三岔口最小角度

#define Round_in_judge  1   //环岛入环判断
#define Round_A_max 160     //环岛入环角点最大角度
#define Round_A_min 60      //环岛入环角点最小角度

#define Round_m     2       //环岛判断最大置信点数

#define Mid_Shake   2       //中线抖动检查宽度


#define A_max   15
#define A_min   10
#define A_wide_max 12
#define A_wide_min  2

#define Ra_Max  400       //边点最大值


#define Lose_k  2           //边线丢失判断的k最大值
#define Side_Sway   3       //边线最高点与最高点的致信宽度
#define High_Sway   2       //出环问题顶线摇摆最大值
#define High_n      10       //顶线判断置信点最大数
#define High_b      1       //顶线最高点
#define Mid_Side_DM 2       //中线最高点和边线最高点最大距离

#define RU_min      1
#define A_des       8       //终点前瞻，理论最小为2
#define D_mark      8       //终点最小判断数

#define ES      1       //丢失倍数

#define Round_pass  7   //环岛过环判断最低点数

#define Rh_max  65
#define Rh_min  50





#define int8    char

extern uint8 threshold;

extern uint8 mid_max;
extern uint8 side_max;
extern uint8 right_b;
extern uint8 left_b;
extern float angular_c;
extern uint8 piancha;

extern uint8 round_in;
extern uint8 round_out;
extern uint8 round_use;
extern uint8 sta_mark;
extern uint8 sta_in;
extern uint8 sta_begain;
extern uint8 sta_end;

extern uint8 sta_begain_lock;
extern uint8 sta_in_lock;

extern int sta_mark_delay;
extern int round_in_delay;
extern int round_out_delay;
extern int round_use_delay;
extern int sta_begain_delay;

void binarization(uint8(*p)[COL]);                                                                      //初始化：输入图片数组，输出已处理的二值化缩小图片
void supplement(uint8(*side_line)[col], uint8 a, uint8 b, uint8 c, uint8 d);                            //补线函数:（side_line,row,col,row,col)
void supplements(uint8(*side_line)[col], uint8 a, uint8 b, uint8 c, uint8 d);
void supplement_m(uint8(*side_line)[col], uint8* mid_line, uint8 a1, uint8 b1, uint8 a2, uint8 b2);     //中线补线
void point_show(uint8(*side_line)[col], uint8 a, uint8 b);                                              //边点显示函数
void flip(uint8(*p)[COL], uint8(*side_line)[col], uint8* mid_line);                                     //写入、恢复图片
int8 mid_value(uint8* mid_line, uint8(*side_line)[col]);                                                //偏移量：面积加权法
uint8 line_sway(uint8(*side_line)[col], uint8 a1, uint8 b1, uint8 a2, uint8 b2, uint8 sw);              //线摆函数，输出超出sw的线点数

uint8 nighbor_judge(uint8(*p)[COL], uint8(*line)[col], uint8 a, uint8 b, uint8 n);                      //邻域判定（逻辑图片，边线，行坐标，列坐标,标记序号:边线标记2，环岛标记5）

void mid_seek(uint8(*side_line)[col], uint8* mid_line, uint8* r_line, uint8* l_line);                   //中线探寻，基于给出的初始点一行中点
void mid_seeks(uint8(*side_line)[col], uint8* mid_line);                                                //中线探寻重载

uint8 destination(uint8(*side_line)[col], uint8(*p)[COL], uint8 A);                          //终点探寻

uint8 comestorages(uint8(*side_line)[col]);                                     //入库,错误输出0，阶段一输出1，阶段2输出2，停车输出3

uint8 delay_mark(uint8(*p)[COL], uint8(*side_line)[col]);                                                               //标志位

int8 lose_test(uint8(*side_line)[col]);                                         //错误输出0，全边点输出1，右丢失输出2，左丢失输出3，
uint8 line_hunting(uint8(*p)[COL], uint8(*side_line)[col]);                         //八邻域法边界寻线,失败返回0，成功返回中点值，并且进行边线最高点和左右线起始点的计算
uint8 element_seeks(uint8(*side_line)[col], uint8(*p)[COL], uint8* mid_line);       //元素判定,错误输出0，环岛入环丢失输出1，入环补线输出2，，十字路口3一切正常输出4

void Image_Seeks(uint8(*image)[COL], uint8(*side_line)[col], uint8* mide_line);
void Image_Seek(uint8(*image)[COL], uint8(*side_line)[col], uint8* mide_line);
/*
测试函数，输出元素类型，
错误输出0，一切正常输出1;
全边点输出11，右丢失输出12，左丢失输出13，三岔口为14，环岛出环为15；
环岛入环输出21，环岛补线输出22，十字路口23，一切正常输出24,过库识别补线输出6
终点入库阶段一输出31，阶段二输出32，停车输出33，错误输出30
 */


