---
title: customizing XC functional in PySCF
tags: [AI4Science/PySCF]
---



```Python
def eval_xc(xc_code, rho, spin=0, relativity=0, deriv=1, verbose=None):
    # A fictitious functional to demonstrate the usage
    rho0, dx, dy, dz = rho
    gamma = (dx ** 2 + dy ** 2 + dz ** 2)
    exc = .01 * rho0 ** 2 + .02 * (gamma + .001) ** .5
    vrho = .01 * 2 * rho0
    vgamma = .02 * .5 * (gamma + .001) ** (-.5)
    vlapl = None
    vtau = None
    vxc = (vrho, vgamma, vlapl, vtau)
    fxc = None # 2nd-order functional derivative
    kxc = None # 3rd-order functional derivative
return exc, vxc, fxc, kxc

dft.libxc.define_xc_(mf_hf._numint, eval_xc, xctype='GGA')
# see the aboce function at pyscf.dft.numint -> pyscf.dft.libxc.define_xc_
mf_hf.kernel()



'''
>>> mol = gto.M(atom='O 0 0 0; H 0 0 1; H 0 1 0', basis='ccpvdz')
>>> mf = dft.RKS(mol)
>>> define_xc_(mf._numint, '.2*HF + .08*LDA + .72*B88, .81*LYP + .19*VWN')
>>> mf.kernel()
-76.3783361189611
>>> define_xc_(mf._numint, 'LDA*.08 + .72*B88 + .2*HF, .81*LYP + .19*VWN')
>>> mf.kernel()
-76.3783361189611
>>> def eval_xc(xc_code, rho, *args, **kwargs):
...     exc = 0.01 * rho**2
...     vrho = 0.01 * 3 * rho**2
...     vxc = (vrho, None, None, None)
...     fxc = None  # 2nd order functional derivative
...     kxc = None  # 3rd order functional derivative
...     return exc, vxc, fxc, kxc
>>> define_xc_(mf._numint, eval_xc, xctype='LDA')
>>> mf.kernel()
48.8525211046668
'''
```
- `define_xc_(ni, description, xctype='LDA', hyb=0, rsh=(0,0,0))`
- Define XC functional.  See also :func:`eval_xc` for the rules of input description.
- Args:
	- ni : an instance of :class:`NumInt`
	- description : str
		- A string to describe the linear combination of different XC functionals. The X and C functional are separated by comma like '.8\*LDA+.2\*B86,VWN'. If "HF" was appeared in the string, it stands for the exact exchange.

- Kwargs:
	- xctype : str
		- 'LDA' or 'GGA' or 'MGGA'
	- hyb : float
		- hybrid functional coefficient
	- rsh : a list of three floats
		- coefficients (omega, alpha, beta) for range-separated hybrid functional.
		- omega is the exponent factor in attenuated Coulomb operator e^{-omega r_{12}}/r_{12}
		- alpha is the coefficient for long-range part, hybrid coefficient can be obtained by alpha + beta

Examples:




- convert self-defined xc functional to numerical integral
	- [`dft.RKS.define_xc_(my_xc, type,)`](https://github.com/pyscf/pyscf/blob/7b91b3ce5a00947654c9057bdf1a22499278b2bf/examples/dft/24-define_xc_functional.py#L50)



## references
- [customizing xc functionals - PySCF docs](https://pyscf.org/user/dft.html#customizing-xc-functionals)
- [24-define_xc_functional - PySCF examples](https://github.com/pyscf/pyscf/blob/master/examples/dft/24-define_xc_functional.py)


