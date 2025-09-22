/*
File: Lemonade_Change.cpp
Date: 2025-09-22 09:12

Problem: Lemonade Change
Link: https://leetcode.com/problems/lemonade-change/
Problem Statement: At a lemonade stand, each lemonade costs $5. Customers are paying 
with $5, $10, and $20 bills. You must provide correct change. You start with no money.
 Return true if you can provide change to all customers, or false otherwise.

-------------------------------------------------
❌ Brute Force
- Idea: This problem does not lend itself well to a brute-force approach. There are no 
  "combinations" to check, as the process is sequential. We must handle each transaction 
  as it comes, making the best choice at each step.
- Time complexity: Not applicable/Infeasible.
- Space complexity: Not applicable/Infeasible.
- Limitations: A recursive or exhaustive search would be pointless and over-complicated.

✅ Optimized Approach
- Idea: The most efficient approach is a greedy algorithm. We process customers one by one
  and keep a running count of the $5 and $10 bills we have on hand.
- Approach: A greedy algorithm.
- Algorithm:
  1. Initialize counters for the number of $5 bills and $10 bills to zero.
  2. Iterate through each customer's payment in the `bills` array.
  3. If the payment is $5, increment the count of $5 bills.
  4. If the payment is $10, we must provide $5 in change. Check if a $5 bill is available.
     If so, decrement the $5 bill count and increment the $10 bill count. If not, it's impossible
     to give change, so return `false`.
  5. If the payment is $20, we need to provide $15 in change. The greedy strategy is to use one $10
     bill and one $5 bill first, as $10 bills are less flexible than $5 bills for making smaller change.
     If this combination is available, use it. Otherwise, if we have at least three $5 bills, use them.
     If neither option is possible, return `false`. After giving change, increment the $20 bill count
     (though this is not strictly necessary as we don't need to give change for a $20 bill later, keeping
     a count of $5s and $10s is sufficient).
  6. If the loop completes without returning `false`, it means all customers were successfully served,
     so return `true`.
- Time complexity: O(N), where N is the number of customers, as we iterate through the `bills` vector once.
- Space complexity: O(1) as we only use a few integer variables to store the counts of $5 and $10 bills.

💡 Key Pattern:
- **Greedy Algorithms**: The problem has the greedy-choice property. At each step, making the locally
  optimal choice (using a $10 bill for change before $5 bills) leads to a globally optimal solution.
  This is because a $10 bill can only be used to make change for a $20 bill, whereas a $5 bill is more versatile.

ℹ️ Keywords:
- Greedy Algorithm, Change Making, LeetCode, Simulation

🗒️ Notes
- The greedy approach works because the denominations are chosen carefully. Specifically, for a $20 bill,
  giving change of $10 + $5 is always better than $5 + $5 + $5, because it conserves the more useful $5 bills.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Determines if it's possible to provide correct change for all customers.
     * @param bills A vector of integers representing the bills customers pay with.
     * @return true if all customers can be served with correct change, false otherwise.
     */
    bool lemonadeChange(vector<int> &bills)
    {
        int five_dollars = 0;
        int ten_dollars = 0;

        for (int payment : bills)
        {
            if (payment == 5)
            {
                five_dollars++;
            }
            else if (payment == 10)
            {
                if (five_dollars > 0)
                {
                    five_dollars--;
                    ten_dollars++;
                }
                else
                {
                    return false;
                }
            }
            else if (payment == 20)
            {
                if (ten_dollars > 0 && five_dollars > 0)
                {
                    ten_dollars--;
                    five_dollars--;
                }
                else if (five_dollars >= 3)
                {
                    five_dollars -= 3;
                }
                else
                {
                    return false;
                }
            }
        }

        return true;
    }
};

int main()
{
    Solution sol;

    // Example 1
    vector<int> bills1 = {5, 5, 5, 10, 20};
    cout << "Example 1: " << (sol.lemonadeChange(bills1) ? "true" : "false") << endl; // Expected: true

    // Example 2
    vector<int> bills2 = {5, 5, 10, 10, 20};
    cout << "Example 2: " << (sol.lemonadeChange(bills2) ? "true" : "false") << endl; // Expected: false

    return 0;
}