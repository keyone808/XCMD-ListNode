# **一、简介**
该工程是我在2025-5月份完成，在FreeRTOS基础上，移植了+使用了XCMD命令行，完成串口交互，书写了部分链表代码，使用arudino编译2.3.4，xshell串口连接交互。
# 二、展示
## （1）进入界面：
![image](https://github.com/user-attachments/assets/484fb91d-e6c8-42af-92a7-d4ebfa087422)
## （2）tab快捷键查看所有功能：
![image](https://github.com/user-attachments/assets/03dfdad1-9e2d-4f2e-8d5f-057beaae4082)
## （3）添加指令方法：
在下图中，定义为命令行函数，需要在下二图中cmds声明，并引用对应函数，实现命令DIY。
![image](https://github.com/user-attachments/assets/b392d71a-3f99-451d-a6c9-466e3575f4ec)
![image](https://github.com/user-attachments/assets/6de831ca-6b76-4306-96c5-1dde82e2a97e)
# 三、XCMD移植教程 
该链接为XCMD的gitee链接，它可以移植到其他单片机：https://gitee.com/two_salted_eggs/xcmd#%E4%BD%BF%E7%94%A8%E8%AF%B4%E6%98%8E
