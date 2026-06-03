#include <ilcplex/ilocplex.h>
#include <vector>

ILOSTLBEGIN

int main() {
    IloEnv env;

    try {
        IloModel model(env);

        // Data
        IloNum cost_per_SolA = 1.5;
        IloNum cost_per_SolB = 1.0;
        IloNum cost_per_CompSEC = 4.0;
        IloNum cost_per_CompCOR = 6.0;

        // Declare Variables
        IloNumVar SolA_SR(env, 0.0, IloInfinity, ILOINT); 
        IloNumVar SolB_SR(env, 0.0, IloInfinity, ILOINT); 
        IloNumVar CompSEC_SR(env, 0.0, IloInfinity, ILOINT); 
        IloNumVar CompCOR_SR(env, 0.0, IloInfinity, ILOINT); 

        IloNumVar SolA_SN(env, 0.0, IloInfinity, ILOINT); 
        IloNumVar SolB_SN(env, 0.0, IloInfinity, ILOINT); 
        IloNumVar CompSEC_SN(env, 0.0, IloInfinity, ILOINT); 
        IloNumVar CompCOR_SN(env, 0.0, IloInfinity, ILOINT); 

        // Objective Function: Minimize Cost
        model.add(IloMinimize(env, 
            cost_per_SolA * (SolA_SR + SolA_SN) + 
            cost_per_SolB * (SolB_SR + SolB_SN) +
            cost_per_CompSEC * (CompSEC_SR + CompSEC_SN) + 
            cost_per_CompCOR * (CompCOR_SR + CompCOR_SN)));

        // Minimum Component Constraints
        model.add(0.3 * SolA_SR + 0.6 * SolB_SR + 1.0 * CompSEC_SR >= 250.0); // SEC in SR
        model.add(0.7 * SolA_SR + 0.4 * SolB_SR + 1.0 * CompCOR_SR >= 500.0); // COR in SR
        
        model.add(0.3 * SolA_SN + 0.6 * SolB_SN + 1.0 * CompSEC_SN >= 50.0);  // SEC in SN
        model.add(0.7 * SolA_SN + 0.4 * SolB_SN + 1.0 * CompCOR_SN >= 125.0); // COR in SN

        // Capacity/Volume Constraints
        model.add(SolA_SR + SolB_SR + CompSEC_SR + CompCOR_SR == 1000.0);
        model.add(SolA_SN + SolB_SN + CompSEC_SN + CompCOR_SN == 250.0);
        
        // Solve the model
        IloCplex cplex(model);
        cplex.setOut(env.getNullStream()); 
        
        cplex.solve();
        
        if (cplex.getStatus() == IloAlgorithm::Optimal) {
            env.out() << "Optimal Solution Found!" << endl;
            env.out() << "------------------------------" << endl;

            env.out() << "Total Cost: R$ " << cplex.getObjValue() << endl;
            env.out() << "SolA in SR: " << cplex.getValue(SolA_SR) << " L" << endl;
            env.out() << "SolB in SR: " << cplex.getValue(SolB_SR) << " L" << endl;
            env.out() << "CompSEC in SR: " << cplex.getValue(CompSEC_SR) << " L" << endl;
            env.out() << "CompCOR in SR: " << cplex.getValue(CompCOR_SR) << " L" << endl;
            env.out() << "SolA in SN: " << cplex.getValue(SolA_SN) << " L" << endl;
            env.out() << "SolB in SN: " << cplex.getValue(SolB_SN) << " L" << endl;
            env.out() << "CompSEC in SN: " << cplex.getValue(CompSEC_SN) << " L" << endl;
            env.out() << "CompCOR in SN: " << cplex.getValue(CompCOR_SN) << " L" << endl;

            env.out() << "------------------------------" << endl;

            env.out() << "Total SolA to buy: " << cplex.getValue(SolA_SR) + cplex.getValue(SolA_SN) << " L" << endl;
            env.out() << "Total SolB to buy: " << cplex.getValue(SolB_SR) + cplex.getValue(SolB_SN) << " L" << endl;
            env.out() << "Total CompSEC to buy: " << cplex.getValue(CompSEC_SR) + cplex.getValue(CompSEC_SN) << " L" << endl;
            env.out() << "Total CompCOR to buy: " << cplex.getValue(CompCOR_SR) + cplex.getValue(CompCOR_SN) << " L" << endl;
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