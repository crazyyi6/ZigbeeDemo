#include<ioCC2530.h>
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
//主函数
void main(void)
{
  Init();//初始化按键和灯
  while(1);
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

  P0IEN |=0x10;//P04设置为中断方式
  PICTL |=0x10;//下降沿触发
  IEN1 |=0x20;//允许P0中断
  P0IFG &=~0x10;//初始化中断标志位
  EA=1;//开总中断
}
//中断处理函数

#pragma vector = P0INT_VECTOR 
__interrupt void P0_ISR(void)
{
  Delayms(6);//防抖动
  if(KEY1==0)
  {
    LED3=~LED3;
    P0IFG &=~0x10;//清除中断标志
    P0IF=0;//清除中断标志
  }
  
}
