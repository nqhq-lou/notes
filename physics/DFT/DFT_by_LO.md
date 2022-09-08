---
title: DFT with local orbit method
tags: [physics/DFT]
---

- 平面波的耗时非常大, 计算量随原子数量cubic增长
- 使用LO方法, 具体KS-DFT的思路和PW basis的差别比较大
- 主要问题: 如何让LO的计算精度逼近平面波

## 基于LO的软件介绍
- 略, 自己看视频
	- 有SIESTA, OpenMX, FHI-aims

![[DFT_by_LO_KSDFT_basis_categories.png|500]]
- Grid 空间格点法, Gaussian的好处是可以解析, 虽然需要的波的数量仍然很多很多
- grid方法, 在实空间网格内求解KSDFT, 但是精度不好, 比如受力的求解比不上PW法
- 原子轨道包括解析和数值两种, 数值原子轨道必须在实空间存在

### 局域轨道基组
- 特征
	- 局域轨道作为描述电子波函数的基矢量
	- 轨道中心在原子坐标上, 随原子移动
	- 对给定体系, 所使用局域轨道数量远小于平面波数量
- 和正交
	- 局域和正交没有必然联系
- 优势
	- 哈密顿矩阵会很小

### 局域轨道下的Hamiltonian
- 外势能是随原子位置改变的
- 赝势分为局域(L)和非局域(NL)的部分
	- 非局域赝势是一个投影子
- 电荷密度系数2是自旋$2s+1$
![[DFT_by_LO_LO_Hamiltonian_formalism.png|600]]

### 局域轨道基矢量下的表示
- Hamiltonian矩阵中
	- 赝势的局域部分和XC势可以合起来evaluate
	- 赝势的非局域部分是投影子的形式, 单独evaluate
- 双中心积分技术
	-  三维波函数转换成一维波函数进行积分, 这里能够大大加速
> **COMMENT**
> 这是什么? 双中心积分技术, 没有找到资料
![[DFT_by_LO_LO_Hamiltonian_matrix.png]]
- 之后求解广义本征值问题就行




## 数值原子轨道

### 数值原子轨道
$$
\phi_{I,l,m,n}(r) = R_{I,l,n}(r) Y_{l,m}(\hat{r})
$$
- index中, $I$为原子的index, $lm$角量子数和磁量子数, $n$是给定$l$之后选取几个径向波函数
- 径向波函数和球谐函数
	- 径向波函数并不一定是贝塞尔J, 可以自己构造合适的更有表现力的数值函数
	- 径向波函数选择合适的阶数, 并且进行严格截断
	- 可以对径向波函数的 大小, 长度, 形状 进行优化
- 术语
	- multi-zeta: 指代$n$的个数, 一个角动量有不同的径向轨道
		- 径向轨道变多, 分别为single-zeta(n=1), double-zeta(n=2), triple-zeta(n=3)
	- 极化轨道: 指代$l$的大小, 高角动量对应的原子轨道
		- 但是很少用到$l=3$的情况, 一般取到d轨道就足够了
- 如下图, sp都在说径向轨道, 一个径向轨道将会对应足够多的球谐函数
	- 增加轨道的数量, 能够非常逼近平面波的结果. 
![[DFT_by_LO_increase_radical_function.png|600]]
- 轨道具体的情况, 需要根据价电子的情况进行确定
> **COMMENT**
> 这个怎么确定? 我需要再看点相关内容.
![[DFT_by_LO_SZ_orbitals_example.png|500]]


### 数值原子轨道构造方法
- 既然是数值原子轨道, 那么我们不一定要用贝塞尔的径向函数 (但是仍然使用球谐函数)
- 完全可以自己构造最合适的轨道, 来构建足够适应度高的径向基矢
- 常见流程
	- 求解一维薛定谔方程, 方程中有约束势场
	- 势场可以有自己的选择, 不同的选择, 最后得到的波函数就会不一样
	- 获得求解的结果, 进行实际实验测试
	- 根据之后可能需要的精度需求, 将构造好的数值轨道分类为适用于不同精度类型的计算
- 其他因素
	- 还需要考虑所使用的赝势的情况

- 数据库
	- OpenMX作者做的数据库: [Database (2013) of optimized VPS and PAO](https://www.jaist.ac.jp/~t-ozaki/vps_pao2013/)
	- ABACUS数值原子轨道库: [Pseudopotentials and orbits](http://abacus.ustc.edu.cn/pseudo/list.htm)




## ABACUS中的数值原子轨道

### spillage方法
- 基础想法:
	- 平面波是最准确的拟合方法, 原因在于基组能够充分描述空间
	- 能不能让选取的LO张成的空间, 尽量接近平面波张成的空间?
- 定义一个非正交轨道组成的投影算符, 所用的非正交轨道就是后来要用于计算的轨道
- 如果我们选取的非正交轨道张成的Hilbert空间和平面波张成的空间越接近, 则S会越小 (但是一直大于0)
	- 计算中, 参考态的波函数 见下
- 在调整选取的LO的过程中, 调整LO basis set, 尽量减小S的数值
![[DFT_by_LO_ABACUS_spillage.png|600]]

#### 径向波函数的分解表示
- 然后NAO的径向部分, 将会被分解为一系列BesselJ叠加的形式, 
- 乘上$g(r)$因子, 让导数在截断处连续 (**??????what**)

![[DFT_by_LO_ABACUS_NAO.png|600]]

#### 根据参考系统计算数值轨道精度
- 实际计算是在不同原子组成的化学环境中进行的
- 因此在全部的数值轨道中, 选择合适的基组, 需要在模仿实际计算场景的reduced的情况下进行
- ABACUS中, 选择计算对象包含元素的dimer, 选取4-5个不同的原子间距, 作为参考系统
- 对参考系统进行DFT电子自洽计算, 获得平面波下的波函数. 使用Spillage方法选择NAO
![[DFT_by_LO_ABACUS_refine_NAO_1.png|600]]
 - 更高阶的NAO(multi-zeta), 为了提高函数的效率, 可以先取正交部分然后进行更高阶的pillage
![[DFT_by_LO_ABACUS_refine_NAO_2.png|500]]
- 轨道震荡, 需要最小化动能, 进行平滑轨道
![[DFT_by_LO_ABACUS_refine_NAO_3.png]]
- 如此详细优化之后, 较少的NAO就能对物理体系进行足够好的描述!



## references
- [陈默涵：局域轨道基矢量](https://www.bilibili.com/video/BV1N14y1s7UG)
- 