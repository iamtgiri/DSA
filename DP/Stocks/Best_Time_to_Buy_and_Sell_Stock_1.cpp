/*
File: Best_Time_to_Buy_and_Sell_Stock_1.cpp
Date: 2025-09-21 12:41

Problem: Best Time to Buy and Sell Stock I
Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

Problem Statement:
Given an array prices where prices[i] is the price of a given stock on day i,
find the maximum profit you can achieve. You may complete at most one transaction
(i.e., buy one and sell one share of the stock). You cannot sell a stock before you buy one.

Example 1:
    Input: prices = [7,1,5,3,6,4]
    Output: 5
    Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
    Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

Example 2:
    Input: prices = [7,6,4,3,1]
    Output: 0
    Explanation: In this case, no transactions are done and the max profit = 0.

-------------------------------------------------
❌ Brute Force
- Idea: Try all possible pairs of buy and sell days.
- Time complexity: O(n^2)
- Space complexity: O(1)
- Limitations: Inefficient for large input arrays.

✅ Optimized Approach 1 (Dynamic Programming / Prefix Minimum)
- Idea: Track the minimum price so far and compute the max profit at each day.
- Time complexity: O(n)
- Space complexity: O(n) for DP array, can be optimized to O(1)

✅ Optimized Approach 2 (Greedy / Single Pass)
- Idea: Track the minimum price while iterating and update the max profit.
- Time complexity: O(n)
- Space complexity: O(1)

💡 Key Pattern:
- Maintain running minimum (or maximum) while iterating to avoid nested loops.
- Classic single-transaction stock DP problem.

Keywords:
- DP on sequences
- Greedy
- Stock problems

🗒️ Notes:
- Can optimize DP array to single variable since only the previous value is used.
- Approach generalizes to other stock variants with multiple transactions or constraints.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // DP approach with O(n) space
    int maxProfitDP(vector<int> &prices)
    {
        int n = prices.size();
        if (n == 0) return 0;

        vector<int> dp(n); // dp[i] = max profit until day i
        dp[0] = 0;
        int minPrice = prices[0];

        for (int i = 1; i < n; ++i)
        {
            dp[i] = max(dp[i - 1], prices[i] - minPrice);
            minPrice = min(minPrice, prices[i]);
        }

        return dp[n - 1];
    }

    // Greedy approach with O(1) space
    int maxProfitGreedy(vector<int> &prices)
    {
        int n = prices.size();
        if (n == 0) return 0;

        int profit = 0;
        int minPrice = prices[0];

        for (int i = 1; i < n; ++i)
        {
            profit = max(profit, prices[i] - minPrice);
            minPrice = min(minPrice, prices[i]);
        }

        return profit;
    }
};

int main()
{
    Solution sol;

    vector<int> prices1 = {7, 1, 5, 3, 6, 4};
    cout << "Max Profit (DP): " << sol.maxProfitDP(prices1) << "\n";
    cout << "Max Profit (Greedy): " << sol.maxProfitGreedy(prices1) << "\n";

    vector<int> prices2 = {7, 6, 4, 3, 1};
    cout << "Max Profit (DP): " << sol.maxProfitDP(prices2) << "\n";
    cout << "Max Profit (Greedy): " << sol.maxProfitGreedy(prices2) << "\n";

    return 0;
}
