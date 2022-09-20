---
title: compile source code
tags: [git]
---


- 下载对应包, 在[git/git from GitHub]([https://github.com/git/git/tags](https://github.com/git/git/tags "https://github.com/git/git/tags"))
- 解压tar.gz到想要的目录下
	- 如我解压出来了`git-2.xx.x`放在了`~/opt`
- 在解压后的文件夹中`make`
	- `make prefix=[path] install`
- 在`[path]`中就会有`bin`里面是程序了

## references
- [# Linux CentOS 8.x 安装Git](https://blog.csdn.net/hkl_Forever/article/details/126914915)