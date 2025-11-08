/*
File: Get_min_at_pop.cpp
Date: 2025-11-08 18:24

Problem: Get min at pop
Link: https://www.geeksforgeeks.org/problems/get-min-at-pop/1

Problem Statement:
Given a stack, print the minimum element present in the stack every time an element is popped.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: For every pop operation, iterate through all remaining elements in the main stack
  to find the new minimum.
- Time complexity: O(N^2) total time (O(N) for each of the N pops).
- Space complexity: O(1) auxiliary space (excluding the main stack).
- Limitations: Inefficient due to repeated linear scans.

Current/Optimized Approachs
- Idea: Maintain the running minimum value associated with the main stack's elements in
  an auxiliary data structure so that retrieval is O(1).
- Approach: **Auxiliary Stack (The Min Stack Pattern)**
- Algorithm:
  1. **Main Stack (`st`):** Stores the actual data elements.
  2. **Auxiliary Stack (`minStack`):** Stores the minimum value encountered *up to and including* the element at the corresponding position in the main stack.
     - When pushing a new element `x` to `st`:
       - Push `x` to `st`.
       - Push `min(x, minStack.top())` to `minStack` (if `minStack` is not empty), otherwise just push `x`.
  3. **During Pop:**
     - The minimum element for the current state is always `minStack.top()`.
     - Pop the element from `st` and pop the minimum tracker from `minStack`.
- Time complexity: O(N) total for N pushes/pops (O(1) per operation).
- Space complexity: O(N) (Two stacks storing up to N elements each in the worst case).

💡 Key Pattern:
- **Auxiliary Data Structure:** Augmenting a data structure (like a stack) with a second,
  parallel structure (like another stack or an array) to pre-calculate or track metadata
  (like min/max, frequencies, etc.) for O(1) lookups.

ℹ️ Keywords:
- Stack, Auxiliary Stack, Min Stack, Prefix Minimum, LIFO.

🗒️ Notes
- The provided function signature forces the minimum tracking to be done inside `_getMinAtPop`
  by rebuilding the state, as seen in the implemented solution. In a standard class,
  the tracking would be done directly during the `_push` method.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Pushes elements of an array onto a stack. (Provided by problem structure)
     * @param arr The array of elements to push.
     * @param n The size of the array.
     * @return The stack containing the elements.
     */
    stack<int> _push(int arr[], int n)
    {
        stack<int> st;
        for (int i = 0; i < n; ++i)
            st.push(arr[i]);
        return st;
    }

    /**
     * @brief Prints the minimum value in the stack each time an element is popped.
     * * This function reconstructs the necessary minimum tracking structure before simulating pops.
     * * @param s The stack (passed by value to allow popping without affecting the external stack).
     */
    void _getMinAtPop(stack<int> s)
    {
        // --- Step 1 & 2: Get elements in insertion order (bottom to top) ---
        // Since 's' is the result of '_push', the top is the last element inserted.
        // We need the sequence from first inserted to last inserted to calculate prefix mins.

        stack<int> reversed_s; // Contains elements in insertion order (first to last)
        while (!s.empty())
        {
            reversed_s.push(s.top());
            s.pop();
        }

        // --- Step 3: Build the Auxiliary Stack (Min Stack Pattern) ---
        stack<int> minStack;

        // Iterate through elements in insertion order
        while (!reversed_s.empty())
        {
            int current_val = reversed_s.top();
            reversed_s.pop();

            if (minStack.empty())
            {
                // First element is the minimum so far
                minStack.push(current_val);
            }
            else
            {
                // Store the minimum of the current value and the previous minimum
                minStack.push(min(current_val, minStack.top()));
            }
        }

        // --- Step 4: Simulate Pop and Print Min ---
        // Now minStack.top() corresponds to the minimum when the main stack's top is popped.

        while (!minStack.empty())
        {
            cout << minStack.top() << " ";
            minStack.pop();
        }
        cout << endl; // Newline for clean output
    }
};

int main()
{
    Solution sol;

    // Test Case 1
    int arr1[] = {1, 2, 3, 4, 5}; // Pushed in order: 1, 2, 3, 4, 5
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    stack<int> st1 = sol._push(arr1, n1);
    cout << "Input Array: [1, 2, 3, 4, 5]" << endl;
    cout << "Min at Pop: ";
    sol._getMinAtPop(st1); // Expected output: 1 1 1 1 1 (Min at each stage is always 1)

    // Test Case 2
    int arr2[] = {10, 5, 15, 2, 20}; // Pushed in order: 10, 5, 15, 2, 20
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    stack<int> st2 = sol._push(arr2, n2);
    cout << "\nInput Array: [10, 5, 15, 2, 20]" << endl;
    cout << "Min at Pop: ";
    // Pop 20 (Min=2), Pop 2 (Min=2), Pop 15 (Min=5), Pop 5 (Min=5), Pop 10 (Min=10)
    sol._getMinAtPop(st2); // Expected output: 2 2 5 5 10

    // Test Case 3: Decreasing order
    int arr3[] = {5, 4, 3, 2, 1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    stack<int> st3 = sol._push(arr3, n3);
    cout << "\nInput Array: [5, 4, 3, 2, 1]" << endl;
    cout << "Min at Pop: ";
    // Pop 1 (Min=1), Pop 2 (Min=2), Pop 3 (Min=3), Pop 4 (Min=4), Pop 5 (Min=5)
    sol._getMinAtPop(st3); // Expected output: 1 2 3 4 5

    return 0;
}