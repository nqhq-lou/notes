---
title: graph SE(3) equivariant convolution
tags: [GNN, equivariant, e3nn]
---

- [documentation to **e3nn**](https://docs.e3nn.org/en/latest/guide/change_of_basis.html)

## background

- node features are related to angular quantum number / representation order
- preserve the SE(3) equivariance for MLP
$$
f_{out} = \mathrm{conv}(f_{in}, \{\vec{r}\}_{vertex})
\quad \& \quad \mathrm{rot} \rightarrow \text{spatial rotation}
\quad \& \quad \mathcal{D}_{in}(\mathrm{rot}),
\mathcal{D}_{out}(\mathrm{rot})
$$
- satisfies equivariant
	- where $\mathcal{D}$ acts in this form because of batch shape: `A @ D.T`
$$
\mathcal{D}_{out}
\mathrm{conv}(f_{in}, \{\vec{r}\}_{vertex})
= \mathrm{conv}
(\mathcal{D}_{in} f_{in},
\mathcal{D}_{in} \{\vec{r}\}_{vertex})
$$

## algo details

- tensor product:
	- the tensors interact by certain rules related to [CG coeff](CG_Coefficient_List.jpg)
$$
u^{(l_1)} \otimes v^{(l_2)}
= (u \otimes v)_m^{(l)} = \sum_{m_1+m_2=m}
C_{(l_1,m_1)(l_2,m_2)}^{(l,m)} u_{m_1}^{(l_1)} v_{m_2}^{(l_2)}
$$
- 这里的 $\otimes$ 实际上对应: 规定path下进行的乘法
$$
f'_i = \frac{1}{\sqrt{z}} \sum_{j \in \partial(i)} \; f_j \; \otimes\!(h(\|x_{ij}\|)) \; Y(x_{ij} / \|x_{ij}\|)
$$
- 上式的实际求和过程 (在一定的$l_1 l_2$的情况下, representation order)
	- $w_{uvw} \leftrightarrow (h(\|x_{ij}\|))$, 可以学习的weight, 这里和$\vec{r}$长度相关
	- $Y(\vec{r}/\|r\|) \leftrightarrow (in2)_{vj}$, 根据空间位置进行传播, 带来$\hat{r}$对应的角度的影响
	- $f_j \leftrightarrow (\text{in1})_{ui}$, 需要进行传递的信息
$$
\text{(value of path)}_{wk} =
\dfrac{1}{\sqrt{m_1 m_2}} \sum_{u=1}^{m_1} \sum_{v=1}^{m_2}
\sum_{i=1}^{2l_1+1} \sum_{j=1}^{2l_2+1}
w_{uvw} C_{ijk} (\text{in1})_{ui} (\text{in2})_{vj}
$$
- 简单一些的过程
	- 这个对应下面的例子
$$
\text{(value of path)}_{uk} =
\dfrac{1}{\sqrt{m_1 m_2}} \sum_{v=1}^{m_2}
\sum_{i=1}^{2l_1+1} \sum_{j=1}^{2l_2+1}
w_{uv} C_{ijk} (\text{in1})_{ui} (\text{in2})_{vj}
$$


## code details

### import
```Python
import torch
from torch_cluster import radius_graph
from torch_scatter import scatter
from e3nn import o3, nn
from e3nn.math import soft_one_hot_linspace, soft_unit_step
# import matplotlib.pyplot as plt
# from mpl_toolkits.mplot3d import Axes3D
```

### reps
```Python
irreps_input = o3.Irreps("10x0e + 10x1e")
irreps_output = o3.Irreps("20x0e + 10x1e")
irreps_input.num_irreps, irreps_output.num_irreps  # (20, 30)
# for 10x1 + 10x1, 20x1 + 10x1
irreps_input.dim, irreps_output.dim  # (40, 50)
# 40 = 10x1x1 + 10x1x3, 50 = 20x1x1 + 10x1x3
irreps_input.slices(), irreps_output.slices()
# ([slice(0, 10, None), slice(10, 40, None)],
#  [slice(0, 20, None), slice(20, 50, None)])
```

### generate graph and features
```Python
# create node positions
num_nodes = 100
pos = torch.randn(num_nodes, 3)  # random node positions
# create edges
max_radius = 1.8  # cutoff radius
edge_src, edge_dst = radius_graph(pos, max_radius, max_num_neighbors=num_nodes - 1)
print(edge_src.shape)  # about 3300 edges
edge_vec = pos[edge_dst] - pos[edge_src]
# compute z
num_neighbors = len(edge_src) / num_nodes
num_neighbors  # about 32.9, m_2 above
# plt.hist((pos.unsqueeze(1) - pos).norm(dim=-1).reshape(-1).detach().numpy(), bins=60);
# plt.hist(edge_vec.norm(dim=1).detach().numpy(), bins=20);
```

```Python
f_in = irreps_input.randn(num_nodes, -1)
f_in.shape, f_in.pow(2).mean()  # (100, 40), tensor(1.0053)
# 100 nodes, 40 dim for each node
```

### Azimuthal / Bessel Y
```Python
irreps_sh = o3.Irreps.spherical_harmonics(lmax=2)  # equal to Irreps("0e + 1o + 2e")
print(f"{irreps_sh = }, {irreps_sh.dim = }")
# irreps_sh = 1x0e+1x1o+1x2e, irreps_sh.dim = 9
sh = o3.spherical_harmonics(irreps_sh, edge_vec, normalize=True, normalization='component')
# # normalize=True ensure that x is divided by |x| before computing the sh
sh.pow(2).mean(), sh.shape  # (tensor(1.), torch.Size([3290, 9]))
```

### define path
```Python
tp = o3.FullyConnectedTensorProduct(irreps_input, irreps_sh, irreps_output, shared_weights=False)
print(f"{tp} needs {tp.weight_numel} weights")
# FullyConnectedTensorProduct(10x0e+10x1e x 1x0e+1x1o+1x2e -> 20x0e+10x1e | 400 paths | 400 weights) needs 400 weights
# 400 = 10*20*1 # 10x0e & 1x0e -> 20x0e, 1 is from 0++0==0, 1 method
#     + 10*10*1 # 10x1e & 1x0e -> 10x1e, 1 is from 1++0==1, 1 method
#     + 10*10*1 # 10x1e & 1x2e -> 10x1e, 1 is from 1++2==1, 1 method
tp.visualize();
```
![path|300](https://docs.e3nn.org/en/stable/_images/convolution_6_1.png)

### radius embedding
```Python
"""check embedding method"""
num_basis = 10
x = torch.linspace(0.0, 1.05*max_radius, 1000)
y = soft_one_hot_linspace(
    x,
    start=0.0,
    end=max_radius,
    number=num_basis,
    basis='smooth_finite',
    cutoff=True,
)
plt.plot(x, y);
```
![soft_one_hot_linspace|300](https://docs.e3nn.org/en/stable/_images/convolution_7_0.png)

```Python
num_basis = 10
edge_length_embedding = soft_one_hot_linspace(
    edge_vec.norm(dim=1),
    start=0.0,
    end=max_radius,
    number=num_basis,
    basis='smooth_finite',
    cutoff=True,
)
edge_length_embedding = edge_length_embedding.mul(num_basis**0.5)
print(edge_length_embedding.shape)  # torch.Size([3290, 10]), connection and num_basis
edge_length_embedding.pow(2).mean()  # tensor(0.9002), the second moment
```

```Python
fc = nn.FullyConnectedNet([num_basis, 16, tp.weight_numel], torch.relu)
weight = fc(edge_length_embedding)  # this is the radius embedding

print(f"{edge_length_embedding.shape=}")
# edge_length_embedding.shape=torch.Size([3290, 10])
print(f"{weight.shape=}, {len(edge_src)=}, {tp.weight_numel=}")
# weight.shape=torch.Size([3290, 400]), len(edge_src)=3290, tp.weight_numel=400
# For a proper notmalization, the weights also need to be mean 0
print(weight.mean(), weight.std())  # should close to 0 and 1
# tensor(-0.0164, grad_fn=<MeanBackward0>) tensor(0.9049, grad_fn=<StdBackward0>)
```

### do message passing
- 之后gather就好了
```Python
summand = tp(f_in[edge_src], sh, weight)  # features, azimuthal, radial
print(f"{f_in[edge_src].shape=}, {sh.shape=}, {weight.shape=}")
# f_in[edge_src].shape=torch.Size([3290, 40]), sh.shape=torch.Size([3290, 9]), weight.shape=torch.Size([3290, 400])
print(f"{summand.shape=}, {summand.pow(2).mean()=}")
# summand.shape=torch.Size([3290, 50]), summand.pow(2).mean()=tensor(0.8107, grad_fn=<MeanBackward0>)
```

## compact version

```Python
def conv(f_in, pos):
    edge_src, edge_dst = radius_graph(pos, max_radius, max_num_neighbors=len(pos) - 1)
    edge_vec = pos[edge_dst] - pos[edge_src]
    sh = o3.spherical_harmonics(irreps_sh, edge_vec, normalize=True, normalization='component')
    emb = soft_one_hot_linspace(edge_vec.norm(dim=1), 0.0, max_radius, num_basis, basis='smooth_finite', cutoff=True).mul(num_basis**0.5)
    return scatter(tp(f_in[edge_src], sh, fc(emb)), edge_dst, dim=0, dim_size=num_nodes).div(num_neighbors**0.5)



import time
wall = time.perf_counter()

edge_src, edge_dst = radius_graph(pos, max_radius, max_num_neighbors=len(pos) - 1)
edge_vec = pos[edge_dst] - pos[edge_src]
print(time.perf_counter() - wall); wall = time.perf_counter()

sh = o3.spherical_harmonics(irreps_sh, edge_vec, normalize=True, normalization='component')
print(time.perf_counter() - wall); wall = time.perf_counter()

# much time
emb = soft_one_hot_linspace(edge_vec.norm(dim=1), 0.0, max_radius, num_basis, basis='smooth_finite', cutoff=True).mul(num_basis**0.5)
print(time.perf_counter() - wall); wall = time.perf_counter()

weight = fc(emb)
print(time.perf_counter() - wall); wall = time.perf_counter()

# much time
summand = tp(f_in[edge_src], sh, weight)
print(time.perf_counter() - wall); wall = time.perf_counter()

ret = scatter(summand, edge_dst, dim=0, dim_size=num_nodes).div(num_neighbors**0.5)
print(time.perf_counter() - wall); wall = time.perf_counter()
ret.shape  # torch.Size([100, 50]), 100 points, 50 rep.dim


# 0.0010225046426057816
# 0.0008919439278542995
# 0.0015640142373740673  # embedding
# 0.0013153678737580776
# 0.0015995614230632782  # summand
# 0.0004855673760175705
```

