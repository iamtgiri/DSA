/*
File: binarySubarrayWithSum.cpp
Date: 2025-09-09 17:51

Problem: Binary Subarrays With Sum
Link: (add link if available)

Problem Statement:
    Given a binary array nums[] and an integer goal,
    return the number of non-empty subarrays with sum = goal.
    A subarray is a contiguous part of the array.

-------------------------------------------------
❌ Brute Force
- Idea: Enumerate all possible subarrays and check their sum.
- Time complexity: O(N^2)
- Space complexity: O(1)
- Limitation: Too slow for large N.

✅ Optimized Approach (Sliding Window Trick)
- Idea:
    1. Define a helper `atMost(nums, K)` = number of subarrays with sum ≤ K.
    2. Then the answer is `atMost(nums, goal) - atMost(nums, goal - 1)`.
    3. Use a sliding window to maintain a running sum and count valid subarrays.
- Time complexity: O(N)
- Space complexity: O(1)

💡 Key Pattern:
- Sliding Window (only works efficiently because array is binary: 0/1)

Keywords:
- Sliding window, prefix sum, subarray counting

🗒️ Notes:
- Learned that the "at most" trick only works on non-negative arrays (like binary arrays).
- For general arrays, prefix-sum + hashmap is required.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int binarySubarrayWithSum(const vector<int> &arr, int target)
    {
        return atMost(arr, target) - atMost(arr, target - 1);
    }
    // Brute force checker (works for any array)
    int bruteForce(const vector<int> &arr, int target)
    {
        int n = arr.size();
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            int sum = 0;
            for (int j = i; j < n; j++)
            {
                sum += arr[j];
                if (sum == target)
                    count++;
            }
        }
        return count;
    }

private:
    int atMost(const vector<int> &arr, int K)
    {
        if (K < 0)
            return 0; // edge case: no subarray can have sum < 0

        int left = 0, sum = 0, count = 0;
        int n = arr.size();

        for (int right = 0; right < n; ++right)
        {
            sum += arr[right];

            while (left <= right && sum > K)
            {
                sum -= arr[left];
                ++left;
            }

            count += (right - left + 1);
        }

        return count;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, goal;
        cin >> n >> goal;

        vector<int> arr(n);
        for (int i = 0; i < n; i++) cin >> arr[i];

        Solution sol;

        int optimized = sol.binarySubarrayWithSum(arr, goal);
        int brute = sol.bruteForce(arr, goal);

        cout << "Optimized: " << optimized << ", Brute: " << brute << "\n";
    }

    return 0;
}
