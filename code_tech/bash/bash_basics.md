---
title: Linux Shell Commands
tags: [shell/Bash]
---
- 尖括号内为应有的内容
	- `<dir>` 路径名称/档案名称
		- `/home/nqhq`
	- `<f1>` 第一个文件的名称(带路径或者相对路径)
		- `/home/nqhq/C/HelloCpp.cpp`
		- 或者当前工作目录已经在`/home/nqhq/C`下 `HelloCpp.cpp`
- 方括号内为可选内容
	- 但是下文中没出现, 这个是C程设老师的记录习惯(好像也是`man`mannual里的习惯)

## `Shell`是什么
- 命令解释器, 提供了用户和系统之间交流的方式

## Directory
- `ls` = list
	- `ls <dir>`
	- `-a` = all, 显示隐藏档(以`.`开头)
	- `-l` = long, 查看更加详细信息
		- 十个字符: property, user/group/other的rwx权力
	- 还有`l` `ll`但是不知道是干什么的
	- `lsblk` print block devices by their assigned name (but not RAM) on the standard output in a tree-like fashion
		- 可选参数 `-l`
- `cd`
	- `cd <dir>` 转移工作目录
- `cp` = copy
	- `cp <f1> <f2>` 把1复制到2
	- `cp <f1> ... <fn> <dir>` 把f1-fn复制到dir
	- `-i` = interactive, 如果已经有同名f2, 复制前先询问, 复制等于覆盖
	- `-r` = repeat递回式, 将一整颗子树都复制到另一个目录中
		- `cp -r <dir1> <dir2>` 把dir1的全部内容复制到dir2
- `mv` = move
	- `mv <f1> <f2>` 将f1的内容移动到f2中(有可能已经有一个f2了)
	- `mv <dir1> <dir2>` 将dir1的内容移动到dir2中
	- `mv <f1> ... <fn> <dir>` 将f1-fn移动到dir
	- `-i` = interactive
	- `-f` = force强迫
- `mkdir` = make directory
	- `mkdir <dir1>` 可以创建多个目录
- `rmdir` = remove directory
	- 如果是个空目录, 下面没有档案
- `touch`
	- `touch <f1>` 创建文件
- `pwd`
	- 显示当前工作目录的路径path
	- UNIX系统中为`/`, DOS中为`\`
- `cat` / `more` / `less`
	- `cat <f1>` = concatenate连成串, 显示档案内容
		- `-n` 显示出来的内容加上行号
		- `cat <f1> <f2> <f3> >> <f4>` 将f1-3合并为f4
	- `more <f1>` 按空格翻到下一页, 按`q`退出
	- `less <f1>` 可以用pageup/pagedown/space翻页, up/down动一行
		- 推荐使用`less`
- `chmod` = change mode
	- `chmod X+Y <f1>`
		- `X` 改变的群组: `u`user, `g`group, `o`others, `a`all
		- `Y` 改变的权力: `r`read, `w`write, `x`execute
		- `x`包括删除本档案的权力
			- 使用`ls -l`查看权限情况
	- `chmod X-Y <f1>`
		- 现在明白了`+`代表什么意思了, 所以`-`意为删除权限
	- `chmod XXX <f1>` (更加方便的命令!)
		- r = 4, w = 2, x = 1, 加起来是一个0-8的数字
		- 三个数字依次指定: user, group, others
		- `chmod 754 <f1>` -> `-rwxr-xr-- 1 nqhq nqhq <date>`
- `chown` = change file owner and group
	- 每个文件都属于a group of user和a owner, 使用`ls -l`查看
	- `chown <group>:<user> <f1>`
- `md5sum`
	- `md5sum <f1>` 检查文件的hash, 确定传输无误
- `dd`
	- 拷贝文件

## Process
- `ps` = process, 显示你的和系统的进程状况
	- `-e` 也列出其他users的进程状况
	- `-f` 列出详细信息
	- `-u` `-x` `-w`
- `top` = 上帝视角?
	- 实时更新的系统进程状态汇总
	- `q` 退出
	- `d` 改变更新时间
	- `1` 查看每个cpu情况
- `kill` / `pkill` / `killall`
	- `kill <PID>` 杀掉这个PID的进程
	- `pkill <programname>` 杀掉这个名称的进程
	- `killall <programname>` 杀掉所有该名称进程
- `history`
	- 显示所有执行过的命令
	- `Ctrl + R` 搜索已经执行过的命令
- `apt` = advanced package tool
	- 对基于Debian的系统的高级安装工具, 自动搜索/安装/更新/解析依赖性
	- `apt-cache` 找到包括某个sub package的package
	- `apt-get` 安装/更新所有包到最新版

## String
- `date`
	- `date --set-'14 may 2021 07:00` 修改日期
- `cal [month year]`
- `echo`
	- 显示一串字符串在terminal上
	- `echo Hello!`
- `grep` = 过滤器?
	- 自一个或多个档案中过滤出具有某个字符串的行, 或是自标准输入过滤出具有某个字符串的行. 一般配合其他命令使用
	- `ls |grep bio` 显示当前目录下, 所有包含`bio`的文件和文件夹
	- `cat <f1> |grep "atom" ><f2>` 将f1中所有包含`"atom"`(带""!)的行按先后写入f2中(覆写)
		- `>`改成`>>` 变为接着f2原来的内容写

## User
- `passwd`
	- 修改密码, 注意Unix的密码是不会显示出来的
- `chsh`
	- 更改登录shell
- 登录和传输文件: Putty
- 其他的方法: FTP
	- 但是怎么用?
- `uname` = Unix name
	- print detailed information about the machine name, Operating System and Kernel
	- `uname -a`
- `sudo` = super user do
	- "To err is human, but to really foul up everything, you need root password."

## Others
- `sed`, `awk`, `grep`, `xargs`, `cut`, `paste`, `sort`, `uniq`

## Compile
- GCC
	- `gcc`是一款C语言编译器,  属于GNU项目
	- `gcc <sourcefile.c> [-Wall] [-lm] [-On] [-o <outputfile>]`
		- `-Wall` 打开警告
- G++
	- `g++`是一款C语言编译器,  属于GNU项目