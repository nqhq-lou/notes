---
title: WSL Configurations for Beginners
tags: [Linux/WSL]
---

- MacOS用户退散:smiley:, 本身就是类Unix系统了
- 本文的主要内容为
	- 希望达到的目标为: 让几个月前的自己在对这方面毫无了解时能够快速上手
	- 对`WSL`系统的描述, 与安装过程的基础, 命令行的基础使用
	- `WSL`与`VSCode`的本地连接 / `ssh`连接
	- 连接后实现`WSL`中`C/C++`的开发环境
	- `vim`基础用法(所以这个有什么好处吗)
	- 左光宏老师"C语言程序设计"课中一些问题的解释(放在其他地址了, 比如`OpenMP`和`EasyX`)
	- 
- 感觉没有完全解释清楚的地方
	- 标注:exclamation:的地方
	- `WSL`子系统的实现方式, 与完全系统的对比
- [MSFT官方文档](https://docs.microsoft.com/zh-cn/windows/wsl/)

## 简介
- Windows subsystem for linux
	- 可以体验全套linux命令行， 进行coding操作
	- 妈妈再也不用担心我装双系统电脑装坏了呢~
- 踩坑过程中常常因为某些地方叙述不清楚而gg
	- 本文尝试做到详略得当
	- 虽然自己也不清楚是怎么把`WSL`搞得能用的
	- 如果仍然不懂, 可以继续上网查
- 本文亦可作为
	- 把`WSL`搞死了之后(很不幸彻底搞死了), 重装的备忘录
- 本文内容包括
	- `WSL`安装 & 初始设置
	- 命令行基本逻辑
	- 如果不了解`VSCode`的基础情况, 详见不存在的介绍(kk和zz还没有写完)
- 欢迎补充!!!(特别是:question:标注部分)
	- 自己本身不是很了解`Linux`, 所以有错的地方跪求纠正
	- 补充时麻烦进行明显的标注, 因为本文档是从`.md`文件中转过来的, 每次更新会直接覆盖之前的全部内容, 所以麻烦进行明显标注方便保留.
	- `.md`文件储存位置: nqhq的`SurfacePro6@C:\Coding\Linux\WSL\beginners.md`

## 安装 & 基础设置
- 前提操作
	- 管理员权限`powershell`运行命令
		- 对:exclamation:
		- `Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux`
	- 控制面板
		- :exclamation:
		- 控制面板->程序和功能->启用或关闭Windows功能->(勾选)适用于Linux的Windows子系统
	- 需要重启电脑
- Microsoft Store
	- 到Microsoft Store里搜索`Ubuntu`
	- 安装`LTS`版本(本文基于20.02LTS)
		- long time service
	- 也可以去MSFT网页上找安装包, 这样可以安装到`D:/`盘里.
- 安装成功后打开
	- 显示`Installing...(忘记了)...`, 大概等2min
	- 显示设置用户界面, 按顺序设置用户名, 用户密码, 二次确认密码
		- 注意:question:
	- 更新和升级
		- `sudo apt-get update && sudo apt-get upgrade`
		- `update`下载新软件包, `upgrade`升级下载的新软件包
- 关于换源
	- `WSL`需要安装软件, 是通过向指定的库进行调用:question:
	- :exclamation:一定记得备份原来的源文件!
		- `sudo cp /etc/apt/sources.list /etc/apt/sources.list.bak`
		- `sudo`: 超级管理员权限, `cp`: copy, 带`/`的东西: 文件地址
	- 可以选择清华, 科大, 阿里云等等的源, 网上有详细介绍
		- 似乎换源会引发文件依赖性问题, 但是并不确定, 而且学校网速可以接收
	- 挂vpn换源好像不管用!
- 如何重置: 如果觉得`WSL`真的:boom:死了(并且心:broken_heart:也死了)
	- 在`Start Menu`里对图标击右键, 选择`应用设置`
	- 找到`重置`icon并且点击, 就已经重置了
	- 或者即使备份`WSL`, 详见下一节
- 关闭/重启`WSL`
	- powershell管理员
	- `net stop LxssManager`
	- `net start LxssManager`
	- 或者`wsl -t <DistributionName>`(后面会说到)
- 注册表中的位置
	- `计算机\HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Lxss\`

## WSL备份
- 划重点: `powershell`下 `wsl export/import`
	- 所有的操作都在Windows的`powershell`里进行
- 备份子系统
	- `wsl --help` 查看可用选项
	- `wsl -l -v` 查看正在运行的分发版(Distribution)
		- 注意, 名字可能为`Ubuntu`, 也可能很长, e.g.`Ubuntu-20.04-20210101`
		- 比如, 我安装的版本的DistributionName就是`Ubuntu`
	- `wsl -t <DistributionName>` 注销这个分发版的`WSL`
	- `wsl --export <DistributionName> <FilePath>`
		- e.g. `wsl --export Ubuntu C:\Users\louze\Downloads\Ubuntu-20210201.tar`
	- 推荐导出为`tar`格式, 至于为什么, 不知道
- 删除子系统
	- `wsl --unregister <DistributionName>`
- 还原子系统
	- `wsl --import <DistributionName> <InstallLocation> <FilePath>`
	- 此时默认用户会是`root`而不是个人用户, 会影响vscode使用, 需要解决
		- 在注册表中找到`\HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Lxss\DefaultUid`
		- 修改为个人id的值(通过`id <UserName> -u`查看)
- 其实, 这个方法可以用来在不同的存储器中转移`WSL`(或者在别人的电脑上安装自己的)
	- 参考文章: [WSL备份还原子系统](http://xfy-learning.com/2020/05/30/WSL%E5%A4%87%E4%BB%BD%E4%B8%8E%E8%BF%98%E5%8E%9F/)

## 文件结构 & 命令行基本逻辑
- 结构
	- `<尖括号>`为必选项目的项目, `(圆括号)`标记可选项目
	- `<命令> <附加> <对象地址>`
		- `rm -rf /`(对不起这是个错误示范, 千万不要使)
		- `cd /`和`cd ~`
	- `(sudo) <应用> <对象地址>`
		- `sudo apt-get install sshd`(然而这个还没搞定)
- 一些常用命令
	- 安装软件: `sudo apt-get install <deb name>`
	- `su <username>` 换个用户登录
- 待补充:stuck_out_tongue_closed_eyes:
- 不懂的问题(求解答:flushed:)
	- `apt install`和`apt-get install`的区别?
	- `deb`软件包的实现?

## C/C++ 配置
- `VSCode`和`WSL`结合, 可以实现极佳的`C`/`C++`调试体验
	- 通过`GNU`的`gcc` `g++` `gdb`进行
	- 通过`VSCode`中插件`Remote - WSL`进行连接.
	- 如果不熟悉`VSCode`基础操作, 见网页
- 前提
	- 确保电脑上已经安装了`VSCode`
	- 在`WSL`命令行, 对应的所在目录里输入`code .`, 自动切换到`VSCode`里
		- 爽, 不用手动配置了
		- `VSCode`打开`bash`: 快捷键(ALT加`)(后者在键盘左上角)
