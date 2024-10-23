#include "headfile.h"

_pid_t pid_left_front;     /*结构体 左前轮PID参数*/
_pid_t pid_right_front;     /*结构体 右前轮PID参数*/
_pid_t pid_left_rear;           /*结构体 左后轮PID参数*/
_pid_t pid_right_rear;          /*结构体 右后轮PID参数*/

uint8 basic_speed;
uint8 Rotate_speed;

//float KP = 0;
//float KD = 0;

float P = 90;//90;
float I = 22;//22;
float D = 30;//30;

/*pid初始化*/
void Pid_Config_Init(void)
{
    basic_speed = 50;
    Rotate_speed = 120;

    pid_left_front.kp=140;//150
        pid_left_front.ki=5;//5
        pid_left_front.kd=15;//15

        pid_right_front.kp=140;
        pid_right_front.ki=5;
        pid_right_front.kd=15;

        pid_left_rear.kp=140;
        pid_left_rear.ki=5;
        pid_left_rear.kd=15;

        pid_right_rear.kp=140;
        pid_right_rear.ki=5;
        pid_right_rear.kd=15;

    pid_left_front.err=0;
    pid_left_front.last_err=0;
    pid_left_front.last_last_err=0;
    pid_left_front.result=0;

    pid_right_front.err=0;
    pid_right_front.last_err=0;
    pid_right_front.last_last_err=0;
    pid_right_front.result=0;


    pid_left_rear.err=0;
    pid_left_rear.last_err=0;
    pid_left_rear.last_last_err=0;
    pid_left_rear.result=0;

    pid_right_rear.err=0;
    pid_right_rear.last_err=0;
    pid_right_rear.last_last_err=0;
    pid_right_rear.result=0;

}

void PID_Control(_pid_t *pid, int16 actual, int16 set)
{
    float p = 0, i = 0, d = 0;
    pid->err = set - actual;

    p = pid->kp * pid->err;
   i = pid->ki * (pid->err - pid->last_err);
  d = pid->kd * ((pid->err - pid->last_err) - pid->last_last_err);

  pid->last_last_err = pid->err - pid->last_err;
        pid->last_err = pid->err;

        pid->result = p + i + d;


    if(pid->result>9000)
        pid->result = 9000;
    else if(pid->result<-9000)
        pid->result = -9000;
    pid->last_last_err = pid->last_err;
    pid->last_err = pid->err;
}
int16 SpeedGet;
float Turn[2][3] = {{-100, -21,-21},   // 130  // 转向外环动态PID    中线法
                        {-100, -15, -15},
//                    {100, 8, 8, 400},
//                    {100, 9, 9, 400},
//                    {100, 10, 10, 400}
};

PID_S SpeedAL_PID,SpeedAR_PID,SpeedBL_PID,SpeedBR_PID
      ,Gyro_PID
      ,TurnCamer_PIDS
      ,TurnCamer_PIDH
      ,TurnCamer_park
      ,Turn_PID
      ,BX_PWM
      ,B_PWM;

void PID_Init(PID_S *sptr)
{
    sptr->Kd=0;
    sptr->Ki=0;
    sptr->Kp=0;
    sptr->LastErr=0;
    sptr->LastOut=0;
    sptr->PastErr=0;
    sptr->SumError=0;
    sptr->SumErrorMax=0;
}
void PID_Init_All(void)
{
    PID_Init(&SpeedAL_PID);
}
/*-----------------------------------------------------------------*/
//PID（比例（proportion）、积分（integral）、微分（differential））
//p影响速度，过小反应慢，过大，高频震荡
//i加大消除静差
//d抑制震荡
//位置式动态PID
int16 PlacePID_Control(PID_S*User,float *PID,int16 NowDat,int16 SetDat)
{
    int16 NowError;
    int16 OutPut;
    float Kp;
    float Kd;
    NowError=NowDat-SetDat;
    User->SumError+=NowError*0.01;
    if(User->SumError>=User->SumErrorMax)
    {User->SumError=User->SumErrorMax;}
    else if(User->SumError<=-User->SumErrorMax)
    {User->SumError=-User->SumErrorMax;}
    Kp=1.0*(NowError*NowError)/PID[KP]+PID[KI];//P值与差值成二次函数关系，此处P和I不是PID参数，而是动态PID参数，要注意！！！
    Kd=1.0*(NowError*NowError)/PID[KP]+PID[KD];
    OutPut=0.1f*(Kp*NowError+Kd*((0.8*NowError+0.2*User->LastErr)-User->LastErr));//只用PD
    User->LastErr=NowError;
    return OutPut;
}
//位置式PID
int16 PositPID(PID_S *User,float NowDat,int16 SetDat)
{
    //定义为寄存器变量，只能用于整型和字符型变量，提高运算速度
    int16 NowError;
    int16 OutPut;
    NowError=NowDat-SetDat;
    User->SumError+=NowError;  //误差积分
    if(User->SumError>=User->SumErrorMax)
    {User->SumError=User->SumErrorMax;}
    else if(User->SumError<=-User->SumErrorMax)
    {User->SumError=-User->SumErrorMax;}
    OutPut=User->Kp*NowError
            +User->Ki*User->SumError
            +User->Kd*(NowError-User->LastErr);
    User->PastErr=User->LastErr;// 更新前次误差
    User->LastErr=NowError;// 更新上次误差
    User->LastOut=OutPut;  // 更新上次数据
    return OutPut;
}
#define Max 3000
//增量式PID电机控制
//pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
int16 IncrementPID(PID_S *User,int16 Nowdat,int16 Setdat)
{
    int16 NowError;
    int16 OutPut;
    int16 KpError,KiError,KdError;
    NowError=Nowdat-Setdat;
    KpError=NowError-User->LastErr;
    KiError=0;
    KdError=NowError-2*(User->LastErr)+User->PastErr;
    if(User->LastOut>Max)
    {
        if(NowError<=0)
        {
            KiError=NowError;
        }
    }
    else if(User->LastOut<(-Max))
    {
        if(NowError>=0)
        {
            KiError=NowError;
        }
    }
    else {
        KiError=NowError;
    }
    OutPut=User->Kp*KpError+User->Ki*KiError+User->Kd*KdError;
//    OutPut=User->Kp*(NowError-User->LastErr)
//            +User->Ki*NowError
//            +User->Kd*(NowError-2*User->LastErr+User->PastErr);
    User->PastErr=User->LastErr;
    User->LastErr=NowError;
    User->LastOut=OutPut;
    return OutPut;
}

