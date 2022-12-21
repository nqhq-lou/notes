---
title: PyG advanced mini-batch
tags: []
---


## could deal with...
- a graph consists of multitype vertexes, and are irrelevant (e.g. no edge connection)
	- multi subgraphs, with private attrs
- a graph consists of multitype vertexes, and are relevant (e.g. edge connection)
	- multipart graphs, with mutual attrs
- a graph consists of global attrs
	- global properties


## main ideas

- `torch_geometric.loader.DataLoader.collate()`
	- inherit from `torch.utils.data.Dataloader` rewriting `collate()`
	- define how a list of examples should be grouped together
	- when mini-batch
		- concat `edge_index` tensor in the second dimension
		- other tensors will just get concated in the first dimension, without any further increment of their values

- `torch_geometric.data.Data.__inc__(), Data.__cat_dim__()`
	- rewrite for your data format and requirements

> **COMMENT**
> `__inc__` will be used in `index` related properties
> so do remember to use `index` where there should be

```Python
def __inc__(self, key, value, *args, **kwargs):
	"""define incremental values"""
    if 'index' in key or 'face' in key:
        return self.num_nodes
    else:
        return 0

def __cat_dim__(self, key, value, *args, **kwargs):
	"""indicate which dimension to concat"""
    if 'index' in key or 'face' in key:
        return 1
    else:
        return 0
```

### example: a `Data` contains multi subgraph

- the subgraphs are irrelevant
	- like no edge connection
- rewrite `__inc__` for batching
```Python
class PairData(Data):
    def __init__(self, edge_index_s=None, x_s=None, edge_index_t=None, x_t=None):
        super().__init__()
        self.edge_index_s = edge_index_s
        self.x_s = x_s
        self.edge_index_t = edge_index_t
        self.x_t = x_t
  
    def __inc__(self, key, value, *args, **kwargs):
        if key == 'edge_index_s':
            return self.x_s.size(0)
        if key == 'edge_index_t':
            return self.x_t.size(0)
        else:
            return super().__inc__(key, value, *args, **kwargs)

edge_index_s = torch.tensor([
    [0, 0, 0, 0],
    [1, 2, 3, 4],
])
x_s = torch.randn(5, 16)  # 5 nodes.
edge_index_t = torch.tensor([
    [0, 0, 0],
    [1, 2, 3],
])
x_t = torch.randn(4, 16)  # 4 nodes.
  
data = PairData(edge_index_s, x_s, edge_index_t, x_t)
data_list = [data] * 10
loader = DataLoader(data_list, batch_size=3)
batch = next(iter(loader))
print(batch)
> PairDataBatch(edge_index_s=[2, 12], x_s=[15, 16], edge_index_t=[2, 9], x_t=[12, 16])
# auto add `Batch` at the __class__.__name__ end

# concat in the correct dimension
print(batch.edge_index_s)
> tensor([[ 0, 0, 0, 0, 5, 5, 5, 5, 10, 10, 10, 10],
> 		[ 1, 2, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14]])

print(batch.edge_index_t)
> tensor([[ 0, 0, 0, 4, 4, 4, 8, 8, 8],
> 		[ 1, 2, 3, 5, 6, 7, 9, 10, 11]])
```

- use `DataLoader(follow_batch=...)` for indicating index
```Python
loader = DataLoader(data_list, batch_size=2, follow_batch=['x_s', 'x_t'])
batch = next(iter(loader))
  
print(batch)
> PairDataBatch(edge_index_s=[2, 12], x_s=[15, 16], x_s_batch=[15], x_s_ptr=[4],
> 			  edge_index_t=[2, 9], x_t=[12, 16], x_t_batch=[12], x_t_ptr=[4])

print(batch.x_s_batch)  # show graph index in batch
> tensor([0, 0, 0, 0, 0, 1, 1, 1, 1, 1])

print(batch.x_s_ptr)  # show slicing in batch
> tensor([ 0, 5, 10, 15])
```

> **COMMENT**
> auto add `Batch` suffix to batch `__class__.__name__`
> `_batch` indicated the graph index in the batch
> `_ptr` indicates the node begin/end pointer number


### example: bipartite graphs

- one graph consists of two or more types of vertexes
	- and there are edges between them
- needs `__inc__` better defined
```Python
from torch_geometric.data import Data
from torch_geometric.loader import DataLoader
  
class BipartiteData(Data):
    def __init__(self, edge_index=None, x_s=None, x_t=None):
        super().__init__()
        self.edge_index = edge_index
        self.x_s = x_s
        self.x_t = x_t
        # self.num_nodes = self.x_s.size(0)
    def __inc__(self, key, value, *args, **kwargs):
        if key == 'edge_index':
            return torch.tensor([[self.x_s.size(0)], [self.x_t.size(0)]])
        else:
            return super().__inc__(key, value, *args, **kwargs)
  
edge_index = torch.tensor([
    [0, 0, 1, 1],
    [0, 1, 1, 2],
])
x_s = torch.randn(2, 16)  # 2 nodes.
x_t = torch.randn(3, 16)  # 3 nodes.
data = BipartiteData(edge_index, x_s, x_t)
data_list = [data]*10
loader = DataLoader(data_list, batch_size=3)
batch = next(iter(loader))
  
print(batch)
> BipartiteDataBatch(edge_index=[2, 12], x_s=[6, 16], x_t=[9, 16], batch=[9], ptr=[4])

print(batch.edge_index)
> tensor([[0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5],  # this addes 2 by each graph
> 		[0, 1, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8]])  # this addes 3 by each graph
```


### example: batching alone new dimensions

- Specifically, a list of attributes of shape `[num_features]` should be returned as `[num_examples, num_features]` rather than `[num_examples * num_features]`
- use `__cat_dim__` by returning `None`
- this is useful for global vars
```Python
from torch_geometric.data import Data
from torch_geometric.loader import DataLoader
  
class MyData(Data):
    def __cat_dim__(self, key, value, *args, **kwargs):
        if key == 'foo':
            return None
        else:
            return super().__cat_dim__(key, value, *args, **kwargs)
  
x = torch.randint(0,1,(3,))
edge_index = torch.tensor([
   [0, 1, 1, 2],
   [1, 0, 2, 1],
])
foo = torch.randn(16)
data = MyData(x=x, edge_index=edge_index, foo=foo)
data_list = [data]*10
loader = DataLoader(data_list, batch_size=3)
batch = next(iter(loader))
  
print(batch)
> MyDataBatch(x=[9], edge_index=[2, 12], foo=[3, 16], batch=[9], ptr=[4])
# foo.shape is [3,16]
```









