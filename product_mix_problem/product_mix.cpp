#include <ilcplex/ilocplex.h>

// Macro da IBM para usar o namespace std e facilitar os inputs/outputs
ILOSTLBEGIN 

int main() {
    IloEnv env; // Cria o ambiente (gerenciador de memória do CPLEX)
    
    try {
        IloModel model(env);

        // Declarando variáveis: (ambiente, limite_inferior, limite_superior, tipo)
        IloNumVar amgs(env, 0.0, IloInfinity, ILOINT);
        IloNumVar re(env, 0.0, IloInfinity, ILOINT);

        // Função Objetivo: Maximizar o lucro
        model.add(IloMaximize(env, 11 * amgs + 12 * re));

        // Restrições
        model.add(amgs + 4 * re <= 10000);
        model.add(5 * amgs + 2 * re <= 30000);

        // Instanciando o solver e resolvendo
        IloCplex cplex(model);
        
        // Desativa os logs gigantes do CPLEX no terminal (opcional)
        cplex.setOut(env.getNullStream()); 

        if (cplex.solve()) {
            env.out() << "Lucro Máximo: R$ " << cplex.getObjValue() << endl;
            env.out() << "AMGS: " << cplex.getValue(amgs) << " kg" << endl;
            env.out() << "RE: " << cplex.getValue(re) << " kg" << endl;
        } else {
            env.out() << "Não foi possível encontrar uma solução." << endl;
        }
        
    } catch (IloException& e) {
        cerr << "Erro do CPLEX: " << e << endl;
    }
    
    // Limpeza obrigatória de memória no C++ com CPLEX
    env.end(); 
    return 0;
}