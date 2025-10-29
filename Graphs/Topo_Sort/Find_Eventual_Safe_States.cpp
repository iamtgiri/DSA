/*
File: Find_Eventual_Safe_States.cpp
Date: 2025-10-29 10:48

Problem: Find Eventual Safe States
Link: https://leetcode.com/problems/find-eventual-safe-states/description/

Problem Statement:
A node is an **eventual safe state** if every possible path starting from that
node eventually leads to a terminal node (a node with no outgoing edges).
Return the indices of all eventual safe states in ascending order.

-------------------------------------------------
❌ Brute Force
- Idea: For every node, perform a depth-first search (DFS) to explore all paths.
  Keep track of visited nodes within the current path to detect cycles.
- Time complexity: O(N * (N + E)), where N is the number of nodes and E is the
  number of edges. In the worst case (a dense graph), this could be
  O(N * N^2) = O(N^3) or O(N^2) if using memoization on the DFS result.
- Space complexity: O(N) for recursion stack and visited/memoization arrays.
- Limitations: Time-consuming as it re-explores subgraphs multiple times
  without proper graph structure optimization.

✅ Optimized Approachs
- Idea: An eventual safe state is a node that is **not** part of a cycle and **not** on a path that leads into a cycle. The terminal nodes are the "safest" nodes,
  and safety propagates backward from them.
- Approach: **Reversed Graph Topological Sort (Kahn's Algorithm)**.
- Algorithm:
    1. **Reverse Graph:** Create a reverse graph (`rgraph`) where all edges are
       flipped (if A -> B in the original graph, then B -> A in the reverse graph).
    2. **Indegree Calculation:** Calculate the **in-degree** (`rindeg`) for the
       **original** graph. An original in-degree represents how many paths **end** at a node. Wait, no. We need the **out-degree** of the original graph,
       because terminal nodes have out-degree 0. The out-degree of the original
       graph is the **in-degree** of the reversed graph.
       Let's stick to the simplest interpretation:
       Calculate the **in-degree** (`rindeg`) on the **reversed graph**. This
       is equivalent to the **out-degree** of the original graph.
    3. **Queue Initialization:** Initialize a queue `q` with all nodes whose
       reversed in-degree (`rindeg`) is 0. These are the **original terminal nodes**.
    4. **BFS/Topological Sort:** Perform a BFS:
        - Dequeue a safe `node` and add it to the result.
        - For every predecessor `nei` in the reversed graph (i.e., a node that
          originally pointed to `node`):
            - Decrement `rindeg[nei]` (which is the original out-degree of `nei`).
            - If `rindeg[nei]` drops to 0, it means all paths originating from `nei`
              now lead to an already-found safe state (or terminal node). Enqueue `nei`.
    5. **Result:** The final set of nodes collected in the BFS are the eventual
       safe states. Sort the result ascendingly.
- Time complexity: **O(N + E)**, dominated by building the reversed graph and
  running the BFS.
- Space complexity: **O(N + E)** for the reversed graph, in-degree array, and queue.

💡 Key Pattern:
- **Safety/Terminal Propagation:** When a problem asks for states that don't lead
  to a certain problematic state (like a cycle), reversing the graph and using
  Topological Sort from the "safe" sinks is often the optimal approach.

ℹ️ Keywords:
- Directed Graph, Topological Sort, Sink Node, Cycle Detection, Kahn's Algorithm, Reversed Graph.

🗒️ Notes
- Terminal nodes are the initial safe states. Safety propagates backward along
  edges.
- This is mathematically equivalent to finding all nodes that are not part of
  a cycle and do not reach a node that is part of a cycle.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Finds all eventual safe states in a directed graph using Reversed Topological Sort.
     * @param graph The adjacency list representation of the directed graph.
     * @return A vector of 0-based indices of the eventual safe states, sorted ascendingly.
     */
    vector<int> eventualSafeNodes(vector<vector<int>> &graph)
    {
        size_t n = graph.size();

        // rindeg: Stores the IN-DEGREE of the REVERSED graph, which is
        //         equivalent to the OUT-DEGREE of the ORIGINAL graph.
        vector<int> rindeg(n, 0);
        // rgraph: The REVERSED adjacency list (predecessors)
        vector<vector<int>> rgraph(n);

        // 1. Build Reversed Graph (rgraph) and calculate reversed in-degree (rindeg)
        for (size_t i = 0; i < n; ++i)
        {
            // i is the source node in the original graph
            for (int neighbor : graph[i])
            {
                // Original edge: i -> neighbor
                // Reversed edge: neighbor -> i
                rgraph[neighbor].push_back(i);
                rindeg[i]++; // i's OUT-DEGREE in original graph (IN-DEGREE in reversed)
            }
        }

        queue<int> q;
        // 2. Initialize Queue with Terminal Nodes
        // Nodes where original OUT-DEGREE is 0 (rindeg[i] == 0) are terminal nodes (sinks)
        for (size_t i = 0; i < n; ++i)
            if (rindeg[i] == 0)
                q.push(i);

        vector<int> result;

        // 3. BFS/Topological Sort on Reversed Graph
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            result.push_back(node); // The node is safe

            // Iterate over predecessors (rgraph[node] contains nodes 'j' where j -> node originally)
            for (int predecessor : rgraph[node])
            {
                // predecessor's OUT-DEGREE in original graph is reduced because
                // one of its targets ('node') is now known to be safe.
                rindeg[predecessor]--;

                // If a node's remaining original OUT-DEGREE drops to 0, it means
                // ALL its outgoing paths lead to terminal nodes or already-safe states.
                if (rindeg[predecessor] == 0)
                    q.push(predecessor);
            }
        }

        // 4. Sort and Return
        sort(result.begin(), result.end());
        return result;
    }
};

