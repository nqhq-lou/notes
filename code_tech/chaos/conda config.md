---
title: conda config
tags: [python/conda]
---



## source config

```bash
# conda添加tuna
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/pro/
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/r/
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/conda-forge 
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/msys2/
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/pytorch/

# 设置搜索时显示通道地址
conda config --set show_channel_urls yes

# 查看源的优先权
conda config --get channels

# 删除添加的镜像源, 恢复官方默认源
conda config --remove-key channels
```



## references
- [我的服务器conda环境配置方法](https://zhuanlan.zhihu.com/p/283768009)
	- 推荐阅读, 操作非常详细


