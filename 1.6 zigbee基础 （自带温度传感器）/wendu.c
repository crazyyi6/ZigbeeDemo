#include <ioCC2530.h>
#include "InitUART_Timer.h"
#include "stdio.h"
//�¶ȴ�������ʼ������
void initTempSensor(void)
{
  DISABLE_ALL_INTERRUPTS();//�ر������ж�
  InitClock();//����ϵͳ��ʱ��Ϊ32MHZ
  TR0=0x01;//����Ϊ1�������¶ȴ�������SOC_ADC
  ATEST=0x01;//ʹ���¶ȴ�������Ҳ�ɼ�12.2.10 ��TR0 �Ĵ�����������
}
//��ȡ�¶ȴ�����ADֵ����
float getTemperature(void){
uint value;
ADCCON3 =(0x3E);//ѡ��1.25vΪ�ο���ѹ��12λ�ֱ��ʣ� ��Ƭ���¶ȴ���������
ADCCON1 |=0x30;//ѡ��ADC������ģʽΪ�ֶ�
ADCCON1 |=0x40;//����ADת��
while(!(ADCCON1&0x80));//�ȴ�ADת�����
value =ADCL>>4;//ADCL�Ĵ�����4λ��Ч
value |=(((UINT16)ADCH)<<4);
return (value-1367.5)/4.5-4;//����ADֵ�������ʵ�ʵ��¶ȣ�оƬ                               
}
//������
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
    //�¶�ת����ascii�a����
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
