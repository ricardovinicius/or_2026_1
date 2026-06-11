# Frequency Assignment Problem Model

* When the signal of two transmitters interfere with each other, they cannot be assigned the same frequency. 
* The goal of the frequency assignment problem is to assign frequencies to a set of transmitters such that the total number of frequencies used is minimized, while ensuring that no two interfering transmitters are assigned the same frequency.

This is basically a graph coloring problem, where the transmitters are represented as vertices in a graph, and edges represent interference between transmitters. The objective is to color the graph with the minimum number of colors (frequencies) such that no two adjacent vertices (interfering transmitters) share the same color (frequency).

## Data Model:

* Let $T$ be the set of transmitters
* Let $I$ be the set of pairs of transmitters that interfere with each other, i.e., $I = \{(i, j) | i, j \in T, i \neq j, \text{ and } i \text{ interferes with } j\}$.
* Let $K$ as the maximum number of frequencies available. Which can be set to $|T|$ in the worst case, since each transmitter could potentially require a unique frequency.


## 1. Decision Variables $(x_i)$

$$
y_k = \begin{cases}
1 & \text{if frequency } k \text{ is used} \\
0 & \text{otherwise}
\end{cases}
$$

$$
x_{ik} = \begin{cases}
1 & \text{if transmitter } i \text{ is assigned frequency } k \\
0 & \text{otherwise}
\end{cases}
$$

## 2. Objective Function

Minimize the total number of frequencies used:

$$
\text{Minimize} \quad \sum_{k=1}^{K} y_k
$$

## 3. Constraints

1. Each transmitter must be assigned exactly one frequency:

$$
\sum_{k=1}^{K} x_{ik} = 1 \quad \forall i \in T
$$

2. If two transmitters interfere with each other, they cannot be assigned the same frequency:

$$
x_{ik} + x_{jk} \leq y_k \quad \forall (i, j) \in I, \forall k = 1, 2, ..., K
$$

3. A frequency $k$ can only be assigned to a transmitter if it is marked as used:

$$
x_{ik} \leq y_k \quad \forall i \in T, \forall k = 1, 2, ..., K
$$

4. Domain constraints for decision variables:

$$
y_k \in \{0, 1\} \quad \forall k = 1, 2, ..., K
$$

$$
x_{ik} \in \{0, 1\} \quad \forall i \in T, \forall k = 1, 2, ..., K
$$


