# Diet Problem

For the proper functioning of the body, a person needs to ingest a minimum amount of certain vitamins, present in 6 different ingredients that must be combined into a minimum-cost food compound.

| Vitamins | 1 | 2 | 3 | 4 | 5 | 6 | Min. Amount |
| --- | --- | --- | --- | --- | --- | --- | --- |
| A | 1 | 0 | 2 | 2 | 1 | 2 | 9 |
| C | 0 | 1 | 3 | 1 | 3 | 2 | 19 |
| Price | 35 | 30 | 60 | 50 | 27 | 22 |  |

# Modeling

## Decision Variables

$ V_i, \quad \forall i \in \{1,2,3,4,5,6\} $

## Objective Function

$ \min \sum_{i = 1}^{6} V_iP_i \quad (P_i \text{ represents the price of Compound i})$

## Restrictions

$ \sum_{i = 1}^{6} V_iA_i \ge 9 \quad (\text{Vitamin A minimum amount restriction}) $

$ \sum_{i = 1}^{6} V_iC_i \ge 19 \quad (\text{Vitamin C minimum amount restriction}) $

$ V_i \ge 0, \forall i \quad (\text{Non-negativity restriction}) $
