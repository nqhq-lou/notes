---
title: pseudo-potentials, basis collection and exchange-correlation functionals in DFT
tags: [physics/DFT/PP, physics/DFT/XC, physics/DFT/basis]
---


## pseudo-potential
- the counterpart to pseudopotential method (PP) is all-electron method (AE).
- 应当注意到, XC泛函和赝势是关联的, 因为需要赝势+XC泛函的计算结果, 根据原子能级进行对齐!

### NC
- norm-conserving pseudopotential, 模守恒赝势
- 适用于LCAO和平面波两种ji'zu

### US
- ultrasoft pseudopotential, 超软赝势

### PAW方法(不是赝势)
- projector augmented wave, 投影缀加平面波
- 仅适用于平面波基组
- 但是它能很好再现近核电子的行为, 因此有时可以使用较小的基组完成计算








## basis

### PW
- 一般使用赝势, 也就是PP-PW

### LCAO
- linear combination of atomic orbitals
- 可以使用全势, 也就是FP-LCAO

### APW
- augmented plane wave
- [[APW method]]

### LAPW
- linearized augmented plane wave
- [LAPW details from WIEN2k](http://www.wien2k.at/lapw/)

### KKR
- Korring 1947, Kohn Rostoker 1954
- 先把单电子运动方程化为积分方程, 再用散射方法求解能态
- 在计算中使用格林函数
- 成功用于计算金属能带, 推广后可以处理无序体系

### MTO
- muffin-tin orbitals

### LMTO
- linear muffin-tin orbitals

### OPW
- Orthogonalized Plane Wave Method
- 取波函数为平面波和紧束缚波函数的线性组合, 并要求与离子实不同壳层紧束缚波函数正交
- 自然地兼顾了波函数在离子实附近以及在离子之间应有的特征






## XC functionals

- 选择泛函的基本原则
	- 应当尽量使用简单的泛函完成计算
	- 如果简单泛函无法得到合理结果, 才会考虑更加复杂的泛函, 以及校正选项
		- 因为基于经验参数的校正选项可能带来意想不到的误差
	- dd


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
- B3LYP
- M06-2X
- $\omega$B97X



### 校正项目
- Hubbard+U, 范德华力, DFT-1/2等经验参数矫正选项












## references
- [VASP赝势简介](http://www.52souji.net/2652.html)
	- 非常简略...
- [固体DFT计算设置入门教程](https://zhuanlan.zhihu.com/p/87619057)
	- 内容充足, 包括基组/赝势/泛函的解释和设置推荐
- [密度泛函理论（转载）](https://blog.sciencenet.cn/blog-3330179-1194465.html)
	- 包括商业软件具体apply的方法
- [能带结构的计算方法](https://epsilon.ustc.edu.cn/assets/5.6-band-theory--calculation-methods.pdf)
	- 课程slides pdf
	- 讲了 原胞法, APW, Green, OPW正交平面波, PP赝势, KS-DFT 
	- ***可以读一读!***
- [固体DFT计算设置入门教程](https://zhuanlan.zhihu.com/p/87619057)
	- 内容充足, 包括基组/赝势/泛函的解释和设置推荐
- [Hybrid Functionals](https://docs.quantumatk.com/manual/technicalnotes/hybrid_functionals/hybrid_functionals.html)
	- 杂化泛函, 讲了一点点理论


