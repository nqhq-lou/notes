---
title: memo for PySCF
tags: [python/module/PySCF]
---


## files & quick look-up

[Predefined _xc_ Functionals and Functional Aliases](https://pyscf.org/user/dft.html#predefined-xc-functionals-and-functional-aliases "Permalink to this heading")

- PySCF supports two independent libraries of _xc_ functional implementations, namely [Libxc](https://www.tddft.org/programs/libxc/) and [XCFun](https://xcfun.readthedocs.io/en/latest/).
- The former of these is the default, but the latter may be selected by setting `DFT._numint.libxc = dft.xcfun`, cf. [dft/32-xcfun_as_default.py](https://github.com/pyscf/pyscf/blob/master/examples/dft/32-xcfun_as_default.py).
- For complete lists of the available density functional approximations, the user is referred to the `XC_CODES` dictionaries in [pyscf/dft/libxc.py](https://github.com/pyscf/pyscf/blob/master/pyscf/dft/libxc.py) and [pyscf/dft/xcfun.py](https://github.com/pyscf/pyscf/blob/master/pyscf/dft/xcfun.py), respectively.
- The user can choose the library at runtime in order to leverage any of its exclusive features.

[Molecular structure - basis set](https://pyscf.org/user/gto.html#basis-set)
- For complete lists of the available basis, see [pyscf/gto/basis/\_\_init\_\_.py](https://github.com/pyscf/pyscf/blob/master/pyscf/gto/basis/__init__.py)

- For lattice structure
	- pseudo potentials: [pyscf/pbc/gto/pseudo/\_\_init\_\_.py](https://github.com/pyscf/pyscf/blob/master/pyscf/pbc/gto/pseudo/__init__.py)
	- basis: [pyscf/pbc/gto/basis/\_\_init\_\_.py](https://github.com/pyscf/pyscf/blob/master/pyscf/pbc/gto/basis/__init__.py)
















