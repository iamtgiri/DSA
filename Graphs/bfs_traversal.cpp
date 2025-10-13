/*
File: bfs_traversal.cpp
Date: 2025-10-13 14:01

Problem: BFS Traversal of a graph
Link: URL

Problem Statement:

-------------------------------------------------
❌ Brute Force
- Idea:
- Time complexity:
- Space complexity:
- Limitations:

✅ Optimized Approachs
- Idea:
- Approach:
- Algorithm:
- Time complexity:
- Space complexity:

💡 Key Pattern:
-

ℹ️ Keywords:
-

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief
     * @param
     * @return
     */
    vector<int> bfsTraversal(int n, vector<vector<int>> &adjList)
    {
        vector<bool> visited(n, false);
        vector<int> result;
        queue<int> q;

        for (int start = 0; start < n; ++start)
        {
            if (!visited[start])
            {
                visited[start] = true;
                q.push(start);

                while (!q.empty())
                {
                    int node = q.front();
                    q.pop();
                    result.push_back(node);

                    for (int nei : adjList[node])
                    {
                        if (!visited[nei])
                        {
                            visited[nei] = true;
                            q.push(nei);
                        }
                    }
                }
            }
        }
        return result;
    }
};

int main()
{
    Solution sol;
    // Example: undirected graph
    int n = 5;
    vector<vector<int>> adjList(n);
    adjList[0] = {1, 2};
    adjList[1] = {0, 4};
    adjList[2] = {0};
    adjList[3] = {4};
    adjList[4] = {1,3};

    vector<int> bfsOrder = sol.bfsTraversal(n, adjList);

    cout << "BFS Traversal: ";
    for (int node : bfsOrder)
        cout << node << " ";
    cout << endl;

    return 0;

    return 0;
}