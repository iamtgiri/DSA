/*
File: number_that_appears_odd_number_of_times.cpp
Date: 2025-09-24 23:13

Problem: Find the number that appears odd number of times
Link: https://leetcode.com/problems/single-number/description/

Problem Statement:
Given a non-empty array of integers `nums`, every element appears twice except
for one. Find that single one.

-------------------------------------------------
❌ Brute Force
- Idea: Use a hash map to count the frequency of each number. Then, find the
  number with a count of 1.
- Time complexity: O(N)
- Space complexity: O(N)
- Limitations: Uses extra space, which is against a common constraint for this
  problem.

✅ Optimized Approach
- Idea: The bitwise XOR operator has the property that `x \oplus x = 0` and
  `x \oplus 0 = x`. If we XOR all numbers in the array, the duplicates will
  cancel each other out, leaving only the single number.
- Approach: A single pass through the array, using bitwise XOR.
- Algorithm:
    1. Initialize a variable `ans` to 0.
    2. Iterate through each number `num` in the `nums` array.
    3. Update `ans = ans \oplus num`.
    4. Return `ans`.
- Time complexity: O(N)
- Space complexity: O(1)

💡 Key Pattern:
- **Bitwise XOR for Uniqueness**: XOR is a perfect tool for finding a single
  unique element in a list of duplicates, as identical numbers will cancel
  each other out.

ℹ️ Keywords:
- Bitwise XOR, Bit Manipulation, Single Number, Constant Space

🗒️ Notes
- The problem constraints guarantee a single unique number, making this
  approach foolproof.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Finds the number that appears only once in an array where all
     * other numbers appear twice.
     * @param nums The input array of integers.
     * @return The single number.
     */
    int singleNumber(vector<int> &nums)
    {
        int ans = 0;
        for (int num : nums)
        {
            ans ^= num;
        }
        return ans;
    }
};

int main()
{
    Solution sol;

    // Example 1:
    vector<int> nums1 = {2, 2, 1};
    cout << "Single number in {2, 2, 1} is: " << sol.singleNumber(nums1) << endl;
    // Expected: 1

    // Example 2:
    vector<int> nums2 = {4, 1, 2, 1, 2};
    cout << "Single number in {4, 1, 2, 1, 2} is: " << sol.singleNumber(nums2) << endl;
    // Expected: 4

    return 0;
}