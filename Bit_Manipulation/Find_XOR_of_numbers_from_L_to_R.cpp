/*
File: Find_XOR_of_numbers_from_L_to_R.cpp
Date: 2025-09-24 23:17

Problem: Find XOR of numbers from L to R
Link: https://www.geeksforgeeks.org/problems/find-xor-of-numbers-from-l-to-r/1

Problem Statement:
Given two integers L and R, find the XOR sum of all numbers in the range [L, R]
(inclusive).

-------------------------------------------------
❌ Brute Force
- Idea: Iterate from L to R, and XOR each number with a running total.
- Time complexity: O(R - L + 1)
- Space complexity: O(1)
- Limitations: Inefficient for large ranges, will likely time out.

✅ Optimized Approach
- Idea: The XOR sum of numbers from 1 to N follows a pattern based on N % 4.
  We can leverage this pattern and the property `(L..R) = (1..R) ^ (1..L-1)`
  to solve the problem in constant time.
- Approach: Use a helper function to find XOR sum from 1 to N in O(1).
- Algorithm:
    1. Create a helper `xorUpto(n)` that returns the XOR sum from 1 to n.
    2. `xorUpto(n)` checks `n % 4` and returns `n`, `1`, `n+1`, or `0`
       accordingly.
    3. The final result is `xorUpto(R) ^ xorUpto(L - 1)`.
- Time complexity: O(1)
- Space complexity: O(1)

💡 Key Pattern:
- **XOR's Cyclical Property**: The XOR sum of consecutive integers has a
  predictable pattern of length 4, which enables O(1) solutions for range sums.

ℹ️ Keywords:
- Bitwise XOR, XOR Sum, Range Query, Mathematical Pattern, O(1)

🗒️ Notes
- This is a classic example of using mathematical properties of an operator
  to optimize a brute-force approach that would otherwise be linear.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Helper function to find XOR sum of numbers from 1 to n.
     * @param n The upper limit.
     * @return The XOR sum.
     */
    int xorUpto(int n)
    {
        switch (n % 4)
        {
        case 0:
            return n;
        case 1:
            return 1;
        case 2:
            return n + 1;
        case 3:
            return 0;
        }
        return 0; // Should not be reached
    }

    /**
     * @brief Finds the XOR sum of numbers in a given range [l, r].
     * @param l The lower bound of the range.
     * @param r The upper bound of the range.
     * @return The XOR sum of all numbers in the range.
     */
    int findXOR(int l, int r)
    {
        return xorUpto(r) ^ xorUpto(l - 1);
    }
};

int main()
{
    Solution sol;

    // Example 1
    int l1 = 2, r1 = 4;
    cout << "XOR sum from 2 to 4 is: " << sol.findXOR(l1, r1) << endl;
    // Expected: 2^3^4 = 1

    // Example 2
    int l2 = 1, r2 = 10;
    cout << "XOR sum from 1 to 10 is: " << sol.findXOR(l2, r2) << endl;
    // Expected: 1^2^...^10 = 8

    return 0;
}