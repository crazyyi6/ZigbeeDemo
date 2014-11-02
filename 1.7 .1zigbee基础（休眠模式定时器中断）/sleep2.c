#include <ioCC2530.h>
#define uint unsigned int 
#define uchar unsigned char
#define UINT32 unsigned long
#define UINT8 unsigned char

//����led��
#define LED1 P0_0
#define LED2 P0_1
#define LED3 P1_4

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
 i=mode;
 if(mode<4)
 {
   SLEEPCMD |=i;
   for(j=0;j<4;j++);
      PCON=0x01;
 }
 else
 {
   PCON=0x00;
   LED1=1;
 }
}
//��ʼ��Sleep Timer
void Init_SLEEEP(void)
{
  ST2=0x00;
  ST1=0x0F;
  ST0=0x0F;
  EA=1;
  STIE=1;
  STIF=0;
}
void Set_ST_Period(uint sec)
{
  UINT32 sleepTimer =0;
  sleepTimer |=ST0;
  sleepTimer |=(UINT32)ST1<<8;
  sleepTimer |=(UINT32)ST2<<16;
  sleepTimer |=((UINT32)sec *(UINT32)32768);
  ST2 =(UINT8)(sleepTimer>>16);
  ST1=(UINT8)(sleepTimer>>8);
  ST0=(UINT8)sleepTimer;
}
void main(void)
{
  //uchar i;
  InitLed();
  Init_SLEEEP();
  while(1)
  {
   LED3=1; 
  Set_ST_Period(3);
  SysPowerMode(2);
  }
}
#pragma vector =ST_VECTOR
__interrupt void ST_ISR(void)
{
  STIF=0;
  SysPowerMode(4);
}
