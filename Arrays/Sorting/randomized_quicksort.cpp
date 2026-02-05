/*
File: randomized_quicksort.cpp
Date: 2026-02-05 11:27

Problem: Randomized Quicksort
Link: URL

Problem Statement:

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea:
- Time complexity:
- Space complexity:
- Limitations:

Current/Optimized Approachs
- Idea:
- Approach:
- Algorithm:
- Time complexity:
- Space complexity:

💡 Key Pattern:
-

ℹ️ Keywords:
-

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Randomized Quicksort function to sort an array
     * @param arr The array to be sorted
     * @param low The starting index of the array segment to be sorted
     * @param high The ending index of the array segment to be sorted
     */
    // Write your function here
    void randomizedQuicksort(vector<int> &arr, int low, int high)
    {
        if (low < high)
        {
            int pivotIndex = randomizedPartition(arr, low, high);
            randomizedQuicksort(arr, low, pivotIndex - 1);
            randomizedQuicksort(arr, pivotIndex + 1, high);
        }
    }

private:
    // Helper function to perform randomized partitioning
    int randomizedPartition(vector<int> &arr, int low, int high)
    {
        int pivotIndex = low + rand() % (high - low + 1);
        swap(arr[pivotIndex], arr[high]);
        return partition(arr, low, high);
    }
    // Standard partition function
    int partition(vector<int> &arr, int low, int high)
    {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j)
        {
            if (arr[j] < pivot)
            {
                ++i;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }
};

int main()
{
    Solution sol;
    srand(time(nullptr)); // Seed for random number generation
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    sol.randomizedQuicksort(arr, 0, n - 1);

    for (int i = 0; i < n; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";

    return 0;
}