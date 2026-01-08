/*
File: one_loop_insertion_sort.cpp
Date: 2026-01-08 10:34

Problem: One Loop Insertion Sort
Link: URL (Commonly referred to as Gnome Sort)

Problem Statement:
Write a program to implement the insertion sort algorithm using only one loop.

-------------------------------------------------
Brute Force (Standard Insertion Sort)
- Idea: Use two nested loops. The outer loop iterates through the array from the second element
  to the last. The inner loop moves the current element backward into its correct sorted
  position among the previously seen elements.
- Time complexity: O(N^2) for the nested iteration.
- Space complexity: O(1) in-place.
- Limitations: Uses two loops explicitly.

Current/Optimized Approach
- Idea: Simulate the "inner loop" behavior by manually decreasing the loop index when a swap
  is necessary and increasing it when the local elements are in order.
- Approach: Single-Loop Pointer Management (Gnome Sort logic).
- Algorithm:
  1. Initialize a pointer 'i' at index 1.
  2. While 'i' is less than the array size:
     a. Check if 'i' is 0 or if the element at 'i' is greater than or equal to the element at 'i-1'.
     b. If either is true, the current window is sorted. Move the pointer forward (i++).
     c. Otherwise, the elements are out of order. Swap arr[i] and arr[i-1], and move the
        pointer backward (i--) to ensure the swapped element is checked against its new
        preceding neighbor.
- Time complexity: O(N^2). In the worst case (reverse sorted array), the pointer moves back
  to index 0 for every element, resulting in the same number of comparisons as standard
  insertion sort.
- Space complexity: O(1) auxiliary space.

💡 Key Pattern:
- Pointer Backtracking: Controlling the loop variable manually (incrementing/decrementing)
  allows a single loop to perform multi-dimensional tasks.

ℹ️ Keywords:
- Insertion Sort, Gnome Sort, Single Loop, In-place Sort, Stable Sort.

🗒️ Notes
- While this implementation uses only one loop syntactically, the number of operations
  performed is still quadratic.
- This is a "Stable" sort, meaning equal elements maintain their relative order.
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
     * @brief Sorts an array in ascending order using the logic of Insertion Sort
     * but restricted to a single loop structure.
     * @param arr The vector of integers to be sorted.
     */
    void oneloop_insertion_sort(vector<int> &arr)
    {
        int n = arr.size();
        // Start from the second element
        for (int i = 1; i < n;)
        {
            // If the current element is smaller than the previous one, they are out of order.
            if (i > 0 && arr[i] < arr[i - 1])
            {
                // Swap them
                swap(arr[i], arr[i - 1]);
                // Move backward to re-check the swapped element against its new predecessor
                i--;
            }
            else
            {
                // If they are in order or we reached the start, move to the next unsorted element
                i++;
            }
        }
    }
};

// Helper function to print the vector
void printArray(const vector<int> &arr)
{
    cout << "[";
    for (size_t i = 0; i < arr.size(); ++i)
    {
        cout << arr[i] << (i == arr.size() - 1 ? "" : ", ");
    }
    cout << "]" << endl;
}

int main()
{
    Solution sol;

    // Test Case 1: Random array
    vector<int> arr1 = {5, 2, 9, 1, 5, 6};
    cout << "Test 1 Original: ";
    printArray(arr1);
    sol.oneloop_insertion_sort(arr1);
    cout << "Test 1 Sorted:   ";
    printArray(arr1);
    cout << "------------------------------------" << endl;

    // Test Case 2: Reverse sorted array
    vector<int> arr2 = {10, 8, 6, 4, 2};
    cout << "Test 2 Original: ";
    printArray(arr2);
    sol.oneloop_insertion_sort(arr2);
    cout << "Test 2 Sorted:   ";
    printArray(arr2);
    cout << "------------------------------------" << endl;

    // Test Case 3: Already sorted array
    vector<int> arr3 = {1, 2, 3, 4, 5};
    cout << "Test 3 Original: ";
    printArray(arr3);
    sol.oneloop_insertion_sort(arr3);
    cout << "Test 3 Sorted:   ";
    printArray(arr3);
    cout << "------------------------------------" << endl;

    return 0;
}