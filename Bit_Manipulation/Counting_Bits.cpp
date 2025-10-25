/*
File: Counting_Bits.cpp
Date: 2025-10-25 10:26

Problem: Counting Bits
Link: https://leetcode.com/problems/counting-bits/description/

Problem Statement:
Given an integer n, return an array ans of length n + 1 such that for every i (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.

-------------------------------------------------
❌ Brute Force
- Idea: For every number `i` from 1 to `n`, iterate through its binary representation (e.g., using a loop and bitwise AND with 1, followed by a right shift) to count the set bits.
- Time complexity: O(N log N). For N numbers, checking each takes O(log i) time.
- Space complexity: O(N) to store the result array.
- Limitations: Not linear time, which is usually required for optimization in competitive programming.

✅ Optimized Approachs
- Idea: Use Dynamic Programming (DP) combined with bit manipulation. The number of set bits in any integer `i` can be derived from the count of a smaller integer.
- Approach: Least Significant Bit (LSB) Dependency / Right Shift DP.
- Algorithm:
    1. Initialize a result array `result` of size `n + 1`. `result[0]` is 0.
    2. For any number `i > 0`, the number of set bits in `i` is equal to the number of set bits in `i / 2` (`i >> 1`) plus the value of its last bit (`i & 1`).
    3. Formula: `result[i] = result[i >> 1] + (i & 1)`.
- Time complexity: O(N). Each element is computed in O(1) time.
- Space complexity: O(N) for the result array.

💡 Key Pattern:
- **Bitwise DP:** Utilizing bit shift operations (`>>` and `& 1`) to reduce the problem to a previously solved subproblem, leading to an efficient linear-time DP solution.

ℹ️ Keywords:
- Bit Manipulation, Dynamic Programming, Hamming Weight, Popcount.

🗒️ Notes
- This DP approach cleverly avoids the cost of repeatedly counting bits from scratch. For example, `bits(10)` (binary `1010`) is equal to `bits(5)` (binary `101`) + 0. The number 5 is half of 10.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Counts the number of set bits (1s) in the binary representation of every number from 0 to n.
     * Uses a Dynamic Programming approach for O(N) complexity.
     * @param n The upper limit of the range [0, n].
     * @return A vector where the i-th element is the count of set bits in i.
     */
    vector<int> countBits(int n)
    {
        // Initialize DP array of size n + 1. result[0] is automatically 0.
        vector<int> result(n + 1);

        // Iterate from 1 up to n
        for (int i = 1; i <= n; ++i)
        {
            // DP Relation: result[i] = result[i >> 1] + (i & 1)
            // i >> 1: is i / 2. This removes the LSB. We rely on the result already calculated for i/2.
            // i & 1: is i % 2. This adds 1 if the LSB of i was 1, and 0 otherwise.
            result[i] = result[i >> 1] + (i & 1);
        }
        return result;
    }
};

// Helper function to print the vector for test verification
void printVector(const vector<int> &vec)
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
    cout << "]" << endl;
}

int main()
{
    Solution sol;

    cout << "--- Counting Bits (DP Solution) ---\n";

    // Test Case 1: n = 2
    // Input: n = 2
    // Expected: [0, 1, 1] (0->0, 1->1, 2->10)
    int n1 = 2;
    vector<int> result1 = sol.countBits(n1);
    cout << "N = " << n1 << "\n";
    cout << "Output: ";
    printVector(result1);
    cout << "--------------------------------\n";

    // Test Case 2: n = 5
    // Input: n = 5
    // Expected: [0, 1, 1, 2, 1, 2] (0, 1, 10, 11, 100, 101)
    int n2 = 5;
    vector<int> result2 = sol.countBits(n2);
    cout << "N = " << n2 << "\n";
    cout << "Output: ";
    printVector(result2);
    cout << "--------------------------------\n";

    // Test Case 3: n = 10
    // Input: n = 10
    int n3 = 10;
    vector<int> result3 = sol.countBits(n3);
    cout << "N = " << n3 << "\n";
    cout << "Output: ";
    printVector(result3);
    // Expected: [0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2]
    cout << "--------------------------------\n";

    return 0;
}
