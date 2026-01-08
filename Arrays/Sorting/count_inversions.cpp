/*
File: count_inversions.cpp
Date: 2026-01-08 10:40

Problem: Count the total number of inversions
Link: https://www.geeksforgeeks.org/problems/inversion-of-array-1587115620/1

Problem Statement:
Given an array of integers, count the total number of inversions.
An inversion is defined as a pair (i, j) such that i < j and arr[i] > arr[j].
Inversions represent how far an array is from being sorted.

-------------------------------------------------
Brute Force
- Idea: Use two nested loops to check every possible pair (i, j).
  If i < j and arr[i] > arr[j], increment the inversion count.
- Time complexity: O(N^2)
- Space complexity: O(1)
- Limitations: Inefficient for large arrays (N > 10,000).

Current/Optimized Approachs
- Idea: Modify the Merge Sort algorithm. During the merge step, when we pick
  an element from the right subarray that is smaller than the current element
  in the left subarray, it signifies an inversion with the current element
  and all subsequent elements in the left subarray (since the left subarray is sorted).
- Approach: Divide and Conquer (Merge Sort variation).
- Algorithm:
    1. Divide the array into two halves recursively.
    2. Count inversions in the left half.
    3. Count inversions in the right half.
    4. Count "cross-inversions" during the merge step:
       - Maintain two pointers i and j for left and right subarrays.
       - If arr[i] <= arr[j], no inversion relative to arr[i].
       - If arr[i] > arr[j], then arr[j] is smaller than all elements from
         index i to the end of the left subarray.
         Add (size_of_left_subarray - i) to the total inversion count.
    5. Sum all counts and return.
- Time complexity: O(N log N), identical to standard Merge Sort.
- Space complexity: O(N) for the temporary arrays used during merging.

💡 Key Pattern:
- Divide and Conquer: Using the structure of a sorting algorithm to extract
  metadata (inversions) without increasing the asymptotic complexity.

ℹ️ Keywords:
- Inversion Count, Merge Sort, Divide and Conquer, Sorting, O(N log N).

🗒️ Notes
- Using long long for the inversion count is essential because a reverse-sorted
  array of size 10^5 can have nearly 5 * 10^9 inversions, which exceeds a 32-bit integer.
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    /**
     * @brief Merges two sorted halves and counts inversions between them.
     * @param arr The main array being sorted.
     * @param left Starting index of the range.
     * @param mid Middle index separating the two halves.
     * @param right Ending index of the range.
     * @return Number of cross-inversions found during this merge.
     */
    long long mergeAndCount(vector<int> &arr, int left, int mid, int right)
    {
        // Create temporary arrays for left and right subarrays
        vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
        vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

        long long invCount = 0;
        size_t i = 0, j = 0;
        int k = left;

        // Standard merge logic with inversion counting
        while (i < leftArr.size() && j < rightArr.size())
        {
            if (leftArr[i] <= rightArr[j])
            {
                arr[k++] = leftArr[i++];
            }
            else
            {
                // If leftArr[i] > rightArr[j], then all elements from i to
                // the end of leftArr are also > rightArr[j].
                arr[k++] = rightArr[j++];
                invCount += (leftArr.size() - i);
            }
        }

        // Copy remaining elements of leftArr, if any
        while (i < leftArr.size())
        {
            arr[k++] = leftArr[i++];
        }

        // Copy remaining elements of rightArr, if any
        while (j < rightArr.size())
        {
            arr[k++] = rightArr[j++];
        }

        return invCount;
    }

    /**
     * @brief Recursively divides the array and sums up inversion counts.
     * @param arr The array.
     * @param left Start index.
     * @param right End index.
     * @return Total inversion count in the range [left, right].
     */
    long long mergeSortAndCount(vector<int> &arr, int left, int right)
    {
        long long invCount = 0;
        if (left < right)
        {
            int mid = left + (right - left) / 2;

            // Count inversions in the left half
            invCount += mergeSortAndCount(arr, left, mid);
            // Count inversions in the right half
            invCount += mergeSortAndCount(arr, mid + 1, right);
            // Count inversions across the two halves while merging
            invCount += mergeAndCount(arr, left, mid, right);
        }
        return invCount;
    }
};

int main()
{
    Solution sol;

    // Test Case 1: Random array
    vector<int> arr1 = {8, 4, 2, 1};
    // Pairs: (8,4), (8,2), (8,1), (4,2), (4,1), (2,1) -> 6 inversions
    cout << "Test 1: {8, 4, 2, 1}" << endl;
    cout << "Inversion Count: " << sol.mergeSortAndCount(arr1, 0, arr1.size() - 1) << " (Expected: 6)" << endl;
    cout << "------------------------------------" << endl;

    // Test Case 2: Already sorted array
    vector<int> arr2 = {1, 2, 3, 4, 5};
    cout << "Test 2: {1, 2, 3, 4, 5}" << endl;
    cout << "Inversion Count: " << sol.mergeSortAndCount(arr2, 0, arr2.size() - 1) << " (Expected: 0)" << endl;
    cout << "------------------------------------" << endl;

    // Test Case 3: Reverse sorted array
    vector<int> arr3 = {5, 4, 3, 2, 1};
    // 5+4+3+2+1... wait, n*(n-1)/2 = 5*4/2 = 10
    cout << "Test 3: {5, 4, 3, 2, 1}" << endl;
    cout << "Inversion Count: " << sol.mergeSortAndCount(arr3, 0, arr3.size() - 1) << " (Expected: 10)" << endl;
    cout << "------------------------------------" << endl;

    return 0;
}