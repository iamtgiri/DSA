/*
File: Circle_of_strings.cpp
Date: 2025-11-07 10:27

Problem: Circle of strings
Link: https://www.geeksforgeeks.org/problems/circle-of-strings4530/1

Problem Statement:
Given an array of strings arr[], determine if the strings can be chained to form a
circle. A string X can be chained to string Y if the last character of X is the same
as the first character of Y.

-------------------------------------------------
❌ Brute Force
- Idea: Try every possible permutation of the N strings and check if the resulting
  sequence forms a valid circle (last char of one matches first char of next, and
  last char of the last string matches first char of the first string).
- Time complexity: O(N! * N * L_avg), where N is the number of strings and L_avg is
  the average string length. This is infeasible for large N.
- Space complexity: O(1) auxiliary space (excluding input storage).
- Limitations: Extremely high time complexity due to the factorial nature of
  permutation checks.

✅ Optimized Approachs
- Idea: The problem is equivalent to finding an **Eulerian Circuit** in a directed graph.
  - Nodes: The 26 letters ('a' to 'z').
  - Edges: Each string creates a directed edge from its starting character to its ending character.
  - A circle exists if and only if all edges (strings) can be traversed exactly once,
    forming a circuit, and all nodes are connected.
- Approach: **Graph Construction and Eulerian Circuit Verification**
- Algorithm:
  1. **Construct Graph & Degrees:** Create an adjacency list (adj) for the graph and two arrays, `indeg` (in-degree) and `outdeg` (out-degree), for the 26 nodes. For every string, add an edge from (first_char) to (last_char) and update the degrees.
  2. **Degree Check:** Iterate through all 26 possible nodes. If for any node, `indeg[i] != outdeg[i]`, a circuit is impossible. Return 0.
  3. **Connectivity Check:** Start a DFS from the first character of the first string (`start`). This is to ensure all characters that participate in the chain (i.e., have `indeg > 0` or `outdeg > 0`) belong to the same strongly connected component.
  4. **Final Verification:** Check all 26 nodes. If a node has `indeg[i] > 0` (meaning it's an active part of the graph) but was **not** visited by the DFS (`!vis[i]`), the graph is not strongly connected. Return 0.
  5. If both checks pass, return 1.
- Time complexity: **O(N * L_avg + V + E)**, where N is number of strings, L_avg is
  average length, V=26 (vertices), and E=N (edges). Dominantly O(N * L_avg).
- Space complexity: **O(V^2 + N * L_avg)**, dominated by the input array and the
  adjacency list/degree arrays (V=26 is constant).

💡 Key Pattern:
- **Eulerian Paths/Circuits:** Problems requiring a sequence that visits every edge exactly once. The core conditions are Balanced Degrees (for circuits) and Connectivity.

ℹ️ Keywords:
- Eulerian Circuit, Directed Graph, Graph Connectivity, DFS, In-degree, Out-degree.

🗒️ Notes
- This problem is an adaptation of finding an Eulerian path/circuit, which uses Hierholzer's algorithm for construction but only requires degree and connectivity checks for existence.
- The use of `indeg[i]` in the final check (instead of `outdeg[i]` or `indeg[i] || outdeg[i]`) is robust, as any character that is a target of an edge (`indeg[i] > 0`) must be reachable from the starting node.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Performs DFS to check connectivity of the graph starting from 'node'.
     * @param adj The adjacency list (graph).
     * @param vis The visited array.
     * @param node The starting node (character index 0-25).
     */
    void dfs(const vector<vector<int>> &adj, vector<bool> &vis, int node)
    {
        vis[node] = true;
        for (int nei : adj[node])
        {
            // The DFS function should take 'adj' by const reference for efficiency
            if (!vis[nei])
                dfs(adj, vis, nei);
        }
    }

    /**
     * @brief Checks if a list of strings can form a circle (Eulerian Circuit).
     * @param arr The array of strings.
     * @return 1 if a circle can be formed, 0 otherwise.
     */
    int isCircle(vector<string> &arr)
    {
        // 1. Graph Construction and Degree Tracking
        vector<vector<int>> adj(26);
        vector<int> indeg(26, 0), outdeg(26, 0);

        for (const string &w : arr)
        {
            int from = w[0] - 'a';
            int to = w[w.size() - 1] - 'a';

            // Add edge from start char to end char
            adj[from].push_back(to);
            indeg[to]++;
            outdeg[from]++;
        }

        // 2. Degree Check: In-degree must equal Out-degree for all nodes
        for (int i = 0; i < 26; ++i)
            if (indeg[i] != outdeg[i])
                return 0; // Not a Eulerian Circuit

        // Handle the edge case of an empty array
        if (arr.empty())
            return 1;

        // 3. Connectivity Check: Find a starting point (the first character of the first string)
        int start = arr[0][0] - 'a';
        vector<bool> vis(26, false);

        // Find the first active node if the starting node itself has no edges
        // (though in this problem, arr is non-empty, so start is guaranteed to be active)
        if (outdeg[start] == 0 && indeg[start] == 0)
        {
            // Find the first letter that is actually used in the graph
            for (int i = 0; i < 26; ++i)
            {
                if (outdeg[i] > 0 || indeg[i] > 0)
                {
                    start = i;
                    break;
                }
            }
        }

        // Run DFS from the starting node
        dfs(adj, vis, start);

        // 4. Final Verification: Check if all active nodes were visited
        for (int i = 0; i < 26; ++i)
        {
            // If the node 'i' is part of the graph (indeg > 0 or outdeg > 0)
            // but was not reached by DFS, the graph is not connected.
            if ((indeg[i] > 0 || outdeg[i] > 0) && !vis[i])
                return 0;
        }

        return 1; // Both conditions (Degree and Connectivity) are met
    }
};

int main()
{
    Solution sol;
    cout << "--- Circle of Strings Test Cases ---\n";

    // Test Case 1: Circle possible
    // "aab" -> 'a' to 'b'
    // "bac" -> 'b' to 'c'
    // "caa" -> 'c' to 'a'
    vector<string> arr1 = {"aab", "bac", "caa"};
    cout << "Test 1 (aab, bac, caa): Expected 1, Got " << sol.isCircle(arr1) << endl;

    // Test Case 2: Degrees unbalanced
    // "abc" ('a'->'c') and "cdf" ('c'->'f')
    // Out('a')=1, In('c')=1, Out('c')=1, In('f')=1. All others 0.
    // Error: Out('a')=1, In('a')=0. Fails.
    vector<string> arr2 = {"abc", "cdf"};
    cout << "Test 2 (abc, cdf): Expected 0, Got " << sol.isCircle(arr2) << endl;

    // Test Case 3: Disconnected components (Degrees balanced locally)
    // "aba" ('a'->'a') and "cdc" ('c'->'c')
    // Out('a')=1, In('a')=1. Out('c')=1, In('c')=1. Degrees balance, but components are separate.
    vector<string> arr3 = {"aba", "cdc"};
    cout << "Test 3 (aba, cdc): Expected 0, Got " << sol.isCircle(arr3) << endl;
    // Start DFS from 'a'. 'c' is not visited. Fails connectivity check.

    return 0;
}