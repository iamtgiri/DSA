/*
File: Largest_Square_in_Cityscape.cpp
Date: 2025-11-05 01:08

Problem: Largest Square in Cityscape

Problem Statement:
Find the largest square that can fit under the histogram formed by
the array heights[], where each value is a skyscraper height.
Side = min(min_height_in_segment, width)
Goal: Find the maximum possible side length.
-------------------------------------------------
❌ Brute Force (Current Implementation)
- Idea: Check every possible contiguous segment (i, j). In each
        segment, calculate the minimum height and the segment width.
- Time complexity: O(N^2). Two nested loops iterate over all
                   possible start and end indices.
- Space complexity: O(1).
- Limitations: Too slow for large inputs (N > 5000).

✅ Optimized Approachs
- Idea: Convert to a variation of the Largest Rectangle in
        Histogram (LRH). For each bar `heights[i]`, find the
        widest possible segment where `heights[i]` is the minimum
        height, and then find the maximum square size based on that.
- Approach: Use a Monotonic Stack to find the nearest shorter
            bars to the left and right for every bar `i`.
- Algorithm:
    1. For each bar `i`, find its effective width `W` using the
       monotonic stack (or pre-calculated arrays).
    2. The largest square side for this bar is `side = min(W, heights[i])`.
    3. The final answer is the maximum `side` found across all bars.
- Time complexity: O(N). The monotonic stack approach is linear.
- Space complexity: O(N) for the stack and auxiliary arrays.

💡 Key Pattern:
- **Largest Rectangle in Histogram (LRH) Adaptation:** The concept
  of fixing a bar's height and extending the width until a
  shorter bar is found is central to both problems.

ℹ️ Keywords:
- Histogram, Largest Square, Monotonic Stack, Range Minimum Query.

🗒️ Notes
- The largest square is constrained by the smaller of the segment
  width and the segment's minimum height.
-------------------------------------------------
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// O(N^2) Brute Force Implementation
int largestSquareUnderHistogram(vector<int> &heights)
{
    int n = heights.size();
    int max_side = 0;

    // Outer loop: starting index i
    for (int i = 0; i < n; ++i)
    {
        int min_height = heights[i];
        // Inner loop: ending index j
        for (int j = i; j < n; ++j)
        {
            // Update min height in the segment [i, j]
            min_height = min(min_height, heights[j]);

            // Width of the segment is the number of bars
            int width = j - i + 1;

            // Side of the largest square that fits in this segment
            int side = min(width, min_height);

            // Update the overall maximum side
            max_side = max(max_side, side);
        }
    }

    return max_side;
}

int main()
{
    // Test case: {3, 1, 3, 2, 2}
    // Segments:
    // [3, 1, 3] -> min_h=1, width=3, side=min(3,1)=1
    // [3, 1, 3, 2, 2] -> min_h=1, width=5, side=min(5,1)=1
    // [3, 2, 2] -> min_h=2, width=3, side=min(3,2)=2
    vector<int> heights = {3, 1, 3, 2, 2};
    cout << "Input heights: {3, 1, 3, 2, 2}\n";
    cout << "Largest square side: "
         << largestSquareUnderHistogram(heights) << endl;

    // Another test case: {6, 2, 5, 4, 5, 1, 6} -> max_side=3
    vector<int> heights2 = {6, 2, 5, 4, 5, 1, 6};
    cout << "Input heights: {6, 2, 5, 4, 5, 1, 6}\n";
    cout << "Largest square side: "
         << largestSquareUnderHistogram(heights2) << endl; // Should be 3

    return 0;
}
