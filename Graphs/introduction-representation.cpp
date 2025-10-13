/*
File: introduction-representation.cpp
Date: 2025-10-13 08:20

Problem: Graph Representation
Link: (None)

Problem Statement:
Implement and analyze two fundamental ways to represent a graph (V vertices and E edges):
the Adjacency Matrix and the Adjacency List. The implementation should focus on an
undirected graph.

-------------------------------------------------
✅ Approachs 1
- Idea: **Adjacency Matrix**. Use a 2D array (V x V) where the cell M[i][j] stores 1 if there is an edge between vertex 'i' and vertex 'j', and 0 otherwise. For an undirected graph, the matrix is symmetric (M[i][j] = M[j][i]).
- Time complexity (Edge Check): **O(1)**. Checking if an edge exists between two vertices u and v is instant: M[u][v].
- Space complexity: **O(V^2)**. Proportional to the square of the number of vertices.
- Limitations (if any): Very space-inefficient for **sparse graphs** (graphs with few edges, $E \ll V^2$). Iterating over all neighbors of a vertex takes O(V) time.

✅ Approachs 2
- Idea: **Adjacency List**. Use an array or vector of size V, where each index 'i' holds a list (or vector) of all vertices adjacent to vertex 'i'.
- Approach: Array of Vectors (or Linked Lists).
- Algorithm: For each edge (u, v), add v to the list of u, and add u to the list of v (for undirected graphs).
- Time complexity (Edge Check): **O(degree of u)**. Checking if an edge exists requires iterating through the list of neighbors for one of the vertices.
- Space complexity: **O(V + E)**. Proportional to the number of vertices plus the number of edges. This is highly efficient for sparse graphs.
- Limitations (if any): Checking if an edge (u, v) exists is slower than the matrix approach.

💡 Key Pattern:
- **Space vs. Time Trade-off:** The choice between Matrix (fast edge check, high space cost) and List (slow edge check, low space cost for sparse graphs) depends on the graph density and the most frequent operation required (checking edges vs. iterating neighbors).

ℹ️ Keywords:
- Graph Theory, Adjacency Matrix, Adjacency List, Undirected Graph, Sparse Graph, Dense Graph

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- The Adjacency List is generally preferred in most practical applications unless the graph is guaranteed to be dense.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)

/**
 * @brief Creates an Adjacency Matrix representation for an undirected graph.
 * @return A 2D vector<vector<bool>> representing the adjacency matrix.
 */
vector<vector<bool>> createUndirectedAdjMat()
{
    int vertex, edges;
    cout << "Enter number of vertex: ";
    cin >> vertex;
    cout << "Enter no of edges:";
    cin >> edges;
    // Initializes a V x V matrix with all values set to 0 (false)
    vector<vector<bool>> graph(vertex, vector<bool>(vertex, 0));

    cout << "Enter edges (u v, 0-indexed):";
    FOR(i, 0, edges)
    {
        int u, v;
        cin >> u >> v;
        // Set both M[u][v] and M[v][u] to 1 for an undirected graph
        if (u >= 0 && u < vertex && v >= 0 && v < vertex)
        {
            graph[u][v] = 1;
            graph[v][u] = 1;
        }
        else
        {
            cout << "Warning: Edge " << u << " " << v << " is out of bounds [0, " << vertex - 1 << "]. Skipped.\n";
        }
    }
    return graph;
}

/**
 * @brief Creates an Adjacency List representation for an undirected graph.
 * @return A vector<vector<int>> representing the adjacency list.
 */
vector<vector<int>> createUndirectedAdjList()
{
    int vertex, edges;
    cout << "Enter number of vertex:";
    cin >> vertex;
    // Initializes an array of V vectors
    vector<vector<int>> adjList(vertex);
    cout << "Enter number of edges:";
    cin >> edges;
    cout << "Enter edges (u v, 0-indexed): ";
    FOR(i, 0, edges)
    {
        int u, v;
        cin >> u >> v;
        // Add v to u's list and u to v's list for an undirected graph
        if (u >= 0 && u < vertex && v >= 0 && v < vertex)
        {
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
        else
        {
            cout << "Warning: Edge " << u << " " << v << " is out of bounds [0, " << vertex - 1 << "]. Skipped.\n";
        }
    }
    return adjList;
}

/**
 * @brief Prints the Adjacency List representation.
 * @param adjList The adjacency list (vector of vectors).
 */
void printAdjList(vector<vector<int>> adjList)
{
    cout << "\n--- Adjacency List ---\n";
    FOR(i, 0, adjList.size())
    {
        // Only print if the vertex has neighbors
        if (!adjList[i].empty())
        {
            cout << "Vertex " << i << " -> ";
            for (int v : adjList[i])
                cout << v << " ";
            cout << "\n";
        }
    }
}

/**
 * @brief Prints the Adjacency Matrix representation.
 * @param graph The adjacency matrix (vector of vectors of bool).
 */
void printAdjMat(vector<vector<bool>> graph)
{
    cout << "\n--- Adjacency Matrix ---\n";
    int n = graph.size();
    // Print column headers (optional, for clarity)
    cout << "  ";
    FOR(j, 0, n)
        cout << j << " ";
    cout << "\n";

    // Print separator
    cout << "  ";
    FOR(j, 0, n)
        cout << "--";
    cout << "\n";

    FOR(i, 0, n)
    {
        cout << i << "|"; // Row header
        FOR(j, 0, n)
        cout << graph[i][j] << " ";
        cout << "\n";
    }
}

int main()
{
    // --- Adjacency Matrix Example ---
    cout << "\n--- Starting Adjacency Matrix Creation ---\n";
    vector<vector<bool>> graphMat = createUndirectedAdjMat();
    printAdjMat(graphMat);

    // --- Adjacency List Example ---
    cout << "\n--- Starting Adjacency List Creation ---\n";
    vector<vector<int>> adjList = createUndirectedAdjList();
    printAdjList(adjList);

    return 0;
}
