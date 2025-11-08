/*
File: Maximum_Sum_of_Distinct_Subarrays_With_Length_K.cpp
Date: 2025-11-08 16:22

Problem: Maximum Sum of Distinct Subarrays With Length K
Link: https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/description/

Problem Statement:
Given an integer array nums and an integer k, return the maximum subarray sum
of all the subarrays of length k that contain distinct elements. If no such
subarray exists, return 0.

-------------------------------------------------
Brute Force
- Idea: Iterate through all possible contiguous subarrays of length K. For each
  subarray, check if all elements are distinct and calculate its sum.
- Time complexity: O(N * K). We iterate N-K+1 times for the start of the subarray,
  and checking distinctness takes O(K) time using a hash set.
- Space complexity: O(K) for the temporary hash set used for checking distinctness.
- Limitations: Time Limit Exceeded (TLE) for large N.

Optimized Approachs
- Idea: Use the Fixed-Size Sliding Window technique to check the distinctness
  constraint and update the sum in O(1) time per step.
- Approach: Sliding Window + Hash Map
  - The window size is fixed at K.
  - We use an unordered_map (freq) to track the count of each element within the
    current window. The size of the map (freq.size()) gives us the number of distinct
    elements in the window.
- Algorithm:
  1. Initialize currSum = 0 and maxSum = 0. Initialize an empty hash map (freq).
  2. Iterate through the array (i) from 0 to n-1:
     a. Add nums[i] to currSum and increment its count in freq.
     b. If the window has grown past size K (i >= K):
        i. Subtract nums[i - K] from currSum.
        ii. Decrement the count of nums[i - K] in freq.
        iii. If the count reaches 0, remove the element from the map (freq.erase).
     c. Check the condition: If the window is exactly size K (i >= K - 1) AND
        the number of distinct elements equals K (freq.size() == K), update
        maxSum = max(maxSum, currSum).
- Time complexity: O(N). Each element is processed in O(1) average time.
- Space complexity: O(K). The hash map stores at most K distinct elements.

Key Pattern:
- Sliding Window (Fixed Size): Used to maintain a subarray of fixed length K.
- Hash Map for Distinctness: Used to track frequencies; the size of the map
  directly indicates the number of distinct elements.

Keywords:
- Sliding Window, Hash Map, Distinct Elements, Subarray Sum, Fixed Window.

Notes
- Careful handling of long long for currSum and maxSum is required as the sum
  can exceed the capacity of a standard 32-bit integer.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Finds the maximum sum of a distinct subarray of length k using a sliding window.
     * @param nums The input array.
     * @param k The required length of the subarray.
     * @return The maximum sum found.
     */
    long long maximumSubarraySum(vector<int> &nums, int k)
    {
        // Tracks frequency of elements in the current window.
        unordered_map<int, int> freq;
        // Current window sum and maximum sum found so far.
        long long currSum = 0, maxSum = 0;
        int n = nums.size();

        for (int i = 0; i < n; i++)
        {
            // SLIDE RIGHT: Add the current element nums[i]
            currSum += nums[i];
            freq[nums[i]]++;

            // SLIDE LEFT: Remove the element that falls out of the window
            if (i >= k)
            {
                // Element leaving the window is nums[i - k]
                currSum -= nums[i - k];
                freq[nums[i - k]]--;

                // Remove the key from the map if its count drops to zero
                if (freq[nums[i - k]] == 0)
                    freq.erase(nums[i - k]);
            }

            // CHECK CONDITION: Window is size k (i >= k - 1) AND all elements are distinct (map size is k)
            if (i >= k - 1 && (int)freq.size() == k)
            {
                maxSum = max(maxSum, currSum);
            }
        }
        return maxSum;
    }
};

int main()
{
    Solution sol;

    // Test Case 1: Standard case (Expected: 15)
    vector<int> nums1 = {1, 5, 4, 2, 9, 9, 9};
    int k1 = 3;
    // Subarrays of size 3:
    // {1, 5, 4} -> Distinct, Sum 10
    // {5, 4, 2} -> Distinct, Sum 11
    // {4, 2, 9} -> Distinct, Sum 15 (Max)
    // {2, 9, 9} -> Not Distinct
    // {9, 9, 9} -> Not Distinct
    cout << "Test 1 ({1, 5, 4, 2, 9, 9, 9}, k=3): Expected 15, Got " << sol.maximumSubarraySum(nums1, k1) << endl;

    // Test Case 2: No distinct subarray (Expected: 0)
    vector<int> nums2 = {4, 4, 4};
    int k2 = 3;
    cout << "Test 2 ({4, 4, 4}, k=3): Expected 0, Got " << sol.maximumSubarraySum(nums2, k2) << endl;

    // Test Case 3: Mixed (Expected: 9)
    vector<int> nums3 = {1, 3, 2, 1, 4, 1, 3, 2, 1};
    int k3 = 3;
    // {1, 3, 2} -> 6
    // {3, 2, 1} -> 6
    // {2, 1, 4} -> 7
    // {1, 4, 1} -> Not Distinct
    // {4, 1, 3} -> 8
    // {1, 3, 2} -> 6
    // {3, 2, 1} -> 6
    // Corrected trace for {1, 3, 2, 1, 4, 1, 3, 2, 1}, k=4. Let's use k=4 for a better test.

    // Test Case 4: Larger K (Expected: 9)
    vector<int> nums4 = {1, 3, 2, 1, 4};
    int k4 = 4;
    // {1, 3, 2, 1} -> Not Distinct
    // {3, 2, 1, 4} -> Distinct, Sum 10
    // Correcting Test 3 for K=3: Max sum is {4, 1, 3} -> 8.
    vector<int> nums5 = {1, 3, 2, 1, 4, 1, 3, 2, 1};
    int k5 = 3;
    cout << "Test 3 ({1, 3, 2, 1, 4, 1, 3, 2, 1}, k=3): Expected 8, Got " << sol.maximumSubarraySum(nums5, k5) << endl;

    // Test Case 4: Long input with large values (Requires long long) (Expected: 18)
    vector<int> nums6 = {7, 7, 7, 7, 7, 7, 7, 10, 8, 0};
    int k6 = 3;
    // {7, 7, 7} -> Not distinct
    // {7, 7, 10} -> Not distinct
    // {7, 10, 8} -> Distinct, Sum 25 (Max)
    // {10, 8, 0} -> Distinct, Sum 18
    cout << "Test 4 ({7, 7, 7, 7, 7, 7, 7, 10, 8, 0}, k=3): Expected 25, Got " << sol.maximumSubarraySum(nums6, k6) << endl;

    return 0;
}