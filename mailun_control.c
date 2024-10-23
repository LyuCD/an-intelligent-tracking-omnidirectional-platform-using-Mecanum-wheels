#include "headfile.h"
#include "math.h"

#define a_PARAMETER     (0.09f)
#define b_PARAMETER     (0.09f)
int16 goalspeed_A,goalspeed_B,goalspeed_C,goalspeed_D;
void McNamm_Control(float Vx,float Vy,float Vz)
{
    goalspeed_C    = -Vx+Vy-Vz*(a_PARAMETER+b_PARAMETER);
    goalspeed_A   = +Vx+Vy-Vz*(a_PARAMETER+b_PARAMETER);
    goalspeed_B  = -Vx+Vy+Vz*(a_PARAMETER+b_PARAMETER);
    goalspeed_D   = +Vx+Vy+Vz*(a_PARAMETER+b_PARAMETER);
}


