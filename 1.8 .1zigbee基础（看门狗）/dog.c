#include <ioCC2530.h>
#define uchar unsigned char
#define uint unsigned int

#define LED1 P0_0
#define LED2 P0_1
#define LED3 P1_4

void Delayms(uint);
void Init(void);
void FeetDog(void);
//出事化
void Init(void)
{
   P0DIR |=0x03;
  P1DIR |=0x10;
  LED1 =0;
  LED2=0;
  LED3=0;
  
  WDCTL=0x00;//打开IDLE才能设置看门狗
  WDCTL |=0x08;//时间间隔一秒，看门狗模式
 
}
//延迟函数
void Delayms(uint xms)
{
  uint i,j;
  for(i=xms;i>0;i--)
    for(j=20000;j>0;j--);
}
void FeetDog(void)
{
  WDCTL=0xa0;
  WDCTL=0x50;
}
void main()
{
  Init();
  LED1=0;
  while(1)
  {
    LED3=~LED3;
    for(int i=0;i<9000;i++)
         Delayms(30000);
     for(int i=0;i<9000;i++)
         Delayms(30000);
      for(int i=0;i<9000;i++)
         Delayms(30000);
       for(int i=0;i<9000;i++)
         Delayms(30000);
       for(int i=0;i<9000;i++)
         Delayms(30000);
       for(int i=0;i<9000;i++)
         Delayms(30000);
       for(int i=0;i<9000;i++)
         Delayms(30000);
    LED1=1;
   // FeetDog();
  }
  
}