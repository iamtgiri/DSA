/*
File: Valid_Library_Log.cpp
Date: 2025-11-09 16:52

Problem: Valid Library Log

Problem Statement:
A library maintains a log of book transactions as a string S,
where each character represents one event:
    'I' — A book is Issued
    'R' — A book is Returned
A log is considered valid if:
    1. In every prefix of the log, the number of 'R' characters <= number of 'I' characters.
    2. At the end of the log, the total number of 'I' = total number of 'R'.

Your task is to remove the minimum number of characters from the
string so that the remaining log becomes valid, and then output all
possible valid logs after such minimal removals.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Generate all possible subsequences of the input string S, and for each
  subsequence, check if it satisfies both validity conditions.
- Time complexity: O(N * 2^N), where N is the length of S. (2^N subsequences, O(N) check per subsequence).
- Space complexity: O(N * 2^N) to store all valid subsequences found.
- Limitations: Exponential time complexity; too slow for large N.

Current/Optimized Approachs
- Idea: Since we need the *minimum* number of removals, we can model the problem as
  finding the shortest path (in terms of removal depth) to a valid state, which is
  perfect for **Breadth-First Search (BFS)**.
- Approach: **BFS on State Space**
- Algorithm:
  1. Initialize a queue with the original string S.
  2. Use a set (`visited`) to store processed strings to avoid cycles and redundant work.
  3. Start BFS, level by level. Each level represents one more character removal.
  4. In each iteration, check if the current string (`cur`) is valid using `isValid()`.
     a. If **valid**, add it to the result list and set a flag (`found = true`).
     b. If `found` is true, we stop queueing new strings for the next level, ensuring we only capture valid logs at the *current* minimal removal depth.
  5. If **not valid**, generate all possible strings (`next`) by removing one 'I' or 'R' character from `cur`. If `next` hasn't been visited, add it to `visited` and push it to the queue.
- Time complexity: A precise analysis is complex, but the upper bound remains O(N * 2^N) in the worst case (though much faster in practice due to pruning).
- Space complexity: O(N * C), where C is the number of visited states (strings), potentially O(N*2^N) in the worst case.

💡 Key Pattern:
- **BFS for Minimal Changes:** When searching for solutions that require the minimum number
  of operations (removals, insertions, swaps), BFS guarantees finding the shortest path first.

ℹ️ Keywords:
- BFS, Minimum Removals, Stack/Balance Check, String Manipulation, State Space Search.

🗒️ Notes
- This problem maps directly to balanced parentheses logic: 'I' is '(' and 'R' is ')'. The
  key is the prefix constraint (never R > I) and the final constraint (Total R = Total I).
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Checks if a log string is valid.
     * A log is valid if:
     * 1. The balance (I - R) never drops below zero.
     * 2. The final balance is zero.
     * @param s The log string to check.
     * @return True if valid, False otherwise.
     */
    bool isValid(const string &s)
    {
        int balance = 0;
        for (char c : s)
        {
            if (c == 'I')
                balance++;
            else if (c == 'R')
            {
                balance--;
                // Condition 1: Number of 'R's cannot exceed 'I's in any prefix
                if (balance < 0)
                    return false;
            }
        }
        // Condition 2: Total number of 'I' must equal total number of 'R'
        return balance == 0;
    }

    /**
     * @brief Finds all valid logs with the minimum number of character removals.
     * @param s The initial corrupted log string.
     * @return A sorted vector of all possible valid logs after minimal removals.
     */
    vector<string> removeInvalidLogs(string s)
    {
        unordered_set<string> visited;
        queue<string> q;
        vector<string> result;
        bool found = false;

        q.push(s);
        visited.insert(s);

        while (!q.empty())
        {
            string cur = q.front();
            q.pop();

            // 1. Check for validity at the current minimal removal level
            if (isValid(cur))
            {
                result.push_back(cur);
                found = true;
            }

            // If we found a valid log in this level (minimal removals),
            // we stop exploring deeper levels. We continue the loop to
            // collect all valid strings *at this level*.
            if (found)
                continue;

            // 2. Generate next level of strings (one more removal)
            for (int i = 0; i < cur.size(); ++i)
            {
                // We only remove 'I' and 'R' characters
                if (cur[i] != 'I' && cur[i] != 'R')
                    continue;

                // Remove character at index i
                string next = cur.substr(0, i) + cur.substr(i + 1);

                // Add to queue only if not visited
                if (visited.find(next) == visited.end())
                {
                    visited.insert(next);
                    q.push(next);
                }
            }
        }

        // The problem often requires the output to be sorted
        sort(result.begin(), result.end());
        return result;
    }

    // Utility function to print the vector result
    void printVector(const vector<string> &v)
    {
        cout << "{";
        for (size_t i = 0; i < v.size(); ++i)
        {
            cout << "\"" << v[i] << "\"";
            if (i < v.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "}" << endl;
    }
};


int main() {
    Solution sol;
    vector<string> results;

    // Test 1: Corrupted prefix and imbalance
    string s1 = "RIIIR";
    cout << "Input: " << s1 << "\n";
    results = sol.removeInvalidLogs(s1);
    cout << "Output (minimal removals): ";
    sol.printVector(results); // Expected: {"IR"}

    // Test 2: One extra 'I' at end
    string s2 = "IIR";
    cout << "Input: " << s2 << "\n";
    results = sol.removeInvalidLogs(s2);
    cout << "Output (minimal removals): ";
    sol.printVector(results); // Expected: {"IR"}

    // Test 3: Prefix violation (starts with R)
    string s3 = "RIR";
    cout << "Input: " << s3 << "\n";
    results = sol.removeInvalidLogs(s3);
    cout << "Output (minimal removals): ";
    sol.printVector(results); // Expected: {"IR"}

    // Test 4: Already valid
    string s4 = "IIRR";
    cout << "Input: " << s4 << "\n";
    results = sol.removeInvalidLogs(s4);
    cout << "Output (minimal removals): ";
    sol.printVector(results); // Expected: {"IIRR"}

    // Test 5: Example from prompt
    string s5 = "IRIRRIR";
    cout << "Input: " << s5 << "\n";
    results = sol.removeInvalidLogs(s5);
    cout << "Output (minimal removals): ";
    sol.printVector(results); // Expected: {"IIRRIR", "IRIRIR"}

    return 0;
}