---
title: Kohn-Sham density functional theory details
tags: [physics/DFT]
---

- most of the content is in reference to 陈默涵
- 



## intro to DFT

- 哈密顿量包含两个部分
	- 多电子系统自身哈密顿量
		- exchange: 满足fermion波函数交换反对称引起的势能
		- correlation: 当前H与真实电子系统的能量差别
	- 外势对应的哈密顿量

- 问题预设
	- 体系分为电子构成的多电子系统, 以及原子核和外场构成的外势
	- 多电子系统的性质全部由电子系统的哈密顿量决定

### Hohenberg-Kohn theorem
- HK好处: 降低求解的自由度, 电子密度仅仅与空间位置相关
- HK1: **系统的基态电荷密度和外势能一一对应**, so-called **V-representability** V表示下的电子密度
	- 证明: 同一系统, 不同外势将对应不同基态电子密度
		- 反证法, 假设两个不同外势能的体系, 分别有基态波函数和能量
- HK2: 可以定义一个电子密度系统能量泛函, 通过求解或者泛函的极小值, 进而得到系统的总能量
	- 泛函的形式? 泛函需要的参数?
	- 外势决定电子密度, 那么有无电子密度不对应任何外势
	- 电子动能关于电子密度的泛函又是什么?
	- 在Thomas Fermi模型中, 电子动能密度的近似为$n(r)^\frac{2}{3}$
		- 其实这直接就是无相互作用独立费米气的最简单结果
		- 但是能量中为$- C_2 n^{4/3}$的交换能是怎么来的?


### Levy-Lieb Principle
so-called **LL方案**, **可以定义一个系统总能量关于电子密度的泛函**
- 分两步进行
	1. 固定电子密度, 能够得到对应这个电子密度的多体波函数, 在这些波函数中寻找能量最低态
		- 也就是在后侧积分作为常数的前提下,  最小化前面的内容
		$$
		E_{LL} [n] = \min_{\psi \rightarrow n(r)} [\bra\psi \hat{T} \ket \psi + \bra\psi \hat{V}_{int} \ket \psi] + \int V_{ext}(r) n(r) d^3 r
		$$
	2. 改变电子密度, 在电子密度组成的态空间中, 找能量最低态
		$$ E_{GS}[n] = \min E_{LL} [n(r)] $$
	3. 循环上述两步, 直到结果收敛
- LL方案中, 电子密度和多体波函数对应 (而不是HK中的外势)
	- so-called **N-representability**, N表示下的电荷密度

> **COMMENT**
> 1. HK从势能出发获得波函数, 没法操作
> 2. LL从多体波函数和迭代出发, 能够操作, 同时能够处理简并态

### KS hypothesis
- 假设: 有相互作用系统的基态电子密度, 可以被一个没有相互作用系统的基态电子密度表示出来
	- 因此可以采用单电子picture, 多体波函数在这个假设下变成了单体波函数
	- 单电子波函数的计算是相对简单的
	- (好像这件事情还没有被证明)
- 关键在于如何match单电子picture下的电子密度, 和实际上实际情况下的电子密度
	- 因此这个方法也是精确的 (如果真的能够match上的话)
	- 有了这个mimic出来的电子密度, 就能进一步计算更多的物理性质 (电子密度比波函数重要!)
- 在单电子picture近似的情况下, 采用的近似为**交换关联能**的近似, 近似的准确度直接决定求解的最终准确度.
	- 这是个比较困难的问题, 可以使用ML的相关方法解决

![[DFT_scheme_disp1.png|400]]

> **COMMENT**
> KS假设直接修改了问题, 之前问题中电子密度求解的问题, 被转化为Exc具体形式问题.
> 同时LL方案在KS假设下也可以继续使用.


## real things

### apply LL principle in KS hypothesis

