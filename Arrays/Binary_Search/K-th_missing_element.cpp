/*
File: K-th_missing_element.cpp
Date: 2025-11-25 09:16

Problem: K-th missing element
Link: https://www.geeksforgeeks.org/problems/k-th-missing-element3635/1

Problem Statement:
Given a sorted array of distinct integers `arr` and an integer `k`, return the k-th missing integer in the sequence that starts from `arr[0]`. If there are fewer than k missing elements in the range of the array, return -1.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Iterate through the array. Maintain a count of missing elements between `arr[i]` and `arr[i+1]`. Stop when the cumulative count reaches `k`.
- Time complexity: O(N)
- Space complexity: O(1)
- Limitations: Not scalable for very large arrays, as we have to scan linearly.

Current/Optimized Approachs
- Idea: The number of missing elements before a given index `i` is deterministic and calculated by: `arr[i] - arr[0] - i`. This function is monotonic (non-decreasing) with `i`. We can use **Binary Search** to efficiently find the boundary where the count of missing elements crosses the threshold `k`.
- Approach: **Binary Search on the Count of Missing Numbers**
- Algorithm:
  1. Define a function `missing(i)`: `arr[i] - arr[0] - i` which calculates the count of missing numbers between `arr[0]` and `arr[i]`.
  2. Use binary search to find the smallest index `ans` such that `missing(ans) >= k`.
  3. The $k$-th missing element is located in the gap *before* `arr[ans]`, specifically after `arr[ans-1]`.
  4. The number of missing elements before `arr[ans-1]` is $M_{prev} = \text{missing}(ans-1)$.
  5. The required element is $k - M_{prev}$ positions after `arr[ans-1]`.
  6. **Result:** `arr[ans - 1] + (k - missing(ans - 1))`.
  7. Handle the edge case where $k$ is too large (i.e., `ans == n`).
- Time complexity: **O(log N)** (where N is the size of the array).
- Space complexity: O(1).

💡 Key Pattern:
- **Binary Search on Answer/Monotonic Function:** Applying binary search not directly on the element value, but on an index whose derived property (in this case, the count of missing numbers) is monotonic.

ℹ️ Keywords:
- Binary Search, Missing Number, Monotonic Function, Sorted Array.

🗒️ Notes
- The constraints in the problem link usually specify that $k$-th missing element should be within the range defined by the array. If the $k$-th element falls outside the range (i.e., the total missing count is less than $k$), the problem expects -1.
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution
{
public:
    /**
     * @brief Finds the K-th missing element in the sequence starting from arr[0].
     * @param arr The sorted input array.
     * @param k The desired missing element rank (e.g., k=3 means 3rd missing element).
     * @return The K-th missing element or -1 if it does not exist in the array's range.
     */
    int KthMissingElement(vector<int> &arr, int &k)
    {
        int n = arr.size();

        // Lambda function to calculate the number of missing elements
        // in the sequence starting from arr[0] up to and excluding arr[i].
        // The expected number of elements is arr[i] - arr[0] + 1.
        // The actual number of elements (including arr[i]) is i + 1.
        // Missing count = (arr[i] - arr[0]) - i
        auto missing = [&](int i)
        {
            return arr[i] - arr[0] - i;
        };

        // Standard binary search template to find the first index 'ans'
        // where missing(ans) >= k.
        int l = 0, r = n - 1, ans = n;

        while (l <= r)
        {
            int mid = l + (r - l) / 2;

            if (missing(mid) >= k)
            {
                // mid might be the answer, try to find an even smaller index
                ans = mid;
                r = mid - 1;
            }
            else
            {
                // Too few missing elements, search in the right half
                l = mid + 1;
            }
        }

        // Edge Case 1: If ans == n, it means even arr[n-1] did not yield
        // enough missing elements (missing(n-1) < k).
        if (ans == n)
        {
            return -1;
        }

        // Edge Case 2: The k-th missing element is before arr[0] (not allowed by problem context)
        // If ans is 0, it means missing(0) >= k, which is only true if k=0, which is unlikely.
        // Since we typically start counting missing *after* arr[0], we return -1 if ans == 0.
        if (ans == 0)
        {
            return -1;
        }

        // The k-th missing element is located between arr[ans-1] and arr[ans].
        // 1. Get the count of missing elements up to the previous index (arr[ans-1]).
        int missing_before_prev = missing(ans - 1);

        // 2. Calculate how many steps past arr[ans-1] we need to go.
        int steps_to_kth = k - missing_before_prev;

        // 3. The k-th missing element is arr[ans-1] + steps_to_kth.
        return arr[ans - 1] + steps_to_kth;
    }
};

int main()
{
    Solution sol;

    // Test Case 1: Standard case
    vector<int> arr1 = {2, 3, 5, 9};
    int k1 = 1; // 1st missing is 4
    int res1 = sol.KthMissingElement(arr1, k1);
    cout << "Arr: {2, 3, 5, 9}, k=" << k1 << ", Result: " << res1 << " (Expected: 4)" << endl;

    // Test Case 2: K is larger
    vector<int> arr2 = {4, 7, 9, 10};
    int k2 = 3; // Missing are 5, 6, 8. 3rd missing is 8.
    int res2 = sol.KthMissingElement(arr2, k2);
    cout << "Arr: {4, 7, 9, 10}, k=" << k2 << ", Result: " << res2 << " (Expected: 8)" << endl;

    // Test Case 3: K is too large (total missing is 5, k=6 is out of range)
    vector<int> arr3 = {10, 11, 12, 13, 14, 15};
    int k3 = 6; // Total missing is 0. Expected -1.
    int res3 = sol.KthMissingElement(arr3, k3);
    cout << "Arr: {10, 11, 12, 13, 14, 15}, k=" << k3 << ", Result: " << res3 << " (Expected: -1)" << endl;

    // Test Case 4: K is exactly the last missing element
    vector<int> arr4 = {2, 3, 5, 9};
    int k4 = 4; // Missing are 4, 6, 7, 8. 4th missing is 8.
    int res4 = sol.KthMissingElement(arr4, k4);
    cout << "Arr: {2, 3, 5, 9}, k=" << k4 << ", Result: " << res4 << " (Expected: 8)" << endl;

    return 0;
}