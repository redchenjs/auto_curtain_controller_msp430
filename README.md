# bth_curtain

一个基于MSP430G2553超低功耗单片机，BH1750FVI光照度传感器，DS3231时钟芯片，HC-05蓝牙UART模块，SSD1331 96x96 RGB显示屏的家用自动窗帘控制器设计。

**编译选项：--cpp_default -fg --printf_support nofloat**

**程序结构说明：**

	目录说明：
			./src					程序源文件主目录
			./src/device/			片上资源驱动程序目录
			./src/driver/			片外设备驱动程序目录
			./src/interface/		通讯协议驱动程序目录
			./src/system/			系统函数入口及初始化目录
			./src/user/				用户程序入口及自定义功能目录
			
	文件说明：
			./src/system/main.c		主函数入口源文件

			./src/system/init.c		系统初始化函数源文件		
			./src/system/init.h		系统初始化函数头文件
			
			./src/system/config.h	全局配置头文件
			
			./src/user/user.c		用户程序初始化及用户主循环函数源文件
			./src/user/user.h		用户程序初始化及用户主循环函数头文件
