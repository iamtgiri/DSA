/*
File: Number_of_Provinces.cpp
Date: 2025-10-13 18:08

Problem: Number of Provinces
Link: https://leetcode.com/problems/number-of-provinces/

Problem Statement:
There are n cities. Some are connected, while some are not. If city a is
connected directly with city b, and city b is connected directly with city c,
then city a is connected indirectly with city c.

A province is a group of directly or indirectly connected cities and no other
cities outside of the group.

You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the
ith city and the jth city are directly connected, and isConnected[i][j] = 0
otherwise. Return the total number of provinces.
-------------------------------------------------
❌ Brute Force
- This problem is about finding connected components in a graph. Standard
  graph traversal algorithms like BFS or DFS are already the efficient and
  standard way to solve this. There isn't a significantly different "brute
  force" method that is substantially less efficient yet still correct.

✅ Optimized Approach (BFS)
- Idea: Treat cities as nodes and connections as edges in a graph. The goal
  is to count the number of connected components in this graph.
- Approach: Iterate through each city. If a city hasn't been visited, it
  marks the start of a new province. We then start a traversal (like BFS)
  from this city to find all connected cities and mark them as visited.
  We increment our province count and repeat until all cities are visited.
- Algorithm:
  1. Initialize a `visited` array and set the number of provinces to 0.
  2. Loop from city 0 to n-1.
  3. If the current city has not been visited:
     a. Increment the province count.
     b. Start a BFS from this city.
     c. Add the city to a queue and mark it as visited.
     d. While the queue is not empty, explore its neighbors.
     e. Mark all reachable (and unvisited) cities as visited.
  4. Return the total province count.
- Time complexity: O(n^2). We iterate through the n x n matrix.
- Space complexity: O(n). For the visited array and the BFS queue.

💡 Key Pattern:
- Using graph traversal (BFS or DFS) to find and count connected components.
- This pattern is fundamental for problems involving network connectivity.

ℹ️ Keywords:
- Graph, Adjacency Matrix, BFS, DFS, Connected Components, Union-Find

🗒️ Notes
- This is a classic "number of connected components" problem.
- An alternative efficient solution is using a Disjoint Set Union (DSU) or
  Union-Find data structure, which can be faster if the graph is sparse
  and represented by an edge list.
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution
{
public:
    /**
     * @brief Finds the number of provinces in a graph represented by an
     * adjacency matrix.
     * @param isConnected An n x n matrix representing city connections.
     * @return The total number of provinces (connected components).
     */
    int findCircleNum(vector<vector<int>> &isConnected)
    {
        int n = isConnected.size();
        if (n == 0)
        {
            return 0;
        }

        vector<bool> visited(n, false);
        queue<int> q;
        int provinces = 0;

        // Iterate through each city to find unvisited ones.
        for (int startNode = 0; startNode < n; ++startNode)
        {
            // If a city hasn't been visited, it's the start of a new province.
            if (!visited[startNode])
            {
                provinces++;
                q.push(startNode);
                visited[startNode] = true;

                // Start BFS to find all cities in the current province.
                while (!q.empty())
                {
                    int currentNode = q.front();
                    q.pop();

                    // Check all other cities for a connection.
                    for (int neighbor = 0; neighbor < n; ++neighbor)
                    {
                        // If connected and not visited, add to queue.
                        if (isConnected[currentNode][neighbor] && !visited[neighbor])
                        {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
            }
        }
        return provinces;
    }
};

void runTest(const string &testName, vector<vector<int>> &isConnected, int expected)
{
    Solution sol;
    int result = sol.findCircleNum(isConnected);
    cout << testName << ": " << (result == expected ? "Passed" : "Failed") << endl;
    cout << "  Expected: " << expected << ", Got: " << result << endl;
}

int main()
{
    // Example test case 1
    vector<vector<int>> isConnected1 = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
    runTest("Test Case 1", isConnected1, 2);

    // Example test case 2
    vector<vector<int>> isConnected2 = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    runTest("Test Case 2", isConnected2, 3);

    // Example test case 3: All connected
    vector<vector<int>> isConnected3 = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    runTest("Test Case 3", isConnected3, 1);

    return 0;
}
