/*
File: Largest_Rectangle_in_Histogram.cpp
Date: 2025-11-06 12:05

Problem: Largest Rectangle in Histogram
Link: https://leetcode.com/problems/largest-rectangle-in-histogram/description/

Problem Statement:
Given an array of integers `heights` representing the histogram's bar heights,
find the area of the largest rectangle in the histogram. Each bar has a width of 1.

-------------------------------------------------
❌ Brute Force
- Idea: Iterate through every bar `i` and calculate the largest rectangle area where
  `heights[i]` is the height of that rectangle. To do this, for each bar `i`,
  expand outwards (left and right) until a bar shorter than `heights[i]` is found
  to determine the width.
- Time complexity: O(N^2). We iterate through N bars, and for each bar, we perform
  an O(N) scan left and right to find the boundaries.
- Space complexity: O(1).
- Limitations: Too slow for large inputs (N up to 10^5).

✅ Optimized Approachs
- Idea: For any bar `i`, the largest rectangle area using its height `h = heights[i]`
  is defined by finding the **Nearest Smaller Element (NSE)** to its left (NSL) and
  the **Nearest Smaller Element** to its right (NSR). The width is `NSR - NSL - 1`.
  The Monotonic Stack is the most efficient way to find all NSLs and NSRs in a single pass.
- Approach: **Monotonic Increasing Stack (Single Pass)**.
- Algorithm:
  1. Initialize an empty stack `st` to store the **indices** of the bars in strictly
     **increasing** height order.
  2. Iterate from `i = 0` to `n` (including a dummy index `n`). The current height
     is `heights[i]` or `0` if `i == n`.
  3. **While loop (Monotonicity Check):** While the stack is *not* empty and the
     current height `curr_height` is less than the height of the bar at the index
     on the top of the stack (`heights[st.top()]`):
     a. **Pop & Calculate:** Pop the top index `h_idx`. This bar's height `h` is
        now the height of the potential largest rectangle.
     b. The current index `i` is the **NSR** for the popped bar.
     c. The new `st.top()` (the element *below* the popped one) is the **NSL** for the popped bar.
     d. **Calculate Width:** `width = i - st.top() - 1`. If the stack is empty after
        the pop, it means no smaller bar exists to the left, so the width is `i`.
     e. Update `max_area = max(max_area, h * width)`.
  4. **Push:** Push the current index `i` onto the stack (this maintains the
     increasing property for the next iteration).
  5. The dummy index `i == n` with height 0 ensures all remaining indices in the
     stack are processed and finalized.
- Time complexity: **O(N)**. Each index is pushed onto the stack once and popped
  from the stack at most once.
- Space complexity: **O(N)** for the stack.

💡 Key Pattern:
- **Monotonic Stack for Next Smaller/Greater Element:** Used to solve problems where
  you need to find the nearest element to the left or right that satisfies a
  particular ordering condition (e.g., smaller, greater).

ℹ️ Keywords:
- Stack, Monotonic Stack, Nearest Smaller Element (NSE), Histogram, Area Calculation.

🗒️ Notes
- The addition of a dummy bar of height 0 at the end of the iteration (`i == n`)
  is a critical optimization that removes the need for separate pre-calculation of
  NSL and NSR arrays, simplifying the code greatly.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Finds the area of the largest rectangle in a histogram using a Monotonic Stack.
     * @param heights A vector of integers representing bar heights.
     * @return The maximum area of the rectangle.
     */
    int largestRectangleArea(vector<int> &heights)
    {
        int n = heights.size();
        stack<int> st; // Stores indices of bars in increasing order of height
        int max_area = 0;

        // Iterate up to n (including the dummy index)
        for (int i = 0; i <= n; ++i)
        {
            // Define the current height (0 for the dummy bar at i == n)
            int curr_height = (i == n) ? 0 : heights[i];

            // Monotonic Stack logic: If the current bar is shorter than the stack top,
            // we have found the Next Smaller Element to the Right (NSR) for the stack top.
            while (!st.empty() && curr_height < heights[st.top()])
            {
                // 1. Pop the index of the bar whose area we are calculating
                int h_idx = st.top();
                int h = heights[h_idx];
                st.pop();

                // 2. Determine the boundaries and calculate the width
                // - NSR is 'i' (the current index that is shorter)
                // - NSL is 'st.top()' (the index below the popped element)
                int width = st.empty()
                                       ? i                 // If stack is empty, no smaller bar to the left. Width = i.
                                       : i - st.top() - 1; // Width = NSR - NSL - 1

                // 3. Update the maximum area
                max_area = max(max_area, h * width);
            }

            // Push the current index to maintain the increasing order property
            st.push(i);
        }
        return max_area;
    }
};

int main()
{
    Solution sol;

    cout << "--- Largest Rectangle in Histogram Test Cases ---\n";

    // Test Case 1: Standard example
    vector<int> heights1 = {2, 1, 5, 6, 2, 3};
    // Max area is 10 (bars of height 5 and 6, width 2)
    cout << "Test 1 ([2, 1, 5, 6, 2, 3]): Expected 10, Got " << sol.largestRectangleArea(heights1) << endl;

    // Test Case 2: All same height
    vector<int> heights2 = {2, 2, 2, 2, 2};
    // Max area is 10 (height 2, width 5)
    cout << "Test 2 ([2, 2, 2, 2, 2]): Expected 10, Got " << sol.largestRectangleArea(heights2) << endl;

    // Test Case 3: Increasing heights (processed by the dummy 0)
    vector<int> heights3 = {1, 2, 3, 4, 5};
    // Max area is 9 (bar of height 4, width 2, or height 3, width 3) - Max is 5 * 1 or 1*5 = 5. Wait, 3*3=9, 4*2=8, 5*1=5. Max is 9. No, 5*1=5, 4*2=8, 3*3=9, 2*4=8, 1*5=5. Max is 9. Ah, max is 3*3 (indices 0, 1, 2, height 3 at index 2). The largest rectangle is 3*3=9.
    // The largest rectangle here is the full width of 5 at height 1 (Area 5), or height 2 over width 4 (Area 8), or height 3 over width 3 (Area 9).
    cout << "Test 3 ([1, 2, 3, 4, 5]): Expected 9, Got " << sol.largestRectangleArea(heights3) << endl;

    // Test Case 4: Single largest bar (1)
    vector<int> heights4 = {1};
    cout << "Test 4 ([1]): Expected 1, Got " << sol.largestRectangleArea(heights4) << endl;

    return 0;
}