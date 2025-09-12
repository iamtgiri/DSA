/*
File: 3-minimum_window_substring.cpp
Date: 2025-09-10 13:55

Problem: Minimum Window Substring
Link: https://leetcode.com/problems/minimum-window-substring/
Problem Statement:
    Given two strings s and t, return the minimum window substring of s such that
    every character in t (including duplicates) is included in the window.
    If there is no such substring, return the empty string "".

Example:
    Input: s = "zoomlazapzo", t = "oza"
    Output: "omlaz"

-------------------------------------------------
❌ Brute Force
- Idea: Generate all substrings of s and check if they contain all chars of t.
- Time complexity: O(n^3) (O(n^2) substrings × O(n) check).
- Space complexity: O(1).
- Limitations: Too slow for n > 100.

✅ Optimized Approach (Sliding Window + HashMap)
- Idea:
    * Count frequencies of characters in t (need[]).
    * Expand right pointer, include characters into the window.
    * When window covers all of t, shrink left pointer to minimize length.
    * Track best (smallest) valid window.
- Time complexity: O(n), since each char is processed at most twice.
- Space complexity: O(1), because we only track ASCII (256) characters.

Pseudocode:
-----------------------------------------------------------------------
function minWindow(s, t):
    if length(t) > length(s):
        return ""

    need = frequency map of t
    have = empty map
    requiredSize = number of distinct chars in t
    formedSize = 0

    left = 0
    start = 0
    minLen = ∞

    for right = 0 to length(s)-1:
        c = s[right]
        have[c]++

        if need[c] exists AND have[c] == need[c]:
            formedSize++

        while formedSize == requiredSize:
            if currLen < minLen:
                minLen = right - left + 1
                start = left

            d = s[left]
            have[d]--
            if need[d] exists AND have[d] < need[d]:
                formedSize--
            left++

    if minLen == ∞:
        return ""
    else:
        return substring_of_s(start to start + minLen)
-----------------------------------------------------------------------


💡 Key Pattern:
- Sliding Window
- Two Pointers
- Frequency Counting

Keywords:
- String, HashMap, Sliding Window, Two Pointers

🗒️ Notes
- Very common interview problem.
- Be careful with duplicates in t.
- Track "formed" count to know when window is valid.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string minWindow(string s, string t)
    {
        if (t.size() > s.size())
            return "";

        // Step 1: Build frequency map for t
        unordered_map<char, int> need, have;
        for (char c : t)
            need[c]++;

        int required = need.size(); // distinct chars required
        int formed = 0;             // distinct chars currently satisfied

        // Step 2: Sliding window pointers
        int left = 0, right = 0;

        // Step 3: Result tracking
        int minLen = INT_MAX;
        int start = 0; // starting index of best window

        // Step 4: Expand the window using right pointer
        while (right < s.size())
        {
            char c = s[right];
            have[c]++;

            // If current char meets the required frequency
            if (need.count(c) && have[c] == need[c])
            {
                formed++;
            }

            // Step 5: Shrink window from left if valid
            while (formed == required)
            {
                // Update minimum window result
                if (right - left + 1 < minLen)
                {
                    minLen = right - left + 1;
                    start = left;
                }

                // Remove leftmost char from window
                char d = s[left];
                have[d]--;
                if (need.count(d) && have[d] < need[d])
                {
                    formed--; // window no longer valid
                }
                left++;
            }

            // Step 6: Move right pointer forward
            right++;
        }

        // Step 7: Return result
        return (minLen == INT_MAX) ? "" : s.substr(start, minLen);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    string s, t;
    cin >> s >> t;

    cout << sol.minWindow(s, t) << "\n";
    return 0;
}
