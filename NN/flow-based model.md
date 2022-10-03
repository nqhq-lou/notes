---
title: flowed-based model
tags: []
---



## 之前方法的defects

- diffusion model
	- 生成速度慢
- VAE
	- lower bound难于进行优化
- GAN
	- 训练不稳定




## 基础想法

- 隐空间变量为高斯分布
- 在高斯分布中采样, 通过Generator生成尽量和数据分布相同的分布
	- $\pi$ 指代高斯分布, $i$ 指代数据集中数据点
$$
\pi(z) \longrightarrow x = G(z) \longrightarrow 
p_G(x)  \approx p_{real}(x)
$$

- 在这里应该使用maximum likehood进行拟合, 但是KL散度也是差不多可以有相同的作用的, 那就直接用KL散度把
	- 这里应该就是cross entropy吧? 最小化 $-\sum p_{data}(x^i) \log p_G(x^i)$
	- 那这样我感觉对第一行不是很理解

$$
\begin{aligned}
G^* =&\ \arg \max_G \sum_{i=1}^m \log p_G(x^i) \\
=&\ \arg\min_G \mathbb{KL}(p_{data} || p_G) \\
=&\ \arg\min_G \sum_{i=1}^m p_{data}(x^i) \log \dfrac{p_{data}(x^i)}{p_G(x^i)}
\end{aligned}
$$


### 概率变换 (change of variable theorem)
- 在从隐空间到预测空间的变换$\pi$中, 可以使用Jacobian描述某个点映射前后, 概率幅的变化
	- $x = G(z) \qquad p(x) = \pi(z) \cdot |\mathcal{J}(z,x)| = \pi(z) \left|\frac{dz}{dx}\right|$
- 视频中给出了一个正方形变菱形的直观推导
$$
\begin{aligned}
x =&\ G(z) \\
p(x) \Delta x =&\ p(z) \Delta z \\
p(x) |det(\mathcal{J}_G)| =&\ \pi(z) \\
p(x) =&\ \pi(z) |det(\mathcal{J}_G^{-1})| \\
\end{aligned}
$$
- 同时应该注意到, $\mathcal{J}_G^{-1} = \mathcal{J}_{G^{-1}}$

### 优化对象

$$
\begin{aligned}
G^* =&\ \arg \max_G \sum_{i=1}^m \log p_G(x^i) \\
p_G(x^i) =&\ \pi(z^i) |\det(\mathcal{J}_G^{-1})| \\
z^i =&\ G^{-1}(x^i) \\
\log p_G(x^i) =&\ \log \pi(G^{-1}(x^i)) + \log |\det(\mathcal{J}_G^{-1})| \\
\end{aligned}
$$
- 要优化最后一个式子, 就要知道训练中具体是什么样子
- 可能Jacobian很大, 导致计算带来问题
- 需要好好涉及generator的样子, 方便计算Jacobian和它的inverse

### 网络和损失函数设计
- 网络设计
	- input和output的dimension是一样的
	- 可以进行多次flow, 也就是多个jacobian乘起来
- 损失函数
	- 形式表达:
		- $p_k(x^i) = \pi(z^i)(|\det(\mathcal{J}_{G_1}^{-1}|)\cdots(|\det\mathcal{J}_{G_k}^{-1}|)$
	- 对应的优化对象:
		- $\arg \max_G \log p_G(x^i) = \log \pi(G^{-1}(x^i)) + \sum_k \log |\det(\mathcal{J}_{G_k}^{-1})|$
	- 理解
		- 第一项最大时, $G^{-1}$生成的都是$\vec{0}$, 但是这会导致第二项log后为-inf
		- 因此第一项使得生成的隐空间变量尽量集中(在0附近), 第二项保证不过与集中(而导致出现零向量的情况)

### 具体网络设计
- 知名的model: NICE, Real NVP
	- 使用了相同的构建flow的方式: coupling layer
- 具体一次flow的方法
	- 将latent分开成两部分, 一部分直接传递, 同时用于生成F和H
	- 剩余的latent部分分别乘上F并加上, 得到这个部分的更新
- Jacobian计算
	-  之间的关联非常简单, 矩阵分为四个部分
	- 直接copy部分时identity
	- 处理的部分是一个线性映射, 因此diagonal, 非常方便计算jacobian
	- 具体见下二图

![[flow-based_model_01.png|500]]
![[flow-based_model_02.png|500]]


### 训练过程
- 实际上我们训练$G^{-1}$, 也就是从$x^i$到$z^i$
- 但是使用$G$进行生成






## references
- [LHY P86 Flowed-based Generative Model](https://www.bilibili.com/video/av69736833/?p=86&vd_source=abde52485befe3b1269211c68fdf85fb)



