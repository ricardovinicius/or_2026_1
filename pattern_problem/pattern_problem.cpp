#include <ilcplex/ilocplex.h>
#include <vector>

ILOSTLBEGIN

int main() {
    IloEnv env;

    try {
        IloModel model(env);

        // Data
        std::vector<int> sheetType1({4, 0, 2, 3}); // Amount of bodies for each pattern
        std::vector<int> sheetType2({0, 2, 1, 0}); // Amount of tops for each pattern
        
        int profitPerCan = 50; // Profit per can printed
        int costPerUnusedBody = 50; // Cost per unused body sheet
        int costPerUnusedTop = 3; // Cost per unused top sheet
        int totalMaterial1 = 200; // Total available type 1 sheets
        int totalMaterial2 = 90; // Total available type 2 sheets

        // Decision variables
        IloNumVarArray x(env, sheetType1.size(), 0, IloIntMax, ILOINT); // Number of printings of each pattern
        IloIntVar y(env, 0, IloIntMax); // Assembled cans
        IloIntVar s_b(env, 0, IloIntMax); // Unused body sheets
        IloIntVar s_t(env, 0, IloIntMax); // Unused top sheets
        
        // Material Constraints
        IloExpr totalPrintedType1(env);
        totalPrintedType1 += x[0] + x[2] + x[3];
        model.add(totalPrintedType1 <= totalMaterial1);

        IloExpr totalPrintedType2(env);
        totalPrintedType2 += x[1];
        model.add(totalPrintedType2 <= totalMaterial2);

        // Cans Assembly Constraints
        model.add(y + s_b == sheetType1[0] * x[0] + sheetType1[2] * x[2] + sheetType1[3] * x[3]);
        model.add(2 * y + s_t == sheetType2[1] * x[1] + sheetType2[2] * x[2]);
        
        // Objective: Maximize the profit from printing patterns while minimizing the cost of unused sheets
        IloExpr objective(env);
        objective += profitPerCan * y - costPerUnusedBody * s_b - costPerUnusedTop * s_t;
        model.add(IloMaximize(env, objective));

        // Solve the model
        IloCplex cplex(model);
        cplex.setOut(env.getNullStream());
        cplex.solve();
        
        // Output results
        cout << "Optimal profit: " << cplex.getObjValue() << endl;
        for (int i = 0; i < sheetType1.size(); ++i) {
            cout << "Number of printings of pattern " << i + 1 << ": " << cplex.getValue(x[i]) << endl;
        }
        cout << "Number of cans assembled: " << cplex.getValue(y) << endl     << "Unused body sheets: " << cplex.getValue(s_b) << endl
         << "Unused top sheets: " << cplex.getValue(s_t) << endl;

    } catch (IloException& e) {
        std::cerr << "CPLEX Error: " << e << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
    }
    
    env.end();
    return 0;
}