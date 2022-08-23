---
title: cluster expansion greenhand-friendly
tags: [physics/solidstate, hands-on]
---

This is a note on the operational stuff on cluster expansion.

## Concepts
- Atom
	- The element to form cluster, which presents various states in lattice: does / doesn’t occupy certain site (or occupies certain site with certain spin direction).
	- All atoms are featured a variable called structure fundamental descriptor of crystal. The value of the variable is related to the atom site, spin, and other information that could be useful in CMS (and also your own denoting choice). Denotes by $\sigma_{p}$ (Here I only show that $\sigma_{p}$ varies by position, but it still could vary by other parameters).
- Cluster
	- Filled by atom-combination, of which the atom must be variable-concentration in the structure and the effective cluster interaction must exist between the atoms. The atom could be replaced by vacancy in the structure. The atom in cluster x could be the member of cluster y.
	- Clusters are not about the detailed state of atoms, but about the spatial configuration.
	- The state of a cluster is defined by the product of $\sigma_{p,s}$ in the cluster under certain crystal configurations.
- Equivalent Clusters
	- Derived from same atom-combination through different space group operations, and present the same effective cluster interaction.
	- The clusters are coupling-tolerant (different clusters could include common atom), although orbits are coupling-prohibited (there must be no common cluster in different clusters).
- Orbit
	- A logical set of equivalent clusters. The cluster which belongs to orbit x must not belong to orbit y. In cluster structure information for the calculation, any orbit is not equivalent to the others.
	- The orbit is just a logical concept as a set of equivalent clusters.
- Chief Cluster
	- The first cluster of one orbit. In an orbit, any cluster could be the chief one.
- Multiplicity of Cluster
	- Number of equivalent clusters to chief cluster (include itself); also the number of clusters in an orbit.
- Effective Cluster Interaction (ECI)
	- A cluster is an aggregation of atom(s) which can present the effect to total energy of system. The effect is so called effective cluster interaction.

## Cluster Expansion Step by Step

$$
E(\sigma) = \sum_\alpha m_\alpha J_\alpha \langle \prod_{p \in \alpha'} \sigma_{p} \rangle
$$

- $\alpha$ denotes the chief cluster of an orbit.
	- The orbit is symbolized by $\alpha$ to some extent.
	- Sometimes I consider orbit a useless concept.
- $\alpha'$ are the equivalent clusters of $\alpha$
- $J$ is the ECI, effective cluster interaction. It is actually determined by First Principle calculation (when clusters are chosen).
- $m_\alpha$ is the cluster multiplicity for the orbit.
- $\sigma$ is the current configuration of the matter / crystal, etc.
	- $\sigma_p$ is the atoms arrangement variable. It is the variable for atom at site $p$. I mentioned the variable above with a name "structure fundamental descriptor of crystal"
	- The variable vary by atom type, spin.
	- For common bialloy cases, $\pm 1$ is OK.
	- I think the choice related to the values of ECI.

For an orbit, the cluster $\alpha$ is chosen to by the chief cluster as a faithful symbol of the orbit (here "faithful" is just for fun, for I thought of "faithful representation" in group theory the semester). Still, there are many clusters, which is correlated to the chief one by a spatial transformation, belongs to the orbit denote by $\{\alpha'\}$.

For each of the cluster $\alpha'$, the state of the cluster is defined by the product of atom properties descriptor as below. Actually the state of cluster is a function of cluster, which is used to describe the cluster (describe what? energy property I guess, see below).

$$
\alpha'_{state} = \prod_{\sigma_p \in \alpha'} \sigma_{p}
$$

Here I feel a little bit confused by the qualititive arguments (Wu et al., 2016):

> "Because every atom is identical to the other(s) in common cluster, and state of each atom is necessary for representation of cluster state, cluster function of ax can be formulated as a function of its atoms arrangement as (above)."

But now that the cluster expansion works for most occasions, we should buy the speaker's story and continue to see what happens next.

We have the state of cluster, presumably capable to describe the clusters $\{\alpha'\}$, we should find some way to describe the orbit $O_\alpha$ denotes by its chief cluster $\alpha$, say the state of orbit.

Although all the cluster are of similar spatial configuration (let alone the difference of a spatial transformation), the states of different clusters in the same orbit could be different (for the descriptors of atoms $\sigma_{p,i,s}$ are different). Here we simply (naively?) describe the state of orbit by the average of its clusters, see below.

$$
O_{\alpha, state} = \langle \alpha_{state} \rangle = \langle \prod_{p \in \alpha'} \sigma_p \rangle \quad \forall \alpha' \in \{\alpha'\}_\alpha
$$

Hereby, the rest seems straight forward. The $J_\alpha$ (ECI), which vary by different orbits (so it vary by different chief cluster, as its subscript tells us),  is calculated by First Principle methods when the clusters are defined. Considering that there are many clusters in the same orbit, we should use the multiplicity $m_\alpha$ , the number of clusters in the orbit denoted by $\alpha$, to ensure that the energy is reasonable when there is multiplicity. After all, we should sum up all the orbits and get the final expression for energy.

$$
E(\sigma) = \sum_\alpha m_\alpha J_\alpha \langle \prod_{p \in \alpha'} \sigma_{p} \rangle
$$

May I address again that $\sigma$ here is the current configuration of the matter / crystal, etc, $\alpha$s are the chief clusters of orbits, $\{\alpha'\}$ is a set of clusters in the orbit denotes by $\alpha$, and $p$ is the position of atom (its "structure fundamental descriptor" is $\sigma_p$)

By the way, the orbits could be classified by the atom number in one of their own clusters. (What a complex and "don't know what for" classification system!)

## references
- [ATAT: Theoretical Background](https://www.brown.edu/Departments/Engineering/Labs/avdw/atat/manual/node19.html)
- Wu, Q. et al. (2016) ‘Cluster expansion method and its application in computational materials science’, Computational Materials Science, 125, pp. 243–254. doi:10.1016/j.commatsci.2016.08.034.


