---
title: DFT ABACUS ML
tags: [physics/DFT/ML, ML/DFT]
---

- 本节讨论内容均为LO表示下的DFT
- relevant notes:
	- [[DeePKS_basics]]

## 双中心积分和格点积分

### 涉及到的双中心积分
- LO表示下的电子动能矩阵
	$$
	T(R) = \bra{\psi_\mu^*(r)} -\dfrac{1}{2} \nabla^2 \ket{\phi_\nu (r-R)}
	$$
- LO表示下的局域势矩阵
	$$
	V_{\mu,\nu}^\mathrm{loc} = \bra{\phi_\mu (r-R_\mu)} V^\mathrm{loc} (r) \ket{\phi_\nu(r-R_\nu)}
	$$
- 以上两个积分可以在实空间或者倒空间做
- 应当注意到, 波函数都分为径向的数值轨道NAO部分和球谐函数部分

### 双中心积分可拆分

#### overlap matrix
- 是一个广义展开问题
	- 其中, 一维轨道从实空间到倒空间可以变换, 见公式
$$
\begin{aligned}
S_{l_\mu m_\mu, l_\nu m_\nu, l m} (R) = &
4 \pi i^{-l} \int_0^{\infty} j_l(kR) f_\mu(k) f_\nu(k) k^2 d k \\
f_\mu (k) = & \sqrt{\dfrac{2}{\pi}} (-i)^{l_\mu} \int_0^\infty
r^2 j_{l_\nu}(kr) f_\mu(r) d r
\end{aligned}
$$
- 径向部分可以做成表格
	- 根据截断半径, 探测体系内可能出现的最大的有overlap的原子间距
	- 在这个间距范围内dense points, 算出来任意两个径向数值原子轨道的交叠
- 角向部分是Gaunt系数, 三个球谐函数的乘积
$$
S_{l_\mu m_\mu, l_\nu m_\nu, l m} (R) = \int_0^\pi d\theta \sin\theta
\int_0^{2\pi} d \phi Y_{l_\mu m_\mu} (\theta, \phi) Y_{l_\nu m_\nu} (\theta, \phi) Y_{lm} (\theta, \phi)
$$
> **COMMENT**
> 这里的下标, 没有理清楚情况.

#### 动能矩阵
$$
\begin{aligned}
T(R) = & \int \psi_\mu^*(r) \left( -\dfrac{1}{2} \nabla^2 \right) \phi_\nu (r-R) d^3 r


\end{aligned}
$$
- 动能矩阵在倒空间做很容易, 因为是涉及到 Laplacian
	- Laplacian 带来一个$k^2$, 还剩一个$k^2 \sin\theta$是球积分带来的(三维积分编程一维积分)
- 径向部分在倒空间做, $k$的四次方项如上所述
	- 之后也是根据插值方法, 计算未计算的量
$$
T_{l_\mu m_\mu, l_\nu m_\nu, l m} (R) = 2 \pi i^{-l}
\int_0^{\infty} j_l(kR) f_\mu(k) f_\nu(k) k^4 d k
$$
> **COMMENT**
> $\sin$呢?
> 以上内容都是很节省时间的


### 格点积分
- 势能需要三维空间格点进行格点积分了, 因为包含三项形式不一样的势能, 格式不统一
	- 局域势包括三部分, 赝势的局域部分, Hatree势, 交换关联势
	- 局域势在倒空间做, 然后用快速傅里叶变换变换回实空间中
![[DFT_ABACUS_ML_latticeint1.png|600]]


#### 格点积分举例
- 局域轨道有一定半径限制, 因此我们需要在计算前, 寻找有交叠/需要积分的pair
![[DFT_ABACUS_ML_latticeint_eg1.png|600]]
![[DFT_ABACUS_ML_latticeint_eg2.png|600]]
- 没有细讲这里的流程

#### 格点积分的副作用 Eggbox effect
- 如果格点在空间内进行平移, 则求得的物理量将会有随格点位置而周期性变化的小震荡
- 解决方法: 增加网格密度

#### Gamma点和多k点算法
- 这个也没有仔细讲欸
![[DFT_ABACUS_ML_gamma.png|600]]

#### 局域轨道求力
- 也没仔细讲, 自己看吧
![[DFT_ABACUS_ML_force.png|600]]



