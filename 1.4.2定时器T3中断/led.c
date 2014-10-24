#include<ioCC2530.h>
#define uint unsigned int 
#define uchar unsigned char
//定义三个led灯
#define LED1 P0_0
#define LED2 P0_1
#define LED3 P1_4
//计数位
 uchar count;
//函数声明
void Init(void);
void Init(void)
{
  P0DIR |=0x03;
  P1DIR |=0x10;
  //关闭所有的灯，默认是上拉的，根据电路图灯会亮
  LED1 =0;
  LED2 =0;
  LED3 =0;
 
  T3CTL |=0x08;//中断使能
  T3IE =1;//开总中断和T3中断
  T3CTL |=0xE0;//128分频
  T3CTL &=~0x03;//自动重装00->0xff
  T3CTL |=0x10;//启动
  EA =1;//开总中断
}

// 主函数
void main(void)
{
  Init();//初始化
  while(1){}
  
}
//中断函数
#pragma vector =T3_VECTOR //定时器3
__interrupt void T3_ISR(void)
{

  IRCON=0x00;  //清中断标志，也可以由硬件自动完成
 if(++count>254)  // 254 中断后LED取反，闪烁一次
  {
    count=0;
    LED3=~LED3;
    
  }
}