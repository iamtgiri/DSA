/*
File: Best_Time_to_Buy_and_Sell_Stock_III.cpp
Date: 2025-09-21 16:20

Problem: Best Time to Buy and Sell Stock III
Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/

Problem Statement:
You are given an array prices where prices[i] is the price of a given stock on the ith day.
Find the maximum profit you can achieve. You may complete at most two transactions.
Note: You must sell before you buy again.

-------------------------------------------------
❌ Brute Force
- Idea: Try all possible pairs of buy/sell for two transactions.
- Time complexity: O(n^4) (choose two subarrays, check profit).
- Space complexity: O(1)
- Limitations: Completely infeasible for n up to 1e5.

✅ Optimized Approach 1 (Two-pass DP)
- Idea:
    1. Compute max profit if we do only ONE transaction in [0..i] → leftProfit[i].
    2. Compute max profit if we do only ONE transaction in [i..n-1] → rightProfit[i].
    3. For each split i, answer = max(leftProfit[i] + rightProfit[i+1]).
- Time complexity: O(n)
- Space complexity: O(n)

✅ Optimized Approach 2 (State Machine DP)
- Idea:
    Maintain 4 states while iterating:
      firstBuy   = best profit after 1st buy
      firstSell  = best profit after 1st sell
      secondBuy  = best profit after 2nd buy
      secondSell = best profit after 2nd sell
    Update them daily:
      firstBuy   = max(firstBuy, -price)
      firstSell  = max(firstSell, firstBuy + price)
      secondBuy  = max(secondBuy, firstSell - price)
      secondSell = max(secondSell, secondBuy + price)
- Time complexity: O(n)
- Space complexity: O(1)

💡 Key Pattern:
- Stock I → prefix/suffix max profits.
- Stock III → combine two Stock I solutions or use state machine.
- State machine scales better to Stock IV, cooldown, and fee variants.

Keywords:
- DP on sequences
- Stock problems
- State compression

🗒️ Notes
- Two-pass DP is more intuitive (split into left/right).
- State machine is more compact (O(1) space) and generalizable.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // Approach 1: Two-pass DP (Left + Right profits)
    int maxProfitTwoPass(vector<int> &prices)
    {
        int n = prices.size();
        if (n == 0)
            return 0;

        vector<int> leftProfit(n, 0);
        vector<int> rightProfit(n + 1, 0);

        // Left profit (best single transaction in [0..i])
        int minPrice = prices[0];
        for (int i = 1; i < n; ++i)
        {
            leftProfit[i] = max(leftProfit[i - 1], prices[i] - minPrice);
            minPrice = min(minPrice, prices[i]);
        }

        // Right profit (best single transaction in [i..n-1])
        int maxPrice = prices[n - 1];
        for (int i = n - 2; i >= 0; --i)
        {
            rightProfit[i] = max(rightProfit[i + 1], maxPrice - prices[i]);
            maxPrice = max(maxPrice, prices[i]);
        }

        // Combine two parts
        int profit = 0;
        for (int i = 0; i < n; ++i)
        {
            profit = max(profit, leftProfit[i] + rightProfit[i + 1]);
        }
        return profit;
    }

    // Approach 2: State Machine DP (O(1) space)
    int maxProfitStateMachine(vector<int> &prices)
    {
        int firstBuy = INT_MIN, firstSell = 0;
        int secondBuy = INT_MIN, secondSell = 0;

        for (int price : prices)
        {
            firstBuy = max(firstBuy, -price);                // buy first
            firstSell = max(firstSell, firstBuy + price);    // sell first
            secondBuy = max(secondBuy, firstSell - price);   // buy second
            secondSell = max(secondSell, secondBuy + price); // sell second
        }

        return secondSell;
    }
};

int main()
{
    Solution sol;
    vector<int> prices1 = {3, 3, 5, 0, 0, 3, 1, 4};
    cout << sol.maxProfitTwoPass(prices1) << "\n";      // Output: 6
    cout << sol.maxProfitStateMachine(prices1) << "\n"; // Output: 6

    vector<int> prices2 = {1, 2, 3, 4, 5};
    cout << sol.maxProfitTwoPass(prices2) << "\n";      // Output: 4
    cout << sol.maxProfitStateMachine(prices2) << "\n"; // Output: 4

    vector<int> prices3 = {7, 6, 4, 3, 1};
    cout << sol.maxProfitTwoPass(prices3) << "\n";      // Output: 0
    cout << sol.maxProfitStateMachine(prices3) << "\n"; // Output: 0

    return 0;
}
