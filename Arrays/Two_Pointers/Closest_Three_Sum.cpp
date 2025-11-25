/*
File: Closest_Three_Sum.cpp
Date: 2025-11-25 08:26

Problem: Closest Three Sum
Link: https://www.geeksforgeeks.org/problems/three-sum-closest/1    
Problem Statement:
Given an array 'arr' of N integers and an integer 'target', find three integers in 'arr' such that their sum is closest to 'target'. Return the sum of the three integers.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Iterate through all possible triplets (i, j, k) using three nested loops, calculate their sum, and keep track of the sum that has the minimum absolute difference from the target.
- Time complexity: O(N^3)
- Space complexity: O(1)
- Limitations: Inefficient for large input arrays.

Current/Optimized Approachs
- Idea: Reduce the complexity from O(N^3) to O(N^2) by using the Two-Pointer Technique on a sorted array. Fix one element and find the remaining two elements in O(N) time.
- Approach: **Sorting + Two Pointers** 
- Algorithm:
  1. Sort the input array 'arr' in ascending order.
  2. Initialize 'best' sum with the sum of the first three elements.
  3. Iterate through the array with a fixed pointer 'i' from index 0 to N-3.
  4. Initialize 'left' pointer at i + 1 and 'right' pointer at N - 1.
  5. While 'left' < 'right':
     a. Calculate 'current_sum' = arr[i] + arr[left] + arr[right].
     b. Compare the absolute difference: if abs(target - current_sum) < abs(target - best), update 'best' = 'current_sum'.
     c. If 'current_sum' < 'target', increment 'left' (to increase the sum).
     d. If 'current_sum' > 'target', decrement 'right' (to decrease the sum).
     e. If 'current_sum' == 'target', return the sum immediately.
- Time complexity: **O(N^2)** (O(N log N) for sorting + O(N^2) for the nested loops).
- Space complexity: O(1) (excluding space for sorting, if not done in-place).

💡 Key Pattern:
- **Two-Pointer Technique:** Used on sorted arrays to efficiently find pairs (or triplets/quadruplets) that satisfy a certain sum or distance criterion.

ℹ️ Keywords:
- Two Pointers, Sorting, Triplet Sum, Closest Sum, O(N^2).

🗒️ Notes
- Sorting the array is crucial for the Two-Pointer technique to work, as it guarantees that moving 'left' increases the sum and moving 'right' decreases the sum.
- Initializing 'best' to a valid sum (like the first three elements) ensures correct distance comparison.
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

class Solution {
public:
    /**
    * @brief Finds three elements in the array whose sum is closest to the target.
    * @param arr The input vector of integers.
    * @param target The target integer sum.
    * @return The sum of the three integers closest to the target.
    */
    int threeSumClosest(vector<int>& arr, int target) {
        // 1. Sort the array
        sort(arr.begin(), arr.end());
        
        int n = arr.size();
        // Initialize 'best' sum with the sum of the first three elements
        int best = arr[0] + arr[1] + arr[2]; 

        for (int i = 0; i < n - 2; ++i) {
            // Optimization: Skip duplicates for the fixed pointer 'i'
            if (i > 0 && arr[i] == arr[i - 1]) {
                continue;
            }

            int left = i + 1, right = n - 1;

            while (left < right) {
                int sum = arr[i] + arr[left] + arr[right];

                // 2. Update closest sum
                if (abs(target - sum) < abs(target - best) || 
                (abs(target - sum) == abs(target - best) && best < sum)) {
                    best = sum;
                }
                // Handle tie-breaker: if two sums have the same difference, 
                // returning the one with the larger value.
                
                // 3. Move pointers based on sum comparison
                if (sum < target) {
                    // Current sum is too small, increase 'left' pointer
                    ++left;
                } else if (sum > target) {
                    // Current sum is too large, decrease 'right' pointer
                    --right;
                } else {
                    // Exact match found! This is the closest possible sum.
                    return sum; 
                }
            }
        }

        return best;
    }

};

int main() {
    Solution sol;
    
    // Test Case 1
    vector<int> arr1 = {-1, 2, 1, -4};
    int target1 = 1;
    int res1 = sol.threeSumClosest(arr1, target1);
    cout << "Array: {-1, 2, 1, -4}, Target: 1. Closest sum: " << res1 << " (Expected: 2)" << endl;
    
    // Test Case 2
    vector<int> arr2 = {0, 0, 0};
    int target2 = 1;
    int res2 = sol.threeSumClosest(arr2, target2);
    cout << "Array: {0, 0, 0}, Target: 1. Closest sum: " << res2 << " (Expected: 0)" << endl;
    
    // Test Case 3
    vector<int> arr3 = {1, 1, -1, -1, 3};
    int target3 = 3;
    int res3 = sol.threeSumClosest(arr3, target3);
    cout << "Array: {1, 1, -1, -1, 3}, Target: 3. Closest sum: " << res3 << " (Expected: 3)" << endl;

    // Test Case 4 (No exact match, difference is 1)
    vector<int> arr4 = {4, 0, 5, -5, 3, 3, 0, -4, -5};
    int target4 = -2;
    int res4 = sol.threeSumClosest(arr4, target4);
    cout << "Array: {4, 0, 5, -5, 3, 3, 0, -4, -5}, Target: -2. Closest sum: " << res4 << " (Expected: -2 or -3, depends on implementation/tie-breaker logic, but -2 is achievable: -5 + 0 + 3)" << endl;


    return 0;
}