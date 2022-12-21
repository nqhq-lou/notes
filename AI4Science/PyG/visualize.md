---
title: Visualize PyG graph with networkx
tags: [PyG]
---



![networkx graph class|500](https://pic4.zhimg.com/80/v2-fe91a708fffea87d427273bf7a70ec7b_1440w.webp)

```Python
import torch
import torch_geometric as tg
import networkx as nx
import matplotlib.pyplot as plt
from torch_geometric.data import Data


def plot_graph(data:Data, circular_layout:bool=True, figsize=(2,2)) -> nx.DiGraph:
    g = nx.DiGraph()
    edge_index = data.edge_index.T.detach().cpu().numpy()
    g.add_edges_from(edge_index)
    plt.figure(figsize=figsize)
    if circular_layout:
        nx.draw(g, pos=nx.circular_layout(g), with_labels=True)
    else:
        nx.draw(g, with_labels=True)
    return g

edge_index = torch.tensor([[0, 1, 1, 2],
                           [1, 0, 2, 1]], dtype=torch.long)
x = torch.tensor([[-1], [0], [1]], dtype=torch.float)
data = Data(x=x, edge_index=edge_index)
plot_graph(data);
```




## reference
- [基于networkx实现图可视化](https://zhuanlan.zhihu.com/p/457578483)
- [networks tutorials](https://networkx.org/documentation/stable/tutorial.html)


