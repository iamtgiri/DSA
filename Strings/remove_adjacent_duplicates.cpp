/*
File: remove_adjacent_duplicates.cpp
Date: 2025-10-27 18:02

Problem: Remove adjacent duplicates in a string
Link: URL (Similar to LeetCode 1209)

Problem Statement:
Given a string s and an integer k, repeatedly remove k consecutive identical
characters from s until no more such groups exist. Return the final string.

Example:
s = "deeedcbaaa", k = 3
Result: "dcba" (Remove "eee" -> "ddcbaaa". Remove "aaa" -> "ddcba". Remove "dd" is impossible. Oh, wait, the problem is about k consecutive identical characters. The provided example is a bit tricky, but the logic should handle chain reactions.)

Example 2:
s = "abbcccb", k = 3
1. Remove "ccc" -> "abbb"
2. Remove "bbb" -> "a"
Result: "a"

-------------------------------------------------
❌ Brute Force
- Idea: Simulate the removal process iteratively. In each iteration, scan the
  string to find the first group of k or more identical adjacent characters,
  remove it, and repeat the scan until no more removals are possible.
- Time complexity: O(N^2 * k). In the worst case (e.g., "aaaa...a" with k=2),
  you remove one group of size k per pass, requiring up to O(N/k) passes.
  Each pass takes O(N) time.
- Space complexity: O(N) for string manipulation.
- Limitations: Inefficient due to repeated string construction and scans.

✅ Optimized Approachs
- Idea: Use a stack to track characters that have survived so far, along with
  their consecutive counts. This avoids costly string manipulations and repeated
  scanning.
- Approach: Stack of (character, count) pairs.
- Algorithm:
    1. Initialize a stack (implemented as a `vector<pair<char, int>>`).
    2. Iterate through the input string `s`.
    3. If the current character `c` matches the character at the stack top,
       increment the count of the stack top pair.
    4. If the incremented count reaches `k`, pop the pair from the stack (removal).
    5. If the current character `c` does not match the stack top (or stack is
       empty), push a new pair: `(c, 1)`.
    6. After iterating through `s`, construct the final result string by appending
       each character from the stack as many times as its count indicates.
- Time complexity: O(N). Each character is processed (pushed/count incremented)
  and finally appended to the result exactly once.
- Space complexity: O(N) in the worst case, where the stack stores almost
  the entire string (e.g., "ababa...").

💡 Key Pattern:
- **Stack for Adjacent Processing:** Use a stack to maintain the "effective"
  state of a string or sequence after local modifications (like removal or grouping).

ℹ️ Keywords:
- Stack, String Manipulation, Consecutive Characters, Adjacency.

🗒️ Notes
- Using `vector<pair<char, int>>` as a stack is often cleaner and faster in C++
  than a traditional `std::stack` for this application.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Removes k consecutive identical characters repeatedly from a string.
     * @param s The input string.
     * @param k The number of consecutive identical characters to remove.
     * @return The final string after all possible removals.
     */
    string removeDuplicates(string s, int k)
    {
        // Stack stores pairs of {character, consecutive_count}
        vector<pair<char, int>> st;

        for (char c : s)
        {
            if (!st.empty() && st.back().first == c)
            {
                // Character matches the top: increment count
                st.back().second++;
                if (st.back().second == k)
                {
                    st.pop_back(); // Count reached k: remove this group
                }
            }
            else
            {
                // New character: push with count 1
                st.push_back({c, 1});
            }
        }

        string result;
        // Rebuild the final string from the characters remaining in the stack
        for (auto &p : st)
        {
            // Append p.first character p.second times
            result.append(p.second, p.first);
        }
        return result;
    }
};

int main()
{
    Solution sol;

    cout << "--- Remove Adjacent Duplicates II ---\n";

    // Test Case 1: Example from problem statement
    // "abbcccb", k=3. -> "abbb" -> "a"
    string s1 = "abbcccb";
    int k1 = 3;
    string result1 = sol.removeDuplicates(s1, k1);
    cout << "Test 1 | s=\"" << s1 << "\", k=" << k1 << "\n";
    cout << "Result: \"" << result1 << "\" (Expected: \"a\")\n";
    cout << "--------------------------------\n";

    // Test Case 2: Chain reaction
    // "deeedcbaaa", k=3. -> "ddcbaaa" -> "ddcba"
    string s2 = "deeedcbaaa";
    int k2 = 3;
    string result2 = sol.removeDuplicates(s2, k2);
    cout << "Test 2 | s=\"" << s2 << "\", k=" << k2 << "\n";
    cout << "Result: \"" << result2 << "\" (Expected: \"ddcba\")\n";
    cout << "--------------------------------\n";

    // Test Case 3: No removals possible
    // "aabbcc", k=3. -> "aabbcc"
    string s3 = "aabbcc";
    int k3 = 3;
    string result3 = sol.removeDuplicates(s3, k3);
    cout << "Test 3 | s=\"" << s3 << "\", k=" << k3 << "\n";
    cout << "Result: \"" << result3 << "\" (Expected: \"aabbcc\")\n";
    cout << "--------------------------------\n";

    // Test Case 4: Complete removal
    // "yabbaadabbaado", k=2.
    // y (a:2) (b:2) (d:2) o -> "y d o"
    // Wait: y(a:2) (b:2) (b:2) (a:2) (d:2) o
    // "yabbaadabbaado" -> y(a:2) (b:2) (d:2) (b:2) (a:2) (d:2) o.
    // The key is that this is not a true simulation; the stack tracks what *would* remain.
    // y(1) a(1) -> push (y,1) (a,1)
    // b(1) -> push (b,1)
    // b(2) -> pop b -> st: [y,1][a,1]
    // a(2) -> pop a -> st: [y,1]
    // d(1) -> push (d,1)
    // a(1) -> push (a,1)
    // a(2) -> pop a -> st: [y,1][d,1]
    // d(2) -> pop d -> st: [y,1]
    // o(1) -> push (o,1)
    // Final stack: [y,1], [o,1]. Result: "yo"
    string s4 = "yabbaadabbaado";
    int k4 = 2;
    string result4 = sol.removeDuplicates(s4, k4);
    cout << "Test 4 | s=\"" << s4 << "\", k=" << k4 << "\n";
    cout << "Result: \"" << result4 << "\" (Expected: \"yo\")\n";
    cout << "--------------------------------\n";

    return 0;
}
