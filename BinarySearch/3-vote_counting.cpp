/*
File: 3-vote_counting.cpp
Date: 2025-09-10 11:50

Problem: Minions and Voting
Link: https://www.codechef.com/problems/MINVOTE
Problem Statement:
    There is a group of N members (P0, P1, ..., PN−1), each with an influence level arr[i].
    A single member may cast any number of votes.
    Rule: Pj will vote for Pi (i ≠ j) if and only if the influence level of Pj is greater than or
    equal to the sum of influence levels of all members strictly between them.
    Find the number of votes received by each member.

Example:
    Input: arr = {12, 16, 12, 13, 11}
    Output: [1, 3, 2, 3, 1]

-------------------------------------------------
❌ Brute Force
- Idea: For every pair (i, j), compute sum of elements between them using prefix sums and
        check the voting condition.
- Time complexity: O(N^2)
- Space complexity: O(N) for prefix sums
- Limitations: Too slow for large N.

✅ Optimized Approach
- Idea:
    1. Precompute prefix sums for O(1) subarray queries.
    2. For each member Pi, use binary search to determine the contiguous range of members
       they can vote for (both left and right side).
    3. Use a difference array to efficiently mark vote ranges.
    4. Convert difference array back to actual counts using prefix sums.
- Time complexity: O(N log N)
- Space complexity: O(N)

💡 Key Pattern:
- Prefix sums + binary search
- Range updates with difference array

Keywords:
- Binary search, prefix sum, difference array, range updates

🗒️ Notes
- Learned how to optimize pairwise vote checks using range updates.
- Avoided O(N^2) brute force with binary search trick.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> vote(int n, vector<int> &arr)
    {
        // Step 1: Build prefix sum (1-based indexing for safe range sums)
        vector<int> pref(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            pref[i] = pref[i - 1] + arr[i - 1];
        }

        // Step 2: Difference array to store range updates for votes
        vector<int> ans(n + 1, 0);

        for (int i = 0; i < n; i++)
        {
            int it = arr[i];

            // -------- Right side voting --------
            int l = i + 1, h = n - 1;
            while (l <= h)
            {
                int mid = l + (h - l) / 2;
                // sum of arr[i+1 .. mid-1]
                int between = pref[mid] - pref[i + 1];
                if (between > it)
                    h = mid - 1;
                else
                    l = mid + 1;
            }
            // P[i] votes for indices [i+1, l-1]
            if (i + 1 <= l - 1)
            {
                ans[i + 1]++;
                ans[l]--;
            }

            // -------- Left side voting --------
            l = 0;
            h = i - 1;
            while (l <= h)
            {
                int mid = l + (h - l) / 2;
                // sum of arr[mid+1 .. i-1]
                int between = pref[i] - pref[mid + 1];
                if (between > it)
                    l = mid + 1;
                else
                    h = mid - 1;
            }
            // P[i] votes for indices [l, i-1]
            if (l <= i - 1)
            {
                ans[l]++;
                ans[i]--;
            }
        }

        // Step 3: Convert difference array → actual vote counts
        for (int i = 1; i < n; i++)
        {
            ans[i] += ans[i - 1];
        }

        ans.resize(n); // drop the extra element
        return ans;
    }
};

int main()
{
    Solution sol;
    // Example test case
    vector<int> arr = {12, 16, 12, 13, 11};
    vector<int> res = sol.vote(arr.size(), arr);

    cout << "Votes: ";
    for (int x : res)
        cout << x << " ";
    cout << "\n";

    return 0;
}
