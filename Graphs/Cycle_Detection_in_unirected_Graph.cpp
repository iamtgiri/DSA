/*
File: Cycle_Detection_in_undirected_Graph.cpp
Date: 2025-10-13 19:12

Problem: Cycle Detection in an Undirected Graph
Link: https://www.geeksforgeeks.org/problems/detect-cycle-in-an-undirected-graph/1

Problem Statement:
Given an undirected graph with V vertices and E edges, check whether it
contains any cycle. The graph may be disconnected.

-------------------------------------------------
❌ Brute Force
- A naive approach is not practical here. Standard graph traversals like BFS
  and DFS are already the most efficient ways to solve this problem.

✅ Optimized Approach (DFS)
- Idea: Traverse the graph depth-first. A cycle is detected if we encounter
  a visited vertex that is not the immediate parent of the current vertex.
- Approach: For each unvisited vertex, start a DFS. Pass the parent of the
  current node in the recursion.
- Algorithm:
  1. For each vertex, if not visited, call a recursive `dfs` function.
  2. In `dfs(current, parent)`, mark `current` as visited.
  3. For each neighbor of `current`:
     a. If the neighbor is not visited, recurse: `dfs(neighbor, current)`.
     b. If the neighbor is visited and is not the parent, a cycle exists.
  4. If the loop finishes without finding a cycle, return false.
- Time complexity: O(V + E), where V is vertices and E is edges.
- Space complexity: O(V) for the visited array and recursion stack.

✅ Optimized Approach (BFS)
- Idea: Traverse the graph breadth-first. A cycle is found if we visit a
  node that's already been visited and is not the parent of the current node.
- Approach: For each unvisited vertex, start a BFS. Use a queue that stores
  pairs of `{node, parent}`.
- Algorithm:
  1. For each vertex, if not visited, start a BFS.
  2. Push `{start_node, -1}` to a queue and mark `start_node` as visited.
  3. While the queue is not empty, dequeue `{node, parent}`.
  4. For each neighbor of `node`:
     a. If the neighbor is not visited, mark it and enqueue `{neighbor, node}`.
     b. If the neighbor is visited and is not the `parent`, a cycle exists.
- Time complexity: O(V + E).
- Space complexity: O(V) for the visited array and queue.

💡 Key Pattern:
- Tracking the parent node during a graph traversal (DFS or BFS) to
  differentiate between a path back to the parent and a back-edge to an
  ancestor, which indicates a cycle in an undirected graph.

ℹ️ Keywords:
- Graph, Undirected Graph, Cycle Detection, BFS, DFS, Adjacency List

🗒️ Notes
- The parent tracking technique is crucial for undirected graphs.
- For disconnected graphs, we must iterate through all vertices and start a
  traversal if a vertex hasn't been visited yet.
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

class Solution
{
public:
    /**
     * @brief Helper function to detect a cycle using DFS.
     * @param adj The adjacency list of the graph.
     * @param visited A boolean vector to track visited nodes.
     * @param current The current node being visited.
     * @param parent The parent node of the current node.
     * @return True if a cycle is detected, false otherwise.
     */
    bool hasCycleDFS(vector<int> adj[], vector<bool> &visited, int current, int parent)
    {
        visited[current] = true;
        for (int neighbor : adj[current])
        {
            if (!visited[neighbor])
            {
                if (hasCycleDFS(adj, visited, neighbor, current))
                {
                    return true;
                }
            }
            // If the neighbor is visited and not the parent, there is a cycle.
            else if (neighbor != parent)
            {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Helper function to detect a cycle using BFS.
     * @param V The number of vertices.
     * @param adj The adjacency list of the graph.
     * @param startNode The starting node for the BFS traversal.
     * @param visited A boolean vector to track visited nodes.
     * @return True if a cycle is detected, false otherwise.
     */
    bool hasCycleBFS(int V, vector<int> adj[], int startNode, vector<bool> &visited)
    {
        // Queue stores {node, parent}.
        queue<pair<int, int>> q;

        q.push({startNode, -1});
        visited[startNode] = true;

        while (!q.empty())
        {
            int node = q.front().first;
            int parent = q.front().second;
            q.pop();

            for (int neighbor : adj[node])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push({neighbor, node});
                }
                // If neighbor is visited and is not the immediate parent.
                else if (neighbor != parent)
                {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * @brief Detects if a cycle exists in an undirected graph.
     * @param V The number of vertices.
     * @param adj The adjacency list representation of the graph.
     * @return True if the graph contains a cycle, false otherwise.
     */
    bool isCycle(int V, vector<int> adj[])
    {
        vector<bool> visited(V, false);
        for (int i = 0; i < V; ++i)
        {
            if (!visited[i])
            {
                // Use either BFS or DFS.
                // if (hasCycleDFS(adj, visited, i, -1))
                if (hasCycleBFS(V, adj, i, visited))
                    return true;
            }
        }
        return false;
    }
};

void runTest(const string &testName, int V, const vector<vector<int>> &edges, bool expected)
{
    Solution sol;
    vector<int> adj[V];
    for (const auto &edge : edges)
    {
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]);
    }
    bool result = sol.isCycle(V, adj);
    cout << testName << ": " << (result == expected ? "Passed" : "Failed") << endl;
    cout << "  Expected: " << (expected ? "Cycle" : "No Cycle")
         << ", Got: " << (result ? "Cycle" : "No Cycle") << endl;
}

int main()
{
    // Test Case 1: Graph with a cycle
    int V1 = 5;
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 1}};
    runTest("Test Case 1 (Cycle)", V1, edges1, true);

    // Test Case 2: Graph without a cycle (a line)
    int V2 = 4;
    vector<vector<int>> edges2 = {{0, 1}, {1, 2}, {2, 3}};
    runTest("Test Case 2 (No Cycle)", V2, edges2, false);

    // Test Case 3: Disconnected graph with a cycle in one component
    int V3 = 7;
    vector<vector<int>> edges3 = {{0, 1}, {1, 2}, {2, 0}, {3, 4}, {5, 6}};
    runTest("Test Case 3 (Disconnected with Cycle)", V3, edges3, true);

    // Test Case 4: Disconnected graph without a cycle
    int V4 = 6;
    vector<vector<int>> edges4 = {{0, 1}, {2, 3}, {4, 5}};
    runTest("Test Case 4 (Disconnected, No Cycle)", V4, edges4, false);

    return 0;
}
