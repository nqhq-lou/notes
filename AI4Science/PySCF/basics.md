---
title: basic examples in PySCF
tags: [AI4Science/PySCF]
---


## entity classes

```Python
"""init a molecule"""
# given values are of default
from pyscf import gto
mol = gto.Mole()  # class init
mol.basis:str = ...  # str indicate conventional basis
mol.verbose:int = 3  # smaller for less output

mol.cart:bool = False  # if use Cartesian basis, False to use spherical harmonics
mol.spin:int = 0  # set total spin
mol.charge:int = 0  # charge to the molecule
mol.build()  # setup the molecule
```

```Python
"""configuration to the molecule"""
mol.natm  # int, number of atoms
mol.nelec  # return (alpha, beta)
# in restricted case
so = slice(0, mol.nelec[0])  # slice object for occupied orbitals
sv = slice(mol.nelec[0], mol.nao)  # slice object for virtual orbitals

mol.atom_coords()  # shape (N,3), in Bohr
# length convert use 1 Bohr = lib.param.BOHR Ang
mol.atom_charges()  # nuc charge for each atom, shape (N)
mol.energy_nuc()  # nuclear energy, Z_A Z_B / 2 r_AB
```


## CGTO

- Contracted Gaussian-Type Orbital
	- s orbitals
$$
\phi_\mu^{CGTO}(r-A) = d_{p\mu} \phi_p^{GTO}(\alpha_{p\mu}, r-A)
$$
$$
\phi_p^{GTO}(\alpha_{p\mu}, r-A)
=
\left( \dfrac{2\alpha_{p\mu}}{\pi} \right)^{3/4} \tilde{g}_s (\alpha_{p\mu},r-A)
=
\left( \dfrac{2\alpha_{p\mu}}{\pi} \right)^{3/4}
\exp (-\alpha_{p\mu} ||r-A||_2^2)
$$

- integral
	- 感觉这里的A-B范数的指数不太对?
$$
\int \tilde{g}_s (\alpha, r-A) \tilde{g}_s (\beta, r-A)
= \left( \dfrac{\pi}{\alpha+\beta} \right)^{3/2}
\exp \left( - \dfrac{\alpha\beta}{\alpha + \beta} ||A-B||_2^2 \right)
$$

```Python
mol._basis
>>>
{'O': [[0, [5484.6717, 0.0018311], [825.23495, 0.0139501], [188.04696, 0.0684451],
	       [52.9645, 0.2327143], [16.89757, 0.470193], [5.7996353, 0.3585209]],  # 1
       [0, [15.539616, -0.1107775], [3.5999336, -0.1480263], [1.0137618, 1.130767]],  # 1
       [0, [0.2700058, 1.0]],  # 1
       [1, [15.539616, 0.0708743], [3.5999336, 0.3397528], [1.0137618, 0.7271586]],  # 3
       [1, [0.2700058, 1.0]]],  # 3
 'H': [[0, [18.731137, 0.0334946], [2.8253937, 0.23472695], [0.6401217, 0.81375733]],  # 1
	   [0, [0.1612778, 1.0]]]}  # 1
# 1+1+1+3+3+1+1=11, *2=22 total atomic orbitals
# 这里实际上是atomic shells, 需要考虑如p的xyz才是atomic orbitals
# 每一个[d, a]都是GTO的参数, 相当于给出了GTO2AO的参数
```
- Here 0 for s-orbitals and 1 for p-orbitals
	- $[d_{p\mu}, \alpha_{p\mu}]$ listed respectively, each refers to a **primitive** gauss function
	- Here O has 2 p-orbitals, and $p_x, p_y, p_z$ takes the same parameter (but still in different direction)
- For O atom
	- 1s orbital is single-zeta
		- consists of 6 primitives
	- 2s and 2p is double-zeta
		- 2s consists of (3, 1) primitives
- zeta is from the param to slater determinant $\zeta$

```Python
mol._bas
>>> 
array([[ 0, 0, 6, 1, 0, 36, 42, 0],
	   [ 0, 0, 3, 1, 0, 48, 51, 0],
	   [ 0, 0, 1, 1, 0, 54, 55, 0],
	   [ 0, 1, 3, 1, 0, 56, 59, 0],
	   [ 0, 1, 1, 1, 0, 62, 63, 0],
	   [ 1, 0, 6, 1, 0, 36, 42, 0],
	   [ 1, 0, 3, 1, 0, 48, 51, 0],
	   [ 1, 0, 1, 1, 0, 54, 55, 0],
	   [ 1, 1, 3, 1, 0, 56, 59, 0],
	   [ 1, 1, 1, 1, 0, 62, 63, 0],
	   [ 2, 0, 3, 1, 0, 64, 67, 0],
	   [ 2, 0, 1, 1, 0, 70, 71, 0],
	   [ 3, 0, 3, 1, 0, 64, 67, 0],
	   [ 3, 0, 1, 1, 0, 70, 71, 0]], dtype=int32)
```
- `[atom index, angular momentum l, primitives, ?, ?, ?, ?, ?]`

```Python
mol.npgto_nr()  # primitive functions count, for atomic orbital, not atomic shell
mol.nao  # atomic orbitals count

scf = 
...  # do scf
scf_eng.mo_coeff  # the C_uv (AO2MO), \psi_v = \sum_u C_uv \phi_u
```


## shell and orbital subdivide

```Python
mol.aoslice_by_atom()  # shape (N,4)
>>>
array([[ 0, 5, 0, 9],  # O1
	   [ 5, 10, 9, 18],  # O2
	   [10, 12, 18, 20],  # H1
	   [12, 14, 20, 22]])  # H2
# [ash_s, ash_e, ao_s, ao_e] with python slice rule


mol_slice = lambda atm, mol: slice(*mol.aoslice_by_atom()[atm,2:])

def mol_slice(atm, mol):
    _, _, p0, p1 = mol.aoslice_by_atom()[atm]
    return slice(p0, p1)
# 可以用于切片
```

- `[0, 5, 0, 9]`
	- 氧原子3个s, 2个p
	- $3+2=5$ 称为 atomic shells
	- $3*1+2*3=9$ 称为 atomic orbitals