// Helper function to print a vector of integers
template <typename T>
void printVector(const vector<T> &vec)
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

    cout << "--- Find Eventual Safe States ---\n";

    // Test Case 1: Simple linear and terminal nodes
    // Graph: 0 -> 1 -> 2. Terminals: 2. Safe: 0, 1, 2
    int n1 = 3;
    vector<vector<int>> graph1 = {{1}, {2}, {}};
    vector<int> res1 = sol.eventualSafeNodes(graph1);
    cout << "Test 1 | Graph: 0->1->2\n";
    cout << "Result: ";
    printVector(res1);
    cout << " (Expected: [0, 1, 2])\n";
    cout << "--------------------------------\n";

    // Test Case 2: Cycle detection
    // Graph: 0 -> 1, 1 -> 2, 2 -> 1 (Cycle: 1-2). 3 -> 0. 4 -> 5, 5 -> (terminal).
    // Safe: 4, 5. Unsafe: 0, 1, 2, 3 (3 leads to 0, which leads to cycle)
    int n2 = 6;
    vector<vector<int>> graph2 = {{1}, {2}, {1}, {0}, {5}, {}};
    vector<int> res2 = sol.eventualSafeNodes(graph2);
    cout << "Test 2 | Graph: 0->1, 1<->2, 3->0, 4->5\n";
    cout << "Result: ";
    printVector(res2);
    cout << " (Expected: [4, 5])\n";
    cout << "--------------------------------\n";

    // Test Case 3: Complex graph with multiple paths
    // Graph: 0->1, 1->2, 2->3, 3->0 (Cycle: 0-1-2-3). 4->3. 5->6, 6->(terminal)
    // Safe: 5, 6. Unsafe: 0, 1, 2, 3, 4 (4 leads to cycle)
    int n3 = 7;
    vector<vector<int>> graph3 = {{1}, {2}, {3}, {0}, {3}, {6}, {}};
    vector<int> res3 = sol.eventualSafeNodes(graph3);
    cout << "Test 3 | Graph: 0-1-2-3-0 (cycle), 4->3, 5->6\n";
    cout << "Result: ";
    printVector(res3);
    cout << " (Expected: [5, 6])\n";
    cout << "--------------------------------\n";

    // Test Case 4: No edges, all are terminal
    int n4 = 4;
    vector<vector<int>> graph4 = {{}, {}, {}, {}};
    vector<int> res4 = sol.eventualSafeNodes(graph4);
    cout << "Test 4 | Graph: No edges\n";
    cout << "Result: ";
    printVector(res4);
    cout << " (Expected: [0, 1, 2, 3])\n";
    cout << "--------------------------------\n";

    return 0;
}
