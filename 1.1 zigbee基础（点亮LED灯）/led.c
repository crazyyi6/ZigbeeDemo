#include <ioCC2530.h>
#define LED1 P0_0  //�궨��LED1 ΪP0_0
#define LED2 P0_1   
#define LED3 P1_4
void IO_Init(void)
{
  P0DIR |=0x03;  // ����P0_0P0_1Ϊ���
  P1DIR |=0x10;  //����P1_4 Ϊ���
    LED1=0;      //��ʼ��LED1.2.3��
    LED2=0;
    LED3=0;
}
void main(void)
{
   IO_Init();  //  ��ʼ��
    LED1=1;     //����LED1
    LED2=1;    //����LED2
    LED3=0;     //���LED3
    while(1);  
  
}