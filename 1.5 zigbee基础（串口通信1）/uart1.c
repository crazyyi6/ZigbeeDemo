#include <ioCC2530.h>
#include <string.h>

#define uint unsigned int
#define uchar unsigned char

//定义三个led灯
#define LED1 P0_0
#define LED2 P0_1
#define LED3 P1_4

//函数声明

void Delay(uint);
void InitUart(void);
void UartSend (char *Data,int len);
char Txdata[14];
//主函数
void main(void)
{
  CLKCONCMD &=~0x40;  //设置系统时钟源为32MHZ晶振
  while(CLKCONSTA&0x40);   ///等待晶振稳定为32M
  CLKCONCMD=~0x47;// 设置系统主时钟频率为32MHZ
  InitUart();
  strcpy(Txdata,"hello xiaocai");//将发送内容复制到txdata
  while(1)
  {
    UartSend(Txdata,sizeof("hello xiaocai"));//串口发送数据
    Delay(500);  //延时
    LED3=!LED3;  //标志发送状态
  }
}
void Delay(uint n)
{
  uint i,j;
  for(i=0;i<n;i++)
  {
    for(j=0;j<1774;j++);
  }
}
void InitUart()
{
  P0DIR |=0x03;
  P1DIR |=0x10;
  //关闭所有的灯，默认是上拉的，根据电路图灯会亮
  LED1 =0;
  LED2 =0;
  LED3 =0;
  
  PERCFG =0x00;    //位置1  P0口
  P0SEL=0x0c;      // P02,P03用作串口（外部设备功能）
  P2DIR &=~0xc0;  //p0优先作为UART0
  U0CSR |=0x80;     //设置UART方式
  U0GCR  |=11;
  U0BAUD |=216 ;  // 波特率设置为115200
  UTX0IF = 0; //UART TX 中断标志初始置位0
    
}
void UartSend(char *Data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF=*Data++;
    while(UTX0IF ==0);
    UTX0IF =0;
  }
}