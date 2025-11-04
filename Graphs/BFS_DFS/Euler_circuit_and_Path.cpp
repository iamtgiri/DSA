/*
File: Euler_circuit_and_Path.cpp
Date: 2025-11-04 16:56

Problem: Euler circuit and Path
Link: https://www.geeksforgeeks.org/problems/euler-circuit-and-path/1

-------------------------------------------------
🧩 Problem Statement:
Given an undirected graph represented by an adjacency list, determine if it contains
an Euler Circuit (return 2), an Euler Path (return 1), or neither (return 0).

-------------------------------------------------
✅ Optimized Approach
We use the **Eulerian Graph Theorem**, which gives necessary and sufficient conditions
based on graph connectivity and vertex degrees.

Algorithm:
1. **Connectivity Check:**
   Perform a BFS/DFS from a vertex with nonzero degree.
   If any other vertex with nonzero degree is unreachable, the graph is disconnected.

2. **Degree Parity Check:**
   Count the vertices with odd degree (`oddDeg`).

3. **Classification:**
   - If `oddDeg == 0`: Euler Circuit → return 2
   - If `oddDeg == 2`: Euler Path → return 1
   - Else: Neither → return 0

Edge Cases:
- If the graph has no edges at all, it trivially has an Euler Circuit (return 2).

-------------------------------------------------
⏱️ Time Complexity: O(N + E)
💾 Space Complexity: O(N + E)

-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Determines if the graph has an Euler Circuit (2), Euler Path (1), or neither (0).
     * @param n   Number of vertices.
     * @param adj Adjacency list of the undirected graph.
     * @return 0, 1, or 2 based on Eulerian properties.
     */
    int isEulerCircuit(int n, vector<int> adj[])
    {
        vector<bool> vis(n, false);
        int startNode = -1;

        // Find the first vertex with a nonzero degree
        for (int i = 0; i < n; ++i)
        {
            if (!adj[i].empty())
            {
                startNode = i;
                break;
            }
        }

        // If no edges exist, the graph is trivially Eulerian (circuit)
        if (startNode == -1)
            return 2;

        // --- Connectivity Check ---
        queue<int> q;
        q.push(startNode);
        vis[startNode] = true;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v : adj[u])
            {
                if (!vis[v])
                {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }

        // --- Degree Parity and Connectivity Verification ---
        int oddDeg = 0;
        for (int i = 0; i < n; ++i)
        {
            if (!adj[i].empty())
            {
                if (!vis[i])
                    return 0; // Disconnected component with edges
                if (adj[i].size() % 2 != 0)
                    oddDeg++;
            }
        }

        // --- Classification ---
        if (oddDeg == 0)
            return 2; // Euler Circuit
        if (oddDeg == 2)
            return 1; // Euler Path
        return 0;     // Neither
    }
};

// -----------------------------------------------------------
// Example test cases
// -----------------------------------------------------------
int main()
{
    Solution sol;

    // Test 1: Euler Circuit (0-1-2-3-0)
    int n1 = 4;
    vector<int> adj1[n1];
    adj1[0] = {1, 3};
    adj1[1] = {0, 2};
    adj1[2] = {1, 3};
    adj1[3] = {0, 2};
    cout << "Test 1 (Circuit): Expected 2, Got " << sol.isEulerCircuit(n1, adj1) << endl;

    // Test 2: Euler Path (0-1-2)
    int n2 = 3;
    vector<int> adj2[n2];
    adj2[0] = {1};
    adj2[1] = {0, 2};
    adj2[2] = {1};
    cout << "Test 2 (Path): Expected 1, Got " << sol.isEulerCircuit(n2, adj2) << endl;

    // Test 3: Neither (Star graph)
    int n3 = 4;
    vector<int> adj3[n3];
    adj3[0] = {1, 2, 3};
    adj3[1] = {0};
    adj3[2] = {0};
    adj3[3] = {0};
    cout << "Test 3 (Neither): Expected 0, Got " << sol.isEulerCircuit(n3, adj3) << endl;

    // Test 4: Disconnected graph (0-1 and 2-3)
    int n4 = 4;
    vector<int> adj4[n4];
    adj4[0] = {1};
    adj4[1] = {0};
    adj4[2] = {3};
    adj4[3] = {2};
    cout << "Test 4 (Disconnected): Expected 0, Got " << sol.isEulerCircuit(n4, adj4) << endl;

    return 0;
}
