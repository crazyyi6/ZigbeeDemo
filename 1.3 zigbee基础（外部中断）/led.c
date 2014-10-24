#include<ioCC2530.h>
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
//������
void main(void)
{
  Init();//��ʼ�������͵�
  while(1);
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

  P0IEN |=0x10;//P04����Ϊ�жϷ�ʽ
  PICTL |=0x10;//�½��ش���
  IEN1 |=0x20;//����P0�ж�
  P0IFG &=~0x10;//��ʼ���жϱ�־λ
  EA=1;//�����ж�
}
//�жϴ�����

#pragma vector = P0INT_VECTOR 
__interrupt void P0_ISR(void)
{
  Delayms(6);//������
  if(KEY1==0)
  {
    LED3=~LED3;
    P0IFG &=~0x10;//����жϱ�־
    P0IF=0;//����жϱ�־
  }
  
}
