# Facilities Problem Model

* Given a set of $N$ potential facility locations and a set of $M$ customers
* Each facility has a fixed cost of opening $f_i$
* Each customer has a cost of being served by a facility $c_{ij}$, where $i$ is the facility and $j$ is the customer
* The goal is to minimize the total cost of opening facilities and serving customers

## Data Model:

* $N$: Number of potential facility locations
* $M$: Number of customers
* $f_i$: Fixed cost of opening facility $i$
* $c_{ij}$: Cost of serving customer $j$ from facility $i$ 

## 1. Decision Variables $(x_i)$

$$x_i = \begin{cases}
1 & \text{if facility } i \text{ is opened} \\
0 & \text{otherwise}
\end{cases}$$

$$y_{ij} = \begin{cases}
1 & \text{if customer } j \text{ is served by facility } i \\
0 & \text{otherwise}
\end{cases}$$

## 2. Objective Function

$$\min Z = \sum_{i=1}^{N} f_i x_i + \sum_{i=1}^{N} \sum_{j=1}^{M} c_{ij} y_{ij}$$

## 3. Constraints

1. Each customer must be served by exactly one facility:

$$\sum_{i=1}^{N} y_{ij} = 1 \quad \forall j = 1, 2, ..., M$$

2. A customer can only be served by an open facility:

$$
y_{ij} \leq x_i \quad \forall i = 1, 2, ..., N; \forall j = 1, 2, ..., M
$$

3. Binary domain constraints on decision variables:

$$x_i \in \{0, 1\} \quad \forall i = 1, 2, ..., N$$
$$
y_{ij} \in \{0, 1\} \quad \forall i = 1, 2, ..., N; \forall j = 1, 2, ..., M
$$ 

