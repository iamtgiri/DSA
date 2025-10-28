/*
File: Alien_Dictionary.cpp
Date: 2025-10-28 10:48

Problem: Alien Dictionary
Link: https://www.geeksforgeeks.org/problems/alien-dictionary/1

Problem Statement:
Given a sorted list of words (lexicographically) from an alien language, find
the order of characters in that language. If the order is impossible (due to
a contradiction/cycle), return an empty string. Assume all characters are
lowercase English letters.

-------------------------------------------------
❌ Brute Force
- Idea: Try every possible permutation of the unique characters (C!) and check
  if the generated order is consistent with the given sorted word list.
- Time complexity: O(C! * N * L), where C is the number of unique characters,
  N is the number of words, and L is the max word length.
- Space complexity: O(C) for storing the character permutation.
- Limitations: Factorial complexity is prohibitively slow, even for small C (e.g., C=26).

✅ Optimized Approachs
- Idea: The problem is one of dependency resolution: if word 'A' comes before
  word 'B', the first differing character in 'A' must come before the first
  differing character in 'B'. This forms a directed graph where an edge
  u -> v means u must precede v.
- Approach: **Topological Sort (Kahn's Algorithm)**.
- Algorithm:
    1. **Initialization:** Identify all unique characters (nodes, C) and initialize
       their indegrees to zero.
    2. **Graph Construction:** Iterate through adjacent pairs of words (W_i-1, W_i).
       Find the first index j where W_i-1[j] != W_i[j]. Add a directed
       edge W_i-1[j] -> W_i[j]. Check for the invalid prefix rule
       (e.g., "abc" before "ab"). Use a set to prevent adding duplicate edges
       and correctly update indegrees.
    3. **Kahn's Algorithm:** Use a queue to process characters with indegree=0.
       Dequeue, append to the result, decrement neighbors' indegrees, and enqueue
       any neighbor whose indegree drops to zero.
    4. **Cycle Check:** If the resulting string contains all unique characters,
       return the string. Otherwise, a cycle exists, return an empty string.
- Time complexity: O(N * L + C + E). Dominated by **O(N * L + C)**, where N is
  number of words, L is max word length, C is number of characters, and E is number
  of edges (E <= N*L).
- Space complexity: O(C + E) for adjacency list and indegree map.

💡 Key Pattern:
- **Topological Sort:** Always the go-to pattern for ordering problems
  (dependencies, prerequisites, build sequence).

ℹ️ Keywords:
- Directed Acyclic Graph (DAG), Topological Sort, Kahn's Algorithm, Lexicographical Order.

🗒️ Notes
- The use of `unordered_set<char>` for the adjacency list handles duplicate
  dependencies cleanly by only incrementing the indegree once per unique edge.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Determines the lexicographical order of characters in an alien language.
     * @param words A vector of strings sorted according to the alien alphabet.
     * @return The string representing the valid character order, or an empty string
     * if a cycle (impossible order) is detected.
     */
    string findOrder(vector<string> &words)
    {
        // 1. Collect all unique characters (nodes)
        unordered_set<char> chars;
        for (const string &w : words)
            for (char c : w)
                chars.insert(c);

        // Adjacency list: character -> set of dependent characters
        unordered_map<char, unordered_set<char>> adj;
        // Indegree map: character -> number of prerequisites
        unordered_map<char, int> indeg;
        for (char c : chars)
            indeg[c] = 0;

        // 2. Build edges (dependencies)
        for (size_t i = 1; i < words.size(); ++i)
        {
            const string &a = words[i - 1];
            const string &b = words[i];
            size_t minlen = min(a.size(), b.size());
            size_t j = 0;

            // Find the first differing character
            while (j < minlen && a[j] == b[j])
                ++j;

            if (j == minlen)
            {
                // Check for invalid prefix rule: e.g., "abc" followed by "ab"
                if (a.size() > b.size())
                {
                    return ""; // Longer word cannot precede its prefix
                }
                // If a.size() <= b.size(), no ordering info from this pair.
            }
            else
            {
                char from = a[j], to = b[j];
                // Add edge from -> to if it doesn't exist yet
                if (adj[from].insert(to).second)
                {
                    indeg[to] += 1;
                }
            }
        }

        // 3. Kahn's algorithm for topological sort
        queue<char> q;
        // Start with characters that have no prerequisites
        for (auto &p : indeg)
        {
            if (p.second == 0)
                q.push(p.first);
        }

        string order;
        while (!q.empty())
        {
            char c = q.front();
            q.pop();
            order.push_back(c);

            // Process neighbors (dependent characters)
            if (adj.count(c))
            {
                for (char nei : adj[c])
                {
                    indeg[nei]--;
                    if (indeg[nei] == 0)
                        q.push(nei);
                }
            }
        }

        // 4. Cycle check
        // If the number of characters in the order equals the total number of unique characters, success
        if (order.size() == chars.size())
            return order;
        return ""; // Cycle exists -> impossible to find a valid order
    }
};

// Helper function to print a vector of strings
void printWords(const vector<string> &words)
{
    cout << "{";
    for (size_t i = 0; i < words.size(); ++i)
    {
        cout << "\"" << words[i] << "\"";
        if (i < words.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << "}";
}

int main()
{
    Solution sol;

    cout << "--- Alien Dictionary Order Finder ---\n";

    // Test Case 1: Simple linear order
    // Dependencies: w->e, e->r, r->t
    vector<string> words1 = {"wert", "weert", "wet"};
    string result1 = sol.findOrder(words1);
    cout << "Test 1 | Words: ";
    printWords(words1);
    cout << "\nResult: \"" << result1 << "\" (Expected: \"w...e...t\")\n";
    cout << "--------------------------------\n";

    // Test Case 2: Full alphabet cycle check
    // Dependencies: c->a, a->t, t->c (Cycle)
    vector<string> words2 = {"cat", "ca", "dog"}; // Invalid prefix "ca" after "cat" is not handled here, only t->d
    // The problem statement logic: If words is {"wrt", "wrf", "er", "ett", "rftt"}
    // w->e, r->t, t->f, w->e, r->f
    // Unique chars: w, r, t, f, e
    vector<string> words3 = {"wrt", "wrf", "er", "ett", "rftt"};
    string result3 = sol.findOrder(words3);
    cout << "Test 3 | Words: ";
    printWords(words3);
    cout << "\nResult: \"" << result3 << "\" (Expected: valid permutation like \"wertf\" or \"wterf\")\n";
    cout << "--------------------------------\n";

    // Test Case 4: Impossible order (Cycle)
    // Dependencies: a->b, b->c, c->a
    vector<string> words4 = {"a", "b", "c", "a"}; // Assumes problem has more complexity.
    // If words are: {"caa", "aaa", "aab"}
    // c->a, a->b
    vector<string> words5 = {"caa", "aaa", "aab"};
    string result5 = sol.findOrder(words5);
    cout << "Test 5 | Words: ";
    printWords(words5);
    cout << "\nResult: \"" << result5 << "\" (Expected: \"cba\")\n";
    cout << "--------------------------------\n";

    // Test Case 6: Invalid Prefix (Should return "")
    // Dependencies: "abc" before "ab"
    vector<string> words6 = {"abc", "ab"};
    string result6 = sol.findOrder(words6);
    cout << "Test 6 | Words: ";
    printWords(words6);
    cout << "\nResult: \"" << result6 << "\" (Expected: \"\")\n";
    cout << "--------------------------------\n";

    return 0;
}
