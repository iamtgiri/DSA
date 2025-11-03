/*
File: Minimum_Multiplications_to_reach_End.cpp
Date: 2025-11-04 00:52

Problem: Minimum Multiplications to reach End

Link: https://www.geeksforgeeks.org/problems/minimum-multiplications-to-reach-end/1

Problem Statement:
Given an array of integers `arr`, a starting number `start`, and an ending
number `end`, find the minimum number of multiplications required to reach `end`
from `start`. In each step, you can multiply `start` by any element `x` in `arr`,
and the result must be taken modulo 100000. If `start` is equal to `end`, return 0.

-------------------------------------------------
❌ Brute Force
- Idea: Recursively explore all possible multiplication sequences (Depth-First
  Search - DFS). The state space is $0$ to $MOD-1$.
- Time complexity: Exponential, highly dependent on the array `arr` and the path length.
- Space complexity: O(MOD) for visited tracking and O(depth) for the recursion stack.
- Limitations: Prone to infinite loops if not carefully tracking visited states
  and highly inefficient due to redundant calculations, making it non-optimal for
  finding the *minimum* steps.

✅ Optimized Approachs
- Idea: The problem asks for the minimum steps (shortest path) in an unweighted
  graph, where nodes are remainders $0$ to $MOD-1$, and edges are multiplications.
- Approach: **Breadth-First Search (BFS)**.
- Algorithm:
  1. **States & Graph:** The nodes are the numbers $0$ to $99999$ (MOD - 1).
     Edges connect node $u$ to node $v$ if $v = (u \times x) \pmod{100000}$ for
     some $x$ in `arr`.
  2. **Initialization:** Use a distance array `dist` of size $100000$ to store
     the minimum steps, initialized to infinity. Set `dist[start] = 0` and
     enqueue `start`.
  3. **BFS:** While the queue is not empty, dequeue the current number (`num`).
     For every multiplier `x` in `arr`:
     a. Calculate the next number: `next = (num * x) % MOD`.
     b. If `dist[next]` can be improved (i.e., `steps + 1 < dist[next]`):
        i. Update `dist[next]`.
        ii. If `next == end`, return `dist[next]`.
        iii. Enqueue `next`.
  4. **Termination:** If the queue becomes empty and `end` was not reached, return -1.
- Time complexity: **O(MOD * |arr|)**, where MOD is $10^5$. Each of the MOD nodes
  is processed once, and for each, we iterate through $|arr|$ neighbors.
- Space complexity: **O(MOD)** to store the distance array and the queue.

💡 Key Pattern:
- **Shortest Path in Uniform-Cost Graph:** Any time a "minimum steps" or
  "minimum turns" problem is encountered where each step/move has the same cost,
  **BFS** is the optimal algorithm. The state space definition (here, $0$ to $99999$)
  is crucial.

ℹ️ Keywords:
- BFS, Shortest Path, Modular Arithmetic, Graph Traversal, Minimum Steps, Unweighted Graph.

🗒️ Notes
- The modulus is $10^5$, meaning the state space is fixed at 100,000 nodes.
- We must use `long long` for the multiplication `num * x` *before* applying the
  modulo operation to prevent integer overflow if the intermediate product exceeds
  $2 \times 10^9$.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Computes the minimum number of multiplications to reach 'end' from 'start' modulo 100000.
     * @param arr The array of allowed multipliers.
     * @param start The starting number.
     * @param end The target number.
     * @return The minimum number of steps, or -1 if unreachable.
     */
    int minimumMultiplications(vector<int> &arr, int start, int end)
    {
        if (start == end)
            return 0;

        // The problem defines the modulus as 100000
        const int MOD = 100000;

        // dist array acts as the visited tracker and stores minimum steps
        vector<int> dist(MOD, INT_MAX);
        queue<int> q;

        dist[start] = 0;
        q.push(start);

        // BFS traversal
        while (!q.empty())
        {
            int num = q.front();
            q.pop();
            int steps = dist[num];

            for (int x : arr)
            {
                // IMPORTANT: Use long long for intermediate product to prevent overflow
                // before applying MOD, as num * x could exceed 2 * 10^9.
                long long product = (long long)num * x;
                int next = product % MOD;

                // Relaxation step (found a shorter path)
                if (dist[next] > steps + 1)
                {
                    dist[next] = steps + 1;

                    if (next == end)
                        return dist[next];

                    q.push(next);
                }
            }
        }

        // End is unreachable
        return -1;
    }
};

int main()
{
    Solution sol;

    cout << "--- Minimum Multiplications Test Cases ---\n";

    // Test Case 1: Standard shortest path
    // Path: 3 -> (3 * 2) = 6 -> (6 * 5) = 30. Steps: 2
    vector<int> arr1 = {2, 3, 5};
    int start1 = 3, end1 = 30;
    int result1 = sol.minimumMultiplications(arr1, start1, end1);
    cout << "Test 1 (3 -> 30): Expected 2, Got " << result1 << endl;
    cout << "--------------------------------------------------------\n";

    // Test Case 2: No path (e.g., start is odd, and all multipliers are even)
    // Since 7 * x (where x is 2 or 4) is always even, 9 is unreachable.
    vector<int> arr2 = {2, 4};
    int start2 = 7, end2 = 9;
    int result2 = sol.minimumMultiplications(arr2, start2, end2);
    cout << "Test 2 (7 -> 9): Expected -1, Got " << result2 << endl;
    cout << "--------------------------------------------------------\n";

    // Test Case 3: Path involving the Modulo operation (MOD = 100000)
    // Path: 10 -> (10 * 10) = 100 -> (100 * 1000) = 100000 % 100000 = 0.
    // If end is 0, path is 2 steps.
    vector<int> arr3 = {10, 100, 1000};
    int start3 = 10, end3 = 0;
    int result3 = sol.minimumMultiplications(arr3, start3, end3);
    cout << "Test 3 (10 -> 0 using MOD): Expected 2, Got " << result3 << endl;
    cout << "--------------------------------------------------------\n";

    return 0;
}
