---
title: KS-DFT calculation procedure
tags: [physics/DFT/streamline]
---


## purpose
- main problem is that the exact/accurate form functional of the XC term.
- based on [[KS-DFT basics]] ideas, we should list the detailed operational procedures of calculation.

## plane wave
- 本节讨论平面波基矢下, KS方程求解的相关事宜.
- 缩写PW为平面波, 有可能指代平面波基矢

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

### FFT在计算中的角色
- DFT中的傅里叶变换FFT
	- FFT复杂度是$\mathcal{O} (N \log N)$
- FFT是PWDFT的核心操作和关键的耗时步骤
	- FFT用于求解本征值和本征向量的过程中
	- 见下
- 几个计算
	- PW导数 $\nabla_r^2 e^{i G \cdot r} = |G|^2 e^{i G \cdot r}$
	- PW basis下的Hamiltonian $H_{ij} = \bra{G_i} \hat{T} + \hat{V} \ket{G_j}$
		- 势能, 在实空间中的矩阵为对角矩阵
		- 动能, 在倒空间中的矩阵为对角矩阵
		- 因此分别在实空间和倒空间分别求势能和动能矩阵之后, 通过FFT变换到实空间
		- 进行完计算后, 再用FFT变回倒空间

### 能量截断和基矢数量
- PW basis数量增加, 有助于计算结果收敛
	- 增加基矢数量, 能够拟合更加复杂的图形
	- 如遇到电子波函数在势能大的情况下短距离内多次抖动, 就需要更高频的PW分量加入fit
- 但是此时我们也要选取动量的合适的截断, 因为过高能量可能是没有意义的
	- 因此需要有效的方法检查PW是否足够用, 也就是计算结果是否有效收敛
- 如何检查PW收敛:
	- 增加能能量截断值(等效增加PW的个数), 直到系统总能量收敛
	- 虽然在经典的势场中很少这样测试, 但是正式计算性质前, 必须要进行这样的验证操作.
- 基矢数量随函数性质的修改
	- 如果波函数使用一倍的基矢数量, 那么电子密度需要使用两倍以上的基矢数量
	- 因为波函数乘得电子密度的过程中, 陡峭的地方将会变得更加陡峭
	- 需要更多的基矢对电子密度进行准确描述
	- VASP能够根据用户设置的精度, 对波函数和电子密度的基矢数量比例进行自动设定.
- 基矢数量随能系统大小的修改
	- 系统增大两倍, 应当保持能量截断不变, 而不是PW数目不变
	- 这样能够仍然以足够高的精度描述物理

### 平面波计算的特点
- 哈密顿矩阵中, 对上百个原子, PW数量可以达到100k量级, 哈密顿量很大, 并不适合都放在cache
	- 一般用更巧妙的方法处理
- 对角化操作的计算复杂度为$\mathcal{O}(n^3)$, 或者更加接近$\mathcal{O}(n^2 \times n_{bands})$
- 所以PW basis下Hamitonian的对角化是DFT计算的瓶颈



## pseudo-potential
- 更方便的表示电子和离子之间的相互作用 
	- 如果使用hard的势函数($\frac{-Z}{r}$), 那么将会使用很多很多个平面波
	- 赝势用来描述离子-电子相互作用

### 从电子排布理解赝势
- 价电子在物理过程中, 波函数变化很大
- 内层电子在物理过程中, 状态基本不变
- 如C, 我们可以忽略$1s^2$的电子, 只看$2s^2p^2$这四个电子
- 那就不如把内层电子和原子实看作一个整体

### 赝势的可以执行
- 赝势的提出是从反应是否参与角度提出的
- 那么不同程度的反应, 必然导致赝势的可用范围存在一定限制
- 通常赝势的构造针对单原子, 但是赝势的有效性与原子的环境相关
- 需要更好的构造可移植赝势的方法

### 模守恒赝势, 以及需要满足的性质
- most famous: SG15 ONCV Potentials
- 总之, 所有约束都是赝势下波函数(PW)和全电子下波函数(AE)的性质对照
1. 在截断半径$r_c$之外, 全电子波函数和赝势波函数相同
	- $\phi_l^{PS}(r) = \phi_l^{AE}(r) \quad \text{for} \ r > r_c$
2. 对于给定电子构型, 价电子能级相同
	- $\epsilon_l^{PS} = \epsilon_l^{AE}$
	- 如下图中, 将Al的10个内层电子砍掉, 赝势中计算出的外层电子, 仍然是处在和全电子情况下相同的能级中
	- 可以想象, 这个时候截断半径外的波函数, 在使用赝势前后也是相同的
![[DFT_procedure_fig1.png|500]]
3. 赝势函数在$r_c$之内平缓无节点
	- 用赝势算出来的电子波函数, 在截断半径内平缓没有节点
	- 下图中, 红色的是全电子波函数, 蓝色是赝势波函数
	- 可见两者在赝势区域外重合
> **COMMENT**
> 这是个从简化问题角度出发进行的限制吗?
> 赝势的什么性质, 最能够影响这个约束条件?
> 有可能出现不满足的情况吗?
![[DFT_procedure_fig2.png|500]]
4. 满足模守恒norm conserving要求
	- 容易理解, 这就是不改变赝势外电子分布的性质
	- 式子是示意, 总之就是赝势涉及的区域内电子波函数的概率不变
	$$
	\int_0^{r_c} |\phi^{AE}(r)|^2 r^2 dr
	= \int_0^{r_c} |\phi^{PS}(r)|^2 r^2 dr
	$$

### 对角动量依赖的赝势
- 主要考虑为, 电子构型是分布在不同角动量的轨道上的, 具有不同的角动量
- 计算量太大, 比较失败, 因为$\braket{\psi_{l} | V_{ll'} | \psi_{l'}}$对应的矩阵实在是太大了

### 可分赝势(仍然是模守恒赝势)
- 在以上四个约束的基础上, 增加一个projector(能够减少积分的计算量)
- 这样积分的种类少了轨道个数个量级
- 后面一项称为投影子
$$
\hat{V_{PS}} = V_{PS}^{loc} + \sum_{lm} D_l \ket{\beta_{lm}} \bra{\beta_{lm}}
$$



## XC functional
- How the functionals are developed
- and how ML are applied

### general
- XC functional determines the ultimate accuracy of KS-DFT.
- example for Fe:
	- Fe is stable in bcc compared to fcc, naturally
	- but LSDA tells us that fcc is more stable, which is incorrect
	- while GGA tells the right answer
	- the reason is that LSDA considers only $n$, while GGA considers $n$ and $\nabla n$

### Jacob's ladder
![[DFT_procedure_Jacobs_ladder.png|300]]



## SCF iteration method
- self-consistent field = SCF
- electron density 2 Hamiltonian 2 eigen problem 2 new wave function and new electron density
- so iterative, actually self-consistent field method (SCF)
- d 


**这里有几个图可以参考一下**

**明天继续!**


## references
- [陈默涵：密度泛函理论计算流程](https://www.bilibili.com/video/BV1GU4y1r7RA)


