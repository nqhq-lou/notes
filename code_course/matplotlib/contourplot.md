---
title: [contourplot by matplotlib]
tags: [python/module/matplotlib]
---



```Python
作者：沧浪亭美鱼  
链接：
来源：知乎  
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。  
  

import matplotlib.pyplot as plt import numpy as np #以下为等高线图的画法
def f(x,y): #the height function
	return(1-x/2+x**5+y**3)*np.exp(-x**2-y**2) n=256 
	
x=np.linspace(-3,3,n)
y=np.linspace(-3,3,n)
X,Y = np.meshgrid(x,y) #将x,y设置为禁锢在边框中的随机点并且重新赋值X,Y
#use plt.contourf to filing contours #先设置等高图 
plt.contourf(X,Y,f(X,Y),10,alpha = 0.75, cmap = plt.cm.hot) #其中的8代表的是填充8个颜色,透明度。cmap:将每个数字对应在cmap图中有不同的颜色，有hot和cool两种
#再设置等高线
C=plt.contour(X,Y,f(X,Y), 10,colors ='black',linewidth = .5 )
#设置线的参数，数字嵌套在内部，数字的label大小为10
plt.clabel(C, inline = True, fontsize = 10)
plt.xticks(())
plt.yticks(())
plt.show()
```

![|400](https://pic1.zhimg.com/v2-515675e76a21cee033d2dd295808c7c0_b.jpg)

## references
- https://zhuanlan.zhihu.com/p/576424939  