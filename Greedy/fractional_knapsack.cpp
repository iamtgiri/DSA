/*
File: fractional_knapsack.cpp
Date: 2025-09-21 18:39

Problem: Fractional Knapsack
Link: URL
Problem Statement: Given weights and values of N items, and a knapsack of a specified capacity, find the maximum total value you can get. You can take a fraction of any item.

-------------------------------------------------
❌ Brute Force
- Idea: This problem is a variation of the 0/1 Knapsack, but with the added flexibility of taking fractions. A brute-force approach for the 0/1 knapsack would involve trying every combination of items, which isn't applicable here since we can take fractions. A more relevant brute-force approach might involve iterating through all possible fractional combinations, which is computationally infeasible.
- Time complexity: Not applicable/Infeasible
- Space complexity: Not applicable/Infeasible
- Limitations: Exponential time complexity, making it unviable for practical use.

✅ Optimized Approach
- Idea: The most efficient way to solve the Fractional Knapsack problem is using a greedy strategy. The core idea is to prioritize items that give the most value per unit of weight. This is achieved by calculating the value-to-weight ratio for each item and then greedily picking items in descending order of this ratio. Because we can take fractions, we fill the knapsack completely, either with whole items or a fraction of the last item.
- Time complexity: O(N log N) due to sorting the items by their ratio, which a max-priority queue does implicitly. The loop to fill the knapsack is O(N).
- Space complexity: O(N) to store the items and their ratios in the priority queue.

💡 Key Pattern:
- **Greedy Algorithms**: This problem is a classic example of a greedy algorithm where the locally optimal choice (taking the item with the highest value-to-weight ratio) leads to the globally optimal solution. This works because the problem has the "greedy-choice property" and "optimal substructure."

Keywords:
- Greedy Algorithm, Priority Queue, Knapsack, Value-to-Weight Ratio

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- The Fractional Knapsack problem is fundamentally different from the 0/1 Knapsack problem. The 0/1 Knapsack problem does not exhibit the greedy-choice property and requires dynamic programming.
- The use of a max-priority queue simplifies the greedy choice by automatically keeping the item with the highest ratio at the top.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Solves the Fractional Knapsack problem using a greedy approach.
     * @param val A vector of item values.
     * @param wt A vector of item weights.
     * @param capacity The maximum weight the knapsack can hold.
     * @return The maximum total value achievable.
     */
    double fractionalKnapsack(vector<int> &val, vector<int> &wt, int capacity)
    {
        int n = val.size();

        // Use a max-priority queue to get the item with the highest ratio first.
        // The pair stores {ratio, index}.
        priority_queue<pair<double, int>> ratio_pq;
        for (int i = 0; i < n; ++i)
        {
            double r = static_cast<double>(val[i]) / wt[i];
            ratio_pq.emplace(r, i);
        }

        double total_value = 0.0;

        // Greedily fill the knapsack with items having the highest value-to-weight ratio.
        while (capacity > 0 && !ratio_pq.empty())
        {
            auto [current_ratio, item_index] = ratio_pq.top();
            ratio_pq.pop();

            int current_weight = wt[item_index];
            int current_value = val[item_index];

            // If the current item fits completely.
            if (capacity >= current_weight)
            {
                total_value += current_value;
                capacity -= current_weight;
            }
            // If we can only take a fraction of the current item.
            else
            {
                total_value += current_ratio * capacity;
                capacity = 0; // Knapsack is full.
            }
        }
        return total_value;
    }
};

int main()
{
    Solution sol;

    // Example 1
    vector<int> val1 = {60, 100, 120};
    vector<int> wt1 = {10, 20, 30};
    int capacity1 = 50;
    double result1 = sol.fractionalKnapsack(val1, wt1, capacity1);
    cout << "Example 1 Result: " << result1 << endl; // Expected: 240.0

    // Example 2
    vector<int> val2 = {500, 300};
    vector<int> wt2 = {50, 20};
    int capacity2 = 30;
    double result2 = sol.fractionalKnapsack(val2, wt2, capacity2);
    cout << "Example 2 Result: " << result2 << endl; // Expected: 800.0

    return 0;
}






