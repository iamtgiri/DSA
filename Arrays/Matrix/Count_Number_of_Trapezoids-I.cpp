/*
File: Count_Number_of_Trapezoids-I.cpp
Date: 2025-10-25 23:20

Problem: Count Number of Trapezoids I
Link: https://leetcode.com/problems/count-number-of-trapezoids-i/description/

Problem Statement:
Given a list of points in a 2D plane, count the number of trapezoids that can be
formed using these points, where the two parallel sides must be horizontal.
The result should be modulo 10^9 + 7.

-------------------------------------------------
❌ Brute Force
- Idea: Iterate over all combinations of 4 points ($P_a, P_b, P_c, P_d$). Check
  if these four points can form a trapezoid with horizontal parallel sides. This
  means checking if two pairs of points share the same y-coordinate, and the
  remaining pair of points share a *different* y-coordinate.
- Time complexity: O(N^4), where N is the number of points.
- Space complexity: O(1).
- Limitations: Extremely slow for large N.

✅ Optimized Approachs
- Idea: A trapezoid with horizontal parallel sides is defined by selecting two
  distinct horizontal line segments (bases) from two different y-coordinates.
- Approach: Grouping and Combinatorics (Dynamic Sweeping).
- Algorithm:
    1. **Group Points:** Count the number of points at each unique y-coordinate.
       Store these counts in a sorted map (`std::map`) to ensure iteration is
       in ascending order of y-coordinate.
    2. **Calculate Segments:** For a level with $C$ points, the number of distinct
       horizontal line segments (bases) is $\binom{C}{2} = C(C-1)/2$.
    3. **Sweep and Combine:** Iterate through the y-levels in ascending order.
        a. Maintain a `cumulativePairs` count, which is the total number of
           segments from all *lower* levels (potential bottom bases).
        b. For the current level $y$, calculate its segments (`pairsAtLevel`).
        c. Each segment at level $y$ can combine with any of the `cumulativePairs`
           segments to form a trapezoid. Add $cumulativePairs \times pairsAtLevel$
           to the total `trapezoidCount`.
        d. Update `cumulativePairs` by adding `pairsAtLevel`.
    4. All calculations are performed modulo $10^9 + 7$.
- Time complexity: O(N + U log U). O(N) to count points, and $O(U \log U)$
  for map insertion and iteration, where U is the number of unique y-coordinates.
- Space complexity: O(U) to store the y-level counts.

💡 Key Pattern:
- **Geometric Counting with Combinations:** Reducing a complex geometric counting
  problem to a combinations problem ($\binom{N}{2}$) and a dynamic programming
  style sweep.

ℹ️ Keywords:
- Combinatorics, Geometry, Horizontal Lines, Sorted Map, Combinations.

🗒️ Notes
- Using `std::map` instead of `std::unordered_map` is crucial to ensure the
  y-coordinates are processed in ascending order, guaranteeing that the
  `cumulativePairs` only includes lower levels.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Counts the number of trapezoids with horizontal parallel sides formed
     * by the given points.
     * @param points The vector of 2D points (x, y).
     * @return The count of trapezoids modulo 10^9 + 7.
     */
    int countTrapezoids(vector<vector<int>> &points)
    {
        const int MOD = 1000000007;

        // Use std::map to ensure iteration over y-coordinates is in ascending order.
        // Key: y-coordinate, Value: count of points at that y-level.
        map<int, long long> yLevelCount;

        // Step 1: Count points at each y-level
        for (auto &point : points)
            yLevelCount[point[1]]++;

        long long trapezoidCount = 0;
        // Cumulative count of all segments (pairs of points) from lower y-levels
        // processed so far. These are potential bottom bases.
        long long cumulativePairs = 0;

        // Step 2 & 3: Sweep through y-levels in ascending order (guaranteed by std::map)
        for (auto &[yCoord, count] : yLevelCount)
        {
            if (count < 2)
            {
                // Cannot form a segment with less than 2 points
                continue;
            }

            // Calculate C(count, 2): number of distinct segments (pairs) at this level.
            // These segments act as the NEW top base.
            long long pairsAtLevel = count * (count - 1) / 2;

            // Combine: Each new top base can pair with every segment from a lower level.
            trapezoidCount =
                (trapezoidCount + cumulativePairs * pairsAtLevel) % MOD;

            // Update: Add the current level's segments to the cumulative count for
            // future (higher) levels.
            cumulativePairs = (cumulativePairs + pairsAtLevel) % MOD;
        }

        return static_cast<int>(trapezoidCount);
    }
};

// Helper function to print a vector of vectors (for cleaner test output)
void printPoints(const vector<vector<int>> &points)
{
    cout << "{";
    for (size_t i = 0; i < points.size(); ++i)
    {
        cout << "{" << points[i][0] << ", " << points[i][1] << "}";
        if (i < points.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << "}";
}

int main()
{
    Solution sol;

    cout << "--- Count Number of Trapezoids I ---\n";

    // Test Case 1: Example where 2 levels have 3 points each.
    // y=1: 3 points -> 3 pairs. y=5: 3 points -> 3 pairs. Total = 3 * 3 = 9.
    vector<vector<int>> points1 = {{1, 1}, {2, 1}, {3, 1}, {1, 5}, {2, 5}, {3, 5}};
    int result1 = sol.countTrapezoids(points1);
    cout << "Test 1 | Points: ";
    printPoints(points1);
    cout << "\nResult: " << result1 << " (Expected: 9)\n";
    cout << "--------------------------------\n";

    // Test Case 2: Three levels with different counts.
    // y=1: 4 points -> 6 pairs. y=3: 2 points -> 1 pair. y=5: 3 points -> 3 pairs.
    // Level 3 pairs with Level 1: 1 * 6 = 6
    // Level 5 pairs with (Level 1 + Level 3): 3 * (6 + 1) = 21
    // Total = 6 + 21 = 27.
    vector<vector<int>> points2 = {
        {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 3}, {6, 3}, {7, 5}, {8, 5}, {9, 5}};
    int result2 = sol.countTrapezoids(points2);
    cout << "Test 2 | Points: ";
    printPoints(points2);
    cout << "\nResult: " << result2 << " (Expected: 27)\n";
    cout << "--------------------------------\n";

    // Test Case 3: Edge case (no trapezoids possible)
    vector<vector<int>> points3 = {{1, 1}, {2, 1}, {3, 2}};
    int result3 = sol.countTrapezoids(points3);
    cout << "Test 3 | Points: ";
    printPoints(points3);
    cout << "\nResult: " << result3 << " (Expected: 0)\n";
    cout << "--------------------------------\n";

    // Test Case 4: Only one y-level with enough points (no trapezoids)
    vector<vector<int>> points4 = {{1, 10}, {2, 10}, {3, 10}, {4, 10}};
    int result4 = sol.countTrapezoids(points4);
    cout << "Test 4 | Points: ";
    printPoints(points4);
    cout << "\nResult: " << result4 << " (Expected: 0)\n";
    cout << "--------------------------------\n";

    return 0;
}
