#include <ilcplex/ilocplex.h>
#include <vector>

ILOSTLBEGIN

int main() {
    IloEnv env;

    try {
        IloModel model(env);

        // Data
        vector<vector<IloNum>> capacities({
            {0, 5, 4, 6, 0, 0, 0, 0}, // s
            {0, 0, 4, 0, 6, 5, 0, 0}, // v1
            {0, 0, 0, 3, 0, 4, 0, 0}, // v2
            {0, 0, 0, 0, 0, 6, 5, 0}, // v3
            {0, 0, 0, 0, 0, 0, 0, 5}, // v4
            {0, 0, 0, 0, 5, 0, 0, 3}, // v5
            {0, 0, 0, 0, 0, 7, 0, 6}, // v6
            {0, 0, 0, 0, 0, 0, 0, 0}  // t
        });

        int numNodes = capacities.size();
        vector<int> neighbors_of_t = {4, 5, 6}; // Nodes that have edges into sink 't'
        
        // Declare Variables
        IloArray<IloNumVarArray> x(env, numNodes);
        for (int i = 0; i < numNodes; ++i) {
            x[i] = IloNumVarArray(env, numNodes, 0.0, IloInfinity, ILOINT);
        }

        // Objective Function: Maximize flow from source 's' to sink 't'
        IloExpr objective(env);
        for (int i = 0; i < neighbors_of_t.size(); ++i) {
            objective += x[neighbors_of_t[i]][7]; // flow into sink 't'
        }
        model.add(IloMaximize(env, objective));

        // Capacity Constraints
        for (int i = 0; i < numNodes; ++i) {
            for (int j = 0; j < numNodes; ++j) {
                model.add(x[i][j] <= capacities[i][j]);
            }
        }

        // Flow Conservation Constraints
        for (int i = 1; i < numNodes - 1; ++i) { // Exclude source 's' and sink 't'
            IloExpr flow_in(env);
            IloExpr flow_out(env);
            for (int j = 0; j < numNodes; ++j) {
                flow_in += x[j][i]; // flow into node i
                flow_out += x[i][j]; // flow out of node i
            }
            model.add(flow_in == flow_out);
        }

        // Solve the model
        IloCplex cplex(model);
        cplex.setOut(env.getNullStream());
        cplex.solve();

        // Output results
        std::cout << "Maximum flow from source 's' to sink 't': " << cplex.getObjValue() << std::endl;
        for (int i = 0; i < numNodes; ++i) {
            for (int j = 0; j < numNodes; ++j) {
                if (capacities[i][j] > 0) {
                    std::cout << "Flow from node " << i << " to node " << j << ": " << cplex.getValue(x[i][j]) << std::endl;
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