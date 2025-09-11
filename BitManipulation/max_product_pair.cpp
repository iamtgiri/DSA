/*
File: 4-max_product_pair.cpp
Date: 2025-09-11

Problem: Maximum Product Pair for Given C
Link: URL
Problem Statement:
    Given an integer C, find two integers A and B such that:
        - (A ^ B) = C  (XOR is equal to C)
        - The product A * B is maximized.
    Return the pair (A, B).

Example:
    Input:
        C = 10
    Output:
        A = 7, B = 13
    Explanation:
        - 7 ^ 13 = 10
        - Product = 7 * 13 = 91 (maximum possible)

-------------------------------------------------
❌ Brute Force
- Idea: Iterate over all possible pairs (A, B) such that A ^ B = C,
        compute product, and take maximum.
- Time complexity: O(C)
- Space complexity: O(1)
- Limitations: Not feasible for large C.

✅ Optimized Approach
- Idea:
    1. Find the binary length `m` of C (highest set bit).
    2. Let A = (2^(m-1)) - 1 → all 1s just below highest bit.
    3. Compute B = C ^ A.
    4. Return (A, B).
- Reason: This ensures A and B differ at the MSB of C, maximizing product.
- Time complexity: O(log C)
- Space complexity: O(1)

💡 Key Pattern:
- Bit Manipulation
- XOR properties
- Greedy construction of A

Keywords:
- XOR, Binary representation, Max product, Greedy

🗒️ Notes
- Learned: Always consider MSB manipulation for XOR problems.
- Similar problems: "Maximize XOR with given number", "Maximum AND pair".
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    pair<long long, long long> maxProductPair(long long C) {
        if (C == 0) return {1, 1};

        // find binary length of C
        int m = 0;
        long long temp = C;
        while (temp > 0) {
            m++;
            temp >>= 1;
        }

        long long A = (1LL << (m - 1)) - 1; // all ones below MSB
        long long B = C ^ A;               // ensures A ^ B = C

        return {A, B};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long C;
    cout << "Enter C: ";
    cin >> C;

    Solution sol;
    auto ans = sol.maxProductPair(C);

    cout << ans.first << " " << ans.second << "\n";
    return 0;
}
