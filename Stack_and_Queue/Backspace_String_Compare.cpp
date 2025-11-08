/*
File: Backspace_String_Compare.cpp
Date: 2025-11-08 17:50

Problem: Backspace String Compare
Link: https://leetcode.com/problems/backspace-string-compare/description/

Problem Statement:
Given two strings S and T, return if they are equal when both are typed into
empty text editors. '#' means a backspace character. Note that after an empty text,
typing a character followed by a backspace deletes nothing.

-------------------------------------------------
❌ Brute Force (Conceptual/Simple Simulation)
- Idea: Explicitly construct the final string for both S and T using a helper function
  that simulates the typing (e.g., using a dynamically growing vector or string as a stack),
  then compare the two resulting strings for equality.
- Time complexity: O(N_s + N_t), where N_s and N_t are the lengths of S and T.
- Space complexity: O(N_s + N_t) to store the fully built resulting strings.
- Limitations: Uses linear extra space, which can be avoided.

✅ Optimized Approachs
- Idea: The Backspace operation inherently means "delete the last character added," which is
  a **Last-In, First-Out (LIFO)** behavior, making a Stack the natural fit.
- Approach: **Stack-Based Simulation (Current Implementation)**
- Algorithm:
  1. Process string S: For each character, push it to stack 1. If the character is '#', pop
     from stack 1 if it's not empty.
  2. Process string T: Repeat step 1 with stack 2.
  3. Compare the contents of stack 1 and stack 2 element-by-element (or by size and then element content).
- Time complexity: O(N_s + N_t) (Two passes through the strings).
- Space complexity: O(N_s + N_t) (To store the two stacks).

---

Alternative Optimized Approach: **Two-Pointers (O(1) Space)**
- Idea: Since the backspace affects characters *before* it, processing the string *backward* allows us to determine which characters are kept without needing extra space.
- Algorithm:
  1. Initialize two pointers, one at the end of S (`i`) and one at the end of T (`j`).
  2. Loop while `i >= 0` or `j >= 0`:
     a. Find the true next valid character for S: Count consecutive backspaces (`#`). Move `i` left, skipping characters equal to the backspace count.
     b. Find the true next valid character for T: Repeat for `j`.
     c. Compare the characters at `S[i]` and `T[j]`. If they don't match (or one pointer is out of bounds and the other isn't), return `false`.
     d. Move `i` and `j` one step left.
  3. If the loop completes, return `true`.
- Time complexity: O(N_s + N_t)
- Space complexity: O(1)

💡 Key Pattern:
- **Stack / LIFO:** Used for sequential processing where the most recent operation/element
  must be prioritized (e.g., Backspace, Valid Parentheses).
- **Two Pointers (Backward):** Used when processing order (like backspace effects) simplifies
  the logic from the end of a sequence.

ℹ️ Keywords:
- Stack, Simulation, Two Pointers, String Comparison, LIFO.

🗒️ Notes
- The Stack approach is often preferred for readability, while the Two-Pointer approach
  is technically superior due to its O(1) space complexity.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
private:
    // Helper function (Optional, but shows the core stack logic cleanly)
    string build_string(const string &s)
    {
        stack<char> st;
        for (char c : s)
        {
            if (c == '#')
            {
                if (!st.empty())
                {
                    st.pop();
                }
            }
            else
            {
                st.push(c);
            }
        }

        string result = "";
        while (!st.empty())
        {
            // Prepending here rebuilds the string in the correct forward order
            result = st.top() + result;
            st.pop();
        }
        return result;
    }

public:
    /**
     * @brief Compares two strings after backspace operations are applied.
     * @param s The first input string.
     * @param t The second input string.
     * @return True if the final strings are equal, False otherwise.
     */
    bool backspaceCompare(string s, string t)
    {
        stack<char> st1, st2;

        // Process s
        for (char c : s)
        {
            if (c == '#')
            {
                if (!st1.empty())
                    st1.pop();
            }
            else
            {
                st1.push(c);
            }
        }

        // Process t
        for (char c : t)
        {
            if (c == '#')
            {
                if (!st2.empty())
                    st2.pop();
            }
            else
            {
                st2.push(c);
            }
        }

        // Step 3: Compare final stacks (must be identical in content and order)
        // Check size first for early exit
        if (st1.size() != st2.size())
            return false;

        while (!st1.empty())
        {
            if (st1.top() != st2.top())
                return false;
            st1.pop();
            st2.pop();
        }

        return true;
    }

    /* // Uncomment for O(1) Space solution:
    bool backspaceCompare_O1(string s, string t) {
        int i = s.length() - 1;
        int j = t.length() - 1;
        int skips = 0;
        int skipt = 0;

        while (i >= 0 || j >= 0) {
            // Find the index of the next valid character in S
            while (i >= 0) {
                if (s[i] == '#') {
                    skips++;
                    i--;
                } else if (skips > 0) {
                    skips--;
                    i--;
                } else {
                    break;
                }
            }

            // Find the index of the next valid character in T
            while (j >= 0) {
                if (t[j] == '#') {
                    skipt++;
                    j--;
                } else if (skipt > 0) {
                    skipt--;
                    j--;
                } else {
                    break;
                }
            }

            // Compare the characters (only if both pointers are still valid)
            if (i >= 0 && j >= 0) {
                if (s[i] != t[j]) {
                    return false;
                }
            }
            // Handle edge case: one string has characters left, the other doesn't (must be false)
            else if (i >= 0 || j >= 0) {
                return false;
            }

            i--;
            j--;
        }

        return true;
    }
    */
};

int main()
{
    Solution sol;

    // Test cases for the stack-based solution
    cout << "Test 1: \"ab#c\" vs \"ad#c\" -> " << (sol.backspaceCompare("ab#c", "ad#c") ? "True" : "False") << " (Expected: True, both result in \"ac\")" << endl;
    cout << "Test 2: \"ab##\" vs \"c#d#\" -> " << (sol.backspaceCompare("ab##", "c#d#") ? "True" : "False") << " (Expected: True, both result in \"\")" << endl;
    cout << "Test 3: \"a##c\" vs \"#a#c\" -> " << (sol.backspaceCompare("a##c", "#a#c") ? "True" : "False") << " (Expected: True, both result in \"c\")" << endl;
    cout << "Test 4: \"a#c\" vs \"b\" -> " << (sol.backspaceCompare("a#c", "b") ? "True" : "False") << " (Expected: False, results are \"c\" and \"b\")" << endl;
    cout << "Test 5: \"y#fo##f\" vs \"y#f#o##f\" -> " << (sol.backspaceCompare("y#fo##f", "y#f#o##f") ? "True" : "False") << " (Expected: True, both result in 'f')" << endl;
    cout << "Test 6: \"bxj##tw\" vs \"bxj###tw\" -> " << (sol.backspaceCompare("bxj##tw", "bxj###tw") ? "True" : "False") << " (Expected: False, results are \"btw\" and \"tw\")" << endl;

    return 0;
}