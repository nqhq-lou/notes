---
title: pseudo-potential and basis collection in DFT
tags: [physics/DFT]
---


## pseudo-potential
- the counterpart to pseudopotential method (PP) is all-electron method (AE).

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
- 

### LMTO
- linear muffin-tin orbitals
- 

### LAPW
- linearized augmented plane wave
- 





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