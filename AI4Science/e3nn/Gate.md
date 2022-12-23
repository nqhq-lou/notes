---
title: gate conv
tags: [e3nn]
---

## `e3nn.nn.Activation`
- for `l=0` scalars
- the activation is self-defined, but will be normalized to `N(0,1)`
	- see `e3nn.math.normalize2mom`, it is used in `Activation.__init__`

- basic test
```Python
import torch
import torch.nn as nn
from e3nn import o3
import e3nn.nn as enn

ir = o3.Irreps('3x0e')
ir_vec = torch.randn(ir.dim)
print(f"{ir.dim=}, {ir.num_irreps=}, {ir_vec.shape=}")
# ir.dim=3, ir.num_irreps=3, ir_vec.shape=torch.Size([3])
print(ir_vec)
# tensor([-0.7791, 1.1621, 0.1969])
act_func = nn.ELU()
act = enn.Activation(ir, [act_func] * len(ir))
print(act.irreps_out)
# 3x0e
print(act(ir_vec), act_func(ir_vec), act(ir_vec) / act_func(ir_vec))
# tensor([-0.6747, 1.4489, 0.2454]) tensor([-0.5412, 1.1621, 0.1969]) tensor([1.2468, 1.2468, 1.2468])
```



## `e3nn.nn.Gate`