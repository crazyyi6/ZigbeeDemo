#include<ioCC2530.h>
#define uint unsigned int 
#define uchar unsigned char
//��������led��
#define LED1 P0_0
#define LED2 P0_1
#define LED3 P1_4
//��������
void Init(void);
void Delay(uint xms);
void Delayms(uint xms)//�ӳٺ�����
{
  uint i,j;
  for(i=xms;i>0;i--)
    for(j=1000;j>0;j--);
}
void Init(void)
{
  P0DIR |=0x03;
  P1DIR |=0x10;
  //�ر����еĵƣ�Ĭ���������ģ����ݵ�·ͼ�ƻ���
  LED1 =0;
  LED2 =0;
  LED3 =0;
  //��ʱ����ʼ��
  //ϵͳ�����ù���ʱ��ʱʹ���ڲ�RC��������16MHZ
  T1CTL=0x0d;
}
// ������
void main(void)
{
  uchar count;
  Init();//��ʼ��
  while(1)
  {
    if(IRCON>0) //��ѯ��ʽ IRCON���жϱ�־�Ĵ���
    {
      IRCON=0;
      if(++count==1)
      {
        count=0;
        LED3=!LED3;//LED1��˸
      }
    }
  }
}