#include <ilcplex/ilocplex.h>
#include <vector>

ILOSTLBEGIN

int main() {
    IloEnv env;

    try {
        IloModel model(env);

        // Data
        const int N = 5; // Number of potential facilities
        const int M = 10; // Number of customers
        std::vector<double> fixed_costs = {150, 150, 120, 130, 110}; // Fixed costs for opening each facility
        std::vector<std::vector<double>> service_costs = { // Service costs from each facility to each customer
            {20, 30, 25, 35, 40, 45, 50, 55, 60, 65},
            {25, 35, 30, 40, 45, 50, 55, 60, 65, 70},
            {30, 40, 35, 45, 50, 55, 60, 65, 70, 75},
            {35, 45, 40, 50, 55, 60, 65, 70, 75, 80},
            {40, 50, 45, 55, 60, 65, 70, 75, 80, 85}
        };
        

        // Declare Variables

        // x[i] = 1 if facility i is opened, 0 otherwise
        IloArray<IloBoolVar> x(env, N);
        for (int i = 0; i < N; ++i) {
            x[i] = IloBoolVar(env);
        }

        // y[i][j] = 1 if customer j is served by facility i, 0 otherwise
        IloArray<IloArray<IloBoolVar>> y(env, N);
        for (int i = 0; i < N; ++i) {
            y[i] = IloArray<IloBoolVar>(env, M);
            for (int j = 0; j < M; ++j) {
                y[i][j] = IloBoolVar(env);
            }
        }

        // Objective Function: Minimize the cost of opening facilities and serving customers
        IloExpr objective(env);
        for (int i = 0; i < N; ++i) {
            objective += fixed_costs[i] * x[i]; // Fixed cost for opening facility i
            for (int j = 0; j < M; ++j) {
                objective += service_costs[i][j] * y[i][j]; // Service cost from facility i to customer j
            }
        }
        model.add(IloMinimize(env, objective));

        // Constraints

        // 1. Each customer must be served by exactly one facility
        for (int j = 0; j < M; ++j) {
            IloExpr customer_served(env);
            for (int i = 0; i < N; ++i) {
                customer_served += y[i][j];
            }
            model.add(customer_served == 1);
            customer_served.end();
        }

        // 2. A customer can only be served by an open facility
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                model.add(y[i][j] <= x[i]);
            }
        }

        // 3. Binary constraints on decision variables are implicitly defined by IloBoolVar

        // Solve the model
        IloCplex cplex(model);
        cplex.setOut(env.getNullStream());
        cplex.solve();

        // Output results
        std::cout << "Optimal Cost: " << cplex.getObjValue() << std::endl;
        std::cout << "Facilities opened: ";
        for (int i = 0; i < N; ++i) {
            if (cplex.getValue(x[i]) > 0.5) {
                std::cout << i << " ";
            }
        }
        std::cout << std::endl;
        std::cout << "Customer assignments: " << std::endl;
        for (int j = 0; j < M; ++j) {
            for (int i = 0; i < N; ++i) {
                if (cplex.getValue(y[i][j]) > 0.5) {
                    std::cout << "Customer " << j << " is served by Facility " << i << std::endl;
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