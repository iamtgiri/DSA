/*
File: Successful_Pairs_of_Spells_and_Potions.cpp
Date: 2025-10-26 00:13

Problem: Successful Pairs of Spells and Potions
Link: https://leetcode.com/problems/successful-pairs-of-spells-and-potions/description/

Problem Statement:
Given a list of spells and a list of potions, and a success threshold, find
the number of successful pairs for each spell. A pair (spell[i], potion[j]) is
successful if spell[i] * potion[j] >= success.

-------------------------------------------------
❌ Brute Force
- Idea: For every spell, iterate through the entire list of potions and check
  the success condition (spell * potion >= success).
- Time complexity: O(N * M), where N is the number of spells and M is the
  number of potions.
- Space complexity: O(N) for storing the result array.
- Limitations: Time Limit Exceeded (TLE) for large inputs due to quadratic time.

✅ Optimized Approachs
- Idea: For a fixed spell $S$, we need potions $P \ge \lceil success / S \rceil$.
  By sorting the potions, we can use binary search to quickly find the count
  of all potions that meet this minimum requirement.
- Approach: Sorting and Binary Search.
- Algorithm:
    1. **Sort Potions:** Sort the `potions` array in ascending order.
    2. **Iterate Spells:** For each spell $S$ in `spells`:
        a. **Calculate Minimum Potion:** Determine the minimum required potion
           strength $P_{min} = \lceil success / S \rceil$. This is calculated
           using integer division as `(success + S - 1) / S`.
        b. **Binary Search:** Use `std::lower_bound` on the sorted `potions`
           array to find the index `idx` of the first potion $P \ge P_{min}$.
        c. **Count Pairs:** The number of successful pairs is $M - idx$
           (the number of elements from `idx` to the end).
    3. Return the result vector.
- Time complexity: O(M log M + N log M). O(M log M) for sorting, O(N log M)
  for N binary searches.
- Space complexity: O(N) for the result vector.

💡 Key Pattern:
- **Monotonicity + Binary Search:** When a check (like the success condition)
  is monotonic (stronger potions always satisfy the condition), sorting enables
  the use of binary search to count suitable elements efficiently.

ℹ️ Keywords:
- Binary Search, Sorting, Ceiling Division, Two Pointers (implicitly via binary search).

🗒️ Notes
- Using the integer ceiling trick `(a + b - 1) / b` is important to avoid
  floating-point calculations and maintain precision for the large `success` value.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Calculates the number of successful pairs for each spell.
     * @param spells The strengths of the spells.
     * @param potions The strengths of the potions.
     * @param success The minimum required product.
     * @return A vector where result[i] is the number of successful pairs for spells[i].
     */
    vector<int> successfulPairs(vector<int> &spells, vector<int> &potions, long long success)
    {
        // Step 1: Sort the potions array. O(M log M)
        sort(potions.begin(), potions.end());

        int n = spells.size();
        int m = potions.size();
        vector<int> result(n);

        // Step 2: Iterate through each spell. O(N * log M)
        for (int i = 0; i < n; ++i)
        {
            long long spell = spells[i];

            // Step 2a: Calculate the minimum required potion strength (P_min).
            // P_min = ceil(success / spell). Using integer arithmetic ceiling:
            long long minPotion = (success + spell - 1) / spell;

            // Step 2b: Find the first potion >= minPotion using binary search.
            auto it = lower_bound(potions.begin(), potions.end(), minPotion);
            int idx = it - potions.begin();

            // Step 2c: The count is the number of elements from 'idx' to the end.
            result[i] = m - idx;
        }

        return result;
    }
};

// Helper function to print a vector
template <typename T>
void printVector(const vector<T> &vec)
{
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        cout << vec[i];
        if (i < vec.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << "]";
}

int main()
{
    Solution sol;

    cout << "--- Successful Pairs of Spells and Potions ---\n";

    // Test Case 1: Example 1 from LeetCode
    // success = 7
    // spell=3: min_potion=ceil(7/3)=3. Potions >= 3: [3, 4, 5]. Count: 3
    // spell=1: min_potion=ceil(7/1)=7. Potions >= 7: []. Count: 0
    // spell=2: min_potion=ceil(7/2)=4. Potions >= 4: [4, 5]. Count: 2
    vector<int> spells1 = {5, 1, 3};
    vector<int> potions1 = {1, 2, 3, 4, 5};
    long long success1 = 7;
    vector<int> result1 = sol.successfulPairs(spells1, potions1, success1);
    cout << "Test 1 | Spells: ";
    printVector(spells1);
    cout << ", Potions: ";
    printVector(potions1);
    cout << ", Success: " << success1 << "\n";
    cout << "Result: ";
    printVector(result1);
    cout << " (Expected: [4, 0, 3])\n"; // Note: Output is [4, 0, 3] if spells are {5, 1, 3}
    cout << "--------------------------------\n";

    // Test Case 2: Example 2 from LeetCode
    // success = 25
    // spell=8: min_potion=ceil(25/8)=4. Potions >= 4: [4, 5]. Count: 2
    // spell=5: min_potion=ceil(25/5)=5. Potions >= 5: [5]. Count: 1
    vector<int> spells2 = {8, 5};
    vector<int> potions2 = {1, 2, 3, 4, 5};
    long long success2 = 25;
    vector<int> result2 = sol.successfulPairs(spells2, potions2, success2);
    cout << "Test 2 | Spells: ";
    printVector(spells2);
    cout << ", Potions: ";
    printVector(potions2);
    cout << ", Success: " << success2 << "\n";
    cout << "Result: ";
    printVector(result2);
    cout << " (Expected: [2, 1])\n";
    cout << "--------------------------------\n";

    // Test Case 3: Edge case (large numbers, zero count)
    // success = 100
    // spell=1: min_potion=100. Potions >= 100: []. Count: 0
    vector<int> spells3 = {1, 50, 100};
    vector<int> potions3 = {1, 2, 99};
    long long success3 = 100;
    vector<int> result3 = sol.successfulPairs(spells3, potions3, success3);
    cout << "Test 3 | Spells: ";
    printVector(spells3);
    cout << ", Potions: ";
    printVector(potions3);
    cout << ", Success: " << success3 << "\n";
    cout << "Result: ";
    printVector(result3);
    cout << " (Expected: [0, 1, 1])\n";
    cout << "--------------------------------\n";

    return 0;
}
