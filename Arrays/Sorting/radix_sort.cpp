/*
File: 7-radix_sort.cpp
Date: 2025-09-11 21:00

Problem: Radix Sort Implementation (using Counting Sort as subroutine)
Link: URL
Problem Statement:
    Implement Radix Sort for non-negative integers using Counting Sort 
    as a stable subroutine for sorting by each digit place.

Example:
    Input:  [170, 45, 75, 90, 802, 24, 2, 66]
    Output: [2, 24, 45, 66, 75, 90, 170, 802]

-------------------------------------------------
❌ Brute Force
- Idea: Use simple comparison-based sorts like Bubble Sort or Selection Sort.
- Time complexity: O(N^2)
- Space complexity: O(1)
- Limitations: Too slow for large N.

✅ Optimized Approach (Radix Sort)
- Idea:
    - Sort numbers digit by digit (units, tens, hundreds…).
    - Use Counting Sort (stable) for each digit.
    - Continue until the maximum number’s highest digit is processed.
- Time complexity: O(N * d) where d = number of digits.
- Space complexity: O(N + k), k = range of digits (10 here).
- Works best when numbers are integers with limited digit length.

💡 Key Pattern:
- Stable sort on each digit.
- Counting sort as helper for digit-based sorting.

Keywords:
- Radix Sort, Counting Sort, Non-comparison sort, Linear time sorting

🗒️ Notes
- Only works efficiently for integers (non-negative).
- Counting Sort must be stable for Radix Sort to work correctly.
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Counting Sort for a specific digit (exp = 1 → units, 10 → tens, ...)
    void count_sort_digit(int arr[], int n, int exp) {
        vector<int> freq(10, 0); // digit frequencies
        vector<int> result(n);

        // count digit occurrences
        for (int i = 0; i < n; i++) {
            int digit = (arr[i] / exp) % 10;
            freq[digit]++;
        }

        // prefix sum for stable positions
        for (int i = 1; i < 10; i++) {
            freq[i] += freq[i - 1];
        }

        // build result array (stable: traverse backwards)
        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i] / exp) % 10;
            result[freq[digit] - 1] = arr[i];
            freq[digit]--;
        }

        // copy back
        for (int i = 0; i < n; i++) {
            arr[i] = result[i];
        }
    }

    // Radix Sort main function
    void radix_sort(int arr[], int n) {
        if (n == 0) return;

        // find maximum number to know digit count
        int maxe = *max_element(arr, arr + n);

        // apply counting sort for each digit place
        for (int exp = 1; maxe / exp > 0; exp *= 10) {
            count_sort_digit(arr, n, exp);
        }
    }
};

int main() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array:\n";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n";

    Solution sol;
    sol.radix_sort(arr, n);

    cout << "Sorted array:\n";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n";

    return 0;
}
