# Knapsack Problem Model

* Given a set of $n$ items and a integer capacity $W$ of a knapsack
* Each item $i$ has a weight $w_i$ and a value $v_i$
* The goal is to determine the subset of items to include in the knapsack such that the total weight does not exceed $W$ and the total value is maximized

## Data Model:

* $n$: number of items
* $W$: capacity of the knapsack
* $w_i$: weight of item $i$ for $i = 1, 2, \ldots, n$
* $v_i$: value of item $i$ for $i = 1, 2, \ldots, n$


## 1. Decision Variables $(x_i)$

$$
\begin{cases}
x_i = 1 & \text{if item } i \text{ is included in the knapsack} \\
x_i = 0 & \text{otherwise}
\end{cases}
$$


## 2. Objective Function

$$
\max Z = \sum_{i=1}^{n} v_i x_i
$$

## 3. Constraints

$$
\sum_{i=1}^{n} w_i x_i \leq W
$$

$$
x_i \in \{0, 1\}, \quad \forall i = 1, 2, \ldots, n
$$