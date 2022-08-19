---
title: 安装 oh-my-posh
tags: [shell/PowerShell, shell/beautify]
---

## 引言
- 人皆爱美, 我也一样
  - 我要好看的命令行

## 准备工作
- 为了方便`oh-my-posh`安装, 我们可以先安装`scoop`
  - 详情参见另一篇, 关于`scoop`安装的记录
- 有的地方说`oh-my-posh`只支持`powershell7`
  - 但是我装完之后发现在`ps5`里面也可以正常使用
  - 查看自己当前`ps`版本: `$PSVersionTable`, 第一行中
  - 升级`ps`参见: []

## 安装`oh-my-posh`
- `oh-my-posh`现在已经有ver3了
- 本文使用`scoop`安装, `scoop install oh-my-posh3`
- 在`~/scoop/persist/oh-my-posh3/themes/`文件夹下, 是主题配置文件
  - 看起来比较好懂, 都是人言就不说了, 因为我是一项一项试出来干啥的

## 配置`ps`
- 在命令行里输入这个, 可以把主题设置为`blue-owl.omp.json`文件中的内容
  - `oh-my-posh --init --shell pwsh --config ~/blue-owl.omp.json | Invoke-Expression`
- 可以在`$PROFILE`文件中添加这句话, 这样启动的时候自动执行


## 仍然没有解决的问题
- 目前只有`Get-PoshContent`命令能用, 其他的比如快速换装的命令不知道怎么搞


## 参考文献
- [官网: 在powershell中安装](https://ohmyposh.dev/docs/pwsh)
- [官网: 可选主题](https://ohmyposh.dev/docs/themes)
- [官网: 关于字体](https://ohmyposh.dev/docs/fonts)
  - 同时也给出了在`windows terminal`中如何配置默认字体