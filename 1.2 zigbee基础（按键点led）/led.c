#include <ioCC2530.h>
#define uint unsigned int 
#define uchar unsigned char
//��������led��
#define LED1 P0_0
#define LED2 P0_1
#define LED3 P1_4
//���尴��key1
#define KEY1 P0_4
//����������
void Delay(uint);
void Init(void);
uchar KeyScan();
//������
void main(void)
{
  Init();//��ʼ�������͵�
  while(1)
  {
    if(KeyScan())//�жϰ���״̬
      LED3=~LED3;//�Ƶ�״̬ȡ��
  }
}
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
  //���ð�����ؼĴ���
  P0SEL &=~0x10;
  P0DIR &=~0x10;
  P0INP &=~0x10;
}
uchar KeyScan(void)
{
  if(KEY1==0)
  {
    Delayms(10);//������
    if(KEY1==0)
    {
      while(!KEY1);
      return 1;
    }
  }
  return 0;
}