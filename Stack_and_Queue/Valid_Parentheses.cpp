/*
File: Valid_Parentheses.cpp
Date: 2025-11-08 17:31

Problem: Valid Parentheses
Link: https://leetcode.com/problems/valid-parentheses/description/

Problem Statement:
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']',
determine if the input string is valid. A string is valid if:
1. Open brackets must be closed by the same type of brackets.
2. Open brackets must be closed in the correct order.
3. Every close bracket has a corresponding open bracket of the same type.

-------------------------------------------------
❌ Brute Force
- Idea: Repeatedly search for and remove the innermost valid pairs (e.g., "()", "{}", "[]")
  from the string until no more pairs can be removed. If the final string is empty, it's valid.
- Time complexity: O(N^2), due to potentially many passes and expensive string manipulation/search operations.
- Space complexity: O(N) for intermediate string copies.
- Limitations: Highly inefficient and complex to implement reliably.

✅ Optimized Approachs
- Idea: The requirement for correct **nesting** and **order of closure** perfectly aligns with
  the **Last-In, First-Out (LIFO)** behavior of a Stack. The most recently opened bracket
  must be the first one closed.
- Approach: Stack-Based Matching
- Algorithm:
  1. Initialize an empty **stack** to store opening brackets.
  2. Iterate through the string character by character.
  3. If an **opening bracket** (`(`, `{`, `[`) is encountered, push it onto the stack.
  4. If a **closing bracket** (`)`, `}`, `]`) is encountered:
     a. Check if the stack is empty. If it is, return `false` (closing bracket has no opener).
     b. Check if the **top element** of the stack is the corresponding opening bracket.
        If it matches, pop the top element.
     c. If it doesn't match, return `false` (mismatching types or incorrect order).
  5. After the loop, the string is valid if and only if the stack is **empty**.
- Time complexity: O(N), as we iterate through the string once, and stack operations are O(1).
- Space complexity: O(N), in the worst case (e.g., "((((...")) where the stack holds up to N/2 elements.

💡 Key Pattern:
- **Stack / LIFO Structure:** Problems involving matching, nesting, or recent history (e.g., finding the next smaller/larger element, function calls) are generally solved using a stack.

ℹ️ Keywords:
- Stack, LIFO, Matching, Parentheses, Nesting.

🗒️ Notes
- The use of a Hash Map (`p`) to quickly look up the required opening bracket corresponding to a closing bracket makes the logic cleaner than a series of `if/else if` statements.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Determines if the input string containing parentheses is valid.
     * @param s The input string.
     * @return True if the string is valid, False otherwise.
     */
    bool isValid(string s)
    {
        stack<char> st;
        // Map closing bracket to its required opening bracket
        unordered_map<char, char> p = {{')', '('}, {'}', '{'}, {']', '['}};

        for (char c : s)
        {
            // Check if 'c' is a closing bracket (it exists as a key in the map 'p')
            if (p.count(c))
            {
                // If the stack is empty OR the top element does not match the required opener
                if (st.empty() || st.top() != p[c])
                    return false;

                // Match found, pop the opener
                st.pop();
            }
            else
            {
                // 'c' is an opening bracket, push it
                st.push(c);
            }
        }

        // The string is valid only if the stack is empty (all openers were closed)
        return st.empty();
    }
};

int main()
{
    Solution sol;

    cout << "Test 1: \"()[]{}\" -> " << (sol.isValid("()[]{}") ? "True" : "False") << " (Expected: True)" << endl;
    cout << "Test 2: \"([{}])\" -> " << (sol.isValid("([{}])") ? "True" : "False") << " (Expected: True)" << endl;
    cout << "Test 3: \"(]\" -> " << (sol.isValid("(]") ? "True" : "False") << " (Expected: False)" << endl;
    cout << "Test 4: \"(((\" -> " << (sol.isValid("(((") ? "True" : "False") << " (Expected: False)" << endl;
    cout << "Test 5: \"{}[}\" -> " << (sol.isValid("{}[}") ? "True" : "False") << " (Expected: False)" << endl;

    return 0;
}