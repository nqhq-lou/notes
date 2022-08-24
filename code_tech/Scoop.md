---
title: scoop basics
tags: [software/scoop]
---

# 关于`scoop`的入门


## 介绍
- 是不是被windows中下载软件的各种奇妙操作耍花眼?
- 你需要一个**干干净净**的安装器!
- 但是这个安装器还不是很完善
  - 软件不全, 不是很坚不可摧, 系统权限方面不尽如人意


## 安装
- 首先修改用户权限
- 然后通过`iex`安装
- 详见文末链接

## 设计理念
- 暂时还不是很了解
- bucket可以理解为软件源


## 基础使用
- 通过`scoop help`查看
- 注意: 应该即使备份`scoop/apps/scoop`文件夹, 不然某次`update`失败之后会出问题

### 常用命令
```text
scoop help #查看帮助
scoop help <某个命令> # 具体查看某个命令的帮助

scoop install <app>   # 安装 APP
scoop uinstall <app>  # 卸载 APP

scoop list  # 列出已安装的 APP
scoop search # 搜索 APP
scoop status # 检查哪些软件有更新

scoop update # 更新 Scoop 自身
scoop update appName1 appName2 # 更新某些app
scoop update *  # 更新所有 app （前提是需要在apps目录下操作）

scoop bucket known #通过此命令列出已知所有 bucket（软件源）
scoop bucket add bucketName #添加某个 bucket

scoop cache rm <app> # 移除某个app的缓存
```

### bucket操作
```text
# bucket的用法
scoop bucket add|list|known|rm [<args>]

scoop bucket add extras  # 官方的bucket

scoop bucket add dorado https://github.com/h404bi/dorado  # 非官方的bucket

scoop install dorado/<app_name>  # 从某个bucket中安装软件
# 下面是dorado中特有的软件，测试其是否添加成功
scoop search trash
```

### 安装卸载程序
```text
# 安装之前，通过 search 搜索 APP, 确定软件名称
scoop search  xxx

# 安装 APP
scoop install AppName

# 安装特定版本的 APP；语法 AppName@[version]，示例
scoop install git@2.23.0.windows.1

# 卸载 APP 
scoop uninstall #卸载 APP
```

### 更新软件
```text
scoop update # 更新 Scoop 自身

scoop update appName1 appName2 # 更新某些app

# 更新所有 app （可能需要在apps目录下操作）
scoop update *

# 禁止某程序更新
scoop hold <app>
# 允许某程序更新
scoop unhold <app>
```

### 清除缓存和旧版本
```text
# 查看所有以下载的缓存信息
scoop cache show

# 清除指定程序的下载缓存
scoop cache rm <app>

# 清除所有缓存
scoop cache rm *

# 删除某软件的旧版本
scoop cleanup <app>

# 删除全局安装的某软件的旧版本
scoop cleanup <app> -g

# 删除过期的下载缓存
scoop cleanup <app> -k
```

### 别名
```text
# 可用操作
scoop alias add|list|rm [<args>]

## 添加别名，格式：
scoop alias add <name> <command> <description>

# 示例：（注意：必须在 Powershell中运行）
scoop alias add st 'scoop status' '检查更新'
# 检查已添加的别名
scoop alias list -v

Name Command      Summary
---- -------      -------
st   scoop status 检查更新

# 测试已添加的别名 st
scoop st


# 另一个示例：
scoop alias add rm 'scoop uninstall $args[0]' '卸载某 app'
```

### 切换程序不同版本
```text
scoop reset [app]@[version]

scoop reset idea-ultimate-eap@201.6668.13

scoop reset idea-ultimate-eap@201.6073.9

# 切换到最新版本
scoop reset idea-ultimate-eap
```


## git pull proxy error

- [Git - SSL_ERROR_SYSCALL 问题解决](https://blog.hyperzsb.tech/git-ssl-error/)

使用 HTTPS 代理
在使用 HTTPS 连接 GitHub 进行 push/pull 时（即 origin 地址为 `https://github.com/xxx/xxx.git` )
需要更改本git 的配置，使用代理向 GitHub 发起请求.
执行如下命令:

```bash
$ git config --global -e
```
这将进入 git 的配置文件编辑界面（将使用 git 指定的默认编辑器打开）。
在该文件中加入如下内容：
```text
[http]
        proxy = socks5://127.0.0.1:7891
[https]
        proxy = socks5://127.0.0.1:7891
```

其中“7891”为你的代理软件的指定出入端口，请根据实际情况自行修改。


## 注意事项
- ``scoop``会对自己进行升级, 在这个过程中他好像会去给自己搬家
  - 如果强制要求停止, 那么`scoop`就废掉了
  - 所以尽量给`scoop`设置好网络代理, 防止因为网络不通而出现问题
- ``scoop``还在发展中, 多多见谅, 虽然我不是开发者
- 如果下载了`aria2`, 可能会在下载中出现一些问题
  - 使用`scoop config aria2-enabled false`取消`aria2`下载



## 参考文献
- [「一行代码」搞定软件安装卸载，用 Scoop 管理你的 Windows 软件 from zhihu](https://zhuanlan.zhihu.com/p/54822449)
- [你需要掌握的scoop技巧和知识 from zhihu](https://zhuanlan.zhihu.com/p/135278662)


