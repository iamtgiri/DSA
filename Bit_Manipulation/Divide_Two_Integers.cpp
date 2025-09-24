/*
File: Divide_Two_Integers.cpp
Date: 2025-09-24 23:09

Problem: Divide Two Integers
Link: https://leetcode.com/problems/divide-two-integers/description/

Problem Statement:
Given two integers `dividend` and `divisor`, divide them without using
multiplication, division, and modulo operators.

-------------------------------------------------
❌ Brute Force
- Idea: Repeatedly subtract `abs(divisor)` from `abs(dividend)` and count the
  number of subtractions.
- Time complexity: $O(dividend/divisor)$.
- Space complexity: $O(1)$.
- Limitations: Very slow for large inputs, leading to a Time Limit Exceeded.

✅ Optimized Approach
- Idea: Use bit shifting to perform binary long division. Instead of subtracting
  one by one, we can efficiently subtract multiples of the divisor that are
  powers of 2.
- Approach: A greedy algorithm using bitwise operations.
- Algorithm:
    1. Handle edge cases: `divisor == 0` and `dividend == INT_MIN` with
       `divisor == -1`.
    2. Determine the sign of the result. Use `long long` to handle absolute
       values, especially for `INT_MIN`.
    3. Iterate from bit 31 down to 0.
    4. In each step, if the absolute `dividend` is greater than or equal to the
       `abs(divisor)` shifted left by `i` bits, subtract that value and add
       `2^i` to the result.
    5. Apply the final sign to the result and return it as an integer.
- Time complexity: $O(\log N)$, where N is the dividend.
- Space complexity: $O(1)$.

💡 Key Pattern:
- **Binary Long Division**: The approach mirrors how one would perform long
  division in base 2, leveraging bit shifts for fast multiplication by powers
  of 2.

ℹ️ Keywords:
- Bitwise, Binary Long Division, Bit Shifting, Integer Overflow

🗒️ Notes
- Using `long long` is crucial to handle the case of `INT_MIN`, since its
  absolute value is larger than `INT_MAX`.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Divides two integers without using multiplication, division,
     * or modulo operators.
     * @param dividend The number to be divided.
     * @param divisor The number to divide by.
     * @return The quotient of the division.
     */
    int divide(int dividend, int divisor)
    {
        // Handle edge case for overflow: INT_MIN / -1
        if (dividend == INT_MIN && divisor == -1)
            return INT_MAX;

        // Handle division by zero
        if (divisor == 0)
            return INT_MAX; // Or throw an exception, depending on requirements

        // Determine the sign of the result
        bool is_negative = (divisor < 0) ^ (dividend < 0);

        // Use long long to handle the edge case of INT_MIN
        long long a = abs((long long)dividend);
        long long b = abs((long long)divisor);
        long long result = 0;

        // Perform binary long division
        for (int i = 31; i >= 0; --i)
        {
            if (a >= (b << i))
            {
                a -= b << i;
                result += 1LL << i;
            }
        }

        // Apply the correct sign
        if (is_negative)
            result = -result;

        return static_cast<int>(result);
    }
};

int main()
{
    Solution sol;

    // Example test cases
    cout << "10 / 3 = " << sol.divide(10, 3) << endl; // Expected: 3
    cout << "-7 / 2 = " << sol.divide(-7, 2) << endl; // Expected: -3
    cout << "2147483647 / 1 = " << sol.divide(INT_MAX, 1) << endl;
    cout << "-2147483648 / -1 = " << sol.divide(INT_MIN, -1) << endl; // Expected: 2147483647

    return 0;
}