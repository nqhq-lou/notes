---
title: SOAP - Smooth Overlap of Atomic Positions descriptor
tags: [AI4Science/descriptor]
---



## construction

- atom $i$, neighbor $j$ and its element type $a_j$, element type $a$.
- for atom $i$ and neighbor chemical element $a$, the env is
	- use regularity(or smoothness) $\sigma_a$, cutoff function $f_{cut}(r)$
$$
\rho^{i,a} (\vec{r}) = \sum_j \delta_{a,a_j}
\exp \left( \dfrac{- |r-r_{ij}|^2}{2 \sigma_a^2} \right) f_{cut} (r_{ij})
$$
- use braket formalism
	- $\braket{q|A}$, $q$ for presentation and selection, $A$ for physics quantity
	- $\rho^{i,a}(\vec{r}) = \braket{a \vec{r} | \rho_i}$, here $\rho_i$ is the density surrounded atom $i$
	- $R_n (r) = \braket{r | n}$ for a basis of orthogonal radial function
	- $Y_l^m(\hat{r}) = \braket{\hat{r}|lm}$ for spherical harmonics
- expand the $\rho^{i,a} (r)$ by radical and spherical orthogonal basis
$$
\rho^{i,a} (\vec{r}) = \sum_{nlm} c_{nlm}^{i,a} R_n (r) Y_l^m (\hat{r})
\qquad
\braket{a \vec{r}|\rho_i} = \braket{r|n} \braket{\hat{r}|lm} \braket{anlm|\rho_i}
$$
$$
c_{nlm}^{i,a} = \int d^3 \vec{r} R_n(r)^* Y_l^m(\hat{r})^* \rho^{i,a}(\vec{r})
\qquad
\braket{anlm|\rho_i} = \braket{n|r} \braket{lm|\hat{r}} \braket{a \vec{r}|\rho_i}
$$
- project it into power spectrum $p_{nn'l}^{i,aa'}$
	- This is actually averaging a double dot tensor product of atom density over rotations
	- usually the power spectrum is yield to unit length vector $\xi = p/|p|$
$$
p_{nn'l}^{i,aa'} = \dfrac{1}{\sqrt{2l+1}} \sum_m c_{nlm}^{i,a*} c_{n'lm}^{i,a'}
\qquad
\braket{an;a'n';l|\overline{\rho^{\otimes2}}} = \dfrac{1}{\sqrt{2l+1}} \sum_m
\braket{\rho_i|anlm} \braket{a'n'lm|\rho_i}
$$
- Channels to electron density
	- element channels $aa'$, radical channels $nn'$, angular channel $l$
- For each atom $i$ there is a power spectrum to it.

## Properties

- Smooth and continuous with respect to atomic displacements
- Invariant with respect to physical symmetries.
- Only one free parameter $\{\sigma_i\}$
	- must be related to physical properties like atomic radius by intuitions.
- not unique on the four-atom level, like bispectrum



## compare similarity

- 





## reference
- Volker L. Deringer et al., “Gaussian Process Regression for Materials and Molecules,” _Chemical Reviews_ 121, no. 16 (August 25, 2021): 10073–141, [https://doi.org/10.1021/acs.chemrev.1c00022](https://doi.org/10.1021/acs.chemrev.1c00022).