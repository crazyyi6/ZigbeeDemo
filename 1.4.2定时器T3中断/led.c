#include<ioCC2530.h>
#define uint unsigned int 
#define uchar unsigned char
//��������led��
#define LED1 P0_0
#define LED2 P0_1
#define LED3 P1_4
//����λ
 uchar count;
//��������
void Init(void);
void Init(void)
{
  P0DIR |=0x03;
  P1DIR |=0x10;
  //�ر����еĵƣ�Ĭ���������ģ����ݵ�·ͼ�ƻ���
  LED1 =0;
  LED2 =0;
  LED3 =0;
 
  T3CTL |=0x08;//�ж�ʹ��
  T3IE =1;//�����жϺ�T3�ж�
  T3CTL |=0xE0;//128��Ƶ
  T3CTL &=~0x03;//�Զ���װ00->0xff
  T3CTL |=0x10;//����
  EA =1;//�����ж�
}

// ������
void main(void)
{
  Init();//��ʼ��
  while(1){}
  
}
//�жϺ���
#pragma vector =T3_VECTOR //��ʱ��3
__interrupt void T3_ISR(void)
{

  IRCON=0x00;  //���жϱ�־��Ҳ������Ӳ���Զ����
 if(++count>254)  // 254 �жϺ�LEDȡ������˸һ��
  {
    count=0;
    LED3=~LED3;
    
  }
}