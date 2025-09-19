/*
File: Ninja_Training.cpp
Date: 2025-09-19 23:25

Problem: Ninja's Training
Link: https://www.geeksforgeeks.org/problems/geeks-training/1

Problem Statement:
Ninja can perform 3 activities each day: Running, Fighting, or Learning.
Each activity gives some merit points on each day, but Ninja cannot do the same
activity on consecutive days. Find the maximum merit points after n days.

-------------------------------------------------
❌ Brute Force (Recursion)
- Idea: Try all possibilities of picking an activity each day (except previous).
- Time complexity: O(3^n) -> exponential.
- Space complexity: O(n) recursion stack.
- Limitations: Too slow for n up to 1e5.

✅ Optimized Approach (DP)
- Idea: Use DP with state [day][last] where last is previous activity.
- Time complexity: O(n * 4 * 3) = O(n).
- Space complexity: O(n*4) for memo/tabulation, optimized to O(4).

💡 Key Pattern:
- "Pick an option but not equal to last choice" → DP with extra state.
- Same as "House Robber with 3 choices per day".

Keywords:
- DP on grids, choices, last activity constraint.

🗒️ Notes
- Learned how recursion → memoization → tabulation → space-optimization chain works.
- Similar to Geek's Training / Ninja's Training problem.
- Mistake I made: tried greedy, but greedy fails because local max ≠ global max.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // ----------------- 1. Pure Recursion -----------------
    int solveRec(int day, int last, vector<vector<int>> &arr)
    {
        if (day == 0)
        {
            int best = 0;
            for (int task = 0; task < 3; task++)
            {
                if (task != last)
                    best = max(best, arr[0][task]);
            }
            return best;
        }

        int best = 0;
        for (int task = 0; task < 3; task++)
        {
            if (task != last)
            {
                best = max(best, arr[day][task] + solveRec(day - 1, task, arr));
            }
        }
        return best;
    }

    // ----------------- 2. Memoization (Top-Down) -----------------
    int solveMem(int day, int last, vector<vector<int>> &arr, vector<vector<int>> &dp)
    {
        if (day == 0)
        {
            int best = 0;
            for (int task = 0; task < 3; task++)
            {
                if (task != last)
                    best = max(best, arr[0][task]);
            }
            return dp[0][last] = best;
        }

        if (dp[day][last] != -1)
            return dp[day][last];

        int best = 0;
        for (int task = 0; task < 3; task++)
        {
            if (task != last)
            {
                best = max(best, arr[day][task] + solveMem(day - 1, task, arr, dp));
            }
        }
        return dp[day][last] = best;
    }

    // ----------------- 3. Tabulation (Bottom-Up DP) -----------------
    int solveTab(vector<vector<int>> &arr)
    {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(4, 0));

        // Base case (day 0)
        dp[0][0] = max(arr[0][1], arr[0][2]);              // last = 0 → can't do 0
        dp[0][1] = max(arr[0][0], arr[0][2]);              // last = 1 → can't do 1
        dp[0][2] = max(arr[0][0], arr[0][1]);              // last = 2 → can't do 2
        dp[0][3] = max({arr[0][0], arr[0][1], arr[0][2]}); // no restriction

        // Fill table
        for (int day = 1; day < n; day++)
        {
            for (int last = 0; last < 4; last++)
            {
                int best = 0;
                for (int task = 0; task < 3; task++)
                {
                    if (task != last)
                    {
                        best = max(best, arr[day][task] + dp[day - 1][task]);
                    }
                }
                dp[day][last] = best;
            }
        }

        return dp[n - 1][3]; // no restriction
    }

    // ----------------- 4. Space Optimization -----------------
    int solveSpaceOpt(vector<vector<int>> &arr)
    {
        int n = arr.size();
        vector<int> prev(4, 0), curr(4, 0);

        // Base case (day 0)
        for (int last = 0; last < 4; last++)
        {
            int best = 0;
            for (int task = 0; task < 3; task++)
            {
                if (task != last)
                    best = max(best, arr[0][task]);
            }
            prev[last] = best;
        }

        for (int day = 1; day < n; day++)
        {
            for (int last = 0; last < 4; last++)
            {
                int best = 0;
                for (int task = 0; task < 3; task++)
                {
                    if (task != last)
                    {
                        best = max(best, arr[day][task] + prev[task]);
                    }
                }
                curr[last] = best;
            }
            prev = curr;
        }

        return prev[3]; // no restriction
    }

    // ----------------- Wrapper -----------------
    int maximumPoints(vector<vector<int>> &arr)
    {
        int n = arr.size();

        // 1. Recursion (⚠ exponential, for learning only)
        // return solveRec(n-1, 3, arr);

        // 2. Memoization
        vector<vector<int>> dp(n, vector<int>(4, -1));
        return solveMem(n - 1, 3, arr, dp);

        // 3. Tabulation
        // return solveTab(arr);

        // 4. Space Optimization
        // return solveSpaceOpt(arr);
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> arr1 = {{1, 2, 5}, {3, 1, 1}, {3, 3, 3}};
    cout << sol.maximumPoints(arr1) << "\n"; // 11

    vector<vector<int>> arr2 = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    cout << sol.maximumPoints(arr2) << "\n"; // 6

    vector<vector<int>> arr3 = {{4, 2, 6}};
    cout << sol.maximumPoints(arr3) << "\n"; // 6

    return 0;
}
