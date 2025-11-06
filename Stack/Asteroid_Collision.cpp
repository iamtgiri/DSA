/*
File: Asteroid_Collision.cpp
Date: 2025-11-06 11:15

Problem: Asteroid Collision

Link: https://leetcode.com/problems/asteroid-collision/description/

Problem Statement:
We are given an array of integers representing asteroids in a row. For each asteroid,
the absolute value represents its size, and the sign represents its direction: positive
means moving right, and negative means moving left. Find the state of the asteroids
after all collisions. All asteroids move at the same speed. If two asteroids meet,
the smaller one explodes. If both are the same size, both explode. Right-moving
asteroids never collide with other right-moving asteroids, and the same for left-moving.
Collisions only happen when a positive asteroid meets a negative one.

-------------------------------------------------
❌ Brute Force
- Idea: Simulate the movement of the asteroids time step by time step. Since speed is
  constant, collisions only occur between adjacent asteroids moving toward each other
  (i.e., a positive number followed by a negative number). After each collision, update
  the array, remove destroyed asteroids, and repeat the scan.
- Time complexity: O(N^2). In the worst case (e.g., [5, 5, 5, ..., -1]), one collision
  happens per step, requiring O(N) steps, and each step requires array modification
  and scanning, leading to O(N * N).
- Space complexity: O(1) additional space (if modifying the input array in place).
- Limitations: Inefficient due to continuous array modification (insertion/deletion)
  and repeated scans.

✅ Optimized Approachs
- Idea: This problem has the characteristics of a **Last-In, First-Out (LIFO)** system.
  When a left-moving asteroid (`< 0`) encounters a stream of right-moving asteroids
  (`> 0`), it will always collide with the **last** right-moving asteroid that has
  yet to be destroyed. This suggests using a **stack**.
- Approach: **Stack-based Simulation**.
- Algorithm:
  1. Initialize an empty stack `s` to hold the surviving asteroids encountered so far.
  2. Iterate through the input `asteroids` array from left to right.
  3. **Case 1: No collision possible.** If the current asteroid is positive (`> 0`),
     or if the stack is empty, or if the stack top is already moving left (`< 0`),
     push the current asteroid onto the stack.
  4. **Case 2: Potential collision.** If the current asteroid (`it`) is negative
     and the stack top (`s.top()`) is positive:
     a. **While loop:** While a collision is possible and the stack top is smaller
        than the current negative asteroid (i.e., `abs(it) > s.top()`), pop the
        smaller right-moving asteroid off the stack (it is destroyed).
     b. **Equality check:** If the stack is not empty and the sizes are equal
        (i.e., `abs(it) == s.top()`), pop the stack (both are destroyed). The current
        negative asteroid is also destroyed, so we `continue` to the next iteration.
     c. **Stack top wins:** If the stack is not empty and the stack top is larger
        (i.e., `abs(it) < s.top()`), the current negative asteroid is destroyed,
        and we do nothing (the stack top survives).
     d. **Stack empty/safe push:** If the stack becomes empty during the process,
        or if the stack top is negative, the current asteroid survives the gauntlet
        and is pushed onto the stack.
  5. After iterating, transfer the remaining elements from the stack to a result
     vector and reverse it to get the final order.
- Time complexity: **O(N)**. Each asteroid is pushed onto the stack at most once
  and popped from the stack at most once.
- Space complexity: **O(N)** to store the stack and the final result vector.

💡 Key Pattern:
- **Stack for Directional Simulation:** Use a stack when a new element's fate depends
  on interaction with the most recently stored, relevant element (in this case,
  the last right-moving asteroid).

ℹ️ Keywords:
- Stack, Simulation, Collision, LIFO.

🗒️ Notes
- The final step of reversing the elements popped from the stack is crucial
  because the stack holds the survivors in reverse order of their appearance.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Simulates asteroid collisions using a stack.
     * @param asteroids A vector of integers representing asteroid sizes and directions.
     * @return The vector of asteroids remaining after all collisions.
     */
    vector<int> asteroidCollision(vector<int> &asteroids)
    {
        stack<int> s;
        vector<int> ans;

        for (auto it : asteroids)
        {
            // Case 1: Right-moving asteroid, or no collision possible (stack empty or top is also left-moving).
            if (it > 0 || s.empty() || s.top() < 0)
            {
                s.push(it);
            }
            else
            {
                // Case 2: Left-moving asteroid (it < 0) meeting a right-moving asteroid (s.top() > 0).

                // Keep popping while the current left-moving asteroid is bigger and destroys the stack top.
                while (!s.empty() && s.top() > 0 && abs(it) > s.top())
                {
                    s.pop();
                }

                // Check the result of the collisions:

                // If they are equal size, both are destroyed.
                if (!s.empty() && s.top() > 0 && abs(it) == s.top())
                {
                    s.pop();
                    // Current 'it' is destroyed, so move to the next asteroid in the input.
                }
                // If the current asteroid survived the previous collisions (stack is empty or top is negative),
                // OR if the stack top won the collision (abs(it) < s.top()), the left-moving asteroid ('it') is destroyed.
                // If the stack top won (i.e., abs(it) < s.top()), we do nothing and move to the next 'it'.

                // Only push 'it' if it survived completely (i.e., collided with an empty stack or a left-moving asteroid)
                else if (s.empty() || s.top() < 0)
                {
                    s.push(it);
                }
            }
        }

        // Transfer the survivors from the stack to the result vector in the correct order.
        while (!s.empty())
        {
            ans.push_back(s.top());
            s.pop();
        }
        reverse(ans.begin(), ans.end());

        return ans;
    }
};

int main()
{
    Solution sol;

    cout << "--- Asteroid Collision Test Cases ---\n";

    // Test Case 1: Right-moving asteroid (5) meets smaller left-moving (-2). 5 survives.
    vector<int> asteroids1 = {5, 10, -5};
    vector<int> result1 = sol.asteroidCollision(asteroids1);
    cout << "Test 1 ([5, 10, -5]): Expected [5, 10], Got [";
    for (int i = 0; i < result1.size(); ++i)
        cout << result1[i] << (i == result1.size() - 1 ? "" : ", ");
    cout << "]\n";

    // Test Case 2: Equal collision. Both destroyed.
    vector<int> asteroids2 = {8, -8};
    vector<int> result2 = sol.asteroidCollision(asteroids2);
    cout << "Test 2 ([8, -8]): Expected [], Got [";
    for (int i = 0; i < result2.size(); ++i)
        cout << result2[i] << (i == result2.size() - 1 ? "" : ", ");
    cout << "]\n";

    // Test Case 3: Left-moving asteroid (-5) is bigger and destroys 10, then 5. (-5 survives)
    vector<int> asteroids3 = {10, 5, -5, -10};
    vector<int> result3 = sol.asteroidCollision(asteroids3);
    cout << "Test 3 ([10, 5, -5, -10]): Expected [-10], Got [";
    for (int i = 0; i < result3.size(); ++i)
        cout << result3[i] << (i == result3.size() - 1 ? "" : ", ");
    cout << "]\n";

    // Test Case 4: Complex collision chain
    vector<int> asteroids4 = {-2, -1, 1, 2};
    vector<int> result4 = sol.asteroidCollision(asteroids4);
    cout << "Test 4 ([-2, -1, 1, 2]): Expected [-2, -1, 1, 2], Got [";
    for (int i = 0; i < result4.size(); ++i)
        cout << result4[i] << (i == result4.size() - 1 ? "" : ", ");
    cout << "]\n";

    return 0;
}