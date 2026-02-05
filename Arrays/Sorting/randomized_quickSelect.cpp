/*
File: randomized_quickSelect.cpp
Date: 2026-02-05 11:35

Problem: Randomized QuickSelect
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
     * @brief Finds the median of an array using the Randomized QuickSelect algorithm
     * @param arr The input array
     * @return The median value
     */
    double find_median(vector<int> &arr)
    {
        int n = arr.size();

        if (n == 0)
            throw invalid_argument("Array is empty");

        if (n % 2 == 1)
        {
            return static_cast<double>(quick_select(arr, 0, n - 1, n / 2 + 1));
        }
        else
        {
            int leftMid = quick_select(arr, 0, n - 1, n / 2);
            int rightMid = quick_select(arr, 0, n - 1, n / 2 + 1);
            return double(leftMid + (rightMid - leftMid) / 2.0);
        }
    }

private:
    int quick_select(vector<int> &arr, int low, int high, int target)
    {
        if (low == high)
            return arr[low];

        int pivotIndex = randomized_partition(arr, low, high);
        int count = pivotIndex - low + 1;

        if (count == target)
            return arr[pivotIndex];
        else if (target < count)
            return quick_select(arr, low, pivotIndex - 1, target);
        else
            return quick_select(arr, pivotIndex + 1, high, target - count);
    }
    int randomized_partition(vector<int> &arr, int low, int high)
    {
        int pivotIndex = low + rand() % (high - low + 1);
        swap(arr[pivotIndex], arr[high]);
        return partition(arr, low, high);
    }
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
    double median = sol.find_median(arr);
    cout << "Median: " << median << "\n";

    return 0;
}