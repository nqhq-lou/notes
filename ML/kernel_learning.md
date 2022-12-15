---
title: kernel learning
tags: [ML/kernel]
---

## basics ideas

- Regression
	- dimension of weight $w$ is dependent on dimension of features $x$, say $D$
$$
\hat{y} = \vec{w} \cdot \vec{x} + b
$$
- Kernel learning
	- dimension of weight is dependent on the number of training points $N$
	- $\braket{\cdot}$ is distance between two feature vectors and $\vec{x}_i$ is the $i$th training data point.
	- $\braket{\cdot}$ is the **kernel function**
$$
\hat{y} = \sum_{i}^N w_i \braket{\vec{x}, \vec{x}_i} + b
$$
- benefits
	- $N < D$, reduce number of parameters
	- maybe if view data relations with distances, it is more clear
	- $\vec{w} \cdot \vec{x}$ is hard to compute (like a infinite function), but $\braket{\cdot}$ is easy to find

## kernel function
- should follow some properties
	- Positive: $\braket{x, x'} \ge 0$
	- Symmetric: $\braket{x, x'} = \braket{x', x}$
	- Point-separating: $\braket{x, x'} = 0$ if and only if $x = x'$
- common kernel functions
	- $l_2$ norm: $\braket{x, x'} = \sqrt{\sum_i^D (x_i - x_i')^2}$
		- **Kernel Ridge Regression**
	- $l_1$ norm
		- **Lasso Ridge Regression**
		- $l_1$ may zero-out specific parameters. But here it zeros out certain data point
		- So $l_2$ is more popular here.
	- Some of the most interesting applications of kernel learning though are when x is not a vector, but a function or some other structured object.


>**Primal & Dual Form**
>**Dual Form** is what some call our model equation when it uses the kernels: $\hat{y} = \sum_i^N w_i \left<\vec{x}, \vec{x}_i\right>+ b$.
>To distinguish from the dual form, you can also refer to the usual model equation as the **Primal Form**  $\hat{y} = \vec{w}\vec{x} + b$.


## regularization

- To restrict kernel weight, could use regularization
- $l_1$ and $l_2$ are the most common choices




## references
- [kernel learning by Andrew White](https://dmol.pub/ml/kernel.html)