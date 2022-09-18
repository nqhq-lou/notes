---
title: matplotlib primitives and container
tags: [python/module/matplotlib]
---


## 概述

- matplotlib有三层api
- 程序和计算机底层的交互
	- `matplotlib.backend_bases.FigureCanvas`代表了绘图区，所有的图像都是在绘图区完成的
	- `matplotlib.backend_bases.Renderer` 代表了渲染器，可以近似理解为画笔，控制如何在`FigureCanvas`上画图
- 用户通常调用的接口
	- `matplotlib.artist.Artist` 代表了具体的图表组件，即调用了Renderer的接口在Canvas上作图


- Artist分为两类
- `primitives` 基本要素, 在绘图区绘制的标准图形对象
	- 如曲线Line2D，文字text，矩形Rectangle，图像image
- `container` 容器, 容纳基本要素
	- 包括图形figure、坐标系Axes和坐标轴Axis
	- Axis为坐标轴, Axes为单个画图框, Figure为整个画布



to be continued...








## 基本元素 primitives


### 2DLines

#### 设置Line2D的属性

#### 如何绘制lines


### patches

#### Rectangle-矩形

#### Polygon-多边形

#### Wedge-契形


### collections


### images

to be continued...


## 对象容器 object container

### Figure容器


### Axes容器


### Axis容器


### Tick容器


to be continued...
