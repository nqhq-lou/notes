---
title: Dimenet
tags: [AI4Science/MPNNs]
---



## general idea
- This is for molecular dynamics simulation
	- so only atoms' positions and types are considered
- present all four parts of the energy incorporated
	- where non-bonded term mimics the van der Waals interactions and so on.
$$
E = E_{bonds} + E_{angle} + E_{torsion} + E_{non-bonded}
$$


## questions to be solved
- use equivariant embedding method
	- instead of distance matrix with cutoff
	- to be precise, continuous equivariance with respect to rotations
	- generate a separate embedding $m_{ji}$ for each atom i and the neighbor j by applying the same learned filter **in the direction of each neighboring atom**
	- $E_{bonds}$ is enabled here
- design special GNN procedure functions
	- $m_{ji}$s' aggregation is related to angle
	- use spherical Bessel functions
	- $E_{angle}$ is enabled here
- summary
	- the messages are essentially embeddings of atom pairs rather than single atom with its environment
	- So this is provably more efficient in distinguishing difference in structure


## solutions

### Bessel functions
- early work uses gaussian radical basis, which might be redundant
- Here we use orthogonal Bessel functions for compactness and efficiency.

#### spherical part
- considered that should utilize $d_{kj}$ and $\alpha_{(kj,ji)}$ (where $i$ neighbors $j$ but not $k$)
	- set $m=0$, and use cutoff $c$ and zero-point $z_{ln}$
	- the descriptors then depends on $l$ and $n$, which is SHBF (harmonic) and SRBF (radical)
- best balanced performance for $N_{SRBF}=6$ in experiment
$$
a_{SBF}(d,\alpha) \propto j_l(\dfrac{z_{ln}}{c} d) Y_l^0 (\alpha)
$$
#### radical part
- for only radical information (no $\alpha$), just set $l=m=0$ and only varies $n$
	- this is simply a $sinc$ function
- best balanced performance for $N_{RBF}=6$ in experiment

### continuous cutoff
- cutoff is acted on $d$, chosen to have a second order zero point on the cutting edge.
- The form of cutoff function of weird! And not explained how to achieve it.


## what I could do

- see to embedding layer
	- just use the concat information, then do VAE



## notices
- use continuous activation function, not ReLU or LeakyReLU
	- for the continuous presentation of energy and force


