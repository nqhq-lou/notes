


## integral

- use `mol.intor()`

```Python
S = mol.intor("int1e_ovlp")  # overlap matrix, shape (N,N)
T = mol.intor("int1e_kin")  # kinetic matrix, shape (N,N)
eri = mol.intor("int2e")  # double electron matrix, shape (N,N,N,N)
mdip = mol.intor("int1e_r")  # dipole, shape (3,N,N)
```

- for detailed integral string,
	- [`pyscf.gto.moleintor`](https://pyscf.org/pyscf_api_docs/pyscf.gto.html#module-pyscf.gto.moleintor)
		- `int_name` not sufficient
	- for detailed integrate list, see [`pyscf.gto.moleintor._INTOR_FUNCTIONS`](https://github.com/pyscf/pyscf/blob/master/pyscf/gto/moleintor.py#L263)
		- this one should be all the `int_name`s


## numint module

- `dft.numint`

- `eval_ao`: Evaluate AO function value on the given grids.
	- actually call `mol.eval_gto()` from `gto.eval_got.eval_gto`
- `eval_rho`


## memo

```Python
ni = dft.numint.NumInt()
int_gen = ni.block_loop(mol, quad_grids, nao, 1, 2048)  # generator for integral

quad_grids_ao, quad_grids_weights, quad_grids_coords = numpy.zeros((4, ngrids, nao)), numpy.zeros(ngrids), numpy.zeros((ngrids, 3))
g_start, g_end, g_mem = 0, 0, 2000  # index label, index label, 确保不会内存裂开
for ao, mask, weights, coords in ni.block_loop(mol, quad_grids, nao, deriv=1, g_mem):
    g_end = g_start + ao.shape[1]
    g_slice = slice(g_start, g_end)
    quad_grids_ao[:, g_slice, :] = ao  # ni.eval_ao(), with first derivative, shape (4, N, nao)
    quad_grids_weights[g_slice] = weights  # grids.weights
    quad_grids_coords[g_slice] = coords  # grids.coords
    g_start = g_end  # for indexing
```



## LDA

- 电子能量
$$
E_{elec}[D_{\mu\nu}] = (h_{\mu\nu} + \dfrac{1}{2} J_{\mu\nu} [D_{\kappa\lambda}]) D_{\mu\nu} + E_x^{Slater} [\rho]
$$
- Slater交换能, on quad grids
$$
E_x^{Slater}[\rho] = -\dfrac{3}{4} \left(\dfrac{3}{\pi}\right)^{1/3} w_g \rho_g^{4/3}
$$
- Slater交换能核
$$
f^\mathrm{Slater} [\rho] = - \frac{3}{4}\left( \frac{3}{\pi} \right)^{1/3} \rho^{1/3}
$$
- $w_g, \rho_g$为weight, 当地密度
```Python
E_s = (-3/4) * (3/numpy.pi)**(1/3) * (grids.weights * rho_s_0**(4/3)).sum()  # Slater energy
kernel_s = - 3/4 * (3/numpy.pi)**(1/3) * rho_s_0**(1/3)  # Slater kernel
exc_s = ni.eval_xc("Slater", rho_s_0, deriv=0)[0]  # Slater kernel
```

- dd

