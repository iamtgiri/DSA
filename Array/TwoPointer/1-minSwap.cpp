/*
Problem Statement:
-----------------
A circular row of seats is arranged for a meeting, where each seat is either 
occupied (1) or empty (0). Your task is to determine the minimum number of 
swaps needed to rearrange people so that all occupied seats (1's) are grouped 
together in a single contiguous block of seats.

- A swap means choosing two people sitting in different seats and exchanging 
  their positions.
- Since the seats are arranged in a circle, the first and last seats are 
  considered adjacent.

Examples:
---------
Input:
7
0 1 0 1 1 0 0
Output:
1

Input:
9
0 1 1 1 0 0 1 1 0
Output:
2

Input:
5
1 1 0 0 1
Output:
0
*/

#include <bits/stdc++.h>
using namespace std;

int minSwaps(vector<int>& seats) {
    int n = seats.size();

    // Count how many 1s exist in the array
    int totalOnes = 0;
    for (int val : seats) {
        if (val == 1) ++totalOnes;
    }

    // Edge cases: no 1s or all 1s
    if (totalOnes == 0 || totalOnes == n) return 0;

    // Duplicate the array to handle circular case
    vector<int> extended(seats.begin(), seats.end());
    extended.insert(extended.end(), seats.begin(), seats.end());

    // Initialize first window
    int zerosInWindow = 0;
    for (int i = 0; i < totalOnes; ++i) {
        if (extended[i] == 0) ++zerosInWindow;
    }

    int minSwapsNeeded = zerosInWindow;

    // Sliding window across the extended array
    for (int left = 0, right = totalOnes; right < n + totalOnes; ++left, ++right) {
        if (extended[right] == 0) ++zerosInWindow;  // new element enters
        if (extended[left] == 0) --zerosInWindow;   // old element leaves
        minSwapsNeeded = min(minSwapsNeeded, zerosInWindow);
    }

    return minSwapsNeeded;
}

int main() {
    int n;
    cout << "Enter array size:";
    cin >> n;

    cout <<"Enter array elements";
    vector<int> seats(n);
    for (int i = 0; i < n; i++) {
        cin >> seats[i];
    }

    cout << minSwaps(seats) << "\n";

    return 0;
}
