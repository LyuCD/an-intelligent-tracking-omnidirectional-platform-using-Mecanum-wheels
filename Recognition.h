#include "math.h"
#include"common.h"
#include"headfile.h"


#define PI  3.1415926       //Բ����

#define ROW MT9V03X_H
#define COL MT9V03X_W

#define row ROW/2               //�߼�ͼƬ����(���ӿ��Ϊ2�����)
#define col COL/2               //�߼�ͼƬ����

#define Grey_Max    250     //��߻Ҷ�


#define Round_D     -1      //��Ϊ-1���һ�Ϊ1
#define Sta_BD      -1     //�����Ϊ-1���ҳ���Ϊ1
#define Sta_ED      -1      //�����Ϊ-1�������Ϊ1


#define Round_in_delay  50 //�����뻷��ʱ�˳�
#define Round_out_delay 100 //����������ʱ�˳�
#define Round_use_delay 20
#define Sta_mark_delay  8 //�յ���ʱ�˳�
#define Sta_in_delay    2  //�յ�����ӳ�
#define Sta_begain_delay    20   //������ʱ

#define Round_in_unuse_delay    20   //�뻷��Ч�ӳ٣������������������뻷����
#define Round_out_use_delay     30  //�뻷ת�����ӳ٣�����һ��ʱ����������
#define End_lock_delay  1000


#define Begain_angular      20*Sta_BD     //����̶���
#define Round_angular       20*Round_D    //�����̶���
#define Round_angular_s     10*Round_D    //�뻷Ԥ�н�
#define Round_in_angular    20*Round_D    //�뻷��ʧ�̶���
#define Round_out_angular   -10*Round_D    //����������
#define End_angular         -5*Sta_ED    //��������
#define END_angulars        20*Sta_ED
#define END_angularss       20*Sta_ED


#define MN          4       //�е�ջ���С����

#define Mid_Deal    2       //���߽��ܵ���ϰڶ����
#define RLS     8           //���ұ��߷���ҡ��������ſ��
#define RLS_M   2           //��Բ��ҡ�ڿ��
#define MLS     2           //����ҡ������ȣ������ڴ����������䣩
#define Lose_dec    5

#define Stasway 2       //����������������ֵ
#define Stacode 4       //����ⷽ��
#define StaEmax 8       //������ʱҪ�����͵㣬���˺�ͣ��
#define Staside 3       //���׶ζ�����ȷ�����������ֵ��ڸ���ֵ�ı�����Ч�㣬��Ϊ��Ч
#define Staes1  1       //���׶�һ�Ŵ���
#define Staes2  0.8       //���׶ζ��Ŵ���
#define Stasw   1       //���׶ζ��������߰�
#define Stajp   3       //����������ֵ
#define StaImax 15      //���׶�һ��ߴ�������
#define StaAmax 15      //���׶ζ������ϽǶ�
#define StaBmax 16       //������ߴ�����

#define RJW     5           //�����жϿ�ȣ��Դ����
#define RJA     60          //�����жϽǶȣ��Ƕ�ֵ��

#define ITJ     5           //����·���жϳ��ȣ��ǵ���Ѱ����
#define RATJ    100         //����·���������������ϲ�����ITJ���ı�
#define TriW    15          //������жϱ߿�
#define TriMH   15          //����ڵ͵���ߴ����߶�

#define TriA_max 170        //��������Ƕ�
#define TriA_min 90        //�������С�Ƕ�

#define Round_in_judge  1   //�����뻷�ж�
#define Round_A_max 160     //�����뻷�ǵ����Ƕ�
#define Round_A_min 60      //�����뻷�ǵ���С�Ƕ�

#define Round_m     2       //�����ж�������ŵ���

#define Mid_Shake   2       //���߶��������


#define A_max   15
#define A_min   10
#define A_wide_max 12
#define A_wide_min  2

#define Ra_Max  400       //�ߵ����ֵ


#define Lose_k  2           //���߶�ʧ�жϵ�k���ֵ
#define Side_Sway   3       //������ߵ�����ߵ�����ſ��
#define High_Sway   2       //�������ⶥ��ҡ�����ֵ
#define High_n      10       //�����ж����ŵ������
#define High_b      1       //������ߵ�
#define Mid_Side_DM 2       //������ߵ�ͱ�����ߵ�������

