---
title: structure searching general
tags: [AI4Science/structure_searching]
---

## features of PES

3 points


## local minima

Suppose that a large system of $N$ atoms can be divided into $M$ equivalent subsystems, each of $\frac{N}{M}$ atoms. If the subsystems are large enough they will have independent stable configurations. The total number of locally stable configurations of the system $n_s$, therefore satisfies:
$$
n_s(N) = \left[ n_s (\dfrac{N}{M}) \right]^M
$$
And the solution is
$$
n_s(N) = \mathrm{e}^{\alpha N}
\quad
\alpha \in \mathbb{C}
$$
Therefore, the local minimas on the PES proliferate with the system atom numbers.


## Importance of structure searching
- Structure prediction is relevant to all areas of science in which one would like to know the relative positions of atoms.
- Computational searching can be much easier and cheaper than experiments.
- The low energy metastable minima are also interesting as they can be accessed at finite temperatures, under pressure, or trapped during growth or processing.
- Computational searches can augment experimental studies when the data is of poor quality or incomplete.
- Computational searches can also be used to investigate materials under conditions which cannot currently be accessed experimentally.


## references
- [[自制课程]材料结构搜索-AIRSS](https://www.bilibili.com/video/BV12v411r7i9)