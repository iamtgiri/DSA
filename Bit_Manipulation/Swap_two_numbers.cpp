/*
File: Swap_two_numbers.cpp
Date: 2025-09-24 23:22

Problem: Swap two numbers
Link: https://www.geeksforgeeks.org/problems/swap-two-numbers3844/1

Problem Statement:
Given two numbers `a` and `b`, swap them without using a temporary variable.

-------------------------------------------------
❌ Brute Force
- Idea: Use a third, temporary variable to hold one of the values during the swap.
- Time complexity: O(1)
- Space complexity: O(1)
- Limitations: Requires a temporary variable, consuming a small amount of extra
  memory.

✅ Optimized Approach
- Idea: The bitwise XOR operator can be used to swap two numbers in-place due to
  its properties: `a^b^b = a`. By performing three strategic XOR operations,
  the values can be exchanged.
- Approach: Bitwise XOR swap algorithm.
- Algorithm:
    1. `a = a ^ b;`
    2. `b = a ^ b;`
    3. `a = a ^ b;`
- Time complexity: O(1)
- Space complexity: O(1)

💡 Key Pattern:
- **Bitwise XOR Swap**: A classic in-place swap trick that avoids the need for a
  temporary variable, demonstrating the power of bit manipulation.

ℹ️ Keywords:
- Bitwise XOR, In-place Swap, Bit Manipulation, Constant Space

🗒️ Notes
- This method is more of a clever trick than a performance optimization. The
  standard temporary variable swap is often more readable and, in practice,
  just as fast due to compiler optimizations.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Swaps two integers without using a temporary variable.
     * @param a The first integer.
     * @param b The second integer.
     * @return A pair containing the swapped values.
     */
    pair<int, int> get(int a, int b)
    {
        // A simple check to prevent the edge case where a and b are the same
        // memory location (though not relevant for simple integer values).
        if (a == b)
        {
            return make_pair(a, b);
        }

        a = a ^ b;
        b = a ^ b;
        a = a ^ b;

        return make_pair(a, b);
    }
};

int main()
{
    Solution sol;

    // Example test cases
    pair<int, int> result1 = sol.get(5, 10);
    cout << "Swapping 5 and 10 results in: (" << result1.first << ", "
         << result1.second << ")" << endl; // Expected: (10, 5)

    pair<int, int> result2 = sol.get(-3, 8);
    cout << "Swapping -3 and 8 results in: (" << result2.first << ", "
         << result2.second << ")" << endl; // Expected: (8, -3)

    return 0;
}