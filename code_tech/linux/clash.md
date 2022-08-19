---
title: set system proxy via clash
tags: [software/Clash, proxy]
---

# linux配置使用clash作为网络代理

## 下载软件
- https://github.com/Dreamacro/clash/releases
- `wget`或`scp`

## 解压, 修改权限
- `gzip`
- 解压之后的结果应该是一个可执行文件, 但是权限不对
  - `chmod +x <executiveFile>`

## 配置文件
- 建议放在个人文件夹里, 路径为`~/.config/clash/`这里
- 需要一个`.yml`文件
  - 可以直接从已经下载好的电脑上copy, 不然配置内容需要重设, 比较麻烦
  - 比如说windows上的配置文件, 也在`~/.config/clash/`这个目录下

## 运行
- 逻辑是: 用`clash`可执行文件, 基于配置文件, 后台运行
- `sudo nohup /opt/clash-v1.7.1/clash -f ~/.config/clash/config.yml >> ~/.config/clash/nohup.out 2>&1 &`
  - 我是用的命令
- 使用`ps -def | grep clash`
  - 显示clash相关的进程
```bash
root      342540       1  0 09:18 ?        00:00:00 sudo nohup /opt/clash-v1.7.1/clash -f /home/username/.config/clash/ByWave.yml
root      342541  342540  0 09:18 ?        00:00:01 /opt/clash-v1.7.1/clash -f /home/username/.config/clash/ByWave.yml
username  366833  366414  0 10:25 pts/1    00:00:00 grep --color=auto clash
```
- 第一个是nohup进程
- 第二个是clash进程
- 第三个是grep进程(看到的时候应该已经自己消失了)