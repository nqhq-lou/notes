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
$$
\dfrac{\partial L}{\partial A} = X \bar{\Lambda} X^T - \bar{V} X^T
$$
bar for perturbations, $\Lambda X$ for eigval matrix and eigvec matrix



```Python
for d_d, w, v in zip(d_dcpt, eigvals, eigvecs):
    temp = []
    for j in range(w.shape[0]):  # iter the mag number
        for i in range(w.shape[0]):  # iter the mag number
            d_w = w[j] - w[i]
            if i == j: continue
            if numpy.abs(d_w) < d_safe: continue
            temp.append(d_w * numpy.outer(v[:,i], v[:,i]) @ numpy.outer(d_d[:,j], v[:,j]))
    d_proj_dm.append(numpy.stack(temp, axis=0).sum(axis=0))
return d_proj_dm
```

## reference
- M. F. Kasim and S. M. Vinko, “Learning the Exchange-Correlation Functional from Nature with Fully Differentiable Density Functional Theory,” _Physical Review Letters_ 127, no. 12 (September 15, 2021): 126403, [https://doi.org/10.1103/PhysRevLett.127.126403](https://doi.org/10.1103/PhysRevLett.127.126403).
	- Supplementary, sec E


