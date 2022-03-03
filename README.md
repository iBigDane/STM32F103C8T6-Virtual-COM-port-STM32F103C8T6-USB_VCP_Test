### STM32F103C8T6 Virtual COM port STM32F103C8T6 USB_VCP_Test

实验器材:
	STM32F103C8T6核心板
	
实验目的:
	学习STM32的USB功能使用,实现一个USB虚拟串口功能.
	
硬件资源:
	1,PC13 LED灯
	2,串口1(波特率:115200,PA9/PA10连接在板载USB转串口芯片CH340上面）
	4,USB_SLAVE接口(D-/D+连接在PA11/PA12上)
	
实验现象:
	本实验，利用STM32自带的USB功能,连接电脑USB,虚拟出一个USB串口，实现电脑和开发板的数据通信。当USB连接电脑（USB线入USB_SLAVE接口），开发板将通过USB和电脑建立连接虚拟出一个串口（注意：需要先安装STM32 USB虚拟串口驱动VCP_V1.4.0_Setup.exe这个驱动软件），USB和电脑连接成功后，在找到虚拟串口后，即可打开串口调试助手，即：STM32通过USB虚拟串口和上位机对话，STM32在收到上位机发过来的字符串（以回车换行结束）后，原原本本的返回给上位机。下载后，PC13闪烁，提示程序在运行，同时每隔一定时间，通过USB虚拟串口输出一段信息到电脑。 
	
注意事项:
	1,本实验需安装STM32 USB虚拟串口驱动VCP_V1.4.0_Setup.exe这个驱动
	2,如果电脑显示驱动安装不正常（有惊叹号），请手动选择驱动安装，驱动路径（以WIN7系统为例）：C:\
	  Program Files (x86)\STMicroelectronics\Software\Virtual comport driver\Win7
	3,本例程USB线需要插在:USB_SLAVE,并确保P9的D-/D+通过跳线帽连接在PA11/PA12.
	

































