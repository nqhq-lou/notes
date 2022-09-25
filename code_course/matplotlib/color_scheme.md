---
title: color scheme
tag: [python/module/matplotlib]
---




## 绘图样式 style

- 常用三种方法: 修改预定义样式, 自定义样式, `rcparams`

### 预定义样式
- `plt.style.use(str)`
	- `default, ggplot`, etc
- 查看所有可用style: `print(plt.style.available)`
```python
['Solarize_Light2', '_classic_test_patch', 'bmh', 'classic', 'dark_background', 'fast', 'fivethirtyeight', 'ggplot', 'grayscale', 'seaborn', 'seaborn-bright', 'seaborn-colorblind', 'seaborn-dark', 'seaborn-dark-palette', 'seaborn-darkgrid', 'seaborn-deep', 'seaborn-muted', 'seaborn-notebook', 'seaborn-paper', 'seaborn-pastel', 'seaborn-poster', 'seaborn-talk', 'seaborn-ticks', 'seaborn-white', 'seaborn-whitegrid', 'tableau-colorblind10']
```


### 用户自定义 stylesheet
- 在任意路径下创建一个后缀名为mplstyle的样式清单，编辑文件添加以下样式内容
```text
axes.titlesize : 24  
axes.labelsize : 20  
lines.linewidth : 3  
lines.markersize : 10  
xtick.labelsize : 16  
ytick.labelsize : 16
```
- 引用自定义stylesheet后观察图表变化。
```python
plt.style.use('file/presentation.mplstyle')
plt.plot([1,2,3,4],[2,3,4,5]);
```
![|400](https://datawhalechina.github.io/fantastic-matplotlib/_images/index_8_01.png)

- 支持多种样式混用
	- 输入列表, 当涉及同样参数时, 右侧样式覆盖左侧值
```python
plt.style.use(['dark_background', 'file/presentation.mplstyle'])
plt.plot([1,2,3,4],[2,3,4,5]);
```
![|400](https://datawhalechina.github.io/fantastic-matplotlib/_images/index_10_01.png)


### 设置rcparams
```python
plt.style.use('default') # 恢复到默认样式
mpl.rcParams['lines.linewidth'] = 2
mpl.rcParams['lines.linestyle'] = '--'
# mpl.rc('lines', linewidth=4, linestyle='-.')  # 一次性修改多个样式
plt.plot([1,2,3,4],[2,3,4,5]);
```
![|400](https://datawhalechina.github.io/fantastic-matplotlib/_images/index_13_02.png)



## 色彩设置 color

- 分为单颜色和多颜色方法
	- 单颜色: 5种常用方法
	- 多颜色: `colormap`

从可视化编码的角度对颜色进行分析，可以将颜色分为**色相、亮度和饱和度**三个视觉通道。通常来说:
- **色相**： 没有明显的顺序性、一般不用来表达数据量的高低，而是用来表达数据列的类别。  
- **明度和饱和度**： 在视觉上很容易区分出优先级的高低、被用作表达顺序或者表达数据量视觉通道。

RGB和HEX RGB转换: [ColorHexa](https://www.colorhexa.com/)

### RGB或RGBA
```python
plt.style.use('default')
# 颜色用[0,1]之间的浮点数表示，四个分量按顺序分别为(red, green, blue, alpha)，其中alpha透明度可省略
plt.plot([1,2,3],[4,5,6],color=(0.1, 0.2, 0.5))
plt.plot([4,5,6],[1,2,3],color=(0.1, 0.2, 0.5, 0.5));
```
![|400](https://datawhalechina.github.io/fantastic-matplotlib/_images/index_18_0.png)

### HEX RGB或RGBA
```python
# 用十六进制颜色码表示，同样最后两位表示透明度，可省略
plt.plot([1,2,3],[4,5,6],color='#0f0f0f')
plt.plot([4,5,6],[1,2,3],color='#0f0f0f80');
```
![|400](https://datawhalechina.github.io/fantastic-matplotlib/_images/index_20_0.png)

### 灰度色阶
```python
# 当只有一个位于[0,1]的值时，表示灰度色阶
plt.plot([1,2,3],[4,5,6],color='0.5');
```
![|400](https://datawhalechina.github.io/fantastic-matplotlib/_images/index_22_0.png)

### 单字符基本颜色
```python
# matplotlib有八个基本颜色，可以用单字符串来表示，分别是'b', 'g', 'r', 'c', 'm', 'y', 'k', 'w'，对应的是blue, green, red, cyan, magenta, yellow, black, and white的英文缩写
plt.plot([1,2,3],[4,5,6],color='m');
```
![|400](https://datawhalechina.github.io/fantastic-matplotlib/_images/index_24_0.png)

### 颜色名称
```python
# matplotlib提供了颜色对照表，可供查询颜色对应的名称
plt.plot([1,2,3],[4,5,6],color='tan');
```
![|400](https://datawhalechina.github.io/fantastic-matplotlib/_images/index_26_0.png)

![|600](https://matplotlib.org/3.1.0/_images/sphx_glr_named_colors_002.png)
![|600](https://matplotlib.org/3.1.0/_images/sphx_glr_named_colors_003.png)

### 使用colormap设置一组颜色
在matplotlib中，colormap共有五种类型:
- 顺序（Sequential）。通常使用单一色调，逐渐改变亮度和颜色渐渐增加，用于表示有顺序的信息
- 发散（Diverging）。改变两种不同颜色的亮度和饱和度，这些颜色在中间以不饱和的颜色相遇;当绘制的信息具有关键中间值（例如地形）或数据偏离零时，应使用此值。
- 循环（Cyclic）。改变两种不同颜色的亮度，在中间和开始/结束时以不饱和的颜色相遇。用于在端点处环绕的值，例如相角，风向或一天中的时间。
- 定性（Qualitative）。常是杂色，用来表示没有排序或关系的信息。
- 杂色（Miscellaneous）。一些在特定场景使用的杂色组合，如彩虹，海洋，地形等。
```python
x = np.random.randn(50)
y = np.random.randn(50)
plt.scatter(x,y,c=x,cmap='RdPu');
```
![|400](https://datawhalechina.github.io/fantastic-matplotlib/_images/index_28_0.png)

- 在以下官网页面可以查询上述五种colormap的字符串表示和颜色图的对应关系
	- [https://matplotlib.org/stable/tutorials/colors/colormaps.html](https://matplotlib.org/stable/tutorials/colors/colormaps.html)