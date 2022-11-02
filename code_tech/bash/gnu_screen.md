---
title: GNU screen
tags: []
---


## resources
- for official sites, see [GNU Screen](https://www.gnu.org/software/screen/)
- source code: [Index of /gnu/screen](https://ftp.gnu.org/gnu/screen/)
- installation: [手动安装screen](https://blog.csdn.net/computerme/article/details/80154666)

## install

```bash
# 解压tar.gz
# 在解压后的安装目录中
./autogen.sh  # 配置初始内容, 产生config文件
./configure  --prefix=[path/to/install]  # 检查环境
make
make install
```


## trouble shooting

- `configure: error: !!! no tgetent - no screen`
	- [Linux非root用户配置安装screen](https://cxybb.com/article/m0_37584687/88958204)
```bash
# 首先安装ncurses
pass

# 准备screen的安装环境变量
export LDFLAGS='-L [path/to/ncurses/lib]'  # like ~/opt/lib
export CPPFLAGS='-I [path/to/ncurses/include]'  # like ~/opt/include
./autogen.sh  # 配置初始内容, 产生configure文件
./configure --prefix=[path/to/install/screen]
make
make install
# 安装完成后, 在对应的bin中可以找到
```




