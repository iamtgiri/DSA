/*
File: 3-k_max_sum_combinations.cpp
Date: 2025-09-11 12:05

Problem: K Maximum Sum Combinations
Link: URL
Problem Statement:
    Given two integer arrays A[] and B[] of length n each, 
    find the k maximum values of (A[i] + B[j]) such that 
    0 ≤ i, j < n.

Example:
    Input:
        A = [1, 4, 2, 3]
        B = [2, 5, 1, 6]
        k = 3
    Output:
        [10, 9, 9]

-------------------------------------------------
❌ Brute Force
- Idea: Compute all n^2 possible sums (A[i] + B[j]), store them, 
        sort in descending order, take top-k.
- Time complexity: O(n^2 log(n^2)) = O(n^2 log n)
- Space complexity: O(n^2)
- Limitations: Not feasible for large n due to O(n^2) memory.

✅ Optimized Approach
- Idea:
    1. Sort both arrays in descending order.
    2. Use a max-heap to always pick the current largest pair sum.
    3. Use a set to avoid revisiting the same index pairs.
    4. Pop from heap k times, each time pushing possible next pairs:
       (i+1, j) and (i, j+1).
- Time complexity: O(k log k)
- Space complexity: O(k) for heap + set.

💡 Key Pattern:
- "Top K" problems
- Max-Heap + Visited Set
- Greedy exploration of sum pairs

Keywords: Heap, Priority Queue, Top-K, Greedy

🗒️ Notes
- Very similar to "K pairs with smallest sums".
- Mistake to avoid: pushing all n^2 sums into heap — unnecessary.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> kMaxCombinations(vector<int>& A, vector<int>& B, int k) {
        int n = A.size();
        sort(A.begin(), A.end(), greater<int>());
        sort(B.begin(), B.end(), greater<int>());

        // max-heap of (sum, i, j)
        priority_queue<tuple<int, int, int>> pq;
        set<pair<int, int>> visited;

        pq.emplace(A[0] + B[0], 0, 0);
        visited.emplace(0, 0);

        vector<int> result;
        while (k-- && !pq.empty()) {
            auto [sum, i, j] = pq.top();
            pq.pop();
            result.push_back(sum);

            if (i + 1 < n && !visited.count({i + 1, j})) {
                pq.emplace(A[i + 1] + B[j], i + 1, j);
                visited.emplace(i + 1, j);
            }
            if (j + 1 < n && !visited.count({i, j + 1})) {
                pq.emplace(A[i] + B[j + 1], i, j + 1);
                visited.emplace(i, j + 1);
            }
        }
        return result;
    }
};

int main() {
    Solution sol;

    vector<int> A = {1, 4, 2, 3};
    vector<int> B = {2, 5, 1, 6};
    int k = 3;

    vector<int> ans = sol.kMaxCombinations(A, B, k);

    cout << "Top " << k << " maximum sum combinations: ";
    for (int val : ans) cout << val << " ";
    cout << "\n";

    return 0;
}
