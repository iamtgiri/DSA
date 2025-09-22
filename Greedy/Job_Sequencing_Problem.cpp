/*
File: Job_Sequencing_Problem.cpp
Date: 2025-09-22 19:05

Problem: Job Sequencing Problem
Link: https://www.geeksforgeeks.org/problems/job-sequencing-problem-1587115620/1

Problem Statement:
You are given two arrays: deadline[], and profit[], which represent a set of jobs,
where each job is associated with a deadline, and a profit. Each job takes 1 unit of time
to complete, and only one job can be scheduled at a time. You will earn the profit
associated with a job only if it is completed by its deadline.

Your task is to find:
1. The maximum number of jobs that can be completed within their deadlines.
2. The total maximum profit earned by completing those jobs.

-------------------------------------------------
❌ Brute Force
- Idea: Try all possible schedules and calculate profit. Keep the best.
- Time complexity: O(n!), infeasible for n > 15.
- Space complexity: O(1).
- Limitations: Too slow for practical input sizes.

✅ Optimized Greedy Approach 1 (Naive Slot Allocation)
- Idea: Jobs with higher profit should be scheduled earlier, if possible.
- Approach:
  1. Pair jobs as (profit, deadline).
  2. Sort jobs by profit in descending order.
  3. Maintain a slot array to track scheduled jobs.
  4. For each job, place it in the latest available slot ≤ its deadline.
- Time complexity: O(n log n + n * maxDeadline) ≈ O(n²) in worst case.
- Space complexity: O(maxDeadline).

✅ Optimized Greedy Approach 2 (DSU + Greedy)
- Idea: Use Disjoint Set Union (Union-Find) to find the latest available free slot quickly.
- Approach:
  1. Pair jobs as (profit, deadline).
  2. Sort jobs by profit in descending order.
  3. Initialize DSU parent[] where parent[x] = latest free slot ≤ x.
  4. For each job, find the latest available slot with DSU.
  5. If available, schedule job and union(slot, slot-1).
- Time Complexity: O(n log n) (sorting dominates).
- Space Complexity: O(maxDeadline).

💡 Key Pattern:
- Greedy scheduling
- Interval/slot allocation
- Sorting by "value priority" (profit)

ℹ️ Keywords:
- Greedy Algorithm, Job Sequencing, Sorting, Scheduling, Deadlines

🗒️ Notes
- Learned the importance of scheduling jobs at the *latest free slot* before deadline.
- Initial mistake: naïve deadline checking caused inefficiency (TLE).
- Similar problems: Activity Selection Problem, N Meetings in One Room.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

/// @brief Comparator to sort jobs by profit (descending).
bool comp(pair<int, int> a, pair<int, int> b)
{
    return a.first > b.first;
}

class Solution
{
public:
    /**
     * @brief Greedy solution with slot allocation (O(n²) in worst case).
     * @param deadline A vector of job deadlines.
     * @param profit A vector of job profits.
     * @return {number of jobs done, total profit}.
     */
    vector<int> jobSequencing(vector<int> &deadline, vector<int> &profit)
    {
        int n = profit.size();
        vector<pair<int, int>> jobs;
        for (int i = 0; i < n; ++i)
        {
            jobs.emplace_back(profit[i], deadline[i]); // (profit, deadline)
        }

        // Sort jobs by profit descending
        sort(jobs.begin(), jobs.end(), comp);

        int maxDeadline = *max_element(deadline.begin(), deadline.end());
        vector<int> slot(maxDeadline + 1, -1); // -1 = free slot

        int total_jobs = 0, total_profit = 0;

        for (auto [p, d] : jobs)
        {
            // Find the latest free slot before or on deadline d
            for (int t = d; t > 0; --t)
            {
                if (slot[t] == -1)
                {
                    slot[t] = p; // schedule job
                    total_jobs++;
                    total_profit += p;
                    break;
                }
            }
        }

        return {total_jobs, total_profit};
    }

    /**
     * @brief Optimized Greedy + DSU solution (O(n log n)).
     * @param deadline A vector of job deadlines.
     * @param profit A vector of job profits.
     * @return {number of jobs done, total profit}.
     */
    vector<int> jobSequencingOpt(vector<int> &deadline, vector<int> &profit)
    {
        int n = profit.size();
        vector<pair<int, int>> jobs;
        for (int i = 0; i < n; ++i)
        {
            jobs.emplace_back(profit[i], deadline[i]); // (profit, deadline)
        }

        // Sort jobs by profit descending
        sort(jobs.rbegin(), jobs.rend());

        int maxDeadline = *max_element(deadline.begin(), deadline.end());

        // DSU parent array
        vector<int> parent(maxDeadline + 1);
        iota(parent.begin(), parent.end(), 0);

        int total_jobs = 0, total_profit = 0;

        for (auto [p, d] : jobs)
        {
            int available = find(parent, d);
            if (available > 0)
            {
                // Assign job to slot `available`
                total_jobs++;
                total_profit += p;
                // Merge this slot with the previous one
                parent[available] = find(parent, available - 1);
            }
        }

        return {total_jobs, total_profit};
    }

private:
    /// @brief DSU find with path compression.
    int find(vector<int> &parent, int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent, parent[x]);
    }
};

int main()
{
    Solution sol;

    vector<int> d1 = {4, 1, 1, 1};
    vector<int> p1 = {20, 10, 40, 30};
    auto res1 = sol.jobSequencing(d1, p1);
    cout << "Example 1 (Naive) -> Jobs: " << res1[0] << ", Profit: " << res1[1] << endl;

    vector<int> d2 = {2, 1, 2, 1, 1};
    vector<int> p2 = {100, 19, 27, 25, 15};
    auto res2 = sol.jobSequencingOpt(d2, p2);
    cout << "Example 2 (Optimized) -> Jobs: " << res2[0] << ", Profit: " << res2[1] << endl;

    vector<int> d3 = {3, 1, 2, 2};
    vector<int> p3 = {50, 10, 20, 30};
    auto res3 = sol.jobSequencingOpt(d3, p3);
    cout << "Example 3 (Optimized) -> Jobs: " << res3[0] << ", Profit: " << res3[1] << endl;

    return 0;
}
