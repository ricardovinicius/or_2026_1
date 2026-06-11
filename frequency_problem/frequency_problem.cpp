#include <ilcplex/ilocplex.h>
#include <vector>

ILOSTLBEGIN

int main() {
    IloEnv env;

    try {
        IloModel model(env);

        // Data
        const int numTransmitters = 5; // Example number of transmitters
        vector<pair<int, int>> interferencePairs = {{0, 1}, {1, 2}, {2, 3}, {3, 4}}; // Example interference pairs

        // Declare Variables
        IloArray<IloBoolVarArray> x(env, numTransmitters); // x[i][k] = 1 if transmitter i is assigned frequency k
         for (int i = 0; i < numTransmitters; ++i) {
            x[i] = IloBoolVarArray(env, numTransmitters); // Assuming at most numTransmitters frequencies
            for (int k = 0; k < numTransmitters; ++k) {
                x[i][k] = IloBoolVar(env);
            }
        }
        
        IloBoolVarArray y(env, numTransmitters); // y[k] = 1 if frequency k is used
        for (int k = 0; k < numTransmitters; ++k) {
            y[k] = IloBoolVar(env);
        }

        // Objective Function: Minimize the total number of frequencies used
        IloExpr objective(env);
        for (int k = 0; k < numTransmitters; ++k) {
            objective += y[k];
        }
        model.add(IloMinimize(env, objective));
        objective.end();

        // Constraints
        // 1. Each transmitter must be assigned exactly one frequency
        for (int i = 0; i < numTransmitters; ++i) {
            IloExpr sumFrequencies(env);
            for (int k = 0; k < numTransmitters; ++k) {
                sumFrequencies += x[i][k];
            }
            model.add(sumFrequencies == 1);
        }

        // 2. If two transmitters interfere with each other, they cannot be assigned the same frequency
        for (const auto& pair : interferencePairs) {
            int i = pair.first;
            int j = pair.second;
            for (int k = 0; k < numTransmitters; ++k) {
                model.add(x[i][k] + x[j][k] <= y[k]);
            }
        }   

        // 3. A frequency is considered used if at least one transmitter is assigned to it
        for (int k = 0; k < numTransmitters; ++k) {
            for (int i = 0; i < numTransmitters; ++i) {
                model.add(x[i][k] <= y[k]);
            }
        }

        // 4. Domain constraints for decision variables are already defined by IloBoolVar
  
        // Solve the model
        IloCplex cplex(model);
        cplex.setOut(env.getNullStream());
        cplex.solve();

        // Output results
        if (cplex.getStatus() == IloAlgorithm::Optimal) {
            std::cout << "Optimal number of frequencies used: " << cplex.getObjValue() << std::endl;
            for (int i = 0; i < numTransmitters; ++i) {
                for (int k = 0; k < numTransmitters; ++k) {
                    if (cplex.getValue(x[i][k]) > 0.5) { // Check if x[i][k] is 1
                        std::cout << "Transmitter " << i << " is assigned frequency " << k << std::endl;
                    }
                }
            }
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