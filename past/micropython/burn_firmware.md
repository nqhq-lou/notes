---
title: install microPython
tags: [Language/microPython]
---

## 参考文献
- [使用MicroPython开发ESP32（01）：快速入门](https://blog.csdn.net/naisu_kun/article/details/103983140)
- [ESP32概述与入门准备](https://blog.csdn.net/Naisu_kun/article/details/84583785)
- [ESP32-DevKitC V4 入门指南](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/hw-reference/esp32/get-started-devkitc.html?highlight=kitc#)
- [官方文档: 与ESP32创建连接](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/get-started/establish-serial-connection.html#)
    - 需要安装CP210x USB 至 UART 桥 VCP 驱动程序

## Thonny
- 原则上找一个能用串口软件就可以, 比如putty, VSCode.
- 但是推荐Thonny. 该工具集固件烧录, Python Shell调试, 文件管理于一体, 是目前用MicroPython开发最理想的工具.
- [官方网站](https://thonny.org/)

## 方法
- 固件升级: 讲支持micropython的bin文件写入flash中, 这个文件可以在micropython官网上找到
    - 本处写入的bin为`esp32-idf4-20210202-v1.14.bin`, 名称里有无idf是什么意思我不知道
    - 最新版本1.16名字里没有idf我不敢装
- 然后进行后续设置

## 初始化步骤
- 安装Thonny
- 进行flash烧写(这个用词对吗)
    - 工具栏: `工具` -> `设置` -> `解释器`
    - 选择右下角"install or update firmware"
    - 选择ESP32对应的port, 选择bin文件, 点击安装
    - 可勾选项目分别为: **黑体**为勾选上的
        - |  **from image file (keep)**  |  Quad I/O (qio)  |
        - |  Dual I/O (dio)  |  Dual Output (dout)  |
        - **Erase flash before installing**
- 安装之后就可以正常使用micropython了
