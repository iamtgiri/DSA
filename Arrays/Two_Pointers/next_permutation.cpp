/*
File: 2-next_permutation.cpp
Date: 2025-09-10 09:25

Problem: Next Permutation
Link: https://leetcode.com/problems/next-permutation/
Problem Statement:
    Given an array of integers, rearrange its numbers into the
    lexicographically next greater permutation of numbers.
    If no such arrangement is possible (i.e., array is descending),
    rearrange it into the lowest possible order (sorted ascending).

Example:
    Input: [1,2,3] → Output: [1,3,2]
    Input: [3,2,1] → Output: [1,2,3]

-------------------------------------------------
❌ Brute Force
- Idea: Generate all permutations, sort them,
        and pick the next one after the current.
- Time complexity: O(n! * n log n)
- Space complexity: O(n! * n)
- Limitations: Completely impractical.

✅ Optimized Approach
- Idea:
    * Find pivot index i such that arr[i] < arr[i+1] (from right).
    * If no such pivot, array is last permutation → reverse it.
    * Otherwise, find the smallest element > arr[i] to the right.
    * Swap arr[i] and that element.
    * Reverse the suffix to get smallest lexicographic order.
- Time complexity: O(n)
- Space complexity: O(1)

💡 Key Pattern:
- Next lexicographic ordering
- Suffix manipulation

Keywords:
- Arrays, Greedy, Permutations

🗒️ Notes
- Classic problem, often seen in coding interviews.
- Careful with strictly descending arrays (edge case).
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextPermutation(vector<int> arr) {
        int n = arr.size();
        int pivot = n - 2;

        // Step 1: find pivot
        while (pivot >= 0 && arr[pivot] >= arr[pivot + 1]) {
            --pivot;
        }

        // Step 2: if no pivot, it's last permutation
        if (pivot < 0) {
            reverse(arr.begin(), arr.end());
            return arr;
        }

        // Step 3: find element to swap with pivot
        int swp = n - 1;
        while (arr[swp] <= arr[pivot]) {
            --swp;
        }
        swap(arr[pivot], arr[swp]);

        // Step 4: reverse suffix
        reverse(arr.begin() + pivot + 1, arr.end());
        return arr;
    }
};

int main() {
    Solution sol;
    vector<int> arr = {30, 12, 10, 20, 17, 11, 9};

    arr = sol.nextPermutation(arr);

    for (int x : arr) cout << x << " ";
    return 0;
}
