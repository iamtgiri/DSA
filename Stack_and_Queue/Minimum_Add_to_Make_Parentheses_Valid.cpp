/*
File: Minimum_Add_to_Make_Parentheses_Valid.cpp
Date: 2025-11-08 17:40

Problem: Minimum Add to Make Parentheses Valid
Link: https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/description/

Problem Statement:
Given a string S of '(' and ')', we want to add the minimum number of parentheses 
(either '(' or ')') so that the resulting string is valid. Return the minimum number 
of additions needed.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: This problem is inherently greedy/sequential, and a true brute force (trying all 
  possible insertions at all possible indices) is exponentially complex and impractical.
- Time complexity: Exponential.
- Space complexity: N/A.
- Limitations: Infeasible due to combinatorial explosion of insertions.

Current/Optimized Approachs
- Idea: We can solve this in a single pass using a **Greedy** approach, ensuring we match 
  open brackets whenever possible. The minimum additions required will be the total count 
  of **unmatched opening brackets** and **unmatched closing brackets**.
- Approach: Stack-Based or Counter-Based Tracking.
- Algorithm (Stack-Based, as implemented): 
  1. Initialize a **stack** (`st`) to store unmatched brackets.
  2. Iterate through the string `s` character by character (`c`):
     a. **If `c` is ')' and the stack is NOT empty and the top is '(':** We found a valid 
        match pair. Pop the '(' from the stack.
     b. **Otherwise (if `c` is '(' or `c` is ')' but the stack is empty/top is not '('):** This character is currently unmatched. Push it onto the stack.
        - If we push '(', it requires a future ')' addition.
        - If we push ')', it requires a preceding '(' addition.
  3. The final result is the **size of the stack**. This size represents the total number of 
     unmatched characters, which is equal to the minimum number of additions required 
     to balance them (e.g., each remaining '(' needs a ')' added, and each remaining ')' needs a '(' added).
- Time complexity: O(N), single pass through the string, with O(1) stack operations.
- Space complexity: O(N), in the worst case (e.g., "(((" or ")))))") where the stack holds up to N elements.

💡 Key Pattern:
- **Stack / Greedy Matching:** Using a stack (or a simple counter for binary matching) 
  to track necessary matches in sequence is the standard solution for parentheses problems.

ℹ️ Keywords: 
- Stack, Greedy, Parentheses, Matching, Minimum Insertions.

🗒️ Notes
- The logic can be simplified even further using two counters: `balance` (for open brackets) and `result` (for total additions). 
  - `balance` increments for '(' and decrements for ')'.
  - If `balance` drops below zero, it means we encountered an unmatched ')', so we increment `result` and reset `balance` to zero.
  - Finally, we return `result + balance`. This counter approach achieves O(1) space complexity.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
    * @brief Calculates the minimum number of parentheses to add to make the string valid.
    * @param s The input string of parentheses.
    * @return The minimum number of additions required.
    */
    int minAddToMakeValid(string s) {
        stack<char> st; // Stores unmatched characters
        for (char c : s) {
            // Check for a perfect match with the last unmatched open bracket
            if (!st.empty() && st.top() == '(' && c == ')')
                st.pop();
            else
                // Push all unmatched open brackets and all closing brackets that couldn't find a match
                st.push(c);
        }
        // The size of the stack is the total number of characters that need a corresponding insertion
        return st.size();
    }

    // Alternative O(1) space approach using counters:
    int minAddToMakeValid_O1(string s) {
        int required_additions = 0;
        int open_balance = 0;

        for (char c : s) {
            if (c == '(') {
                open_balance++;
            } else { // c == ')'
                if (open_balance > 0) {
                    open_balance--; // Found a match
                } else {
                    // Unmatched closing bracket found. We must add an opening '(' before it.
                    required_additions++;
                }
            }
        }

        // After iteration, any remaining open_balance needs a closing ')' added.
        required_additions += open_balance;
        return required_additions;
    }
};

int main() {
    Solution sol;

    cout << "Test 1: \"())" << "\" -> " << sol.minAddToMakeValid("())") << " (Expected: 1)" << endl;
    cout << "Test 2: \"(((" << "\" -> " << sol.minAddToMakeValid("(((") << " (Expected: 3)" << endl;
    cout << "Test 3: \"()\"" << "\" -> " << sol.minAddToMakeValid("()") << " (Expected: 0)" << endl;
    cout << "Test 4: \"))((\"" << " -> " << sol.minAddToMakeValid("))((") << " (Expected: 4)" << endl;
    
    // Testing O(1) space version
    cout << "Test 5 (O(1)): \"()))((\"" << " -> " << sol.minAddToMakeValid_O1("()))((") << " (Expected: 4)" << endl;


    return 0;
}