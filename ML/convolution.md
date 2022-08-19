---
title: convolution layer
tags: [ML/convolution]
---


## convolution

- $(N, C_{in}, L_{in}) \rightarrow (N, C_{out}, L_{out})$
- 输出长度计算
$$L_{out} = Floor\left[
	\dfrac{L_{in} + 2 \times padding
		- dilation \times (kernel\_size - 1) - 1}{stride}
	\right] + 1$$
- [Conv1d from PyTorch](https://pytorch.org/docs/stable/generated/torch.nn.Conv1d.html)
	- `dilation`用于扩大视野



## deconvolution

- $(N, C_{in}, L_{in}) \rightarrow (N, C_{out}, L_{out})$
- 输出长度计算
$$L_{out} = stride \times (L_{in}-1) - 2 \times padding + dilation \times (kernel\_size - 1) + output\_padding + 1$$




- [ConvTranspose1d from PyTorch](https://pytorch.org/docs/stable/generated/torch.nn.ConvTranspose1d.html)



