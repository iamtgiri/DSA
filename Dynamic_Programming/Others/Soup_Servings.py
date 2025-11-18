"""
File: Soup_Servings.py
Date: 2025-11-18 23:56

Problem: Soup Servings
Link: https://leetcode.com/problems/soup-servings/description/

Problem Statement:
There are two bowls of soup, A and B, each initially containing N milliliters of soup.
We perform a series of servings, each with a 25% probability for one of four outcomes:
1. Serve 100 ml of A and 0 ml of B (i.e., A - 4, B - 0)
2. Serve 75 ml of A and 25 ml of B (i.e., A - 3, B - 1)
3. Serve 50 ml of A and 50 ml of B (i.e., A - 2, B - 2)
4. Serve 25 ml of A and 75 ml of B (i.e., A - 1, B - 3)

The serving stops when a bowl is empty. Find the probability that soup A runs out first,
plus half the probability that both soups run out simultaneously.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Recursive simulation without memoization. Explore all possible serving paths 
  until a termination condition (A runs out, B runs out, or both run out) is met.
- Time complexity: O(4^(N/25)). Exponential time complexity due to redundant subproblems.
- Space complexity: O(N/25) for recursion depth.
- Limitations: Infeasible for large N due to Time Limit Exceeded (TLE).

Current/Optimized Approach
- Idea: This is a **Dynamic Programming** problem on probability. The state is defined by the remaining amounts of 
  soup (A, B). Since the transitions are fixed and many states are revisited, Memoization is used.
- Approach: **Memoization (Top-Down Dynamic Programming)** using Python's `lru_cache`.
- Algorithm: 
  1. **Scaling:** Convert N ml to units of 25 ml: M = ceil(N/25).
  2. **Optimization (Cutoff):** If N >= 4800, return 1.0 (probability converges).
  3. **State:** P(a, b) is the required probability when 'a' and 'b' units of soup remain.
  4. **Base Cases:**
     - a <= 0 and b <= 0: Both run out. P(a, b) = 0.5.
     - a <= 0 and b > 0: A runs out first. P(a, b) = 1.0.
     - a > 0 and b <= 0: B runs out first. P(a, b) = 0.0.
  5. **Recurrence:**
     P(a, b) = 0.25 * [P(a-4, b) + P(a-3, b-1) + P(a-2, b-2) + P(a-1, b-3)]
- Time complexity: O(M^2), where M = ceil(N/25). Due to the cutoff, this is effectively O(1) constant time complexity.
- Space complexity: O(M^2) for the memoization cache.

💡 Key Pattern:
- **Dynamic Programming on Probability:** Calculating the probability of reaching a target state by summing probabilities
  of previous states weighted by transition likelihoods.

ℹ️ Keywords:
- Dynamic Programming, Probability, Memoization, Recurrence Relation, State Transition.

🗒️ Notes
- The cutoff value (4800) is necessary for passing the time limit.
- Scaling to 25ml units is essential for a manageable DP grid size.
-------------------------------------------------
"""

from typing import List, Optional, Any
from functools import lru_cache

class Solution:
    def soupServings(self, n: int) -> float:
        # Cutoff Optimization: For large N (N >= 4800), the probability 
        # converges to 1.0 because soup A is consumed more aggressively.
        if n >= 4800:
            return 1.0

        # Scale N (ml) to M (25ml units), rounding up.
        # Example: 50ml -> 2 units. 51ml -> 3 units.
        m = (n + 24) // 25 

        # Use lru_cache for memoization (Top-Down DP)
        @lru_cache(None)
        def dp(a: int, b: int) -> float:
            # Base Case 1: Both soups run out simultaneously (Prob = 0.5)
            if a <= 0 and b <= 0:
                return 0.5
            # Base Case 2: Soup A runs out first (Prob = 1.0)
            if a <= 0:
                return 1.0
            # Base Case 3: Soup B runs out first (Prob = 0.0)
            if b <= 0:
                return 0.0

            # Recurrence Relation: Sum of probabilities for the four serving options
            # 
            return 0.25 * (
                dp(a - 4, b) +      # A-100, B-0
                dp(a - 3, b - 1) +  # A-75, B-25
                dp(a - 2, b - 2) +  # A-50, B-50
                dp(a - 1, b - 3)    # A-25, B-75
            )

        # Start the recursive calculation from the initial state (m, m)
        return dp(m, m)


if __name__ == "__main__":
    sol = Solution()
    # Example test cases
    n1 = 50
    print(f"N={n1}, Probability: {sol.soupServings(n1)}") # Expected: 0.625

    n2 = 100
    print(f"N={n2}, Probability: {sol.soupServings(n2)}") # Expected: 0.71875

    n3 = 5000 
    print(f"N={n3}, Probability: {sol.soupServings(n3)}") # Expected: 1.0 (due to cutoff)