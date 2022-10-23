---
title: pprojected augmented wave
tags: [physics/DFT]
---

## initialization

- 使用基组/基函数的线性组合表示波函数
	- $\phi(x) = \sum_i c_i \xi_i(x)$
- 薛定谔方程就会变成
	- $\sum_i \hat{H} \xi_i(x) c_i = E \sum_i \xi_i(x)$
- 考虑适当基组
	- 让基组尽量契合函数的形式
		- 用原子轨道的想法, 拟合分子中的波函数
	- 函数本身不能太复杂
		- 用平面波去拟合周期性体系的波函数, 更符合周期性体系的特征
	- 希望将上面的两个想法结合起来



## for atoms

- 体系中存在重原子, 因此函数震荡较多, 难以拟合
- 修改Sch方程, 算符$\hat{T}$代表波函数的变换?
$$
\psi(x) = \hat{T} \phi(x)
\qquad
\phi(x) = \hat{T}^{-1} \psi(x)
$$
$$
\hat{H} \psi(x) = E \psi(x)
\quad \rightarrow \quad
\hat{H} \hat{T} \phi(x) = E \hat{T} \phi(x)
\qquad
\hat{T}^{-1} \hat{H} \hat{T} \phi(x) = E \phi(x)
$$
- 这里等效修改了Hamiltonian
- 这里找到一个合适的变换, 使得新的$\phi$并不会像原本的波函数$\psi$一样震荡剧烈
- 这样描述时就可以减少需要的基组

## procedure

- 给定原子轨道基组$\psi_A(x)$, 进行平滑得到$\phi_A(x)$
- 计算变换算符$\hat{T} = 1 + \sum_A (\ket{\psi_A} - \ket{\phi_A}) \bra{\phi_A}$
- 对变换后的哈密顿量求解本征值
	- $\hat{T}^{-1} \hat{H} \hat{T} \phi = E \phi$
	- 其中$\phi = \sum_A c_A \phi_A$, 这里cA就是组合系数, 并不和上面的组合系数重合
	- 将结果变换回原来的轨道基组$\psi = \hat{T} \phi$



## references
- [PAW（Projected augmented wave）算法介绍](https://zhuanlan.zhihu.com/p/575479762)



