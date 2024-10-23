#include"headfile.h"

int16 SpeedAL_Value_Last;
int16 SpeedAR_Value_Last;
int16 SpeedHL_Value_Last;
int16 SpeedHR_Value_Last;



float  Middle_Err_Filter(float middle_err)    //中心偏差滤波
{
  float Middle_Err_Fltered;
  static float Pre3_Error[4];
  Pre3_Error[3]=Pre3_Error[2];
  Pre3_Error[2]=Pre3_Error[1];
  Pre3_Error[1]=Pre3_Error[0];
  Pre3_Error[0]=middle_err;
  Middle_Err_Fltered=Pre3_Error[0]*0.4+Pre3_Error[1]*0.3+Pre3_Error[2]*0.2+Pre3_Error[3]*0.1;
  return Middle_Err_Fltered;
}


void Timer2_IQR_handle(void)
{
//    static uint8 PIT_10ms=0;
//            static uint8 PIT_20ms=0;
//            PIT_10ms+=1;
//            PIT_20ms+=1;
//            Speed_Get();//获取速度
//            Flag_User.Speed_flag=1;
//            Speed_Control();
//            if(PIT_10ms*PIT_TIMER>=10)
//            {
//                    ICM_POSE();
//        //            GetAngle(&MPUMess,&MPUAngle,0.05);  //陀螺仪数据获取
//            }
//            if(PIT_20ms*PIT_TIMER>=20)
//            {
//                Flag_User.Turn_flag=1;
//            }
    //float pcout;

  //  get_icm20602_accdata_spi();


    pid_left_front.result=pid_left_front.result*0.7+SpeedAL_Value_Last*0.3;       //低通滤波平滑输出
                SpeedAL_Value_Last=pid_left_front.result;
    pid_right_front.result=pid_right_front.result*0.7+SpeedAR_Value_Last*0.3;       //低通滤波平滑输出
                SpeedAR_Value_Last=pid_right_front.result;
    pid_left_rear.result=pid_left_rear.result*0.7+SpeedHL_Value_Last*0.3;       //低通滤波平滑输出
                          SpeedHL_Value_Last=pid_left_rear.result;
    pid_right_rear.result=pid_right_rear.result*0.7+SpeedHR_Value_Last*0.3;       //低通滤波平滑输出
                          SpeedHR_Value_Last=pid_right_rear.result;
    Set_Pwm(-pid_left_front.result,-pid_right_front.result,pid_left_rear.result,pid_right_rear.result);



}
//

//


