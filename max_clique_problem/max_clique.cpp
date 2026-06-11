#include <ilcplex/ilocplex.h>
#include <vector>

ILOSTLBEGIN

int main() {
    IloEnv env;

    try {
        IloModel model(env);

        // Data
        vector<std::vector<int>> adjacencyMatrix = {
            {0, 1, 1, 0},
            {1, 0, 1, 1},
            {1, 1, 0, 1},
            {0, 1, 1, 0}
        };
        int n = adjacencyMatrix.size();

        // Declare Variables
        IloBoolVarArray x(env, n);
        

        // Objective Function: Maximize the size of the clique
        IloExpr objective(env);
        for (int j = 0; j < n; ++j) {
            objective += x[j];
        }
        model.add(IloMaximize(env, objective));

        // Constraints
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                model.add(x[i] + x[j] <= 1 + adjacencyMatrix[i][j]);
            }
        }


        // Solve the model
        IloCplex cplex(model);
        cplex.setOut(env.getNullStream());
        cplex.solve();

        // Output results
        if (cplex.getStatus() == IloAlgorithm::Optimal) {
            std::cout << "Maximum Clique Size: " << cplex.getObjValue() << std::endl;
            std::cout << "Vertices in the Clique: ";
            for (int j = 0; j < n; ++j) {
                if (cplex.getValue(x[j]) > 0.5) {
                    std::cout << j << " ";
                }
            }
            std::cout << std::endl;
        } else {
            std::cout << "No optimal solution found." << std::endl;
        }
    } catch (IloException& e) {
        std::cerr << "CPLEX Error: " << e << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
    }
    
    env.end();
    return 0;
}