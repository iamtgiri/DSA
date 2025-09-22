/*
File: Shop_in_Candy_Store.cpp
Date: 2025-09-22 15:22

Problem: Shop in Candy Store
Link: https://www.geeksforgeeks.org/problems/shop-in-candy-store1145/1
Problem Statement:
In a candy store, there are different types of candies available and prices[i]
represent the price of  ith types of candies. You are now provided with an
attractive offer. For every candy you buy from the store, you can get up to k
other different candies for free. Find the minimum and maximum amount of money
needed to buy all the candies. Note: In both cases, you must take the maximum
number of free candies possible during each purchase.

Examples :

    Input: prices[] = [3, 2, 1, 4], k = 2
    Output: [3, 7]
    Explanation: As according to the offer if you buy one candy you can take at most k
    more for free. So in the first case, you buy the candy worth 1 and takes candies
    worth 3 and 4 for free, also you need to buy candy worth 2. So min cost: 1+2 = 3.
    In the second case, you can buy the candy worth 4 and takes candies worth 1 and 2
    for free, also you need to buy candy worth 3. So max cost: 3+4 = 7.

    Input: prices[] = [3, 2, 1, 4, 5], k = 4
    Output: [1, 5]
    Explanation: For minimimum cost buy the candy with the cost 1 and get all the other
    candies for free. For maximum cost buy the candy with the cost 5 and get all other
    candies for free.
-------------------------------------------------
❌ Brute Force
- Idea: The brute force approach would involve generating all possible
combinations of purchases and free candies, then calculating the cost for each
combination to find the minimum and maximum.
- Time complexity: Exponential, highly inefficient.
- Space complexity: O(N) for recursion stack.
- Limitations: This is not feasible for large N.

✅ Optimized Approachs
- Idea: This problem is a classic greedy problem. To minimize the total cost, we
should always buy the cheapest candies and get the most expensive ones for free.
To maximize the total cost, we should always buy the most expensive candies and
get the cheapest ones for free.
- Approach: A greedy, two-pointer algorithm on a sorted array.
- Algorithm:
  1. Sort the `prices` array in non-decreasing order.
  2. To calculate **minimum cost**:
     - Iterate from the cheapest candy (start of the array).
     - For each candy purchased, add its price to the `min_cost`.
     - Use the offer to get `k` free candies from the end of the array (most expensive).
     - This is done by decrementing an `end` pointer by `k` for each purchase.
  3. To calculate **maximum cost**:
     - Iterate from the most expensive candy (end of the array).
     - For each candy purchased, add its price to the `max_cost`.
     - Use the offer to get `k` free candies from the start of the array (cheapest).
     - This is done by incrementing a `start` pointer by `k` for each purchase.
  4. Return the calculated minimum and maximum costs.
- Time complexity: O(N log N) dominated by the initial sorting step.
- Space complexity: O(1) if sorting is done in-place.

💡 Key Pattern:
- **Greedy Algorithms with Sorting**: When a problem involves minimizing or
maximizing a sum from a list, sorting the list and then making greedy choices from
either end is a common and effective pattern.

ℹ️ Keywords:
- Greedy Algorithm, Sorting, Two Pointers, Minimum Cost, Maximum Cost

🗒️ Notes
- The problem constraints ensure that we can always buy all candies. The core
insight is recognizing that the greedy strategy (either buying cheapest or most
expensive) is optimal because the choice at each step doesn't negatively impact
future optimal choices.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Calculates the minimum and maximum cost to buy all candies.
     * @param prices A vector of integers representing the prices of candies.
     * @param k The number of free candies for each purchase.
     * @return A vector of two integers: {min_cost, max_cost}.
     */
    vector<int> minMaxCandy(vector<int> &prices, int k)
    {
        int n = prices.size();
        
        // Sort the prices to apply greedy strategy.
        sort(prices.begin(), prices.end());

        int min_cost = 0;
        int max_cost = 0;

        // Calculate minimum cost: buy cheapest, get most expensive for free.
        int start_min = 0;
        int end_min = n - 1;
        while (start_min <= end_min)
        {
            min_cost += prices[start_min++];
            end_min -= k;
        }

        // Calculate maximum cost: buy most expensive, get cheapest for free.
        int start_max = 0;
        int end_max = n - 1;
        while (start_max <= end_max)
        {
            max_cost += prices[end_max--];
            start_max += k;
        }

        return {min_cost, max_cost};
    }
};

int main()
{
    Solution sol;
    
    // Example 1
    vector<int> prices1 = {3, 2, 1, 4};
    int k1 = 2;
    vector<int> result1 = sol.minMaxCandy(prices1, k1);
    cout << "Example 1: Min cost = " << result1[0] << ", Max cost = " << result1[1] << endl;
    
    // Example 2
    vector<int> prices2 = {3, 2, 1, 4, 5};
    int k2 = 4;
    vector<int> result2 = sol.minMaxCandy(prices2, k2);
    cout << "Example 2: Min cost = " << result2[0] << ", Max cost = " << result2[1] << endl;

    return 0;
}