## ABACUS程序介绍

- 需要让DFT软件有ML的功能
- 旧的DFT代码框架(如Fortran)已难以适应AI发展和新计算平台(如GPU)
- 需要做AI for DFT

![[DFT_ABACUS_ML_roadmap.png]]

ABACUS关注的事情
- 希望把程序基础层进行包封, 适合用于不同的硬件平台进行计算
- 加入其他非KSDFT的求解方法
	- 随机波函数密度泛函理论? 这个是什么
	- 看看其他几个DFT的理论吧
- 加入已经开发的Hamiltonian模型



## 基于机器学习的密度泛函

![[DFT_ABACUS_ML_XC1.png|600]]
![[DFT_ABACUS_ML_LDA_GGA_err.png|500]]

### DeePKS方法
- general idea: 采用深度神经网络模型表示高精度和低精度的方法之差
	- 如从GGA修正到Hybrid functional, 能量和力的修正分别是什么
- 同时因为网络需要预测能量和力的修正, 两者时间的关系是位移
	- 所以希望神经网络的输入项是和位移相关的项目, 这样方便进行计算

![[DFT_ABACUS_ML_DeePKS1.png|600]]

#### 变量定义
- $\ket{a_{nlm}^{I}} \& \ket{a_{nlm'}^{I}}$ 是localized的数值原子轨道
	- 之所以叫做参考态, 是因为是神经网络进行训练时, 作为的单电子轨道们在某个原子周围的basis
	- 用于将单电子波函数, 拆解成单个原子的贡献
	- 同时具有一定的泛化性, 
- $\ket{\chi_\mu}$是进行KSDFT求解时选用的数值原子轨道
	- 陈默涵说, DeePKS中这里用的是Bessel
- $\ket{\psi_i}$ 一次次SCF迭代得到的单电子波函数
	- 第一次是用baseline的functional里算出来
	- $\ket{\psi_i} = \sum_\mu c_{i\mu} \ket{\chi_\mu}$
- $\rho$ 是单电子密度矩阵
	- $$\rho = \sum_i^N \ket{\psi_i}\bra{\psi_i} = \sum_{\mu\nu} \rho_{\mu\nu} \ket{\chi_\nu} \bra{\chi_\mu}$$
	- 描述了全空间的电子概率密度信息, 但是并不是直接的电子密度!

#### 操作过程
- 准备工作
	- 根据高精度的target functional, 计算体系的$E$和$F$, 之后的NN model中将会用到
	- 选取一组数值原子轨道$\alpha_{nlm}^I$, localize在各个原子$I$周围, 作为投影用
- 第一次操作
	- 使用baseline的functional, 计算得到单电子波函数们$\ket{\psi_i}$, $E_{baseline}$和$F_{baseline}$, 进一步计算得到密度矩阵$\rho = \sum_i^N \ket{\psi_i}\bra{\psi_i}$ (这里的密度矩阵我感觉还是不了解)
- 迭代过程
	- 计算投影密度矩阵, ***局域化***
		- 使用密度矩阵$\rho$和单电子波函数$\ket{\alpha_{nlm}^I}$ 和 投影用数值原子轨道$\ket{\psi_i}$
		- 得到描述原子化学环境的矩阵$D_{nlmm'}^I = \sum_i^N \braket{\alpha_{nlm}^I | \psi_i}\braket{\psi_i | \alpha_{nlm'}^I}$
		- so called  projected density matrix
	- 计算描述符, ***关于对称性***
		- 计算$(D_{nl}^I)_{mm'}$的本征值$d_{nl}^I$作为描述符, 相同的$I$拼成一个描述符$d^I$
		- 此时, 可以选择是否进行对称化操作得到$d_{nl}^{I,symm}$
	- 训练神经网络 $F_{NN}(\omega)$
		- 输入为一个个的描述符$d_{nl}^I$, 输出为$E$的修正值$E_\delta$, 网络参数为$\omega$
			- 实际上描述符是一个一个输入网络的, 一次输入一个原子周围电子的描述符
			- 能量的修正量也是一个一个网络输出直接加起来的 $E_\delta = \sum_I E_\delta^I = \sum_I F_{NN}(d^I|\omega)$
			- 这里体现了***可扩展性***
		- 损失函数由$E$部分和$F$部分组成, 优化目标是越接近高精度target越好
		- 对于一组完整的NN参数$\omega$, 能够计算出能量修正量$E_\delta$, 以及力的修正量$F_\delta = \dfrac{\partial E_\delta}{\partial X}$, 用于上述内容的计算
		- 优化之后得到优化过后的神经网络参数$\omega$, 该参数是基于目前的单电子波函数(和$\ket{\alpha_{nlm}^I}$相关)的
	- 计算势能修正项目$\hat{V}^\delta$
		- 根据神经网络参数, 计算势能的修正项$\hat{V}^\delta$, 获得新的KSDFT中的修正Hamiltonian
		- 势函数修正项计算, 主要的技术手段是双中心积分
		- 这里就引出了一个自洽迭代的问题 (下面这个式子的表述不对)
			- $$\dfrac{\delta \braket{\psi_i | \hat{H}_{baseline} + \hat{V}^\delta | \psi_i}}{\delta \bra{\psi_i}} = (E_{baseline} + E_\delta^I) \ket{\psi_i}$$
	- 根据新的Hamiltonian计算
		- 计算新的单电子波函数(和$\ket{\alpha_{nlm}^I}$相关)
		- 这时, 根据上一个单电子波函数神经网络参数并不对应新的单电子波函数, 所以需要重训神经网络
		- 神经网络仍然是输入描述符, 输出$E_\delta$和$F_\delta$
		- 两个修正量应该满足修正target和baseline泛函计算结果的差距
		- 进入SCF的迭代循环, 直到相邻几次误差足够小

- 下图是DeePKS-kit进行自动化迭代训练的示意图
![[DFT_ABACUS_ML_rec_train.png|600]]

> **COMMENT**
> 高精度target泛函的计算结果, 仅仅使用了计算结果中的能量和力, 用于NN model中的损失函数
> 低精度baseline泛函的计算结果, 用于作为$E$和$F$修正项的基础.
> 实验结论: 进行方法的测试, 发现对于水分子体系, 需要两百个杂化泛函的计算结果就可以收敛.
> 问题: 为什么描述符的矩阵是关于$mm'$的? 为什么将$nl$作为重复描述量?
> 暂时没有解释

- 不考虑周期性边界条件, DeePKS方法的势函数修正, 和对应的力
![[DFT_ABACUS_ML_V_F_non.png|600]]

- 考虑周期性边界条件, DeePKS方法的势函数修正, 和对应的力
	- 多了一个基矢, 这使得数据存储和矩阵并行稍微变得复杂了一些
![[DFT_ABACUS_ML_V_F_periodic.png|600]]

- 根据文章(Chen et al., 2021), 电子密度也加入了loss, 使用的是一个penalty, 实际上会引入一个penalty带来的势能, 让电子密度更快趋于收敛, 同时收敛效果更好.

Chen Y, Zhang L, Wang H, E W. DeePKS: A Comprehensive Data-Driven Approach toward Chemically Accurate Density Functional Theory. _J Chem Theory Comput_. 2021;17(1):170-181. doi:[10.1021/acs.jctc.0c00872](https://doi.org/10.1021/acs.jctc.0c00872)




### DeePKS中的关键点和难点
- 理解网络的输入: 为什么使用源于单电子波函数的描述子, 而不是电子密度, 作为神经网络输入
	- 电子密度往往被表示在实空间格点上
	- 对总能量的修正难以拆分为单个格点的动向
	- 在较小体系上训练后, 无法应用到更大体系
	- 不具有体系旋转, 平移的对称性
- 投影部分 & 双中心积分
![[DFT_ABACUS_ML_keypoints.png]]

> **COMMENT**
> 什么是Pulay force和Pulay stress?



### 回顾整体DeePKS的流程

![[DFT_ABACUS_ML_DeePKS_iteration.png|400]]















## reference
- [陈默涵：ABACUS和基于机器学习的密度泛函](https://www.bilibili.com/video/BV1se411g7KL)
- [DeePKS+ABACUS：AI辅助的电子结构方法](https://www.bilibili.com/video/BV1bt4y137Xj)
	- 24:25, pySCF无法处理周期性体系





