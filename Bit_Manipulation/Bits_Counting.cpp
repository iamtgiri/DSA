/*
File: Bits_Counting.cpp
Date: 2025-11-25 10:07

Problem: Bits Counting

Link: https://www.geeksforgeeks.org/problems/bits-counting/1

Problem Statement:
Given a non-negative integer 'n', return an array of size n + 1 where each element at index i (0 <= i <= n) is the number of '1's in the binary representation of i.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: For each number i from 0 to n, iterate through its 32 bits and count the set bits using a loop and bitwise operations (e.g., `i & 1`, then `i >>= 1`).
- Time complexity: O(N * log N) (N iterations, and up to log N operations per number).
- Space complexity: O(N) (to store the result).
- Limitations: Inefficient due to repeated bit calculations for numbers.

Current/Optimized Approachs
- Idea: Dynamic Programming based on the most significant bit (MSB) or the parity of the number. The count for any number 'i' can be derived from the count of a smaller number.
- Approach: **DP via Bit Shift (Parity Method)**
- Algorithm:
  1. Initialize a result vector `ans` of size $n+1$, with $ans[0]=0$.
  2. For $i > 0$:
     * The number of set bits in $i$ is equal to the number of set bits in $i/2$ (or $i \gg 1$) plus one if $i$ is odd (the least significant bit is 1), or zero if $i$ is even (the least significant bit is 0).
     * The relation is: $ans[i] = ans[i / 2] + (i \text{ mod } 2)$.
     * Using bitwise operations: `ans[i] = ans[i >> 1] + (i & 1);`
  3. This relationship allows constant-time $O(1)$ calculation for each $i$.
- Time complexity: **O(N)** (Linear time, since each number is processed in constant time).
- Space complexity: O(N) (to store the result vector).

💡 Key Pattern:
- **Dynamic Programming on Bit Manipulation:** Using a known, smaller subproblem result (the count of $i/2$) to compute the current problem (the count of $i$).

ℹ️ Keywords:
- Dynamic Programming, Bit Counting, Population Count, Brian Kernighan's Algorithm (alternative, not used here), Bitwise Operators, Parity.

🗒️ Notes
- This $O(N)$ approach is optimal because we must at least read and output $N$ numbers.
- The same problem can also be solved using the relation $ans[i] = ans[i \& (i-1)] + 1$.
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution
{
public:
    /**
     * @brief Counts the number of set bits for every number from 0 to n using Dynamic Programming.
     * @param n The upper limit of the range (0 to n).
     * @return A vector where ans[i] is the count of set bits in i.
     */
    vector<int> countBits(int n)
    {
        // Initialize vector to store the results. ans[0] is automatically 0.
        vector<int> ans(n + 1);

        // Base case: ans[0] = 0 (already handled by vector initialization)

        for (int i = 1; i <= n; i++)
        {
            // DP Relation: ans[i] = ans[i / 2] + (i % 2)

            // i >> 1 is equivalent to i / 2 (right shift discards LSB)
            int count_of_prev = ans[i >> 1];

            // i & 1 is 1 if i is odd (LSB is 1), and 0 if i is even (LSB is 0)
            int lsb = (i & 1);

            // The count for i is the count of i/2 plus the value of its LSB.
            ans[i] = count_of_prev + lsb;
        }
        return ans;
    }
};

int main()
{
    Solution sol;

    // Test Case 1: n = 5
    int n1 = 5;
    vector<int> res1 = sol.countBits(n1);
    cout << "n = " << n1 << endl;
    cout << "Results (0 to 5): [";
    for (size_t i = 0; i < res1.size(); ++i)
    {
        cout << res1[i] << (i == res1.size() - 1 ? "" : ", ");
    }
    cout << "] (Expected: [0, 1, 1, 2, 1, 2])" << endl;

    // Test Case 2: n = 8
    int n2 = 8;
    vector<int> res2 = sol.countBits(n2);
    cout << "n = " << n2 << endl;
    cout << "Results (0 to 8): [";
    for (size_t i = 0; i < res2.size(); ++i)
    {
        cout << res2[i] << (i == res2.size() - 1 ? "" : ", ");
    }
    cout << "] (Expected: [0, 1, 1, 2, 1, 2, 2, 3, 1])" << endl;

    return 0;
}