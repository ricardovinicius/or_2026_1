# Max Flow Problem Model

*   A natural gas producer *s* needs to send the maximum amount of gas to factory *t* through pipelines.
*   Each pipeline *ij* is directed (gas passes only in one direction) and has an associated capacity.

#### Graph Representation (Mermaid)

```mermaid
graph LR
    %% Define nodes
    s((s))
    t((t))
    v1((v1))
    v2((v2))
    v3((v3))
    v4((v4))
    v5((v5))
    v6((v6))

    %% Connections from source 's'
    s -- 5 --> v1
    s -- 4 --> v2
    s -- 6 --> v3

    %% Vertical connections in first column (downwards)
    v1 -- 4 --> v2
    v2 -- 3 --> v3

    %% Connections between columns
    v1 -- 6 --> v4
    v1 -- 5 --> v5
    v2 -- 4 --> v5
    v3 -- 6 --> v5
    v3 -- 5 --> v6

    %% Vertical connections in second column (upwards)
    v5 -- 5 --> v4
    v6 -- 7 --> v5

    %% Connections to sink 't'
    v4 -- 5 --> t
    v5 -- 3 --> t
    v6 -- 6 --> t
```

## 1. Decision Variables $(x_j)$

$$
x_{ij} = \text{flow of gas from node } i \text{ to node } j \quad \forall (i, j) \in A
$$

## 2. Objective Function

$$
\max \sum_{i \in N(t)} x_{i,t} \quad \text{(maximize flow from source 's' to sink 't')}
$$

## 3. Constraints

1. Non-negativity: $x_{ij} \geq 0 \quad \forall (i, j) \in A$

2. Capacity constraints: $x_{ij} \leq u_{ij} \quad \forall (i, j) \in A$

3. Flow conservation: 

$$
\sum_{j} x_{ij} = \sum_{j} x_{ji} \quad \forall i \in V \setminus \{s, t\} \\

(\text{flow into node } i \text{ equals flow out of node } i)
$$

