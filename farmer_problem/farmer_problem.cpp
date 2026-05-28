#include <ilcplex/ilocplex.h>
#include <vector>

ILOSTLBEGIN

int main() {
    IloEnv env; // Create the environment (memory manager for CPLEX)

    try {
        IloModel model(env);

        // Data
        float water_per_corn = 5.5;
        float water_per_rice = 4.0;
        float water_per_bean = 3.5;

        float profit_per_corn = 5000.0;
        float profit_per_rice = 4000.0;
        float profit_per_bean = 1800.0;

        vector<float> max_area_per_farm({400.0, 650.0, 350.0}); 
        vector<float> max_water_per_farm({1800.0, 2200.0, 950.0});
        vector<float> max_area_per_plant({660.0, 880.0, 400.0});

        // Declare Variables
        IloNumVarArray corn(env, 3, 0.0, IloInfinity, ILOINT); // Corn per farm (3 farms)
        IloNumVarArray rice(env, 3, 0.0, IloInfinity, ILOINT); // Rice per farm (3 farms)
        IloNumVarArray bean(env, 3, 0.0, IloInfinity, ILOINT); // Beans per farm (3 farms)

        // Objective Function: Maximize Profit
        IloExpr profit(env);
        for (int i = 0; i < 3; i++) {
            profit += profit_per_corn * corn[i] + profit_per_rice * rice[i] + profit_per_bean * bean[i];
        }
        model.add(IloMaximize(env, profit));
        profit.end(); // Free memory used by the expression

        // Constraints
        for (int i = 0; i < 3; i++) {
            // Water constraint
            model.add(water_per_corn * corn[i] + water_per_rice * rice[i] + water_per_bean * bean[i] <= max_water_per_farm[i]);
            // Land constraint
            model.add(corn[i] + rice[i] + bean[i] <= max_area_per_farm[i]);
            
        }

        // Total area constraint for each plant type across all farms
        IloExpr corn_sum(env);
        IloExpr rice_sum(env);
        IloExpr bean_sum(env);
        for (int i = 0; i < 3; i++) {
            corn_sum += corn[i];
            rice_sum += rice[i];
            bean_sum += bean[i];
        }
        
        model.add(corn_sum <= max_area_per_plant[0]);
        model.add(rice_sum <= max_area_per_plant[1]);
        model.add(bean_sum <= max_area_per_plant[2]);

        corn_sum.end();
        rice_sum.end();
        bean_sum.end();

        // Equal production proportion for corn across all farms
        model.add(650.0 * (corn[0] + rice[0] + bean[0]) == 400.0 * (corn[1] + rice[1] + bean[1]));
        model.add(350.0 * (corn[1] + rice[1] + bean[1]) == 650.0 * (corn[2] + rice[2] + bean[2]));

        // Instantiate the solver and solve
        IloCplex cplex(model); 
        cplex.setOut(env.getNullStream()); // Optional: Suppress CPLEX output in the terminal
        cplex.solve();
        if (cplex.getStatus() == IloAlgorithm::Optimal) {
            env.out() << "Maximum Profit: $" << cplex.getObjValue() << endl;
            for (int i = 0; i < 3; i++) {
                env.out() << "Farm " << i << ": " << endl;
                env.out() << "  Corn: " << cplex.getValue(corn[i]) << " units" << endl;
                env.out() << "  Rice: " << cplex.getValue(rice[i]) << " units" << endl;
                env.out() << "  Beans: " << cplex.getValue(bean[i]) << " units" << endl;
            }
        } else {
            env.out() << "No optimal solution found." << endl;
        }
    } catch (IloException& e) {
        cerr << "CPLEX Error: " << e << endl;
    }
}