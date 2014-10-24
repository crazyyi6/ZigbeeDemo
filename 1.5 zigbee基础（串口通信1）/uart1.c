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
char Txdata[14];
//������
void main(void)
{
  CLKCONCMD &=~0x40;  //����ϵͳʱ��ԴΪ32MHZ����
  while(CLKCONSTA&0x40);   ///�ȴ������ȶ�Ϊ32M
  CLKCONCMD=~0x47;// ����ϵͳ��ʱ��Ƶ��Ϊ32MHZ
  InitUart();
  strcpy(Txdata,"hello xiaocai");//���������ݸ��Ƶ�txdata
  while(1)
  {
    UartSend(Txdata,sizeof("hello xiaocai"));//���ڷ�������
    Delay(500);  //��ʱ
    LED3=!LED3;  //��־����״̬
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
  //�ر����еĵƣ�Ĭ���������ģ����ݵ�·ͼ�ƻ���
  LED1 =0;
  LED2 =0;
  LED3 =0;
  
  PERCFG =0x00;    //λ��1  P0��
  P0SEL=0x0c;      // P02,P03�������ڣ��ⲿ�豸���ܣ�
  P2DIR &=~0xc0;  //p0������ΪUART0
  U0CSR |=0x80;     //����UART��ʽ
  U0GCR  |=11;
  U0BAUD |=216 ;  // ����������Ϊ115200
  UTX0IF = 0; //UART TX �жϱ�־��ʼ��λ0
    
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