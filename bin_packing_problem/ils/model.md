# Meta-Heuristic Solution: Iterated Local Search (ILS)

## Solution Representation
In the context of the Bin Packing Problem, a solution can be represented as a list of bins, where each bin contains a subset of items. For example, if we have 5 items and 3 bins, a solution could be represented as:
```
Bin 1: {Item 1, Item 3}
Bin 2: {Item 2}
Bin 3: {Item 4, Item 5}
```

To facilitate the implementation of the ILS algorithm, we can represent the bins as a struct:
```cpp
struct Bin {
    std::vector<int> items; // List of item indices in this bin
    double cur_weight; // Total weight of items in this bin

    Bin() : cur_weight(0) {}

    // Function to add an item to the bin
    void addItem(int item_index, double item_weight) {
        items.push_back(item_index);
        cur_weight += item_weight;
    }

    // Function to remove an item from the bin
    void removeItem(int item_index, double item_weight) {
        items.erase(std::remove(items.begin(), items.end(), item_index), items.end());
        cur_weight -= item_weight;
    }

    // Function to check if an item can be added without exceeding capacity
    bool canAddItem(double item_weight) {
        return (cur_weight + item_weight <= 1.0);
    }
};
```

And the overall solution can be represented as another struct that contains a list of bins:
```cpp
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
```

## Solution Evaluation
The evaluation of a solution in the Bin Packing Problem is straightforward: we want to minimize the number of bins used. Therefore, the objective function can be defined as:
```cpp
int evaluateSolution(const Solution& solution) {
    return solution.getNumBins();
}
```

Additionally, we can add a tie-breaking mechanism based on the sum of the squares of the weights in the bins to encourage more balanced solutions:
```cpp
double evaluateSolution(const Solution& solution) {
    int num_bins = solution.getNumBins();
    double tie_breaker = 0.0;
    for (const auto& bin : solution.bins) {
        tie_breaker += bin.cur_weight * bin.cur_weight; // Sum of squares of weights
    }
    return num_bins - (tie_breaker / num_bins); // Primary objective is to minimize bins, secondary is to balance weights
}
```


## Initial Solution Generation
To generate an initial solution, we can use a simple heuristic such as the First-Fit algorithm. This algorithm iterates through the items and places each item in the first bin that has enough remaining capacity to accommodate it. If no such bin exists, a new bin is created for that item.
```cpp
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
```

## Neighborhood Structure

In the ILS algorithm, we need to define a neighborhood structure that allows us to explore the solution space. For the Bin Packing Problem, we can define the neighborhood as follows:
1. **Move an item from one bin to another**: This involves selecting an item from a bin and trying to place it in a different bin that has enough capacity.
2. **Swap items between two bins**: This involves selecting an item from one bin and swapping it with an item from another bin, provided that the swap does not violate the capacity constraints of either bin.
3. **Merge two bins**: This involves selecting two bins and merging their contents into a single bin, provided that the total weight of the merged bin does not exceed the capacity.

We gonna use the first neighborhood structure (moving an item from one bin to another) for our ILS implementation. This allows us to explore the solution space effectively while maintaining feasibility of the solutions.

## Local Search Procedure
The local search procedure involves iterating through the neighborhood of the current solution and evaluating each neighbor. If a neighbor has a better objective value (i.e., uses fewer bins), we move to that neighbor and continue the search from there. This process continues until no better solution is found in the neighborhood.
```cpp
Solution localSearch(const Solution& initial_solution) {
    Solution current_solution = initial_solution;
    bool improvement = true;

    while (improvement) {
        improvement = false;
        for (size_t i = 0; i < current_solution.bins.size(); ++i) {
            for (size_t j = 0; j < current_solution.bins[i].items.size(); ++j) {
                int item_index = current_solution.bins[i].items[j];
                double item_weight = item_weights[item_index];

                // Try to move the item to another bin
                for (size_t k = 0; k < current_solution.bins.size(); ++k) {
                    if (k != i && current_solution.bins[k].canAddItem(item_weight)) {
                        // Move the item
                        Solution new_solution = current_solution; // Create a copy of the current solution
                        new_solution.bins[i].removeItem(item_index, item_weight);
                        new_solution.bins[k].addItem(item_index, item_weight);
                        new_solution.cleanUpEmptyBins();

                        // Evaluate the new solution
                        if (evaluateSolution(new_solution) < evaluateSolution(initial_solution)) {
                            improvement = true;
                            current_solution = new_solution;
                            break; // Exit the loop to start from the new solution
                        } else {
                            // Move back the item if no improvement
                            current_solution.bins[k].removeItem(item_index, item_weight);
                            current_solution.bins[i].addItem(item_index, item_weight);
                            current_solution.cleanUpEmptyBins();
                        }
                    }
                    if (improvement) break;
                }
                if (improvement) break;
            }
            if (improvement) break;
        }
    }
    return current_solution;
}
```

## Perturbation Mechanism (part of ILS)
In the ILS algorithm, after performing a local search, we apply a perturbation to the current solution to escape local optima. The perturbation can be defined as a random move that significantly alters the current solution. For example, we can randomly select a bin and move all its items to another bin, or we can randomly shuffle the items in a few bins.
```cpp
void perturbation(Solution& solution) {
    // Randomly select a bin to perturb
    int bin_to_perturb = rand() % solution.bins.size();
    Bin& bin = solution.bins[bin_to_perturb];

    // Move all items from the selected bin to another random bin
    int target_bin_index = rand() % solution.bins.size();
    while (target_bin_index == bin_to_perturb) {
        target_bin_index = rand() % solution.bins.size();
    }
    Bin& target_bin = solution.bins[target_bin_index];

    for (int item_index : bin.items) {
        double item_weight = item_weights[item_index];
        if (target_bin.canAddItem(item_weight)) {
            target_bin.addItem(item_index, item_weight);
        } else {
            // If the target bin cannot accommodate the item, we can either skip it or create a new bin
            Bin new_bin;
            new_bin.addItem(item_index, item_weight);
            solution.bins.push_back(new_bin);
        }
    }
    // Clear the original bin after moving its items
    bin.items.clear();
    bin.cur_weight = 0;
}
```

## Stopping Criteria
The ILS algorithm can be stopped based on several criteria, such as:
1. A maximum number of iterations is reached.
2. A certain amount of time has elapsed.
3. No improvement is found after a certain number of iterations.

For our implementation, as required by the assignment, we will use a limit of time (e.g., 60 seconds) as the stopping criterion. We can implement this using a timer to track the elapsed time during the execution of the algorithm.

```cpp
#include <chrono>

bool shouldStop(const std::chrono::steady_clock::time_point& start_time, int time_limit_seconds) {
    auto current_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();
    return elapsed_time >= time_limit_seconds;
}
```