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



## physics quantities

- acquisition of physics quantities manually

```Python
"""import modules"""
from pyxdh import GridHelper, KernelHelper


"""do the project"""
mol = gto.M(...)
grids = dft.Grids(mol)
# quad_grids.atom_grid = (99, 590)
grids.build()
# mf = scf.RHF(mol)
mf = dft.RKS(mol)
mf.xc = "B3LYPg"
mf.grids = grids  # determine grids
mf.kernel()  # run
```

- $S_{\mu\nu} = \braket{\mu|\nu} = \phi_\mu \phi_\nu$ 因为都是real所以就不标注conj了
```Python
"""basics quantityes"""

# MO coefficient
C = mf.mo_coeff  # comb ao for mo

# 1-elec self-overlap
S = mol.intor("int1e_ovlp")

# transfrom matrix
X = scipy.linalg.fractional_matrix_power(S, -0.5)  # X.T@S@X = diag(1)

# random generalized density matrix, for later use
R = np.random.random((nao, nao));
R = R + R.T

# 2-elec
eri = mol.intor("int2e")  # no "_ovlp"

# nucleus repulsion energy
E_nuc = mol.energy_nuc()
E_nuc = mf.energy_nuc()
Z_A = mol.atom_charges()
Z_AB = Z_A[:,None] * Z_A
r_A = mol.atom_coords()
r_AB = np.linalg.norm(r_A[:, None, :] - r_A[None, :, :], axis=-1)
E_nuc = 0.5 * (Z_AB / r_AB).sum()
```

- $T_{\mu\nu} = \braket{\mu | -\dfrac{1}{2} \partial_r^2 | \nu} = - \dfrac{1}{2} \phi_\mu \phi_{rr\nu}$, 两个$r$代表同一方向上求导, $\nu$为下标
- $J_{\mu \nu}[R_{\kappa \lambda}] = (\mu \nu | \kappa \lambda) R_{\kappa \lambda}$
- $K_{\mu \nu}[R_{\kappa \lambda}] = (\mu \kappa | \nu \lambda) R_{\kappa \lambda}$

```Python
grdh = GridHelper(mol, quad_grids, mf.make_rdm1())  # provide ao spatial values
kerh = KernelHelper(grdh, "B3LYPg", deriv=3)  # provide functional kernel

"""advanced quantities"""
# 1-elec density matrix
dm1 = mf.make_rdm1()  # electron density matrix, D in general texts
ao_occ = slice(mol.nelec[0])
dm1 = 2 * C[:,ao_occ] @ C[:,ao_occ].T

# kinetic T
T = mol.intor("int1e_kin")
T = - 0.5 * np.einsum("g, gu, gvr -> uv", grdh.weight, grdh.ao_0, grdh.ao_2.diagonal(axis1=0, axis2=1))  # grids.weight == grdh.weight, ao_x is from dft.numint.eval_ao(mol, coords,deriv=3)

# H^{core} = T_{ee} + V_{nuc,e}
Hcore = mf.get_hcore()
Hcore = mol.intor("int1e_kin") + mol.intor("int1e_nuc")

# Coulomb integral, used in many cases
J = mf.get_j(dm=R)  # here R is generalized dm, which dm1 is included
J = np.einsum("uvkl, kl -> uv", mol.intor("int2e"), R)  # R is generalized dm

# Exchange integral, used in many cases
K = mf.get_k(dm=R, hermi=...)  # check docs for hermi option
K = np.einsum("ukvl, kl -> uv", mol.intor("int2e"), R)  # R is generalized dm
```

- RHF中的Fock矩阵为
	- $F_{\mu \nu}^\mathrm{HF} [R_{\kappa \lambda}] = h_{\mu \nu} + J_{\mu \nu}[R_{\kappa \lambda}] - \frac{1}{2} K_{\mu \nu}[R_{\kappa \lambda}]$
- GGA中交换积分有一系数$c_x$, `cx = ni.hybrid_coeff("B3LYPg") == 0.2`
	- $F_{\mu \nu} = h_{\mu \nu} + J_{\mu \nu}[R_{\kappa \lambda}] - \frac{1}{2} c_\mathrm{x} K_{\mu \nu}[R_{\kappa \lambda}] + v_{\mu \nu}^\mathrm{xc} [R_{\kappa \lambda}]$
- $v_{\mu \nu}^\mathrm{xc} [R_{\kappa \lambda}]$: `ni.nr_rks()`
```Python
# Fock matrix (AO)
F = mf.get_fock(dm=R)  # related to mf.xc
F = mf.get_hcore() + mf.get_j() - 0.5 * mf.get_k()  # for RHF
F = scfh.H_0_ao + scf_eng.get_j(dm=R) - 0.5 * cx * scf_eng.get_k(dm=R) + ni.nr_rks(mol, grids, "B3LYPg", R)[2]  # for B3LYPg functional
```

- RHF中电子态能量为
	- $E_\mathrm{elec}^\mathrm{HF} [R_{\mu \nu}] = (h_{\mu \nu} + \frac{1}{2} J_{\mu \nu} [R_{\kappa \lambda}] - \frac{1}{4} K_{\mu \nu} [R_{\kappa \lambda}]) R_{\mu \nu}$
- GGA中电子态能量为
	- $E_\mathrm{elec} [R_{\mu \nu}] = (h_{\mu \nu} + \frac{1}{2} J_{\mu \nu} [R_{\kappa \lambda}] - \frac{1}{4} c_\mathrm{x} K_{\mu \nu} [R_{\kappa \lambda}]) R_{\mu \nu} + f^R \rho^R$
	- upper $R$ for integral by $R$ quad grid, $f$ is functional core 泛函核
	- $f^R$就是我们预测的东西吧!
