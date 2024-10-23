#ifndef _FANGXIANG_H_
#define _FANGXIANG_H_
#include"common.h"
extern float Turn_Speed;
extern float Turn_Out;
extern float pid_err_pre;

typedef struct{
    uint8 Motor_Flag;
    uint8 Speed_flag;//�ٶȻ�����
    uint8 tran_flag;
    uint8 Turn_flag;
    uint8 Forward_modle;//����ģʽ
    uint8 Turn_Mode;
    uint8 rboot;//�����ǳ�ʼ����־
    uint8 rboot1;
    uint8 BXflag;
    uint8 Steer;
    uint8 PARK;
    uint8 out;
}Flag_S;
//typedef enum{
//    roadcondition_ImageWay=0,//��ͨ·��
//    roadcondition_BreakWay,//��·
//    roadcondition_Cir,//Բ��
//    roadcondition_Cross,//ʮ��
//    roadcondition_UpWay,//�µ�
//}__roadcondition;

typedef struct{
//    float slowdown_flag;//����

//    __roadcondition roadcondition;//��·״̬
//    int16_t HisTurnOut[3];//��ʷ���ε�ת��ֵ
//    int16_t TurnCamera_Avr; //��ʷ����ת��ֵƽ��ֵ
    int16 TurnOut;
    int8 Turn_Cammera;           //����ͷת��ƫ��
    float slowdown_flagR;
    float slowdown_flagL;
    float slowdown;
}State_S;
extern  uint8 Turn_Mode;
extern Flag_S Flag_User;
extern State_S State;
extern uint8 Fres; // ǰհ
extern float Turn_Can_PWM;
extern float Turn_PWM;
void Speed_Control(void);
void Falg(void);
void slow(void);
void Direction_Control(void);

#endif
