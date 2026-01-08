/*
File: 3_way_merge_sort.cpp
Date: 2026-01-08 10:37

Problem: 3 Way Merge Sort
Link: URL

Problem Statement:
Implement a modified Merge Sort algorithm where, instead of splitting the array
into two parts, the array is divided into three equal (or nearly equal) parts.
Sort these parts recursively and merge them back together.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Standard 2-way Merge Sort.
- Time complexity: O(N log2 N)
- Space complexity: O(N)
- Limitations: While very efficient, the recursion depth is log2(N). 3-way merge sort
  aims to reduce recursion depth to log3(N) at the cost of more comparisons per merge step.

Current/Optimized Approachs
- Idea: Use the Divide and Conquer paradigm to split the problem into three
  sub-problems. The merge step must then handle three sorted sequences simultaneously.
- Approach: **Recursive 3-way Divide and Conquer**.
- Algorithm:
    1. **Divide:** If the range size is greater than 1, calculate two middle indices
       to split the range `[left, right)` into three segments:
       `[left, mid1)`, `[mid1, mid2)`, and `[mid2, right)`.
    2. **Conquer:** Recursively call `mergeSort3` on all three segments.
    3. **Merge:** Combine the three sorted segments:
       - Maintain three pointers (i, j, k) at the start of each segment.
       - In each step of the merge, compare the elements at the three pointers.
       - Pick the smallest of the three, move it to a temporary buffer, and
         advance the corresponding pointer.
       - Handle exhausted segments by using a sentinel value (e.g., INT_MAX).
    4. **Copy:** Transfer the merged elements from the temporary buffer back to
       the original array.
- Time complexity: **O(N log3 N)**. The recursion depth is reduced, but the
  number of comparisons in the merge step increases (2 comparisons to find the
  minimum of 3 elements).
- Space complexity: **O(N)** for the auxiliary buffer used during merging.

💡 Key Pattern:
- **Multi-way Merge:** Extending the standard 2-way merge to K ways (in this case, 3).
  This is a fundamental concept used in external sorting (merging multiple sorted
  files or "runs").

ℹ️ Keywords:
- Merge Sort, 3-way Merge, Divide and Conquer, Recursion, O(N log N).

🗒️ Notes
- Splitting into 3 parts: `third = (right - left) / 3`.
  `mid1 = left + third`.
  `mid2 = left + 2 * third + ((right - left) % 3 > 0 ? 1 : 0)`.
- Using `INT_MAX` as a sentinel simplifies the comparison logic when one or
  two of the three segments are exhausted.
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution
{
public:
    /**
     * @brief Merges three sorted sub-ranges of an array into a single sorted range.
     * @param arr The main array.
     * @param left Start index of the first segment.
     * @param mid1 Start index of the second segment.
     * @param mid2 Start index of the third segment.
     * @param right End index (exclusive) of the third segment.
     */
    void merge3(vector<int> &arr, int left, int mid1, int mid2, int right)
    {
        vector<int> temp;
        temp.reserve(right - left);

        int i = left; // Pointer for [left, mid1)
        int j = mid1; // Pointer for [mid1, mid2)
        int k = mid2; // Pointer for [mid2, right)

        // Continue until all elements from all three segments are merged
        while (i < mid1 || j < mid2 || k < right)
        {
            // Use INT_MAX as sentinel if a segment is exhausted
            int val1 = (i < mid1) ? arr[i] : INT_MAX;
            int val2 = (j < mid2) ? arr[j] : INT_MAX;
            int val3 = (k < right) ? arr[k] : INT_MAX;

            // Find the minimum among the three current elements
            if (val1 <= val2 && val1 <= val3)
            {
                temp.push_back(val1);
                i++;
            }
            else if (val2 <= val1 && val2 <= val3)
            {
                temp.push_back(val2);
                j++;
            }
            else
            {
                temp.push_back(val3);
                k++;
            }
        }

        // Copy the merged elements back to the original array
        for (int idx = 0; idx < (int)temp.size(); idx++)
        {
            arr[left + idx] = temp[idx];
        }
    }

    /**
     * @brief Recursive function to perform 3-way merge sort.
     * @param arr The array to be sorted.
     * @param left The starting index (inclusive).
     * @param right The ending index (exclusive).
     */
    void mergeSort3(vector<int> &arr, int left, int right)
    {
        // Base case: range has 0 or 1 element
        if (right - left < 2)
            return;

        // Divide the range into three parts
        int n = right - left;
        int third = n / 3;

        int mid1 = left + third;
        // Ensure mid2 calculation covers remainders (n % 3)
        int mid2 = left + 2 * third + (n % 3 == 2 ? 1 : 0);

        // Sort the three parts recursively
        mergeSort3(arr, left, mid1);
        mergeSort3(arr, mid1, mid2);
        mergeSort3(arr, mid2, right);

        // Merge the three sorted parts
        merge3(arr, left, mid1, mid2, right);
    }
};

// Helper function to print the array
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
    vector<int> arr1 = {45, -2, 10, 15, 2, 7, 11, 0, 5};
    cout << "Test 1 Original: ";
    printArray(arr1);
    sol.mergeSort3(arr1, 0, arr1.size());
    cout << "Test 1 Sorted:   ";
    printArray(arr1);
    cout << "------------------------------------" << endl;

    // Test Case 2: Sorted array
    vector<int> arr2 = {1, 2, 3, 4, 5, 6, 7, 8};
    cout << "Test 2 Original: ";
    printArray(arr2);
    sol.mergeSort3(arr2, 0, arr2.size());
    cout << "Test 2 Sorted:   ";
    printArray(arr2);
    cout << "------------------------------------" << endl;

    // Test Case 3: Small array
    vector<int> arr3 = {2, 1};
    cout << "Test 3 Original: ";
    printArray(arr3);
    sol.mergeSort3(arr3, 0, arr3.size());
    cout << "Test 3 Sorted:   ";
    printArray(arr3);
    cout << "------------------------------------" << endl;

    return 0;
}