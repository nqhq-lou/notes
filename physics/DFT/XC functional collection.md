---
title: XC functional collection
tag: [physics/DFT/XC]
---


- 选择泛函的基本原则
	- 应当尽量使用简单的泛函完成计算
	- 如果简单泛函无法得到合理结果, 才会考虑更加复杂的泛函, 以及校正选项
		- 因为基于经验参数的校正选项可能带来意想不到的误差
	- dd

## traditional XC functionals

### LDA
- local density approximation
- 局域泛函, 速度最快
- 使用均匀电子气来计算体系的交换能（均匀电子气的交换能是可以精确求解的），而相关能部分则采用对自由电子气进行拟合的方法来处理。

### GGA / MetaGGA
- generalized gradient approximation
- 半局域泛函, 引入电子密度梯度项目
- 分为
	- PW91(Perdew-Wang 91)
	- PBE(Perdew-Burke-Ernzerhof)

### SCAN
- Strongly Constrained and Appropriately Normed Semilocal Density Functional
- 是MetaGGA的一种

### Hybrid functionals

### 校正项目
- Hubbard+U, 范德华力, DFT-1/2等经验参数矫正选项







## references
- [固体DFT计算设置入门教程](https://zhuanlan.zhihu.com/p/87619057)
	- 内容充足, 包括基组/赝势/泛函的解释和设置推荐
- [Hybrid Functionals](https://docs.quantumatk.com/manual/technicalnotes/hybrid_functionals/hybrid_functionals.html)
	- 杂化泛函, 讲了一点点理论