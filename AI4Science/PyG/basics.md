---
title: PyG basics learn
tags: [pyg]
---

## share crystal data format
- for the latest conventions, see [data conventions](https://gitlab.pjlab.org.cn/hugengyuan/atom-graph-database/-/blob/main/docs/Data_convention.md)
```Python
from torch_geometric.data import Data
from torch import Tensor
d = Data(x:Tensor,  # atom number, shape (n_nodes, 1)
		 pos:Tensor,  # atom position, shape (n_nodes, 3)
		 cell:Tensor,  # edge vector, row vec, shape (3,3)
		 edge_indes:Union[Tensor, None]  # edge index, could be None
		 **kwargs)
```
- attrs to `Data`
	- `x, pos, cell`: must have
		- `x` shape is `(n_nodes, 1)`. Actually it is for the convenience for later data concat.
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
- Exceptional large data entry
	- should establish a new dataset and upload it to the Ceph
	- e.g. quad grid values


## Data stuffs

### Data Handling of Graphs
- a single graph in PyG is described by an instance of `torch_geometric.data.Data`
	- `data.x` node feature matrix with shape `[num_nodes, per_node_features]`
	- `data.edge_attr` edge feature matrix with shape `[num_edges, per_edge_features]`
	- `data.edge_index` graph connectivity with shape `[2, num_edges]`, type `torch.long`
		- edge arrow from row 0 to row 1
	- `data.y` target to train against (arb shape)
	- `data.pos` node position matrix with shape `[num_nodes, num_dim]`
	- actually `Data` object is not restricted to these attributes, could invoke any attr
```Python
edge_index = torch.tensor([[0, 0, 1, 1, 2],
                           [0, 1, 0, 2, 1]], dtype=torch.long)
x = torch.tensor([[-1], [0], [1]], dtype=torch.float)
y = torch.tensor([1], dtype=torch.long)
data = Data(x=x, y=y, edge_index=edge_index)
data.validate(raise_on_error=True)  # check exceed node number in edges
data.num_nodes  # 3
data.num_edges  # 5
data.num_node_features  # 1
data.has_isolated_nodes()  # False
data.has_self_loops()  # True
data.is_directed()  # False
```


### Dataset
- basic dataset
```Python
from torch_geometric.datasets import TUDataset
dataset = TUDataset(root='/home/louzekun/pyg/data/ENZYMES', name='ENZYMES')
dataset  # ENZEYMES(600), dataset.name = ENZEYMES
dataset.num_classes  # 6, correspond to the possible y values in the dataset
dataset.num_node_features  # 3, correspond to the x values shape in the dataset
dataset[:540]  # ENZYMES(540)
dataset.shuffle()  # ENZYMES(600), shuffled, object returned
```


### MiniBatches
- PyG achieves parallelization over a mini-batch by creating sparse block diagonal adjacency matrices
- PyG contains its own [`torch_geometric.loader.DataLoader`](https://pytorch-geometric.readthedocs.io/en/latest/modules/loader.html#torch_geometric.loader.DataLoader "torch_geometric.loader.DataLoader"), which already takes care of this concatenation process.
```Python
dataset = TUDataset(root='/home/louzekun/pyg/data/ENZYMES', name='ENZYMES')
loader = DataLoader(dataset, batch_size=32, shuffle=True)
for idx, batch in enumerate(loader):
	print(batch)
	# DataBatch(edge_index=[2, 3992], x=[1065, 3], y=[32], batch=[1065], ptr=[33]) 32
```


### Transform
```Python
from torch_geometric.datasets import ShapeNet
dataset = ShapeNet(root='/home/louzekun/pyg/data/ShapeNet', categories=['Airplane'])
len(dataset), dataset[0]
# (2349, Data(x=[2518, 3], y=[2518], pos=[2518, 3], category=[1]))

import torch_geometric.transforms as T
from torch_geometric.datasets import ShapeNet
dataset = ShapeNet(root='/home/louzekun/pyg/data/ShapeNet', categories=['Airplane'],
                   pre_transform=T.KNNGraph(k=6))
dataset[0]  # Data(x=[2518, 3], y=[2518], pos=[2518, 3], category=[1])
```


### other functions
```Python
from torch_geometric.utils import add_self_loops, degree

add_self_loops(
	torch.tensor([[0,1,2,3],[1,0,3,2]], dtype=torch.long),
	num_nodes=5,
	edge_attr=torch.randn(4, 2),
	fill_value=0)
> (tensor([[0, 1, 2, 3, 0, 1, 2, 3, 4], [1, 0, 3, 2, 0, 1, 2, 3, 4]]),
> tensor([[ 0.9906, 0.2766], [-0.2558, -0.2515], [ 0.1514, 1.1928], [ 1.0415, 0.2221], [ 0.0000, 0.0000], [ 0.0000, 0.0000], [ 0.0000, 0.0000], [ 0.0000, 0.0000], [ 0.0000, 0.0000]]))

degree(edge_index[2], x.size(0), dtype=x.dtype)


```



## Message Passing

$$
\mathbf{x}_i^{(k)} = \gamma^{(k)} \left( \mathbf{x}_i^{(k-1)}, \square_{j \in \mathcal{N}(i)} \, \phi^{(k)}\left(\mathbf{x}_i^{(k-1)}, \mathbf{x}_j^{(k-1)},\mathbf{e}_{j,i}\right) \right),
$$
- $\square$ denotes a differentiable, permutation invariant function, like sum, mean, max
- $\gamma, \phi$ denotes differentiable functions like MLP
- $i, j$ presents main node and neighboring nodes respectively


### `MessagePassing`

- helps in creating such kinds of message passing graph neural networks by automatically taking care of message propagation
- use only has to define the function $\phi$ `message()`, $\gamma$ `update()`, and aggregation scheme (`aggr=Union["add", "mean", "max"]`)

- methods you could define before use (raise NotImplementedError)
	- `message_and aggregate()`
	- `edge_update()`
- methods used, but not explicitly defined (like return the inputs)
	- `update()`
	- `message()`



## simple GCN

$$
\mathbf{x}_i^{(k)} = \sum_{j \in \mathcal{N}(i) \cup \{ i \}} \frac{1}{\sqrt{\deg(i)} \cdot \sqrt{\deg(j)}} \cdot \left( \mathbf{W}^{\top} \cdot \mathbf{x}_j^{(k-1)} \right) + \mathbf{b},
$$

1.  Add self-loops to the adjacency matrix. ($j$ could be $i$)
2.  Linearly transform node feature matrix.
3.  Compute normalization coefficients.
4.  Normalize node features in $\phi$.
5.  Sum up neighboring node features (`"add"` aggregation).
6.  Apply a final bias vector.

Usually complete step 1-3 before message passing.
Do step 4-6 in message passing

```Python
class GCNConv(MessagePassing):
    def __init__(self, in_channels, out_channels):
        super().__init__(aggr='add')
        self.lin = nn.Linear(in_channels, out_channels, bias=False)
        self.bias = nn.ParameterDict(torch.Tensor(out_channels))
        self.reset_parameters()
  
    def reset_parameters(self):
        self.lin.reset_parameters()
        self.bias.data.zero_()
  
    def message(self, x_j, norm):  # if you use x_i, then it means the main node
        # x_j, shape (edge_num, out_channels)
        # step 4: normalize node features
        out = norm.view(-1, 1) * x_j
        return out
  
    def forward(self, x, edge_index):
        """x: shape (N, in_channels)
        edge_index: shape (2, edge_num)"""
        # step 1: Add self-loops to the adjacencey matrix.
        edge_index, _ = add_self_loops(edge_index, num_nodes=x.size(0))
        # step 2: Linearly transform node feature matrix.
        x = self.lin(x)
        # step 3: Compute normalization
        row, col = edge_index
        deg = degree(col, x.size(0), dtype=x.dtype)
        deg_inv_sqrt = deg.pow(-0.5)
        deg_inv_sqrt[deg_inv_sqrt == float('inf')] = 0  # change the self loop values to 0
        norm = deg_inv_sqrt[row] * deg_inv_sqrt[col]  # for all the edges
        # step 4-5: start propagating messages.
        out = self.propagate(edge_index, x=x, norm=norm)
        # step 6: Apply a final bias vector
        out = out + self.bias
        return out

def _test():
	edge_index = torch.tensor([[0, 1, 1, 2],
	                           [1, 0, 2, 1]], dtype=torch.long)
	x = torch.randn(3, 16, dtype=torch.float64)
	y = torch.tensor([1], dtype=torch.long)
	data = Data(x=x, y=y, edge_index=edge_index)
	data, data.validate(raise_on_error=True)  # check exceed node number in edges
	m = GCNConv(16,32).to(dtype=torch.float64)
	m(data.x, data.edge_index).shape  # torch.Size([3, 32])
```

- When call `propagate()`, automatically call `message()`, `aggregate()`, `update()`
- In the `message()` function, we need to normalize the neighboring node features `x_j` by `norm`.
	- Here, `x_j` denotes a _lifted_ tensor, which contains the source node features of each edge, _i.e._, the neighbors of each node.
	- Node features can be automatically lifted by appending `_i` or `_j` to the variable name.
	- In fact, any tensor can be converted this way, as long as they hold source or destination node features.

