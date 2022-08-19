# 0418 Meeting Note

## :date:计划调整
- :boom:学期内不向上装新刀片

## :book:答疑环节
- 网络相关知识太少
    - 可以参考一下网页
    - :ice_cream:[鸟哥的Linux私房菜](http://cn.linux.vbird.org/), 基础篇和服务器篇可选
    - [鸟哥的首页](https://linux.vbird.org/), more to be explorer
- 无法执行`sudo cd /root`
    - 意在查看里面的文件, 但是确实没有访问权限
    - 如果知道文件路径, 可以`cat`
    - e.g. `sudo cat /root/anaconda-ks.cfg`, 有结果输出
    - 安装者希望把anaconda的这个文件拷贝进去, 但是后来没用这个拷贝.
- 服务器上软件`lrzsz`无法使用
    - 就不用了, 用`scp`
- 用Python向`./xfile`输入参数
    ```Python
    import os
    date = os.popen('date')  # 能够获得返回的值
    print(data.read())
    ```
    - [python执行系统命令四种方法比较](https://blog.csdn.net/luckytanggu/article/details/51793218)
- openMPI for C Language
    - 网上直接看教程
    - 自己搜的: [Open MPI安装使用](http://hmli.ustc.edu.cn/doc/mpi/openmpi-install.htm)
    - 后来按照这个做了: [在CentOS上安装MPI](https://www.jianshu.com/p/57b1460c8afd), 具体操作见下block.
    - 检查位置`sudo find / -name "mpicc"`
        - 已经安装了`mpich`, 位置在`/usr/lib64/mpich/bin/mpicc`
        - 好像`openmpi`也有了
        - 已经把上面的路径加入了我自己的`.bashrc`
    - 抄写了一个文件, 确认`mpicc`和`mpirun`没有问题, 文件在`~/C/0420.c`
        - 照着上面的抄的, [在CentOS上安装MPI](https://www.jianshu.com/p/57b1460c8afd)
        - 但是没有尝试多个node同时执行
```
[zklou@login ~]$ yum list mpi*
Loaded plugins: fastestmirror, refresh-packagekit, security
Loading mirror speeds from cached hostfile
 * epel: mirror.math.princeton.edu
https://packages.microsoft.com/yumrepos/vscode/repodata/repomd.xml: [Errno 12] Timeout on https://packages.microsoft.com/yumrepos/vscode/repodata/repomd.xml: (28, 'connect() timed out!')
Trying other mirror.
Installed Packages
mpi-selector.x86_64               1.0.3-1.40200              installed
mpitests_openmpi.x86_64           3.2.19-acade41.40200       installed
Available Packages
mpi4py-common.noarch              1.3.1-1.el6                epel
mpi4py-docs.noarch                1.3.1-1.el6                epel
mpi4py-mpich.x86_64               1.3.1-1.el6                epel
mpi4py-openmpi.x86_64             1.3.1-1.el6                epel
mpich.i686                        3.1-5.el6                  base
mpich.x86_64                      3.1-5.el6                  base
mpich-autoload.x86_64             3.1-5.el6                  base
mpich-devel.i686                  3.1-5.el6                  base
mpich-devel.x86_64                3.1-5.el6                  base
mpich-doc.noarch                  3.1-5.el6                  base
mpich2.i686                       1.2.1-2.3.el6              base
mpich2.x86_64                     1.2.1-2.3.el6              base
mpich2-devel.i686                 1.2.1-2.3.el6              base
mpich2-devel.x86_64               1.2.1-2.3.el6              base
mpich2-doc.noarch                 1.2.1-2.3.el6              base
mpir.i686                         1.3.1-4.el6                epel
mpir.x86_64                       1.3.1-4.el6                epel
mpir-devel.i686                   1.3.1-4.el6                epel
mpir-devel.x86_64                 1.3.1-4.el6                epel
mpitests-mpich.x86_64             3.2.4-2.el6                base
mpitests-mvapich.x86_64           3.2.4-2.el6                base
mpitests-mvapich-psm.x86_64       3.2.4-2.el6                base
mpitests-mvapich2.x86_64          3.2.4-2.el6                base
mpitests-mvapich2-psm.x86_64      3.2.4-2.el6                base
mpitests-openmpi.x86_64           3.2.4-2.el6                base
[zklou@login ~]$ sudo yum install -y mpich*
...
[zklou@login ~]$ sudo find / -name "mpicc"
/usr/lib64/mpich/bin/mpicc
/usr/mpi/gcc/openmpi-2.0.2a1/bin/mpicc
/public/software/mpi/openmpi/intel/2.1.2/bin/mpicc
/public/software/mpi/intelmpi/2017.4.239/intel64/bin/mpicc
/public/software/mpi/intelmpi/2017.4.239/mic/bin/mpicc
# 然后把第一个加入环境变量
```

## :calendar:To Do
- 服务器上安装Lammps和Comsol, 相应的环境调整
    - Comsol安装包?
- mpi跑起来
    - 多节点的
- 网络自动连接! 一个月了没解决quq
    - 已经配置了`~/fd-net-auth.sh`文件&`\etc\crondtab`
    - 但是没法用`service`命令, 据说是因为没有`root`权限
    - 舟舟说有一个等效于`service`的命令?
    - `sudo service restart crond`舟舟试了一下成功了
- clash装上
    - [教程](https://www.mebi.me/1723.html)
    - 装不上
- ShadowSocksR
    - [shadowsocks](https://blog.hlogc.com/2019/07/17/centos-install-ssr/)
    - 好像是安装了一个服务端?????? 离谱
```bash
Congratulations, ShadowsocksR server install completed!
Your Server IP        :  11.11.11.253
Your Server Port      :  19374
Your Password         :  shadowsocksr
Your Protocol         :  auth_aes128_md5
Your obfs             :  plain
Your Encryption Method:  aes-256-cfb

Your QR Code: (For ShadowsocksR Windows, Android clients only)
 ssr://MTEuMTEuMTEuMjUzOjE5Mzc0OmF1dGhfYWVzMTI4X21kNTphZXMtMjU2LWNmYjpwbGFpbjpjMmhoWkc5M2MyOWphM055Lz9vYmZzcGFyYW09
Your QR Code has been saved as a PNG file path:
 /public/home/zklou/clash/shadowsocks_r_qr.png

Welcome to visit: https://teddysun.com/486.html
Enjoy it!
```

## :bulb:about lammps
- 学长带着看了一个文件
    - 见另一个文件:rocket:
- [tutorial](https://lammps.sandia.gov/tutorials/sor13/SoR_02-Getting_Started.pdf)
    - 里面有`VMD`的安装过程
- `VMD`
    - 专门用来可视化分子动力学的
    - `.xyz`文件
    - 需要dump出具体坐标/速度, 然后可视化
    - 无限边界条件
        - 有现成的: period/reflect重复或者定向
    - 还有一个软件叫做`Ovito`, 非常方便
        - [official site](https://www.ovito.org/)
- 注意
    - 非mpi版本只能单核
    - 尽量用linux环境
- advantages of lammps
    - 直接指定模型
    - 自动生成mpi
    - 生成的是可执行文件, 不是逐行解读
    - 不用担心迭代的方法等等
    - 可以在后来写程序的时候注意一下

## :smile:appendix
- [emoji for md](https://gist.github.com/rxaviers/7360908)

