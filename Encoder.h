
#ifndef __ENCODER_H
#define __ENCODER_H
#include"common.h"

extern int16 Encoder_A,Encoder_B,Encoder_C,Encoder_D;//��ǰ�ٶȣ���ǰ���ٶȣ�������ٶȣ��Һ����ٶ�

  void Qtimer_Init(void);
  void QtimerC_read (void);
  void QtimerD_read (void);
  void QtimerB_read (void);
  void QtimerA_read (void);

 #endif
