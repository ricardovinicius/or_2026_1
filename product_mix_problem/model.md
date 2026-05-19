# Dog Food Problem

A dog food company produces 2 types of dog food:

- All Mega Giga Suprema (AMGS) and Ração das Estrelas (RE).
- Cereals and meat are used in their manufacturing.
- AMGS uses 5 kg of cereals and 1 kg of meat, and RE uses 4 kg of meat and 2 kg of cereals.
- The price of AMGS is 20 reais and the price of RE is 30 reais.
- 1 kg of meat costs 4 reais and 1 kg of cereal costs 1 real.
- There are 10,000 kg of meat and 30,000 kg of cereals available.
- What should the company's production be to make the maximum amount of money?

# Modeling

## Decision Variables

$AMGS: \text{Quantity of Production of All Mega Giga Suprema} $

$RE: \text{Quantity of Production of Ração das Estrelas} $

## Function Objective

**Profit Objective: Income - Cost**

$ \max{Z} = {AMGS} * 20 + RE * 30 - AMGS(5*1 + 1*4) - RE(4*4 + 2*1)  $

$ \max{Z} = 11(AMGS) + 12(RE) $

## Restrictions

**Ingredients Availability Restriction:**

$ AMGS + 4(RE) \le 10000 \quad \text{(Meat Restriction)} $ 


$ 5(AMGS) + 2(RE) \le 30000 \quad \text{(Cereal Restriction)} $ 

**Non-negativity Restriction:**

$ AMGS,RE \ge 0 \quad \text{(Non-negativity Restrictions)} $

