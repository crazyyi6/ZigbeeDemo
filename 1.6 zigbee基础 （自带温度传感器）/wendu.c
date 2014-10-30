#include <ioCC2530.h>
#include "InitUART_Timer.h"
#include "stdio.h"
//温度传感器初始化函数
void initTempSensor(void)
{
  DISABLE_ALL_INTERRUPTS();//关闭所有中断
  InitClock();//设置系统主时钟为32MHZ
  TR0=0x01;//设置为1来连接温度传感器到SOC_ADC
  ATEST=0x01;//使能温度传感器（也可见12.2.10 节TR0 寄存器描述）。
}
//读取温度传感器AD值函数
float getTemperature(void){
uint value;
ADCCON3 =(0x3E);//选择1.25v为参考电压，12位分辨率； 对片内温度传感器采样
ADCCON1 |=0x30;//选择ADC的启动模式为手动
ADCCON1 |=0x40;//启动AD转化
while(!(ADCCON1&0x80));//等待AD转换完成
value =ADCL>>4;//ADCL寄存器低4位无效
value |=(((UINT16)ADCH)<<4);
return (value-1367.5)/4.5-4;//根据AD值，计算出实际的温度，芯片                               
}
//主函数
void main(void)
{
  char i;
  char TempValue[6];
  float AvgTemp;
  InitClock();
  InitLed();
  InitT3();
  InitUART0();
  initTempSensor();
  while(1)
  {
    AvgTemp=0;
    for(i=0;i<64;i++)
    {
      AvgTemp +=getTemperature();
      AvgTemp=AvgTemp/2;
    }
    //温度转换成ascii碼发送
    TempValue[0]=(unsigned char)(AvgTemp)/10+48;
    TempValue[1]=(unsigned char)(AvgTemp)%10+48;
    TempValue[2]='.';
    TempValue[3]=(unsigned char)(AvgTemp*10)%10+48;
    TempValue[4]=(unsigned char)(AvgTemp*100)%10+48;
    TempValue[5]='\n';
    UartTX_Send_String(TempValue,6);
    Delayms(20000);
      
  }
  
}
