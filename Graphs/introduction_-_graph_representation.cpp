/*
File: introduction-representation.cpp
Date: 2025-10-13 08:20

Problem: Graph Representation
Link: (None)

Problem Statement:
Implement and analyze the fundamental ways to represent a graph (V vertices, E edges)
using Adjacency Matrix and Adjacency List structures, covering both **unweighted** (0/1)
and **weighted** (int W) edges, and **undirected** and **directed** connections.

-------------------------------------------------
✅ Approachs 1 (Adjacency Matrix)
- Idea: **Adjacency Matrix**. Use a 2D array (V x V) where M[i][j] stores the weight
  W of the edge between 'i' and 'j' (or 1/0 for unweighted, 0 for no edge).
- Time complexity (Edge Check): **O(1)**. Checking if an edge exists or getting its weight is instant: M[u][v].
- Space complexity: **O(V^2)**. Proportional to the square of the number of vertices.
- Limitations (if any): Very space-inefficient for **sparse graphs** (E << V^2). Iterating over all neighbors of a vertex takes O(V) time.

✅ Approachs 2 (Adjacency List)
- Idea: **Adjacency List**. Use an array or vector of size V, where each index 'i' holds a list of its adjacent vertices (and their associated weights, if weighted).
- Approach: Array of Vectors. Use `vector<int>` for unweighted; `vector<pair<int, int>>` for weighted (<neighbor, weight>).
- Algorithm: For each edge (u, v, W), add the entry to u's list (and v's list for undirected).
- Time complexity (Edge Check): **O(degree of u)**. Requires iterating through the list of neighbors for one of the vertices.
- Space complexity: **O(V + E)**. Proportional to the number of vertices plus the number of edges. This is highly efficient for **sparse graphs**.
- Limitations (if any): Checking if an edge (u, v) exists is slower than the matrix approach.

💡 Key Pattern:
- **Matrix vs. List:** Use the **Matrix** if V is small (dense graph) or if constant-time edge checking is critical. Use the **List** if V is large (sparse graph) or if iteration over neighbors is the primary operation.

ℹ️ Keywords:
- Graph Theory, Adjacency Matrix, Adjacency List, Weighted Graph, Directed Graph, Undirected Graph

🗒️ Notes
- Matrix functions return `vector<vector<int>>` where non-zero values are weights.
- List functions return `vector<vector<int>>` for unweighted and `vector<vector<pair<int, int>>>` for weighted.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)

// =========================================================================
// UNDIRECTED GRAPH REPRESENTATIONS
// =========================================================================

/**
 * @brief Creates an Adjacency Matrix (unweighted) for an undirected graph.
 * @return A 2D matrix (0 or 1).
 */
