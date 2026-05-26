#include <ilcplex/ilocplex.h>
#include <vector>

ILOSTLBEGIN

int main() {
    IloEnv env; // Create the environment (memory manager for CPLEX)

    try {
        IloModel model(env);

        vector<int> compound_vitamin_a({1, 0, 2, 2, 1, 2});
        vector<int> compound_vitamin_c({0, 1, 3, 1, 3, 2});

        int vitamin_a_requirement = 9;
        int vitamin_c_requirement = 19;

        vector<int> compound_cost({35, 30, 60, 50, 27, 22});

        // Declare Variables
        IloNumVarArray x(env, compound_vitamin_a.size(), 0.0, IloInfinity, ILOINT);
        for (int i = 0; i < compound_vitamin_a.size(); i++) {
            x[i].setName(("x" + to_string(i)).c_str());
        }

        // Objective Function: Minimize Cost
        IloExpr objective(env);
        for (int i = 0; i < compound_cost.size(); i++) {
            objective += compound_cost[i] * x[i];
        }
        model.add(IloMinimize(env, objective));
        objective.end(); // Free memory used by the expression

        // Constraints
        IloExpr vitamin_a_constraint(env);
        for (int i = 0; i < compound_vitamin_a.size(); i++) {
            vitamin_a_constraint += compound_vitamin_a[i] * x[i];
        }
        model.add(vitamin_a_constraint >= vitamin_a_requirement);
        vitamin_a_constraint.end(); // Free memory

        IloExpr vitamin_c_constraint(env);
        for (int i = 0; i < compound_vitamin_c.size(); i++) {
            vitamin_c_constraint += compound_vitamin_c[i] * x[i];
        }
        model.add(vitamin_c_constraint >= vitamin_c_requirement);
        vitamin_c_constraint.end(); // Free memory
        
        // Instantiate the solver and solve
        IloCplex cplex(model); 
        cplex.setOut(env.getNullStream()); // Optional: Suppress CPLEX output in the terminal
        cplex.solve();
        if (cplex.getStatus() == IloAlgorithm::Optimal) {
            env.out() << "Minimum Cost: $" << cplex.getObjValue() << endl;
            for (int i = 0; i < compound_vitamin_a.size(); i++) {
                env.out() << "Compound " << i << ": " << cplex.getValue(x[i]) << " units" << endl;
            }
        } else {
            env.out() << "No optimal solution found." << endl;
        }
    } catch (IloException& e) {
        cerr << "CPLEX Error: " << e << endl;
    }
}