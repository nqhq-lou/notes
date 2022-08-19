# HPC note

## commandlines
- `pestat`: see to the running state of the group

## Docs
- [中科曙光](https://www.sugon.com/download/lists?zl=1&product_model=ParaStor300S&zl=3)

## Auto 2 Internet
```bash
cat fd-net-auth.sh
#!/bin/bash

URL="https://10.108.255.249/include/auth_action.php"
username=[yourid]
password=[yourpasswd]
ip=[youripaddress]

curl $URL --insecure --data "action=login&username=$username&password=$password&ac_id=1&user_ip=$ip&nas_ip=&user_mac=&save_me=1&ajax=1" > /dev/null 2>&1

# 用户名和密码以及ip用自己的替换掉.
# 另外可能需要写入/etc/crontab后每天自动运行一遍.
```
- 这台电脑上不是`cron`， 是`crond`
- `service crond status` 检查是否运行, 使用`ntsysv`修改是否开机启动
- referneces
    - [Linux之定时任务Crond详解 from jb51](https://www.jb51.net/article/113308.htm)
    - [Linux基本操作--Crond定时任务 from CSDN](https://blog.csdn.net/qq_22172133/article/details/81263736)
    - 


## `Crond`定时任务
- Intro
    - `Crond`是linux系统中用来定期执行命令/脚本或指定程序任务的一种服务或软件
    - Crond服务会定期(默认1min检查一次)检查系统中是否有要执行的任务工作
    - 必须保留的启动服务:
        - crond: 定时任务服务
        - network:网络服务
        - rsyslog:日志服务
        - sshd:远程链接服务
        - sysstat:系统监控服务
    - 一句话检查依上服务情况
        - `chkconfig --list | egrep -v "crond|network|rsyslog|sshd|sysstat" | awk -F " " '{print "chkconfig",$1,"off"}' | bash`
        - 但是不知道为什么`sysstat`服务似乎有问题, 无法检查, `service sysstat status`没有返回值
        - `chkconfig --list | grep 3:on`


## scp usage note
- 基础命令模式
    ```bash
    scp [-1246BCpqrv] [-c cipher] [-F ssh_config] [-i identity_file]
        [-l limit] [-o ssh_option] [-P port] [-S program]
        [[user@]host1:]file1 [...] [[user@]host2:]file2
    ```
    - `-r`: 递归整个目录
    - `-P port`: 指定端口
- 本地到远程
    - 文件复制
        - `scp local_file remote_username@remote_ip:remote_folder`
            - 指定了远程的目录, 所以复制过去文件名字不变
        - `scp local_file remote_username@remote_ip:remote_file`
            - 指定了远程的文件名
    - 目录复制
        - `scp -r local_folder remote_username@remote_ip:remote_folder`
- 远程到本地
    - `scp remote_username@remote_ip:remote_folder local_file`
    - `scp remote_username@remote_ip:remote_file local_file`
    - `scp -r remote_username@remote_ip:remote_folder local_folder`




