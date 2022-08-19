# Q & A on bashhistory

## 已经基本解决
- 软件安装地址

## `ip a`
- 重复检查`ip a`

## 网络
- `inet`和`eth(数字)`是什么
- 重复`ifup eth3`和`ifdown eth3`
- 对网络相关的内容不了解
- 需要简单介绍
- [鸟哥](http://linux.vbird.org/)
    - 可以不用从头看, 寻找需要的部分
- [更合适的?](http://cn.linux.vbird.org/)
    - 也是鸟哥, 大陆版本的

## 权限
- `sudo`不管用了
- 无法进入`/root`
- 想看一下`/root/anaconda-ks.cfg`里是什么
- 知道路径可以打出来, 权限情况为`dr-xr-x---`
- `ks.cfg`, 当时希望把这个从windows拷到服务器上, 但是没成功

## lrzsz
- Windows 和 Linux 互传文件
- 但是无法使用欸

## `sed` = `stream editor`
- 自己上网查

## 推荐教材?
- 旗标? flag `gcc a.c -o a.out -O3`
- linux命令行
- 网络连接?
    - 见上, 鸟哥
- 看不下去manual
- openMPI for C Language
    - 网上直接看教程

python
- `./a.out -a 1000 -b 1000`
python 命令行 & 读取命令行中内容?
- `os.system`
    - `os.popen`
    - [python执行系统命令四种方法比较](https://blog.csdn.net/luckytanggu/article/details/51793218)

```Python
import os
date = os.popen('date')  # 能够获得返回的值
print(data.read())
```





