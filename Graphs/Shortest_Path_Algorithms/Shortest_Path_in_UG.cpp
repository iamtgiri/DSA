/*
File: Shortest_Path_in_UG.cpp
Date: 2025-10-29 22:40

Problem: Shortest Path in Undirected Graph
Link: https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph-having-unit-distance/1

Problem Statement:
Given an undirected graph where all edges have a unit distance (weight of 1),
find the shortest distance from a given source node to all other nodes.
If a node is unreachable, its distance should be -1.

--------------------------------------------------------------------------------------------------
❌ Brute Force
- Idea: Use Depth First Search (DFS) or a recursive approach to explore all
  possible paths from the source to every other node and track the minimum
  distance found so far.
- Time complexity: O(N^N) in the worst case without proper cycle checking/optimization,
  or O(N * E) if using memoization but still inefficiently exploring.
- Space complexity: O(N) for recursion stack and distance tracking.
- Limitations: Highly inefficient due to redundant exploration of paths and
  failure to leverage the unit-distance property.

✅ Optimized Approachs
- Idea: Since all edge weights are uniform (1), Breadth-First Search (BFS) is guaranteed
  to find the shortest path to any reachable node upon its first visit.
  It explores the graph layer by layer (distance 0, then 1, then 2, etc.).
- Approach: Breadth-First Search (BFS).
- Algorithm:
    1. Initialization: Initialize a distance array (`dist`) with -1 (or infinity)
       for all nodes and a visited array (`vis`).
    2. Queue Setup: Start BFS by pushing the source node and its distance (0)
       into a queue (e.g., `queue<pair<int, int>>`). Mark the source as visited.
    3. BFS Loop: While the queue is not empty:
        - Dequeue the current node and its distance (`d`).
        - Set `dist[node] = d`.
        - For every unvisited neighbor (`nei`):
            - Mark `nei` as visited.
            - Enqueue `(nei, d + 1)`.
    4. Result: The `dist` array contains the shortest distance to all nodes.
- Time complexity: O(N + E), where N is the number of vertices and E is the number of edges.
  This is optimal for graph traversal.
- Space complexity: O(N + E) for the adjacency list, distance array, and queue.

💡 Key Pattern:
- Shortest Path in Unweighted Graph: Always solvable by BFS.

ℹ️ Keywords:
- Unweighted Graph, Unit Distance, Breadth-First Search (BFS), Shortest Path.

🗒️ Notes
- The use of the `visited` array is crucial for preventing cycles and ensuring that a
  node is processed only once, which guarantees its distance is the shortest possible.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Computes the shortest path distance from a source node to all other
     * nodes in an undirected graph with unit-distance edges.
     * @param adj The adjacency list of the graph (adj[i] contains neighbors of i).
     * @param src The source node (0-based index).
     * @return A vector of integers where the element at index i is the shortest
     * distance from src to i, or -1 if unreachable.
     */
    vector<int> shortestPath(vector<vector<int>> &adj, int src)
    {
        // n is the number of vertices
        int n = adj.size();
        // dist initialized to -1 (representing unreachable)
        vector<int> dist(n, -1);
        vector<bool> vis(n, false);

        // Queue stores {node, distance}
        queue<pair<int, int>> q;
        q.push({src, 0});
        vis[src] = true;

        while (!q.empty())
        {
            // C++17 structured binding for clarity
            auto [node, d] = q.front();
            q.pop();
            dist[node] = d; // Found shortest distance to this node

            for (int nei : adj[node])
            {
                if (!vis[nei])
                {
                    vis[nei] = true;
                    // Distance to neighbor is one more than current node's distance
                    q.push({nei, d + 1});
                }
            }
        }
        return dist;
    }
};

// Helper function to print a vector of integers
void printVector(const vector<int> &vec)
{
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        cout << vec[i];
        if (i < vec.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << "]";
}

int main()
{
    Solution sol;

    cout << "--- Shortest Path in Undirected Unit-Distance Graph ---\n";

    // Test Case 1: Simple Path with Disconnected Component
    // Graph with 8 nodes (0 to 7)
    // Component 1: 0 - 1 - 2
    // Component 2: 3 - 4
    // Component 3: 5 - 6 - 7
    // Relations are 0-1, 1-2, 3-4, 5-6, 6-7
    int n1 = 8;
    vector<vector<int>> adj1(n1);
    adj1[0] = {1};
    adj1[1] = {0, 2};
    adj1[2] = {1};
    adj1[3] = {4};
    adj1[4] = {3};
    adj1[5] = {6};
    adj1[6] = {5, 7};
    adj1[7] = {6};
    int src1 = 0;

    // Expected: [0, 1, 2, -1, -1, -1, -1, -1]
    vector<int> res1 = sol.shortestPath(adj1, src1);
    cout << "Test 1 | Source: " << src1 << ". Graph: Disconnected (0-1-2, 3-4, 5-6-7)\n";
    cout << "Result: ";
    printVector(res1);
    cout << " (Expected: [0, 1, 2, -1, -1, -1, -1, -1])\n";
    cout << "--------------------------------\n";

    // Test Case 2: Complex Graph with multiple paths
    // Graph with 5 nodes (0 to 4)
    // 0 - 1
    // 0 - 2
    // 1 - 3
    // 2 - 3
    // 3 - 4
    // Source: 0
    int n2 = 5;
    vector<vector<int>> adj2(n2);
    adj2[0] = {1, 2};
    adj2[1] = {0, 3};
    adj2[2] = {0, 3};
    adj2[3] = {1, 2, 4};
    adj2[4] = {3};
    int src2 = 0;

    // Expected distances from 0:
    // 0: 0
    // 1: 1 (0->1)
    // 2: 1 (0->2)
    // 3: 2 (0->1->3 or 0->2->3)
    // 4: 3 (0->...->3->4)
    // Result: [0, 1, 1, 2, 3]
    vector<int> res2 = sol.shortestPath(adj2, src2);
    cout << "Test 2 | Source: " << src2 << ". Graph: Converging paths\n";
    cout << "Result: ";
    printVector(res2);
    cout << " (Expected: [0, 1, 1, 2, 3])\n";
    cout << "--------------------------------\n";

    // Test Case 3: Star Graph (Source in center)
    // Graph: 0 -> 1, 0 -> 2, 0 -> 3
    int n3 = 4;
    vector<vector<int>> adj3(n3);
    adj3[0] = {1, 2, 3};
    adj3[1] = {0};
    adj3[2] = {0};
    adj3[3] = {0};
    int src3 = 0;

    // Expected: [0, 1, 1, 1]
    vector<int> res3 = sol.shortestPath(adj3, src3);
    cout << "Test 3 | Source: " << src3 << ". Graph: Star graph\n";
    cout << "Result: ";
    printVector(res3);
    cout << " (Expected: [0, 1, 1, 1])\n";
    cout << "--------------------------------\n";

    return 0;
}
