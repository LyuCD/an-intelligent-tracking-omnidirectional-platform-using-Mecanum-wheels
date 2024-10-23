#ifndef _MAILUN_CONTROL_h
#define _MAILUN_CONTROL_h

#include "common.h"
extern  int16 goalspeed_A,goalspeed_B,goalspeed_C,goalspeed_D;
void McNamm_Control(float Vx,float Vy,float Vz);
void Speed_Conversion(u8 setspeedl,int setspeeds,int16 x,int16 y);

#endif

