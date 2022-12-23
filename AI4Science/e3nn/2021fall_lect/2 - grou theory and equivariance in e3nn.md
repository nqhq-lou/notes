---
title: Group theory and equivariant interactions in e3nn
tags: [e3nn/lect]
---

[tutor2 video](https://www.youtube.com/watch?v=9rS8gtey_Ic)
[tutor2 resources](http://e3nn.org/e3nn-tutorial-mrs-fall-2021/#tut2)

## polynomials

- Representation: group properties, linear, group structure
- properties
	- $g \in G, x \in V$
	- $D(g, x+y) = D(g,x) + D(g,y)$
	- $D(gh, x) = D(g, D(h, x))$
- notation: $D(g)x$ for simplicity
	- $D(g): V \rightarrow V \quad D(g) \in \mathbb{R}^{d \times d} \quad D(gh) = D(g) D(h)$

- Equivariance: $f(D(g)x) = D(g)f(x)$

- reducible representations: example of two-vector direct product
$$
M = v_1 \otimes v_2
= \begin{bmatrix}
x_1 x_2 & x_1 y_2 & x_1 z_2 \\
y_1 x_2 & y_1 y_2 & y_1 z_2 \\
z_1 x_2 & z_1 y_2 & z_1 z_2 \\
\end{bmatrix}
$$
- decompose
	- trace $Tr(M) = v_1 \cdot v_2$
	- cross product $v_1 \times v_2 = [y_1 z_2 - z_1 y_2, z_1 x_2 - x_1 z_2, x_1 y_2 - y_1 x_2]$
	- symmetric traceless $\begin{bmatrix}x_1z_2+z_1x_2 \\ x_1y_2+y_1x_2 \\ 2y_1y_2-x_1x_2-z_1z_2 \\ y_1z_2+z_1y_2 \\ z_1z_2-x_1x_2 \end{bmatrix}$
	- so $3\otimes3 = 1\oplus3\oplus5$, actually these are dimensions to representations
	- and further more for representations, $l^1 \otimes l^1 = l^0 \oplus l^1 \oplus l^2$, all in odd parity
- generally, $L_1 \otimes L_2 = |L_1 - L_2| \oplus \cdots \oplus (L_1 + L_2)$


- equivariant polynomials
	- Composition ($\circ$)
		- $f(h(x)) = f \circ h (x)$
	- Addition ($+$)
		- simply $f(x) + h(x)$
	- Multiplication ($\otimes$)
		-  $\vec{v}_{l_1} \otimes \vec{v}_{l_2}$ transforms by $D_{l_1}(g) \otimes D_{l_2}(g)$




## examples & code





## nonlinearities

$$
\phi(P(x))Q(x)
$$
- $P$ is invariant poly, thus scalars
- $\phi$ is a nonlinear function, where sigmoid works well
- $Q$ is equivariant poly




