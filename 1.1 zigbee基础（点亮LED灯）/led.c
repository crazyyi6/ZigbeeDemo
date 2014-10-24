#include <ioCC2530.h>
#define LED1 P0_0  //宏定义LED1 为P0_0
#define LED2 P0_1   
#define LED3 P1_4
void IO_Init(void)
{
  P0DIR |=0x03;  // 设置P0_0P0_1为输出
  P1DIR |=0x10;  //设置P1_4 为输出
    LED1=0;      //初始化LED1.2.3灯
    LED2=0;
    LED3=0;
}
void main(void)
{
   IO_Init();  //  初始化
    LED1=1;     //点亮LED1
    LED2=1;    //点亮LED2
    LED3=0;     //灭掉LED3
    while(1);  
  
}