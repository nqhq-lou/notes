


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

