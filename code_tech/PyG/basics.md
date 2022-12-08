---
title: PyG basics learn
tags: [pyg]
---

## share crystal data format
```Python
from torch_geometric.data import Data
from torch import Tensor
d = Data(x:Tensor,  # atom number, shape (n_nodes,)
		 pos:Tensor,  # atom position, shape (n_nodes, 3)
		 cell:Tensor,  # edge vector, row vec, shape (3,3)
		 edge_indes:Union[Tensor, None]  # edge index, could be None
		 **kwargs)
```
- attrs to `Data`
	- `x, pos, cell`: must have
	- `kwargs`: optional
	- If attrs include labels related to edge, then `edge_index` should be defined
- Naming rules
	- `node_xxx`: related to node, e.g. `node_mass`
	- `edge_xxx`: related to edge, e.g. `edge_distance`
	- `xxx`: no prefix, related to the whole graph, e.g. `mol_id`
	- This is a must, for mini batches and PyG tricks.
- Data type
	- 3D vectors are row vectors, shape `(..., 3)`
	- Except for special cases, should use `torch.Tensor`
		- integer -> `torch.int64`
		- float -> `torch.float64`
		- For iterables, use `list`, don't use `tuple`


## Data Handling of Graphs

- a single graph in PyG is described by an instance of `torch_geometric.data.Data`
	- `data.x` node feature matrix with shape `[num_nodes, per_node_features]`
	- `data.edge_attr` edge feature matrix with shape `[num_edges, per_edge_features]`
	- `data.edge_index` graph connectivity with shape `[2, num_edges]`, type `torch.long`
	- `data.y` target to train against (arb shape)
	- `data.pos` node position matrix with shape `[num_nodes, num_dim]`
	- actually `Data` object is not restricted to these attributes, could invoke any attr
- 