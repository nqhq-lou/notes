---
title: matplotlib subfigure
tags: [python/module/pandas]
---



## subfigure

### 均匀子图
- `plt.subplots`



### 非均匀子图
- `fig.add_gridspec`





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
- [第三回：布局格式定方圆[¶](https://datawhalechina.github.io/fantastic-matplotlib/%E7%AC%AC%E4%B8%89%E5%9B%9E%EF%BC%9A%E5%B8%83%E5%B1%80%E6%A0%BC%E5%BC%8F%E5%AE%9A%E6%96%B9%E5%9C%86/index.html#id1 "永久链接至标题")](https://datawhalechina.github.io/fantastic-matplotlib/%E7%AC%AC%E4%B8%89%E5%9B%9E%EF%BC%9A%E5%B8%83%E5%B1%80%E6%A0%BC%E5%BC%8F%E5%AE%9A%E6%96%B9%E5%9C%86/index.html)