/*
File: Subsequence_Sort.cpp
Date: 2025-10-31 23:14

Problem: Subsequence Sort
Link: (Contextual problem: Can 'binary' form 'pattern' as a subsequence with prefix '1' count constraint?)

Problem Statement:
Given two binary strings, 'binary' (the source) and 'pattern' (the template containing '0', '1', or '?'),
determine if there exists a valid target string T that matches 'pattern' and can be obtained
as a subsequence of 'binary', subject to two conditions:
1. The total number of '1's in T must equal the total number of '1's in 'binary'.
2. For every prefix of length i, the count of '1's in T[0...i] must be less than or equal
   to the count of '1's in binary[0...i].

-------------------------------------------------
❌ Brute Force
- Idea: Recursively try all possible assignments for the '?' characters in 'pattern' (2^Q choices, where Q is the number of '?'). For each resulting target string T, check if it has the correct number of total '1's and then verify the prefix constraint against 'binary'.
- Time complexity: O(2^Q * N), where Q is the number of '?'s and N is the string length.
- Space complexity: O(N) for recursion stack and string copies.
- Limitations: Exponential time complexity makes it infeasible for large N.

✅ Optimized Approachs
- Idea: The problem involves minimizing a prefix sum subject to a global total sum, which suggests a **Greedy** choice. To satisfy the prefix constraint (T_i^1 <= B_i^1) at every step, we must assign '1' to a '?' *only when absolutely necessary*.
- Approach: **Greedy Prefix Minimal Assignment**.
- Algorithm:
    1. **Preprocessing (O(N)):** Calculate the prefix sums of '1's for 'binary' ($B_{prefix\_1s}$). Count the total '1's in 'binary' ($B_{1s}$) and the counts of '0's, '1's, and '?'s in 'pattern' ($pat_{0s}, pat_{1s}, pat_{q}$).
    2. **Total Count Check (O(1)):** Calculate the exact number of '?'s that must be converted to '1's: $Q_{1s\_needed} = B_{1s} - pat_{1s}$. If $Q_{1s\_needed}$ is outside the range $[0, pat_{q}]$, the total count constraint is impossible.
    3. **Greedy Assignment (O(N)):** Determine the target string T that uses these $Q_{1s\_needed}$ '1's while keeping the prefix '1' count ($T_{prefix\_1s}$) as low as possible at every index $i$. This is achieved by assigning '1' only to the $Q_{1s\_needed}$ **right-most** '?' positions.
    4. **Prefix Verification:** Iterate through $i=0$ to $N-1$:
        - Maintain $T_{prefix\_1s}$ based on the minimal prefix T.
        - If $T_{prefix\_1s} > B_{prefix\_1s}[i]$, return "NO".
    5. **Result:** If all checks pass, return "YES".

- Time complexity: **O(N)**, achieved through a single linear pass after O(N) preprocessing.
- Space complexity: **O(N)** for storing the prefix sum array.

💡 Key Pattern:
- **Prefix Sum Constraint:** When a sequence must satisfy a prefix sum inequality (like $T_i^1 \le B_i^1$), the optimal greedy strategy is often to construct the sequence that *minimizes* that prefix sum at every step, subject to the overall total constraint.

ℹ️ Keywords:
- Greedy Algorithm, Subsequence, Prefix Sum, Binary String, String Matching.

🗒️ Notes
- The logic simplifies the prefix check by pre-calculating the minimum $1$s required for the overall total, and then checking if this minimal $T$ violates any prefix rule. If the minimal $T$ fails, no other valid $T$ (which would have higher prefix sums) can succeed.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Checks if a binary string 'binary' can form a 'pattern' as a subsequence
     * while respecting prefix '1' count constraints.
     * @param binary The source binary string.
     * @param pattern The pattern string with '?', '0', or '1'.
     * @return "YES" if possible, "NO" otherwise.
     */
    string canObtain(string binary, string pattern)
    {
        int n = binary.size();
        if (n != pattern.size())
            return "NO"; // Should assume equal length based on problem context

        // 1. Preprocessing: Binary Counts
        int B_1s = count(binary.begin(), binary.end(), '1'); // Total 1s in binary

        // Precalculate binary prefix 1s: B_i^1
        vector<int> prefix_B_1s(n);
        int current_B_1s = 0;
        for (int i = 0; i < n; ++i)
        {
            current_B_1s += (binary[i] == '1');
            prefix_B_1s[i] = current_B_1s;
        }

        // 2. Preprocessing: Pattern Counts
        int pat_1s = 0; // Fixed '1's in pattern
        int pat_q = 0;  // '?' count
        for (char c : pattern)
        {
            if (c == '1')
                pat_1s++;
            else if (c == '?')
                pat_q++;
        }

        // 3. Total Count Constraint Check (Find Q_1s_needed)
        // We need T to have exactly B_1s ones.
        int Q_1s_needed = B_1s - pat_1s;

        // Check if the required number of '1's can be supplied by the '?'s
        if (Q_1s_needed < 0 || Q_1s_needed > pat_q)
            return "NO";

        // 4. Greedy Prefix Check (Minimal T)
        // Strategy: Assign '1' only to the Q_1s_needed right-most '?' positions.
        // This forms the target string T with the minimal possible prefix '1' count T_i^1.

        int T_prefix_1s = 0;
        int q_count = 0; // Tracks the total number of '?'s seen so far

        // The first pat_q - Q_1s_needed '?'s should be assigned '0' (the "early" '?'s).
        // The remaining Q_1s_needed '?'s must be assigned '1' (the "late" '?'s).
        int zero_assignment_limit = pat_q - Q_1s_needed;

        for (int i = 0; i < n; ++i)
        {
            if (pattern[i] == '1')
            {
                // Fixed '1' is always counted
                T_prefix_1s++;
            }
            else if (pattern[i] == '?')
            {
                q_count++;

                // If the number of '?'s seen so far (q_count) exceeds the limit for '0'
                // assignments, this '?' is one of the "late" ones and must be a '1'
                // in our minimal T for the check.
                if (q_count > zero_assignment_limit)
                {
                    T_prefix_1s++;
                }
            }

            // Critical Prefix Check: T_i^1 <= B_i^1
            if (T_prefix_1s > prefix_B_1s[i])
            {
                return "NO"; // Minimal T violates the constraint, so all valid T fail.
            }
        }

        return "YES";
    }
};

