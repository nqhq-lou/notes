---
title: PyG basics learn
tags: [pyg]
---


## Data Handling of Graphs

- a single graph in PyG is described by an instance of `torch_geometric.data.Data`
	- `data.x` node feature matrix with shape `[num_nodes, per_node_features]`
	- `data.edge_attr` edge feature matrix with shape `[num_edges, per_edge_features]`
	- `data.edge_index` graph connectivity with shape `[2, num_edges]`, type `torch.long`
	- `data.y` target to train against (arb shape)
	- `data.pos` node position matrix with shape `[num_nodes, num_dim]`
	- actually `Data` object is not restricted to these attributes, could invoke any attr
- 