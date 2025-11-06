/*
File: Ball_Collision.cpp
Date: 2025-10-26 15:31

Problem: Ball Collision
Link: URL (Similiar to LeetCode 735: Asteroid Collision)

Problem Statement:
There are `n` balls on a 1D line.
Each ball has:
    * a direction → `1` (right) or `-1` (left)
    * a strength → positive integer

When a ball moving right meets a ball moving left, they **collide**:
    * The ball with the **greater strength** survives.
    * If both have the **same strength**, both are destroyed.

Return the indices (0-based) of the balls that remain after all collisions — in ascending order.
-------------------------------------------------
❌ Brute Force
- Idea: Simulate time step by step. In each step, find all adjacent right-left
  pairs, resolve their collisions, and update the array of remaining balls.
- Time complexity: O(N^2). In the worst case, the simulation could run for
  N steps, with O(N) work per step.
- Space complexity: O(N) to store the state of the balls.
- Limitations: Inefficient due to quadratic time complexity.

✅ Optimized Approachs
- Idea: The only collisions occur between a ball moving right (stack top) and
  a ball moving left (current ball). This LIFO interaction is perfectly
  modeled by a stack.
- Approach: Stack-based simulation. The stack stores the indices of balls
  currently moving to the right that may collide later.
- Algorithm:
    1. Iterate through balls from left to right (index `i`).
    2. Maintain a stack of indices for surviving right-moving balls.
    3. If the current ball moves left (`-1`), repeatedly check for collisions
       with the stack top (a right-moving ball, `1`).
    4. Resolve collisions: pop the weaker ball; if strengths are equal, pop the
       stack top and destroy the current ball.
    5. If the current ball survives the collisions, push its index.
    6. After iteration, reverse the indices in the stack to get the correct order.
- Time complexity: O(N). Each ball index is pushed onto the stack at most once
  and popped at most once.
- Space complexity: O(N) for the stack and result vector.

💡 Key Pattern:
- **Stack for 1D Collision/Grouping:** Use a stack to track elements waiting for
  a potential future interaction (like right-moving balls waiting for a left-moving ball).

ℹ️ Keywords:
- Stack, Simulation, Collision, 1D Array, LIFO.

🗒️ Notes
- The final result must be sorted by index, requiring a reversal of the stack content.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Simulates 1D ball collisions and returns the indices of surviving balls.
     * @param direction Vector where 1 is right and -1 is left.
     * @param strength Vector of positive integer strengths.
     * @return Vector of 0-based indices of the surviving balls, in ascending order.
     */
    vector<int> findRemainingBalls(vector<int> &direction, vector<int> &strength)
    {
        // store indices of surviving balls
        stack<int> st;

        for (int i = 0; i < direction.size(); ++i)
        {
            bool destroyed = false;

            // Only potential collision if stack top moves right (1) and current moves left (-1)
            while (!st.empty() && direction[st.top()] == 1 && direction[i] == -1)
            {

                // Case 1: Stack top (right-mover) is weaker
                if (strength[st.top()] < strength[i])
                {
                    st.pop(); // right-mover destroyed

                    continue; // current (left-mover) continues checking previous balls
                }
                // Case 2: Strengths are equal
                else if (strength[st.top()] == strength[i])
                {
                    st.pop(); // both destroyed
                    destroyed = true;
                    break;
                }
                // Case 3: Stack top (right-mover) is stronger
                else // strength[st.top()] > strength[i]
                {
                    destroyed = true; // current (left-mover) destroyed
                    break;
                }
            }

            // If the current ball was not destroyed during the collision loop, push it.
            // Also pushes balls moving right (1) or balls moving left (-1) that
            // didn't collide because the stack was empty or top was moving left.
            if (!destroyed)
                st.push(i);
        }

        // collect remaining indices
        vector<int> survivors;
        while (!st.empty())
        {
            survivors.push_back(st.top());
            st.pop();
        }
        // The stack gives the indices in reverse order of processing (right to left).
        // Must reverse to return ascending index order (left to right).
        reverse(survivors.begin(), survivors.end());
        return survivors;
    }
};

// Helper function to print a vector
template <typename T>
void printVector(const vector<T> &vec)
{
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        cout << vec[i];
        if (i < vec.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << "]";
}

int main()
{
    Solution sol;

    cout << "--- Ball Collision Simulator ---\n";

    // Test Case 1: Simple collision, larger survives
    // [R10, L5] -> R10 survives (index 0)
    vector<int> dir1 = {1, -1};
    vector<int> str1 = {10, 5};
    vector<int> result1 = sol.findRemainingBalls(dir1, str1);
    cout << "Test 1: Dir=[1, -1], Str=[10, 5]\n";
    cout << "Result Indices: ";
    printVector(result1);
    cout << " (Expected: [0])\n";
    cout << "--------------------------------\n";

    // Test Case 2: Multi-collision, chain reaction
    // [R5, R10, L15] -> L15 destroys R10, then destroys R5. None remain.
    vector<int> dir2 = {1, 1, -1};
    vector<int> str2 = {5, 10, 15};
    vector<int> result2 = sol.findRemainingBalls(dir2, str2);
    cout << "Test 2: Dir=[1, 1, -1], Str=[5, 10, 15]\n";
    cout << "Result Indices: ";
    printVector(result2);
    cout << " (Expected: [])\n";
    cout << "--------------------------------\n";

    // Test Case 3: Equal strength, both destroyed
    // [R8, L8] -> both destroyed.
    vector<int> dir3 = {1, -1};
    vector<int> str3 = {8, 8};
    vector<int> result3 = sol.findRemainingBalls(dir3, str3);
    cout << "Test 3: Dir=[1, -1], Str=[8, 8]\n";
    cout << "Result Indices: ";
    printVector(result3);
    cout << " (Expected: [])\n";
    cout << "--------------------------------\n";

    // Test Case 4: Complex Scenario
    // [R5(0), L10(1), R2(2), L3(3), L4(4)]
    // i=0 (R5): Push 0. Stack: [0]
    // i=1 (L10): Collides with R5. L10 stronger. Pop 0. Stack: []. Push 1. Stack: [1]
    // i=2 (R2): Push 2. Stack: [1, 2]
    // i=3 (L3): Collides with R2. L3 stronger. Pop 2. Stack: [1].
    //          Collides with L10. No collision (same direction). Push 3. Stack: [1, 3]
    // i=4 (L4): Collides with L3. No collision. Push 4. Stack: [1, 3, 4]
    // Result: [1, 3, 4]
    vector<int> dir4 = {1, -1, 1, -1, -1};
    vector<int> str4 = {5, 10, 2, 3, 4};
    vector<int> result4 = sol.findRemainingBalls(dir4, str4);
    cout << "Test 4: Dir=[1, -1, 1, -1, -1], Str=[5, 10, 2, 3, 4]\n";
    cout << "Result Indices: ";
    printVector(result4);
    cout << " (Expected: [1, 3, 4])\n";
    cout << "--------------------------------\n";

    return 0;
}