- about $f^R$: `ni.eval_xc`
	- $\rho^R = R_{\mu\nu} \phi_\mu \phi_\nu$, $\partial_r \rho^R = 2 R_{\mu\nu} (\partial_r \phi_\mu) \phi_\nu$
	- $f^R = f^R (\rho^R, \partial_r \rho^R)$

```Python
# electronic energy (after SCF)
# for HF
Eelec0, Eelec1 = mf.energy_elec(dm=R)  # actually return (total energy, HF energy)
Eelec0_V = mf.get_hcore() + 0.5 * mf.get_j() - 0.25 * mf.get_k()
Eelec0 = (Eelec0_V * dm1).sum()
Eelec1_V = 0.5 * mf.get_j() - 0.25 * mf.get_k()
Eelec1 = (Eelec0_V * dm1).sum()
# for GGA
Eelec0 = mf.energy_elec(dm=R)  # total energy, GGA energy
rho_0_R = np.einsum("uv, gu, gv -> g", R, grdh.ao_0, grdh.ao_0)  # 零阶, shape (ngrids, )
rho_1_R = 2 * np.einsum("uv, rgu, gv -> rg", R, grdh.ao_1, grdh.ao_0)  # 一阶, shape (3, ngrids)
rho_01_R = np.vstack([rho_0_R, rho_1_R])  # shape (4, ngrids)
exc_R = ni.eval_xc("B3LYPg", rho_01_R, deriv=0)[0]  # volumetric xc
# exc_R *= grids.weights  # 写在下面比较清楚
Eelec0 = (
    + ((H + 0.5 * J_R - 0.25 * ni.hybrid_coeff("B3LYPg") * K_R) * R).sum()  # 在ao空间做
    + (grids.weights * exc_R * rho_0_R).sum()  # 在实空间做
)
```

$$v_{\mu \nu}^\mathrm{xc} [\rho] = \langle \mu | \frac{\delta E_\mathrm{xc} [\rho]}{\delta \rho} | \nu \rangle$$
$$
\text{(ni.eval\_xc())} \quad
E_{xc}[\rho]
= f^R \rho^R
\neq v_{\mu\nu}^{xc}[\rho] D_{\mu\nu}
= \langle \mu | \frac{\delta E_\mathrm{xc} [\rho]}{\delta \rho} | \nu \rangle D_{\mu\nu}
= \int \frac{\delta E_{xc}[\rho]}{\delta \rho(\boldsymbol{r})} \rho(\boldsymbol{r}) \, \mathrm{d} \boldsymbol{r}
\quad \text{(ni.nr\_rks())}
$$
- `ni.eval_xc()`
	- `[0]`: $f^R$ is volumetric for energy eval, `exc` so-called
	- `[1,2,3]`: i-order functional derivatives
		- for 1 (`vxc`) is (`vrho, vgamma, vlapl, vtau`), the first-order functional derivatives evaluated at each grid point, each shape (N) (`=ngrids`).
- `ni.nr_rks()`
	- `[0]`: `nelec`, number of electrons
	- `[1]`: is $E_{xc}[\rho]$
	- `[2]`: $v_{\mu\nu}^{xc}[\rho]$ is orbital (AO) for Fock matrix (used messages from the `ni.eval_xc()`)

```Python
# 这两个相等, 是上侧等式右边的内容
numpy.einsum("uv,uv->", mf.make_rdm1(), ni.nr_rks(mol, grids, mf.xc, mf.make_rdm1())[1])
quad_rho_grid = numint.eval_rho(mol, mol.eval_gto('GTOval', grids.coords), mf.make_rdm1())
numpy.sum(quad_rho_grid	* grids.weights * ni.eval_xc(mf.xc, quad_rho_grid, deriv=1)[1])
```

```Python
# 从ni.eval_xc()的vrho 能够得到ni.nr_rks()[2]
quad_ao_value = mol.eval_gto('GTOval', grids.coords)  # ni.eval_ao recommended
quad_rho_grid = numint.eval_rho(mol, quad_ao_value, mf.make_rdm1())
quad_vrho_grid = ni.eval_xc("LDA", quad_rho_grid, deriv=1)[1][0]  # get vrho
quad_vrho_dm_recon = numpy.einsum("pi, p, pj -> ij", quad_ao_value, grids.weights*quad_vrho_grid, quad_ao_value)
numpy.allclose(quad_vrho_dm_recon, xc_v_dm)
```


```Python
# system total energy
Etol = mf.energy_tol(dm=R)
Etol = mf.energy_elec(dm=R)[0] + mf.energy_nuc()

# MO energy
Emo = mf.mo_energy
Emo = np.diag(C.T @ mf.get_fock() @ C)

# MO occupation
mo_occ = mf.mo_occ


"""match band energy with total energy"""
scf_eng.mo_energy[ao_occ].sum()*2  # close shell energy sum
>>> -94.5189564217388
Eelec0, Ecore = scf_eng.energy_elec()[0], np.einsum("uv, vu ->", mf.get_hcore(), dm1)
(Eelec0 - Ecore) * 2 + Ecore
>>> -94.51895616984223


"""nuclear replusion energy integral"""
# mol.with_rinv_as_nucleus(nuc_idx)
# 它通过传入原子序号，将积分时的原点坐标更变为当前原子的坐标
# 但除了特定积分以外，分子的所有性质，包括坐标，都保持不变。
v = np.zeros((nao, nao))
for M in range(natm):
    with mol.with_rinv_as_nucleus(M):
        v += - mol.atom_charge(M) * mol.intor("int1e_rinv")
np.allclose(v, mol.intor("int1e_nuc"))
```










