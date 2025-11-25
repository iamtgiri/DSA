/*
File: Find_median_in_a_stream.cpp
Date: 2025-11-25 07:54

Problem: Find median in a stream
Link: https://www.geeksforgeeks.org/problems/find-median-in-a-stream-1587115620/1

Problem Statement:
Given a stream of integers, find the median of the numbers added to the stream so far after each new element is introduced.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Store all incoming elements in a dynamic array (vector). After each insertion, sort the array and find the median (the middle element, or average of the two middle elements).
- Time complexity: O(N^2) overall. Each step requires O(N log N) for sorting or O(N) for insertion into a sorted array, leading to a total time complexity of O(N^2).
- Space complexity: O(N) to store the stream elements.
- Limitations: Not scalable for large data streams due to the high time complexity per operation.

Current/Optimized Approachs
- Idea: Maintain two balanced heaps to partition the elements into two halves: a smaller half (Max Heap) and a larger half (Min Heap). The median will always be at the top of one or both heaps.
- Approach: **Two Priority Queues (Heaps)**
- Algorithm:
  1. Initialize 'left' (Max Heap, stores smaller half) and 'right' (Min Heap, stores larger half).
  2. **Insertion:** For each incoming number x:
     - If 'left' is empty or x <= left.top(), push x into 'left'.
     - Otherwise, push x into 'right'.
  3. **Rebalancing:** Ensure the heaps are balanced such that left.size() is either equal to right.size() or left.size() = right.size() + 1.
     - If left.size() > right.size() + 1, move left.top() to 'right'.
     - If right.size() > left.size(), move right.top() to 'left'.
  4. **Median Calculation:**
     - If left.size() = right.size() (Even total elements), median = (left.top() + right.top()) / 2.
     - If left.size() = right.size() + 1 (Odd total elements), median = left.top().
- Time complexity: **O(N log N)** total. Each insertion/rebalancing step is **O(log N)** because it involves a constant number of heap operations (push/pop).
- Space complexity: O(N) to store all elements in the heaps.

💡 Key Pattern:
- **Two Heaps (Max/Min Heap)**: Used to efficiently calculate order statistics (like median, or k-th smallest element) in a dynamic or streaming environment where the data structure must handle continuous insertions.

ℹ️ Keywords:
- Priority Queue, Max Heap, Min Heap, Stream, Median, Order Statistics, Balanced Heaps.

🗒️ Notes
- The Max Heap ('left') holds the lower half, and the Min Heap ('right') holds the upper half. By keeping them balanced, the median is always accessible at the roots.
- C++ 'priority_queue' is a Max Heap by default. To create a Min Heap, we use 'priority_queue<int, vector<int>, greater<int>>'.
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <queue>
#include <iomanip> // for setprecision

using namespace std;

class Solution
{
public:
    /**
     * @brief Finds the running median for a stream of integers.
     * @param arr The vector containing the stream of integers.
     * @return A vector of doubles containing the median after each element insertion.
     */
    vector<double> getMedian(vector<int> &arr)
    {
        int n = arr.size();
        // Min Heap (stores the LARGER half of the elements)
        priority_queue<int, vector<int>, greater<int>> right;
        // Max Heap (stores the SMALLER half of the elements) - default in C++
        priority_queue<int> left;

        vector<double> result;
        result.reserve(n);

        for (int x : arr)
        {
            // 1. Insertion: Maintain the heap property (left <= right)
            if (left.empty() || x <= left.top())
            {
                left.push(x);
            }
            else
            {
                right.push(x);
            }

            // 2. Rebalancing: Maintain the size property (left.size() == right.size() or left.size() == right.size() + 1)

            // If left heap is too large (size difference > 1)
            if (left.size() > right.size() + 1)
            {
                // Move the largest element from left to right
                int e = left.top();
                left.pop();
                right.push(e);
            }
            // If right heap is too large (size difference > 0)
            else if (right.size() > left.size())
            {
                // Move the smallest element from right to left
                int e = right.top();
                right.pop();
                left.push(e);
            }

            // 3. Calculate Median
            if (left.size() == right.size())
            {
                // Even number of elements: median is the average of the two top elements
                double median = (double)(left.top() + right.top()) / 2.0;
                result.push_back(median);
            }
            else
            {
                // Odd number of elements: median is the top of the larger heap (which is guaranteed to be 'left')
                result.push_back((double)left.top());
            }
        }
        return result;
    }
};

// Helper function to print the results
void printResults(const vector<double> &results)
{
    cout << fixed << setprecision(1); // Set precision to 1 decimal place
    cout << "[";
    for (size_t i = 0; i < results.size(); ++i)
    {
        cout << results[i];
        if (i < results.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

int main()
{
    Solution sol;

    // Test Case 1: Simple Stream
    vector<int> arr1 = {5, 15, 1, 3};
    vector<double> res1 = sol.getMedian(arr1);
    cout << "Stream: {5, 15, 1, 3}" << endl;
    cout << "Medians: ";
    printResults(res1); // Expected: [5.0, 10.0, 5.0, 4.0]
    cout << "---" << endl;

    // Test Case 2: Larger Stream
    vector<int> arr2 = {10, 5, 2, 20, 15, 30};
    vector<double> res2 = sol.getMedian(arr2);
    cout << "Stream: {10, 5, 2, 20, 15, 30}" << endl;
    cout << "Medians: ";
    printResults(res2); // Expected: [10.0, 7.5, 5.0, 7.5, 10.0, 12.5]
    cout << "---" << endl;

    // Test Case 3: Duplicates
    vector<int> arr3 = {1, 2, 2, 3, 3, 3, 4};
    vector<double> res3 = sol.getMedian(arr3);
    cout << "Stream: {1, 2, 2, 3, 3, 3, 4}" << endl;
    cout << "Medians: ";
    printResults(res3); // Expected: [1.0, 1.5, 2.0, 2.0, 2.5, 3.0, 3.0]

    return 0;
}