---
title: custom color in matplotlib.pyplot
tags: [python/module/matplotlib]
---


- for built-in color schemes
	- see [pyplot cmap颜色](https://zhuanlan.zhihu.com/p/114420786)

```Python
# colors = plt.cm.Set3(numpy.linspace(0, 1, 10))  # discrete color scheme
colors = plt.cm.coolwarm(numpy.linspace(0, 1, 10))  # continuous color scheme
  
arr = numpy.random.randn(10,20) + 2*numpy.arange(0,10).reshape(-1,1)
for i, x in enumerate(arr):
    plt.plot(x, label=f'mean={x.mean():.3f} std={x.std():.3f}', color=colors[i])
plt.grid()
plt.legend()
plt.show()
```





