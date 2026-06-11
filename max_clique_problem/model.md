# Maximum Clique Problem Model

* Given an undirected graph $G = (V, E)$, where $V$ is the set of vertices and $E$ is the set of edges, the maximum clique problem aims to find the largest subset of vertices such that every two vertices in the subset are connected by an edge.
* Or formally, we want to find a subset of vertices $C \subseteq V$ such that for every pair of vertices $u, v \in C$, there is an edge $(u, v) \in E$, and the size of $C$ is maximized.
* Or in other words, we want to find the largest complete subgraph of $G$.

## Data Model:

* Let $G = (V, E)$ be an undirected graph, where $V$ is the set of vertices and $E$ is the set of edges.
* Let $n = |V|$ be the number of vertices in the graph.
* Let $m = |E|$ be the number of edges in the graph.
* Let $A$ be the adjacency matrix of the graph, where $A_{ij} = 1$ if there is an edge between vertices $i$ and $j$, and $A_{ij} = 0$ otherwise.
* Let $x_j$ be a binary decision variable that indicates whether vertex $j$ is included in the clique (1) or not (0).


## 1. Decision Variables $(x_j)$

$$
x_j = \begin{cases}
1 & \text{if vertex } j \text{ is included in the clique} \\
0 & \text{otherwise}
\end{cases}
$$

## 2. Objective Function

The objective is to maximize the size of the clique, which can be expressed as:

$$
\text{Maximize} \quad \sum_{j=1}^{n} x_j
$$

## 3. Constraints

To ensure that the selected vertices form a clique, we need to add constraints that enforce that if two vertices are both included in the clique, there must be an edge between them. This can be expressed as:

$$
x_i + x_j \leq 1 + A_{ij} \quad \forall i, j \in V, i < j
$$

* Domain Constraints:

$$
x_j \in \{0, 1\} \quad \forall j \in V
$$

