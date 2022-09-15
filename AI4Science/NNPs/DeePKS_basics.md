---
title: DeePKS intro
tags: [AI4Science/NNPs]
---

- relevant notes
	- [[DFT_ABACUS_DeePKS#基于机器学习的密度泛函]]



## basics
- Deep Potential Kohn-Sham model, a ML-based DFT model
	- One of the DeePMD (deep potential method) method 
	- The goal it to lift the accuracy of baseline functionals towards that provided by more accurate methods via a ML-based model while maintaining their efficiency
- A neural network-based functional model is used to construct a correction term, used as XC functional.
	- Offers closely-matched energies and forces, while requires magnitude less training data in comparison.
	- DeePKS can serve as a bridge between expensive QM models and ML potentials: one can generate a decent amount of high-accuracy QM data to train a DeePKS model, and then use the DeePKS model to label a much larger amount of configurations to train a ML potential.
- relevant works: NeuralXC, OrbNet


## procedure
- DeePKS model reproduces the target energies and forces given by strongly constrained and appropriately normed (SCAN) meta-GGA functional for salt water and hybrid SCAN0 functional for pure water at only a few times more expensive computational cost as compared to the Perdew-Burke-Ernzerhof (PBE) GGA functional.
- The trained DeePKS model is applied in SCF calculations to generate labels for the DeePMD model, with an estimated two orders of magnitude saving in computational time for labeling.
- The resulting DeePMD model is then employed for MD simulations to compute various structural and dynamical properties of pure and salt water.
- Excellent agreement is found between the results and previously made results upon SCAN method.

![[DFT_ABACUS_ML_DeePKS_iteration.png|400]]

## references
- 