- LL方案中, 需要优化的内容如下
	- $\psi$为ground truth的多体波函数
	- 按顺序为: 单电子动能, 单电子库伦排斥(Hartree Energy), 单电子交换能, 电子关联能
	$$
	F_{LL} = \min_{\psi \rightarrow n(r)} \bra\psi \hat{T} + \hat{V}_{ee} \ket \psi
	= T_S[n] + E_H[n] + E_X[n] + E_C[n]
	$$
	- 其中单电子库伦排斥只和电子密度相关, 为$E_H = \dfrac{1}{2} \displaystyle\int d^3r d^3r' \dfrac{n(r)n(r')}{ |r-r'| }$
- 考虑动能项目, 可以直接使用单电子波函数计算动能
	- KS假设下, 单电子动能可以泛函 ($\phi_i$为占据的轨道) (S是single)
	$$
	T_S[n] = \min_{\psi \rightarrow n(r)} \bra\psi \hat{T} \ket\psi
	= - \dfrac{1}{2} \sum_{i=1}^{occ} \bra{\phi_i} \nabla^2 \ket{\phi_i}
	$$
	- 因此有相互作用的实际系统, 电子动能可以写为 $T[n] = T_C[n] + T_S[n]$
	- 其中$T_C[n]$为动能的关联函数, 是不知道的东西
- 考虑势能项目, 单电子计算下的势能与实际的势能存在区别
	- 按顺序为: 势能的关联能, 单电子库伦排斥hatree能, 单电子交换能
	$$
	\bra\psi V_{ee} \ket\psi = V_C[n] + E_H[n] + E_X[n]
	$$
	- 这里的$V_C$, 也就是势能的关联能部分, 是单电子势能和势能的差别
- 综上, 关联能量包括两部分: $E_C[n] = T_C[n] + V_C[n]$
	- straight forward 就是动能和势能的交换能部分组成总的交换能
- 关联能的定义为
	$$
	E_C[n] = F_{LL} - (T_S[n] + E_H[n] + E_X[n])
	$$
	- $F_{LL}$为多体波函数得到的, 也就是真实的能量
	- 多体部分和单体部分(单体动能, Hatree势能, 单体交换能)的差值, 就是交换项了

> **COMMENT**
> 单电子搞不定的, 就是交换能的部分
> a problem solved with a new problem found.



## Kohn-Sham 方程

分为几个步骤进行, 得到KS方程

> **COMMENT**
> 已经知道KS系统总能量$E_{KS}$的选择的泛函形式, 希望找到基态的波函数
> 单电子波函数为$\psi_i^\sigma$, $ij$是电子index, $\sigma$是自旋. 单电子波函数之间应当正交.

1. 在KS假设下, 系统总能量对波函数的变分可以写成
	- 找到波函数使得系统的总能量最低, 即处在这个电子密度分布下的基态
	$$
	\dfrac{\delta E_{KS}[n(r)]}{\delta \psi_i^{\sigma*} (r)} = 0
	$$
	- 在次过程中, 单电子波函数正交条件约束为 $\braket{ \psi_i^\sigma (r) | \psi_j^{\sigma'} (r)} = \delta_{ij} \delta_{\sigma \sigma'}$
2. 由于波函数满足正交归一条件, 用Lagrange multiplier $\varepsilon_i^\sigma$, 得到限制下的变分方程为
		$$
		\dfrac{\delta}{\delta \psi_i^{\sigma*} (r)}
		\left[
			E_{KS} - \varepsilon_i^\sigma \sum_{ij}
			\left(
				\int \psi_i^{\sigma*} (r) \psi_j^\sigma (r) d^3 r
				- \delta_{ij} \delta_{\sigma \sigma'}
			\right)
		\right]
		= 0
		$$
	- 化简后得到
	$$
	\dfrac{\delta E_{KS}}{\delta \psi_i^{\sigma*} (r)}
	- \varepsilon_i^\sigma \psi_i^{\sigma}(r)
	= 0
	$$
1. 将Kohn-Sham系统总能量$E_{KS}$的具体形式带入以上方程
	- KS系统总能量为电子密度的泛函, 具体形式和项目如下
	- 按顺序为: 无相互作用系统动能, 电子库伦排斥Hatree能, 外势, 电子交换能, 电子关联能.
		$$
		E_{KS}[n] = T_S[n] + V_{ext}[n] + E_H[n] + E_X[n] + E_C[n]
		$$
	- $K_{KS}$进行$\delta \psi_i^{\sigma*} (r)$后为
	$$
	\begin{aligned}
	\dfrac{\delta E_{KS}}{\delta \psi_i^{\sigma*} (r)}
	=\ & \dfrac{\delta T_{S}}{\delta \psi_i^{\sigma*} (r)}
	+ \left[
	\dfrac{\delta E_{ext}}{\delta n(r, \sigma)}
	+ \dfrac{\delta E_{H}}{\delta n(r, \sigma)}
	+ \dfrac{\delta E_{XC}}{\delta n(r, \sigma)}
	\right] \dfrac{n(r, \sigma)}{\delta \psi_i^{\sigma*} (r)} \\
	=\ & -\dfrac{1}{2}\nabla^2 \psi_i^{\sigma}(r)
	+ \left[
	V_{ext}(r) + V_{H}(r) + V_{XC}^\sigma (r)
	\right] \psi_i^{\sigma}(r)
	\end{aligned}
	$$
	$$
	\begin{aligned}
	H_{KS}^\sigma
	=\ & -\dfrac{1}{2}\nabla^2 + V_{KS}(r) \\
	=\ & -\dfrac{1}{2}\nabla^2 + V_{ext}(r) + V_{H}(r) + V_{XC}^\sigma (r) \\
	=\ & -\dfrac{1}{2}\nabla^2 + V_{ext}(r) + \dfrac{\delta E_{H}}{\delta n(r, \sigma)} + \dfrac{\delta E_{XC}}{\delta n(r, \sigma)}
	\end{aligned}
	$$
	- 带入之前的那个Lagrange乘子法的结果, 就可以得到KS方程为
		- 就是普通的本征值问题
		- 不要忘了单体波函数之间应该是正交的!
	$$
	(H_{KS}^\sigma - \varepsilon_i^\sigma) \psi_i^\sigma(r) = 0
	$$

> **COMMENT**
> XC term中, X可以有自己的形式吗?
> 为什么课程中, 叙述的方式, 看起来觉得C的影响很大?

### total energy
 - 单电子能量中, Hatree能计算的是完整的
 - 因此在汇总体系总能量过程中, 考虑到double-counting, 需要减去一倍的势能
	 - 或者直接就算单个电子的时候就加上1/2的系数








## references
- [陈默涵：密度泛函理论基础](https://www.bilibili.com/video/BV1je4y1Y71P)
	- 从计算流程出发进行解释
- 