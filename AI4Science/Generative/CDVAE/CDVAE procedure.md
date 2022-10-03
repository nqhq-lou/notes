---
title: CDVAE procedure
tags: [AI4Science/Generative/CDVAE]
---

## net components

- `fc_num_atoms`
	- MLP with several equi-dimension hidden layer
	- Input is VAE latent variable
	- Output is `max_atoms` + 1
- `fc_lattice`
	- MLP with several equi-dimension hidden layer
	- Input is VAE latent variable
	- Output is a vector of 6 scalars
		- Lattice is reduced to 6 unique, rotation invariant parameters with the Niggli algorithm, the lengths of the 3 lattice vectors, the angles between them.
