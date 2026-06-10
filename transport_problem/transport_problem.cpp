#include <ilcplex/ilocplex.h>
#include <vector>

ILOSTLBEGIN

int main() {
    IloEnv env;

    try {
        IloModel model(env);

        // Data
        vector<vector<IloNum>> cost({
            {8, 5, 6},
            {15, 10, 12},
            {3, 9, 10}
        });

        vector<IloNum> supply({120, 80, 80});
        vector<IloNum> demand({150, 70, 60});

        // Declare Variables
        IloArray<IloNumVarArray> x(env, supply.size());
        for (size_t i = 0; i < supply.size(); ++i) {
            x[i] = IloNumVarArray(env, demand.size(), 0.0, IloInfinity, ILOINT);
        }

        // Objective Function: Minimize Cost
        IloExpr objective(env);
        for (size_t i = 0; i < supply.size(); ++i) {
            for (size_t j = 0; j < demand.size(); ++j) {
                objective += cost[i][j] * x[i][j];
            }
        }
        model.add(IloMinimize(env, objective));

        // Supply Constraints
        for (size_t i = 0; i < supply.size(); ++i) {
            IloExpr supply_constraint(env);
            for (size_t j = 0; j < demand.size(); ++j) {
                supply_constraint += x[i][j];
            }
            model.add(supply_constraint <= supply[i]);
        }

        // Demand Constraints
        for (size_t j = 0; j < demand.size(); ++j) {
            IloExpr demand_constraint(env);
            for (size_t i = 0; i < supply.size(); ++i) {
                demand_constraint += x[i][j];
            }
            model.add(demand_constraint >= demand[j]);
        }

        // Solve the model
        IloCplex cplex(model);
        cplex.setOut(env.getNullStream());
        cplex.solve();

        // Output results
        if (cplex.getStatus() == IloAlgorithm::Optimal) {
            env.out() << "Optimal Solution Found!" << endl;
            env.out() << "------------------------------" << endl;

            env.out() << "Total Cost: R$ " << cplex.getObjValue() << endl;
            for (size_t i = 0; i < supply.size(); ++i) {
                for (size_t j = 0; j < demand.size(); ++j) {
                    env.out() << "x[" << i << "][" << j << "] = " << cplex.getValue(x[i][j]) << endl;
                }
            }
        } else {
            env.out() << "No optimal solution found." << endl;
        }
    } catch (IloException& e) {
        std::cerr << "CPLEX Error: " << e << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
    }
    
    env.end();
    return 0;
}