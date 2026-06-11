# Nurse Scheduling Problem Model

* In a hospital, the goal is to schedule nurses for the night shift. 
* The demand for night shift nurses on day $i$ is an integer $d_i$, with $i = 1 \dots 7$. 
* Each nurse works 5 consecutive days and rests for the following three days. 
* The objective is to minimize the number of hired nurses.

## 1. Decision Variables $(x_j)$

$$
x_i = \text{number of nurses starting their 5-day shift on day } i \quad \forall i = 1 \dots 7
$$

## 2. Objective Function

$$
\min \sum_{i=1}^{7} x_i \quad \text{(minimize total number of nurses hired)}
$$


## 3. Constraints

1. Integer constraints: $x_i \in \mathbb{Z}^+ \quad \forall i = 1 \dots 7$

2. Demand constraints: For each day $i$, the total number of nurses working must meet or exceed the demand $d_i$. Since each nurse works for 5 consecutive days, the constraints can be expressed as:

$$
\begin{aligned}
x_1 + x_7 + x_6 + x_5 &\geq d_1 \quad \text{Sunday }\\
x_2 + x_1 + x_7 + x_6  &\geq d_2 \quad \text{Monday }\\
x_3 + x_2 + x_1 + x_7 &\geq d_3 \quad \text{Tuesday }\\
x_4 + x_3 + x_2 + x_1 &\geq d_4 \quad \text{Wednesday }\\
x_5 + x_4 + x_3 + x_2 &\geq d_5 \quad \text{Thursday }\\
x_6 + x_5 + x_4 + x_3  &\geq d_6 \quad \text{Friday }\\
x_7 + x_6 + x_5 + x_4 &\geq d_7 \quad \text{Saturday }\\
\end{aligned}