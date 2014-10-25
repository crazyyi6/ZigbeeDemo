#include <ioCC2530.h>
#include <string.h>

#define uint unsigned int
#define uchar unsigned char

//��������led��
#define LED1 P0_0
#define LED2 P0_1
#define LED3 P1_4

//��������

void Delay(uint);
void InitUart(void);
void UartSend (char *Data,int len);
uint RXTXflag=1;
char temp ;
int datanumber;
char Rxdata[50];
//������
void main(void)
{
  InitUart();
  
  while(1)
  {
    if(RXTXflag==1)
    {
      LED3=1;//����״ָ̬ʾ
      if(temp!=0)
      {
        if((temp!='#')&&(datanumber<50)) //��#Ϊ��β�����ܵ��ַ�ֻ����50��
          Rxdata[datanumber++]=temp;
        else
        {
          RXTXflag=3;//���뷢��״̬
          LED3=0;
        }
        temp=0;
      }
    }
    if(RXTXflag==3)//����״̬
    {
      LED1=1;//���ͱ�־
      U0CSR&=~0x40;//��ֹ����
      UartSend(Rxdata,datanumber);//����
      U0CSR |=0x40; //�������
      RXTXflag =1;//�ظ���־
      datanumber=0;//����
      LED1=0;
    }
  }
}
//дһ���ⲿ�жϽ�U0DBUF��ֵ������temp
#pragma vector =URX0_VECTOR
__interrupt void UART0_TSR(void)
{
  URX0IF=0;
  temp =U0DBUF;
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
  //�ر����еĵƣ�Ĭ���������ģ����ݵ�·ͼ�ƻ���
  LED1 =0;
  LED2 =0;
  LED3 =0;
  
  CLKCONCMD &=~0x40;  //����ϵͳʱ��ԴΪ32MHZ����
  while(CLKCONSTA&0x40);   ///�ȴ������ȶ�Ϊ32M
  CLKCONCMD=~0x47;// ����ϵͳ��ʱ��Ƶ��Ϊ32MHZ
  
  PERCFG =0x00;    //λ��1  P0��
  P0SEL=0x3c;      // P02,P03,P04,P05�������ڣ��ⲿ�豸���ܣ�
  P2DIR &=~0xc0;  //p0������ΪUART0
  
  U0CSR |=0x80;     //����UART��ʽ
  U0GCR  |=11;
  U0BAUD |=216 ;  // ����������Ϊ115200
  UTX0IF = 0; //UART TX �жϱ�־��ʼ��λ0
  
  U0CSR |=0x40;//�������
  IEN0 |=0x84;//�����жϣ������ж�
    
}
void UartSend(char *Data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF=*Data++;
    while(UTX0IF ==0);//�������
    UTX0IF =0;
  }
}