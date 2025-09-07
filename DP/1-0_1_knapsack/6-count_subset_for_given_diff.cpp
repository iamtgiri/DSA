#include <iostream>
#include <vector>
using namespace std;

/*
Problem Statement:
-----------------
You are given an array of positive integers and a target difference `diff`.
Count the number of ways to partition the array into two subsets S1 and S2 such that:

    sum(S1) - sum(S2) = diff

Example:
--------
Input:
4 1
1 1 2 3

Output:
3

Explanation:
Subsets with difference = 1 are:
- {1, 3} and {1, 2}
- {3} and {1, 1, 2}
- {1, 1, 3} and {2}
*/

/*
Function: countSubsetGivenDiff
------------------------------
Uses Dynamic Programming to count subsets with given difference.

- Equation:
    s1 - s2 = diff
    s1 + s2 = S   (total sum)
  => s1 = (S + diff)/2

So the problem reduces to: count subsets with sum = (S + diff)/2
*/
int countSubsetGivenDiff(const vector<int>& arr, int diff) {
    int n = arr.size();
    int S = 0;
    for (int x : arr) S += x;

    // If (S + diff) is odd or diff > S, no solution
    if ((S + diff) % 2 != 0 || diff > S) return 0;

    int target = (S + diff) / 2;

    // DP table: dp[i][j] = number of ways to form sum j using first i elements
    vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));

    // Base case: sum 0 can always be formed with empty subset
    for (int i = 0; i <= n; ++i) dp[i][0] = 1;

    // Fill DP
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= target; ++j) {
            if (arr[i - 1] <= j) {
                dp[i][j] = dp[i - 1][j] + dp[i - 1][j - arr[i - 1]];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[n][target];
}

/*
Main function:
--------------
Input format:
n diff
arr[0] arr[1] ... arr[n-1]

Example:
4 1
1 1 2 3

Output:
3
*/

int main() {
    int n, diff;
    cin >> n >> diff;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i];

    cout << countSubsetGivenDiff(arr, diff) << endl;

    return 0;
}