- 安装: 在`bash`中使用`sudo apt-get install`加上要安装的东西
	- 如`sudo apt-get install gcc`
	- `build-essential` `gcc` `g++` `gdb` `cmake`
		- `libboost-all-dev`是干什么的?
	- 通过查看版本, 检查是否安装成功
		- `gcc -v`, `g++ -v`, `gdb -v`
		- `cmake --Version`
	- 有可能已经安装过了, 关注一下检查版本时的情况
- 安装: `VSCode`中的插件
	- C/C++, C++ Intellisense, CMake, Cmake Tools
- `gdb`的使用
	- 自动创建即可, 注意选择需要的方式
	- 使用`whereis g++`命令查看g++在的位置, 推荐使用`/usr/bin/g++`路径
	- 可能出现缺少文件:
		- 无法打开“random.c”: 无法读取文件'vscode-remote://ssh-remote+314/build/glibc-ZN95T4/glibc-2.31/stdlib/random.c'
		- [解决方法](https://blog.csdn.net/yihuajack/article/details/107151801)
		- 注意`N95T4`和`2.31`
- 参考文献
	- [来自知乎](https://zhuanlan.zhihu.com/p/135225476)

## `VSCode` 远程连接 `WSL`
- 通过`ssh`连接, 搭配`VSCode`插件
	- :exclamation: 需要更加详细描述
- 重装`openssh-server` (据说可能有一定问题)
	- `sudo apt-get remove openssh-server`
	- `sudo apt-get install openssh-server`
- 编辑`\etc\ssh\sshd_config`
	- 注意要编辑的文件是`sshd_config`! 有`d`
	- 使用`vim`编辑
		- 还不会
	- 使用`nano`编辑
		- `sudo nano \etc\ssh\sshd_config`
		- 每行`#`开头为被注释掉
		- 修改三行(所以这个文件可以叫做设置文件吗?)
			- `Port 2222`
			- `PermitRootLogin yes`
			- `PasswordAuthentication yes`
			- 为什么端口不用自带的`22`: 因为`Windows`中`22`有其他用处, 需要避开
		- 同时按下`Ctrl`+`O`(是字母O), 然后`Enter`保存
		- 同时按下`Ctrl`+`X`退出`nano`编辑器
- 重启服务 `sudo service ssh --full-restart`
- 查询`WSL`的`ip`
	- 使用`net-tools`工具: `sudo apt-get install net-tools`
	- 命令行查询: `ifconfig`
		- 第二行(?) `inet`后为`ipv4`
- 使用`VSCode`连接
	- 使用插件, 直接安装`Remote Development`, 它附加四个插件(一次性装五个插件)
		- 包括`Remote - SSH`(要用的), `Remote - WSL`(本机连接`WSL`要用的), `Remote - Containers`(`Docker`要用的)
			- `Remote - SSH`会附加`Remote - SSH: Editing Configuration Files`
	- 对`Remote - SSH`配置文件
		```
		Host myWSL    // 实例名, 随便取, 简单最好
		Hostname 10.10.10.10    // 刚刚的inet ipv4
		Port 2222   // 刚刚配置的端口
		User cupt   // 想连接的用户的名称(一开始设置的), 也可以是root
		IdentityFile <DirName>  // 密钥路径, 没有也行, 没搞懂怎么用
		```
- 不单单可以用`VSCode`连接
	- 在`Windows powershell`里`ssh <username>@<ipv4>`
	- 例如: `ssh cupt@10.10.10.10`
	- 但是怎么指定端口为`2222`?
- 目前的问题
	- 有些教程中说要设置防火墙的出入站规则? 没设置好像也行?
	- 如何在校外不使用VPN就能连接校内某台电脑的WSL?
	- 如果WSL所在的电脑网络连接为WiFi, 那么即使校内也连不上去. 怎么解决?
	- Windows端ipconfig和WSL端ifconfig的inet的ipv4不一致: 见下
- Windows端ipconfig和WSL端ifconfig的inet的ipv4不一致
	- 在powershell管理员里执行
		- `netsh interface portproxy add v4tov4 listenaddress=0.0.0.0 listenport=2222 connectaddress=[IP] connectport=[PORT]`
			- 这里[IP]为WSL的ifconfig的ipv4, [PORT]我自己取2222
		- `netsh advfirewall firewall add rule name=WSL2 dir=in action=allow protocol=TCP localport=2222`
			- 这一步为配置防火墙
	- 然后解决了

- vncserver安装


## `vim` 怎么用
- 金光闪闪的大佬编辑器
	- 是`vi`的升级版
	- 命令行输入`vimtutor`进入快速学习的文档, 建议打开拷贝的版本
- 基础操作
	- 两种情况, INSERT模式和Normal模式, 使用`i`和`Esc`进行切换
	- `hjkl` 左下上右
	- Normal模式和INSERT模式之间的切换
		- `i`和`Esc`
		- Normal模式下
			- `:q!`退出而不保存
			- `:wq`退出并保存
			- `x`键删除下面的字符
			- `dw`, `d$` (叙述见后)
		- INSERT模式下
			- 相应的还有append模式`A`, 在一行的末尾输入
			- 注意必须是大写的`A`!!!
- UNDO / REDO:
	- `u`撤销, `U`撤销一整行
	- `Ctrl-R`: 重做一次
- motion: `w` `e` `#` `$`
	- 光标的移动
	- `w`移动到下一个(词的开头)
	- `e`移动到下一个(词的结尾)
	- `#`移动到本行开始(??这条存疑)
	- `$`移动到本行结尾
		- 上面两句话注意断句
- operator: `d`开头的命令
	- `d`=`delete`, 操作为`d`+`另一个符号`
	- `dw`删除, 到下一个词, 不留空格
	- `de`删除, 这个词删完, 留下空格
	- `d$`删除(从此处)本行直到结尾
	- `dd`删除本行
	- `x`键删除下面的字符
	- 被删除的内容都会被储存
		- `p`将刚刚删除储存的内容输出
- operator: `r` replace
	- `r<x>`用`x`替代光标下的字母
- operator: `c` change
	- `ce`修改这个词
	- `c<n>e`用上count
	- 会导致变更到`INSERT`模式
- count: 重复n次
	- motion前数字
	- `2w`向后移动过两个字
	- `2dd`删除两行
	- 不明白`d2w`是什么意思

## 其他的零零碎碎
- 在一个终端查看另一个终端的输出: `reptyr`
- `markdown`转`wikidoku`: `$ pandoc -f gfm -t dokuwiki <filename.md> -o <filename.txt>`
	- 需要先安装pandoc
- [Win10 Terminal + WSL2](https://www.cnblogs.com/willick/p/13924325.html)
	- 升级WSL2: 自己搜搜就好
- 手动安装某个包的例子
	- [手动安装Node.js](https://blog.csdn.net/darkwindzzh/article/details/82192704)

## 一个目标
- 装上远程vnc桌面: [WSL2 with GUI using Xvnc](https://gist.github.com/tdcosta100/385636cbae39fc8cd0937139e87b1c74)
	- 但是自己还没有尝试

## WSL2配置
- 足够详细: [Winux之路-WSL 2的使用及填坑](https://zhuanlan.zhihu.com/p/224753478)
- 希望可以vnc桌面: [WSL2 with GUI using Xvnc](https://gist.github.com/tdcosta100/385636cbae39fc8cd0937139e87b1c74)
- Warning: 除非你的电脑缓存足够大(16GB), 才能够有效运用带桌面的linux, 不然电脑跑不动
	- surface用户哭了


