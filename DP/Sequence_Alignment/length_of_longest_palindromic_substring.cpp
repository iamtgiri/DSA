/*
File: length_of_longest_palindromic_substring.cpp
Date: 2025-09-14 22:19

Problem: Length of Longest Palindromic Substring
Link: URL

Problem Statement:
------------------
Given a string X, find the length of the longest palindromic substring in it.
A palindromic substring is contiguous and reads the same forwards and backwards.

Examples:
---------
Input: "babad"
Output: 3 ("bab" or "aba")

Input: "cbbd"
Output: 2 ("bb")

-------------------------------------------------
❌ Brute Force
- Idea: Generate all substrings and check if palindrome.
- Time complexity: O(n^3).
- Space complexity: O(1).
- Limitations: Too slow for n > 1000.

✅ Optimized Approach (Expand Around Center)
- Idea:
  - For each index, expand around it (odd-length palindrome).
  - Also expand around each pair of indices (even-length palindrome).
  - Track maximum length found.
- Time complexity: O(n^2).
- Space complexity: O(1).
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int longest_palindrome_substring(const string &s)
    {

    }
};

int main()
{
    Solution sol;
    cout << sol.longest_palindrome_substring("babad") << "\n"; // 3
    cout << sol.longest_palindrome_substring("cbbd") << "\n";  // 2
    cout << sol.longest_palindrome_substring("a") << "\n";     // 1
    cout << sol.longest_palindrome_substring("ac") << "\n";    // 1
    return 0;
}
