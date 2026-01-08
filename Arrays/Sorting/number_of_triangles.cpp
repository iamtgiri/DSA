/*
File: number_of_triangles.cpp
Date: 2026-01-08 10:43

Problem: Number of Triangles
Link: https://www.geeksforgeeks.org/problems/count-possible-triangles-1587115620/1

Problem Statement:
Given an unsorted array of positive integers, count the number of triangles that
can be formed with three different array elements as lengths of three sides of
the triangle. A triangle can be formed if and only if the sum of any two sides
is greater than the third side (a + b > c).

-------------------------------------------------
Brute Force
- Idea: Use three nested loops to pick every possible triplet (i, j, k).
  For each triplet, check if it satisfies the triangle inequality conditions:
  (arr[i] + arr[j] > arr[k]), (arr[i] + arr[k] > arr[j]), and (arr[j] + arr[k] > arr[i]).
- Time complexity: O(N^3)
- Space complexity: O(1)
- Limitations: Inefficient for arrays with more than a few hundred elements.

Current/Optimized Approachs
- Idea: If we sort the array, the triangle inequality simplifies. For three
  sorted elements a <= b <= c, we only need to check if a + b > c. If this holds,
  then all other inequalities (a + c > b and b + c > a) are automatically satisfied.
- Approach: Sorting + Two Pointers.
- Algorithm:
    1. Sort the array in ascending order.
    2. Fix the largest side 'arr[i]' by iterating from the end of the array
       (i = n-1 down to 2).
    3. For each fixed 'i', use two pointers: 'left' at 0 and 'right' at i-1.
    4. While left < right:
       - If arr[left] + arr[right] > arr[i]:
         - Since the array is sorted, if (arr[left] + arr[right]) is greater than
           arr[i], then any element between 'left' and 'right' added to arr[right]
           will also be greater than arr[i].
         - Total such pairs for current 'right' and 'i' = (right - left).
         - Add (right - left) to the count and move the 'right' pointer down (right--).
       - Else:
         - The sum is too small. Move the 'left' pointer up (left++) to increase the sum.
- Time complexity: O(N^2). Sorting takes O(N log N) and the nested loops take O(N^2).
- Space complexity: O(1) auxiliary space (excluding space used by the sorting algorithm).

💡 Key Pattern:
- Two Pointers on Sorted Array: Reducing a 3-variable problem (triplets) to a
  2-variable problem by fixing one variable and using pointers to find valid pairs.

ℹ️ Keywords:
- Triangle Inequality, Two Pointers, Sorting, O(N^2), Triplets.

🗒️ Notes
- The "right - left" logic is the core optimization that avoids the third loop.
- The input must consist of positive integers; zero or negative values cannot
  form physical triangle sides.
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
     * @brief Counts the number of triplets that can form a valid triangle.
     * @details A triangle can be formed if the sum of any two sides is greater than the third side.
     * This function sorts the array and uses a two-pointer technique to efficiently count
     * the valid triplets. 
     * @param arr The input vector of side lengths.
     * @return Total number of possible triangles.
     */
    int countTriangles(vector<int> &arr)
    {
        int n = arr.size();
        if (n < 3)
            return 0;

        // 1. Sort the array to use the two-pointer property
        sort(arr.begin(), arr.end());
        int count = 0;

        // 2. Fix the longest side 'i'
        for (int i = n - 1; i >= 2; i--)
        {
            int left = 0;
            int right = i - 1;

            // 3. Find pairs (left, right) such that arr[left] + arr[right] > arr[i]
            while (left < right)
            {
                if (arr[left] + arr[right] > arr[i])
                {
                    // If arr[left] + arr[right] > arr[i], then every index k
                    // from left to right-1 also satisfies arr[k] + arr[right] > arr[i]
                    count += (right - left);

                    // Move right pointer to check for other possible pairs with the same i
                    right--;
                }
                else
                {
                    // Sum is not large enough, need a larger value from the left
                    left++;
                }
            }
        }
        return count;
    }
};

int main()
{
    Solution sol;

    // Test Case 1: Standard case
    vector<int> arr1 = {3, 5, 4, 7};
    // Sorted: 3, 4, 5, 7
    // i=3 (7): (3,5), (4,5) -> count=2
    // i=2 (5): (3,4) -> count=1
    // Total: 3
    cout << "Test 1: {3, 5, 4, 7}" << endl;
    cout << "Result: " << sol.countTriangles(arr1) << " (Expected: 3)" << endl;
    cout << "------------------------------------" << endl;

    // Test Case 2: No triangles possible
    vector<int> arr2 = {10, 2, 1, 3};
    // Sorted: 1, 2, 3, 10
    // i=3 (10): 1+3 < 10, 2+3 < 10
    // i=2 (3): 1+2 = 3 (not >)
    // Total: 0
    cout << "Test 2: {10, 2, 1, 3}" << endl;
    cout << "Result: " << sol.countTriangles(arr2) << " (Expected: 0)" << endl;
    cout << "------------------------------------" << endl;

    // Test Case 3: All sides equal
    vector<int> arr3 = {2, 2, 2, 2};
    // nCr(4, 3) = 4
    cout << "Test 3: {2, 2, 2, 2}" << endl;
    cout << "Result: " << sol.countTriangles(arr3) << " (Expected: 4)" << endl;
    cout << "------------------------------------" << endl;

    return 0;
}