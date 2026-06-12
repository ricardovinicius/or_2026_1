# Lista de Exercícios - OR2026 - 2026/1

## 1. Implementação de uma Meta-heurística de Solução Única para o Bin Packing Problem (BPP)

A solução foi implementada e está disponível no repositório, especificamente na pasta `bin_packing_problem/ils`. O código inclui a definição do modelo, a implementação da meta-heurística Iterated Local Search (ILS) e um gerador de instâncias para o problema.

Também foi implementado um script com uma solução exata utilizando Programação Linear Inteira (ILP) para comparação, disponível na pasta `bin_packing_problem/ilp`. 

Na pasta `bin_packing_problem/instances`, há um script para gerar instâncias do problema, e algumas instâncias de exemplo estão incluídas para teste.

Em cada solução, há uma pasta `output` onde os resultados são armazenados, incluindo o número de bins utilizados e a distribuição dos itens em cada bin. Assim como os arquivos de código, os resultados estão organizados para facilitar a análise e comparação entre as abordagens exata e heurística.

A modelagem do problema, tanto para a solução exata quanto para a meta-heurística, está detalhada nos arquivos `model.md` dentro de cada pasta correspondente. Esses arquivos explicam a estrutura dos dados, as variáveis de decisão, a função objetivo e as restrições do problema.

## 2. Implemente todos os modelos de Programação Linear Inteira (ILP) vistos em aula.

Todos os problemas de ILP discutidos em aula foram implementados e estão disponíveis no repositório. Cada modelo está organizado em sua própria pasta, com um arquivo `model.md` que detalha a formulação do modelo, incluindo as variáveis de decisão, a função objetivo e as restrições.

Segue uma tabela resumida dos modelos implementados:

| Problema                 | Pasta no Repositório         | Descrição                                      |
|--------------------------|-----------------------------|------------------------------------------------|
| Coverage Problem         | `coverage_problem/`       | Modelo de ILP para o problema de cobertura.    |
| Knapsack Problem         | `knapsack_problem/`       | Modelo de ILP para o problema da mochila.      |
| Diet Problem             | `diet_problem/`           | Modelo de ILP para o problema da dieta.        |
| Facility Location Problem | `facilities_problem/` | Modelo de ILP para o problema de localização de instalações. |
| Farmer Problem             | `farmer_problem/`         | Modelo de ILP para o problema do fazendeiro.   |
| Frequency Assignment Problem | `frequency_problem/` | Modelo de ILP para o problema de atribuição de frequências. |
| Inks Problem             | `ink_problem/`           | Modelo de ILP para o problema de tintas.       |
| Maximum Clique Problem         | `max_clique_problem/`         | Modelo de ILP para o problema da clique máxima. |
| Maximum Flow Problem         | `max_flow_problem/`         | Modelo de ILP para o problema do fluxo máximo. |
| Nurses Scheduling Problem         | `nurses_scheduling_problem/`         | Modelo de ILP para o problema de escalonamento de enfermeiros. |
| Pattern Matching Problem         | `pattern_problem/`         | Modelo de ILP para o problema de impressão de padrões. |
| Product Mix Problem         | `product_mix_problem/`         | Modelo de ILP para o problema de mistura de produtos. |
| Transportation Problem         | `transport_problem/`         | Modelo de ILP para o problema de transporte.   |

Todos os modelos foram implementados utilizando a biblioteca de otimização escolhida (CPLEX) em C++. Os arquivos de código estão organizados para facilitar a compreensão e a execução, e cada modelo inclui um exemplo de instância para teste.

O script de cada modelo já está compilado e pronto para execução, basta executar com `<nome_do_problema>` e o output da instância de teste será exibido no terminal, incluindo a solução ótima encontrada e o tempo de execução.