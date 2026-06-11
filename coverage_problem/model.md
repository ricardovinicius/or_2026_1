# Coverage Problem Model

* The government is planning to build schools in a way to satisfy the demand in a city.
* Is not known how many schools are needed, but the law requires that every district must have a school, or be neighboring to a district with a school.
* What districts should be selected to build schools in order to minimize the total number of building schools? 

## Data Model:

This problem can be represented as a graph, where:
* Each district is represented as a vertex (node) in the graph.
* An edge exists between two vertices if the corresponding districts are neighboring.

We can represent the graph using an adjacency matrix $A$, where $A_{ij} = 1$ if district $i$ is neighboring to district $j$, and $A_{ij} = 0$ otherwise.

## 1. Decision Variables $(x_j)$

$$
\begin{cases}
x_j = 1 & \text{if a school is built in district } j \\
x_j = 0 & \text{otherwise}
\end{cases}
$$

## 2. Objective Function

Minimize the total number of schools built:

$$
\min Z = \sum_{j=1}^{n} x_j 
$$

## 3. Constraints

Each district must have a school, or be neighboring to a district with a school:

$$
\sum_{j \in N(i)} x_j \geq 1, \quad \forall i = 1, 2, \ldots, n
$$

where $N(i)$ denotes the set of closed (including itself) neighboring districts to district $i$.

* Domain constraints:

$$
x_j \in \{0, 1\}, \quad \forall j = 1, 2, \ldots, n
$$
