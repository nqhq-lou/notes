---
title: Flask basics (bia Python)
tags: [software/Flask]
---

# Flask @ Python

- [使用 Python 和 Flask 生成 AI Web 应用 - Learn | Microsoft Docs](https://docs.microsoft.com/zh-cn/learn/modules/python-flask-build-ai-web-app/)

## 环境安装

- 使用`venv`
- 需要的包:flask, python-dotenv, requests
  - dotenv用于密钥管理, 但是没理解这里的密钥是什么

## 定性介绍

- Flask是一种开源Web微框架, 包含基础功能, 但是没有高级功能.
- 核心概念: 路由, 方法, 模板化
  - 路由:
    - 通过浏览不同URL进行功能定位, 一般`.com/`后面就是"路由"
    - 用户通过访问不同的路由, 进而完成不同的功能
  - 方法 / 谓词:
    - 只访问路由的方式
    - 最常见的是
      - "GET"(用户正在请求信息)
      - "POST"(用户需要向我们发送信息并接受响应)
    - 例如:
      - 用户通过GET访问注册表单
      - 填写注册表单并点击提交
      - 表单信息通过POST发送服务器
      - 服务器返回"成功"提示
  - 模板
    - HTML: 超文本标记语言, 用于构造浏览器上显示信息的语言
    - CSS: 级联样式表, 用于管理样式和布局
    - Web框架的作用
      - 大多数HTML语言为静态
      - 为了使得页面具有动态性, 需要以编程方式讲信息放入HTML
      - 几乎每一个Web 框架都可通过模板来满足这一需求

## 创建应用

1. 创建核心应用
   1. 通常Flask应用程序的入口为`app.py`的文件
2. 为应用程序添加路由
   1. 默认路由:`@app.route('/', methods=['GET'])`
3. 为网站创建HTML模板
   1. 需要将其添加在根目录的`templates`文件夹下
4. 测试应用程序
   1. 设置为调试运行:`set FLASK_ENV=development`
   2. 运行程序`flask run`
   3. 默认端口是5000
