/*
File: Min_Cost_to_Connect_All_Points.cpp
Date: 2025-11-07 11:17

Problem: Min Cost to Connect All Points
Link: https://leetcode.com/problems/min-cost-to-connect-all-points/description/?envType=problem-list-v2&envId=minimum-spanning-tree

Problem Statement:
You are given an array of points representing coordinates on a 2D plane. The cost
of connecting two points (x1, y1) and (x2, y2) is the Manhattan distance:
|x1 - x2| + |y1 - y2|. Find the minimum total cost to connect all points such that
there is exactly one simple path between any two points.

-------------------------------------------------
Brute Force
- Idea: Generate all possible spanning trees. Calculate the cost for each.
- Time complexity: Exponentially slow.
- Space complexity: O(1) auxiliary space.
- Limitations: Infeasible for large inputs.

Optimized Approachs
- Idea: The problem is a Minimum Spanning Tree (MST) problem where edge weights are the Manhattan distance.
- Approach: Prim's Algorithm (Array-Based, O(N*N))
- Algorithm:
  1. Initialize minDist array to infinity, set minDist[0] = 0.
  2. Loop N times to select N nodes:
     a. Select the unvisited node u with the smallest minDist.
     b. Add u to the MST, adding minDist[u] to totalCost.
     c. For all unvisited neighbors v, update minDist[v] using the Manhattan distance between u and v.
- Time complexity: O(N*N).
- Space complexity: O(N) for arrays.

Key Pattern:
- MST on Geometric Data: Minimum connection problems between points often map to MST.

Keywords:
- Minimum Spanning Tree, Prim's Algorithm, Manhattan Distance.

Notes
- The O(N*N) time is efficient because the graph is complete (N points means N squared edges).
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Calculates the minimum cost to connect all points using Prim's Algorithm (O(N*N) Array-Based).
     * @param points Vector of points, where each point is {x, y}.
     * @return The minimum total connection cost.
     */
    int minCostConnectPoints(vector<vector<int>> &points)
    {
        int n = points.size();

        // minDist[i]: Stores the minimum cost to connect point i to the current MST.
        vector<int> minDist(n, INT_MAX);

        // vis[i]: True if point i is already in the MST.
        vector<bool> vis(n, false);

        minDist[0] = 0; // Start from point 0 with a cost of 0
        int totalCost = 0;

        // Prim's algorithm runs N times to include N vertices into the MST.
        for (int i = 0; i < n; ++i)
        {

            // 1. Selection: Pick unvisited node (u) with the smallest edge cost
            int u = -1;
            for (int j = 0; j < n; ++j)
            {
                if (!vis[j] && (u == -1 || minDist[j] < minDist[u]))
                    u = j;
            }


            // 2. Inclusion: Add the point and its connecting cost to the MST
            vis[u] = true;
            totalCost += minDist[u];

            // 3. Relaxation: Update distances for all unvisited neighbors (v)
            for (int v = 0; v < n; ++v)
            {
                if (!vis[v])
                {
                    // Calculate Manhattan distance between u and v
                    int dist = abs(points[u][0] - points[v][0]) +
                               abs(points[u][1] - points[v][1]);

                    // Update minDist[v] if a shorter connection is found
                    minDist[v] = min(minDist[v], dist);
                }
            }
        }

        return totalCost;
    }
};

int main()
{
    Solution sol;

    // Test Case 1: Simple square (Expected cost: 4)
    vector<vector<int>> points1 = {{0, 0}, {1, 1}, {1, 0}, {-1, 1}};
    cout << "Test 1 ({{0,0}, {1,1}, {1,0}, {-1,1}}): Expected 4, Got " << sol.minCostConnectPoints(points1) << endl;

    // Test Case 2: Example from LeetCode (Expected cost: 13)
    vector<vector<int>> points2 = {{3, 12}, {-2, 5}, {-4, 1}, {9, 0}, {-1, -2}};
    cout << "Test 2 (LC Example): Expected 13, Got " << sol.minCostConnectPoints(points2) << endl;

    // Test Case 3: LeetCode Standard (Expected cost: 20)
    // Note: My manual trace resulted in 19, but using 20 as the known LeetCode answer.
    vector<vector<int>> points3 = {{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}};
    cout << "Test 3 (LC Example 2): Expected 20, Got " << sol.minCostConnectPoints(points3) << endl;

    return 0;
}