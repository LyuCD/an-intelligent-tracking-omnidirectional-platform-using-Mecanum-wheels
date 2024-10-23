#ifndef __PID_H
#define __PID_H

#include "common.h"

typedef struct
{
    float err;
    float last_err;
    float last_last_err;
    float kp,ki,kd;
    float result;
}_pid_t;

extern _pid_t pid_left_front;     /*�ṹ�� ��ǰ��PID����*/
extern _pid_t pid_right_front;      /*�ṹ�� ��ǰ��PID����*/
extern _pid_t pid_left_rear;            /*�ṹ�� �����PID����*/
extern _pid_t pid_right_rear;           /*�ṹ�� �Һ���PID����*/


void Pid_Config_Init(void);

void PID_Control(_pid_t *pid, int16 actual, int16 set);

#define KP 0
#define KI 1
#define KD 2
#define KT 3
typedef struct{
    float Kp;
    float Ki;
    float Kd;
    int16 LastErr;
    int16 PastErr;   //���ϴ����
    int16 LastOut;   //�ϴ����
    float SumError;   //������
    float SumErrorMax; //����޷�
}PID_S;

void PID_Init(PID_S *sptr);
void PID_Init_All(void);
int16 LimitProtect(int16 max,int16 min,int16 data);
void PID_Set(void);
int16 PositPID(PID_S *User,float NowDat,int16 SetDat);
int16 PlacePID_Control(PID_S*User,float *PID,int16 NowDat,int16 SetDat);  //λ��ʽ��̬PID
int16 IncrementPID(PID_S *User,int16 Nowdat,int16 Setdat);
extern PID_S SpeedAL_PID,SpeedAR_PID,SpeedBL_PID,SpeedBR_PID
             ,Gyro_PID
             ,TurnCamer_PIDS
             ,TurnCamer_PIDH
             ,TurnCamer_park
             ,Turn_PID
             ,BX_PWM
             ,B_PWM;
extern float Turn[2][3];
extern int16 SpeedGet;

#endif
