#include <ioCC2530.h>
#define uint unsigned int 
#define uchar unsigned char
//定义三个led灯
#define LED1 P0_0
#define LED2 P0_1
#define LED3 P1_4
//定义按键key1
#define KEY1 P0_4
//函数的声明
void Delay(uint);
void Init(void);
uchar KeyScan();
//主函数
void main(void)
{
  Init();//初始化按键和灯
  while(1)
  {
    if(KeyScan())//判断按键状态
      LED3=~LED3;//灯的状态取反
  }
}
void Delayms(uint xms)//延迟函数，
{
  uint i,j;
  for(i=xms;i>0;i--)
    for(j=1000;j>0;j--);
}
void Init(void)
{
  P0DIR |=0x03;
  P1DIR |=0x10;
  //关闭所有的灯，默认是上拉的，根据电路图灯会亮
  LED1 =0;
  LED2 =0;
  LED3 =0;
  //设置按键相关寄存器
  P0SEL &=~0x10;
  P0DIR &=~0x10;
  P0INP &=~0x10;
}
uchar KeyScan(void)
{
  if(KEY1==0)
  {
    Delayms(10);//防抖动
    if(KEY1==0)
    {
      while(!KEY1);
      return 1;
    }
  }
  return 0;
}