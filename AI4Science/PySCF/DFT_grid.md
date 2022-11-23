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



## dm & grid conversion

```Python
quad_ao_value = mol.eval_gto('GTOval', grids.coords)  # ni.eval_ao recommended, see `basis`
quad_ao_value_1 = ni.eval_ao(mol, grids.coords, deriv=0)
quad_ao_value_2 = ni.eval_ao(mol, grids.coords, deriv=1)  # with higher order diff
numpy.allclose(quad_ao_value_1, quad_ao_value)  # True
numpy.allclose(quad_ao_value_2[0], quad_ao_value)  # True

"""S: int1e_ovlp"""
S = mol.intor("int1e_ovlp")
S_int = numpy.einsum("pi, p, pj -> ij", quad_ao_value,  grids.weights, quad_ao_value)
numpy.allclose(S, S_int, atol=1e-4)  # True

"""rho: dm2grid"""
rho_dm2rho_grid = numpy.einsum("iu, uv, iv -> i", quad_ao_value, rho_dm, quad_ao_value)
quad_rho_grid = numint.eval_rho(mol, quad_ao_value, rho_dm)
numpy.allclose(rho_dm2rho_grid, quad_rho_grid)  # True

"""xc_v: grid2dm"""
"""similar op, see to: pyscf.dft.numint.nr_rks(), L1160, wv is weighted vrho"""
quad_vrho_grid = ni.eval_xc(mf.xc, quad_rho_grid, deriv=1)[1][0]  # note the deriv here
quad_vrho_grid2dm = numpy.einsum("iu, i, iv -> uv", quad_ao_value, grids.weights*quad_vrho_grid, quad_ao_value)
xc_v_dm = ni.nr_rks(mol, grids, mf.xc, rho_dm)[2]
numpy.allclose(quad_vrho_grid2dm, xc_v_dm)  # True

"""other operations are not allowed"""
```














