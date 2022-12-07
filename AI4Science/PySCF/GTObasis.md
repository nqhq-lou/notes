---
title: look into pyscf basis formatting
tags: [AI4Science/PySCF]
---

```Python
"""called functions"""
<pyscf.gto.mole>
[L2406] Mole.build()
[L2505] self._basis = self.format_basis(_basis)
[L2613] def format_basis(self, basis_tab): return format_basis(basis_tab)
[L410] def format_basis(basis_tab)

'''Convert the input :attr:`Mole.basis` to the internal data format.

``{ atom: [(l, ((-exp, c_1, c_2, ..),
				(-exp, c_1, c_2, ..))),
		   (l, ((-exp, c_1, c_2, ..),
				(-exp, c_1, c_2, ..)))], ... }``

Args:
	basis_tab : dict
		Similar to :attr:`Mole.basis`, it **cannot** be a str

Returns:
	Formated :attr:`~Mole.basis`

Examples:

>>> gto.format_basis({'H':'sto-3g', 'H^2': '3-21g'})
{'H': [[0,
	[3.4252509099999999, 0.15432897000000001],
	[0.62391373000000006, 0.53532813999999995],
	[0.16885539999999999, 0.44463454000000002]]],
 'H^2': [[0,
	[5.4471780000000001, 0.15628500000000001],
	[0.82454700000000003, 0.90469100000000002]],
	[0, [0.18319199999999999, 1.0]]]}
'''
```



