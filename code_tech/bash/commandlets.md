---
title: commandlets in linux
tags: [Linux/cmd]
---

## grep

[generals on regex](https://www.runoob.com/linux/linux-comm-grep.html)
[use regex in grep](https://phoenixnap.com/kb/grep-regex)


## ps - process status

-  -A 列出所有的进程
-  -w 显示加宽可以显示较多的资讯
-  -au 显示较详细的资讯
-  -aux 显示所有包含其他使用者的进程
- -au(x) outputs
	- `USER PID %CPU %MEM VSZ RSS TTY STAT START TIME COMMAND`
- show most mem(4) / cpu(3) costy processes
	- `ps aux | sort -rnk 4 | head -5 | grep '^[[:alnum:] +./:]\+[0-9]\+:[0-9]\+' -o`


## tar

https://cloud.tencent.com/developer/article/1404921

- 仅打包 & 解包
	- `tar -cvf test.tar ./test/`
	- `tar -xvf test.tar`
- 压缩 & 解压
	- `tar -czvf test.tar.gz ./test/`
	- `tar -xzvf test.tar.gz`


## ln - link

`ln -s [tolink] [thelink]`

- `ln –s /var/www/test test
	- link `/var/www/test` to `test` in current dir


## find & xargs

- delete by type
	- `find -type f | xargs rm -f`
- delete by user
	- `find -user [usrname] | xargs rm -f`



## awk




## disk revelant


### df
- 按照指定格式显示系统中已安装的文件系统的使用情况
	- [Linux df 命令 from runoob](https://www.runoob.com/linux/linux-comm-df.html)
- `-h`: human-readable
- `-a`: 显示所有文件系统信息


### du
- 按指定单位统计文件或目录的大小
	- [Linux du 命令 from runoob](https://www.runoob.com/linux/linux-comm-du.html)
- `du -sh ./* | sort -rhk 1`
	- 查看按用户的本文件夹用量
- `du -h /home/zhangsan`: 列出每个子目录的大小
- `du -h -d 0`: 显示当前一级目录信息


