/*
File: 2-max_sum_with_k_swaps.cpp
Date: 2025-09-11 21:30

Problem: Maximize Sum with At Most K Inclusions
Link: URL
Problem Statement:
    You are given two arrays a[] and b[] of length n.
    You need to maximize the following expression:

        sum = Σ (a[i] - b[i]) + 2 * (selected k elements from b[i])

    - You can "select" at most k indices where b[i] > 0.
    - When you select index i, effectively b[i] is added instead of subtracted,
      so contribution changes by +2*b[i].

    Return the maximum possible sum.

Example:
    Input:
        n = 5, k = 2
        a = [5, 2, 8, 1, 6]
        b = [1, 3, -2, 4, 2]
    Output:
        27
    Explanation:
        Baseline sum = Σ(a[i] - b[i]) = 5-1 + 2-3 + 8-(-2) + 1-4 + 6-2 = 12
        Choose top-2 positives from b = [4, 3]
        Extra = 2*(4+3) = 14
        Total = 12 + 14 = 26

-------------------------------------------------
❌ Brute Force
- Idea: Try all subsets of indices of size ≤ k and compute sum.
- Time complexity: O(2^N)
- Space complexity: O(1)
- Limitations: Infeasible for large N.

✅ Optimized Approach (Greedy + Heap)
- Idea:
    1. Start with baseline = Σ(a[i] - b[i]).
    2. Select top-k positive values from b[].
    3. For each selected b[i], we add +2*b[i] to the result.
    4. Use a min-heap to maintain top-k values efficiently.
- Time complexity: O(N log K)
- Space complexity: O(K)

💡 Key Pattern:
- Baseline sum adjustment
- Top-K selection using heap

Keywords:
- Priority Queue, Heap, Greedy, Optimization

🗒️ Notes
- Similar to "maximize profit with limited choices".
- Trick: baseline subtracts all b[i], then add back +2*b[i] for chosen.
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int maxSum(const vector<int>& a, const vector<int>& b, int n, int k) {
        int sum = 0;     // baseline sum (all a[i] - b[i])
        int toAdd = 0;   // sum of top-k positive b[i]
        priority_queue<int, vector<int>, greater<>> pq; // min-heap

        for (int i = 0; i < n; i++) {
            // baseline contribution
            sum += (a[i] - b[i]);

            // consider b[i] for top-k if positive
            if (b[i] > 0) {
                if ((int)pq.size() < k) {
                    pq.push(b[i]);
                    toAdd += b[i];
                } else if (pq.top() < b[i]) {
                    toAdd -= pq.top();
                    pq.pop();
                    pq.push(b[i]);
                    toAdd += b[i];
                }
            }
        }

        return sum + 2 * toAdd; // adjustment for chosen indices
    }
};

int main() {

    int n, k;
    cout << "Enter n and k: ";
    cin >> n >> k;

    vector<int> a(n), b(n);

    cout << "Enter array a: ";
    for (int i = 0; i < n; i++) cin >> a[i];

    cout << "Enter array b: ";
    for (int i = 0; i < n; i++) cin >> b[i];

    Solution sol;
    cout << "Maximum possible sum = " << sol.maxSum(a, b, n, k) << "\n";

    return 0;
}
