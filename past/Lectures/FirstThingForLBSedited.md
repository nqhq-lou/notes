<head>
	<meta charset="utf-8">
	<title>HTML设置超链接颜色</title>
	<style type="text/css">
		a:link {
			/* color:cyan; */
			color:pink;
			text-decoration:none;
		}
		a:visited {
			color:pink;
			text-decoration:none;
		}
		a:hover {
			color:blue;
			text-decoration:none;
		}
		a:active {
			color:pink;
			text-decoration:none;
		}
	</style>
</head>





---

## 理辩社

# 第一次培训

#### [phylab](http://phylab.fudan.edu.cn/) 以及(一些)夹带私货

### by 19 物理 娄泽坤

[:email:myEmailAddr:email:](mailto:nqhqnqhq@outlook.com)





---

## 提纲

- [phylab](http://phylab.fudan.edu.cn/) & [DokuWiki](https://zh.wikipedia.org/wiki/DokuWiki)

  - phylab简介, DokuWiki的基础语法

  - How it works?

- Markdown

  - 推荐的编辑器和实现方式

  - 基础语法

- $\LaTeX$

  - 是什么, 为什么, 怎么做

* 管好你的 **Windows** !!! 🐱‍💻🐱‍👤🐱‍🏍🐱‍🐉🐱‍👓🐱‍🚀s

  * C盘: 挥之不去的噩梦

  * 防护软件的一些想法

  * 快捷键

  * 命令行:shell:, scoop:wrench:, Linux(yes!)

* 参考文献

  * 可以看一看, 说不定有什么用的内容

  * ~~为了好看的占位文字~~

**基础部分**: 带着大家做一遍

**困难部分**: 不作强制要求, 给出指导链接:link:

<font color=red>所有内容都会放到群里, **不需要记录**哦</font>



---

## [phylab @ fudan](http://phylab.fudan.edu.cn/) 简介

* ![QRCode](http://phylab.fudan.edu.cn/lib/exe/fetch.php?cache=&media=fudan2d3.png)

* ***复旦大学物理教学实验中心***

* 课程安排, 资料归档, 技术交流, 成果展示

- 查询课程信息, 老师和助教联系方式

- 查询课程资料: 每节课均有个对应页面
- 参加讨论: 页面后讨论区
- 文件传递: 下载资料, 提交作业
- 搭建网页: 放一些自己写的教程
- 页面存档: 方便回溯





---

## phylab runs on [DokuWiki](https://zh.wikipedia.org/wiki/DokuWiki)

- 好:horse:佩好鞍
- ![](https://tse4-mm.cn.bing.net/th/id/OIP-C.c1_gHtUmXEtJ9mMUbySYAgHaHd?pid=ImgDet&rs=1)


* Wiki引擎, 适合中小企业和个人使用
* 不需要数据库: 基于文本存储
* 功能齐全(链接, 编辑页面, 目录)
* 用作资料网站, 归档, 指南, 读书笔记等





---

## phylab的交互

- 申请账户
- 页面层次(网站地图)
- 页面编辑

* 编辑说明
  - 预览按钮
  - 冲突编辑
  - 历史回溯
  - 权限

莫着急! 课件上传
回去再试, 服务器承载能力有限



---

## DokuWiki的基础语法

[这次的playground](http://phylab.fudan.edu.cn/doku.php?id=home:students:nqhq:grammarplayground)

- 标题
- 列表及缩进
- 表格
- 插入资源
- 数学公式
- 代码块

更加详细的语法内容, 请见:
[dokuwiki官方语法学习页面](https://www.dokuwiki.org/wiki:syntax#code_blocks)

tips: 够用就行, 需要再查





---

## DokuWiki对个人使用的不足

- 不尽人意
  - 来回点击预览按键, 个人使用时操作效率低
  - 奇奇怪怪: 列表需要空两格
  - 不是本地内容

- 目标需求
  - 快速记录, 可移植性, 资源占用小
  - 自由输入, 格式可控, 不用担心排版
  - 好看, 好看, 好看:smile:





---

## <font face="Fira Code">Markdown</font> ![noAlias](https://www.runoob.com/wp-content/uploads/2019/03/iconfinder_markdown_298823.png)

简单的纯文本$\stackrel{\color{red}\text{markdown的规则}}{\longrightarrow\longrightarrow\longrightarrow}$较好的文档效果

- 轻量级标记语言: 用易读易写的纯文本格式编写文档.
- 在 2004 年由 ~~XX · XXXX~~ 创建.
- 可以导出 `html`, `word`, `img`, `pdf`, `epub`等多种格式的文档 (需要`pandoc`)
  - `pandoc -f gfm -t dokuwiki <filename.md> -o <filename.txt>`
- 文件后缀为 `.md` 或 `.markdown`
  - 文件中只有<u>文字</u>和<u>规则下的标记</u>, 需要相应的渲染

```markdown
![noAlias](https://www.runoob.com/wp-content/uploads/2019/03/iconfinder_markdown_298823.png)
简单的纯文本$\stackrel{\color{red}\text{markdown的规则}}{\longrightarrow\longrightarrow\longrightarrow}$较好的文档效果

- 轻量级标记语言: 用易读易写的纯文本格式编写文档.
- 在 2004 年由 ~~XX · XXXX~~ 创建.
- 可以导出 `html`, `word`, `img`, `pdf`, `epub`等多种格式的文档 (需要`pandoc`)
  - `pandoc -f gfm -t dokuwiki <filename.md> -o <filename.txt>`
- 文件后缀为 `.md` 或 `.markdown`
  - 文件中只有<u>文字</u>和<u>规则下的标记</u>, 需要相应的渲染
```




---

## Why <font face="Fira Code">Markdown</font>?

- 快速记录, 格式多变, 可移植性, 资源占用小

  - 都满足! <font size=3>成年人的快乐, 小孩子才做选择.</font>

- 已经被广泛采用: [github](https://github.com/peng-zhihui/Dummy-Robot), [gitbook](https://nqhqnqhq.gitbook.io/manualette/)

- 局限:

  - 非常适合代码工作[例子](https://github.com/Dreamacro/clash/discussions)
    - :tada: :art: :zap: :fire: :bug: :ambulance: :memo: :sparkles: :rocket: :beers:

  - 轻度适合数学书写 (考虑[Math![none](https://cdn.mathcha.io/image/logo.svg)](https://www.mathcha.io/))(强烈推荐!)

  - 极不适合大量记录数据 (考虑:raised_hands::pencil:)





---

## <font face="Fira Code">Markdown</font> where?

- Typora
  - WYSIWYG: what you see is what you get

- VS Code (individual, **system**) (recommended)
  - `Markdown Preview Enhanced` yyds!
  - 也有其他选择: [搭建 Markdown 舒适写作环境](https://zhuanlan.zhihu.com/p/139140492)

- jupyter lab / jupyter notebook (while coding, hybrid)

- markdown制作幻灯片: [sli.dev](https://sli.dev/)



---

## <font face="Fira Code">Markdown</font>基础语法
###### 本身就是为了方便而诞生的东西, 怎么会不方便呢?

[本机的playground](C:\Users\zekun\Documents\Notes\Lectures\grammarPlayground.md)

- 标题
  - from `#` to `######`
- 列表及缩进
  - `- ` or `* `
  - `1.` and `1.` and `1.`
  - `tab`
- 表格
  - `|||`
- 插入资源
  - `[avator](address)`
  - `![avator](address)`

* 非基础语法
  * 用html在里面写
    * `<u>`下划线
    * `<font>`更改字体/字号/颜色
  * <font color=red size=25>f</font><font color=orange size=25>a</font><font color=brown size=25>a</font><font color=green size=25>n</font><font color=cyan size=25>c</font><font color=blue size=25>y</font><font color=purple size=25>y</font>

更加详细的教程, 请访问[markdown preview enhanced documentation](https://shd101wyy.github.io/markdown-preview-enhanced/#/zh-cn/markdown-basics)





---

## $\LaTeX$ ![](https://upload.wikimedia.org/wikipedia/commons/thumb/4/45/LaTeX_project_logo_bird.svg/316px-LaTeX_project_logo_bird.svg.png)

- 简介
  - [$\LaTeX$ from WikiPedia](https://zh.wikipedia.org/wiki/LaTeX)
  - 一种基于$\TeX$的排版系统, 生成高质量印刷品.
    - $\TeX$: MIT高德纳教授, "每指出$\TeX$的一个错误，就能得到2.56美元".
  - 始于1984年, 经过发展, 现在版本为$\LaTeX \ 2_\varepsilon$

- 任何想得到的东西, 都能排出来!
  - 乐谱, 棋谱(可动态), 化学结构式, 电路图, 费曼图...
  - 已有规则$\rightarrow$写宏包$\rightarrow$简单语法排版

- 逻辑描述
  - 转换程序 $\otimes$ ((格式)宏包 + 输入的内容) == 漂漂亮亮的pdf
  - 纯文本输入, 通过程序转换为pdf
  - 通过预设格式的"宏包", 能够在原先软件的规范下, 实现更多格式





---

## $\LaTeX$ 配置导引

- MiKTeX
  - 参考配置指导: [搭建 LaTeX 轻量级写作环境 (MiKTeX+VSCode)](https://zhuanlan.zhihu.com/p/139210056)

- 希望上手$\LaTeX$的参考
  - 最新版的官方说明: [112分钟了解$\LaTeX \ 2_\varepsilon$](https://ctan.math.washington.edu/tex-archive/info/lshort/chinese/lshort-zh-cn.pdf)





---

## 如何管理好 🐱‍💻🐱‍👤🐱‍🏍🐱‍🐉🐱‍👓🐱‍🚀s

### 基础工具介绍

- 任务管理器 `ctrl`+`shift`+`esc`: 电脑进程查看
- 注册表 `win`+`R` && `regedit` && `enter` 不要乱动!!!!
- 恶意软件卸载 `win`+`R` && `mrt` && `enter`
- 全局搜索`win`+`Q` && `<toCheck>` && `enter`
  - 高级系统设置, 事件查看器
  - 已安装的应用程序





---

## 如何管理好 🐱‍💻🐱‍👤🐱‍🏍🐱‍🐉🐱‍👓🐱‍🚀s

- 关闭不必要的服务
  - ~~多嘴的~~小娜 (推荐Dism++)
  - Xbox, etc
- 自启动管理
  - 任务管理器 中 启动 选项卡
- 高级系统设置
  - 性能设置
- 任务管理器
  - 监视奇怪进程 & `kill`

* 禁忌
  * 中文路径, 路径带空格
  * `C:/` 根目录乱搞
* 零零碎碎
  * 任务栏的搜索框, 小娜, 新闻
  * 详见快捷键部分
  * `alt`+`tab` 浏览器单窗格
  * `win`+`tab` 速览视图
  * `ctrl`+`win`+`←/→` 切换桌面





---

## 防护软件 for 🐱‍💻🐱‍👤🐱‍🏍🐱‍🐉🐱‍👓🐱‍🚀s

- :blush: windows defender
  - 安静, 乖, 不乱搞
- :smiley: 火绒安全
  - 安静, 乖, 不乱搞, 自定义难
  - 弹窗拦截:ok:, 但是查杀率低
- :satisfied: 卡巴斯基
  - 全能:thumbsup:卡巴不卡
  - 免费版杀毒够用
- :question: 其他的
  - 不太清楚, 自行百度

* :sweat_smile: 联想电脑管家
  * 曾经贼喊捉贼
  * 他的兄弟们依然是贼
* :innocent: :clock3::clock6::clock12:
  * 3恰6烂0钱!
  * 适合电脑盲, 占用巨大资源
* :sweat: :100:deg, 🈲:mountain:deg霸
* :shit: 鲁大师, 腾讯电脑管家, 驱动精灵

总之: 官方下载, 正版掏钱, 盗版小心, 拒绝<font size=5>小网站</font>





---

## 快捷键 & 相应使用方式
| 快捷键 | 描述 |
| :-: | :-: |
| `alt`+`tab` | 切换桌面最前方的进程|
| `win`+`tab` | 多桌面 |
| `win`+`V` | 剪切板 |
| `win`+`Q` | 全局搜索 |
| `win`+`X` | menu右键 |
| `win`+`R` | 运行 |
| `win`+`<num>` | 打开任务栏的图标 |





---

## 命令行 导引
##### (基于个人理解)

- 一种和电脑交互的方式, 有的时候比图形界面交互效率更高
- 不要害怕! 理解操作逻辑. 有很多帮助(网页, 文档).

- 推荐简单学习linux的命令行基础, 因为后来可能会用到

- 一些区分不清的概念
  - u? x?: unix, linux, macos, freeBSD
  - linux的发行版: centos, ubuntu, etc.





---

## WSL == Windows Subsystem for Linux 导引
- `Linux`的好处
  - 方便的环境配置: 免除"查询一小时, 开发5min"的痛苦
  - 统一的软件安装管理: `apt`, `yum`, 等等
  - 关于window和linux的评价: [windows和Linux比较 from zhihu](https://zhuanlan.zhihu.com/p/78988945)
- `WSL`介绍
  - 拥有(近似)完整的`linux`内核, 可以使用相应的系统操作
  - 刚安装时, 只有命令行(后续可以选择安装桌面并且显示)
- 两个版本:
  - `WSL1`: 直接写进windows的进程中 (win10默认)
  - `WSL2`: 一个虚拟机, 但是适配做的好
- 推荐使用方式: `VSCode` & `Terminal`
- 后续版本: `WSLg` (win11默认)
  - 原生支持windows中的窗口
  - 增加对GPU的支持





---

## <font face="Fira Code">scoop</font> 导引

- Linux上安装gcc
  - `sudo apt-get install gcc`
  - 好馋!
- windows安装gcc
  - 掠过10+条":shit:软件园"的广告
  - 找sourceforge, 用5min加载网页
  - 在14个下载选项中找到要的tar
  - 下载tar之后解压, 用时10min
  - 将解压文件放在合适的位置
  - 添加环境变量

* windows用scoop安装gcc
  * `scoop install gcc`
  * 效果为以上的所有:tada:
* <font face="Fira Code">scoop</font>优缺点
  * :thumbsup:一行安装, 无目录/环境变量污染
  * :thumbsup:方便后续管理/升级
  * :wink:约20k个软件收录
  * :thumbsdown:需要配置代理(vpn, 梯子)
  * :thumbsdown:更新中断导致崩坏
* 建议: 记得备份`~/scoop/apps/scoop/`

如果你想试试:
[「一行代码」搞定软件安装卸载，用 Scoop 管理你的 Windows 软件 from zhihu](https://zhuanlan.zhihu.com/p/54822449)
[你需要掌握的Scoop技巧和知识 from zhihu](https://zhuanlan.zhihu.com/p/135278662)





---

## 需要大家自己探索的

1. 科学上网 [|](https://www.iszy.cc/page/bgfw/)
   1. Google Scholar, Zotero, WikiPedia
1. 学校图书馆的好用功能: [library.fudan.edu.cn](http://www.library.fudan.edu.cn/)
1. 想要的书基本都有: [library genisis](https://libgen.is/)
1. 好用的软件
   1. everything, utools, Dism++, wiztree
   2. terminal, terminus, potplayer, etc.

被扶着走路-->>自己走路
zhihu, csdn, msdn, github_issues, doc




---

## 一些建议
##### <有些建议, 权作建议, 不听也无妨>
1. 遇事不决
   - [zhihu](https://www.zhihu.com/) & [csdn](https://www.csdn.net/) & [msdn](https://docs.microsoft.com/zh-cn/) & [Documentation](http://findYourSelf_thisIsNotALink)
2. 管理好电脑
   - 满足日常需求 || 为了管理而管理
3. 不要过分追求<font color=red size=25>f</font><font color=orange size=25>a</font><font color=brown size=25>a</font><font color=green size=25>n</font><font color=cyan size=25>c</font><font color=blue size=25>y</font><font color=purple size=25>y</font>的效果
   - 比如[cyan色的超链接](https://www.w3cschool.cn/article/25797017.html), 以及一些后续效果
   - 又或者, 为了<font face="Fira Code">Fira Code Retina</font>字体, ~~<font color=red size=25>怒</font>删系统字体~~
   - 权衡: 之后的需求 / 本次操作的时间
4. 时间管理
   - 祝你成为:watch:时间管:raised_hands:理大师:alarm_clock:
   - Microsoft TODO, Notion, Wolai





---

## 以及一个生动的教学案例
### 上一个slides的代码

```html
## 一些建议
##### <有些建议, 权作建议, 不听也无妨>
1. 遇事不决
   - [zhihu](https://www.zhihu.com/) & [csdn](https://www.csdn.net/) & [msdn](https://docs.microsoft.com/zh-cn/) & [Documentation](http://findYourSelf_thisIsNotALink)
2. 管理好电脑
   - 满足日常需求 || 为了管理而管理
3. 不要过分追求<font color=red size=25>f</font><font color=orange size=25>a</font><font color=brown size=25>a</font><font color=green size=25>n</font><font color=cyan size=25>c</font><font color=blue size=25>y</font><font color=purple size=25>y</font>的效果
   - 比如[cyan色的超链接](https://www.w3cschool.cn/article/25797017.html), 以及一些后续效果
   - 又或者, 为了<font face="Fira Code">Fira Code Retina</font>字体, ~~<font color=red size=25>怒</font>删系统字体~~
   - 权衡: 之后的需求 / 本次操作的时间
4. 时间管理
   - 祝你成为:watch:时间管:raised_hands:理大师:alarm_clock:
   - Microsoft TODO, Notion, Wolai
```

- 这上面的内容一共用了 30min





---

## 以及另外一个生动的例子
### lzk的0920这一天是怎么过去的

- <要做的事情>
  - <发生的问题list>
- 计算物理, 作业要写readme
  - 还没安装miktex和配置环境
- 安装miktex并配置环境
- 用latex写伪代码
  - 不会, 学
  - 分不清`algorithmic`等一堆包的区别
  - 翻了很多网页, 学会并且写完作业
  - 看着`.tex`文件很乱, (* ￣︿￣)
- `.tex`文件实现自动整理
  - 使用`scoop`下载perl
- `scoop install perl`
  - `scoop update`失败
  - 并且自己把自己删除了

* 重装`scoop`
* 配置命令行代理
  * 找了很多网页
  * 没有效果
* 重装scoop, 配置git代理
  * 找了很多网页
  * 问题解决
* 以为下班了
  * 发现`julia`也没了
* `scoop install julia`
  * 发现`julia Pkg`冲突
* 删除原有`Pkg`, 重新安装
  * 无法安装
* 配置代理, 重设命令行代理
* 下班吃晚饭, 晚上继续学习





---

## 参考文献

- 推荐阅读:
  - [MarkDown 教程 from RUNOOB.com](https://www.runoob.com/markdown/md-tutorial.html)
  - [dokuwiki官方语法学习页面](https://www.dokuwiki.org/wiki:syntax#code_blocks)
- 准备过程中发现的可能对大家学python有帮助的东西
  - [华东师范大学《编程思维与实践》课程主站 from github](https://github.com/neolee/wop-ecnu-pub)
- 看起来比较靠谱的git和github入门: [wop-ecnu-pub/x3-git-github.ipynb](https://github.com/neolee/wop-ecnu-pub/blob/master/x3-git-github.ipynb)
- 以及先前页面里引用的页面, 不再一一列举




---

## BTW

### 两个自己最近再看的东西:

#### (假装自己很厉害的样子)

![](https://julialang.org/assets/infra/logo.svg)

![](https://raw.githubusercontent.com/Qiskit/qiskit/master/images/qiskit_header.png)

有兴趣的同学可以上网搜一搜, 如果有兴趣的话我们可以私下交流




