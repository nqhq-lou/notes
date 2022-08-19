# 记录给服务器配置桌面

- 文中有些地方`sudo`省略了, 因为我用`root`操作了

## 安装桌面

- 可以选择不同的桌面
  - 我选择了`gnome-session-flashback`, 还可以`ubuntu-gnome-desktop`
- `gnome-session-flashback`
  - 直接`apt-get install gnome-session-flashback`
  - 直接包括了需要的四个包`gnome-panel, gnome-settings-daemon, metacity`
- `ubuntu-gnome-desktop`
  - 这个包比较大, 不用了
  - 安装是`apt-get install ubuntu-gnome-desktop`
  - 设置开机启动:
    - `sudo systemctl start gdm`
    - `sudo systemctl enable gdm`
- 好像还要配置防火墙, 先不管了, 之后有问题再来

## 安装vncserver

- 这里选择`tightvncserver`
  - `apt-get install tightvncserver`

## 修改 `~/.vnc/xstartup`文件

- `xfce`
  ```bash
  #!/bin/sh
  unset SESSION_MANAGER
  unset DBUS_SESSION_BUS_ADDRESS
  startxfce4 &
  [ -x /etc/vnc/xstartup ] && exec /etc/vnc/xstartup
  [ -r $HOME/.Xresources ] && xrdb $HOME/.Xresources
  xsetroot -solid grey
  ```
- `ubuntu-gnome-desktop`
  ```bash
  #!/bin/sh
  # Uncomment the following two lines for normal desktop:
  export XKL_XMODMAP_DISABLE=1
  unset SESSION_MANAGER
  # exec /etc/X11/xinit/xinitrc
  unset DBUS_SESSION_BUS_ADDRESS
  gnome-panel &
  gnmoe-settings-daemon &
  metacity &
  nautilus &
  gnome-terminal &
  ```
- `gnome-session-flashback`
  - 最后用的这个
  - 但是需要安装`gnome-terminal`,`nautilus`
    - `vncconfig`这个vncserver说不知道是什么, apt安装也说没有, 不管了

  ```bash
  #!/bin/sh
  unset SESSION_MANAGER
  # unset DBUS_SESSION_BUS_ADDRESS  # 这个必须注释掉, 不然会花屏+❌鼠标
  export XKL_XMODMAP_DISABLE=1
  export XDG_CURRENT_DESKTOP="GNOME-Flashback:GNOME"
  export XDG_MENU_PREFIX="gnome-flashback-"
  # [ -x /etc/vnc/xstartup ] && exec /etc/vnc/xstartup
  [ -x /etc/vnc/xstartup ] && exec ~/.vnc/xstartup
  [ -r $HOME/.Xresources ] && xrdb $HOME/.Xresources
  # xsetroot -solid grey    # 设置背景色
  vncconfig -nowin &    #
  # vncconfig -iconic &    #
  gnome-terminal &    # 连接后会直接打开一个terminal窗口
  nautilus &    # 连接后会直接打开一个文件窗口
  gnome-session --session=gnome-flashback-metacity --disable-acceleration-check &
  ```

## 进一步配置

- `sudo apt-get install xfonts-base`
- `gnome-terminal`字体奇丑无比, 改一下profile就好
- settings打不开, 尝试进入`gnome-control-center`, 报错没有`gnome.mutter`
  - `apt-get install mutter-common`
  - 仍然不行, 卸载`gnome-control-center`提示无效卸载
  - 报错为:`gnome-control-center segmentation fault (core dumped)`
- 不知道为什么解决了:`dconf reset -f /org/gnome/control-center/`
  - [about dconf from ask ubuntu](https://askubuntu.com/questions/22313/what-is-dconf-what-is-its-function-and-how-do-i-use-it)
- AL1报错: 相同报错
  ```bash
  nqhq@AL1server:~$ vncserver -list
  Couldn't start Xtightvnc; trying default font path.
  Please set correct fontPath in the vncserver script.
  Couldn't start Xtightvnc process.
  ```

  - 安装字体:`sudo apt-get install xfonts-75dpi`,`sudo apt-get install xfonts-100dpi`,`sudo apt-get install xfonts-base`
- 大概明白了: 是因为点进了settings中的Display, 然后会dump
  - 可能是gnome的问题, 下次试一试其他的桌面
  - 尝试卸载`gnome-control-center`之后重新安装, 但是没用
  - 应该是解决方法了
    - https://bugs.archlinux.org/task/61974?project=1&string=glib2
    - #24: "Downgrading package glib2-2.60.0-1 to glib2-2.58.3-1 fixes the problem."
    - 但是不知道这个怎么搞
    - https://bbs.archlinux.org/viewtopic.php?id=244792
    - "The only workaround I know of at the moment is to downgrade (assuming you haven't cleared your pacman cache) to the previous version of glib2"
    - "As a temporary work-around, if you have opened the details section and can no longer start control-center, open dconf-editor and clear the "custom value" for the following key: /org/gnome/control-center/last-panel"
    - `dconf reset -f /org/gnome/control-center/last-panel`
      - It works!

## about apt

- `remove` 删除软件主体
- `purge` 连带配置文件一起删除

## 客户端

- 注意: 需要先进行服务器端口的设置
- 下载并安装VNCViewer:[realVNC下载地址](https://www.realvnc.com/en/connect/download/viewer/)
- 在最上侧框框输入(在服务器上设置好的connector)
  - `[ipv4]::[port]`
  - e.g.`10.10.10.10::5903`
- 输入密码登录
  - 如果在建立端口的时候没有设置密码, 那么这里的密码好像是端口建立人的登陆密码

### 常用命令

- 检查和控制
  - 查看当前有的接口:`-list`
  - 删除接口, 编号为3:`-kill :3`
  - 查看链接状态:`netstat -lp | grep -i vnc`
- 创建端口
  - 创建端口, 编号为3:`:3`
    - 这个时候的port为`5903`
  - 设置分辨率:`-geometry <length>x<width>` (2240x1400)

## 参考文献

- https://blog.csdn.net/catshitone/article/details/103181202、
- https://blog.csdn.net/carrousel0516/article/details/114886334
- https://www.linuxrumen.com/rmxx/1871.html
- d
