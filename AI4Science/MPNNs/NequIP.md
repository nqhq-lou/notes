---
title: notes on NequIO
tags: []
---



## intro





## networks details


![networks](https://media.springernature.com/full/springer-static/image/art%3A10.1038%2Fs41467-022-29939-5/MediaObjects/41467_2022_29939_Fig1_HTML.png?as=webp)

- Convolutional filter
	- $R(r_{ij})$ embed interatomic distance
	- $\sigma$ for `SiLU`
	- $B(r_{ij})$ init $b=[1,2,...,N_b]$, optim $b$ with BP
$$
\begin{aligned}
S_m^{(l)} (\vec{r}_{ij}) = \ & R(r_{ij}) Y_m^{(l)}(\hat{r}_{ij}) \\
R(r_{ij}) = \ & W_n \sigma(\ldots \sigma(W_2 \sigma(W_1 B(r_{ij})))) \\
B(r_{ij}) = \ & \dfrac{2}{r_c} \dfrac{\sin (\frac{b\pi}{r_c} r_{ij})}{r_{ij}} f_{env} (r_{ij}, r_c) \\
\end{aligned}
$$
- tensor product and convolution: see [[SE(3)convolution]]
- 


## ref

- [NequIP - GitHub](https://github.com/mir-group/nequip)
- [the article](https://www.nature.com/articles/s41467-022-29939-5)
- tensor product
	- Nathaniel Thomas et al., “Tensor Field Networks: Rotation- and Translation-Equivariant Neural Networks for 3D Point Clouds” (arXiv, May 18, 2018), [http://arxiv.org/abs/1802.08219](http://arxiv.org/abs/1802.08219).