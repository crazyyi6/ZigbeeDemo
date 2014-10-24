#include<ioCC2530.h>
#define uint unsigned int 
#define uchar unsigned char
//定义三个led灯
#define LED1 P0_0
#define LED2 P0_1
#define LED3 P1_4
//函数声明
void Init(void);
void Delay(uint xms);
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
  //定时器初始化
  //系统不配置工作时钟时使用内部RC振荡器，即16MHZ
  T1CTL=0x0d;
}
// 主函数
void main(void)
{
  uchar count;
  Init();//初始化
  while(1)
  {
    if(IRCON>0) //查询方式 IRCON是中断标志寄存器
    {
      IRCON=0;
      if(++count==1)
      {
        count=0;
        LED3=!LED3;//LED1闪烁
      }
    }
  }
}