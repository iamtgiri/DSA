/*
File: 2-chatban.cpp
Date: 2025-09-10 00:38

Problem: Chat Ban (Codeforces)
Link: https://codeforces.com/problemset/problem/1805/B
Problem Statement:
    A user can send "emotes" in a chat. The number of emotes allowed per message 
    first increases linearly from 1 up to k, then decreases linearly back to 1.
    Given integers k and x, find the minimum number of messages required 
    to send at least x emotes.

Example:
    Input: k = 3, x = 8
    Sequence of emotes per message: [1, 2, 3, 2, 1]
    Total emotes = 9
    Answer = 4 (messages [1, 2, 3, 2] = 8)

-------------------------------------------------
❌ Brute Force
- Idea: Simulate message by message until reaching x.
- Time complexity: O(k)
- Space complexity: O(1)
- Limitations: Too slow for k ~ 1e9.

✅ Optimized Approach 1 (Binary Search)
- Idea: Binary search on number of messages.
- Use arithmetic formulas to compute emotes in `mid` messages.
- Time complexity: O(log k)
- Space complexity: O(1)

✅ Optimized Approach 2 (Quadratic Formula)
- Idea: Directly solve quadratic equations for prefix sums in 
  increasing or decreasing phase.
- Time complexity: O(1)
- Space complexity: O(1)
- ⚠️ Needs careful handling of rounding and edge cases.

💡 Key Pattern:
- Prefix sum of arithmetic progression
- Binary search / closed-form quadratic solution

Keywords:
- Binary Search, Math, Prefix Sum, Quadratic Equation

🗒️ Notes
- Binary search is safer in contests.
- Quadratic is faster (O(1)) but more error-prone.
- Good exercise in handling AP sums and math carefully.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Quadratic formula approach (O(1))
    long long chatban_optimal(long long k, long long x) {
        long long max_emotes = 1LL * k * k;
        if (x >= max_emotes) {
            return 2 * k - 1; // all messages needed
        }

        long long phase1_max = 1LL * k * (k + 1) / 2;

        if (x <= phase1_max) {
            // Solve m(m+1)/2 >= x
            double a = 1, b = 1, c = -2.0 * x;
            return solveQuadratic(a, b, c);
        } else {
            // Phase 2: decreasing part
            long long need = x - phase1_max;
            // Equation: m(2k - m + 1)/2 >= need
            // Rearranged into quadratic
            double a = 1, b = -2.0 * k + 1, c = 2.0 * need;
            return k + solveQuadratic(a, b, c);
        }
    }

    // Binary search approach (O(log k)), safe for contests
    long long chatban_binary(long long k, long long x) {
        long long total = 1LL * k * k;
        long long low = 1, high = 2 * k - 1;

        while (low < high) {
            long long mid = (low + high) / 2;
            long long cur = emotesIn(mid, k);

            if (cur < x)
                low = mid + 1;
            else
                high = mid;
        }
        return low;
    }

private:
    // Compute emotes in m messages
    long long emotesIn(long long m, long long k) {
        if (m <= k) {
            return m * (m + 1) / 2;
        } else {
            long long total = 1LL * k * k;
            long long rem = 2 * k - 1 - m;
            return total - (rem * (rem + 1)) / 2;
        }
    }

    // Solve quadratic ax^2 + bx + c >= 0 for smallest positive integer root
    long long solveQuadratic(double a, double b, double c) {
        double d = sqrt(b * b - 4 * a * c);
        double r1 = (-b + d) / (2 * a);
        double r2 = (-b - d) / (2 * a);
        double ans = max(r1, r2); // take the positive root
        return (long long)ceil(ans);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    int T;
    cin >> T;
    while (T--) {
        long long k, x;
        cin >> k >> x;

        // You can test either method
        cout << sol.chatban_optimal(k, x) << "\n";
        // cout << sol.chatban_binary(k, x) << "\n";
    }

    return 0;
}
