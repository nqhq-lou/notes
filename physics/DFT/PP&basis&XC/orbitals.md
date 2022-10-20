---
title: generals on orbitals
tags: [physics/DFT/orbitals]
---

- basis set
- Slater-Type Orbital, STO
	- 指的是用斯莱特型函数模拟原子轨道，用斯莱特型函数构成的基组具有明确的物理意义，能够较好的描述电子云的特征，缺点是在计算多中心双电子积分时，计算量很大。
- Gaussian Type Orbital, GTO
	- 高斯型轨道是指用高斯型函数替代原来的斯莱特型函数去模拟原子轨道，高斯型函数基组的优点是易于计算，但不能很好地描述原子轨道的特征。
- Contracted GTO, CGTO
	- 为了兼具斯莱特型函数和高斯型函数的优点，将多个GTO线性组合压缩成一个STO轨道，就构成了所谓的压缩高斯型轨道。压缩高斯型基组是目前使用最多的基组。
- minimal basis set
	- 当我们用三个GTO线性组合压缩成一个STO时，就构成了最小基组，表示成STO-3G（这个符号的意义是3个GTO压缩成一个STO），它是规模最小的压缩高斯型基组。由于基组规模较小，计算量也就小，但计算精度不高。
- Split-valence basis set
- Polarization function
- Diffuse function
- Full-electron basis set
	- 内层和外层的电子都用基函数来表示
	- e.g. 6-31G, 6-31+G\[d\]






## references
- [Gaussian教程 | 使用基组和赝势](http://blog.molcalx.com.cn/2017/11/30/gaussian-tutorial-basis-set.html)
- d


