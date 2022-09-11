---
title: joyful pandas comprehensive questions
tags: [python/module/pandas]
---


```python
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import numba
```

有点难欸!

### Ex1
```python
# 1
def get_miss(arr):
    diff = set(range(1,len(arr)+2)).difference(set(arr))
    return list(diff)[0]
  
def get_miss(arr):
    diff = np.diff([0]+sorted(arr))-1
    if (diff==0).all():
    else:
        return int(np.where(diff==1)[0])+1
get_miss(np.array([2,3,4])), get_miss(np.array([6,3,5,1,2])), get_miss(np.array([5,2,1,3,4]))
```

```python
# 2 没想到不用for的方法
def get_res(n:int) -> np.array:
    pass
```

```python
# 3
# @numba.jit(nopython=True)
f = lambda x: abs(np.cumsum(np.random.choice([-1,1],x))).mean()/np.sqrt(x)
plt.hist(np.array([f(5000) - np.sqrt(2/np.pi) for i in range(10000)]), 50)
plt.show()
```

```python
# 4




```

### Ex2




