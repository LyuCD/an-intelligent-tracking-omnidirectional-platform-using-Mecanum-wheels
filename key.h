#ifndef __KEY_H
#define __KEY_H

#include "common.h"





//上一次开关状态变量
 extern uint8 key1_last_status;
 extern uint8 key2_last_status;
 extern uint8 key3_last_status;


//开关标志位
 extern uint8 key1_flag;
 extern uint8 key2_flag;
 extern uint8 key3_flag;


 extern float test1,test2,test3,test4;

void key_init(void);
void key(void);
#endif
