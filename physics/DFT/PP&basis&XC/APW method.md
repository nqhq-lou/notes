---
title: augmented plane wave method
tags: [physics/solidstate/band]
---



Augmented wave method is also called muffin-tin potential.

Outside the muffin tin sphere, we use plane wave:
$$
\psi_{q}^{\mathrm{PW}} = e ^{i q \cdot r}
\quad
q = k + K
$$

Inside the sphere, we use the atomic orbital:
$$
\sum_{l=0}^{\inf} \sum_{m=-l}^{l}
A_{lm} \mathcal{R}_l (r) Y_m^l (\theta, \phi)
$$

The radical part of wave function satisfies the atomic wave function:
$$
\left\{
- \dfrac{1}{2r} \dfrac{d^2}{dr^2} r
+ \left[ \dfrac{l(l+1)}{2r^2} + V(r) \right]
\right\}
\mathcal{R}_l(r) = E \mathcal{R}_l(r)
$$
And here the $V(r)$ can be exact Coulomb potential, K-S DFT functionals, or effective potential.

In APW, we match these two wave functions at he muffin boundary, using the spherical harmonic expansion of plane wave (refer to scattering / partial wave analysis in Xiao's lecture).
$$
e^{i q \cdot r} = 
\sum_{l=0}^{\inf} (2l+1) i^l j_l(qr) P_l(\cos(\theta'))
\quad
\theta' = \angle(r, q)
$$

Together with Legendre P and spherical harmonic function Y:
($\theta$ $\theta'$ $\theta_q$ are absolute angle to frame, $\angle(r, q)$ and wave vector's angle to frame)
$$
P_l (\cos(\theta')) = \dfrac{4\pi}{2l+1}
\sum_{m=-l}^{l} (-1)^m Y_{-m}^{l}(\theta_q, \phi_q) Y_m^l (\theta, \phi)
\qquad
(-1)^m Y_{-m}^{l} = (Y_{m}^{l})^*
$$$$
e^{i q \cdot r} = 4\pi \sum_{l=0}^{\inf} \sum_{m=-l}^{l}
i^l j_l (qr) (Y_{m}^{l})^*(\theta_q, \phi_q) Y_m^l (\theta, \phi)
$$
So the plane wave could be converted to the summation of functions, where $R$ is the boundary to the muffin-tin potential.
$$
\psi_q^{\mathrm{PW}}(r) = 4\pi \sum_{l,m} i^l
\left[ \dfrac{j_l (qR)}{\mathcal{R}_l(R)} \right]
\mathcal{R}_l(r) (Y_{m}^{l})^*(\theta_q, \phi_q) Y_m^l (\theta, \phi)
\quad
(r < R)(\text{really? dont understand})
$$

Finally with the linear combination of APW wave, we can reach the best estimation of wave function, where the $\psi^\mathrm{PW}$ are the actual basis to the system.
$$
\psi_k (r) = \sum_{K} C_K \psi_{k+K}^{\mathrm{PW}} (r)
$$

With the crystal potential known, we could write the eigen value problem, and then add to it some modifications
$$
HC=ESC
\qquad
(\mathcal{H} - E) C = 0
\qquad
\mathcal{H} = H - ES + EI
$$

Here this is actually a root finding problem, with common solution found in any computational physics textbook.

## details on Hamiltonian

$$
\begin{aligned}
\mathcal{H}_{ij} & = \langle \boldsymbol{k}+\boldsymbol{K}_i \vert \mathcal{H}\vert \boldsymbol{k}+\boldsymbol{K}_j \rangle \\
& = -EA_{ij} + B_{ij} + \sum_{l=0}^{l_{\rm{max}}} C_{ijl}\frac{\mathcal{R}'_{l}(R)}{\mathcal{R}_{l}(R)} \end{aligned}
$$
$$
\begin{aligned}
A_{ij} & = \frac{-4\pi R^2 j_l(\vert\boldsymbol{K}_i-\boldsymbol{K}_j \vert R)}{\vert\boldsymbol{K}_i-\boldsymbol{K}_j \vert} + \delta_{ij} \\
B_{ij} & = \frac{1}{2}A_{ij}(\boldsymbol{q}_i\cdot\boldsymbol{q}_j)
\quad \boldsymbol{q}_{\lambda} = \boldsymbol{k}+\boldsymbol{K}_{\lambda},
\quad \lambda=i,j \\
C_{ijl} & = (2l+1)\frac{2\pi R^2}{\Omega}
P_{l}(\cos(\theta_{ij}))j_l(q_i R)j_{l}(q_j R) \\
\cos(\theta_{ij}) & =\frac{\boldsymbol{q}_i\cdot\boldsymbol{q}_j}{q_i q_j} \\ \end{aligned}
$$

Do it yourself: derive $ABC$ yourself.



## reference

- [Electronic Structure of solid, pre-DFT (1)](https://zhuanlan.zhihu.com/p/465776018)
- dd
- 