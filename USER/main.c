#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"	 
 
/************************************************
 ALIENTEK战舰STM32开发板实验48
 USB虚拟串口 实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
 
 注释：本程序是再正点原子USB虚拟串口的程序的基础上去掉了LCD程序
 以适配STM32F103C8T6最小系统板，因为加上了LCD的程序会导致虚拟串口的程序失效。
************************************************/


 int main(void)
 {	 
 	u16 t;
	u16 len;	
	u16 times=0;    
	u8 usbstatus=0;	
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	LED_Init();		  		//初始化与LED连接的硬件接口
	delay_ms(1800);
	USB_Port_Set(0); 	//USB先断开
	delay_ms(700);
	USB_Port_Set(1);	//USB再次连接
 	Set_USBClock();   
 	USB_Interrupts_Config();    
 	USB_Init();	    
	while(1)
	{
		if(usbstatus!=bDeviceState)//USB连接状态发生了改变.
		{
			usbstatus=bDeviceState;//记录新的状态
			if(usbstatus==CONFIGURED)
			{
				LED=0;//DS1亮
			}else
			{
				LED=1;//DS1灭
			}
		}
		if(USB_USART_RX_STA&0x8000)
		{					   
			len=USB_USART_RX_STA&0x3FFF;//得到此次接收到的数据长度
			usb_printf("\r\n您发送的消息为:%d\r\n\r\n",len);
			for(t=0;t<len;t++)
			{
				USB_USART_SendData(USB_USART_RX_BUF[t]);//以字节方式,发送给USB 
			}
			usb_printf("\r\n\r\n");//插入换行
			USB_USART_RX_STA=0;
		}else
		{
			times++;
			if(times%5000==0)
			{
				usb_printf("\r\n战舰STM32开发板USB虚拟串口实验\r\n");
				usb_printf("正点原子@ALIENTEK\r\n\r\n");
			}
			if(times%200==0)usb_printf("请输入数据,以回车键结束\r\n");  
			if(times%30==0)LED=!LED;//闪烁LED,提示系统正在运行.
			delay_ms(10);   
		}
	}
}

