---
title: KS-DFT calculation procedure
tags: [physics/DFT/streamline]
---


## purpose
- main problem is that the exact/accurate form functional of the XC term.
- based on [[KS-DFT]] ideas, we should list the detailed operational procedures of calculation.

## plane wave

### 求解KS方程
- KS方程, 形式为
		$$ H \psi_i = \left[ -\dfrac{1}{2} \nabla^2 + V(r) \right] \psi_i = E_i \psi_i $$
	- H矩阵是Hermite matrix
- 基矢的数量决定了H矩阵的大小
	- 可以选取planewave basis, gaussian basis, numerical atomic orbit
		- 不知道的: LMTO, O(N), LAPW
	- 求解H矩阵的eigen problem, 是KS-DFT中用时最长的项目
- 对于每一个Bloch wave的k-point
	- Bloch wave $\psi(r+R_n) = e^{i k \cdot R_n} \psi(r)$
	- 每个k-point都需要求解一下KS方程
	- 也就是
		$$ H_k \psi_{ik} = \left[ -\dfrac{1}{2} \nabla^2 + V(r) \right] \psi_{ik} = E_{ik} \psi_{ik} $$
	- 然后就能得到能带图了!



## pseudo-potential




## XC functional
- How the functionals are developed
- and how ML are applied




## electron iteration procedure
- electron density 2 Hamiltonian 2 eigen problem 2 new wave function and new electron density
- so iterative, actually self-consistent field method (SCF)
- d



## references
- [陈默涵：密度泛函理论计算流程](https://www.bilibili.com/video/BV1GU4y1r7RA)


