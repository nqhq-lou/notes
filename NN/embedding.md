---
title: intro embedding
tags: [ML/embedding]
---

## basics
- We could use one-hot for distinguishing items.
	- one-hot is discrete and sparse
- While embedding gives a more compact expression
	- embedding vector is continuous and compact


## how to obtain an embedding
- we could use an MLP to learn an embedding and examine it in the context of other NN.
- d


## example

- from one-hot to embedding
	- the embedding cates are {gender, sweetness, salinity}
|  cate |     one-hot     |     embedding     |
| -----:|:---------------:|:-----------------:|
|   man | \[1,0,0,0,0,0\] | \[0.99,-0.2,0.2\] |
| women | \[0,1,0,0,0,0\] | \[-0.99,0.3,0.1\] |
| apple | \[0,0,1,0,0,0\] |  \[0,0.7,-0.1\]   |
| melon | \[0,0,0,1,0,0\] |  \[0,0.78,0.2\]   |
|  rice | \[0,0,0,0,1,0\] |   \[0,0.4,0.2\]   |
|  salt | \[0,0,0,0,0,1\] |   \[0,0,0.99\]    |


## references
- [神经网络 Embeddings 理解：离散分类变量到连续数向量的映射](https://zhuanlan.zhihu.com/p/420468695)
- d