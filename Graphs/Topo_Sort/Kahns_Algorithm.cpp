/*
File: Kahns_Algorithm.cpp
Date: 2025-10-17 00:07

Problem: Kahn's Algorithm (Topological Sort)
Link: https://www.geeksforgeeks.org/problems/topological-sort/1

Problem Statement:
Given a Directed Acyclic Graph (DAG) with V vertices and E edges, find a
topological sorting of the graph using Kahn's Algorithm (BFS). A topological
sort is a linear ordering of its vertices such that for every directed edge
from node u to node v, u comes before v in the ordering. This algorithm can
also detect cycles.

----------------------------------------------------------------------------------
❌ Brute Force
- Idea: Iterating through all V! possible permutations of vertices and checking
  if any permutation satisfies the topological ordering criteria.
- Time complexity: O(V! * E). Highly inefficient due to checking every permutation.
- Space complexity: O(V) to store the current permutation.
- Limitations: Infeasible for graphs with more than a few nodes.

✅ Optimized Approachs
- Idea: The core idea of Kahn's Algorithm is to process nodes that have no
  prerequisites (i.e., an in-degree of zero). Once processed, we remove them and
  update the in-degree of their neighbors, potentially creating new nodes with
  an in-degree of zero.
- Approach: Kahn's Algorithm (BFS-based Topological Sort).
- Algorithm:
  1. Calculate the **in-degree** (number of incoming edges) for every vertex.
  2. Initialize a **queue** and add all vertices with an in-degree of 0 to it.
  3. Initialize an empty **result** vector.
  4. While the queue is not empty:
     a. Dequeue a node, `u`, and append it to the `result`.
     b. For every neighbor, `v`, of `u`:
        i. Decrement the in-degree of `v`.
        ii. If the in-degree of `v` becomes 0, enqueue `v`.
  5. After the loop, if the size of the `result` vector is less than V, the
     graph contains a cycle and no topological sort is possible.
- Time complexity: O(V + E). Dominated by iterating through all vertices (V) to
  find initial in-degrees and traversing all edges (E) during the BFS process.
- Space complexity: O(V + E) for the adjacency list and O(V) for the in-degree
  array and the queue. Total space complexity is O(V + E).

💡 Key Pattern:
- **In-Degree Processing:** The pattern is to use **in-degrees** and a **queue** to systematically process nodes in an order that respects dependencies, which
  is the hallmark of BFS-based topological sort.

ℹ️ Keywords:
- Directed Acyclic Graph (DAG), Kahn's Algorithm, In-Degree, BFS, Queue, Cycle Detection

🗒️ Notes
- This algorithm is superior to the DFS method if the goal is also to detect
  cycles, as the cycle detection logic is simple: check if `result.size() < V`.
----------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Computes the topological sort of a graph using Kahn's Algorithm (BFS).
     * @param V The number of vertices (0 to V-1).
     * @param edges A vector of pairs [u, v] representing a directed edge from u to v.
     * @return A vector representing one possible topological ordering, or an empty
     * vector if a cycle is detected.
     */
    vector<int> KahnAlgo(int V, vector<vector<int>> &edges)
    {
        // 1. Initialization: Adjacency List and In-Degree Array
        vector<vector<int>> adj(V);
        vector<int> indeg(V, 0);

        for (auto &e : edges)
        {
            adj[e[0]].push_back(e[1]);
            indeg[e[1]]++; // Increment in-degree for the destination node
        }

        // 2. Start Queue with all nodes having In-Degree 0
        queue<int> q;
        vector<int> result;
        result.reserve(V);

        for (int i = 0; i < V; i++)
            if (indeg[i] == 0)
                q.push(i);

        // 3. Process nodes using BFS
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            result.push_back(node);

            // For all neighbors of the current node
            for (int nei : adj[node])
            {
                // Remove the current node's contribution by decrementing neighbor's in-degree
                indeg[nei]--;

                // If a neighbor's in-degree drops to 0, it's ready to be processed
                if (indeg[nei] == 0)
                    q.push(nei);
            }
        }

        // 4. Cycle Detection
        // If the number of nodes in the result is less than V, a cycle exists.
        if (result.size() < V)
        {
            // Cycle detected (Topological Sort is not possible)
            return {};
        }

        return result;
    }
};

/**
 * @brief Helper function to print the result vector.
 */
void printResult(const vector<int> &result)
{
    if (result.empty())
    {
        cout << "Cycle Detected (Topological Sort not possible)";
        return;
    }
    for (int node : result)
    {
        cout << node << " ";
    }
}

int main()
{
    Solution sol;

    // Test Case 1: Standard DAG (V=6, E=6) - No Cycle
    // Edges: 5->2, 5->0, 4->0, 4->1, 2->3, 3->1
    // Expected sort (one of many): 4 5 0 2 3 1 or 5 4 2 3 0 1
    int V1 = 6;
    vector<vector<int>> edges1 = {{5, 2}, {5, 0}, {4, 0}, {4, 1}, {2, 3}, {3, 1}};
    vector<int> result1 = sol.KahnAlgo(V1, edges1);
    cout << "--- Test Case 1 (Standard DAG) ---" << endl;
    cout << "Vertices (V): " << V1 << endl;
    cout << "Topological Sort: ";
    printResult(result1);
    cout << endl
         << endl;

    // Test Case 2: Simple Chain (V=4, E=3) - No Cycle
    // Edges: 0->1, 1->2, 2->3
    // Expected sort: 0 1 2 3
    int V2 = 4;
    vector<vector<int>> edges2 = {{0, 1}, {1, 2}, {2, 3}};
    vector<int> result2 = sol.KahnAlgo(V2, edges2);
    cout << "--- Test Case 2 (Chain) ---" << endl;
    cout << "Vertices (V): " << V2 << endl;
    cout << "Topological Sort: ";
    printResult(result2);
    cout << endl
         << endl;

    // Test Case 3: Graph with a Cycle (V=3, E=3)
    // Edges: 0->1, 1->2, 2->0 (Cycle)
    // Expected sort: Empty result
    int V3 = 3;
    vector<vector<int>> edges3 = {{0, 1}, {1, 2}, {2, 0}};
    vector<int> result3 = sol.KahnAlgo(V3, edges3);
    cout << "--- Test Case 3 (Graph with Cycle) ---" << endl;
    cout << "Vertices (V): " << V3 << endl;
    cout << "Topological Sort: ";
    printResult(result3);
    cout << endl;

    return 0;
}
