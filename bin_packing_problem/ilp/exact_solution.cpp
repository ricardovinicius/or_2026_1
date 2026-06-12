#include <ilcplex/ilocplex.h>
#include <vector>

ILOSTLBEGIN

int main(int argc, char* argv[]) {
    // Read input data (number of items, weights, etc.)
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    string filename = argv[1];

    ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    int n; // number of items
    infile >> n;

    std::vector<double> weights; // weights of items
    weights.resize(n);
    for (int i = 0; i < n; ++i) {
        infile >> weights[i];
    }

    infile.close();

    cout << "Number of items: " << n << std::endl;

    // -- CPLEX Model Setup --

    IloEnv env;

    try {
        IloModel model(env);

        // Declare Variables

        vector<IloBoolVar> x; // Binary variable indicating if bin i is used
        vector<vector<IloBoolVar>> y; // Binary variable indicating if item u is placed
        int k = n; // Maximum number of bins (worst case)
        x.resize(k);
        y.resize(n);
        for (int i = 0; i < k; ++i) {
            x[i] = IloBoolVar(env);
        }
        for (int u = 0; u < n; ++u) {
            y[u].resize(k);
            for (int i = 0; i < k; ++i) {
                y[u][i] = IloBoolVar(env);
            }
        }

        // Objective Function: Minimize the number of bins used
        IloExpr objective(env);
        for (int i = 0; i < k; ++i) {
            objective += x[i];
        }
        model.add(IloMinimize(env, objective));
        objective.end();

        // Constraints
        // Each item must be placed in exactly one bin
        for (int u = 0; u < n; ++u) {
            IloExpr itemConstraint(env);
            for (int i = 0; i < k; ++i) {
                itemConstraint += y[u][i];
            }
            model.add(itemConstraint == 1);
            itemConstraint.end();
        }

        // The total weight in each bin cannot exceed 1
        for (int i = 0; i < k; ++i) {
            IloExpr binConstraint(env);
            for (int u = 0; u < n; ++u) {
                binConstraint += weights[u] * y[u][i];
            }
            model.add(binConstraint <= x[i]);
            binConstraint.end();
        }

        // Link bin usage with item placement
        for (int i = 0; i < k; ++i) {
            for (int u = 0; u < n; ++u) {
                model.add(y[u][i] <= x[i]);
            }
        }

        // If a bin is used, it must contain at least one item
        for (int i = 0; i < k; ++i) {
            IloExpr binUsageConstraint(env);
            for (int u = 0; u < n; ++u) {
                binUsageConstraint += y[u][i];
            }
            model.add(x[i] <= binUsageConstraint);
            binUsageConstraint.end();
        }

        // Symmetry Breaking: Force bins to be used in sequential order
        for (int i = 0; i < k - 1; ++i) {
            model.add(x[i] >= x[i+1]);
        }

        // Solve the model
        IloCplex cplex(model);
        cplex.setOut(env.getNullStream()); // Suppress output
        
        // Output results
        cout << "Results:" << endl;
        if (cplex.solve()) {
            cout << "Optimal number of bins used: " << cplex.getObjValue() << endl;
            
            // Output the items in each bin
            for (int i = 0; i < k; ++i) {
                if (cplex.getValue(x[i]) > 0.5) { // Bin is used
                    cout << "Bin " << i + 1 << ": ";
                    for (int u = 0; u < n; ++u) {
                        if (cplex.getValue(y[u][i]) > 0.5) {
                            cout << "Item " << u + 1 << " (weight: " << weights[u] << ") ";
                        }
                    }
                    cout << endl;
                }
            }
        } else {
            cout << "No solution found." << endl;
        }
    } catch (IloException& e) {
        std::cerr << "CPLEX Error: " << e << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
    }
    
    env.end();
    return 0;
}