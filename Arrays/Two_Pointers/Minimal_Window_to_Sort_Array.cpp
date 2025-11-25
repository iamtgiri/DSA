/*
File: Minimal_Window_to_Sort_Array.cpp
Date: 2025-11-25 13:50

Problem: Smallest Subarray to be Sorted to make the whole array sorted
Link: https://www.geeksforgeeks.org/dsa/minimum-length-unsorted-subarray-sorting-which-makes-the-complete-array-sorted/

Problem Statement:
Given an array of integers `arr`, find the indices `s` (start) and `e` (end) defining the smallest contiguous subarray `arr[s..e]` such that sorting this subarray makes the entire array sorted. If the array is already sorted, return a window of size 0 (e.g., {0, 0} or {-1, -1}).

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Sort a copy of the array. Compare the original array with the sorted array to find the first mismatch index `s` from the left and the first mismatch index `e` from the right. The subarray is `arr[s..e]`.
- Time complexity: O(N log N) due to sorting.
- Space complexity: O(N) to store the auxiliary sorted array.
- Limitations: Not the most efficient approach if we can avoid a full sort.

Current/Optimized Approachs
- Idea: Identify the minimal window boundaries by finding the start of disorder, the end of disorder, and then adjusting these boundaries outward based on the minimum and maximum values within that initial window.
- Approach: **Linear Scan (Four Pass)**
- Algorithm:
  1. **Find `s` (Start of Disorder):** Scan from the left (`i=0`) and find the first index `i` such that `arr[i] > arr[i+1]`. Set `s = i`. If no such index is found, the array is sorted (return {0, 0}).
  2. **Find `e` (End of Disorder):** Scan from the right (`i=n-1`) and find the first index `i` such that `arr[i-1] > arr[i]`. Set `e = i`.
  3. **Find Min/Max in Subarray `arr[s..e]`:** Calculate `subMin` and `subMax` of the elements within the determined window `arr[s..e]`. These values represent the range that needs to be properly positioned.
  4. **Adjust `s` (Expand Left):** Scan from the beginning (`i=0` to `s-1`). Find the first index `i` where the element `arr[i]` is **greater than** `subMin`. This element is out of place and must be included in the window, so update `s = i`. Stop expanding once found.
  5. **Adjust `e` (Expand Right):** Scan from the end (`i=n-1` to `e+1`). Find the first index `i` where the element `arr[i]` is **less than** `subMax`. This element is out of place and must be included, so update `e = i`. Stop expanding once found.
  6. **Result:** The minimal window is defined by the final indices `s` and `e`.
- Time complexity: **O(N)** (Since the algorithm performs a fixed number of linear passes over the array).
- Space complexity: O(1) auxiliary space (excluding input array).

💡 Key Pattern:
- **Two-Pointer Expansion:** Using initial boundary markers (`s` and `e`) and then expanding them outward to ensure all misplaced elements (relative to the subarray's min/max) are included.

ℹ️ Keywords:
- Subarray, Unsorted, Linear Time, Two Pointers, Minimum Window.

🗒️ Notes
- The steps 4 and 5 are crucial: An element *before* `s` must be included if it's larger than the minimum element *inside* the initial window `arr[s..e]`. Similarly, an element *after* `e` must be included if it's smaller than the maximum element *inside* `arr[s..e]`.
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <utility>

using namespace std;

class Solution
{
public:
    /**
     * @brief Finds the start and end indices of the minimal window to sort the array.
     * @param arr The input array.
     * @return A pair {s, e} representing the start and end indices (0-based) of the subarray.
     */
    pair<int, int> findUnsortedWindow(vector<int> &arr)
    {
        int n = arr.size();
        int s = -1, e = -1;

        // 1) Find first out-of-order from left (Start of disorder)
        for (int i = 0; i < n - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                s = i;
                break;
            }
        }
        // If no such point, array is already sorted (s remains -1)
        if (s == -1)
        {
            // Returning {0, 0} indicates a window of length 0 (already sorted).
            return {0, 0};
        }

        // 2) Find first out-of-order from right (End of disorder)
        for (int i = n - 1; i > 0; i--)
        {
            if (arr[i - 1] > arr[i])
            {
                e = i;
                break;
            }
        }

        // At this point, arr[s..e] is the initial disordered segment.

        // 3) Find min and max in arr[s..e]
        int subMin = INT_MAX, subMax = INT_MIN;
        for (int i = s; i <= e; i++)
        {
            subMin = min(subMin, arr[i]);
            subMax = max(subMax, arr[i]);
        }

        // 4) Expand left: Find the first element in the sorted prefix (0 to s-1)
        // that is greater than the subarray's minimum (subMin).
        for (int i = 0; i < s; i++)
        {
            if (arr[i] > subMin)
            {
                s = i; // Found the new start boundary
                break;
            }
        }

        // 5) Expand right: Find the first element in the sorted suffix (n-1 down to e+1)
        // that is smaller than the subarray's maximum (subMax).
        for (int i = n - 1; i > e; i--)
        {
            if (arr[i] < subMax)
            {
                e = i; // Found the new end boundary
                break;
            }
        }

        return {s, e};
    }
};

int main()
{
    Solution sol;

    // Helper function to print results
    auto print_result = [&](const vector<int> &arr)
    {
        vector<int> copy_arr = arr; // Pass a copy for manipulation
        pair<int, int> result = sol.findUnsortedWindow(copy_arr);
        int s = result.first;
        int e = result.second;

        cout << "Array: {";
        for (int i = 0; i < arr.size(); ++i)
        {
            cout << arr[i] << (i < arr.size() - 1 ? ", " : "");
        }
        cout << "}" << endl;

        if (s == 0 && e == 0)
        {
            cout << "Result: Already sorted." << endl;
        }
        else
        {
            cout << "Minimal Window: [" << s << ", " << e << "]" << endl;
            cout << "Length: " << (e - s + 1) << endl;
        }
        cout << "---" << endl;
    };

    // Example Test Case 1 (Standard case)
    // s=3 (30 > 25), e=7 (50 < 60). subMin=25, subMax=50.
    // Left expansion: arr[2]=20 < 25. No expansion. s=3.
    // Right expansion: arr[9]=80 > 50. No expansion. e=7.
    vector<int> arr1 = {10, 12, 20, 30, 25, 40, 32, 50, 60, 80};
    print_result(arr1); // Expected: [3, 7]

    // Example Test Case 2 (Requires left expansion)
    // s=1 (5 > 1), e=3 (4 > 3). subMin=1, subMax=4.
    // Left expansion: arr[0]=10 > 1 (subMin). New s=0.
    // Right expansion: e=3.
    vector<int> arr2 = {10, 5, 1, 3, 4, 15};
    print_result(arr2); // Expected: [0, 4]

    // Example Test Case 3 (Requires right expansion)
    // s=2 (10 > 5), e=4 (1 > 2). subMin=1, subMax=10.
    // Left expansion: s=2.
    // Right expansion: arr[5]=0 < 10 (subMax). New e=5.
    vector<int> arr3 = {1, 2, 10, 5, 1, 0};
    print_result(arr3); // Expected: [2, 5]

    // Example Test Case 4 (Already sorted)
    vector<int> arr4 = {1, 2, 3, 4, 5};
    print_result(arr4); // Expected: Already sorted.

    return 0;
}