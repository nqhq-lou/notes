
---
title: basic group knowledge
tags: [math/group]
---

## group
- $G \times G \in G$
- identity&inverse, associative

## representations
- only discus finite dimensional representations
- $D: G \rightarrow \mathbb{R}^{d \times d}$, $D(e) = 1, D(ab) = D(a)D(b)$
- An irreducible representation is a representation that does not contain a smaller representation
	- example
		- $3 \times 3$ Cartesian symmetric matrix is of dof 6.
		- can be composed by $l=0$ and $l=2$.
- parity
	- `e`, even, $p=1$
		- like pseudo vectors
	- `o`, odd, $p=-1$
			- like velocity

## equivariance
- a function $f: X \rightarrow Y$ is equivariant under $G$
	- if $f(D_X(g) x) = D_Y(g) f(x)$
	- $\forall g \in G, x \in X$, $D_X(g)$ is the representation of the group element $g$ acting on the space $Y$, resp. $Y$.
- Here we require all individual network operations are equivariant for $G=E(3)$
- learnable parameters: $f: W \times X \rightarrow Y$, where $w \in W$ is a choice of learned parameters
	- require all the parameters to be scalars, meaning that they don't transform under a transformation of $E(3)$
	- that is: $f(w, D_X(g) x) = D_Y(g) f(w,x)$

$$
\begin{equation}
z_m^l=
\begin{cases}
(-i)^l \frac{1}{\sqrt{2}}\left(x_{|m|}^l-i x_{-|m|}^l\right) & m<0 \\
(-i)^l & m=0 \\
(-1)^m(-i)^l \frac{1}{\sqrt{2}}\left(x_{|m|}^l+i x_{-|m|}^l\right) & m>0
\end{cases}
\end{equation}
$$

## spherical harmonics
- Rotation of $Y$
	- $R$ is rotation matrix, $D^l$ is the irreducible representation
$$
Y_l^m (R \vec{x})
= \sum_{m'=-l}^{l} D^l(R)_{mm'} Y_l^{m'} (\vec{x})
$$
- function based on $Y_l$
	- the coefficients vector $\vec{v}_l$ is of length is $2l+1$
	- $\vec{Y}_l: \mathbb{R}^3 \rightarrow \mathbb{R}^{2l+1}$
$$
f(\vec{x}) = \sum_{l=0}^{\infty} \vec{v}_l \cdot \vec{Y}_l (\vec{x})
$$
$$
\begin{aligned}
[Rf](\vec{x}) = \ & f(R^{-1} \vec{x}) \\
= \ & \sum_{l=0}^{\infty} \vec{v}_l \cdot \vec{Y}_l (R^{-1}\vec{x}) \\
= \ & \sum_{l=0}^{\infty} \vec{v}_l \cdot D^l(R^{-1}) \vec{Y}_l (\vec{x}) \\
= \ & \sum_{l=0}^{\infty} D^l(R) \vec{v}_l \cdot \vec{Y}_l (\vec{x})
\end{aligned}
$$
- The $f$ are evaluated by necklace grids on the sphere

## change of basis

- 以二阶张量为例
	- $A_{ij} \sim (l=1) \otimes (l=1)$, 对称矩阵, 自由度为6
	- 空间旋转$R$为: $D^1(R)_{nj} D^1(R)_{mi} A_{ij} = D^1_{nj} D^1_{mi} A_{ij}$
	- 如果写成张量形式, 则有$(D^1 \otimes D^1) A_{\{e_1,e_2\}}$
	- 存在相似变换 $S^{-1} (D^1 \otimes D^1) S = (D^0 \oplus D^2)$, 仍然是六个自由度
	- 实际上是对基组的操作, 进行了角动量的合并
	- 那么 $(D^1 \otimes D^1) A_{e_1,e_2} = (D^0 \oplus D^2) (V^0 \oplus V^2)$
- 推广情况
	- $(D^{l_1} \otimes D^{l_2}) A_{\{e_1,e_2\}} = D^{\oplus l_i} V^{\oplus l_i}$
```Python
chgbase = o3.ReducedTensorProducts('ij=ji', i='1')
print(f"{chgbase.change_of_basis.shape = }")  # torch.Size([6, 3, 3])
print(chgbase)  # ReducedTensorProducts( in: 1x1e times 1x1e out: 1x0e+1x2e )
irrep_W = torch.einsum("...kij,...ij", chgbase.change_of_basis, W)  # 正变换
W2 = torch.einsum("...kij,...k", chgbase.change_of_basis, irrep_W)  # 逆变换
print(f"{numpy.allclose(W, W2) = }")  # numpy.allclose(W, W2) = True
irrep_W.shape  # torch.Size([6])
```


## tensor product

- 线性空间基矢的重新组合

$$
\begin{aligned}
\text{(value of path)}_{wk} =
\dfrac{1}{\sqrt{m_1 m_2}}
\sum_{u=1}^{m_1} \sum_{v=1}^{m_2} \sum_{i=1}^{2l_1+1} \sum_{j=1}^{2l_2+1}
w_{uvw} C_{ijk} V_{ui}^{\text{in1}} V_{vj}^{\text{in2}}
\end{aligned}
$$