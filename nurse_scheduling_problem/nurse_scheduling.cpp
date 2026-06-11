#include <ilcplex/ilocplex.h>
#include <vector>

ILOSTLBEGIN

int main() {
    IloEnv env;

    try {
        IloModel model(env);

        // Data
        vector<int> demandPerDay({3, 2, 4, 5, 3, 1, 2}); // Demand for each day

        // Decision variables
        IloArray<IloIntVar> x(env, demandPerDay.size()); // Number of nurses assigned to each day
        for (int i = 0; i < demandPerDay.size(); ++i) {
            x[i] = IloIntVar(env, 0, IloIntMax, ("x" + to_string(i)).c_str());
        }

        // Constraints
        model.add(x[0] + x[6] + x[5] + x[4] >= demandPerDay[0]); // Sunday
        model.add(x[1] + x[0] + x[6] + x[5] >= demandPerDay[1]); // Monday
        model.add(x[2] + x[1] + x[0] + x[6] >= demandPerDay[2]); // Tuesday
        model.add(x[3] + x[2] + x[1] + x[0] >= demandPerDay[3]); // Wednesday
        model.add(x[4] + x[3] + x[2] + x[1] >= demandPerDay[4]); // Thursday
        model.add(x[5] + x[4] + x[3] + x[2] >= demandPerDay[5]); // Friday
        model.add(x[6] + x[5] + x[4] + x[3] >= demandPerDay[6]); // Saturday

        // Objective: Minimize total number of nurses
        IloExpr totalNurses(env);
        for (int i = 0; i < demandPerDay.size(); ++i) {
            totalNurses += x[i];
        }
        model.add(IloMinimize(env, totalNurses));

        // Solve the model
        IloCplex cplex(model);
        cplex.setOut(env.getNullStream());
        cplex.solve();
        
        // Output results
        cout << "Total number of nurses needed: " << cplex.getObjValue() << endl;
        for (int i = 0; i < demandPerDay.size(); ++i) {
            cout << "Nurses assigned to day " << i + 1 << ": " << cplex.getValue(x[i]) << endl;
        }
    } catch (IloException& e) {
        std::cerr << "CPLEX Error: " << e << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
    }
    
    env.end();
    return 0;
}