int16 LimitProtect(int16 max,int16 min,int16 data)
{
    if(data<min)
    {
        return min;
    }
    else if(data>=max)
    {
        return max;
    }
    else return data;
}

void PID_Set(void)
{
//速度环
//    SpeedAL_PID.Kp=-0; //位置式值-28.6    -31  -22.34
//    SpeedAL_PID.Ki=-0;  //位置式值-1.13  -0.78
//
//    SpeedAR_PID.Kp=-0; //位置式值-29.6
//    SpeedAR_PID.Ki=-0;//位置式值-1.14
//
//    SpeedBL_PID.Kp=-0;//位置式值-30.4
//    SpeedBL_PID.Ki=-0;//位置式值-1.21
//
//      SpeedBR_PID.Kp=-0;//位置式值-28.5
//      SpeedBR_PID.Ki=-0;//位置式值-1.3
  SpeedAL_PID.Kp=-33.4; //位置式值-28.6    -31  -22.34
  SpeedAL_PID.Ki=-2.07;  //位置式值-1.13  -0.78

  SpeedAR_PID.Kp=-37.9; //位置式值-29.6
  SpeedAR_PID.Ki=-2.01;//位置式值-1.14

  SpeedBL_PID.Kp=-36.5;//位置式值-30.4
  SpeedBL_PID.Ki=1.97;//位置式值-1.21

  SpeedBR_PID.Kp=-34.5;//位置式值-28.5
  SpeedBR_PID.Ki= 1.97;//位置式值-1.3
//变形
//  BX_PWM.Kp=0.80;
//  BX_PWM.Ki=0.20;
//  BX_PWM.SumErrorMax=1000;
//  B_PWM.Kp=-1.0;
//  B_PWM.Ki=-0.2;
//  B_PWM.SumErrorMax=1000;
//摄像头转向环
  TurnCamer_PIDS.Kp=-1.75;   //1.0
  TurnCamer_PIDS.Kd=0;
  TurnCamer_PIDS.SumErrorMax=800;
////H起跑
//  TurnCamer_PIDH.Kp=-11.2;   //1.0 60 10
//  TurnCamer_PIDH.Ki=0.3;
//  TurnCamer_PIDH.Kd=-4;
    TurnCamer_PIDH.Kp=-11.2;   //1.0 60 10
    TurnCamer_PIDH.Ki=0;
    TurnCamer_PIDH.Kd=0;
//  TurnCamer_PIDH.Kp=-18;   //1.0 60 10
//  TurnCamer_PIDH.Ki=-0.1;
//  TurnCamer_PIDH.Kd=-6;
  TurnCamer_PIDH.SumErrorMax=50;
////停车
//  TurnCamer_park.Kp=-7.0;
  TurnCamer_PIDS.SumErrorMax=100;
////角加速度环
  Gyro_PID.Kp=-0.08;//-0.08
  Gyro_PID.Kd=-0.00;
  Gyro_PID.SumErrorMax=300;
//电机死区
//  MotorValue_AL.MinSpeed=30;
//  MotorValue_AR.MinSpeed=30;
//  MotorValue_BL.MinSpeed=30;
//  MotorValue_BR.MinSpeed=30;
////设想速度
//  State.slowdown=0.75;
//  MotorValue_AL.IdeaSpeed=100;
//  SpeedGet=MotorValue_AL.IdeaSpeed;
}


