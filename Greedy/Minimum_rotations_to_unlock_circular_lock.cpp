/*
File: Minimum_rotations_to_unlock_circular_lock.cpp
Date: 2025-09-22 16:42

Problem: Minimum rotations to unlock a circular lock
Link: https://www.geeksforgeeks.org/problems/minimum-rotations-to-unlock-a-circular-lock1001/1
Problem Statement:
Given a lock made up of N different circular rings. Each ring has 0-9 digits printed
on it. There is only one particular code which can open the lock. You can rotate each
ring any number of times in either direction. Given the random sequence R and the
desired sequence D, find the minimum number of rotations required to open the lock.

Example 1:
Input: R = 222, D = 333
Output: 3
Explaination: Optimal number of rotations for getting 3 from 2 is 1. There are three
2 to 3 transformations. So answer is 1+1+1 = 3.

Example 2:
Input: R = 2345, D = 5432
Output: 8
Explaination: The optimal shifts for pairs are: (2, 5) = 3, (3, 4) = 1, (4,3) = 1,
(5,2) = 3. So total shifts = 3+1+1+3 = 8.
-------------------------------------------------
❌ Brute Force
- Idea: A brute-force approach is not applicable here as there's no set of
combinations to check. The problem involves a direct calculation based on the digits.
- Time complexity: Not applicable.
- Space complexity: Not applicable.
- Limitations: Infeasible.

✅ Optimized Approach
- Idea: This problem is a **greedy algorithm**. The key insight is that the
rotations of each circular ring are independent of the other rings. Therefore, to
minimize the total number of rotations, we must minimize the rotations for each
individual ring.
- Approach: A greedy, digit-by-digit approach.
- Algorithm:
  1. Initialize a `total_rotations` variable to 0.
  2. Iterate through the digits of the `R` and `D` numbers, from right to left (the
  units place, then tens, and so on). A `while` loop with modulo and division is
  a convenient way to do this.
  3. For each pair of digits (`r` from `R` and `d` from `D`), calculate the absolute
  difference `abs(r - d)`.
  4. Since the rings are circular (0 to 9), the minimum number of rotations is the
  shorter distance: either the direct difference or the difference via the other
  side of the circle. This is given by `min(diff, 10 - diff)`.
  5. Add this minimum rotation count to `total_rotations`.
  6. Repeat until all digit pairs have been processed.
  7. Return `total_rotations`.
- Time complexity: O(log10(max(R, D))) which is equivalent to O(N) where N is the
number of digits.
- Space complexity: O(1) as we only use a few integer variables.

💡 Key Pattern:
- **Greedy for Independent Subproblems**: When a larger problem can be broken down
into smaller, independent subproblems whose solutions can be summed or combined, a
greedy approach is often optimal. This is a common pattern in computational geometry
and optimization problems.

ℹ️ Keywords:
- Greedy Algorithm, Circular Array, Digit Manipulation, Optimization, Modular Arithmetic

🗒️ Notes
- The problem is a good example of how to solve a problem on a circular structure. The
minimum distance between two points on a circle with circumference `C` is `min(diff, C - diff)`.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Calculates the minimum number of rotations to unlock a circular lock.
     * @param R The random sequence of digits.
     * @param D The desired sequence of digits.
     * @return The minimum total number of rotations.
     */
    int rotationCount(long long R, long long D)
    {
        long long total_rotations = 0;

        // Iterate through the digits from right to left using modulo arithmetic.
        while (R > 0 || D > 0)
        {
            int r_digit = R % 10;
            int d_digit = D % 10;

            // Calculate the absolute difference between the digits.
            long long diff = abs(r_digit - d_digit);

            // The minimum rotations on a circular ring is the shorter path.
            total_rotations += min(diff, 10 - diff);

            // Move to the next digit (tens place, hundreds, etc.).
            R /= 10;
            D /= 10;
        }

        return total_rotations;
    }
};

int main()
{
    Solution sol;

    // Example 1
    long long R1 = 222, D1 = 333;
    cout << "Example 1: Min rotations = " << sol.rotationCount(R1, D1) << endl;
    // Expected: 3

    // Example 2
    long long R2 = 2345, D2 = 5432;
    cout << "Example 2: Min rotations = " << sol.rotationCount(R2, D2) << endl;
    // Expected: 8

    return 0;
}