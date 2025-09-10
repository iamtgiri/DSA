/*
File: stablePartition.cpp
Date: 2025-09-09 10:58
-----------------------------------------------------------------------------------------
Problem: Stable Partition
Link: (add if available)

Problem Statement:
    Given an array arr[] of integers, rearrange them such that all negative integers
    appear before all the positive integers. The relative order of both negative and
    positive numbers must be preserved.

Example:
    Input : arr[] = [12, 11, -13, -5, 6, -7, 5, -3, -6]
    Output: [-13, -5, -7, -3, -6, 12, 11, 6, 5]

Explanation:
    All negative elements [-13, -5, -7, -3, -6] are moved before positives [12, 11, 6, 5]
    while keeping the original order intact.

-----------------------------------------------------------------------------------------
❌ Brute Force 1
- Idea: Copy negatives into one array, positives into another, then concatenate.
- Time complexity: O(N)
- Space complexity: O(N)
- Limitation: Stable but not in-place.

❌ Brute Force 2
- Idea: Use two-pointer partitioning (like quicksort partition).
- Time complexity: O(N)
- Space complexity: O(1)
- Limitation: In-place but not stable.

✅ Optimized Approach (Stable Partition using Divide & Conquer + Rotation)
- Idea:
    1. Recursively partition left and right halves.
    2. After recursion, each half looks like [negatives | positives].
    3. Rotate the middle segment (L_Positive -> R_Negative -> L_Positive + R_Negative)
       so right-negatives come before left-positives.
    4. Rotation is done with three reversals.
- Time complexity: O(N log N)
- Space complexity: O(1) auxiliary (O(log N) recursion stack)

💡 Key Pattern:
- Modified merge (divide & conquer + rotation)

ℹ️ Key words: array, stable partition, merge, rotation

🗒️ Notes:
- Learned that stability requires extra work.
- Simple partition cannot guarantee stable order.
- Rotation trick (3 reversals) is powerful for rearranging in-place.

-----------------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    void stablePartition(vector<int> &arr, int left, int right)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;

            // Recurse on both halves
            stablePartition(arr, left, mid);
            stablePartition(arr, mid + 1, right);

            // Merge step: rotate middle part
            merge(arr, left, mid, right);
        }
    }

private:
    void merge(vector<int> &arr, int left, int mid, int right)
    {
        // Find first positive in left half
        int L_positive = left;
        while (L_positive <= mid && arr[L_positive] < 0)
            ++L_positive;

        // Find first positive in right half (i.e. end of right-negatives)
        int R_positive = mid + 1;
        while (R_positive <= right && arr[R_positive] < 0)
            ++R_positive;

        // Rotate [L_positive .. R_positive-1]:
        // [L_positives | R_negatives] -> [R_negatives | L_positives]
        reverse(arr.begin() + L_positive, arr.begin() + mid + 1);    // reverse L_positives
        reverse(arr.begin() + mid + 1, arr.begin() + R_positive);    // reverse R_negatives
        reverse(arr.begin() + L_positive, arr.begin() + R_positive); // reverse combined block
    }
};

int main()
{
    Solution sol;
    vector<int> arr = {12, 11, -13, -5, 6, -7, 5, -3, -6};

    sol.stablePartition(arr, 0, arr.size() - 1);

    for (int x : arr)
        cout << x << " ";
    cout << "\n";

    return 0;
}
