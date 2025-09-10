/*
File: minSwapOne.cpp
Date: 2025-09-09 18:21

Problem: Minimum Swaps to Group All 1’s Together
Link: URL
Problem Statement:
    A swap is defined as taking two distinct positions in an array and swapping the values in them.
    Given a binary array nums[], find the minimum number of swaps required to group
    all 1’s present in the array together at any location.

Example:
    Input: nums = [0, 1, 0, 1, 1, 0, 0]
    Output: 1
Explanation:
    Total ones = 3 → Window size = 3.
    Best window has 2 ones → Needs 1 swap to bring the last one inside.

-------------------------------------------------
❌ Brute Force
- Idea: Try placing all ones together at every possible location
  and calculate swaps needed.
- Time complexity: O(N^2)
- Space complexity: O(1)
- Limitations: Too slow for large N.

✅ Optimized Approach
- Idea:
    1. Count total number of ones → window size.
    2. Use sliding window of this size to check how many zeros inside.
    3. Minimum zeros in any such window = minimum swaps needed.
- Time complexity: O(N)
- Space complexity: O(1)

💡 Key Pattern:
- Sliding Window (fixed-size window)

Keywords:
- Sliding window, binary array, minimum swaps

🗒️ Notes
- Learned how grouping problems can often be solved with
  sliding window technique.
- Similar problems: Minimum swaps to group K elements, max consecutive ones.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minSwap(const vector<int> &arr) {
        int n = arr.size();
        int totalOne = accumulate(arr.begin(), arr.end(), 0);

        if (totalOne == 0 || totalOne == n) return 0; // already grouped

        // Count zeros in the first window of size totalOne
        int countZero = 0;
        for (int i = 0; i < totalOne; ++i) {
            if (arr[i] == 0) ++countZero;
        }

        int minSwapNeed = countZero;

        // Sliding window (circular to allow grouping at array edges)
        for (int i = totalOne; i < n + totalOne; ++i) {
            if (arr[i % n] == 0) ++countZero; // include new element
            if (arr[(i - totalOne) % n] == 0) --countZero; // remove old element
            minSwapNeed = min(minSwapNeed, countZero);
        }

        return minSwapNeed;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) cin >> arr[i];
        cout << sol.minSwap(arr) << "\n";
    }
    return 0;
}
