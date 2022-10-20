---
title: jupyterlab remote
tags: [software/jupyterlab]
---

# 远程使用`jupyterlab`

## 完成逻辑
- 修改`jupyterlab`的配置文件(`ServerApp`)部分
- 登录验证: 对于自己想用的密码, 生成sha加密结果, 放在上述配置文件中

## 安装

### 安装`pip`
- 通过命令行安装, 从`pypa`下载
  - `https://bootstrap.pypa.io/get-pip.py`
- 然后运行这个脚本, 记得`sudo`

### 安装`jupyterlab`
- 个人推荐`sudo`, 虽然并不完全确定这样对不对
- `sudo pip install jupyter`
- `sudo pip install jupyterlab`

## 操作

### 生成密码

- 用module`notebook.auth`的`password()`方法生成
  - 在REPL界面进行如下操作
    ```python
    >>> from notebook.auth import passwd
    >>> passwd()
    Enter password: (这里是你想要的密码, 输入是不可见的)
    Verify password: (repeat)
    'argon2:.xxxxxxxxxxxxxxx'
    ```
  - 把最后`'argon2:.xxxxxxxxxxxxxxx'`复制下来, 后面代用
- 后面用的时候要加上u! (可能不是很需要)
  - 意思是unicode

### 生成配置文件
```bash
nqhq@VM-12-13-ubuntu:~$ jupyter lab --generate-config
Writing default config to: /home/nqhq/.jupyter/jupyter_lab_config.py
```

### 修改配置文件
- 需要修改五个地方
1. `c.ServerApp.allow_remote_access = True`
   - 允许远程连接
2. `c.ServerApp.ip = '*'`
   - 允许来自任意ip连接
3. `c.ServerApp.open_browser = False`
   - 不自动打开浏览器
4. `c.ServerApp.password = u'argon2:.xxxxxxxxxxxxxxx'`
   - 这里是刚刚生成的密码
5. `c.ServerApp.port = 9999`
   - 指定一个连接端口, 不冲突即可

