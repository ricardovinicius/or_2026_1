#include <ilcplex/ilocplex.h>
#include <vector>

ILOSTLBEGIN

int main() {
    IloEnv env;

    try {
        IloModel model(env);

        // Data
        std::vector<std::vector<int>> adjacency_matrix = {
            {0, 1, 0, 1},
            {1, 0, 1, 0},
            {0, 1, 0, 1},
            {1, 0, 1, 0}
        };
        int num_districts = adjacency_matrix.size();

        // Declare Variables
        IloArray<IloBoolVar> x(env, num_districts);
        for (int j = 0; j < num_districts; ++j) {
            x[j] = IloBoolVar(env);
        }

        // Objective Function: Minimize schools built
        IloExpr objective(env);
        for (int j = 0; j < num_districts; ++j) {
            objective += x[j];
        }
        model.add(IloMinimize(env, objective));

        // Constraints
        for (int i = 0; i < num_districts; ++i) {
            IloExpr constraint(env);
            for (int j = 0; j < num_districts; ++j) {
                if (adjacency_matrix[i][j] == 1 || i == j) {
                    constraint += x[j];
                }
            }
            model.add(constraint >= 1);
        }

        // Solve the model
        IloCplex cplex(model);
        cplex.setOut(env.getNullStream());
        cplex.solve();

        // Output results
        if (cplex.getStatus() == IloAlgorithm::Optimal) {
            std::cout << "Optimal solution found." << std::endl;
            std::cout << "Number of schools built: " << cplex.getObjValue() << std::endl;
            std::cout << "Districts with schools:" << std::endl;
            for (int j = 0; j < num_districts; ++j) {
                if (cplex.getValue(x[j]) > 0.5) {
                    std::cout << " - District " << j << std::endl;
                }
            }
        }

    } catch (IloException& e) {
        std::cerr << "CPLEX Error: " << e << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
    }
    
    env.end();
    return 0;
}