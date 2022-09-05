---
title: Kohn-Sham scheme in DFT calculationn
tags: [physics/solidstate, physics/DFT, physics/Kohn-Sham]
---


## procedure

common N-electron wave function:
$$
(\hat{T} + \hat{V}_{ee} + \hat{V}_{ext}) \Psi_0 = E \Psi_0
$$
operators for 
- kinetic
- electron-electron interaction
- and external potential


In the standard Kohn-Sham scheme, one employs an auxiliary non-interacting system under an effective external potential $\hat{V}_{KS}$, which yields the same ground-state electron density as the original interacting system.
$$
(\hat{T} + \hat{V}_{KS}) \phi_i = \epsilon_i \phi_i
\quad
\hat{V}_{KS} = \hat{V}_{ext} + \hat{V}_H + \hat{V}_{XC}
$$
- the external potential of the original interacting systems
- the Hartree potential, namely the static Coulomb potential produced by the electron density of the system
- the exchange-correlation potential, which captures the remaining electron-electron interactions
	- XC may have non-local contributions.

## XC term

- The XC term is the key term in KS scheme.
- Many methods came up with, like LDA, GGA, etc.