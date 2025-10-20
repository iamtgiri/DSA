/*
File: Word_Ladder.cpp
Date: 2025-10-20 12:28

Problem: Word Ladder
Link: https://leetcode.com/problems/word-ladder/description/

Problem Statement:
Given two words, `beginWord` and `endWord`, and a dictionary `wordList`, find
the length of the shortest transformation sequence from `beginWord` to `endWord`
such that:
1. Only one letter can be changed at each step.
2. Each intermediate word must exist in the `wordList`.
If no such sequence exists, return 0.

----------------------------------------------------------------------------------
❌ Brute Force
- Idea: Recursively explore all possible valid paths from `startWord` to
  `targetWord` using DFS or exhaustive path checking, without prioritizing
  shorter paths.
- Time complexity: Exponential, potentially O(N!). Highly dependent on the graph structure.
- Space complexity: O(N * L) for storing paths, where N is the number of words
  and L is the word length.
- Limitations: Extremely inefficient and prone to Time Limit Exceeded (TLE).

✅ Optimized Approachs
- Idea: The problem asks for the **shortest path** in an unweighted graph (where
  words are nodes and single-letter changes are edges). **BFS** is optimal for
  shortest path in unweighted graphs.
- Approach: Breadth-First Search (BFS) using neighbor generation.
- Algorithm:
  1. Store `wordList` in an **unordered_set** (`words`) for O(1) lookup and deletion.
  2. Use a **queue** to store `(word, length)` pairs, starting with `(startWord, 1)`.
  3. In the BFS loop, for the current `node`, generate all possible **one-letter** mutations.
  4. For each mutation:
     a. If it equals `targetWord`, return `length + 1`.
     b. If it exists in the `words` set, enqueue it with `length + 1` and remove
        it from the set to mark it as visited.
- Time complexity: O(N * L^2). N is number of words, L is word length. For each
  word, we check L positions, and for each position, we try 26 letters. String
  operations (creation/lookup) take O(L). Total: O(N * L * 26 * L) simplified
  to **O(N * L^2)** (where 26 is a constant).
- Space complexity: O(N * L) for the word set and the queue.

💡 Key Pattern:
- **Shortest Path in Unweighted Graph:** The requirement for the "shortest"
  sequence is the definitive signal to use **BFS**.
- **On-the-fly Graph Construction:** Instead of pre-building a full graph
  adjacency list, generate neighbors (one-letter diff words) dynamically during
  the BFS traversal.

ℹ️ Keywords:
- BFS, Shortest Path, Graph Traversal, Word Transformation, Hash Set, Queue.

🗒️ Notes
- Using `unordered_set` is crucial for performance.
- Deleting visited words (`words.erase(temp)`) prevents cycles and redundant work.
- The same problem can be solved with **Bi-directional BFS**, which can offer
  significant speedup by meeting in the middle.
----------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Computes the length of the shortest word transformation sequence using BFS.
     * @param startWord The beginning word of the sequence.
     * @param targetWord The ending word of the sequence.
     * @param wordList The list of valid intermediate words.
     * @return The length of the shortest sequence, or 0 if no sequence exists.
     */
    int ladderLength(string startWord, string targetWord,
                     vector<string> &wordList)
    {

        // 1. Initialize words set and check target
        unordered_set<string> words(wordList.begin(), wordList.end());
        if (!words.count(targetWord))
            return 0;

        // 2. Initialize BFS queue
        queue<pair<string, int>> q;
        q.push({startWord, 1});
        words.erase(startWord); // Mark start word as visited

        // 3. BFS traversal
        while (!q.empty())
        {
            // C++17 structured binding
            auto [node, len] = q.front();
            q.pop();

            if (node == targetWord)
                return len;

            // Generate and process neighbors
            addNbr(node, len, words, q);
        }
        return 0; // Target word not reachable
    }

private:
    /**
     * @brief Generates all one-letter difference neighbors of a given word.
     * @param node The current word being processed.
     * @param len The current length of the sequence up to 'node'.
     * @param words The set of unvisited valid words (modified by reference).
     * @param q The BFS queue (modified by reference).
     */
    void addNbr(const string &node, int len, unordered_set<string> &words,
                queue<pair<string, int>> &q)
    {

        string temp = node;
        // Iterate through all character positions
        for (int i = 0; i < temp.size(); ++i)
        {
            char original = temp[i];

            // Try replacing with all 26 lowercase letters
            for (char c = 'a'; c <= 'z'; ++c)
            {
                temp[i] = c;

                // Check if the mutated word is in the set
                if (words.count(temp))
                {
                    q.push({temp, len + 1});
                    words.erase(temp); // Mark as visited
                }
            }
            temp[i] = original; // Backtrack: restore the character for the next position check
        }
    }
};

// Helper function to execute and display test cases
void runTest(Solution &sol, const string &start, const string &target,
             vector<string> list, int expected)
{
    int result = sol.ladderLength(start, target, list);
    cout << "Start: " << start << ", Target: " << target << endl;
    cout << "WordList: {";
    for (const auto &w : list)
        cout << w << (w == list.back() ? "" : ", ");
    cout << "}" << endl;
    cout << "Result: " << result << " (Expected: " << expected << ")" << endl;
    cout << "---" << endl;
}

int main()
{
    Solution sol;

    // Test Case 1: Standard example (Length 5: hit -> hot -> dot -> dog -> cog)
    vector<string> list1 = {"hot", "dot", "dog", "lot", "log", "cog"};
    runTest(sol, "hit", "cog", list1, 5);

    // Test Case 2: No path possible
    vector<string> list2 = {"hot", "dot", "dog", "lot", "log"};
    runTest(sol, "hit", "cog", list2, 0);

    // Test Case 3: Simple path (Length 2: a -> b)
    vector<string> list3 = {"b"};
    runTest(sol, "a", "b", list3, 2);

    return 0;
}
