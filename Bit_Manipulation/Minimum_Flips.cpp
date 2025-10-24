/*
File: Minimum_Flips.cpp
Date: 2025-10-24 22:40

Problem: Minimum Flips to Make a OR b Equal to c
Link: https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/description/

Problem Statement:
Given three positive integers a, b, and c. In one operation, you can flip any bit
in a or b (i.e., change 0 to 1 or 1 to 0). Return the minimum number of flips
required so that (a OR b) == c.

-------------------------------------------------
❌ Brute Force
- Idea: Iterating through all possible combinations of flips (which is up to 64 flips total for 32-bit integers) is computationally infeasible. The core logic must focus on the bit level.
- Time complexity: N/A (Exponential if attempted)
- Space complexity: N/A
- Limitations: The problem structure forces a bitwise-greedy solution.

✅ Optimized Approachs
- Idea: Since bitwise OR operations are independent for each bit position, the problem can be solved by processing the numbers bit-by-bit from LSB to MSB and greedily finding the minimum flips required at each position.
- Approach: Bitwise Iteration (Greedy).
- Algorithm:
    1. Initialize `flips = 0`.
    2. Loop while at least one of `a`, `b`, or `c` is greater than 0.
    3. Extract the Least Significant Bit (LSB) for $a, b,$ and $c$ using the bitwise AND operator (`& 1`).
    4. **Determine flips based on the target $c_{bit}$:**
        * If **$c_{bit}$ is 1**: The current result $(a_{bit} | b_{bit})$ must be 1. If it's 0 (meaning $a_{bit}=0$ and $b_{bit}=0$), we need exactly one flip on $a$ or $b$. $\implies$ `flips += 1`.
        * If **$c_{bit}$ is 0**: The current result $(a_{bit} | b_{bit})$ must be 0. We need to flip every 1 to a 0. If $a_{bit}=1$ and $b_{bit}=1$, we need two flips. If only one is 1, we need one flip. $\implies$ `flips += a_{bit} + b_{bit}$.
    5. Right-shift all three numbers (`>>= 1`) to process the next bit.
- Time complexity: $O(\log(\max(a, b, c)))$, which is $O(1)$ given the 32-bit integer constraint.
- Space complexity: $O(1)$.

💡 Key Pattern:
- **Bitwise Independence:** Bitwise operations allow for highly efficient, greedy solutions by treating each bit position as a separate, local subproblem.

ℹ️ Keywords:
- Bitwise Operations, Greedy Algorithm, LSB, Bit Manipulation.

🗒️ Notes
- The core logic is the case when $c_{bit}=0$. If both $a_{bit}$ and $b_{bit}$ are 1, you must flip both, costing 2 flips. If $c_{bit}=1$ and both $a_{bit}$ and $b_{bit}$ are 0, you only need to flip one, costing 1 flip.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Calculates the minimum flips required so that (a OR b) == c.
     * @param a The first integer.
     * @param b The second integer.
     * @param c The target integer.
     * @return The minimum number of bit flips.
     */
    int minFlips(int a, int b, int c)
    {
        int flips = 0;
        // Continue iterating as long as there are bits remaining in a, b, or c.
        while (a > 0 || b > 0 || c > 0)
        {
            // Extract the Least Significant Bit (LSB)
            int abit = a & 1;
            int bbit = b & 1;
            int cbit = c & 1;

            // Check if a flip is needed
            if ((abit | bbit) != cbit)
            {
                if (cbit == 1)
                {
                    // Target is 1, but current result is 0 (a=0, b=0).
                    // We only need to flip one of them (a or b) to 1. Cost: 1 flip.
                    flips += 1;
                }
                else
                { // cbit == 0
                    // Target is 0, but current result is 1 (a=1 OR b=1 OR both=1).
                    // We must flip every '1' to '0'. Cost: abit + bbit (1 or 2 flips).
                    flips += abit + bbit;
                }
            }

            // Move to the next bit position
            a >>= 1;
            b >>= 1;
            c >>= 1;
        }
        return flips;
    }
};

int main()
{
    Solution sol;

    cout << "--- Minimum Flips to Make (a | b) == c ---\n";

    // Test Case 1: Standard case with all conditions
    int a1 = 2, b1 = 6, c1 = 5;
    // a=010, b=110, c=101. Expected: 3
    // LSB: (0|0)=0 vs 1 (Flip 1). Next: (1|1)=1 vs 0 (Flip 2). Next: (0|1)=1 vs 1 (Flip 0). Total: 1+2=3.
    cout << "Test 1: a=" << a1 << ", b=" << b1 << ", c=" << c1 << " -> Flips: " << sol.minFlips(a1, b1, c1) << " (Expected: 3)" << endl;

    // Test Case 2: Only one flip needed (target 1 needs a 0->1 flip)
    int a2 = 4, b2 = 2, c2 = 7;
    // a=100, b=010, c=111. Expected: 1
    // LSB: (0|0)=0 vs 1 (Flip 1). Other bits match. Total: 1.
    cout << "Test 2: a=" << a2 << ", b=" << b2 << ", c=" << c2 << " -> Flips: " << sol.minFlips(a2, b2, c2) << " (Expected: 1)" << endl;

    // Test Case 3: Case where two flips are needed at one position
    int a3 = 1, b3 = 2, c3 = 0;
    // a=001, b=010, c=000. Expected: 2
    // LSB: (1|0)=1 vs 0 (Flip 1). Next: (0|1)=1 vs 0 (Flip 1). Total: 2.
    cout << "Test 3: a=" << a3 << ", b=" << b3 << ", c=" << c3 << " -> Flips: " << sol.minFlips(a3, b3, c3) << " (Expected: 2)" << endl;

    // Test Case 4: Zero flips needed
    int a4 = 5, b4 = 2, c4 = 7;
    // a=101, b=010, c=111. Expected: 0
    cout << "Test 4: a=" << a4 << ", b=" << b4 << ", c=" << c4 << " -> Flips: " << sol.minFlips(a4, b4, c4) << " (Expected: 0)" << endl;

    return 0;
}
