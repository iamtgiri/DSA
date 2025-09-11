/*
File: 5-chatban.cpp
Date: 2025-09-11 11:40

Problem: Chat Ban (Emote Messages)
Link: URL
Problem Statement:
    In a chat system, a player can send up to `k` emotes:
        - First k messages: 1, 2, 3, ..., k emotes respectively.
        - Then emotes decrease: k-1, k-2, ..., 1.
    So the total possible emotes = k^2.

    Given integers `k` and `x`, find the minimum number of messages needed
    so that the total number of emotes is at least `x`.

Example:
    Input: k = 3, x = 7
    Sequence of emotes per message = [1, 2, 3, 2, 1]
    Minimum messages = 4 (sum = 8 ≥ 7)

-------------------------------------------------
❌ Brute Force
- Idea: Simulate message by message, accumulate emotes until ≥ x.
- Time complexity: O(k)
- Space complexity: O(1)
- Limitations: Too slow for large k.

✅ Optimized Approach 1 (Quadratic Formula)
- Idea:
    - Phase 1 (increasing): use formula sum = n*(n+1)/2.
    - Phase 2 (decreasing): use arithmetic series sum.
    - Reduce to quadratic inequality and solve with formula.
- Time complexity: O(1)
- Space complexity: O(1)

✅ Optimized Approach 2 (Binary Search)
- Idea:
    - Binary search on answer (message count).
    - For mid messages, compute total emotes.
    - Adjust until smallest valid answer is found.
- Time complexity: O(log k)
- Space complexity: O(1)

💡 Key Pattern:
- Binary search on prefix sums
- Quadratic inequality solving

Keywords:
- Binary search, quadratic solver, prefix sums, math problem

🗒️ Notes
- Quadratic method is constant time but requires careful handling of roots.
- Binary search is safer and easier to implement.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // ---------- Quadratic Solver Helper ----------
    long long solver(double a, double b, double c) {
        double d = sqrt(b * b - 4 * a * c);
        double r1 = (-b + d) / (2 * a);
        double r2 = (-b - d) / (2 * a);
        double ans = (r1 > 0) ? r1 : r2; // pick the positive root
        return ceil(ans);
    }

    // ---------- Quadratic Formula Approach ----------
    long long chatban_quadratic(long long k, long long x) {
        long long max_emotes = 1LL * k * k;
        if (x > max_emotes) {
            return 2 * k - 1; // all messages needed
        }

        long long phase1_max = k * (k + 1) / 2;

        if (x <= phase1_max) {
            // Within first increasing phase
            double a = 1, b = 1, c = -2 * x;
            return solver(a, b, c);
        } else {
            // Need part of decreasing phase
            long long need = x - phase1_max;
            double a = -1, b = (2 * k) - 1, c = -2.0 * need;
            return k + solver(a, b, c);
        }
    }

    // ---------- Binary Search Approach ----------
    long long chatban_binary(long long k, long long x) {
        long long total = 1LL * k * k;
        long long low = 1, high = 2 * k - 1;

        while (low < high) {
            long long mid = (low + high) / 2;
            long long cur = 0;

            if (mid <= k)
                cur = (mid * (mid + 1)) / 2;
            else
                cur = total - (((2 * k - mid) * (2 * k - mid - 1)) / 2);

            if (x > cur)
                low = mid + 1;
            else
                high = mid; // mid can still be the answer
        }
        return low;
    }
};

int main() {
    Solution sol;
    long long k, x;
    cout << "Enter k and x: ";
    cin >> k >> x;

    cout << "Quadratic Formula Approach: "
         << sol.chatban_quadratic(k, x) << "\n";
    cout << "Binary Search Approach: "
         << sol.chatban_binary(k, x) << "\n";

    return 0;
}
