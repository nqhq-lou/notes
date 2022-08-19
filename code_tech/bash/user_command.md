---
title: User Management
tags: [shell/Bash, shell/user_management]
---

## 查看现在用户相关信息

- `cat /etc/<something>`
	- `passwd`
		- `nqhq314:x:1000:1000:,,,:/home/nqhq314:/bin/bash`
		- 账号名称 : 账号uid : 账户gid : 用户说说明 : 用户家目录 : shell解释器
	- `shadow`
	- `group`
	- `gshadow`
- `useradd` `usermod` `userdel`
	- 解释: 以上几条命令, 实际上是在`/etc/passwd shadow group`中增加或删除用户的相关记录
	- `-c`: comment, 指定一段注释性描述:question:
    	- 手工指定/etc/passwd文件中各用户信息中第 5 个字段的描述性内容，可随意配置；
	- `-d`: directory, 指定用户主目录. 如果此目录不存在, 可以同时使用`-m`选项创建之
    	- 主目录必须写绝对路径，而且如果需要手工指定主目录，则一定要注意权限；
	- `-m`	建立用户时强制建立用户的家目录。在建立系统用户时，该选项是默认的(really?)；
	- `-g`: 初始用户组, 指定用户所属的初始用户组
    	- 手工指定用户的初始组。一般以和用户名相同的组作为用户的初始组，在创建用户时会默认建立初始组。一旦手动指定，则系统将不会在创建此默认的初始组目录。\
	- `-G`: 附加用户组, 指定用户所属的附加组:question:
    	- 指定用户的附加组。我们把用户加入其他组，一般都使用附加组；
	- `-s`: Shell, 指定用户的登陆Shell, 默认是 /bin/bash
	- `-u`: 用户号, 指定用户的用户号. 如果同时有`-o`选项, 则可以重复使用其他用户的标识号.
    	- 手工指定用户的 UID，注意 UID 的范围（不要小于 500）
	- `-r`: 删除用户时把用户的主目录一起删除
	- `-e` 日期, 指定用户的失效曰期，格式为 "YYYY-MM-DD"。也就是 /etc/shadow 文件的第八个字段；
	- `-o` 允许创建的用户的 UID 相同。例如，执行 "useradd -u 0 -o usertest" 命令建立用户 usertest，它的 UID 和 root 用户的 UID 相同，都是 0
	- `-r` 创建系统用户，也就是 UID 在 1~499 之间，供系统程序使用的用户。由于系统用户主要用于运行系统所需服务的权限配置，因此系统用户的创建默认不会创建主目录。
- 例子
	- `useradd -d /home/nqhq -m nqhq -s /bin/bash`
		- 创建用户sam, 指定并创建其主目录
	- `useradd -s /bin/bash -g group -G adm,root nqhq`
		- 创建用户gem, 该用户登录Shell是`/bin/bash`, 它属于用户组group adm root, 其中group用户组是其主组
- 更多内容
	- http://www.blogjava.net/hello-yun/archive/2012/05/16/378295.html


## 将用户: 加入sudo; 添加到sudoers文件
- `usermod -aG sudo username`
- 加入sudo, 添加到sudoer文件夹
  - https://cloud.tencent.com/developer/article/1626815
- 修改文件`/etc/sudoers.d/username`
- `username  ALL=(ALL) NOPASSWD:ALL`
- `/%sudo/c %sudo  ALL=(ALL:ALL)  NOPASSWD:ALL`
  - 第一段：用户名或者用户组，表示谁有权限来使用后面的配置。%sudo代表sudo组下的所有用户
  - 第二段：表示来源地，即从哪执行这条命令。ALL表示所有计算机
  - 第三段：表示sudo可以切换到什么用户。ALL表示所有用户
  - 第四段：表示sudo可以切换到哪些组下的用户。ALL表示所有组
  - 第五段：表示sudo之后能够执行的命令。NOPASSWD:ALL表示执行任意命令都不需要密码
- `ALL=NOPASSWD:/bin/mkdir,/bin/chmod,PASSWD:/usr/bin/apt`
- `echo "<username> ALL=(ALL) NOPASSWD:ALL,PASSWD:/usr/bin/rm,/bin/rm,/usr/bin/rmdir,/bin/rmdir,/usr/bin/chmod,/bin/chmod" | sudo tee /etc/sudoers.d/<username>`

echo "nqhq ALL=(ALL) NOPASSWD:ALL,PASSWD:/usr/bin/rm,/bin/rm,/usr/bin/rmdir,/bin/rmdir,/usr/bin/chmod,/bin/chmod" | sudo tee /etc/sudoers.d/nqhq

# `WSL`的操作

## WSL系统重启
- 在管理员权限powershell
    - `net stop LxssManager`
    - `net start LxssManager`



