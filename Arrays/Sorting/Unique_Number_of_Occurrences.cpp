/*
File: Unique_Number_of_Occurrences.cpp
Date: 2025-11-25 09:02

Problem: Unique Number of Occurrences

Link: https://www.geeksforgeeks.org/problems/unique-frequencies-of-not/1

Problem Statement:
Given an array of integers, determine if the number of occurrences of each value in the array is unique. That is, no two distinct values should have the same frequency (count).

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Sort the array. Iterate through the sorted array to count frequencies. Store the counts in a list. Sort the list of counts and check for duplicates.
- Time complexity: O(N log N) (due to sorting twice)
- Space complexity: O(N) (to store counts)
- Limitations: Sorting introduces unnecessary logarithmic complexity.

Current/Optimized Approachs
- Idea: Use hashing to count the frequency of each element in O(N) time, and then use a second hash structure (a set) to ensure all calculated frequencies are unique, also in O(N) time.
- Approach: **Two Hash Maps (Frequency Map and Uniqueness Set)**
- Algorithm:
  1. **Step 1: Count Frequencies.** Iterate through the input array `arr`. Use an `unordered_map<int, int>` (`freq`) to store element -> count mappings. This takes O(N) time.
  2. **Step 2: Check Uniqueness.** Iterate through the values (frequencies) in the `freq` map.
  3. Use an `unordered_set<int>` (`st`) to store the frequencies encountered so far.
  4. For each frequency `f`: if `f` is already present in `st`, return `false` immediately (duplicate frequency found). Otherwise, insert `f` into `st`.
  5. If the loop completes without finding duplicates, return `true`.
- Time complexity: **O(N)** (where N is the number of elements in the array, due to constant-time average lookups/insertions in the hash maps).
- Space complexity: O(D + F) where D is the number of distinct elements (for the map) and F is the number of distinct frequencies (for the set). In the worst case, this is O(N).

💡 Key Pattern:
- **Frequency Hashing and Set-based Uniqueness Check:** A standard two-step technique for problems involving counts and uniqueness constraints.

ℹ️ Keywords:
- Hashing, Unordered Map, Unordered Set, Frequency Counting, Uniqueness Check, O(N).

🗒️ Notes
- The provided code correctly uses `unordered_map` and `unordered_set` for optimal average-case performance.
- The `reserve(n)` calls are a useful optimization hint, though the actual capacity needed for `freq` is the number of distinct elements, and for `st` is the number of distinct frequencies.
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution
{
public:
    /**
     * @brief Checks if the number of occurrences of each value in the array is unique.
     * @param n The size of the array.
     * @param arr The input array of integers.
     * @return True if all frequencies are unique, false otherwise.
     */
    bool isFrequencyUnique(int n, int arr[])
    {
        // Step 1: Count frequencies of each element
        unordered_map<int, int> freq;
        freq.reserve(n); // Optimization hint

        for (int i = 0; i < n; ++i)
        {
            freq[arr[i]]++;
        }

        // Step 2: Check if all frequencies are unique
        unordered_set<int> st;
        st.reserve(freq.size()); // Optimization hint: reserve space for number of distinct elements

        for (auto &p : freq)
        {
            int f = p.second; // f is the count (frequency) of the element

            // If the frequency 'f' is already in the set, it means this frequency
            // has appeared for a different element, so frequencies are not unique.
            if (st.count(f))
            {
                return false;
            }

            // Record this frequency
            st.insert(f);
        }

        // If the loop finishes, all frequencies were unique.
        return true;
    }
};

int main()
{
    Solution sol;

    // Test Case 1: Unique frequencies (1: 3 times, 2: 2 times, 3: 1 time)
    int arr1[] = {1, 2, 2, 1, 1, 3};
    int n1 = 6;
    bool res1 = sol.isFrequencyUnique(n1, arr1);
    cout << "Array: {1, 2, 2, 1, 1, 3}, Result: " << (res1 ? "True" : "False") << " (Expected: True)" << endl;

    // Test Case 2: Non-unique frequencies (1: 2 times, 2: 2 times)
    int arr2[] = {1, 2, 2, 1};
    int n2 = 4;
    bool res2 = sol.isFrequencyUnique(n2, arr2);
    cout << "Array: {1, 2, 2, 1}, Result: " << (res2 ? "True" : "False") << " (Expected: False)" << endl;

    // Test Case 3: Empty array (vacuously true)
    int arr3[] = {};
    int n3 = 0;
    bool res3 = sol.isFrequencyUnique(n3, arr3);
    cout << "Array: {}, Result: " << (res3 ? "True" : "False") << " (Expected: True)" << endl;

    // Test Case 4: Complex example (1: 1, 2: 2, 3: 3)
    int arr4[] = {1, 2, 2, 3, 3, 3};
    int n4 = 6;
    bool res4 = sol.isFrequencyUnique(n4, arr4);
    cout << "Array: {1, 2, 2, 3, 3, 3}, Result: " << (res4 ? "True" : "False") << " (Expected: True)" << endl;

    return 0;
}