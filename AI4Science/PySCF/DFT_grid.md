---
title: DFT grid
tags: [AI4Science/PySCF]
---

## Lebedev

- 连续空间积分
$$E_{xc}[\rho] = \int f[\rho] \rho(r) dr$$
- 格点积分为
	- 其中$w$为对应权重
$$E_{xc} [\rho] = \sum_g w_g f_g[\rho] \rho_g$$

```Python
mol = Mol_H2O2().mol
grids = dft.Grids(mol)
grids.atom_grid = (4, 14)  # (径向格点数，球面格点数)
# N_total = 4 * 14 * 4 = 224
# grids.level = 0  # from 0 to 9, 3 by default
grids.build()
# 格点是按顺序的, 按原子编号的顺序产生
grids.weights  # shape = (N,)
grids.coords  # shape = (N, 3)



```







