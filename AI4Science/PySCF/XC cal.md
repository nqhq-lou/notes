---
title: XC calculation in pyscf
tags: [AI4Science/PySCF]
---




## XC eval

path to code: [`pyscf.dft.libxc.eval_xc`](https://github.com/pyscf/pyscf/blob/master/pyscf/dft/libxc.py#L1333)

### brief

Interface to call libxc library to evaluate XC functional, potential and functional derivatives.
* The given functional xc_code must be a one-line string.
* The functional xc_code is case-insensitive.
* The functional xc_code string has two parts, separated by ",".  The first part describes the exchange functional, the second part sets the correlation functional.
	- If "," not appeared in string, the entire string is treated as the name of a compound functional (containing both the exchange and the correlation functional) which was declared in the functional aliases list. The full list of functional aliases can be obtained by calling the function `pyscf.dft.xcfun.XC_ALIAS.keys()`.
		- If the string was not found in the aliased functional list, it is treated as X functional.
	- To input only X functional (without C functional), leave the second part blank. E.g. description='slater,' means a functional with LDA contribution only.
	- To neglect the contribution of X functional (just apply C functional), leave blank in the first part, e.g. description=',vwn' means a functional with VWN only.
	- If compound XC functional is specified, no matter whether it is in the X part (the string in front of comma) or the C part (the string behind comma), both X and C functionals of the compound XC functional will be used.
* The functional name can be placed in arbitrary order.  Two names need to be separated by operators "+" or "-".  Blank spaces are ignored.
	* NOTE the parser only reads operators "+" "-" "\*".  / is not supported.
* A functional name can have at most one factor.  If the factor is not given, it is set to 1.  Compound functional can be scaled as a unit. For example `'0.5*b3lyp'` is equivalent to `'HF*0.1 + .04*LDA + .36*B88, .405*LYP + .095*VWN'`
* String "HF" stands for exact exchange (HF K matrix).  "HF" can be put in the correlation functional part (after comma). Putting "HF" in the correlation part is the same to putting "HF" in the exchange part.
* String "RSH" means range-separated operator. Its format is RSH(omega, alpha, beta).  Another way to input RSH is to use keywords SR_HF and LR_HF: `"SR_HF(0.1) * alpha_plus_beta" and "LR_HF(0.1) * alpha"` where the number in parenthesis is the value of omega.
* Be careful with the libxc convention of GGA functional, in which the LDA contribution is included.

### Args
- xc_code : str
	- A string to describe the linear combination of different XC functionals. The X and C functional are separated by comma like `'.8*LDA+.2*B86,VWN'`. If "HF" (exact exchange) is appeared in the string, the HF part will be skipped.  If an empty string "" is given, the returns `exc, vxc,...` will be vectors of zeros.
- rho : ndarray
	- Shape of `((*,N))` for electron density (and derivatives) if spin = 0; Shape of `((*,N),(*,N))` for alpha/beta electron density (and derivatives) if spin > 0; where N is number of grids. rho `(*,N)` are ordered as `(den,grad_x,grad_y,grad_z,laplacian,tau)` where `grad_x = d/dx den`, `laplacian = \nabla^2 den`, `tau = 1/2(\nabla f)^2`.
	- In spin unrestricted case, rho is `((den_u,grad_xu,grad_yu,grad_zu,laplacian_u,tau_u) (den_d,grad_xd,grad_yd,grad_zd,laplacian_d,tau_d))`
  
### Kwargs
- spin : int
	- spin polarized if spin > 0
- relativity : int
	- No effects.
- verbose : int or object of :class:`Logger`
	- No effects.

- Returns:
	- `ex, vxc, fxc, kxc`, where
	* `vxc = (vrho, vsigma, vlapl, vtau)` for restricted case
	* `vxc` for unrestricted case
	```
	| vrho[:,2]   = (u, d)
	| vsigma[:,3] = (uu, ud, dd)
	| vlapl[:,2]  = (u, d)
	| vtau[:,2]   = (u, d)
	```
	* `fxc` for restricted case:
        `(v2rho2, v2rhosigma, v2sigma2, v2lapl2, vtau2, v2rholapl, v2rhotau, v2lapltau, v2sigmalapl, v2sigmatau)`
	* `fxc` for unrestricted case:
	```
	| v2rho2[:,3]     = (u_u, u_d, d_d)
	| v2rhosigma[:,6] = (u_uu, u_ud, u_dd, d_uu, d_ud, d_dd)
	| v2sigma2[:,6]   = (uu_uu, uu_ud, uu_dd, ud_ud, ud_dd, dd_dd)
	| v2lapl2[:,3]
	| v2tau2[:,3]     = (u_u, u_d, d_d)
	| v2rholapl[:,4]
	| v2rhotau[:,4]   = (u_u, u_d, d_u, d_d)
	| v2lapltau[:,4]
	| v2sigmalapl[:,6]
	| v2sigmatau[:,6] = (uu_u, uu_d, ud_u, ud_d, dd_u, dd_d)
	```
	- `kxc` for restricted case:
        (v3rho3, v3rho2sigma, v3rhosigma2, v3sigma3,
        v3rho2lapl, v3rho2tau,
        v3rhosigmalapl, v3rhosigmatau,
        v3rholapl2, v3rholapltau, v3rhotau2,
        v3sigma2lapl, v3sigma2tau,
        v3sigmalapl2, v3sigmalapltau, v3sigmatau2,
        v3lapl3, v3lapl2tau, v3lapltau2, v3tau3)
	* `kxc` for unrestricted case:
	```
	| v3rho3[:,4]         = (u_u_u, u_u_d, u_d_d, d_d_d)
	| v3rho2sigma[:,9]    = (u_u_uu, u_u_ud, u_u_dd, u_d_uu, u_d_ud, u_d_dd, d_d_uu, d_d_ud, d_d_dd)
	| v3rhosigma2[:,12]   = (u_uu_uu, u_uu_ud, u_uu_dd, u_ud_ud, u_ud_dd, u_dd_dd, d_uu_uu, d_uu_ud, d_uu_dd, d_ud_ud, d_ud_dd, d_dd_dd)
	| v3sigma3[:,10]      = (uu_uu_uu, uu_uu_ud, uu_uu_dd, uu_ud_ud, uu_ud_dd, uu_dd_dd, ud_ud_ud, ud_ud_dd, ud_dd_dd, dd_dd_dd)
	| v3rho2lapl[:,6]
	| v3rho2tau[:,6]      = (u_u_u, u_u_d, u_d_u, u_d_d, d_d_u, d_d_d)
	| v3rhosigmalapl[:,12]
	| v3rhosigmatau[:,12] = (u_uu_u, u_uu_d, u_ud_u, u_ud_d, u_dd_u, u_dd_d,
						d_uu_u, d_uu_d, d_ud_u, d_ud_d, d_dd_u, d_dd_d)
	| v3rholapl2[:,6]
	| v3rholapltau[:,8]
	| v3rhotau2[:,6]      = (u_u_u, u_u_d, u_d_d, d_u_u, d_u_d, d_d_d)
	| v3sigma2lapl[:,12]
	| v3sigma2tau[:,12]   = (uu_uu_u, uu_uu_d, uu_ud_u, uu_ud_d, uu_dd_u, uu_dd_d,
						ud_ud_u, ud_ud_d, ud_dd_u, ud_dd_d, dd_dd_u, dd_dd_d)
	| v3sigmalapl2[:,9]
	| v3sigmalapltau[:,12]
	| v3sigmatau2[:,9]    = (uu_u_u, uu_u_d, uu_d_d, ud_u_u, ud_u_d, ud_d_d, dd_u_u, dd_u_d, dd_d_d)
	| v3lapl3[:,4]
	| v3lapl2tau[:,6]
	| v3lapltau2[:,6]
	| v3tau3[:,4]         = (u_u_u, u_u_d, u_d_d, d_d_d)
	```
- see also `libxc_itrf.c`





