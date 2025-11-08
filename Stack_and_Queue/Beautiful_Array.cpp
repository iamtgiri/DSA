/*
File: Beautiful_Array.cpp
Date: 2025-11-08 17:16

Problem: Beautiful Array
Link: https://leetcode.com/problems/beautiful-array/description/

Problem Statement:
An array nums of size N is called "beautiful" if, for every i < j < k, the
condition 2 * nums[j] = nums[i] + nums[k] is never met. Given N, return any
beautiful array nums of size N that consists of the numbers 1 to N (inclusive).

-------------------------------------------------
Brute Force
- Idea: Generate all N! permutations of numbers from 1 to N. For each permutation,
  check the "beautiful array" condition (no arithmetic progression of length 3).
- Time complexity: O(N! * N*N*N).
- Space complexity: O(N) to store the array.
- Limitations: Infeasible for N > 10.

Optimized Approachs
- Idea: The condition 2 * B = A + C means A, B, C form an Arithmetic Progression (AP).
  We need an array without any 3-term AP. The key mathematical property is that
  if an array A is beautiful, then the array [2*A - 1] followed by [2*A] is also beautiful,
  provided elements are <= N. This is based on the fact that scaling and shifting
  preserves the AP property.
- Approach: Divide and Conquer / Recursive Construction (or Iterative equivalent).
- Algorithm:
  1. Base case: The array {1} is beautiful for N=1.
  2. Recursive step (Divide): To construct the array for N, split the problem
     into generating a beautiful array for the odd-part size (N+1)/2 and the
     even-part size N/2.
  3. Combine: Transform the odd-part result (x -> 2*x - 1) and the even-part result (x -> 2*x).
     Concatenate the odd-transformed elements first, followed by the even-transformed
     elements.
  4. The arrangement [ODD numbers] followed by [EVEN numbers] prevents mixed APs:
     - Odd + Even = Odd. This cannot equal 2 * B (which is always Even).
     - This guarantees that any 3-term AP must be all odd or all even, which is
       handled by the recursive call on the smaller, beautiful subarrays.
- Time complexity: O(N log N). The work at each level of recursion is O(N) due to
  array concatenation/copying.
- Space complexity: O(N log N) for the recursion stack and intermediate result arrays
  (in the recursive version). O(N) for the final result.

Key Pattern:
- Divide and Conquer: Solving a problem by splitting it into subproblems
  (Odd elements and Even elements) and combining the results.

Keywords:
- Beautiful Array, Arithmetic Progression, Divide and Conquer, Recursion.

Notes
- The iterative approach (beautifulArrayItr) implements the exact same mathematical
  construction (Odds first, then Evens) but avoids recursion, potentially saving
  stack space. Both are accepted solutions.
- The property that 2*B != A+C is equivalent to saying no three elements form an
  Arithmetic Progression (AP).
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Generates a beautiful array of size n using the recursive Divide and Conquer method.
     * @param n The required size of the array (elements 1 to n).
     * @return A beautiful array vector.
     */
    vector<int> beautifulArrayRec(int n)
    {
        return helper(n);
    }

    /**
     * @brief Generates a beautiful array of size n using the iterative construction method.
     * @param n The required size of the array (elements 1 to n).
     * @return A beautiful array vector.
     */
    vector<int> beautifulArrayItr(int n)
    {
        // Start with the base case: {1} is beautiful
        vector<int> res = {1};

        // Loop until the size is N
        while ((int)res.size() < n)
        {
            vector<int> tmp;

            // 1. Construct the Odd Part (2*x - 1)
            // Add all transformed elements (2*x - 1) that are <= n.
            for (int x : res)
                if (2 * x - 1 <= n)
                    tmp.push_back(2 * x - 1);

            // 2. Construct the Even Part (2*x)
            // Add all transformed elements (2*x) that are <= n.
            for (int x : res)
                if (2 * x <= n)
                    tmp.push_back(2 * x);

            // The new sequence becomes the basis for the next iteration (doubling the size roughly)
            res = tmp;
        }

        return res;
    }

private:
    // Recursive helper function for the Divide and Conquer approach
    vector<int> helper(int n)
    {
        // Base case
        if (n == 1)
            return {1};

        // Divide step: Recursive call for odds and evens
        // The numbers 1..N are split into two groups based on the solution for 1..(N+1)/2 and 1..N/2
        vector<int> left = helper((n + 1) / 2); // Base for odds (e.g., for N=5, N_odd=3)
        vector<int> right = helper(n / 2);      // Base for evens (e.g., for N=5, N_even=2)

        // Conquer (combine) step
        vector<int> res;

        // Transform and add Odd part (2*x - 1)
        for (int x : left)
            res.push_back(2 * x - 1);

        // Transform and add Even part (2*x)
        for (int x : right)
            res.push_back(2 * x);

        return res;
    }
};

void printVector(const vector<int> &arr)
{
    cout << "{";
    for (size_t i = 0; i < arr.size(); ++i)
    {
        cout << arr[i] << (i == arr.size() - 1 ? "" : ", ");
    }
    cout << "}";
}

int main()
{
    Solution sol;

    int n1 = 4;
    vector<int> res1_rec = sol.beautifulArrayRec(n1); // Expected: {1, 3, 2, 4}
    vector<int> res1_itr = sol.beautifulArrayItr(n1); // Expected: {1, 3, 2, 4}
    cout << "N = " << n1 << " (Recursive): ";
    printVector(res1_rec);
    cout << endl;
    cout << "N = " << n1 << " (Iterative): ";
    printVector(res1_itr);
    cout << endl;

    int n2 = 5;
    vector<int> res2_rec = sol.beautifulArrayRec(n2); // Expected: {1, 5, 3, 2, 4}
    vector<int> res2_itr = sol.beautifulArrayItr(n2); // Expected: {1, 5, 3, 2, 4}
    cout << "N = " << n2 << " (Recursive): ";
    printVector(res2_rec);
    cout << endl;
    cout << "N = " << n2 << " (Iterative): ";
    printVector(res2_itr);
    cout << endl;

    int n3 = 7;
    vector<int> res3_rec = sol.beautifulArrayRec(n3); // Expected: {1, 5, 3, 7, 2, 6, 4}
    vector<int> res3_itr = sol.beautifulArrayItr(n3); // Expected: {1, 5, 3, 7, 2, 6, 4}
    cout << "N = " << n3 << " (Recursive): ";
    printVector(res3_rec);
    cout << endl;
    cout << "N = " << n3 << " (Iterative): ";
    printVector(res3_itr);
    cout << endl;

    return 0;
}