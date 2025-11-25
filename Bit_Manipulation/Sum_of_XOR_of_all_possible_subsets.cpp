/*
File: Sum_of_XOR_of_all_possible_subsets.cpp
Date: 2025-11-25 10:21

Problem: Sum of XOR of all possible subsets
Link: https://www.geeksforgeeks.org/problems/sum-of-xor-of-all-possible-subsets/1

Problem Statement:
Given an array of integers `arr`, find the sum of the XOR total of all its possible subsets. The XOR total of an empty subset is considered 0.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Generate all $2^N$ possible subsets using recursion or iteration (e.g., using bitmasks from 0 to $2^N - 1$). For each subset, calculate the XOR sum of its elements. Finally, sum up all these individual XOR sums.
- Time complexity: O(N * 2^N) (2^N subsets, and O(N) to compute the XOR sum of each subset in the worst case).
- Space complexity: O(1) auxiliary space (excluding recursion stack or result storage).
- Limitations: Exponential time complexity, impractical for N > 20.

Current/Optimized Approachs
- Idea: Instead of summing up subset XORs, calculate the total contribution of each bit position ($j$) to the final sum.
- Approach: **Bitwise Contribution Analysis**
- Algorithm:
  1. **Identify Relevant Bits:** Calculate the bitwise OR (`OR`) of all elements in the array. Any bit $j$ that is NOT set in `OR` can never be set in the XOR sum of *any* subset, so its contribution is 0.
  2. **Count Subsets for Set Bits:** Focus on a bit $j$ that *is* set in `OR`.
     * Let $A'$ be the sub-array containing only elements of $A$ where bit $j$ is set. $|A'| \ge 1$.
     * A subset's XOR sum has bit $j$ set if and only if an odd number of elements from $A'$ are included in the subset.
     * **Key Insight:** For an array of size $N$, if bit $j$ is present in at least one element, then exactly $2^{N-1}$ subsets will have bit $j$ set in their total XOR sum. (This is based on combinatorics: for the $N-1$ elements not including the first element where bit $j$ is set, there are $2^{N-1}$ ways to combine them; exactly half of these combinations will result in an odd count of the $j$-th bit).
  3. **Calculate Total Sum:** The total sum is the sum of the contributions of each bit $j$:
     $$\text{Total Sum} = \sum_{j=0}^{30} (\text{Contribution of bit } j)$$
     $$\text{Contribution of bit } j = 2^j \times (\text{Number of subsets where bit } j \text{ is set})$$
     Since the number of subsets where a relevant bit $j$ is set is always $2^{N-1}$:
     $$\text{Total Sum} = \sum_{\text{bit } j \text{ in OR}} (2^j \times 2^{N-1})$$
     $$\text{Total Sum} = 2^{N-1} \times \sum_{\text{bit } j \text{ in OR}} 2^j$$
     $$\text{Total Sum} = \text{OR} \times 2^{N-1}$$
- Time complexity: **O(N)** (Linear, dominated by calculating the bitwise OR of all elements).
- Space complexity: O(1).

💡 Key Pattern:
- **Bitwise Principle of Inclusion:** When summing up XOR totals, analyze the contribution of each bit position. If a bit can be formed (i.e., it is set in the overall OR), it contributes $2^{N-1}$ times its positional value ($2^j$) to the final sum.

ℹ️ Keywords:
- XOR Sum, Subsets, Bitwise OR, Combinatorics, Bit Manipulation, O(N) solution.

🗒️ Notes
- This problem is a classic example of reducing an exponential subset generation problem to a linear bitwise calculation.
- The constraint relies on the fact that the XOR total of subsets is commutative and associative.
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
     * @brief Calculates the sum of the XOR totals of all possible subsets of the array.
     * @param arr The input array of integers.
     * @return The total sum.
     */
    int subsetXORSum(vector<int> &arr)
    {
        int n = arr.size();
        
        // Handle n=0 edge case, though constraints usually prevent it.
        if (n == 0)
            return 0;

        // 1. Calculate the bitwise OR of all elements.
        // This is equivalent to finding the sum of all powers of 2 (2^j)
        // corresponding to bits that are set in at least one element.
        int total_OR = 0;
        for (int x : arr)
        {
            total_OR |= x;
        }

        // 2. The formula derived from bit contribution analysis is:
        // Total Sum = (Overall OR of array) * 2^(N - 1)
        // where 2^(N-1) is the number of times any relevant bit is set across all subsets.


        // 1 << (n - 1) computes 2^(n - 1)
        return total_OR * (1 << (n - 1));
    }
};

int main()
{
    Solution sol;

    // Test Case 1: arr = {1, 3}
    // Subsets: {}, {1}, {3}, {1, 3}
    // XORs: 0, 1, 3, (1^3)=2
    // Sum: 0 + 1 + 3 + 2 = 6
    vector<int> arr1 = {1, 3};
    int res1 = sol.subsetXORSum(arr1);
    // OR = 1 | 3 = 3. n=2. Result = 3 * 2^(2-1) = 3 * 2 = 6
    cout << "Arr: {1, 3}, Result: " << res1 << " (Expected: 6)" << endl;

    // Test Case 2: arr = {5, 1, 6}
    // OR = 5 | 1 | 6 = 7. n=3. Result = 7 * 2^(3-1) = 7 * 4 = 28
    vector<int> arr2 = {5, 1, 6};
    int res2 = sol.subsetXORSum(arr2);
    cout << "Arr: {5, 1, 6}, Result: " << res2 << " (Expected: 28)" << endl;

    // Test Case 3: arr = {3, 4, 5}
    // OR = 3 | 4 | 5 = 7. n=3. Result = 7 * 4 = 28
    vector<int> arr3 = {3, 4, 5};
    int res3 = sol.subsetXORSum(arr3);
    cout << "Arr: {3, 4, 5}, Result: " << res3 << " (Expected: 28)" << endl;

    return 0;
}