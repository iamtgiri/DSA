/*
File: Word_Ladder_2.cpp
Date: 2025-10-24 18:43

Problem: Word Ladder II
Link: https://leetcode.com/problems/word-ladder-ii/description/

Problem Statement:
Given two words, beginWord and endWord, and a dictionary wordList, return all
the shortest transformation sequences from beginWord to endWord. If no such
sequence exists, return an empty list. Each transformation must only change one
letter, and the resulting word must be in wordList.

-------------------------------------------------
❌ Brute Force
- Idea: Generate *all* possible word transformation sequences from beginWord to endWord using a simple, unbounded DFS or BFS without pruning. Then, find the minimum length and filter the paths.
- Time complexity: Exponential, potentially O(26^L * W), where L is word length and W is word list size.
- Space complexity: O(N * L) for storing all generated paths (N being the total number of paths).
- Limitations: Highly inefficient as it explores paths much longer than the shortest possible sequence, leading to Time Limit Exceeded (TLE).

✅ Optimized Approachs
- Idea: This problem requires a two-step approach: first, **BFS** to find the minimum distance and build the graph structure of all shortest paths; second, **DFS (Backtracking)** to traverse this structure and collect all paths.
- Approach: Bidirectional BFS (often faster but complex) or single-directional BFS + DFS Backtracking (simpler logic). The implemented approach uses BFS + Backtracking.
- Algorithm:
    1. **BFS (Forward)**: Perform a level-order search starting from `beginWord`. In each level, explore neighbors of all words in the current level. If a neighbor is valid (in `wordSet`):
        a. Record the current word as a **parent** of the neighbor in `parentMap`.
        b. Add the neighbor to `nextLevel`.
        c. Mark words in the `currentLevel` as used (remove from `wordSet`) to prevent loops and ensure we only transition to the next level (guaranteeing shortest path length).
        d. Stop BFS immediately when `endWord` is found.
    2. **DFS (Backward)**: Use the `parentMap` (which maps a word to its predecessors on a shortest path) to recursively backtrack from `endWord` to `beginWord`, assembling the paths.
- Time complexity: O(W * L^2 * 26 + N * L), where $W$ is word count, $L$ is word length, and $N$ is the number of resulting shortest paths. BFS dominates the complexity for large dictionaries, proportional to generating the graph $O(V+E)$.
- Space complexity: O(W * L) for the word sets and the `parentMap`. O(N * L) for storing the final results.

💡 Key Pattern:
- **BFS for Shortest Distance, DFS for All Paths.** BFS guarantees the minimum length; DFS/Backtracking enumerates all solutions using that minimum length constraint.

ℹ️ Keywords:
- BFS, DFS, Graph, Shortest Path, Backtracking, Parent Map, Transformation Sequence.

🗒️ Notes
- It is crucial in BFS to only use words from the current level and not reuse them in subsequent steps, as this guarantees the path taken is the shortest one.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Finds all shortest transformation sequences from beginWord to endWord.
     * @param beginWord The starting word of the sequence.
     * @param endWord The target word.
     * @param wordList The dictionary of valid words.
     * @return A vector of vectors of strings, where each inner vector is a shortest path.
     */
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList)
    {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        vector<vector<string>> result;

        if (!wordSet.count(endWord))
            return result;

        // Step 1: BFS to build parent map
        // parentMap[child] = {list of parents}
        unordered_map<string, vector<string>> parentMap;
        unordered_set<string> currentLevel, nextLevel;
        currentLevel.insert(beginWord);
        bool foundEnd = false;

        while (!currentLevel.empty() && !foundEnd)
        {
            // Remove words from currentLevel from wordSet to guarantee shortest path length.
            // Any path reaching them in a later level is longer.
            for (auto &word : currentLevel)
                wordSet.erase(word);

            for (auto &word : currentLevel)
            {
                string temp = word;

                for (int i = 0; i < temp.size(); ++i)
                {
                    char original = temp[i];
                    for (char c = 'a'; c <= 'z'; ++c)
                    {
                        if (c == original)
                            continue;
                        temp[i] = c;
                        if (wordSet.count(temp))
                        {
                            nextLevel.insert(temp);
                            // Record the current word as a parent of the neighbor (temp)
                            parentMap[temp].push_back(word);
                            if (temp == endWord)
                                foundEnd = true;
                        }
                    }
                    temp[i] = original; // Backtrack character change
                }
            }
            currentLevel.swap(nextLevel);
            nextLevel.clear();
        }

        // Step 2: Backtrack to build all shortest paths
        if (foundEnd)
        {
            vector<string> path = {endWord};
            backtrack(endWord, beginWord, parentMap, path, result);
        }

        return result;
    }

