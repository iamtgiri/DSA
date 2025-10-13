/*
File: Connected_Components_in_an_Undirected_Graph.cpp
Date: 2025-10-13 14:36

Problem: Connected Components in an Undirected Graph
Link: https://www.geeksforgeeks.org/problems/connected-components-in-an-undirected-graph/1

Problem Statement:
Given an undirected graph with V vertices and E edges, the goal is to find all
disjoint **Connected Components**. A connected component is a maximal set of vertices
in which every vertex is reachable from every other vertex within the set.

-------------------------------------------------
❌ Brute Force (N/A)
- Idea: Graph traversal is inherently the most efficient way to solve this. No common
  "brute force" exists that is asymptotically slower than O(V+E) unless unnecessary
  operations are introduced.

✅ Optimized Approachs
- Idea: Utilize a **Graph Traversal Algorithm (BFS or DFS)** to explore the graph.
  Each time the traversal algorithm is launched from an unvisited node, it discovers a
  new, complete connected component.
- Approach: **Iterative Breadth-First Search (BFS)**.
- Algorithm:
    1. Construct the **Adjacency List** from the list of edges.
    2. Iterate through every vertex $i$ from 0 to $V-1$.
    3. If vertex $i$ has not been visited, it marks the start of a new component.
    4. Start a **BFS** from $i$, collecting all reachable nodes into a temporary component list.
    5. Mark all nodes found during the BFS as visited.
    6. Add the collected component to the final result list.
- Time complexity: **O(V + E)**. Every vertex (V) is added to the queue and processed once, and every edge (E) is checked once, leading to linear time complexity based on graph size.
- Space complexity: **O(V + E)**. Primarily for the adjacency list $O(V+E)$, the visited array $O(V)$, and the BFS queue $O(V)$.

💡 Key Pattern:
- **Exhaustive Traversal:** To find all disjoint structures in a graph, run a traversal (BFS/DFS) across all vertices, starting a new search only from nodes that haven't been visited yet.

ℹ️ Keywords:
- Connected Component, Undirected Graph, Graph Traversal, BFS, Adjacency List

🗒️ Notes
- The problem is typically solved by either BFS, DFS, or the Disjoint Set Union (DSU) data structure. BFS/DFS provides the actual list of nodes in each component, while DSU efficiently counts the number of components.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Finds all connected components in a given undirected graph.
     * @details Uses Breadth-First Search (BFS) to traverse the graph and identify
     * disjoint sets of connected vertices.
     * @param V The number of vertices (0 to V-1).
     * @param edges A list of edges, where each edge is a vector of two integers [u, v].
     * @return A vector of vectors, where each inner vector represents a connected component.
     */
    vector<vector<int>> getComponents(int V, vector<vector<int>> &edges)
    {
        // Step 1: Build adjacency list
        // Handles graph representation efficiently for sparse graphs.
        vector<vector<int>> adjList(V);
        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            // Since the graph is undirected, add edge in both directions
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        // Step 2: Initialize tracking structures
        vector<bool> visited(V, false);
        vector<vector<int>> result;

        // Step 3: Iterate through all vertices and start traversal if unvisited
        for (int start = 0; start < V; ++start)
        {
            if (!visited[start])
            {
                // Found a new, unvisited component
                vector<int> component;
                queue<int> q;

                q.push(start);
                visited[start] = true;

                // Standard BFS traversal
                while (!q.empty())
                {
                    int node = q.front();
                    q.pop();
                    component.push_back(node);

                    for (int nei : adjList[node])
                    {
                        if (!visited[nei])
                        {
                            visited[nei] = true;
                            q.push(nei);
                        }
                    }
                }

                // Add the fully discovered component to the result set
                result.push_back(component);
            }
        }

        return result;
    }
};

/**
 * @brief Helper function to print the connected components neatly.
 * @param components The vector of vectors containing the vertices of each component.
 */
void printComponents(const vector<vector<int>> &components, int test_num)
{
    cout << "\n--- Test Case " << test_num << " ---" << endl;
    cout << "Found " << components.size() << " connected components:" << endl;

    // Sort components for consistent output if needed, but here we just sort the nodes within
    vector<vector<int>> sorted_components = components;
    for (auto &comp : sorted_components)
    {
        sort(comp.begin(), comp.end());
    }

    for (size_t i = 0; i < sorted_components.size(); ++i)
    {
        cout << "  Component " << i + 1 << ": {";
        for (size_t j = 0; j < sorted_components[i].size(); ++j)
        {
            cout << sorted_components[i][j] << (j == sorted_components[i].size() - 1 ? "" : ", ");
        }
        cout << "}" << endl;
    }
}

int main()
{
    Solution sol;

    // --- Test 1: A single fully connected graph ---
    // V=5, E=4. Expected: 1 component: {0, 1, 2, 3, 4}
    int V1 = 5;
    vector<vector<int>> E1 = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
    vector<vector<int>> R1 = sol.getComponents(V1, E1);
    printComponents(R1, 1);

    // --- Test 2: Multiple distinct components ---
    // V=8, E=4. Expected: 4 components: {0, 1}, {2, 3}, {4, 5}, {6, 7}
    int V2 = 8;
    vector<vector<int>> E2 = {{0, 1}, {2, 3}, {4, 5}, {6, 7}};
    vector<vector<int>> R2 = sol.getComponents(V2, E2);
    printComponents(R2, 2);

    // --- Test 3: Graph with isolated nodes ---
    // V=6, E=2. Expected: 4 components: {0, 1}, {2}, {3}, {4, 5}
    int V3 = 6;
    vector<vector<int>> E3 = {{0, 1}, {4, 5}};
    vector<vector<int>> R3 = sol.getComponents(V3, E3);
    printComponents(R3, 3);

    // --- Test 4: Disconnected components of varying sizes ---
    // V=7, E=5. Expected: 3 components: {0, 1, 2, 3}, {4, 5}, {6}
    int V4 = 7;
    vector<vector<int>> E4 = {{0, 1}, {1, 2}, {2, 3}, {4, 5}};
    vector<vector<int>> R4 = sol.getComponents(V4, E4);
    printComponents(R4, 4);

    return 0;
}
