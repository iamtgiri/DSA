/*
File: Candy.cpp
Date: 2025-09-22 15:49

Problem: Candy
Link: https://leetcode.com/problems/candy/

Problem Statement:
There are n children standing in a line. Each child is assigned a rating value
given in the integer array ratings. You are giving candies to these children
subjected to the following requirements: Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors. Return the
minimum number of candies you need to have to distribute the candies to the
children.

Example 1:
Input: ratings = [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2
candies respectively.

Example 2:
Input: ratings = [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1
candies respectively. The third child gets 1 candy because it satisfies the above
two conditions.
-------------------------------------------------
❌ Brute Force
- Idea: A brute-force solution would be to recursively assign candies, trying all
possible distributions that satisfy the conditions. This would involve a complex
and highly inefficient search.
- Time complexity: Exponential. Infeasible.
- Space complexity: O(N) for recursion stack.
- Limitations: This is not a practical approach.

✅ Optimized Approachs
- Idea: The problem requires satisfying two independent conditions simultaneously:
a child's candy count must be greater than their left neighbor's if they have a
higher rating, and also greater than their right neighbor's if they have a higher
rating. We can handle these two conditions with two separate greedy passes.
- Approach: A two-pass greedy algorithm.
- Algorithm:
  1. Initialize a `candies` array (or two separate arrays) of size `n`, with each
  element set to 1, since every child must have at least one candy.
  2. **First Pass (Left-to-Right):** Iterate from the second child to the last.
  If the current child's rating is greater than their left neighbor's, update
  their candy count to be one more than the neighbor's. This pass ensures the
  "higher rating gets more candy than left neighbor" condition.
  3. **Second Pass (Right-to-Left):** Iterate from the second-to-last child to the
  first. If the current child's rating is greater than their right neighbor's,
  update their candy count to be the maximum of its current value and one more
  than the right neighbor's. Taking the maximum ensures both conditions are met.
  4. After both passes, the total number of candies is the sum of all elements in
  the `candies` array.
- Time complexity: O(N) because we perform two passes over the array.
- Space complexity: O(N) to store the intermediate results (the `left` and `right`
arrays). Can be optimized to O(1) by using a single pass and additional variables.

💡 Key Pattern:
- **Two-Pass Greedy**: This pattern is useful for problems where conditions are
directional. By solving for one direction first (e.g., left-to-right) and then
the other (e.g., right-to-left), we can satisfy all constraints. The final answer
is often a combination (e.g., `max()`) of the results from both passes.

ℹ️ Keywords:
- Greedy Algorithm, Two-Pass, Array, Rating, Dynamic Programming, Single Pass

🗒️ Notes
- The logic is a clever way to avoid complex recursion. The problem seems
interdependent, but the two-pass approach decouples the dependencies, allowing
for a linear-time solution.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Calculates the minimum number of candies required.
     * @param ratings A vector of integers representing the ratings of children.
     * @return The minimum number of candies to distribute.
     */
    int candy(vector<int> &ratings)
    {
        int n = ratings.size();
        if (n <= 1)
        {
            return n;
        }

        // Initialize two arrays to store candy counts from each direction.
        vector<int> left_pass(n, 1), right_pass(n, 1);

        // First Pass: Left-to-right
        // Ensures each child with a higher rating gets more than their left neighbor.
        for (int i = 1; i < n; ++i)
        {
            if (ratings[i] > ratings[i - 1])
            {
                left_pass[i] = left_pass[i - 1] + 1;
            }
        }

        // Second Pass: Right-to-left
        // Ensures each child with a higher rating gets more than their right neighbor.
        for (int i = n - 2; i >= 0; --i)
        {
            if (ratings[i] > ratings[i + 1])
            {
                right_pass[i] = right_pass[i + 1] + 1;
            }
        }

        // Combine results and calculate total candies
        // For each child, the final candy count is the maximum of the two passes.
        int total_candies = 0;
        for (int i = 0; i < n; ++i)
        {
            total_candies += max(left_pass[i], right_pass[i]);
        }

        return total_candies;
    }
};

int main()
{
    Solution sol;

    // Example 1
    vector<int> ratings1 = {1, 0, 2};
    cout << "Example 1: Total candies = " << sol.candy(ratings1) << endl; // Expected: 5

    // Example 2
    vector<int> ratings2 = {1, 2, 2};
    cout << "Example 2: Total candies = " << sol.candy(ratings2) << endl; // Expected: 4

    return 0;
}