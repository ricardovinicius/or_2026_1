#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>

// --- Solution Representation ---

struct Bin {
    std::vector<int> items; 
    double cur_weight; 

    Bin() : cur_weight(0) {}

    void addItem(int item_index, double item_weight) {
        items.push_back(item_index);
        cur_weight += item_weight;
    }

    void removeItem(int item_index, double item_weight) {
        items.erase(std::remove(items.begin(), items.end(), item_index), items.end());
        cur_weight -= item_weight;
    }

    bool canAddItem(double item_weight) const {
        return (cur_weight + item_weight <= 1.0);
    }
};

struct Solution {
    std::vector<Bin> bins;

    Solution() {}

    int getNumBins() const {
        return bins.size();
    }
    
    void cleanUpEmptyBins() {
        bins.erase(std::remove_if(bins.begin(), bins.end(), [](const Bin& bin) {
            return bin.items.empty();
        }), bins.end());
    }
};

// --- Solution Evaluation ---

double evaluateSolution(const Solution& solution) {
    int num_bins = solution.getNumBins();
    if (num_bins == 0) return 0;

    double tie_breaker = 0.0;
    for (const auto& bin : solution.bins) {
        tie_breaker += (bin.cur_weight * bin.cur_weight); 
    }
    
    // Primary objective is to minimize bins, secondary is to maximize density (balance weights)
    return num_bins - (tie_breaker / num_bins); 
}

// --- Initial Solution Generation ---

Solution generateInitialSolution(const std::vector<double>& item_weights) {
    Solution solution;
    for (size_t i = 0; i < item_weights.size(); ++i) {
        bool placed = false;
        for (auto& bin : solution.bins) {
            if (bin.canAddItem(item_weights[i])) {
                bin.addItem(i, item_weights[i]);
                placed = true;
                break;
            }
        }
        if (!placed) {
            Bin new_bin;
            new_bin.addItem(i, item_weights[i]);
            solution.bins.push_back(new_bin);
        }
    }
    return solution;
}

// --- Local Search Procedure ---

Solution localSearch(const Solution& initial_solution, const std::vector<double>& item_weights) {
    Solution current_solution = initial_solution;
    bool improvement = true;

    while (improvement) {
        improvement = false;
        double current_score = evaluateSolution(current_solution);
        bool move_applied = false;

        for (size_t i = 0; i < current_solution.bins.size(); ++i) {
            for (size_t j = 0; j < current_solution.bins[i].items.size(); ++j) {
                int item_index = current_solution.bins[i].items[j];
                double item_weight = item_weights[item_index];

                for (size_t k = 0; k < current_solution.bins.size(); ++k) {
                    if (k != i && current_solution.bins[k].canAddItem(item_weight)) {
                        
                        // Safely create a copy to test the move
                        Solution new_solution = current_solution; 
                        new_solution.bins[i].removeItem(item_index, item_weight);
                        new_solution.bins[k].addItem(item_index, item_weight);
                        new_solution.cleanUpEmptyBins();

                        // Evaluate against the current best known score
                        if (evaluateSolution(new_solution) < current_score) {
                            current_solution = new_solution;
                            improvement = true;
                            move_applied = true;
                            break; // Break loop k
                        }
                    }
                }
                if (move_applied) break; // Break loop j
            }
            if (move_applied) break; // Break loop i
        }
    }
    return current_solution;
}

// --- Perturbation Mechanism ---

void perturbation(Solution& solution, const std::vector<double>& item_weights) {
    if (solution.bins.size() <= 1) return; // Cannot perturb a single bin effectively

    int bin_to_perturb = rand() % solution.bins.size();
    
    int target_bin_index = rand() % solution.bins.size();
    while (target_bin_index == bin_to_perturb) {
        target_bin_index = rand() % solution.bins.size();
    }

    // Safely copy items out before modifying the vector
    std::vector<int> items_to_move = solution.bins[bin_to_perturb].items;
    
    for (int item_index : items_to_move) {
        double item_weight = item_weights[item_index];
        
        // Use index access instead of a reference!
        if (solution.bins[target_bin_index].canAddItem(item_weight)) {
            solution.bins[target_bin_index].addItem(item_index, item_weight);
        } else {
            Bin new_bin;
            new_bin.addItem(item_index, item_weight);
            // This push_back may reallocate memory, but since we rely on indices, we are safe.
            solution.bins.push_back(new_bin); 
        }
    }
    
    // Use index access to clear the original bin safely
    solution.bins[bin_to_perturb].items.clear();
    solution.bins[bin_to_perturb].cur_weight = 0;
    
    solution.cleanUpEmptyBins();
}

// --- Stopping Criteria ---

bool shouldStop(const std::chrono::steady_clock::time_point& start_time, int time_limit_seconds) {
    auto current_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();
    return elapsed_time >= time_limit_seconds;
}

// --- Main Execution ---

int main(int argc, char* argv[]) {
    // Setup & CLI Arguments
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <time_limit_seconds>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    int time_limit_seconds = std::stoi(argv[2]);

    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    int n;
    infile >> n;

    std::vector<double> item_weights(n);
    for (int i = 0; i < n; ++i) {
        infile >> item_weights[i];
    }
    infile.close();

    std::cout << "Starting ILS for Bin Packing..." << std::endl;
    std::cout << "Items: " << n << " | Time Limit: " << time_limit_seconds << "s\n" << std::endl;

    srand(time(NULL)); // Seed random number generator
    auto start_time = std::chrono::steady_clock::now();

    // Generate Initial Solution
    Solution current_solution = generateInitialSolution(item_weights);
    current_solution = localSearch(current_solution, item_weights);
    
    Solution best_solution = current_solution;
    double best_score = evaluateSolution(best_solution);

    std::cout << "Initial Best Bins: " << best_solution.getNumBins() << std::endl;

    // The ILS Main Loop
    int iterations = 0;
    while (!shouldStop(start_time, time_limit_seconds)) {
        
        // Perturb the current local optimum
        Solution perturbed_solution = current_solution;
        perturbation(perturbed_solution, item_weights);

        // Apply Local Search
        Solution new_local_optimum = localSearch(perturbed_solution, item_weights);
        double new_score = evaluateSolution(new_local_optimum);

        // Acceptance Criterion (Accept if better or equal to prevent stagnation)
        if (new_score <= evaluateSolution(current_solution)) {
            current_solution = new_local_optimum;
        }

        // Global Best Tracker
        if (new_score < best_score) {
            best_solution = new_local_optimum;
            best_score = new_score;
            std::cout << "[Update] New Best Bins: " << best_solution.getNumBins() 
                      << " at iteration " << iterations << std::endl;
        }
        
        iterations++;
    }

    // Final Output
    std::cout << "\n=== ILS Finished ===" << std::endl;
    std::cout << "Total Iterations: " << iterations << std::endl;
    std::cout << "Final Minimum Bins: " << best_solution.getNumBins() << std::endl;

    // Output the items in each bin
    for (size_t i = 0; i < best_solution.bins.size(); ++i) {
        std::cout << "Bin " << i + 1 << ": ";
        for (int item_index : best_solution.bins[i].items) {
            std::cout << "Item " << item_index + 1 << " (weight: " << item_weights[item_index] << ") ";
        }
        std::cout << std::endl;
    }

    return 0;
}