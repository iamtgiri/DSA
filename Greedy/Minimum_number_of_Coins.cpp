/*
File: Minimum_Number_of_Coins.cpp
Date: 2025-09-21 18:58

Problem: Minimum Number of Coins
Link: https://www.geeksforgeeks.org/problems/-minimum-number-of-coins4426/1

Problem Statement:
Given a value V, find the minimum number of coins/notes needed to make change for V.
Available denominations are: {1, 2, 5, 10, 20, 50, 100, 200, 500, 2000}.
Assume an infinite supply of each denomination.

-------------------------------------------------
❌ Brute Force
- Idea:
  Try all possible combinations recursively. For each coin, either take it or skip it.
- Time complexity: Exponential (O(2^V)).
- Space complexity: O(V) (recursion depth).
- Limitations:
  Impractical for larger values of V.

✅ Optimized Approach (Greedy)
- Idea:
  The given denominations (Indian currency) form a canonical coin system.
  Always take the largest coin ≤ remaining target. This greedy choice is optimal here.
- Algorithm:
  1. Sort coins in descending order.
  2. For each coin, use as many as possible without exceeding the target.
  3. Subtract and continue until target becomes 0.
- Time complexity: O(D), where D = number of denominations.
- Space complexity: O(1) extra (besides result vector).

💡 Key Pattern:
- Greedy algorithm works only with canonical coin systems (like Indian currency).
- For arbitrary denominations, greedy can fail.

⚠️ Counterexample (non-canonical system):
- Coins = {1, 3, 4}, Target = 6
- Greedy → 4 + 1 + 1 = 3 coins
- Optimal → 3 + 3 = 2 coins

ℹ️ Keywords:
Greedy Algorithm, Coin Change, Canonical Coin System

🗒️ Notes:
- Works correctly for Indian currency system.
- Always validate if the coin system supports greedy.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Greedy approach to find the minimum number of coins for a target value.
     * @param target_value Amount to make change for.
     * @return Vector containing selected coins.
     */
    vector<int> minCoins(int target_value)
    {
        // Indian currency denominations in descending order
        vector<int> denominations = {2000, 500, 200, 100, 50, 20, 10, 5, 2, 1};
        vector<int> result;

        for (int coin : denominations)
        {
            while (target_value >= coin)
            {
                target_value -= coin;
                result.push_back(coin);
            }
        }
        return result;
    }

    /**
     * @brief Returns only the minimum count of coins (variant implementation).
     * @param n Amount to make change for.
     * @return Minimum number of coins.
     */
    int findMin(int n)
    {
        vector<int> coins = {10, 5, 2, 1};
        int count = 0, index = 0;

        while (n > 0)
        {
            int curr_coin = coins[index];
            if (n >= curr_coin)
            {
                count += n / curr_coin;
                n %= curr_coin;
            }
            index++;
        }
        return count;
    }
};


int main()
{
    Solution sol;
    int target_value = 93;

    vector<int> coins = sol.minCoins(target_value);

    cout << "To make change for " << target_value << ", coins are: ";
    for (int coin : coins)
        cout << coin << " ";
    cout << "\nTotal number of coins: " << coins.size() << endl;

    return 0;
}
