---
title: matplotlib basis
tags: [python/module/matplotlib]
---



## matplotlib概述

- 非常常用, 不用多说
- 我们所熟知的pandas和seaborn的绘图接口其实也是基于matplotlib所作的高级封装
- 基础导入内容
```python
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
```

- 在jupyter notebook中使用matplotlib时会发现，代码运行后自动打印`__repr__`
	- 类似`<matplotlib.lines.Line2D at 0x23155916dc0>`这样一段话
	- 这是因为除了行间绘图, matplotlib的绘图代码默认打印出最后一个对象
- 如果不想显示这句话:
	- 在代码块最后加一个分号`;`
	- 在代码块最后加一句plt.show()
	- 在绘图时将绘图对象显式赋值给一个变量


## 基础例子
- 通过`pyplot.subplot`创建figure和axes
```python
fig, ax = plt.subplots()  # 创建一个包含一个axes的figure
ax.plot([1, 2, 3, 4], [1, 4, 2, 3]);  # 绘制图像
```



## figure的组成

- figure包括四个层级(container, 容器)
-   `Figure` 顶层级，用来容纳所有绘图元素
-   `Axes` matplotlib宇宙的核心，容纳了大量元素用来构造一幅幅子图，一个figure可以由一个或多个子图组成
-   `Axis` axes的下属层级，用于处理所有和坐标轴，网格有关的元素
-   `Tick` axis的下属层级，用来处理所有和刻度有关的元素

![figure_anatomy|600](https://matplotlib.org/_images/anatomy.png)


## figure的组成




## references

- [matplotlib初相识](https://datawhalechina.github.io/fantastic-matplotlib/%E7%AC%AC%E4%B8%80%E5%9B%9E%EF%BC%9AMatplotlib%E5%88%9D%E7%9B%B8%E8%AF%86/index.html#id4)
- 