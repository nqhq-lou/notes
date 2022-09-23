## basic idea
- 传统势函数
	- QM计算结果, 结果精确但是计算开销大
	- 经验势函数, 有相应的参数(数十个), 通过数学形式mimic物质行为
- 机器学习势
	- 建立从几何特征(描述符)到原子势能的映射
		- 描述符需要满足若干不变性, 如平移, 转动, 同类原子置换不变
	- 机器学习势能模型中, 待定参数多
		- 约为几千到几百万个不等
	- 训练过程
		- 训练集为QM计算产生的
		- 实际上是网络对QM计算结果的拟合


## current progresses

### Behler et al.
- [Generalized Neural-Network Representation of High-Dimensional Potential-Energy Surfaces](https://doi.org/10.1103/PhysRevLett.98.146401)
	- the first work
- Proposed Behler's symmetry functions





## descriptors

![[descriptors_proposed.png]]
This image is from [Neuroevolution machine learning potentials: Combining high accuracy and low cost in atomistic simulations and application to heat transport](https://journals.aps.org/prb/abstract/10.1103/PhysRevB.104.104309)




## references
- [NEP机器学习势能简介](https://mp.weixin.qq.com/s/1_ihEF33hVFfW2iDq72POg)
- dd