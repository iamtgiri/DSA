/*
File: Prefix_Evaluation.cpp
Date: 2025-11-06 11:11

Problem: Prefix Evaluation
Link: https://www.geeksforgeeks.org/problems/prefix-evaluation/1

Problem Statement:
Given an array of strings representing a Prefix (Polish) Notation expression,
evaluate its result. The expression includes operands (integers) and operators
(+, -, *, /, ^).

-------------------------------------------------
❌ Brute Force
- Idea: Avoid using a stack. Repeatedly scan the array from the right to locate
  the first operator token. Once found, the two tokens immediately following it
  must be its operands. Replace the three tokens (operator, operand1, operand2)
  with the result in the array, and shift the remaining elements. Repeat until
  only one token remains.
- Time complexity: O(N^2). We perform up to O(N) operations, and each operation
  requires scanning and potentially shifting O(N) elements in the array.
- Space complexity: O(1) additional space (if modifying the input array in place).
- Limitations: Inefficient due to excessive array element shifting and redundant scanning.

✅ Optimized Approachs
- Idea: **Prefix Notation** (operator followed by operands, e.g., `+ A B`) is naturally
  evaluated using a stack, but requires processing the expression in **reverse** order
  (right-to-left) to respect the LIFO principle. When processed in reverse, the prefix
  expression behaves exactly like a postfix expression.
- Approach: **Stack-based Evaluation with Reverse Iteration**.
- Algorithm:
  1. Iterate through the `expr` array from **right to left** (index `N-1` down to `0`).
  2. If the current token is an **operand** (number), push its value onto the stack.
  3. If the current token is an **operator** (+, -, *, / etc.):
     a. Pop the first operand from the stack (let's call it `a`).
     b. Pop the second operand from the stack (let's call it `b`).
     c. Calculate the result of `a operator b`.
     *Note: Since we are iterating backward, the first element popped ('a') corresponds
     to the first operand in the prefix structure, and the second element popped ('b')
     corresponds to the second operand.*
     d. Push the result back onto the stack.
  4. The final result is the single element left on the stack.
- Time complexity: **O(N)**, where N is the number of tokens. Every token is visited
  and processed exactly once, and all stack operations are O(1).
- Space complexity: **O(N)** for the stack to store intermediate results.

💡 Key Pattern:
- **Symmetry of Polish Notations:** Prefix (operator first) and Postfix (operator last)
  are structurally symmetric. Evaluating a **Prefix** expression from **Right-to-Left** is algorithmically identical to evaluating a **Postfix** expression from **Left-to-Right**.
  Both require a stack.

ℹ️ Keywords:
- Stack, Prefix Notation, Polish Notation, LIFO, Reverse Iteration, Expression Evaluation.

🗒️ Notes
- Used `long long` for the stack elements to prevent overflow, as intermediate products
  (especially with multiplication) can easily exceed the capacity of a standard 32-bit `int`.
- The `safeDiv` function implements **floor division**, which is crucial if the problem
  requires results to be rounded down towards negative infinity, unlike C++'s default
  truncation towards zero for negative numbers.
- The power operator (`^`) is handled using `pow()`.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Helper function for safe division (floor division).
     * @param a The numerator (operand 1).
     * @param b The denominator (operand 2).
     * @return The result of floor(a / b).
     */
    long long safeDiv(long long a, long long b)
    {
        // Implements floor division: result is rounded towards negative infinity.
        long long q = a / b, r = a % b;
        if (r != 0 && ((a < 0) ^ (b < 0)))
            q -= 1;
        return q;
    }

    /**
     * @brief Evaluates an expression given in Prefix (Polish) Notation by iterating backward.
     * @param expr A vector of strings representing the Prefix expression.
     * @return The final integer result of the expression.
     */
    int evaluatePrefix(vector<string> &expr)
    {
        stack<long long> st;

        // Iterate from right to left
        for (int i = (int)expr.size() - 1; i >= 0; --i)
        {
            string &s = expr[i];

            // 1. Detect and handle numbers (operands)
            // Checks for multi-digit numbers or if the first character is a digit
            // This detection logic is crucial for handling negative numbers correctly.
            bool is_number = true;
            try
            {
                size_t idx;
                stoll(s, &idx);
                if (idx != s.size())
                    is_number = false; // Not a complete number
            }
            catch (const std::invalid_argument &)
            {
                is_number = false;
            }
            catch (const std::out_of_range &)
            {
                is_number = true; // Still a number, but potentially large
            }

            if (is_number)
            {
                st.push(stoll(s));
            }
            else
            {
                // 2. Handle operators

                // Need at least two operands
                if (st.size() < 2)
                    return 0; // Invalid expression

                // Pop operands: a is the first operand, b is the second
                long long a = st.top();
                st.pop();
                long long b = st.top();
                st.pop();

                // Perform operation: (a operator b)
                if (s == "+")
                    st.push(a + b);
                else if (s == "-")
                    st.push(a - b);
                else if (s == "*")
                    st.push(a * b);
                else if (s == "/")
                    st.push(safeDiv(a, b)); // Using floor division
                else if (s == "^")
                    st.push((long long)pow(a, b));
                else
                    return 0; // Unrecognized operator
            }
        }

        // The result is the final element on the stack
        return st.empty() ? 0 : (int)st.top();
    }
};

int main()
{
    Solution sol;

    cout << "--- Prefix Evaluation Test Cases ---\n";

    // Test Case 1: Example from GFG: * + 2 3 4 -> (2 + 3) * 4 = 20
    vector<string> expr1 = {"*", "+", "2", "3", "4"};
    cout << "Test 1 (* + 2 3 4): Expected 20, Got " << sol.evaluatePrefix(expr1) << endl;

    // Test Case 2: - * 2 3 4 -> (2 * 3) - 4 = 2
    vector<string> expr2 = {"-", "*", "2", "3", "4"};
    cout << "Test 2 (- * 2 3 4): Expected 2, Got " << sol.evaluatePrefix(expr2) << endl;

    // Test Case 3: / 10 2 -> 10 / 2 = 5
    vector<string> expr3 = {"/", "10", "2"};
    cout << "Test 3 (/ 10 2): Expected 5, Got " << sol.evaluatePrefix(expr3) << endl;

    // Test Case 4: ^ 2 3 -> 2 ^ 3 = 8
    vector<string> expr4 = {"^", "2", "3"};
    cout << "Test 4 (^ 2 3): Expected 8, Got " << sol.evaluatePrefix(expr4) << endl;

    // Test Case 5: Complex with negative number: * + -1 5 10 -> (-1 + 5) * 10 = 40
    vector<string> expr5 = {"*", "+", "-1", "5", "10"};
    cout << "Test 5 (* + -1 5 10): Expected 40, Got " << sol.evaluatePrefix(expr5) << endl;

    return 0;
}