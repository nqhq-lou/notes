---
title: Gradient from eigvals to matrix
tags: [physics/math]
---


$$
A v_i = \lambda_i v_i
$$

$$
\frac{\partial L}{\partial A}
= - \sum_j \sum_{i \neq j, (\lambda_i \neq \lambda_j)}
(\lambda_i - \lambda_j)^{-1} v_i v_i^T
\frac{\partial L}{\partial v_j} v_j^T
$$





## reference
- M. F. Kasim and S. M. Vinko, “Learning the Exchange-Correlation Functional from Nature with Fully Differentiable Density Functional Theory,” _Physical Review Letters_ 127, no. 12 (September 15, 2021): 126403, [https://doi.org/10.1103/PhysRevLett.127.126403](https://doi.org/10.1103/PhysRevLett.127.126403).
	- Supplementary, sec E


