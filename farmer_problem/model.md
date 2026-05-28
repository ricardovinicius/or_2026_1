# Farmer Problem

An agricultural cooperative operates 3 farms. The total production of each farm depends on the area available for planting and the water for irrigation. The cooperative seeks to diversify its production and will plant 3 crops on each farm this year: corn, rice, and beans. Each crop requires a certain amount of water. Planted area limits are established for each crop. To avoid competition among the cooperative members, it was agreed that the proportion of cultivated area must be the same for each farm. Determine the planted area of each crop on each farm in order to optimize the cooperative's profit.

| Farm | Area (acres) | Water (liters) |
| --- | --- | --- |
| 1 | 400 | 1800 |
| 2 | 650 | 2200 |
| 3 | 350 | 950 |

| Crop | Max Area | Water (liters per area) | Profit (per area) |
| --- | --- | --- | --- |
| Corn | 660 | 5.5 | 5000 |
| Rice | 880 | 4 | 4000 |
| Beans | 400 | 3.5 | 1800 |

# Modeling

## Decision Variables

$ C_1, C_2, C_3 \ge 0 \quad \text{(Quantity of Corn planted in each farm)} $

$ R_1, R_2, R_3 \ge 0 \quad \text{(Quantity of Rice planted in each farm)} $

$ B_1, B_2, B_3 \ge 0 \quad \text{(Quantity of Beans planted in each farm)} $

## Objective Function

$ max \sum_{i = 1}^{3} C_iP_c + R_iP_r + B_iP_b $

$ P_c \text{ is profit of Corn, the others are similar} $

$ P_c = 5000, \quad P_r = 4000, \quad P_b = 1800 $

## Restrictions

$ \text{1. Farm Area Restrictions: } $

$ C_1 + R_1 + B_1 \le 400 $

$ C_2 + R_2 + B_2 \le 650 $

$ C_3 + R_3 + B_3 \le 350 $

$ \text{2. Plant Area Restrictions: } $

$ C_1 + C_2 + C_3 \le 660 $

$ R_1 + R_2 + R_3 \le 880 $

$ B_1 + B_2 + B_3 \le 400 $

$ \text{3. Water per Farm Restrictions: } $

$ W_c = 5.5, \quad W_r = 4, \quad W_b = 3.5 \quad \text{(Water per Area of each plant)}$

$ W_cC_1 + W_rR_1 +  W_bB_1 \le 1800 $

$ W_cC_2 + W_rR_2 +  W_bB_2 \le 2200 $

$ W_cC_3 + W_rR_3 +  W_bB_3 \le 950 $

$ \text{4. Equal Proportion of Cultivated Area Restrictions: } $

$ 650(C_1 + R_1 + B_1) - 400(C_2 + R_2 + B_2) = 0 $

$ 350(C_2 + R_2 + B_2) - 650(C_3 + R_3 + B_3) = 0 $
