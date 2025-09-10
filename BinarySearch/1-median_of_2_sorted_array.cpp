/*
File: 1-median_of_2_sorted_array.cpp
Date: 2025-09-09 19:47

Problem: Median of Two Sorted Arrays
Link: https://leetcode.com/problems/median-of-two-sorted-arrays/
Problem Statement:
    Given two sorted arrays arr1[] and arr2[] of size m and n respectively,
    find the median of the two sorted arrays.

Example 1:
    Input: arr1 = [1, 3], arr2 = [2]
    Output: 2
    Explanation: Merged array is [1, 2, 3], median is 2.

Example 2:
    Input: arr1 = [1, 2], arr2 = [3, 4]
    Output: 2.5
    Explanation: Merged array is [1, 2, 3, 4], median is (2+3)/2.

-------------------------------------------------
❌ Brute Force
- Idea: Merge both arrays, then pick the middle element(s).
- Time complexity: O(m+n)
- Space complexity: O(m+n)
- Limitations: Too slow and memory heavy for large arrays.

✅ Optimized Approach (Binary Search Partition)
- Idea:
    Use binary search on the smaller array to partition both arrays
    such that:
      - Left partitions contain half of the elements.
      - Every element in left <= every element in right.
    Then median is max(left parts) and min(right parts).
- Time complexity: O(log(min(m, n)))
- Space complexity: O(1)

💡 Key Pattern:
- Binary Search on Partition

Keywords:
- Binary Search, Median, Partition

🗒️ Notes
- Very common interview question.
- Learned how to balance two arrays with binary search.
- Edge cases: Empty array, odd/even total length.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(const vector<int> &arr1, const vector<int> &arr2) {
        int n1 = arr1.size(), n2 = arr2.size();

        // Ensure arr1 is the smaller array
        if (n1 > n2) return findMedianSortedArrays(arr2, arr1);

        int low = 0, high = n1;
        int total = n1 + n2;
        int half = (total + 1) / 2; // left side size

        while (low <= high) {
            int cut1 = (low + high) / 2;       // partition in arr1
            int cut2 = half - cut1;            // partition in arr2

            int L1 = (cut1 == 0) ? INT_MIN : arr1[cut1 - 1];
            int L2 = (cut2 == 0) ? INT_MIN : arr2[cut2 - 1];
            int R1 = (cut1 == n1) ? INT_MAX : arr1[cut1];
            int R2 = (cut2 == n2) ? INT_MAX : arr2[cut2];

            if (L1 <= R2 && L2 <= R1) {
                // Correct partition found
                if (total % 2 == 0)
                    return (max(L1, L2) + min(R1, R2)) / 2.0;
                else
                    return max(L1, L2);
            } else if (L1 > R2) {
                high = cut1 - 1; // move left in arr1
            } else {
                low = cut1 + 1;  // move right in arr1
            }
        }
        return -1; // should never happen
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;

    // Example test cases
    vector<int> arr1 = {1, 3}, arr2 = {2};
    cout << sol.findMedianSortedArrays(arr1, arr2) << "\n"; // 2

    arr1 = {1, 2}, arr2 = {3, 4};
    cout << sol.findMedianSortedArrays(arr1, arr2) << "\n"; // 2.5

    arr1 = {2, 5}, arr2 = {1, 3, 4};
    cout << sol.findMedianSortedArrays(arr1, arr2) << "\n"; // 3

    return 0;
}
