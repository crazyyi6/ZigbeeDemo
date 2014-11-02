#include <ioCC2530.h>
#define uint unsigned int 
#define uchar unsigned char

//定义led灯
#define LED1 P0_0
#define LED2 P0_1
#define LED3 P1_4
#define KEY1 P0_4

//函数声明

void Delayms(uint);
void InitLed(void);
void SysPowerMode(uchar sel);
//初始化操作，初始化led，key，和中断
void InitLed(void)
{
  P0DIR |=0x03;
  P1DIR |=0x10;
  //关闭所有的灯，默认是上拉的，根据电路图灯会亮
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
//延迟函数
void Delayms(uint xms)
{
  uint i,j;
  for(i=xms;i>0;i--)
    for(j=20000;j>0;j--);
}
//设置模式
void SysPowerMode(uchar mode)
{
  uchar i,j;
  i=mode ;
  if(mode<4)
  {
    SLEEPCMD |=i;//进入模式i
    for(j=0;j<4;j++);
      PCON=0x01;   //进入模式，通过中断打断
  }
  else
  {
    LED3=1;
    PCON =0x00;//进入正常模式
  }
}
void main(void)
{
  InitLed();
  while(1)
  {
    LED1=~LED1;
    //竟如休眠模式
    SysPowerMode(3);
  }
}
#pragma vector =P0INT_VECTOR
__interrupt void P0_ISR(void)
{
  Delayms(6);
  if(KEY1>0)
  {
    //回到正常模式
    SysPowerMode(4);
    P0IFG&=~0x10;
    P0IF=0;  
  }
}
