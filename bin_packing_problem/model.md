# Bin Packing Problem Model

* The Bin Packing (BP) is a classic combinatorial optimization and computing theory problem, of the NP-hard class. 
* The problem consists of distributing a set of items into a finite number of bins, each with a certain capacity, in a way that minimizes the number of bins used or maximizes the total value of the items packed, depending on the specific variant of the problem.

## Data Model:

Input: 
* $n$: number of items
* $U$: set of items, $U = \{1, 2, ..., n\}$
* $w_u$: weight of item $u$, for all $u \in U$, $0 \leq w_u \leq 1$

Objective:
* Find a partition of the set $U$ into $k$ subsets (bins) $U_1, U_2, \ldots, U_k$ such that the total weight of items in each bin $U_i$ does not exceed 1, and the number of bins $k$ used is minimized.


## 1. Decision Variables $(x_i)$

$$
x_i = \begin{cases}
1 & \text{if bin } i \text{ is used} \\
0 & \text{otherwise}
\end{cases}
$$

$$
y_{ui} = \begin{cases}
1 & \text{if item } u \text{ is placed in bin } i \\
0 & \text{otherwise}
\end{cases}
$$


## 2. Objective Function

$$
\text{Minimize} \quad Z = \sum_{i=1}^{k} x_i
$$

## 3. Constraints

1. Each item must be placed in exactly one bin:

$$
\sum_{i=1}^{k} y_{ui} = 1 \quad \forall u \in U
$$

2. The total weight of items in each bin must not exceed the capacity:

$$
\sum_{u=1}^{n} w_u y_{ui} \leq x_i \quad \forall i = 1, 2, ..., k
$$

3. If a bin is used, it must contain at least one item:

$$x_i \leq \sum_{u=1}^{n} y_{ui} \quad \forall i = 1, 2, ..., k$$

4. Binary constraints on decision variables:

$$
x_i \in \{0, 1\} \quad \forall i = 1, 2, ..., k
$$

$$
y_{ui} \in \{0, 1\} \quad \forall u \in U, \forall i = 1, 2, ..., k
$$


