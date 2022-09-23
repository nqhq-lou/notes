---
title: useful_preamble
tags: [python/module/pandas]
---

```python
# 基本包导入
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# rcParams调整
plt.rcParams['font.sans-serif'] = ['SimHei']   #用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False   #用来正常显示负号

# 细节调整
import matplotlib as mpl
mpl.rcParams["mathtext.fontset"] = "custom"
mpl.rcParams["mathtext.rm"] = "Times New Roman"
mpl.rcParams["mathtext.it"] = "Times New Roman"
mpl.rcParams["mathtext.bf"] = "Times New Roman"
mpl.rc("font", family="serif", size="16")

# 绘制图形用
from matplotlib.lines import Line2D   
from matplotlib.patches import Circle, Wedge
from matplotlib.collections import PatchCollection

# 设置日期格式
import matplotlib.dates as mdates
```

