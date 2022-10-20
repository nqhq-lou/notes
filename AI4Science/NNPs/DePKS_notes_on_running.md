---
title: notes on running DeePKS models
tags: [project/DeePKS]
---


## 0923
[[09-23-22]]

### summary
- 自动OMP threads = 56
- scf中同时计算trn和tst? 没搞懂

### results



### further integration



## 0922
[[09-22-22]]

### summary
- run the examples of deepks-kit (pyscf based)
	- water, single molecule
	- water, cluster (1, 2, 3 atoms)
- 命名规则s
	- 多用数字, 表明iter的次数
	- 多用文件夹
	- 参数中
		- `_input` 指代软件相关的参数
		- `_machine` 指代
		- `init_` 指代第一次的结果云云

### results
- 全程核心使用量在20左右
- scf的起始点
	- DeePHF求解的结果作为首次迭代的输入
- 神经网络拟合时间很短
	- 100frames, 1 water molecule
	- $100*1*3=1800$ items
	- 17:22:14 2600; 17:47:20 3400
	- 那么这里用
	- average time: 5ms/epoch
	- stop training: ~5000epochs
- 现在的猜测是, 因为训练中scf的时间很长
	- 看看scf发生什么问题了
	
### further integration
- 对于deepks的水分子训练结果的迁移测试, 我觉得应该用test的部分进行测试
	- 有现成能用的`deepks scf`, 见water cluster的说明文档
- 一个简单的测试方法
	- 用DeePHS算一步, 作为对比的结果
	- 用水cluster训练出来的结果, 迁移到甲烷上进行测试
- 记得调整machine设置
	- pyscf的max_memory到100GB
	- 设定核心数量限制, 我觉得32比较合适? 害怕被打

