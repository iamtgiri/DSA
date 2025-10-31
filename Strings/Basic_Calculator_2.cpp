/*
File: Basic_Calculator_2.cpp
Date: 2025-10-31 23:10

Problem: Basic Calculator II
Link: https://leetcode.com/problems/basic-calculator-ii/description/

Problem Statement:
Given a string s which represents an expression, evaluate this expression
and return its value. Integer division should truncate toward zero.
You may assume that the given expression is always valid. All intermediate
results will be in the range [-2^31, 2^31 - 1].

-------------------------------------------------
❌ Brute Force
- Idea: Convert the infix expression to postfix (Reverse Polish Notation) first,
  and then evaluate the postfix expression. This requires two full passes and
  extra logic for the conversion step.
- Time complexity: O(N), where N is the length of the string (for two passes).
- Space complexity: O(N) for storing the postfix expression and the stack used for evaluation.
- Limitations: More complex implementation (two distinct phases) than the single-pass stack method.

✅ Optimized Approachs
- Idea: Use a **single pass** and a **stack** to evaluate the expression while
  respecting operator precedence. Multiplication and division are executed immediately
  when encountered, while addition/subtraction results (signed numbers) are pushed
  onto the stack to be summed up at the end.
- Approach: **Single Pass with Stack (Precedence Handling)**.
- Algorithm:
    1. **Initialization:** Use a `stack<int>` to store intermediate numbers. Use `long num = 0`
       to build multi-digit numbers, and `char sign = '+'` to track the last encountered operator.
    2. **Iteration:** Iterate through the string `s`.
    3. **Number Building:** If `s[i]` is a digit, continue building `num = num * 10 + digit`.
    4. **Operator Handling:** If `s[i]` is an operator (`+`, `-`, `*`, `/`) or the end of the string,
       process the accumulated `num` based on the `sign` of the *previous* operator:
        - If `sign == '+'`: Push `num` onto the stack.
        - If `sign == '-'`: Push `-num` onto the stack.
        - If `sign == '*'`: Pop the top, multiply by `num`, and push the result back.
        - If `sign == '/'`: Pop the top, divide by `num`, and push the result back.
    5. **Update:** Update `sign` to `s[i]`, and reset `num = 0`.
    6. **Final Summation:** After the loop, the stack contains all intermediate results
       (signed terms). Sum all elements in the stack to get the final result.
- Time complexity: **O(N)**, where N is the length of the string, as we only iterate once.
- Space complexity: **O(N)** in the worst case (e.g., `1+1+1...`), as the stack stores up to $N/2$ terms.

💡 Key Pattern:
- **Operator Precedence in Single Pass:** Use a stack to defer addition/subtraction until the end, while immediately executing higher precedence operations (`*`, `/`) by modifying the stack's top element.

ℹ️ Keywords:
- Stack, Operator Precedence, String Parsing, Expression Evaluation.

🗒️ Notes
- Using `long` for `num` prevents potential overflow during number construction, though the final result fits in an `int`.
- The condition `i == n - 1` is crucial to process the last number/operation in the string.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Evaluates an arithmetic expression string with +, -, *, / using a single-pass stack approach.
     * @param s The expression string.
     * @return The result of the calculation.
     */
    int calculate(string s)
    {
        // Stack to store intermediate signed terms (results of high-precedence ops)
        stack<long> st;
        long num = 0;
        char sign = '+';
        int n = s.size();

        for (int i = 0; i < n; ++i)
        {
            char c = s[i];

            // 1. Build multi-digit number
            if (isdigit(c))
            {
                num = num * 10 + (c - '0');
            }

            // 2. Process operator or end of string
            // This condition triggers when an operator or space is hit, or we reach the end of the string
            if ((!isdigit(c) && !isspace(c)) || i == n - 1)
            {

                // Process the accumulated 'num' based on the PREVIOUSLY stored 'sign'
                if (sign == '+')
                {
                    st.push(num);
                }
                else if (sign == '-')
                {
                    st.push(-num);
                }
                else if (sign == '*')
                {
                    long top = st.top();
                    st.pop();
                    st.push(top * num);
                }
                else if (sign == '/')
                {
                    long top = st.top();
                    st.pop();
                    // Integer division truncates towards zero (C++ handles this by default for positive/negative)
                    st.push(top / num);
                }

                // Update the sign for the NEXT number and reset current number
                sign = c;
                num = 0;
            }
        }

        // 3. Final summation
        long result = 0;
        while (!st.empty())
        {
            result += st.top();
            st.pop();
        }

        return (int)result;
    }
};

// Helper function to run tests
void runTest(Solution &sol, const string &s, int expected)
{
    int result = sol.calculate(s);
    cout << "Expression: \"" << s << "\" | Result: " << result
         << " | Expected: " << expected;
    if (result == expected)
    {
        cout << " (PASS)\n";
    }
    else
    {
        cout << " (FAIL)\n";
    }
}

int main()
{
    Solution sol;

    cout << "--- Basic Calculator II ---\n";

    // Test Case 1: Mixed operations, spacing
    runTest(sol, "3+2*2", 7);
    // Calculation: 3 + (2*2) = 7

    // Test Case 2: Division and subtraction
    runTest(sol, " 3/2 ", 1);
    // Calculation: 3/2 = 1 (truncation)

    // Test Case 3: Multiple operators and multi-digit numbers
    runTest(sol, " 3+5 / 2 - 10 * 3", 3 + 2 - 30); // 3 + (5/2=2) - (10*3=30) = -25
    runTest(sol, " 3+5 / 2 - 10 * 3", -25);

    // Test Case 4: Leading spaces
    runTest(sol, " 12 + 4 * 2 - 3 / 3", 19);
    // Calculation: 12 + (4*2=8) - (3/3=1) = 20 - 1 = 19

    // Test Case 5: Complex division and subtraction
    runTest(sol, " 50-2*10/4+1", 50 - 5 + 1); // 50 - ((2*10)/4=5) + 1 = 46
    runTest(sol, " 50-2*10/4+1", 46);

    // Test Case 6: Negative result and single number
    runTest(sol, "-1", -1);

    return 0;
}