vector<vector<int>> createUndirectedAdjMat()
{
    int vertex, edges;
    cout << "\n--- Undirected Adjacency Matrix (Unweighted) ---\n";
    cout << "Enter number of vertex: ";
    cin >> vertex;
    cout << "Enter no of edges:";
    cin >> edges;
    vector<vector<int>> graph(vertex, vector<int>(vertex, 0));

    cout << "Enter edges (u v, 0-indexed):";
    FOR(i, 0, edges)
    {
        int u, v;
        cin >> u >> v;
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
 * @brief Creates an Adjacency Matrix (weighted) for an undirected graph.
 * @return A 2D matrix where M[i][j] stores the weight.
 */
vector<vector<int>> createUndirectedWeightedAdjMat()
{
    int vertex, edges;
    cout << "\n--- Undirected Adjacency Matrix (Weighted) ---\n";
    cout << "Enter number of vertex: ";
    cin >> vertex;
    cout << "Enter no of edges:";
    cin >> edges;
    vector<vector<int>> graph(vertex, vector<int>(vertex, 0));

    cout << "Enter edges (u v weight, 0-indexed):";
    FOR(i, 0, edges)
    {
        int u, v, w;
        cin >> u >> v >> w;
        if (u >= 0 && u < vertex && v >= 0 && v < vertex)
        {
            graph[u][v] = w;
            graph[v][u] = w;
        }
        else
        {
            cout << "Warning: Edge " << u << " " << v << " " << w << " is out of bounds. Skipped.\n";
        }
    }
    return graph;
}

/**
 * @brief Creates an Adjacency List (unweighted) for an undirected graph.
 * @return A vector of vectors of ints.
 */
vector<vector<int>> createUndirectedAdjList()
{
    int vertex, edges;
    cout << "\n--- Undirected Adjacency List (Unweighted) ---\n";
    cout << "Enter number of vertex:";
    cin >> vertex;
    vector<vector<int>> adjList(vertex);
    cout << "Enter number of edges:";
    cin >> edges;
    cout << "Enter edges (u v, 0-indexed): ";
    FOR(i, 0, edges)
    {
        int u, v;
        cin >> u >> v;
        if (u >= 0 && u < vertex && v >= 0 && v < vertex)
        {
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
        else
        {
            cout << "Warning: Edge " << u << " " << v << " is out of bounds. Skipped.\n";
        }
    }
    return adjList;
}

/**
 * @brief Creates an Adjacency List (weighted) for an undirected graph.
 * @return A vector of vectors of pairs<neighbor, weight>.
 */
vector<vector<pair<int, int>>> createUndirectedWeightedAdjList()
{
    int vertex, edges;
    cout << "\n--- Undirected Adjacency List (Weighted) ---\n";
    cout << "Enter number of vertex:";
    cin >> vertex;
    vector<vector<pair<int, int>>> adjList(vertex);
    cout << "Enter number of edges:";
    cin >> edges;
    cout << "Enter edges (u v weight, 0-indexed): ";
    FOR(i, 0, edges)
    {
        int u, v, w;
        cin >> u >> v >> w;
        if (u >= 0 && u < vertex && v >= 0 && v < vertex)
        {
            adjList[u].push_back({v, w});
            adjList[v].push_back({u, w});
        }
        else
        {
            cout << "Warning: Edge " << u << " " << v << " " << w << " is out of bounds. Skipped.\n";
        }
    }
    return adjList;
}

// =========================================================================
// DIRECTED GRAPH REPRESENTATIONS
// =========================================================================

/**
 * @brief Creates an Adjacency Matrix (unweighted) for a directed graph.
 * @return A 2D matrix (0 or 1).
 */
vector<vector<int>> createDirectedAdjMat()
{
    int vertex, edges;
    cout << "\n--- Directed Adjacency Matrix (Unweighted) ---\n";
    cout << "Enter number of vertex: ";
    cin >> vertex;
    cout << "Enter no of edges:";
    cin >> edges;
    vector<vector<int>> graph(vertex, vector<int>(vertex, 0));

    cout << "Enter directed edges (u v, 0-indexed, where u -> v):";
    FOR(i, 0, edges)
    {
        int u, v;
        cin >> u >> v;
        if (u >= 0 && u < vertex && v >= 0 && v < vertex)
        {
            graph[u][v] = 1;
        }
        else
        {
            cout << "Warning: Edge " << u << " " << v << " is out of bounds. Skipped.\n";
        }
    }
    return graph;
}

/**
 * @brief Creates an Adjacency Matrix (weighted) for a directed graph.
 * @return A 2D matrix where M[i][j] stores the weight.
 */
vector<vector<int>> createDirectedWeightedAdjMat()
{
    int vertex, edges;
    cout << "\n--- Directed Adjacency Matrix (Weighted) ---\n";
    cout << "Enter number of vertex: ";
    cin >> vertex;
    cout << "Enter no of edges:";
    cin >> edges;
    vector<vector<int>> graph(vertex, vector<int>(vertex, 0));

    cout << "Enter directed edges (u v weight, 0-indexed, where u -> v):";
    FOR(i, 0, edges)
    {
        int u, v, w;
        cin >> u >> v >> w;
        if (u >= 0 && u < vertex && v >= 0 && v < vertex)
        {
            graph[u][v] = w;
        }
        else
        {
            cout << "Warning: Edge " << u << " " << v << " " << w << " is out of bounds. Skipped.\n";
        }
    }
    return graph;
}

/**
 * @brief Creates an Adjacency List (unweighted) for a directed graph.
 * @return A vector of vectors of ints.
 */
vector<vector<int>> createDirectedAdjList()
{
    int vertex, edges;
    cout << "\n--- Directed Adjacency List (Unweighted) ---\n";
    cout << "Enter number of vertex:";
    cin >> vertex;
    vector<vector<int>> adjList(vertex);
    cout << "Enter number of edges:";
    cin >> edges;
    cout << "Enter directed edges (u v, 0-indexed, where u -> v): ";
    FOR(i, 0, edges)
    {
        int u, v;
        cin >> u >> v;
        if (u >= 0 && u < vertex && v >= 0 && v < vertex)
        {
            adjList[u].push_back(v);
        }
        else
        {
            cout << "Warning: Edge " << u << " " << v << " is out of bounds. Skipped.\n";
        }
    }
    return adjList;
}

/**
 * @brief Creates an Adjacency List (weighted) for a directed graph.
 * @return A vector of vectors of pairs<neighbor, weight>.
 */
vector<vector<pair<int, int>>> createDirectedWeightedAdjList()
{
    int vertex, edges;
    cout << "\n--- Directed Adjacency List (Weighted) ---\n";
    cout << "Enter number of vertex:";
    cin >> vertex;
    vector<vector<pair<int, int>>> adjList(vertex);
    cout << "Enter number of edges:";
    cin >> edges;
    cout << "Enter directed edges (u v weight, 0-indexed, where u -> v): ";
    FOR(i, 0, edges)
    {
        int u, v, w;
        cin >> u >> v >> w;
        if (u >= 0 && u < vertex && v >= 0 && v < vertex)
        {
            adjList[u].push_back({v, w});
        }
        else
        {
            cout << "Warning: Edge " << u << " " << v << " " << w << " is out of bounds. Skipped.\n";
        }
    }
    return adjList;
}

// =========================================================================
// PRINTING FUNCTIONS
// =========================================================================

/**
 * @brief Prints the Adjacency List representation for unweighted graphs.
 * @param adjList The adjacency list (vector of vectors of ints).
 * @param isDirected Flag to indicate if the graph is directed.
 */
void printAdjList(vector<vector<int>> adjList, bool isDirected)
{
    cout << "\n--- Adjacency List Output (" << (isDirected ? "Directed" : "Undirected") << ", Unweighted) ---\n";
    FOR(i, 0, adjList.size())
    {
        cout << "Vertex " << i << " -> ";
        if (adjList[i].empty())
        {
            cout << " (No neighbors)";
        }
        else
        {
            for (int v : adjList[i])
                cout << v << " ";
        }
        cout << "\n";
    }
}

/**
 * @brief Prints the Adjacency List representation for weighted graphs.
 * @param adjList The adjacency list (vector of vectors of pairs).
 * @param isDirected Flag to indicate if the graph is directed.
 */
void printWeightedAdjList(vector<vector<pair<int, int>>> adjList, bool isDirected)
{
    cout << "\n--- Adjacency List Output (" << (isDirected ? "Directed" : "Undirected") << ", Weighted) ---\n";
    FOR(i, 0, adjList.size())
    {
        cout << "Vertex " << i << " -> ";
        if (adjList[i].empty())
        {
            cout << " (No neighbors)";
        }
        else
        {
            for (auto const &p : adjList[i])
                cout << "(" << p.first << ", w=" << p.second << ") ";
        }
        cout << "\n";
    }
}

/**
 * @brief Prints the Adjacency Matrix representation (unweighted or weighted).
 * @param graph The adjacency matrix (vector of vectors of int).
 * @param isDirected Flag to indicate if the graph is directed.
 */
void printAdjMat(vector<vector<int>> graph, bool isDirected, bool isWeighted)
{
    cout << "\n--- Adjacency Matrix Output (" << (isDirected ? "Directed" : "Undirected") << ", " << (isWeighted ? "Weighted" : "Unweighted") << ") ---\n";
    int n = graph.size();

    // Print column headers
    cout << "  ";
    FOR(j, 0, n)
        cout << j << (j < 10 ? " " : ""); // Basic formatting for single digits
    cout << "\n";

    // Print separator
    cout << "  ";
    FOR(j, 0, n)
        cout << "--";
    cout << "\n";

    // Print rows
    FOR(i, 0, n)
    {
        cout << i << "|"; // Row header
        FOR(j, 0, n)
        cout << graph[i][j] << " ";
        cout << "\n";
    }
}

// =========================================================================
// MAIN EXECUTION
// =========================================================================

int main()
{
    // Note: You will be prompted for V and E for each example.

    // UNWEIGHTED EXAMPLES

    // 1. Undirected Adjacency Matrix (Unweighted)
    vector<vector<int>> graphMatUndirected = createUndirectedAdjMat();
    printAdjMat(graphMatUndirected, false, false);

    // 2. Undirected Adjacency List (Unweighted)
    vector<vector<int>> adjListUndirected = createUndirectedAdjList();
    printAdjList(adjListUndirected, false);

    // 3. Directed Adjacency Matrix (Unweighted)
    vector<vector<int>> graphMatDirected = createDirectedAdjMat();
    printAdjMat(graphMatDirected, true, false);

    // 4. Directed Adjacency List (Unweighted)
    vector<vector<int>> adjListDirected = createDirectedAdjList();
    printAdjList(adjListDirected, true);

    // WEIGHTED EXAMPLES

    // 5. Undirected Adjacency Matrix (Weighted)
    vector<vector<int>> graphMatUndirectedW = createUndirectedWeightedAdjMat();
    printAdjMat(graphMatUndirectedW, false, true);

    // 6. Undirected Adjacency List (Weighted)
    vector<vector<pair<int, int>>> adjListUndirectedW = createUndirectedWeightedAdjList();
    printWeightedAdjList(adjListUndirectedW, false);

    // 7. Directed Adjacency Matrix (Weighted)
    vector<vector<int>> graphMatDirectedW = createDirectedWeightedAdjMat();
    printAdjMat(graphMatDirectedW, true, true);

    // 8. Directed Adjacency List (Weighted)
    vector<vector<pair<int, int>>> adjListDirectedW = createDirectedWeightedAdjList();
    printWeightedAdjList(adjListDirectedW, true);

    return 0;
}
