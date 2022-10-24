---
title: Lowdin's method of symmetric orthogonalization
tags: [physics/math]
---

## benefits

- the symmetric orthogonal basis functions have the closest in the least-squares to the original nonorthogonal functions.
- In TB method, hopping terms are really small if use Lowdin-orthogonalized AO basis.


## derivative

### presetting
- $\{\varphi_i\}$: nonorthogonal but linearly independent basis function set
	- overlap matrix $S$ with $S_{ij}=\braket{\varphi_i | \varphi_j}$
- $\{\psi_i\}$: orthogonal and linearly independent basis function set
	- relation to $\{\varphi_i\}$: $\psi_i = \sum_{k} C_{ki} \varphi_k$
	- overlap matrix $S$ with $\braket{\psi_i | \psi_j} = \delta_{ij}$
	- hence $$\braket{\psi_i | \psi_j} = \braket{ \sum_{k} C_{ki} \varphi_k | \sum_{l} C_{lj} \varphi_l} = \sum_{k,l} C_{ki}^* S_{kl} C_{lj} = \delta_{ij}$$
	- then $CC^\dagger =S^{-1}$

### conditions
- least square root: $$\sum_i \int | \psi_i - \varphi_i |^2 \mathrm{d} \tau'
= \sum_i \braket{\psi_i - \varphi_i | \psi_i - \varphi_i} \Rightarrow \mathrm{min}$$
- i.e., $$ \sum_i ( \braket{\varphi_i | \psi_i} + \braket{\psi_i | \varphi_i} ) \Rightarrow \mathrm{max}$$
- Here we suppose that we have reached the explicit result of $\psi$, and do a little variation to the basis set, say $\delta \psi$.
- i.e., $$ \sum_i ( \braket{\varphi_i | \delta \psi_i} + \braket{\delta \psi_i | \varphi_i} ) = 0 $$
- We shall further derive the results by adopting proper variations.

### variations

#### variate phase
$$
\psi_i + \delta\psi_i = e^{i \eta} \psi_i
\Longrightarrow
\delta\psi_i = i \eta \psi_i
$$
$$
\braket{\varphi_i | i \eta \psi_i} + \braket{i \eta \psi_i | \varphi_i} = 0
\Longrightarrow
\braket{\varphi_i | \psi_i} = \braket{\psi_i | \varphi_i}
$$
$$
\sum_l S_{il} C_{li} = \sum_l C_{li}^* S_{li}
\Longleftrightarrow
(SC)_{ii} = (C^\dagger S)_{ii}
$$


#### variate by rotation
$$
\begin{aligned}
\delta{\psi_i} & = \eta \psi_j \\
\delta{\psi_j} & = -\eta^* \psi_i
\end{aligned}
\quad
(i \neq j)
$$
$$
\braket{\varphi_i | \delta \psi_i} +
\braket{\delta \psi_i | \varphi_i} +
\braket{\varphi_j | \delta \psi_j} +
\braket{\delta \psi_j | \varphi_j} = 0
\Longrightarrow
\eta (\braket{\varphi_i | \psi_j} - \braket{\psi_j | \varphi_i}) + \mathrm{c.c.} = 0
\Longrightarrow
\braket{\varphi_i | \psi_j} - \braket{\psi_j | \varphi_i} = 0
$$
$$
\sum_l S_{il} C_{lj} = \sum_l C_{li}^* S_{lj}
\Longleftrightarrow
(SC)_{ij} = (C^\dagger S)_{ij}
$$

#### sum up
$$
SC = C^\dagger S  \quad \mathrm{and} \quad CC^\dagger =S^{-1}
\Longrightarrow
SC^2 = 1 \quad C^2 = S^{-1}
$$
- easy to find that matrix C is Hermitian.
$$
C = S^{-\frac{1}{2}}
$$

## usage

### Slater-Koster band fitting

- Lowdin's method could be applied to obtain orthogonal wave function basis
	- with the loss of generality of parameters
	- and the loss of fitting parameters results in worse mse in fitting.




