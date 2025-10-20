/*
File: Bipartite_Graph.cpp
Date: 2025-10-20 16:34

Problem: Bipartite Graph
Link: https://leetcode.com/problems/is-graph-bipartite/description/

Problem Statement:
Given a graph, determine if it is **bipartite**. A graph is bipartite if its
nodes can be partitioned into two independent sets, A and B, such that every
edge connects a node in A to a node in B. Equivalently, no two nodes within the
same set are connected by an edge.

----------------------------------------------------------------------------------
❌ Brute Force
- Idea: Try to partition the graph's nodes into every possible combination of
  two sets, and for each partition, check if any edge connects two nodes within
  the same set.
- Time complexity: O(2^V * E). Highly inefficient, as there are $2^V$ ways to
  partition the nodes into two sets.
- Space complexity: O(V) for storing the partition.
- Limitations: Infeasible for any practical graph size (V > 20).

✅ Optimized Approachs
- Idea: A graph is bipartite if and only if it is **2-colorable** and contains
  no **odd-length cycles**. We can use a graph traversal algorithm (BFS or DFS)
  to attempt coloring the graph with two colors.
- Approach: Breadth-First Search (BFS) / Coloring Algorithm.
- Algorithm:
  1. Initialize a `color` array of size `V` with `-1` (uncolored). Use two
     colors, represented by `0` and `1`.
  2. Iterate through all vertices (`start = 0` to `V-1`) to handle potentially
     **disconnected components**.
  3. If `start` is uncolored, start a BFS:
     a. Enqueue `start` and set its color to `0`.
     b. While the queue is not empty, dequeue the current `node`.
     c. For every `neighbor` of `node`:
        i. **Uncolored Neighbor:** Color the neighbor with the opposite color
           (`1 - color[node]`) and enqueue it.
        ii. **Already Colored Neighbor:** Check if the neighbor's color is the
            same as the current node's color. If `color[nei] == color[node]`,
            a conflict is found (an odd-length cycle), so return `false`.
  4. If the traversal finishes without finding any conflicts, return `true`.
- Time complexity: O(V + E). The traversal visits every vertex (V) and every
  edge (E) exactly once, making it optimal for graph traversal problems.
- Space complexity: O(V) for the `color` array and O(V) for the BFS queue. Total
  space complexity is **O(V + E)** to account for the input graph storage.

💡 Key Pattern:
- **Two-Coloring / Odd Cycle Detection:** Bipartite problems are fundamentally
  solved by attempting to color the graph with two colors, ensuring neighbors
  always have different colors. A coloring failure means an odd cycle exists.

ℹ️ Keywords:
- Bipartite, Two-Coloring, Graph Traversal, BFS, Odd Cycle, Disconnected Components.

🗒️ Notes
- The coloring technique (using `1 - color[node]`) elegantly toggles between
  color 0 and color 1.
- The need to iterate over all nodes (`start`) is crucial for graphs that are
  not fully connected.
----------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Checks if the given graph is bipartite using Breadth-First Search (BFS) coloring.
     * @param graph The adjacency list representation of the graph. graph[i] is a
     * vector of neighbors of node i.
     * @return True if the graph is bipartite, false otherwise.
     */
    bool isBipartite(const vector<vector<int>> &graph)
    {
        int n = graph.size();
        // color array: -1 = uncolored, 0 = Color A, 1 = Color B
        vector<int> color(n, -1);

        // Iterate through all nodes to ensure all components are checked
        for (int start = 0; start < n; ++start)
        {
            // Skip nodes that are already part of a checked component
            if (color[start] != -1)
                continue;

            // Start BFS for the new component
            queue<int> q;
            q.push(start);
            color[start] = 0; // Start coloring with Color A (0)

            while (!q.empty())
            {
                int node = q.front();
                q.pop();

                for (int nei : graph[node])
                {
                    if (color[nei] == -1)
                    {
                        // Neighbor is uncolored: assign the opposite color and enqueue
                        color[nei] = 1 - color[node];
                        q.push(nei);
                    }
                    else if (color[nei] == color[node])
                    {
                        // Neighbor has the same color: found an odd-length cycle (conflict)
                        return false;
                    }
                }
            }
        }
        // If the entire graph is colored without conflicts, it is bipartite
        return true;
    }
};

// Helper function to create and run test cases
void runTest(Solution &sol, const vector<vector<int>> &graph, bool expected)
{
    bool result = sol.isBipartite(graph);
    cout << "Graph Check (V=" << graph.size() << "): " << (result ? "Bipartite" : "NOT Bipartite");
    cout << " (Expected: " << (expected ? "Bipartite" : "NOT Bipartite") << ")" << endl;
    cout << "---" << endl;
}

int main()
{
    Solution sol;

    // Test Case 1: Bipartite Graph (Simple line graph 0-1-2-3)
    // Partition: {0, 2} and {1, 3}
    vector<vector<int>> graph1 = {{1}, {0, 2}, {1, 3}, {2}};
    cout << "Test Case 1: Bipartite (Even Cycle / Path)" << endl;
    runTest(sol, graph1, true);

    // Test Case 2: Non-Bipartite Graph (Triangle / Odd Cycle: 0-1-2-0)
    // Edges: 0<->1, 1<->2, 2<->0
    vector<vector<int>> graph2 = {{1, 2}, {0, 2}, {0, 1}};
    cout << "Test Case 2: Not Bipartite (Odd Cycle)" << endl;
    runTest(sol, graph2, false);

    // Test Case 3: Graph with disconnected components (Both are bipartite)
    // Component 1: 0-1. Component 2: 2-3. Node 4 is isolated.
    vector<vector<int>> graph3 = {{1}, {0}, {3}, {2}, {}};
    cout << "Test Case 3: Bipartite (Disconnected Components)" << endl;
    runTest(sol, graph3, true);

    // Test Case 4: Non-Bipartite with disconnected components
    // Component 1: 0-1-2-0 (Odd cycle). Component 2: 3-4.
    vector<vector<int>> graph4 = {{1, 2}, {0, 2}, {0, 1}, {4}, {3}};
    cout << "Test Case 4: Not Bipartite (One component has odd cycle)" << endl;
    runTest(sol, graph4, false);

    return 0;
}
