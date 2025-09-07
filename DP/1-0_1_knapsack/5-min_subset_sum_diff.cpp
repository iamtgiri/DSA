#include <iostream>
#include <vector>
using namespace std;

/*
Problem Statement:
-----------------
Given an array of positive integers, partition it into two subsets such that
the absolute difference of their sums is minimized.
Return that minimum difference.

Example:
--------
Input:
4
1 6 11 5

Output:
1

Explanation:
Partition into {1, 5, 6} and {11}, sums are 12 and 11, difference = 1.
*/

/*
Function: minSubsetSumDiff
--------------------------
Uses Dynamic Programming to solve the Minimum Subset Sum Difference problem.

- Let total sum = S.
- One subset has sum s1, the other has sum S - s1.
- Difference = |S - 2*s1|.
- Goal: Find maximum s1 <= S/2 that is achievable using subset sum.

DP approach:
------------
dp[i][j] = true if we can form sum 'j' using first 'i' elements.
*/
int minSubsetSumDiff(const vector<int>& arr) {
    int n = arr.size();

    // Step 1: Compute total sum
    int S = 0;
    for (int x : arr) S += x;

    // Step 2: Initialize DP table
    vector<vector<bool>> dp(n + 1, vector<bool>(S + 1, false));

    // Base case: with 0 elements, we can always form sum 0
    for (int i = 0; i <= n; ++i) dp[i][0] = true;

    // Step 3: Fill DP table
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= S; ++j) {
            if (arr[i - 1] <= j) {
                // Include arr[i-1] OR exclude it
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i - 1]];
            } else {
                // Can't include arr[i-1]
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // Step 4: Find the closest sum to S/2 that is achievable
    for (int j = S / 2; j >= 0; --j) {
        if (dp[n][j]) {
            return S - 2 * j;
        }
    }
    return S; // Safety return, though it never reaches here
}

/*
Main function:
--------------
Reads input from stdin.
First line: n (size of array)
Second line: n integers (array elements)
*/
int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    cout << minSubsetSumDiff(arr) << endl;
    return 0;
}
