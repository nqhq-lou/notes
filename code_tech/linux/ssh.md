---
title: ssh chaos
tags: [shell/ssh]
---

# ssh琐事

## `ssh-keygen`
- 钥匙名称无所谓
- 公钥需要放在服务器的authorized_keys里面, 必须是这个文件名称, 权限600
- 然后配置本地`~/.ssh/config`文件

## quickref
- `ssh-keygen -t rsa -b 1024 -f yourkeyname -C "comment"`
- `ssh -L 6006:127.0.0.1:6006 admin@192.168.31.53`
	- 创建管道连接
- `ssh-keygen -t ed25519 -C "comment"`


****