#define RU_min      1
#define A_des       8       //�յ�ǰհ��������СΪ2
#define D_mark      8       //�յ���С�ж���

#define ES      1       //��ʧ����

#define Round_pass  7   //���������ж���͵���

#define Rh_max  65
#define Rh_min  50





#define int8    char

extern uint8 threshold;

extern uint8 mid_max;
extern uint8 side_max;
extern uint8 right_b;
extern uint8 left_b;
extern float angular_c;
extern uint8 piancha;

extern uint8 round_in;
extern uint8 round_out;
extern uint8 round_use;
extern uint8 sta_mark;
extern uint8 sta_in;
extern uint8 sta_begain;
extern uint8 sta_end;

extern uint8 sta_begain_lock;
extern uint8 sta_in_lock;

extern int sta_mark_delay;
extern int round_in_delay;
extern int round_out_delay;
extern int round_use_delay;
extern int sta_begain_delay;

void binarization(uint8(*p)[COL]);                                                                      //��ʼ��������ͼƬ���飬����Ѵ���Ķ�ֵ����СͼƬ
void supplement(uint8(*side_line)[col], uint8 a, uint8 b, uint8 c, uint8 d);                            //���ߺ���:��side_line,row,col,row,col)
void supplements(uint8(*side_line)[col], uint8 a, uint8 b, uint8 c, uint8 d);
void supplement_m(uint8(*side_line)[col], uint8* mid_line, uint8 a1, uint8 b1, uint8 a2, uint8 b2);     //���߲���
void point_show(uint8(*side_line)[col], uint8 a, uint8 b);                                              //�ߵ���ʾ����
void flip(uint8(*p)[COL], uint8(*side_line)[col], uint8* mid_line);                                     //д�롢�ָ�ͼƬ
int8 mid_value(uint8* mid_line, uint8(*side_line)[col]);                                                //ƫ�����������Ȩ��
uint8 line_sway(uint8(*side_line)[col], uint8 a1, uint8 b1, uint8 a2, uint8 b2, uint8 sw);              //�߰ں������������sw���ߵ���

uint8 nighbor_judge(uint8(*p)[COL], uint8(*line)[col], uint8 a, uint8 b, uint8 n);                      //�����ж����߼�ͼƬ�����ߣ������꣬������,������:���߱��2���������5��

void mid_seek(uint8(*side_line)[col], uint8* mid_line, uint8* r_line, uint8* l_line);                   //����̽Ѱ�����ڸ����ĳ�ʼ��һ���е�
void mid_seeks(uint8(*side_line)[col], uint8* mid_line);                                                //����̽Ѱ����

uint8 destination(uint8(*side_line)[col], uint8(*p)[COL], uint8 A);                          //�յ�̽Ѱ

uint8 comestorages(uint8(*side_line)[col]);                                     //���,�������0���׶�һ���1���׶�2���2��ͣ�����3

uint8 delay_mark(uint8(*p)[COL], uint8(*side_line)[col]);                                                               //��־λ

int8 lose_test(uint8(*side_line)[col]);                                         //�������0��ȫ�ߵ����1���Ҷ�ʧ���2����ʧ���3��
uint8 line_hunting(uint8(*p)[COL], uint8(*side_line)[col]);                         //�����򷨱߽�Ѱ��,ʧ�ܷ���0���ɹ������е�ֵ�����ҽ��б�����ߵ����������ʼ��ļ���
uint8 element_seeks(uint8(*side_line)[col], uint8(*p)[COL], uint8* mid_line);       //Ԫ���ж�,�������0�������뻷��ʧ���1���뻷�������2����ʮ��·��3һ���������4

void Image_Seeks(uint8(*image)[COL], uint8(*side_line)[col], uint8* mide_line);
void Image_Seek(uint8(*image)[COL], uint8(*side_line)[col], uint8* mide_line);
/*
���Ժ��������Ԫ�����ͣ�
�������0��һ���������1;
ȫ�ߵ����11���Ҷ�ʧ���12����ʧ���13�������Ϊ14����������Ϊ15��
�����뻷���21�������������22��ʮ��·��23��һ���������24,����ʶ�������6
�յ����׶�һ���31���׶ζ����32��ͣ�����33���������30
 */


