# Pattern Problem Model

* A can factory have 4 different printing patterns in metal sheets.
* Exists 2 types of metal sheets with different dimensions.
* The factory have 200 metal sheets of type 1 and 90 metal sheets of type 2.
* Each can is selled for 50 units.
* Each non-used body of metal sheet have a storage cost of 50 units, and each non-used top of metal sheet have a storage cost of 3 units.
* How many printings of each pattern the factory should do to maximize the profit?

## Data Model:

| | Pattern 1 | Pattern 2 | Pattern 3 | Pattern 4 |
|---|---|---|---|---|
| Sheet Type | 1 | 2 | 1 | 1 |
| Amount of bodies | 4 | 0 | 2 | 3 |
| Amount of tops | 0 | 2 | 1 | 0 |
| Printing time | 2 | 3 | 2 | 1 |


## 1. Decision Variables $(x_i)$

$x_i = \text{number of printings of pattern } i \quad \forall i \in \{1, 2, 3, 4\}$


## 2. Objective Function

$$
\begin{align}
x_i = & \text{number of printings of pattern } i \quad \forall i \in \{1, 2, 3, 4\} \\
y = & {\text{Total number of fully assembled cans}} \\
s_b = & \text{number of non-used bodies of metal sheets} \\
s_t = & \text{number of non-used tops of metal sheets}
\end{align}
$$

$$
\max Z = 50y - 50s_b - 3s_t
$$

## 3. Constraints

* Material constraints: 

$$
\begin{align}
x_1 + x_3 + x_4 & \le 200 \quad \text{(printings of sheet type 1)} \\
x_2 & \le 90 \quad \text{(printings of sheet type 2)}
\end{align}
$$

* Cans assembly constraints:

$$
\begin{align}
y + s_b & = 4x_1 + 2x_3 + 3x_4 \quad \text{(bodies)} \\
2y + s_t & = 2x_2 + x_3 \quad \text{(tops)}
\end{align}
$$

* Domain constraints:

$$
x_i \in \mathbb{Z}_{\ge 0} \quad \forall i \in \{1, 2, 3, 4\}
$$

