# 如何新建工程

## Step1: 建立文件夹和文件
文件夹结构:
```raw
LED: 工程文件夹
    ├--Listing: 存放编译器编译时产生的c/汇编/链接的列表清单
    ├--Output:  存放编译产生的调试信息/hex文件/预览信息/封装库等
    ├--startup_stm32f10x_hd.s
    ├--stm32f10x.h
    └--main.c
```
- 其中`startup`文件位置为:
    - C:\Keil_v5\OD_A\1-程序源码_教程文档\
    - 1-[野火]《STM32库开发实战指南》(标准库源码)【优先学习】\
    - 1-书籍配套例程-F103ZE霸道V1V2_20210331\
    - 0【固件库】STM32F10x_StdPeriph_Lib_V3.5.0\
    - Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\
    - startup\arm\startup_stm32f10x_hd.s

## Step2: KEIL5 新建工程
- ToolBar -> Project -> New μVision Project
- 选择CPU型号
- 在线添加库文件
- 添加文件: 上面说到的三个文件
- 配置魔术棒选项卡: Options -> Target -> Use MicroLIB
- Output输出文件夹定位






