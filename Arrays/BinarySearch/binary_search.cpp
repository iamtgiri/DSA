/*
File: 0-binary_search.cpp
Date: 2025-09-11 11:35

Problem: First and Last Occurrence of a Target in Sorted Array
Link: URL
Problem Statement:
    Given a sorted array of size N and a target value, find the index of the 
    first and last occurrence of the target. If the target does not exist, return -1.

Example:
    Input:
        N = 7
        arr = [2, 4, 4, 4, 6, 8, 9]
        target = 4
    Output:
        First Occurrence = 1
        Last Occurrence  = 3

-------------------------------------------------
❌ Brute Force
- Idea: Scan the entire array linearly, record first and last index of target.
- Time complexity: O(N)
- Space complexity: O(1)
- Limitations: Inefficient for large arrays.

✅ Optimized Approach (Binary Search)
- Idea: Use modified binary search twice —
        once to find the first occurrence,
        once to find the last occurrence.
- Time complexity: O(log N)
- Space complexity: O(1)

💡 Key Pattern:
- Binary search variant
- Narrowing down by moving mid boundary

Keywords:
- Binary search, first occurrence, last occurrence, sorted array

🗒️ Notes
- Classic template for "search range" type problems.
- Be careful with edge cases: target not found, duplicates.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Binary search helper to find either first or last occurrence
    int binarySearch(int arr[], int n, int target, bool findFirst) {
        int left = 0, right = n - 1, ans = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] == target) {
                ans = mid; // record answer
                if (findFirst) {
                    // keep searching left side
                    right = mid - 1;
                } else {
                    // keep searching right side
                    left = mid + 1;
                }
            } 
            else if (arr[mid] < target) {
                left = mid + 1;
            } 
            else {
                right = mid - 1;
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;

    int n, target;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    cin >> target;

    // Find first and last occurrence
    int first = sol.binarySearch(arr.data(), n, target, true);
    int last  = sol.binarySearch(arr.data(), n, target, false);

    cout << first << " " << last << "\n";

    return 0;
}
