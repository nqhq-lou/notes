---
title: Do VAE with GNN
tags: [NN/GNN, NN/VAE]
---


## on a review article

### metas on graph embedding

- Core problems
	- 学习node和(sub)graph的低维embedding
	- 常见的graph结构信息: 节点的global position, 节点的局部临近结构(structure of the node's local graph neighborhood)
- Targets
	- 能够让embedding space中的几何关系反应原始graph的结构信息
	- learn embedding that encode graph structure

### method categories

- Matrix factorization
	- 用矩阵刻画graph信息,并且分解矩阵, 学习节点的低维向量表示
	- e.g. Graph Laplacian Eigenmaps, Graph Factorization
- Random walk
	- 随机游走, 构建上下文的共现对
	- e.g. DeepWalk, Node2Vec
- Graph convolutional networks
	- GNN的卷积, 基于节点local neighborhoods的汇聚
	- e.g. GCN, GraphSAGE

### Encoder-Decoder Framework

- Encoder: 目标是将每个Node映射编码成低维的向量表示, 或embedding
	- 信息包含节点的全局信息和局部临近信息, 用于后续的机器学习任务
$$
ENC: \mathcal{V} \rightarrow \mathbb{R}^d
$$

- Decoder: 目标是利用Encoder输出的Embedding, 来解码关于图的结构信息
	- 输入上述encoder的embedding, 给出需要的graph的结构信息, 如两个vertex之间是否连接
	- 最常用的是pairwise decoder
		- 给入node pair的embeddings, 给出一个实数, 衡量两者在原始graph中的相似性
$$
DEC: \mathbb{R}^d \times \mathbb{R}^d \rightarrow \mathbb{R}^+
\qquad \text{(pairwise decoder)}
$$
$$
DEC(ENC(v_i),ENC(v_j)) = DEC(z_i,z_j) \approx s_\mathcal{G}(v_i,v_j)
\qquad
\mathcal{L} = \sum_{(v_i,v_j)\in\mathcal{D}} \mathcal{L} (DEC(z_i, z_j), s_\mathcal{G} (v_i,v_j))
$$
上述框架涉及到4大组件：
- **Pairwise Similarity Function**, $s_\mathcal{G}: \mathcal{V} \times \mathcal{V} \rightarrow \mathbb{R}^+$, 定义在原始Graph上，衡量了节点之间的相似性。可以看做是pairwise "ground truth" label在Loss中使用，只不过这个ground truth通常是无监督的，反映了原始图的拓扑结构。
- **Encoder Function**，ENC ，产生节点的embedding。这个函数包含了训练参数，最常使用的是embedding lookup操作，即每个节点学习一个自己的embedding表示，不同节点之间**不存在**参数共享。在decoder中使用。
- **Decoder Function**，DEC ，基于embeddings，重构Node相似性。通常不包含训练参数。例如使用点乘、欧式距离等来表示相似性。可以看做是estimated label在Loss中使用，定义了node pair在embedding空间的相似性。
- **Loss Function**, 评判重构好坏，即对比$DEC(z_i,z_j)$和$s_G(v_i,v_j)$。融合了decoder的estimated label和pairwise similarity function的ground truth label来构造损失，指导学习。

### disadvantages

- encoder没有参数共享, 图大时过高的参数量
- 不能建模node的属性
- 不能加入新的node


### further improvements

- SDNE (Structural Deep Network Embeddings)
	- encode时使用到图的结构, 使用AutoEncoder完成encode的过程
	- 实际上为压缩节点的邻居信息到低维空间作为embedding
- GCN (Graph Convolutional Networks)
	- encode的时候，会利用卷积操作来汇聚**Local Neighborhoods**的节点的属性信息，并叠加多层网络，形成节点的embedding表示
	- Decoder和Loss可以使用前面提到的任意方法



## other models

### GraphSAGE

- 基于邻域节点的特征汇聚
![GraphSAGE embedding generation | 500](https://pic2.zhimg.com/80/v2-0431eb2afe060f21b858df8b7bb63bd9_720w.webp)

- 最重要的时aggregator这一步
	- Mean: 直接平均, element-wise
	- GCN: 用一步图卷积
	- LSTM: 直接对邻域节点随机扰动permutation，然后将扰动后的序列使用LSTM来聚合
		- 没看懂干什么的
	- Pooling: 通过一个MLP和activation, 然后element-wise max pooling

### GATs

- 采用了attention
	- 节点$i$ attend到$j$的attention ($j$包括自身)
$$
\begin{aligned}
\alpha_{ij} & = \mathrm{softmax}(\mathrm{attention}(W h_i, W h_j))
= \mathrm{softmax}(e_{ij}) \\
e_{ij} & = \mathrm{LeakyReLU}(a[W h_i, W h_j]) \\
h_i' & = \sigma(\sum_{j \in N_i, i} \alpha_{ij} W h_j)
\qquad \text{(线性变换后按attention加权并激活即可)}
\end{aligned}
$$







## references

- [图表示学习Encoder-Decoder框架 from Zhihu](https://zhuanlan.zhihu.com/p/106726538)



