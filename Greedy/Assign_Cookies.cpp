/*
File: Assign_Cookies.cpp
Date: 2025-09-19 22:45

Problem: Assign Cookies
Link: https://leetcode.com/problems/assign-cookies/

Problem Statement:
------------------
Each child has a "greed factor" g[i], representing the minimum size of cookie 
they need to be satisfied. Each cookie has a size s[j]. A child can receive 
at most one cookie, and a cookie can be given to at most one child.

Goal: Maximize the number of satisfied children.

-------------------------------------------------
❌ Brute Force
- Idea: Try all assignments of cookies to children.
- Time complexity: O(n! * m!), infeasible.
- Space complexity: O(1).
- Limitations: Exponential explosion.

✅ Optimized Approach (Greedy + Sorting)
- Idea:
  1. Sort both greed factors and cookie sizes.
  2. Use two pointers: one for children, one for cookies.
  3. Assign the smallest cookie that can satisfy the current child.
  4. Move to next child when satisfied; otherwise, try the next bigger cookie.
- Time complexity: O(n log n + m log m) for sorting + O(n + m).
- Space complexity: O(1).

💡 Key Pattern:
- Greedy matching with two pointers.
- Similar to "Interval Scheduling" / "Activity Selection".

Keywords:
- Greedy
- Two Pointers
- Sorting

🗒️ Notes
- Don't waste large cookies on less greedy children.
- Sorting enables optimal greedy matching.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int child = 0, cookie = 0;
        int n = g.size(), m = s.size();

        while (child < n && cookie < m) {
            if (s[cookie] >= g[child]) {
                // assign cookie to child
                child++;
            }
            // either way, move to next cookie
            cookie++;
        }
        return child; // number of satisfied children
    }
};

int main() {
    Solution sol;

    vector<int> g1 = {1,2,3}, s1 = {1,1};
    cout << sol.findContentChildren(g1, s1) << "\n"; // 1

    vector<int> g2 = {1,2}, s2 = {1,2,3};
    cout << sol.findContentChildren(g2, s2) << "\n"; // 2

    return 0;
}
