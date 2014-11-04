//initUART_Timer.h
//2010-09-09 PM
//By Hiber From  FEIBIT  Electronics LTD.
// www.feibit.com


#include <ioCC2530.h>
#define uint unsigned int
#define uchar unsigned char
#define LED1 P0_0
#define LED2 P0_1
#define LED3 P1_4
// Data
typedef unsigned char       BYTE;

// Unsigned numbers
typedef unsigned char       UINT8;
typedef unsigned char       INT8U;
typedef unsigned short      UINT16;
typedef unsigned short      INT16U;
typedef unsigned long       UINT32;
typedef unsigned long       INT32U;

// Signed numbers
typedef signed char         INT8;
typedef signed short        INT16;
typedef signed long         INT32;

#define DISABLE_ALL_INTERRUPTS() (IEN0 = IEN1 = IEN2 = 0x00)//����

/**************************
ϵͳʱ�� ����Ƶ
����ʱ�� 32��Ƶ
**************************/
void InitClock(void)
{   
    CLKCONCMD &= ~0x40; // ����ϵͳʱ��ԴΪ 32MHZ����
    while(CLKCONSTA & 0x40);                     // �ȴ������ȶ� 
    CLKCONCMD &= ~0x47;                          // ����ϵͳ��ʱ��Ƶ��Ϊ 32MHZ
}
/****************************
//��ʼ������
*****************************/
void InitLed(void)
{
	 P0DIR |=0x03;
         P1DIR |=0x10;
	LED1 = 0;       //LED1��Ϩ��
        LED2 = 0;    
        LED3 = 0;
}
/****************************
T3��ʼ��
****************************/
void InitT3(void)
{
  T3CCTL0 = 0X44;        // T3CCTL0 (0xCC)��CH0 �ж�ʹ�ܣ�CH0 �Ƚ�ģʽ
  T3CC0 = 0xFA;          // T3CC0����Ϊ250
  T3CTL |= 0x9A;         // ����T3������������ʱ��Ϊ16��Ƶ��ʹ��MODULOģʽ
  IEN1 |= 0X08;     
  IEN0 |= 0X80;          //�����жϣ���T3�ж�
}
/*****************************************
 ���ڳ�ʼ����������ʼ������ UART0		
*****************************************/
void InitUART0(void)
{
	PERCFG = 0x00;				 //λ��1 P0��
	P0SEL = 0x3c;				 //P0��������
	
	P2DIR &= ~0XC0;                           //P0������ΪUART0    
        U0CSR |= 0x80;   	                  //��������ΪUART��ʽ
        U0GCR |= 11;				
        U0BAUD |= 216;		                  //��������Ϊ115200

	UTX0IF = 1;                               //UART0 TX�жϱ�־��ʼ��λ1  
        U0CSR |= 0X40;				  //�������
        IEN0 |= 0x84;				  //�����жϣ������ж�

}

/****************************************************************
   ���ڷ����ַ�������						
****************************************************************/
void UartTX_Send_String(char *Data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF = *Data++;
    while(UTX0IF == 0);
    UTX0IF = 0;
  }
     U0DBUF = 0x0A;      
    while(UTX0IF == 0);
      UTX0IF = 0;
}


/****************************
//��ʱ����
*****************************/
void Delayms(uint xms)   //i=xms ����ʱi���� (16M����ʱ���Լ����32M��Ҫ�޸ģ�ϵͳ���޸�Ĭ��ʹ���ڲ�16M)
{
 uint i,j;
 for(i=xms;i>0;i--)
   for(j=20000;j>0;j--);
} 






