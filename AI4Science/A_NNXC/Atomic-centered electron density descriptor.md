---
title: AC elec desc
tags: [physics/NNXC]
---


## basics

- follow the conventions in PySCF
	- GTO/AO $\phi$, MO $\psi$
$$
\ket{\psi_i} = \sum_a c_{ai} \ket{\phi_a}
$$

- Density matrix with GTO basis
$$
\rho = \sum_{occ,i} \ket{\psi_i}\bra{\psi_i}
= \sum_{occ,i} c_{ai} (c_{bi})^* \ket{\phi_a} \bra{\phi_b}
$$
- actually density matrix is $\sum_{occ,i} c_{ai} (c_{bi})^*$


## descriptor

- atomic-centered projector
	- **HACK**: check how deepks get the Ylm?
$$
\braket{\vec{r} | \alpha_{nlm}} = R_n(r) Y_{l}^m(\theta, \phi)
$$

- atomic-centered descriptor
	- for atom with index $I$
$$
D_{nl,mm'}^{I} = \sum_{occ,i;a,b} c_{ai} (c_{bi})^*
\braket{\phi_b | \alpha_{nlm'}^I} \braket{\alpha_{nlm}^I | \phi_a}
$$

- or better explanation: atomic-centered wave function projection
	- atomic index $I$, MO index $i$
$$
c_{nlm}^{I,i} = \braket{\alpha_{nlm}^{I} | \psi_i}
= \sum_{a} c_{ai} \braket{\alpha_{nlm}^{I} | \phi_a}
$$
- then from wave function projection to descriptor
$$
D_{nl,mm'}^{I} = \sum_{occ,i} c_{nlm}^{I,i} c_{nlm'}^{I,i *}
$$
- notice that $D_{nl}^I$ is Hermit, degree of freedom is only half as the elements number. E.g. dim=3, dof=6.

#### projector format
- [deepks discussion](https://github.com/deepmodeling/deepks-kit/discussions/52)
- [pyscf/basis_format](https://pyscf.org/user/gto.html#basis-format)
- 


#### equivariant descriptor
- 在得到$D$之后可以直接用等变进行, 具体参考gengyuan的代码
	- [pcmd/predictor/base_data.py/`Ylm_change_basis`](https://gitlab.pjlab.org.cn/hugengyuan/pcmd/-/blob/main/pcmd/predictor/base_data.py#L206)
		- change to wiki, then to e3nn
		- [wiki is yzx](https://en.wikipedia.org/wiki/Table_of_spherical_harmonics#Real_spherical_harmonics)
	- [pcmd/predictor/hamiltonian/mace_data.py/`Tp_irrep_convert`](https://gitlab.pjlab.org.cn/hugengyuan/pcmd/-/blob/main/pcmd/predictor/hamiltonian/mace_data.py#L26)
		- see to `o3.ReducedTensorProducts`
	- [pcmd/predictor/base_data.py/`Ylm_change_basis_abacus`](https://gitlab.pjlab.org.cn/hugengyuan/pcmd/-/blob/main/pcmd/predictor/base_data.py#L468)
	- [pyscf.symm.Dmatrix](https://pyscf.org/pyscf_api_docs/pyscf.symm.html#pyscf.symm.Dmatrix.Dmatrix)
		- 产生一个, 和e3nn对照一下即可
- 在最后输出的时候使用类似`'64x0e'`, 得到标量的结果
	- 常见32和64, 能够取得对结果的较好预测

| $l$ of D \\ $l$ | 0e  | 1o  | 2e  | 3o  | 4e  |
| --------------- | --- | --- | --- | --- | --- |
| 0e              | 1   |     |     |     |     |
| 1o              | 1   |     | 1   |     |     |
| 2e              | 1   |     | 1   |     | 1   |


#### invariant descriptor
- eigvals are invariant
- for ranking, use sort or thermal embedding
$$
d_{nl}^I = \mathrm{EigVal}_{mm'}(D_{nl,mm'}^{I}) \quad \text{(sort descending)}
$$



## BP gradient

- mock loss, $r$ is quad grid points
$$E_{XC} = \sum_{r} w^g (r) f^g (r) \rho(r)$$
- from `exc` to `xc_v`
$$
\begin{aligned}
\hat{V}_{\mu\nu}^{XC} = \ & \dfrac{\partial E_{XC}}{\partial \rho_{\mu\nu}} \\
= \ & \sum_{I,nl,mm'} \dfrac{\partial E_{XC}}{\partial D_{nl,mm'}^I} \dfrac{\partial D_{nl,mm'}^I}{\partial \rho_{\mu\nu}} \\
= \ & \sum_{I,nl,mm'} \dfrac{\partial E_{XC}}{\partial D_{nl,mm'}^I} \braket{\phi_\mu | \alpha_{nlm}^I} \braket{\alpha_{nlm'}^I | \phi_\nu}
\end{aligned}
$$
- from eigval to matrix [[Gradient from eigvals to matrix]]
$$D v_i = d_i v_i$$
$$
\frac{\partial L}{\partial D}
= - \sum_j \sum_{i \neq j, (d_i \neq d_j)}
(d_i - d_j)^{-1} v_i v_i^T
\frac{\partial L}{\partial v_j} v_j^T
$$
$$
\dfrac{\partial L}{\partial D} = X \bar{\Lambda} X^T - \bar{V} X^T
$$

- dd





## practice

- position of ghost atom `X`
- Choice of $n,l$, and how to apply them in PySCF


### wheel example
```Python
"""in DeePKS-kit"""
<deepks.utils._zeta & load_basis()>
pyscf.gto.basis.load()  # load gto basis from pyscf

<deepks.scf.scf>
<NetMixin>  self._pbas  # 虚构了一个用来产生投影的mol
<NetMixin.prepare_integrals>  self._t_ovlp_shells
# < mol_ao | alpha^I_rlm >, shape=[nao x natom x nproj]
<NetMixin.proj_ovlp>  # overlap between origin and projected basis, reshaped
<NetMixin.proj_intor>  # 1-electron integrals between origin and projected basis, or say, real mol and composed mol
<t_make_pdm>  # return projected density matrix by shell 
```


