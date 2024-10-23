#ifndef _FANGXIANG_H_
#define _FANGXIANG_H_
#include"common.h"
extern float Turn_Speed;
extern float Turn_Out;
extern float pid_err_pre;

typedef struct{
    uint8 Motor_Flag;
    uint8 Speed_flag;//速度环控制
    uint8 tran_flag;
    uint8 Turn_flag;
    uint8 Forward_modle;//运行模式
    uint8 Turn_Mode;
    uint8 rboot;//陀螺仪初始化标志
    uint8 rboot1;
    uint8 BXflag;
    uint8 Steer;
    uint8 PARK;
    uint8 out;
}Flag_S;
//typedef enum{
//    roadcondition_ImageWay=0,//普通路段
//    roadcondition_BreakWay,//断路
//    roadcondition_Cir,//圆环
//    roadcondition_Cross,//十字
//    roadcondition_UpWay,//坡道
//}__roadcondition;

typedef struct{
//    float slowdown_flag;//减速

//    __roadcondition roadcondition;//道路状态
//    int16_t HisTurnOut[3];//历史三次的转向值
//    int16_t TurnCamera_Avr; //历史三次转向值平均值
    int16 TurnOut;
    int8 Turn_Cammera;           //摄像头转向偏差
    float slowdown_flagR;
    float slowdown_flagL;
    float slowdown;
}State_S;
extern  uint8 Turn_Mode;
extern Flag_S Flag_User;
extern State_S State;
extern uint8 Fres; // 前瞻
extern float Turn_Can_PWM;
extern float Turn_PWM;
void Speed_Control(void);
void Falg(void);
void slow(void);
void Direction_Control(void);

#endif
