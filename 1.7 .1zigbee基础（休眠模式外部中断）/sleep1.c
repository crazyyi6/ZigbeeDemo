#include <ioCC2530.h>
#define uint unsigned int 
#define uchar unsigned char

//����led��
#define LED1 P0_0
#define LED2 P0_1
#define LED3 P1_4
#define KEY1 P0_4

//��������

void Delayms(uint);
void InitLed(void);
void SysPowerMode(uchar sel);
//��ʼ����������ʼ��led��key�����ж�
void InitLed(void)
{
  P0DIR |=0x03;
  P1DIR |=0x10;
  //�ر����еĵƣ�Ĭ���������ģ����ݵ�·ͼ�ƻ���
  LED1 =0;
  LED2=0;
  LED3=0;
  P0INP &=~0x10;
  P0IEN |=0x10;
  PICTL |=0x10;
   IEN1 |=0x20;
  P0IFG &=~0x10;
  EA=1;
}
//�ӳٺ���
void Delayms(uint xms)
{
  uint i,j;
  for(i=xms;i>0;i--)
    for(j=20000;j>0;j--);
}
//����ģʽ
void SysPowerMode(uchar mode)
{
  uchar i,j;
  i=mode ;
  if(mode<4)
  {
    SLEEPCMD |=i;//����ģʽi
    for(j=0;j<4;j++);
      PCON=0x01;   //����ģʽ��ͨ���жϴ��
  }
  else
  {
    LED3=1;
    PCON =0x00;//��������ģʽ
  }
}
void main(void)
{
  InitLed();
  while(1)
  {
    LED1=~LED1;
    //��������ģʽ
    SysPowerMode(3);
  }
}
#pragma vector =P0INT_VECTOR
__interrupt void P0_ISR(void)
{
  Delayms(6);
  if(KEY1>0)
  {
    //�ص�����ģʽ
    SysPowerMode(4);
    P0IFG&=~0x10;
    P0IF=0;  
  }
}
