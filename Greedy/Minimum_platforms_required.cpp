/*
File: Minimum_platforms_required.cpp
Date: 2025-09-22 11:19

Problem: Minimum number of platforms required for a railway
Link: https://www.geeksforgeeks.org/problems/minimum-platforms-1587115620/1

Problem Statement: 
Given the arrival and departure times of all trains that arrive at a railway station, 
find the minimum number of platforms required so that no train has to wait.

-------------------------------------------------
❌ Brute Force
- Idea: Check at every single moment how many trains are at the station (arrived but not departed). 
- Time complexity: O(N^2) if we check each interval against all others.
- Space complexity: O(1)
- Limitations: Not efficient for large N.

✅ Optimized Approach
- Idea: Greedy + Two pointers
- Approach:
  1. Sort arrival and departure times.
  2. Use two pointers to traverse arrivals and departures.
  3. Keep track of available platforms freed by departing trains.
  4. If a train arrives and a platform is free, use it; otherwise, allocate a new platform.
  5. Update total platforms needed dynamically.
- Algorithm:
  - Sort `arr` and `dep`.
  - Initialize counters: `totalPlatforms = 0`, `availablePlatforms = 0`.
  - Traverse with two pointers `a` and `d`.
      - If `arr[a] <= dep[d]`: 
          - Allocate platform (use available if any, else increment totalPlatforms).
          - Move to next arrival (`++a`).
      - Else:
          - Free a platform (`++availablePlatforms`) and move to next departure (`++d`).
- Time complexity: O(N log N) for sorting + O(N) for traversal → O(N log N)
- Space complexity: O(1) extra (besides input arrays)

💡 Key Pattern:
- Greedy Algorithm
- Two Pointers / Sweep Line

Keywords:
- Greedy, Interval Scheduling, Sorting, Platforms, Two Pointers

-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Computes the minimum number of platforms required for a railway station.
     * @param arr Arrival times of trains.
     * @param dep Departure times of trains.
     * @return Minimum number of platforms needed.
     */
    int minPlatform(vector<int> &arr, vector<int> &dep)
    {
        int n = arr.size();

        // Sort arrival and departure times
        sort(arr.begin(), arr.end());
        sort(dep.begin(), dep.end());

        int totalPlatforms = 0;     // Total platforms required
        int availablePlatforms = 0; // Platforms freed by departing trains
        int a = 0, d = 0;

        while (a < n)
        {
            if (arr[a] <= dep[d])
            {
                // Train arrives
                if (availablePlatforms > 0)
                    --availablePlatforms; // Use a freed platform
                else
                    ++totalPlatforms;     // Allocate a new platform

                ++a; // Move to next arrival
            }
            else
            {
                // Train departs
                ++availablePlatforms; // Platform becomes free
                ++d;                  // Move to next departure
            }
        }

        return totalPlatforms;
    }
};

int main()
{
    Solution sol;

    // Example 1
    vector<int> arr1 = {900, 940, 950, 1100, 1500, 1800};
    vector<int> dep1 = {910, 1200, 1120, 1130, 1900, 2000};
    cout << "Example 1: Min platforms = " << sol.minPlatform(arr1, dep1) << endl; // Expected: 3

    // Example 2
    vector<int> arr2 = {900, 1100, 1235};
    vector<int> dep2 = {1000, 1200, 1300};
    cout << "Example 2: Min platforms = " << sol.minPlatform(arr2, dep2) << endl; // Expected: 1

    return 0;
}
