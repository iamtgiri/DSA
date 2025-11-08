/*
File: Print_Bracket_Number.cpp
Date: 2025-11-08 18:11

Problem: Print Bracket Number
Link: https://www.geeksforgeeks.org/problems/print-bracket-number4058/0

Problem Statement:
Given a string of parentheses, assign a sequential number to every opening bracket.
The corresponding closing bracket must be assigned the same number.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: This problem is inherently sequential and structure-dependent. A true brute-force
  approach is not meaningful, as any valid solution must process the string to understand
  the nesting structure.
- Time complexity: N/A
- Space complexity: N/A
- Limitations: N/A

Current/Optimized Approachs
- Idea: We need a mechanism to assign unique sequential IDs to opening brackets and then
  recall the ID of the most recently opened, unmatched bracket when we encounter a closing one.
- Approach: **Stack-based Traversal** and **Unique ID Counter (Greedy)**
- Algorithm:
  1. Initialize a **counter** (`count`) starting at 0 to generate unique bracket pair IDs sequentially.
  2. Initialize a **stack** (`st`) to store the IDs of currently open (unmatched) brackets.
  3. Iterate through the string character by character:
     a. **If character is '(':**
        i. Increment `count` to get the next unique ID.
        ii. Push this new ID onto the stack (`st.push(count)`).
        iii. Record the ID in the result vector.
     b. **If character is ')':**
        i. The matching ID is the one at the top of the stack (`st.top()`).
        ii. Record this ID in the result vector.
        iii. Pop the ID from the stack (`st.pop()`) as the bracket pair is now complete.
- Time complexity: O(N), single pass through the string, where N is the length of the string. Stack operations are O(1).
- Space complexity: O(N), for storing the result vector and the stack, which can hold up to N/2 elements in the worst case (e.g., "(((").

💡 Key Pattern:
- **Stack for Nesting and Matching:** Used to track the "state" or "ID" of the most recently
  encountered element that is waiting for closure.

ℹ️ Keywords:
- Stack, Sequencing, Nesting, Parentheses, Unique ID.

🗒️ Notes
- This technique is similar to validating parentheses, but instead of tracking characters,
  we track the unique *number* associated with each pending open bracket.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Assigns sequential numbers to matching bracket pairs.
     * @param str The input string containing only '(' and ')'.
     * @return A vector of integers representing the bracket numbers in order of appearance.
     */
    vector<int> bracketNumbers(string str)
    {
        vector<int> res;
        int count = 0; // Unique ID generator for each new pair
        stack<int> st; // Stores the IDs of open brackets

        for (char c : str)
        {
            if (c == '(')
            {
                // New opening bracket found: generate ID, push to stack, record
                ++count;
                st.push(count);
                res.push_back(count);
            }
            else if (c == ')')
            {
                // Closing bracket found: use ID from stack top, record, pop
                // We assume the input string is always balanced based on problem context,
                // but robust code would check if st is empty.
                if (!st.empty())
                {
                    res.push_back(st.top());
                    st.pop();
                }
            }
        }
        return res;
    }

    // Utility function to print the vector result
    void printVector(const vector<int> &v)
    {
        cout << "[";
        for (size_t i = 0; i < v.size(); ++i)
        {
            cout << v[i];
            if (i < v.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "]";
    }
};

int main()
{
    Solution sol;
    string s1 = "(())()";
    string s2 = "(((())))";
    string s3 = "()";

    cout << "String: " << s1 << endl;
    cout << "Result: ";
    sol.printVector(sol.bracketNumbers(s1)); // Expected: [1, 2, 2, 1, 3, 3]
    cout << " (Expected: [1, 2, 2, 1, 3, 3])" << endl
         << endl;

    cout << "String: " << s2 << endl;
    cout << "Result: ";
    sol.printVector(sol.bracketNumbers(s2)); // Expected: [1, 2, 3, 4, 4, 3, 2, 1]
    cout << " (Expected: [1, 2, 3, 4, 4, 3, 2, 1])" << endl
         << endl;

    cout << "String: " << s3 << endl;
    cout << "Result: ";
    sol.printVector(sol.bracketNumbers(s3)); // Expected: [1, 1]
    cout << " (Expected: [1, 1])" << endl
         << endl;

    return 0;
}