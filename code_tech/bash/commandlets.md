---
title: commandlets in linux
tags: [Linux/cmd]
---


## ls

```bash
Usage: ls [OPTION]... [FILE]...
List information about the FILEs (the current directory by default).
Sort entries alphabetically if none of -cftuvSUX nor --sort is specified.

Mandatory arguments to long options are mandatory for short options too.
  -r, --reverse              reverse order while sorting
  -t                         sort by modification time, newest first
```


## grep

[generals on regex](https://www.runoob.com/linux/linux-comm-grep.html)
[use regex in grep](https://phoenixnap.com/kb/grep-regex)


## top

### sort by
- `M` for memory usage
- `P` for CPU usage

### interaction keymap
```txt
c: 显示完整的命令
d: 更改刷新频率
f: 增加或减少要显示的列(选中的会变成大写并加*号)
F: 选择排序的列
h: 显示帮助画面
H: 显示线程
i: 忽略闲置和僵死进程
k: 通过给予一个PID和一个signal来终止一个进程。（默认signal为15。在安全模式中此命令被屏蔽）
l: 显示平均负载以及启动时间（即显示影藏第一行）
m: 显示内存信息
M: 根据内存资源使用大小进行排序
N: 按PID由高到低排列
o: 改变列显示的顺序
O: 选择排序的列，与F完全相同
P: 根据CPU资源使用大小进行排序
q: 退出top命令
r: 修改进程的nice值(优先级)。优先级默认为10，正值使优先级降低，反之则提高的优先级 
s: 设置刷新频率（默认单位为秒，如有小数则换算成ms）。默认值是5s，输入0值则系统将不断刷新
S: 累计模式（把已完成或退出的子进程占用的CPU时间累计到父进程的MITE+ ）
T: 根据进程使用CPU的累积时间排序
t: 显示进程和CPU状态信息（即显示影藏CPU行）
u: 指定用户进程
W: 将当前设置写入~/.toprc文件，下次启动自动调用toprc文件的设置 <: 向前翻页 >: 向后翻页
?: 显示帮助画面
1(数字1): 显示每个CPU的详细情况
```

### more things
- to be updated






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
	- `tar -xzvf test.tar.gz -C [decompress/to/this/dir]`
- 分卷压缩与解压, 使用`split`
	- 先压缩, 再分割
		- 压缩略
		- 分割: `split -a 2 -d -b 100m [tarname].tar.gz [tarname].tar.gz.`
			- 结果为形如`[tarname].tar.gz.00`
		- 合并: `cat [tarname].tar.gz.* > [tarname].tar.gz`
		- 解压略
	- 分割与压缩
		- `tar -czvf - [file|dir] | split -a 2 -d -b 100M - [tarname].tar.gz.`
			- 后缀两位数字, 形如`[tarname].tar.gz.00`
		- `cat [tarname].tar.gz.* | tar -zxvf -`
			- 自动按顺序合并?

```bash
tar -czvf - QM7_output_raster | split -a 2 -d -b 2G - QM7_output_raster_split_tar/QM7_output_raster.tar.gz.
```



## ln link

`ln -s [tolink] [thelink]`

- `ln –s /var/www/test test
	- link `/var/www/test` to `test` in current dir

- 更新: `ln -snf [source] [target]`



## find & xargs

- delete by type
	- `find -type f | xargs rm -f`
- delete by user
	- `find -user [usrname] | xargs rm -f`



## awk
- to be updated



## disk relevant

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