// Helper function to run tests
void runTest(Solution &sol, const string &binary, const string &pattern, const string &expected)
{
    string result = sol.canObtain(binary, pattern);
    cout << "Binary: \"" << binary << "\", Pattern: \"" << pattern << "\" | Result: " << result
         << " | Expected: " << expected;
    if (result == expected)
    {
        cout << " (PASS)\n";
    }
    else
    {
        cout << " (FAIL)\n";
    }
}

int main()
{
    Solution sol;
    cout << "--- Subsequence Sort Test Cases ---\n";

    // Test Case 1: Simple YES
    // binary: 0101 (B_1s=2, B_prefix_1s: 0,1,1,2)
    // pattern: 0?1? (pat_1s=1, pat_q=2). Q_1s_needed = 2-1 = 1. Limit=2-1=1.
    // i=0: '0', T_1s=0. OK.
    // i=1: '?', q=1. q<=limit. T_1s=0. OK.
    // i=2: '1', T_1s=1. B_1s=1. OK.
    // i=3: '?', q=2. q>limit. T_1s=2. B_1s=2. OK. -> T = 0011 (Valid)
    runTest(sol, "0101", "0?1?", "YES");

    // Test Case 2: Fails total count (too few 1s in binary)
    // binary: 0000 (B_1s=0)
    // pattern: 1??0 (pat_1s=1). Q_1s_needed = 0-1 = -1. Fails step 3.
    runTest(sol, "0000", "1??0", "NO");

    // Test Case 3: Fails total count (too many 1s needed)
    // binary: 1100 (B_1s=2)
    // pattern: 000? (pat_1s=0, pat_q=1). Q_1s_needed = 2-0 = 2. pat_q=1. Fails step 3.
    runTest(sol, "1100", "000?", "NO");

    // Test Case 4: Fails prefix constraint
    // binary: 0011 (B_1s=2, B_prefix_1s: 0,0,1,2)
    // pattern: 1??? (pat_1s=1, pat_q=3). Q_1s_needed = 2-1 = 1. Limit=3-1=2.
    // i=0: '1', T_1s=1. B_1s[0]=0. Fails prefix check immediately.
    runTest(sol, "0011", "1???", "NO");

    // Test Case 5: Passing case with all '?'
    // binary: 1010 (B_1s=2, B_prefix_1s: 1,1,2,2)
    // pattern: ???? (pat_1s=0, pat_q=4). Q_1s_needed = 2-0 = 2. Limit=4-2=2.
    // T = 0011 (Greedy min prefix assignment)
    runTest(sol, "1010", "????", "YES");

    // Test Case 6: Edge case - must use '1's early
    // binary: 1100 (B_1s=2, B_prefix_1s: 1,2,2,2)
    // pattern: ???1 (pat_1s=1, pat_q=3). Q_1s_needed = 2-1 = 1. Limit=3-1=2.
    // T = 0011 (q_count > 2 at i=2, forces T[2]='1')
    // i=0: '?', q=1. T_1s=0. B_1s=1. OK.
    // i=1: '?', q=2. T_1s=0. B_1s=2. OK.
    // i=2: '?', q=3. q>2. T_1s=1. B_1s=2. OK.
    // i=3: '1', T_1s=2. B_1s=2. OK.
    runTest(sol, "1100", "???1", "YES");

    return 0;
}
