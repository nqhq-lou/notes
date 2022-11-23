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
$$
\braket{\vec{r} | \alpha_{nlm}} = R_n(r) Y_{lm}(\theta, \phi)
$$

- atomic-centered descriptor
	- for atom with index $I$
	- 感觉ab各自求和有点怪
$$
D_{nl,mm'}^{I} = \sum_{occ,i;a,b} c_{ai} (c_{bi})^*
\braket{\alpha_{nlm}^I | \phi_a} \braket{\phi_b | \alpha_{nlm'}^I}
$$

- or better explanation: atomic-centered wave function projection
	- atomic index $I$, MO index $i$
$$
c_{nlm}^{I,i} = \braket{\alpha_{nlm}^{I} | \psi_i}
= \sum_{a} c_{ai} \braket{\alpha_{nlm}^{I} | \phi_a}
$$
- then from wave function projection to descriptor
$$
D_{nl,mm'}^{I} = c_{nlm}^{I,i} c_{nlm'}^{I,i *}
$$

- Thermal embedding: rank eigvals by value
$$
d_{nl}^I = \mathrm{EigVal}_{mm'}(D_{nl,mm'}^{I}) \quad \text{(sort by value)}
$$

- 因为之后要GNN, 所以就不考虑更多双点的descriptor模式了


## BP gradient

- mock loss, $r$ is quad grid points
$$E_{XC} = \sum_{r} w^g (r) f^g (r) \rho(r)$$
- target
$$V_{XC}(r^g) = \dfrac{\delta E_{XC}}{\delta \rho(r^g)}
= w^g (r^g) f^g(r^g) + \sum_r w^g (r) \rho^g (r) \dfrac{\delta f^g (r)}{\delta \rho(r^g)}$$
- d




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


