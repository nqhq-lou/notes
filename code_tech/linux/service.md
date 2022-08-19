---
title: Ubuntu service configurations
tags: [Linux/Ubuntu, Linux/service]
---

# ubuntu service config

## reference
- yffyyds! https://www.cnblogs.com/zwcry/p/9602756.html
- https://blog.csdn.net/blueicex2017/article/details/104207946
- https://blog.csdn.net/m0_50635229/article/details/109903087

## 服务文件描述
略

## 例子

### gitbook开机自启
- `/usr/lib/systemd/system/piraniGitbook.service`
```bash
[Unit]
Description=Start Pirani Gitbook and serve to port 4000
After=systemd-networkd-wait-online.service
After=networking.service  # gitbook dependes on network service
Conflicts=shutdown.target

[Service]
Type=oneshot
WorkingDirectory=/media/piraniDoc/
ExecStart=/usr/bin/bash /media/piraniDoc/piraniGitbookInit.sh
RemainAfterExit=yes
TimeoutSec=0

[Install]
Alias=piraniGitbook
```
- `systemctl enable /usr/lib/systemd/system/piraniGitbook.service`
  - 设置开机启动
- `systemctl start piraniGitbook.service`
  - 启动这个任务
- `systemctl status piraniGitbook.service`
  - 查看任务状态
- `systemctl is-enabled piraniGitbook.service`
  - 查看是否按开机启动
