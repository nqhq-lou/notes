---
title: Hartree-Fock method
tags: [physics/HFmethod]
---


## basics
- The **Hartree–Fock** (**HF**) method is a method of approximation for the determination of the [wave function](https://en.wikipedia.org/wiki/Wave_function "Wave function") and the energy of a [quantum many-body system](https://en.wikipedia.org/wiki/Many-body_problem) in a [stationary state](https://en.wikipedia.org/wiki/Stationary_state "Stationary state").
- The Hartree–Fock method is also called the **self-consistent field method** (**SCF**)
	- The [Fork operator](https://en.wikipedia.org/wiki/Hartree%E2%80%93Fock_method#The_Fock_operator) in the SCF calculation demands that each particle is subjected to the mean field created by all other particles.
	- And the equations are mostly solved by iterative method based on fixed-point iteration algorithm. But note that this doesn't always converge (see Wiki footnotes).
- traditional HF method deals with only closed shell system, which means that each orbit (shell) is occupied by two electrons.

## approximations adopted
- Born-Oppenheimer approximation
- neglect relativistic effects
- a finite number of nonorthogonal basis functions
	- which is expected to be expressive enough
-  Each [energy eigenfunction](https://en.wikipedia.org/wiki/Energy_eigenfunction "Energy eigenfunction") is assumed to be describable by a single [Slater determinant](https://en.wikipedia.org/wiki/Slater_determinant "Slater determinant"), an anti-symmetrized product of one-electron wave functions (i.e., [orbitals](https://en.wikipedia.org/wiki/Molecular_orbital "Molecular orbital")).
	- I think this is an extension on mean-field approximation
	- don't understand
- mean-field approximation
	- Coulomb correlation is ignored, which results in not capable in showing London dispersion.

![[Hartree-Fock_method_SCF_iteration.png|500]]


## Fock matrix


$$
\hat{F}[\{\phi_j\}]^i = \hat{H}^i
+ \sum_{j=1}^{n/2} [ 2 \hat{J}_j^i - \hat{K}_j^i]
$$
- $\{\phi_j\}$ is a set of orbitals basis
- $i$ for i-th electron in the system
- $\hat{H}^i = - \frac{1}{2} \nabla_i^2 - \sum_I \frac{Z_I}{r_{iI}}$, is one-electron Hamiltonian, where $I$ labels nuclei.
- $\hat{J}_j^i$ is the Coulomb operator defining the e-e repulsion energy from the j-th orbital to the i-th electron.
- $\hat{K}_j^i$ is the exchange operator, and is from the anti-symmetry of total $n$-electron wave function.
	- It is simply an artifact of the Slater determinant.
- explicit form of the last two operator?


## references
- [Hartree-Fock method from Wikipedia](https://en.wikipedia.org/wiki/Hartree%E2%80%93Fock_method)
- [Fock operator from Wikipedia](https://en.wikipedia.org/wiki/Hartree%E2%80%93Fock_method#The_Fock_operator)
- Attila Szabo and Neil S. Ostlund, _Modern Quantum Chemistry: Introduction to Advanced Electronic Structure Theory_ (Dover Publications, 1996), [http://gen.lib.rus.ec/book/index.php?md5=8ca9029b150ce3b511fb2392f8a21400](http://gen.lib.rus.ec/book/index.php?md5=8ca9029b150ce3b511fb2392f8a21400).




