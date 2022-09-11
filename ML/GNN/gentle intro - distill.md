---
title: summary on gentle intro to GNN, distill
tags: [ML/GNN/intro]
---


## origin
- A set of objects together with the connections between them are naturally expressed as a graph.
- 


First, we look at what kind of data is most naturally phrased as a graph, and some common examples.

Second, we explore what makes graphs different from other types of data, and some of the specialized choices we have to make when using graphs.

Third, we build a modern GNN, walking through each of the parts of the model, starting with historic modeling innovations in the field.


## graph

### basics
- consists of vertex, edge, global
	- all attributes in the graph are expressed as scalars
	- edge: undirected/directed edge

### xxx as graph

#### image
- specify properties: set edge to neighbors
- eight neighbors in total for one pixel
- the relationship could be presented by adjacency matrix

#### text
- specify properties: set directed edge by sequence to the words
- off-diagonal line-shape adjacency matrix found

#### molecules
- nodes are atoms and edges are covalent bonds

#### social networks
- nodes are individuals and edges are relationships
- the data could be from image context or text.


## problems involves graph structure data

- Three cates, all of them are about prediction.
- All of the three problems are covered by GNN model class.


### graph-level
- In a graph-level task, we predict a single property for a whole graph.
- e.g. molecule smell or its protein receptor, associate a label to an entire graph, identify the mood or emotion of an entire sentence at once.
- Similar to image labelling.

### node-level
- For a node-level task, we predict some property for each node in a graph.
- e.g. predicting identity or role of each node within a graph (like interpersonal relationship graph)
- e.g. predicting parts-of-speech of each word in a sentence.
- Similar to image segmentation.

### edge-level
- For an edge-level task, we want to predict the property or presence of edges in a graph.
- e.g. predict image segmentations relationships.


## challenges of using graphs in ML

### presentation of graph in NN
- Graphs have up to four types of information that we will potentially want to use to make predictions: nodes, edges, global-context and connectivity
- Connectivity presented by adjacency matrix is not permutation invariant.
- Use sparse matrix to present the connection.

## GNN
- **A GNN is an optimizable transformation on all attributes of the graph (nodes, edges, global-context) that preserves graph symmetries (permutation invariances).**
- build GNNs using the “message passing neural network” framework proposed by Gilmer et al
	- adopt a “graph-in, graph-out” architecture
	- meaning that these model types accept a graph as input, with information loaded into its nodes, edges and global-context
	- progressively transform these embeddings, without changing the connectivity of the input graph


### simple GNN with pooling information
- The embeddings from edge/node should interact with node/edge
	- We could use pooling trick
	1. For each item to be pooled, gather each of their embeddings and concatenate them into a matrix
	2. The gathered embeddings are then aggregated, usually via a sum operation.
- In this way, all nodes and edges messages are aggregated.
- Later just send the vectors in nodes and edges into MLPs for value updating.
- If we have new graph attributes, we just have to define how to pass information from one attribute to another.

- In this simplest GNN formulation, we’re **not using the connectivity of the graph** at all **inside the GNN layer**. We just use connectivity when pooling information for prediction.
- Each node is processed independently, as is each edge, as well as the global context. We only use connectivity when pooling information for prediction.
![[gentle intro - distill_fig1.png|500]]


### passing messages between parts of the graph
- We could make use of connectivity inside the GNN layer for more sophisticated predictions.
	- use message passing, where neighboring nodes or edges exchange information and influence each other's updated embeddings.
	1. For each node in the graph, *gather* all the neighboring node embeddings (or messages), which is the $g$ function described above.
	2. Aggregate all messages via an aggregate function (like sum).
	3. All pooled messages are passed through an _update function_, usually a learned neural network.
- As for edges, just pass the message via nodes.
- This procedure is more like a convolution: utilize all the neighboring messages for updating.
![[gentle intro - distill_fig2.png|500]]


### learning from edge/vertex to vertex/edge
- For vertexes, we could pool the message from neighboring edges, and use it as a new message.
	- The same is true for edges.
- Something to note is that the embedding/message of node and edge stored in a graph are not necessarily the same size or shape. This bring about difficulties when combining them.
	- Learn a linear mapping from the space of edges to the space of nodes, and vice versa.
	- Or we could just concatenate them together before the update MLP function.

![[gentle intro - distill_fig3.png|500]]
- Up to here, the updating sequence should be considered.
	- This is a fashionable question.
	- For example we could update in `weave` fashion where we have four updated representations that get combined into new node and edge representations.


### adding global presentations
- Without environment, nodes far apart from each other may never be able to efficiently transfer information.
- One solution is that connect all nodes, which enable them to pass messages to any nodes.
	- But this adds to the computation cost.
- The other solution is called **master node** or **context vector**.
	- A global context vector is connected to all other nodes and edges in the network
	- The global context vector act as a bridge between them to pass messages.
	- Below is one possible setting under such assumptions.
![[gentel intro - distill_fig4.png]]


### sum up
- The key is to leverage all the useful information in the graph.
	- For nodes, consider information from neighboring nodes, connected edges and the global information.



## empirical GNN design lessons
- Below are based on pungent dataset in distill article.
- Parameter number
	- Higher number of parameters does correlate with higher performance.
	- GNN is parameter-efficient: small number of parameters are able to achieve high accuracy.
- Layers
	- Deeper MLP may not lead to better results
	- GNN with a higher number of layers will broadcast information at a higher distance
	- and can risk having their node representations ‘diluted’ from many successive iterations
- Aggregation
	- Sum performs a little little bit better.
	- While max and mean could be equally good
- Message passing
	- The more graph attributes are communicating, the better the performance of the average model.
	- Node embeddings and global embeddings are more useful than edge embeddings

- Increasing the performance of GNN in two ways
	- Adopt more sophisticated graph algorithms
	- Adopt better graph network design.


## other weeds

not read yet



## references
- [A Gentle Introduction to Graph Neural Networks - distill](https://distill.pub/2021/gnn-intro/)
- d