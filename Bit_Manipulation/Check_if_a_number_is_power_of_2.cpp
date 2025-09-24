/*
File: Check_if_a_number_is_power_of_2.cpp
Date: 2025-09-24 23:07

Problem: Check if a number is power of 2
Link: https://leetcode.com/problems/power-of-two/description/

Problem Statement:
Given an integer n, return true if it is a power of two. Otherwise, return false.

-------------------------------------------------
❌ Brute Force
- Idea: Repeatedly divide `n` by 2. If at any point the remainder is not 0
  (except for the final division), `n` is not a power of 2. The loop ends
  when `n` becomes 1.
- Time complexity: $O(\log_2 n)$.
- Space complexity: $O(1)$.
- Limitations: Involves a loop and division, which is less performant than
  a bitwise approach.

✅ Optimized Approach
- Idea: A positive number `n` is a power of two if and only if it has a single
  '1' bit in its binary representation. The expression `n & (n - 1)` clears
  the rightmost set bit. For a number with only one set bit, this operation
  will result in 0.
- Approach: Use a single bitwise AND operation.
- Algorithm:
    1. Check if `n` is greater than 0.
    2. Perform the bitwise operation `n & (n - 1)`.
    3. Return `true` if the result is 0 and `n` is positive; otherwise,
       return `false`.
- Time complexity: $O(1)$.
- Space complexity: $O(1)$.

💡 Key Pattern:
- **Bitwise Trick for Powers of Two**: The expression `n & (n - 1)` is a
  powerful way to check for powers of two. It efficiently isolates the
  rightmost set bit.

ℹ️ Keywords:
- Bitwise Operations, Powers of Two, Binary, Bit Manipulation

🗒️ Notes
- The condition `n > 0` is crucial. The expression `n & (n - 1)` is also
  equal to 0 for `n=0`, but 0 is not considered a power of two.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Checks if a number is a power of two using bitwise manipulation.
     * @param n The integer to check.
     * @return True if n is a power of two, false otherwise.
     */
    bool isPowerOfTwo(int n)
    {
        return n > 0 && ((n & (n - 1)) == 0);
    }
};

int main()
{
    Solution sol;

    // Example test cases
    cout << "8 is a power of two? " << boolalpha << sol.isPowerOfTwo(8) << endl;
    // Expected: true
    cout << "16 is a power of two? " << boolalpha << sol.isPowerOfTwo(16) << endl;
    // Expected: true
    cout << "3 is a power of two? " << boolalpha << sol.isPowerOfTwo(3) << endl;
    // Expected: false
    cout << "0 is a power of two? " << boolalpha << sol.isPowerOfTwo(0) << endl;
    // Expected: false

    return 0;
}