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
![just_example_1](https://datawhalechina.github.io/fantastic-matplotlib/_images/index_2_0.png)


## figure的组成

- figure包括四个层级(container, 容器)
-   `Figure` 顶层级，用来容纳所有绘图元素
-   `Axes` matplotlib宇宙的核心，容纳了大量元素用来构造一幅幅子图，一个figure可以由一个或多个子图组成
-   `Axis` axes的下属层级，用于处理所有和坐标轴，网格有关的元素
-   `Tick` axis的下属层级，用来处理所有和刻度有关的元素

![figure_anatomy|600](https://matplotlib.org/_images/anatomy.png)


## 两种绘图接口

- 显式创建figure和axes，在上面调用绘图方法，也被称为OO模式（object-oriented style) 
- 依赖pyplot自动创建figure和axes，并绘图

```python
""" object-oriented style """
x = np.linspace(0, 2, 100)

plt.plot(x, x, label='linear') 
plt.plot(x, x**2, label='quadratic')  
plt.plot(x, x**3, label='cubic')
plt.xlabel('x label')
plt.ylabel('y label')
plt.title("Simple Plot")
plt.legend()
plt.show()
```



```python
""" 创建figure和axes """
x = np.linspace(0, 2, 100)

fig, ax = plt.subplots()  
ax.plot(x, x, label='linear')  
ax.plot(x, x**2, label='quadratic')  
ax.plot(x, x**3, label='cubic')  
ax.set_xlabel('x label') 
ax.set_ylabel('y label') 
ax.set_title("Simple Plot")  
ax.legend() 
plt.show()
```



## 绘图模板

```python
# step1 准备数据
x = np.linspace(0, 2, 100)
y = x**2

# step2 设置绘图样式，这一模块的扩展参考第五章进一步学习，这一步不是必须的，样式也可以在绘制图像是进行设置
mpl.rc('lines', linewidth=4, linestyle='-.')

# step3 定义布局， 这一模块的扩展参考第三章进一步学习
fig, ax = plt.subplots()  

# step4 绘制图像， 这一模块的扩展参考第二章进一步学习
ax.plot(x, y, label='linear')  

# step5 添加标签，文字和图例，这一模块的扩展参考第四章进一步学习
ax.set_xlabel('x label') 
ax.set_ylabel('y label') 
ax.set_title("Simple Plot")  
ax.legend();
```

- 对于多个子图可以这样
```python
fig = plt.figure(figsize=(3*idx_cnt, 3*2), dpi=200)
  
data_fig = list(zip(idx_list, zip(data_test[0], data_test[1]), zip(data_pred[0], data_pred[1])))
for i, (idx, tst, prd) in enumerate(data_fig):
    ax = fig.add_subplot(2, idx_cnt, i + 1)
    ax.plot(tst[0].data.numpy(), label='test')
    ax.plot(prd[0].data.numpy(), label='predict')
    ax.set_title('clusters ' + str(idx))
    ax.legend()
    ax = fig.add_subplot(2, idx_cnt, idx_cnt + i + 1)
    ax.plot(tst[1].data.numpy(), label='test')
    ax.plot(prd[1].data.numpy(), label='predict')
    ax.set_title('FT ' + str(idx))
    ax.legend()

plt.show()
```




## references

- [matplotlib初相识](https://datawhalechina.github.io/fantastic-matplotlib/%E7%AC%AC%E4%B8%80%E5%9B%9E%EF%BC%9AMatplotlib%E5%88%9D%E7%9B%B8%E8%AF%86/index.html#id4)
- 