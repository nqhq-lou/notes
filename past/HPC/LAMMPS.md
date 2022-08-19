# LAMMPS homemade instruction

## websites
1. Official Sites
- [Main Site from LAMMPS](https://lammps.sandia.gov/)
1. Baidu Tieba
- [Tieba LAMMPS](https://tieba.baidu.com/f?kw=lammps&ie=utf-8)




## Try to Installation
- pre-compiled exe
- run sudo in ternimal for windows
- [PowerShell 设置 alias](https://blog.csdn.net/lei_qi/article/details/106592404)
    - `C:\Users\LX01\Documents\WindowsPowerShell\Microsoft.PowerShell_profile.ps1`
    - `$ Set-ExecutionPolicy RemoteSigned`

## Basic usage
- 生成`.lmp`文件
- 或者使用

## 网页
- [tutorial](https://lammps.sandia.gov/tutorials/sor13/SoR_02-Getting_Started.pdf)
- lmp < .lmp + (后面的命令)
- 里面有`VMD`的安装过程

## `VMD`
- 专门用来可视化分子动力学的
- `.xyz`文件
- 需要dump出具体坐标/速度, 然后可视化
- 无限边界条件
    - 有现成的: period/reflect重复或者定向
- 还有一个软件叫做`Ovito`, 非常方便

## 注意
- 非mpi版本只能单核
- 尽量用linux环境

# advan
- 直接指定模型
- 自动生成mpi
- 生成的是可执行文件, 不是逐行解读
- 不用担心迭代的方法等等




