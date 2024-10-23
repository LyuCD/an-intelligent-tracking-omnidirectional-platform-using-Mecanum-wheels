#include "headfile.h"

float Turn_Can_PWM;
 float Turn_PWM;
//
///*********************方向控制输出********************/
float pid_err;
float pid_kp;
float pid_kd;
float pid_err_out;
float pid_err_pre;

float servo_pd(float err,float err_set)
{
    pid_err=err-err_set;
//    if(pid_err>2)
//    {
        pid_kp=2.0;
        pid_kd=0.0;
//    }
//    else
//    {
//        pid_kp=0.4;
//        pid_kd=0.;
//    }
    pid_err_out=pid_kp*pid_err
               +pid_kd*(pid_err-pid_err_pre);
    pid_err_pre=pid_err;
    if(pid_err_out>500)pid_err_out=500;
    if(pid_err_out<-500)pid_err_out=-500;
    return pid_err_out;

}

 uint8 Turn_Mode;
void Direction_Control(void)
{

//    if(Flag_User.Turn_flag==1)
//    {

//        if(Turn_Mode==1)
//        {
//
//            //angular_c=LimitProtect(40,-40,angular_c);
//            Turn_Can_PWM=PlacePID_Control(&TurnCamer_PIDS,Turn[0],angular_c,0);
//            Turn_PWM=PositPID(&Gyro_PID,icm_gyro_x, 10*Turn_Can_PWM);
//            Turn_PWM=LimitProtect(200,-200,Turn_PWM);     //限幅保护
//
//        }
//        else if(Turn_Mode==2)
//            {
         //   Turn_PWM=-servo_pd(angular_c*10,icm_gyro_z);
   //         angular_c=LimitProtect(40,-40,angular_c);
                Turn_PWM=PositPID(&TurnCamer_PIDH,angular_c,0);
                Turn_PWM=LimitProtect(5000,-5000,Turn_PWM);     //限幅
//
//            }

}



