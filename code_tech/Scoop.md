---
title: scoop basics
tags: [software/scoop]
---

# 关于`scoop`的入门


## 介绍
- 是不是被windows中下载软件的各种奇妙操作耍花眼?
- 你需要一个**干干净净**的安装器!
- 但是这个安装器还不是很完善
  - 软件不全, 不是很坚不可摧, 系统权限方面不尽如人意


## 安装
- 首先修改用户权限
- 然后通过`iex`安装


## 基础使用
- 通过`scoop help`查看
- 注意: 应该即使备份`scoop/apps/scoop`文件夹, 不然某次`update`失败之后会出问题


## 软件逻辑
- 比较简单, 不说了



## 问题解决

- [Git - SSL_ERROR_SYSCALL 问题解决](https://blog.hyperzsb.tech/git-ssl-error/)

<h3 id="使用-https-代理">使用 HTTPS 代理</h3>

<p>在使用 HTTPS 连接 GitHub 进行 push/pull 时（即 origin 地址为 https://github.com/xxx/xxx.git），需要更改本地 git 的配置，使用代理向 GitHub 发起请求。</p>

<blockquote>
  <p>要求：你需要有一个梯子，关于如何获取梯子，可以参考<a href="https://blog.hyperzsb.tech/collections/">我的收藏</a>中关于 VPN 的章节。</p>
</blockquote>

<p>执行如下命令：</p>

<div class="language-shell highlighter-rouge"><div class="highlight"><pre class="highlight"><code><span class="nv">$ </span>git config <span class="nt">--global</span> <span class="nt">-e</span>
</code></pre></div></div>

<p>这将进入 git 的配置文件编辑界面（将使用 git 指定的默认编辑器打开）。</p>

<p>在该文件中加入如下内容：</p>

<div class="language-plaintext highlighter-rouge"><div class="highlight"><pre class="highlight"><code>[http]
        proxy = socks5://127.0.0.1:7891
[https]
        proxy = socks5://127.0.0.1:7891
</code></pre></div></div>

<p>其中“7891”为你的代理软件的指定出入端口，请根据实际情况自行修改。</p>

<blockquote>
  <p>该方法对我有效</p>
</blockquote>


## 注意事项
- ``scoop``会对自己进行升级, 在这个过程中他好像会去给自己搬家
  - 如果强制要求停止, 那么`scoop`就废掉了
  - 所以尽量给`scoop`设置好网络代理, 防止因为网络不通而出现问题
- ``scoop``还在发展中, 多多见谅, 虽然我不是开发者
- 如果下载了`aria2`, 可能会在下载中出现一些问题
  - 使用`scoop config aria2-enabled false`取消`aria2`下载



## 参考文献
- [「一行代码」搞定软件安装卸载，用 Scoop 管理你的 Windows 软件 from zhihu](https://zhuanlan.zhihu.com/p/54822449)