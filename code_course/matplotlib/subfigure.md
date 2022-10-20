---
title: matplotlib subfigure
tags: [python/module/pandas]
---



## subfigure

### 均匀子图
- `plt.subplots`
	- 本质上是`Figure.add_subplot`的封装
```python
fig, axes = plt.subplots(2, 5, figsize=(5*2, 2*2), sharex=True, sharey=False)  # 共用x轴, 不共用y轴
fig.suptitle("样式1", size=20)  # superior title的大小
  
def _plot(ax, **kwargs):  # i 行，j 列
    data = {"x": np.random.randn(100), "y": np.random.randn(100)}
    ax.scatter(data["x"], data["y"])
    ax.set_title(kwargs.get("title", "no title"), size=15)
    ax.set_ylim(data["y"].min()-0.5, data["y"].max()+0.5)
    if kwargs.get("i") == 1:
        ax.set_xlabel("横坐标", size=15)
    elif kwargs.get("j") == 0:
        ax.set_ylabel("纵坐标", size=15)
  
[_plot(axes[i][j], i=i, j=j, title=f"第{i}行 第{j}列") for i in range(2) for j in range(5)];
fig.tight_layout()
```
![[subfigure1.png]]

- `plt.subplot`
	- 本质上是`Figure.add_subplot`的封装
```python
plt.figure()
# 子图1
plt.subplot(2,2,1) 
plt.plot([1,2], 'r')
# 子图2
plt.subplot(2,2,2)
plt.plot([1,2], 'b')
#子图3
plt.subplot(224)  # 当三位数都小于10时，可以省略中间的逗号，这行命令等价于plt.subplot(2,2,4) 
plt.plot([1,2], 'g');
```


### 非均匀子图
- `fig.add_gridspec`
	- 通过切片`spec[0,:3]`
```python
fig = plt.figure(figsize=(10, 4))
spec = fig.add_gridspec(nrows=2, ncols=6, width_ratios=[2,2.5,3,1,1.5,2], height_ratios=[1,2])
fig.suptitle('样例3', size=20)
  
def _plot(fig, spec, **kwargs):
    ax = fig.add_subplot(spec)
    ax.scatter(np.random.randn(100), np.random.randn(100))

[_plot(fig, s) for s in [spec[0, :3], spec[0, 3:5], spec[:, 5], spec[1, 0], spec[1, 1:5]]];
fig.tight_layout()
```
![[subfigure3.png]]



## method of subfigure

- 常用画法为 `axhline, axvline, axline`, 分别为水平 垂直 任意方向

```python
fig, ax = plt.subplots(figsize=(4,3))
ax.axhline(0.5,0.2,0.8)  # 画水平线
ax.axvline(0.5,0.2,0.8)  # 画竖直线
ax.axline([0.3,0.3],[0.7,0.7]);  # 任意两点连线
ax.grid(True)  # 增加网格
ax.set_xscale('log')  # 坐标度规
ax.set_yscale('log')
fig.tight_layout()  # 重整布局
```





## references
- [第三回：布局格式定方圆](https://datawhalechina.github.io/fantastic-matplotlib/%E7%AC%AC%E4%B8%89%E5%9B%9E%EF%BC%9A%E5%B8%83%E5%B1%80%E6%A0%BC%E5%BC%8F%E5%AE%9A%E6%96%B9%E5%9C%86/index.html)