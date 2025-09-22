/*
File: Valid_Parenthesis_String.cpp
Date: 2025-09-22 09:34

Problem: Valid Parenthesis String
Link: https://leetcode.com/problems/valid-parenthesis-string/

Problem Statement: Given a string containing only three types of characters: '(', ')', and '*', write a function to check whether this string is valid. The following rules define a valid string:
1. Any left parenthesis '(' must have a corresponding right parenthesis ')'.
2. Any right parenthesis ')' must have a corresponding left parenthesis '('.
3. The left parenthesis '(' must appear before the corresponding right parenthesis ')'.
4. The '*' character can be treated as a single right parenthesis ')', a single left parenthesis '(', or an empty string "".
5. An empty string is also valid.

-------------------------------------------------
❌ Brute Force
- Idea: The brute-force approach would be to recursively explore all possible interpretations of the '*' characters. For each '*', we could branch into three recursive calls, treating it as '(', ')', or an empty string. We would return `true` if any of these branches lead to a valid string, and `false` otherwise.
- Time complexity: O(3^N), where N is the length of the string, due to the three recursive choices for each '*' character.
- Space complexity: O(N) for the recursion stack depth.
- Limitations: This approach is highly inefficient and would time out for even moderately sized strings.

✅ Optimized Approach
- Idea: This problem can be solved with a single pass using a greedy algorithm. Instead of trying all possibilities, we can track the minimum and maximum possible number of open left parentheses that are needed to make the string valid at any point.
- Approach: A greedy, single-pass algorithm.
- Algorithm:
  1. Initialize two counters, `low` and `high`, to 0. `low` tracks the minimum possible number of open left parentheses, and `high` tracks the maximum.
  2. Iterate through the string character by character.
  3. If the character is '(', increment both `low` and `high`.
  4. If the character is ')', decrement both `low` and `high`.
  5. If the character is '*', decrement `low` (assuming '*' is an empty string or a closing ')' to fulfill a `low` requirement) and increment `high` (assuming '*' is an opening '('). This captures the range of possibilities.
  6. After each character, check the state:
     - If `high` becomes negative, it means we have too many ')' characters, even when all '*'s are treated as '('. In this case, the string is invalid, so return `false`.
     - `low` can become negative if we have an unclosed ')' or '*' at the start. However, this is acceptable because an earlier '*' could act as a '('. We "clamp" `low` at 0 to ensure it never goes below zero, as we can't have a negative balance of open parentheses.
  7. After the loop, the string is valid if and only if the minimum possible number of open parentheses (`low`) is exactly 0. This means all open parentheses have a corresponding closing one.

- Time complexity: O(N), as we iterate through the string once.
- Space complexity: O(1), as we only use a few integer variables.

💡 Key Pattern:
- **Greedy Algorithms with Range Tracking**: This is a non-obvious application of a greedy algorithm. By maintaining a range of possibilities (min and max open parentheses), we can make a single pass decision without backtracking. This pattern is useful for problems that involve matching characters or counting balances with wildcards.

ℹ️ Keywords:
- Greedy Algorithm, String, Parentheses, Two-Pointer, Balance Counter

🗒️ Notes
- The logic for `low` and `high` is critical. `high` represents the "best-case" scenario (all '*'s are '('), while `low` represents the "worst-case" scenario (all '*'s are ')'). For the string to be valid, both scenarios must not fail.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Checks if a string containing '(', ')', and '*' is a valid parenthesis string.
     * @param s The input string.
     * @return true if the string is valid, false otherwise.
     */
    bool checkValidString(string s)
    {
        int low = 0;  // Minimum possible balance of open parentheses
        int high = 0; // Maximum possible balance of open parentheses

        for (char c : s)
        {
            if (c == '(')
            {
                low++;
                high++;
            }
            else if (c == ')')
            {
                // If ')' is encountered, both min and max counts of open parentheses decrease.
                low--;
                high--;
            }
            else // c == '*'
            {
                // '*' can be either '(', ')' or an empty string.
                // To find the minimum possible balance, treat '*' as a ')'.
                low--;
                // To find the maximum possible balance, treat '*' as a '('.
                high++;
            }

            // If `high` ever drops below zero, it means we have too many closing parentheses
            // even if all '*' are treated as opening parentheses.
            if (high < 0)
            {
                return false;
            }

            // `low` can become negative (e.g., if the first character is '*'),
            // but we can't have a negative balance of open parentheses.
            // We clamp it at 0 because an unclosed ')' can be balanced by a '*'
            // that is acting as an empty string or '(' to balance a future ')'.
            low = max(0, low);
        }

        // The string is valid only if the minimum possible balance is 0 at the end.
        // This ensures all open parentheses have been matched.
        return low == 0;
    }
};

int main()
{
    Solution sol;
    
    // Example test cases
    cout << "Test 1: \"()\" -> " << boolalpha << sol.checkValidString("()") << endl; // Expected: true
    cout << "Test 2: \"(*)\" -> " << boolalpha << sol.checkValidString("(*)") << endl; // Expected: true
    cout << "Test 3: \"(*))\" -> " << boolalpha << sol.checkValidString("(*))") << endl; // Expected: true
    cout << "Test 4: \"(())\" -> " << boolalpha << sol.checkValidString("(()))") << endl; // Expected: false
    cout << "Test 5: \"*\" -> " << boolalpha << sol.checkValidString("*") << endl; // Expected: true
    cout << "Test 6: \")*(\" -> " << boolalpha << sol.checkValidString(")*(") << endl; // Expected: false

    return 0;
}