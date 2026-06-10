# Transport Problem Model

* Deposits have demands that must be met.
* Factories have supplies to satisfy the deposits.
* Each arc has a transportation cost $c_{ij}$ between factory $i$ and deposit $j$.
* We want to meet the deposits' demands at a minimum transportation cost, respecting the constraints.

---

### Cost Matrix ($c_{ij}$)

| Fab-Dep | 1 | 2 | 3 |
| --- | --- | --- | --- |
| **1** | 8 | 5 | 6 |
| **2** | 15 | 10 | 12 |
| **3** | 3 | 9 | 10 |

---

### Supplies and Demands

**Factories (Supply)**

* Factory 1: 120
* Factory 2: 80
* Factory 3: 80

**Deposits (Demand)**

* Deposit 1: 150
* Deposit 2: 70
* Deposit 3: 60

## 1. Decision Variables $(x_j)$

$$
x_{ij} >= 0 \quad \forall i = 1, 2, ..., m; \forall j = 1, 2, ..., n \qquad \text{(Amount of demand transported from company $i$ to facility $j$)}
$$

## 2. Function Objective

$$
\min Z = \sum_{i = 1}^{m} \sum_{j = 1}^{n} c_{ij} x_{ij}
$$

## 3. Restrictions

1. Each company need to transport a certain amount of demand:

$$
\sum_{j = 1}^{n} d_{i} x_{ij} = d_i, \forall i = 1, 2, ..., m
$$

2. Each facility can only receive a certain amount of demand:

$$
\sum_{i = 1}^{m} d_{i} x_{ij} \leq d_j, \forall j = 1, 2, ..., n
$$
