---
title: Symmetry considerations in ML for physical sciences
tags: [e3nn/lect]
---

[tutor1 video]
[tutor1 resources](https://e3nn.org/e3nn-tutorial-mrs-fall-2021/#tut1)

## past models

- Alphafold2
	- local and global reference frames
- DeePMD
	- have some symmetry considerations, but not complete


- related works
	- Tensor Field Networks (arXiv:1802.08219)
	- Clebsch-Gordan Nets (arXiv:1806.09231)
	- 3D Steerable CNNs (arXiv:1807.02547)
	- Cormorant (arXiv:1906.04015)
	- SE(3)-Transformers (arXiv:2006.10503)
	- e3nn (github.com/e3nn/e3nne3nn.org) (Technically, e3nn is the only one that implements inversion)

## ground theory

### group representation theory

- All operations are constructed to commute with the group action $D(g)$, like rotations, translations, inversion
	- $f(D(g)x, w) = D(g) f(x,w)$
- $D(g)$ different by what it is acting on, like scalars, vectors and tensors.

- geometric tensors
	- `o3.Irreps("1o")`: real vector
	- `o3.Irreps("1e")`: pseudo-vector
		- doesn't flip under inversion
	- `o3.Irreps("2e")`: double-headed vector
		- like oscillating electric field, just care about the time average
		- **what is this**
	- `o3.Irreps("2o")`: helix
		- doesn't change under rotate
		- change hand sign after inversion

- equivariant convolution
	- from CNN convolution kernel to $W(r)$ filter function in real space and graph
		- $W(r) = R(r)Y_l^m(\hat{r})$m, $R(r)$ is learnable
		- $R(r)$ is embedded length value and an MLP

- the e3nn e3 operations conserve the symmetry, which is good for physics


