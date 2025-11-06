/*
File: Evaluate_Reverse_Polish_Notation.cpp
Date: 2025-11-06 10:56

Problem: Evaluate Reverse Polish Notation
Link: https://leetcode.com/problems/evaluate-reverse-polish-notation/description/

Problem Statement:
Evaluate the value of an arithmetic expression in Reverse Polish Notation (RPN).
Valid operators are +, -, *, and /. Operands can be integers. The division operation
should truncate toward zero.

-------------------------------------------------
❌ Brute Force
- Idea: Avoid using the stack data structure. Instead, repeatedly scan the array
  to find the first operator. Once found, perform the operation on the two preceding
  operands, remove the three tokens, and insert the result back into the array.
  Repeat until the array has only one element.
- Time complexity: O(N-squared). We might perform O(N) operations, and each operation
  (deletion and insertion in the middle of the array/vector) requires shifting the
  remaining O(N) elements, leading to O(N * N).
- Space complexity: O(1) additional space if performed in-place on the input vector (ignoring recursion/call stack).
- Limitations: Extremely inefficient for an inherently sequential and simple problem.
  It wastes time on data rearrangement (shifting) that is unnecessary with a stack.

✅ Optimized Approachs
- Idea: The **Last-In, First-Out (LIFO)** principle of a **stack** is the perfect
  match for Reverse Polish Notation, where operators always apply to the two most
  recently encountered operands.
- Approach: **Stack-based Evaluation**.
- Algorithm:
  1. Iterate through the tokens from left to right.
  2. If the token is a number (operand), push it onto the stack.
  3. If the token is an operator (+, -, *, /), pop the second operand ('b'), pop the
     first operand ('a'), calculate 'a operator b', and push the result back onto the stack.
  4. The division rule (truncating toward zero) is handled naturally by C++ integer division.
  5. The final result is the single remaining element on the stack.
- Time complexity: **O(N)**, where N is the number of tokens. Every token is processed
  exactly once, and all stack operations (push, pop) are O(1).
- Space complexity: **O(N)**. In the worst case, the stack stores approximately N/2 + 1
  operands before the first operator is encountered.

💡 Key Pattern:
- **Stack for Postfix/RPN:** Reverse Polish Notation (postfix) inherently requires a
  stack for efficient evaluation because operators must access the two most recent
  elements pushed.

ℹ️ Keywords:
- Stack, Reverse Polish Notation (RPN), Postfix Notation, LIFO, Expression Evaluation.

🗒️ Notes
- Used `long long` for the stack elements (`st.push(stoll(s))`, `long long b`, etc.)
  to safely handle intermediate results, as the product of two 100-sized integers
  can exceed the capacity of a standard 32-bit `int`, preventing potential overflow.
  The final result is cast back to `int` as per problem constraints.
- Need to be careful with the order of operands when popping: the first pop is the
  second operand ('b'), and the second pop is the first operand ('a').
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Evaluates an arithmetic expression given in Reverse Polish Notation.
     * @param tokens A vector of strings representing the RPN expression.
     * @return The final integer result of the expression.
     */
    int evalRPN(vector<string> &tokens)
    {
        stack<long long> st;

        for (string &s : tokens)
        {
            // Check if the token is a number. Numbers can be multi-digit and negative.
            // isdigit(s[0]) handles positive numbers, and size() > 1 covers negative
            // numbers (like "-10") and positive multi-digit numbers (like "42").
            if (s.size() > 1 || isdigit(s[0]))
            {
                st.push(stoll(s));
            }
            else
            {
                // It is an operator. Pop two operands.
                long long b = st.top(); // Second operand
                st.pop();
                long long a = st.top(); // First operand
                st.pop();

                // Perform the operation and push the result
                if (s == "+")
                    st.push(a + b);
                else if (s == "-")
                    st.push(a - b);
                else if (s == "*")
                    st.push(a * b);
                else
                    st.push(a / b); // Integer division truncates toward zero naturally in C++
            }
        }
        // The final result is the single remaining element on the stack
        return (int)st.top();
    }
};

int main()
{
    Solution sol;

    cout << "--- Evaluate Reverse Polish Notation Test Cases ---\n";

    // Test Case 1: Example from problem: 2 1 + 3 * -> (2 + 1) * 3 = 9
    vector<string> tokens1 = {"2", "1", "+", "3", "*"};
    cout << "Test 1 (2 1 + 3 *): Expected 9, Got " << sol.evalRPN(tokens1) << endl;

    // Test Case 2: Example 2: 4 13 5 / + -> 4 + (13 / 5) = 4 + 2 = 6
    vector<string> tokens2 = {"4", "13", "5", "/", "+"};
    cout << "Test 2 (4 13 5 / +): Expected 6, Got " << sol.evalRPN(tokens2) << endl;

    // Test Case 3: Complex Example
    vector<string> tokens3 = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
    // (10 * (6 / ( (9 + 3) * -11 ) ) ) + 17 + 5
    // (10 * (6 / ( 12 * -11 ) ) ) + 22
    // (10 * (6 / -132)) + 22 -> (6 / -132) = 0 (truncates toward zero)
    // (10 * 0) + 22 = 22
    cout << "Test 3 (Complex): Expected 22, Got " << sol.evalRPN(tokens3) << endl;

    return 0;
}