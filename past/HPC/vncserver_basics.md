# vncserver使用基础

- 本文用于对物理实验中心HPC的tigerVNC的使用说明
- 为实用导向, 具体原理等等参见相关网页文档

## 客户端

- 注意: 需要先进行服务器端口的设置
- 下载并安装VNCViewer:[realVNC下载地址](https://www.realvnc.com/en/connect/download/viewer/)
- 在最上侧框框输入(在服务器上设置好的connector)
  - `[ipv4]::[port]`
  - e.g.`10.10.10.10::5903`
- 输入密码登录
  - 如果在建立端口的时候没有设置密码, 那么这里的密码好像是端口建立人的登陆密码

## 服务器端

- 需要通过命令行创建端口, 然后进行连接

### 常用命令

- 检查和控制
  - 查看当前有的接口:`-list`
  - 删除接口, 编号为3:`-kill :3`
  - 查看链接状态:`netstat -lp | grep -i vnc`
- 创建端口
  - 创建端口, 编号为3:`:3`
    - 这个时候的port为`5903`
  - 设置分辨率:`-geometry <length>x<width>` (2240x1400)

## 可行性解释

1. 被访问机器安装 tigerVNC 成为 VNC server, 暴漏5900端口
2. 客户端访问使用客户端直接进行, 访问端口进行数据交互

<!-- 3. 浏览器访问 VNC server 需要 tcp 到 websocket 的转化，因此 使用 websockify 把5900端口代理到8080. 通过nginx 把noVNC的web服务代理到80端口，供外界访问. 在其他机器上，通过输入 url:80/vnc.html 访问到noVNC页面后，设置websocket访问端口，访问被访问机器。 -->

## 备注

- 也可以使用noVNC进行网页访问! 不过以后再写吧.
- 如果有什么不懂的, 直接搜索: tigerVNC找相关文章
- vnc和anaconda的dbus冲突的解决：[vnc和anaconda冲突解决方法：could not make bus activated clients aware of XDG_CURRENT_DESKTOP=GNOME envi_程大海的博客-CSDN博客](https://blog.csdn.net/cxx654/article/details/106218894)
