---
tags: [shell/PowerShell, proxy]
---

# 如何配置`powershell`的网络代理


## 起因
- 今日配置`scoop`, 网速太慢人要没了
- 愤而配置之, 碰壁许久, 特此记录

## 具体操作
- 修改临时环境变量: `HTTP_PROXY` & `HTTPS_PROXY`
    ```powershell
    $env:HTTP_PROXY="http://127.0.0.1:<#port#>"
    $env:HTTPS_PROXY="https://127.0.0.1:<#port#>"
    ```
    - 这里的`<#port#>`需要到软件里查, 比如clash查到为`7890`(老懒省事了)
- 或者修改`$PROFILE`
  - 更加快捷进入`$PROFILE`的方式
    - `code $PROFILE`
  - 然后使用`function <#alias#> {<#content#>}`进行修改
  - 补充: 查询`$PROFILE`位置的方式
    - `echo $PROFILE`

## 检查是否已经生效
- `curl -v google.com`

## 取消当前代理
- 笨笨的样子
    ```powershell
    $env:HTTP_PROXY=""
    $env:HTTPS_PROXY=""
    ```


## 一些说明
- `ping`和`curl`的实现是不一样的
- 如上方法对于ss, v2ray, clash, 配置完之后可以使用`curl`, 但是无法`ping`通
- 如果要实现`ping`通: 还不知道该怎么办
  - 参见: [windows终端命令行下如何使用代理？](https://github.com/shadowsocks/shadowsocks-windows/issues/1489)
- 对于`cmd`, 需要使用不同的设置方式
  - 详情参见: [powershell 设置代理 from 博客园](https://www.cnblogs.com/xch-jiang/p/14324636.html)


## 参考
- [WIN10给powershell设置全局代理](https://blog.csdn.net/weixin_44120025/article/details/110950434)
- [建议增加 PowerShell 的一键代理命令复制 from clash_for_windows_pkg@Github](https://github.com/Fndroid/clash_for_windows_pkg/issues/837)
- [windows powershell配置http代理]()




