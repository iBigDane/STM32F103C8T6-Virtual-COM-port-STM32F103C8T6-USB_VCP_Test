#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"	 
 
/************************************************
 ALIENTEKս��STM32������ʵ��48
 USB���⴮�� ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
 
 ע�ͣ���������������ԭ��USB���⴮�ڵĳ���Ļ�����ȥ����LCD����
 ������STM32F103C8T6��Сϵͳ�壬��Ϊ������LCD�ĳ���ᵼ�����⴮�ڵĳ���ʧЧ��
************************************************/


 int main(void)
 {	 
 	u16 t;
	u16 len;	
	u16 times=0;    
	u8 usbstatus=0;	
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	delay_ms(1800);
	USB_Port_Set(0); 	//USB�ȶϿ�
	delay_ms(700);
	USB_Port_Set(1);	//USB�ٴ�����
 	Set_USBClock();   
 	USB_Interrupts_Config();    
 	USB_Init();	    
	while(1)
	{
		if(usbstatus!=bDeviceState)//USB����״̬�����˸ı�.
		{
			usbstatus=bDeviceState;//��¼�µ�״̬
			if(usbstatus==CONFIGURED)
			{
				LED=0;//DS1��
			}else
			{
				LED=1;//DS1��
			}
		}
		if(USB_USART_RX_STA&0x8000)
		{					   
			len=USB_USART_RX_STA&0x3FFF;//�õ��˴ν��յ������ݳ���
			usb_printf("\r\n�����͵���ϢΪ:%d\r\n\r\n",len);
			for(t=0;t<len;t++)
			{
				USB_USART_SendData(USB_USART_RX_BUF[t]);//���ֽڷ�ʽ,���͸�USB 
			}
			usb_printf("\r\n\r\n");//���뻻��
			USB_USART_RX_STA=0;
		}else
		{
			times++;
			if(times%5000==0)
			{
				usb_printf("\r\nս��STM32������USB���⴮��ʵ��\r\n");
				usb_printf("����ԭ��@ALIENTEK\r\n\r\n");
			}
			if(times%200==0)usb_printf("����������,�Իس�������\r\n");  
			if(times%30==0)LED=!LED;//��˸LED,��ʾϵͳ��������.
			delay_ms(10);   
		}
	}
}

