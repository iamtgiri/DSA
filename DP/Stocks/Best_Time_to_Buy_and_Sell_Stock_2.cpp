/*
File: Best_Time_to_Buy_and_Sell_Stock_II.cpp
Date: 2025-09-21 12:55

Problem: Best Time to Buy and Sell Stock II
Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/

Problem Statement:
You are given an array prices where prices[i] is the price of a stock on day i.
You can buy and sell the stock multiple times but can hold at most one share at a time.
Find the maximum profit you can achieve.

-------------------------------------------------
❌ Brute Force
- Idea: Try all possible sequences of buy/sell transactions recursively.
- Time complexity: O(2^n)
- Space complexity: O(n) recursion stack
- Limitations: Exponential time, impractical for large n.

✅ Optimized Approach 1 (Greedy)
- Idea: Add up all positive differences between consecutive days.
  Buy whenever the next day's price is higher than today.
- Time complexity: O(n)
- Space complexity: O(1)

✅ Optimized Approach 2 (DP)
- Idea: Keep track of two states:
  1. hold[i] = max profit if holding a stock on day i
  2. cash[i] = max profit if not holding a stock on day i
- Transition:
    hold[i] = max(hold[i-1], cash[i-1] - price[i])
    cash[i] = max(cash[i-1], hold[i-1] + price[i])
- Time complexity: O(n)
- Space complexity: O(n) → can be optimized to O(1)

💡 Key Pattern:
- Single pass greedy works because multiple transactions can be split into consecutive profitable differences.
- DP is useful when there are additional constraints like cooldowns or transaction fees.

Keywords:
- DP on sequences
- Greedy
- Stock problems
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // Greedy approach: sum up all consecutive gains
    int maxProfitGreedy(vector<int> &prices)
    {
        int profit = 0;
        for (int i = 1; i < prices.size(); ++i)
        {
            if (prices[i] > prices[i - 1])
                profit += prices[i] - prices[i - 1];
        }
        return profit;
    }

    // DP approach: track cash and hold states
    int maxProfitDP(vector<int> &prices)
    {
        int n = prices.size();
        if (n == 0)
            return 0;

        int hold = -prices[0]; // max profit holding stock on day 0
        int cash = 0;          // max profit not holding stock on day 0

        for (int i = 1; i < n; ++i)
        {
            int prevCash = cash;
            cash = max(cash, hold + prices[i]);     // sell today or do nothing
            hold = max(hold, prevCash - prices[i]); // buy today or do nothing
        }

        return cash;
    }
};

int main()
{
    Solution sol;

    vector<int> prices1 = {7, 1, 5, 3, 6, 4};
    cout << "Max Profit (Greedy): " << sol.maxProfitGreedy(prices1) << "\n"; // 7
    cout << "Max Profit (DP): " << sol.maxProfitDP(prices1) << "\n";         // 7

    vector<int> prices2 = {1, 2, 3, 4, 5};
    cout << "Max Profit (Greedy): " << sol.maxProfitGreedy(prices2) << "\n"; // 4
    cout << "Max Profit (DP): " << sol.maxProfitDP(prices2) << "\n";         // 4

    vector<int> prices3 = {7, 6, 4, 3, 1};
    cout << "Max Profit (Greedy): " << sol.maxProfitGreedy(prices3) << "\n"; // 0
    cout << "Max Profit (DP): " << sol.maxProfitDP(prices3) << "\n";         // 0

    return 0;
}
