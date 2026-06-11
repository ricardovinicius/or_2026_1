#include <ilcplex/ilocplex.h>
#include <vector>

ILOSTLBEGIN

int main() {
    IloEnv env;

    try {
        IloModel model(env);

        // Data
        IloInt n = 5; // Number of items
        IloInt W = 10; // Capacity of the knapsack
        std::vector<IloInt> w = {2, 3, 4, 5, 6}; // Weights of items
        std::vector<IloInt> v = {3, 4, 5, 6, 7}; // Values of items

        // Declare Variables
        IloArray<IloBoolVar> x(env, n);
        for (IloInt j = 0; j < n; ++j) {
            x[j] = IloBoolVar(env);
        }

        // Objective Function: Maximize value
        IloExpr objective(env);
        for (IloInt j = 0; j < n; ++j) {
            objective += v[j] * x[j];
        }
        model.add(IloMaximize(env, objective));

        // Constraints
        IloExpr weight_constraint(env);
        for (IloInt j = 0; j < n; ++j) {
            weight_constraint += w[j] * x[j];
        }
        model.add(weight_constraint <= W);

        // Solve the model
        IloCplex cplex(model);
        cplex.setOut(env.getNullStream());
        cplex.solve();

        // Output results
        std::cout << "Optimal value: " << cplex.getObjValue() << std::endl;
        std::cout << "Selected items: ";
        for (IloInt j = 0; j < n; ++j) {
            if (cplex.getValue(x[j]) > 0.5) {
                std::cout << j << " ";
            }
        }
        std::cout << std::endl;
        
    } catch (IloException& e) {
        std::cerr << "CPLEX Error: " << e << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
    }
    
    env.end();
    return 0;
}