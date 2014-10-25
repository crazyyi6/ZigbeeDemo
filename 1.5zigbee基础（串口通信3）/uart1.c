#include <ioCC2530.h>
#include <string.h>

#define uint unsigned int
#define uchar unsigned char

//定义三个led灯
#define LED1 P0_0
#define LED2 P0_1
#define LED3 P1_4

//函数声明
void InitUart(void);
uint RXTXflag=1;
char temp ;
int datanumber;
char Rxdata[50];
//主函数
void main(void)
{
  InitUart();
  
  while(1)
  {
    if(RXTXflag==1)//接受状态
    {
    
      if(temp!=0)
      {
        if((temp!='#')&&(datanumber<3)) //以#为结尾，接受的字符只能有3个
          Rxdata[datanumber++]=temp;
        else
        {
          RXTXflag=3;
          
        }
        temp=0;
      }
    }
    if(RXTXflag==3)//发送状态
    {
     if(Rxdata[0]=='L')
       switch(Rxdata[1]-48) //1的ASCII值是49
          {
          case 1: //如果是L1,点亮LED3
            {
              LED3=~LED3;
              break;
            }
             case 2: //如果是L2，灭掉LED3
            {
              LED3=~LED3;
              break;
            }
          }
          RXTXflag=1;
          datanumber=0;
    }
  }
}
//写一个外部中断将U0DBUF的值给变量temp
#pragma vector =URX0_VECTOR
__interrupt void UART0_TSR(void)
{
  URX0IF=0;
  temp =U0DBUF;
}


void InitUart()
{
  P0DIR |=0x03;
  P1DIR |=0x10;
  //关闭所有的灯，默认是上拉的，根据电路图灯会亮
  LED1 =0;
  LED2 =0;
  LED3 =0;
  
  CLKCONCMD &=~0x40;  //设置系统时钟源为32MHZ晶振
  while(CLKCONSTA&0x40);   ///等待晶振稳定为32M
  CLKCONCMD=~0x47;// 设置系统主时钟频率为32MHZ
  
  PERCFG =0x00;    //位置1  P0口
  P0SEL=0x3c;      // P02,P03,P04,P05用作串口（外部设备功能）
  P2DIR &=~0xc0;  //p0优先作为UART0
  
  U0CSR |=0x80;     //设置UART方式
  U0GCR  |=11;
  U0BAUD |=216 ;  // 波特率设置为115200
  UTX0IF = 0; //UART TX 中断标志初始置位0
  
  U0CSR |=0x40;//允许接受
  IEN0 |=0x84;//开总中断，接受中断
    
}
