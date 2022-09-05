---
title: summary on gentle intro to GNN, distill
tags: [GNN/intro]
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

### image as graph
- specify properties: set edge to neighbors
- eight neighbors in total for one pixel
- the relationship could be presented by adjacency matrix

### text as graph
- specify properties: set directed edge by sequence to the words
- off-diagonal line-shape adjacency matrix found

### graph-valued data in the wild






## references
- [A Gentle Introduction to Graph Neural Networks - distill](https://distill.pub/2021/gnn-intro/)
- d