/*
File: Basic_Calculator.cpp
Date: 2025-11-19 01:25

Problem: Basic Calculator
Link: https://leetcode.com/problems/basic-calculator/description/

Problem Statement:
Implement a basic calculator to evaluate a simple expression string. The expression string may
 contain open '(' and closing parentheses ')', the plus '+' or minus '-' sign, non-negative integers and empty spaces ' '.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Convert the infix expression to Reverse Polish Notation (RPN) first, and then evaluate
 the RPN expression using a separate stack.
- Time complexity: O(N) for RPN conversion (using a stack), O(N) for RPN evaluation (using a stack). Total O(N).
- Space complexity: O(N) for the RPN list and O(N) for the evaluation stack. Total O(N).
- Limitations: While technically O(N), it requires two separate passes and additional logic (operator
 precedence rules) which are unnecessary since this problem only involves addition and subtraction.

Current/Optimized Approachs
- Idea: Since there are no multiplication or division operations, we can solve this in a single
 pass by maintaining a running total and using a **stack to save the state** (the current running
  total and the sign that preceded the parenthesis) whenever a new parenthesis block starts.
- Approach: **Single-Pass Iterative Calculation with Stack for Context Management.**
- Algorithm:
  1. Initialize `result = 0`, `number = 0`, and `sign = 1` (for positive).
  2. Use a stack to store the state: `(previous_result, sign_before_paren)`.
  3. Iterate through the string:
     - **Digit:** Parse the entire multi-digit `number`.
     - **'+' / '-':** Incorporate the fully parsed `number` into `result` using the current `sign`.
      Reset `number = 0` and update `sign` for the next number.
     - **'(':** Push the current `result` and `sign` onto the stack to save the context. Reset `result = 0`
      and `sign = 1` to start a new sub-calculation.
     - **')':** Incorporate the final `number` inside the parentheses into `result`. Pop the `prev_sign`
      and `prev_result` from the stack. The final step is to merge: `result = prev_result + prev_sign * current_result`.
     - **Space (' '):** Ignore it.
- Time complexity: **O(N)**, where N is the length of the string, as we process each character exactly once.
- Space complexity: **O(N)**, in the worst case, due to deep parenthesis nesting, requiring the stack to
 store up to N/2 pairs of states.

💡 Key Pattern:
- **Stack for Nested Context/State**: Use a stack to save and restore context variables (like the running
 total and sign) when encountering nested blocks (like parentheses in an expression).

ℹ️ Keywords:
- Stack, Expression Evaluation, Single Pass, Context Management, Parentheses.

🗒️ Notes
- Using `long` for `result` and stack values is a safe practice to prevent potential integer overflow, 
although it's not strictly necessary based on typical LeetCode constraints for this problem.
- The use of the stack to store `(result, sign)` pairs allows the computation to be done immediately without
 the need for an intermediate RPN format.
-------------------------------------------------
*/

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <cctype>

using namespace std;

class Solution
{
public:
    /**
     * @brief Evaluates a basic arithmetic expression using a stack for parenthesis context.
     * @param s The input expression string.
     * @return The integer result of the calculation.
     */
    int calculate(string s)
    {
        // Use long for intermediate results to be safe from overflow,
        // although the problem constraints usually keep results within int range.
        long result = 0;
        long number = 0;
        int sign = 1; // Tracks the sign (+1 or -1) of the current number being processed

        // Stack stores (previous_result, sign_before_paren)
        stack<long> st;

        for (char c : s)
        {
            if (isdigit(c))
            {
                // 1. Parse multi-digit number
                number = number * 10 + (c - '0');
            }
            else if (c == '+')
            {
                // 2. Addition: Apply previous sign and number to result
                result += sign * number;
                number = 0; // Reset number
                sign = 1; // Set sign for the next number
            }
            else if (c == '-')
            {
                // 3. Subtraction: Apply previous sign and number to result
                result += sign * number;
                number = 0; // Reset number
                sign = -1;  // Set sign for the next number
            }
            else if (c == '(')
            {
                // 4. Start of Parenthesis: Save current state (result and sign)
                st.push(result);
                st.push(sign);

                // Reset context for the inner expression
                result = 0;
                sign = 1;
            }
            else if (c == ')')
            {
                // 5. End of Parenthesis:
                // First, incorporate the last number inside the current parenthesis
                result += sign * number;
                number = 0;

                // Pop the sign that was before the parenthesis
                int prevSign = (int)st.top();
                st.pop();

                // Pop the result accumulated before the parenthesis
                long prevRes = st.top();
                st.pop();

                // Merge: (result_before) + (sign_before) * (result_inside_paren)
                result = prevRes + prevSign * result;
            }
            // Spaces are ignored implicitly, or explicitly by adding: else if (c == ' ') continue;
        }

        // 6. After the loop, the last number needs to be applied
        result += sign * number;
        return (int)result;
    }
};

int main()
{
    Solution sol;

    // Example test cases
    string s1 = "1 + 1";
    cout << "Expression: " << s1 << "\nResult: " << sol.calculate(s1) << " (Expected: 2)\n"
         << endl;

    string s2 = " 2-1 + 2 ";
    cout << "Expression: " << s2 << "\nResult: " << sol.calculate(s2) << " (Expected: 3)\n"
         << endl;

    string s3 = "(1+(4+5+2)-3)+(6+8)";
    cout << "Expression: " << s3 << "\nResult: " << sol.calculate(s3) << " (Expected: 23)\n"
         << endl;

    string s4 = "10 + (3 - 5)";
    cout << "Expression: " << s4 << "\nResult: " << sol.calculate(s4) << " (Expected: 8)\n"
         << endl;

    string s5 = "- (3 + (4 + 5))"; // The implicit starting '+' is applied here.
    cout << "Expression: " << s5 << "\nResult: " << sol.calculate(s5) << " (Expected: -12)\n"
         << endl;

    string s6 = "(1)";
    cout << "Expression: " << s6 << "\nResult: " << sol.calculate(s6) << " (Expected: 1)\n"
         << endl;

    return 0;
}