/*
File: Glide_Typing.cpp
Date: 2025-10-25 18:53

Problem: Glide Typing
Link: URL

Problem Statement:
Implement a glide-typing detection system. Given:
- A string s (the user’s swipe input)
- A dictionary of words
Find the lexicographically smallest word in the dictionary that is a subsequence of s.
If no word matches, return "-1".

Example:
s = "hgferyjkllkop"
dictionary = ["coffee", "coding", "happy", "hello", "hop"]
Output: "hello"

-------------------------------------------------
❌ Brute Force
- Idea: Iterate through the dictionary. For each word, use two pointers to check
  if it's a subsequence of the swipe input 's'. Keep track of the first valid word
  found, and if a new valid word is lexicographically smaller, update the result.
- Time complexity: O(D * (S + W)), where D is dictionary size, S is length of 's',
  and W is max word length.
- Space complexity: O(1) auxiliary space (excluding result string).
- Limitations: Inefficient for very large dictionaries, especially since checking
  for the lexicographically smallest word forces a full scan.

✅ Optimized Approachs
- Idea: The most efficient approach requires two steps: sorting the dictionary
  and then performing a linear scan. However, the current code implements a
  single-pass scan, which is efficient for smaller dictionaries.
- Approach: Single-Pass Scan and Subsequence Check.
- Algorithm:
    1. Initialize `result` to an empty string.
    2. Iterate through every `word` in the `dictionary`.
    3. Use a two-pointer approach (`i` for `s`, `j` for `word`) to check if `word`
       is a subsequence of `s`.
    4. If it is a subsequence, check if `result` is empty OR if `word` is
       lexicographically smaller than the current `result`.
    5. Update `result` if the condition is met.
    6. Return `result` or "-1" if no match was found.
- Time complexity: O(D * (S + W)). Each of the D words is checked in O(S + W) time.
- Space complexity: O(1) auxiliary space (excluding input storage).

💡 Key Pattern:
- **Two-Pointer Subsequence Check:** A common pattern for determining if one string
  is a subsequence of another.

ℹ️ Keywords:
- Subsequence, Two Pointers, Lexicographical Sort, String Matching.

🗒️ Notes
- The complexity is dominated by the number of words times the length of the strings.
  Pre-sorting the dictionary would allow early exit, but is not implemented here.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Checks if a given word is a subsequence of the swipe string 's'.
     * @param s The swipe input string.
     * @param word The dictionary word to check.
     * @return True if 'word' is a subsequence of 's', false otherwise.
     */
    bool isSubsequence(const string &s, const string &word)
    {
        int i = 0, j = 0; // i for s, j for word
        // Traverse both strings
        while (i < s.size() && j < word.size())
        {
            // If characters match, advance the pointer for the word (j)
            if (s[i] == word[j])
                j++;
            // Always advance the pointer for the swipe string (i)
            i++;
        }
        // If j reached the end of the word, the entire word was found as a subsequence
        return j == word.size();
    }

    /**
     * @brief Finds the lexicographically smallest word in the dictionary that is a
     * subsequence of the swipe input 's'.
     * @param s The swipe input string.
     * @param dictionary The list of words to check against.
     * @return The smallest matching word, or "-1" if no match is found.
     */
    string getValidWord(const string &s, const vector<string> &dictionary)
    {
        string result = "";
        for (const string &word : dictionary)
        {
            if (isSubsequence(s, word))
            {
                // If result is empty OR the current word is lexicographically smaller
                if (result == "" || word < result)
                {
                    result = word;
                }
            }
        }
        return result == "" ? "-1" : result;
    }
};

// --- Helper Functions for Test Cases ---
void printVector(const vector<string> &vec)
{
    cout << "{";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        cout << "\"" << vec[i] << "\"";
        if (i < vec.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << "}";
}

int main()
{
    Solution sol;

    cout << "--- Glide Typing Detector ---\n";

    // Test Case 1: Example from problem statement
    // Input: s = "hgferyjkllkop", dictionary = ["coffee", "coding", "happy", "hello", "hop"]
    // Matches: "happy", "hello", "hop". Smallest: "hello"
    string s1 = "hgferyjkllkop";
    vector<string> dict1 = {"coffee", "coding", "happy", "hello", "hop"};
    string result1 = sol.getValidWord(s1, dict1);
    cout << "Test 1 | s: \"" << s1 << "\", dict: ";
    printVector(dict1);
    cout << " Result: \"" << result1 << "\" (Expected: \"hello\")\n";
    cout << "--------------------------------\n";

    // Test Case 2: Lexicographically smaller word found later
    // Input: s = "aplebyc", dictionary = ["apple", "bat", "apec"]
    // Matches: "bat", "apec". Smallest: "apec"
    string s2 = "aplebyc";
    vector<string> dict2 = {"apple", "bat", "apec"};
    string result2 = sol.getValidWord(s2, dict2);
    cout << "Test 2 | s: \"" << s2 << "\", dict: ";
    printVector(dict2);
    cout << " Result: \"" << result2 << "\" (Expected: \"apec\")\n";
    cout << "--------------------------------\n";

    // Test Case 3: No match found
    string s3 = "xyz";
    vector<string> dict3 = {"apple", "banana", "cat"};
    string result3 = sol.getValidWord(s3, dict3);
    cout << "Test 3 | s: \"" << s3 << "\", dict: ";
    printVector(dict3);
    cout << " Result: \"" << result3 << "\" (Expected: \"-1\")\n";
    cout << "--------------------------------\n";

    // Test Case 4: Edge case (single character match)
    string s4 = "abcdef";
    vector<string> dict4 = {"ace", "bdf", "a", "z"};
    string result4 = sol.getValidWord(s4, dict4);
    cout << "Test 4 | s: \"" << s4 << "\", dict: ";
    printVector(dict4);
    cout << " Result: \"" << result4 << "\" (Expected: \"a\")\n";
    cout << "--------------------------------\n";

    return 0;
}
