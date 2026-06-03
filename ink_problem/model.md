# Ink Problem

A paint company produces two types of paint: quick-drying (SR) and normal-drying (SN). Both use the same components, varying only in their proportions. The components are: drying component (SEC) and color component (COR). The company has two mixtures available for purchase to compose the paints:

* Solution A (SolA) with **30%** SEC and **70%** COR at R$ 1.50 per liter
* Solution B (SolB) with **60%** SEC and **40%** COR at R$ 1.00 per liter

Additionally, the company also has available:

* Component SEC at R$ 4.00 per liter
* Component COR at R$ 6.00 per liter

Knowing that to compose SR, there must be a minimum of **25%** SEC and a minimum of **50%** COR. For SN, there must be a minimum of **20%** SEC and **50%** COR. What is the quantity of products (SolA, SolB, SEC, COR) to be purchased to produce 1000 liters of SR and 250 liters of SN at the lowest cost?

# Modeling

## Auxiliary Variables

$$\begin{aligned}
SolA &= 0.3(SEC) + 0.7(COR) &\quad \text{Price} &= 1.5 \\
SolB &= 0.6(SEC) + 0.4(COR) &\quad \text{Price} &= 1.0 \\
CompSEC &= 1.0(SEC) &\quad \text{Price} &= 4.0 \\
CompCOR &= 1.0(COR) &\quad \text{Price} &= 6.0
\end{aligned}$$

## Decision Variables

$$
\begin{aligned}
SolA_{SR}, SolA_{SN} &\ge 0 \quad \text{(Quantity of Solution A for SR and SN)} \\
SolB_{SR}, SolB_{SN} &\ge 0 \quad \text{(Quantity of Solution B for SR and SN)} \\
CompSEC_{SR}, CompSEC_{SN} &\ge 0 \quad \text{(Quantity of Component SEC for SR and SN)} \\
CompCOR_{SR}, CompCOR_{SN} &\ge 0 \quad \text{(Quantity of Component COR for SR and SN)} \\

\\ 

SolA &= SolA_{SR} + SolA_{SN} \quad \text{(Total Quantity of Solution A)} \\
SolB &= SolB_{SR} + SolB_{SN} \quad \text{(Total Quantity of Solution B)} \\
CompSEC &= CompSEC_{SR} + CompSEC_{SN} \quad \text{(Total Quantity of Component SEC)} \\
CompCOR &= CompCOR_{SR} + CompCOR_{SN} \quad \text{(Total Quantity of Component COR)}
\end{aligned}
$$


## Objective Function

$$ \min Z = 1.5 \cdot SolA + 1.0 \cdot SolB + 4.0 \cdot CompSEC + 6.0 \cdot CompCOR $$

## Restrictions
$$
\begin{aligned}
SEC_{SR} &= 0.3 \cdot SolA_{SR} + 0.6 \cdot SolB_{SR} + 1.0 \cdot CompSEC_{SR} \\
SEC_{SR} &\ge 250.0 \qquad \text{(SEC component in SR restriction)} \\

\\

COR_{SR} &= 0.7 \cdot SolA_{SR} + 0.4 \cdot SolB_{SR} + 1.0 \cdot CompCOR_{SR} \\
COR_{SR} &\ge 500.0 \qquad \text{(COR component in SR restriction)} \\

\\

SEC_{SN} &= 0.3 \cdot SolA_{SN} + 0.6 \cdot SolB_{SN} + 1.0 \cdot CompSEC_{SN} \\
SEC_{SN} &\ge 50.0 \qquad \text{(SEC component in SN restriction)} \\

\\

COR_{SN} &= 0.7 \cdot SolA_{SN} + 0.4 \cdot SolB_{SN} + 1.0 \cdot CompCOR_{SN} \\
COR_{SN} &\ge 125.0 \qquad \text{(COR component in SN restriction)} \\

\\

SEC_{SR} + COR_{SR} &= 1000.0 \qquad \text{(SR production capacity restriction)} \\
SEC_{SN} + COR_{SN} &= 250.0 \qquad \text{(SN production capacity restriction)}

\end{aligned}
$$