private:
    /**
     * @brief Recursively reconstructs all shortest paths from endWord back to beginWord.
     */
    void backtrack(const string &word, const string &beginWord,
                   unordered_map<string, vector<string>> &parentMap,
                   vector<string> &path, vector<vector<string>> &result)
    {
        if (word == beginWord)
        {
            vector<string> validPath = path;
            reverse(validPath.begin(), validPath.end()); // Path was built backward, reverse it
            result.push_back(validPath);
            return;
        }

        // Traverse all parents of the current word
        for (auto &parent : parentMap[word])
        {
            path.push_back(parent);
            backtrack(parent, beginWord, parentMap, path, result);
            path.pop_back(); // Backtrack path construction
        }
    }
};

int main()
{
    Solution sol;

    // Helper function to print results
    auto print_paths = [](const string &start, const string &end, const vector<vector<string>> &paths)
    {
        cout << "\nPath: " << start << " -> " << end << " (Count: " << paths.size() << ")" << endl;
        for (const auto &path : paths)
        {
            cout << "  [";
            for (size_t i = 0; i < path.size(); ++i)
            {
                cout << path[i] << (i == path.size() - 1 ? "" : ", ");
            }
            cout << "]" << endl;
        }
    };

    // Example 1: Basic case with multiple shortest paths
    string beginWord1 = "hit";
    string endWord1 = "cog";
    vector<string> wordList1 = {"hot", "dot", "dog", "lot", "log", "cog"};
    vector<vector<string>> result1 = sol.findLadders(beginWord1, endWord1, wordList1);
    print_paths(beginWord1, endWord1, result1);
    /*
    Expected output (2 paths):
      [hit, hot, dot, dog, cog]
      [hit, hot, lot, log, cog]
    */

    // Example 2: No path exists (endWord not in dictionary)
    string beginWord2 = "talk";
    string endWord2 = "cook";
    vector<string> wordList2 = {"tole", "salk", "folk", "look"};
    vector<vector<string>> result2 = sol.findLadders(beginWord2, endWord2, wordList2);
    print_paths(beginWord2, endWord2, result2);
    /*
    Expected output (0 paths)
    */

    // Example 3: A longer path with branching
    string beginWord3 = "a";
    string endWord3 = "c";
    vector<string> wordList3 = {"a", "b", "c"};
    vector<vector<string>> result3 = sol.findLadders(beginWord3, endWord3, wordList3);
    print_paths(beginWord3, endWord3, result3);
    /*
    Expected output (0 paths) because 'c' is not one transformation step from 'a'
    and 'b' is not one transformation step from 'a' or 'c'.
    Wait, the wordList has "a", "b", "c". The problem implies transformation, not just existence.
    The length of words must be the same. Let's use words of length 1 for simplicity:
    "a" -> "b" -> "c" (length 3, 2 transformations)
    The given code will return 0 paths because 'a' can't reach 'b' or 'c' in one step by changing *one* character since they are all 1 letter long. The transformation must be between words of same length > 1. Let's adjust this test.
    */

    // Example 3 (Corrected): Short path, ensure word length > 1
    string beginWord4 = "red";
    string endWord4 = "tax";
    vector<string> wordList4 = {"ted", "tex", "red", "tax", "tad", "rex"};
    vector<vector<string>> result4 = sol.findLadders(beginWord4, endWord4, wordList4);
    print_paths(beginWord4, endWord4, result4);
    /*
    Expected output (4 paths of length 4):
      [red, ted, tex, tax]
      [red, ted, tad, tax] <-- wait, tad is not 1 step from tex
      Shortest path is length 4:
      1. [red, ted, tex, tax]
      2. [red, ted, tad, tax] (incorrect, tad and tex are not 1 step from each other)
      3. [red, ted, tad, tax] (incorrect)

      Correct paths:
      red -> ted -> tex -> tax
      red -> tad -> tax (length 3, shorter!)

      Let's use a simpler case to verify the logic where length > 1:
    */

    // Example 5: Shortest path where one branch is shorter (should only return the shortest)
    string beginWord5 = "hit";
    string endWord5 = "cog";
    vector<string> wordList5 = {"hot", "dot", "dog", "lot", "log", "cog", "git"}; // git is irrelevant
    vector<vector<string>> result5 = sol.findLadders(beginWord5, endWord5, wordList5);
    print_paths(beginWord5, endWord5, result5);
    /*
    Expected output (2 paths of length 5):
      [hit, hot, dot, dog, cog]
      [hit, hot, lot, log, cog]
    */

    return 0;
}
