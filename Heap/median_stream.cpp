/*
File: median_of_stream.cpp
Date: 2025-09-10 12:58

Problem: Median of a Stream
Link: https://leetcode.com/problems/find-median-from-data-stream/
Problem Statement:
    You are given a stream of integers. After each insertion,
    output the median of all numbers seen so far.

Example:
    Input: [5, 15, 1, 3]
    Output: 5, 10, 5, 4

-------------------------------------------------
❌ Brute Force
- Idea: Store all elements in an array, sort after each insertion,
        and compute the median.
- Time complexity: O(n log n) per insertion.
- Space complexity: O(n).
- Limitations: Too slow for large streams.

✅ Optimized Approach
- Idea: Maintain two heaps.
    * Max-heap (left half) stores smaller numbers.
    * Min-heap (right half) stores larger numbers.
    * Balance them so their sizes differ by at most 1.
    * Median is either the top of one heap or the average of both.
- Time complexity: O(log n) per insertion, O(1) for median query.
- Space complexity: O(n).

💡 Key Pattern:
- Online algorithm
- Heap (priority queue)

Keywords:
- Median, Streaming, Heaps

🗒️ Notes
- Balancing step is critical.
- Very common in coding interviews.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
    priority_queue<int> leftMax;                             // max-heap for smaller half
    priority_queue<int, vector<int>, greater<int>> rightMin; // min-heap for larger half

public:
    // Insert number into data structure
    void addNum(int num)
    {
        if (leftMax.empty() || num <= leftMax.top())
        {
            leftMax.push(num);
        }
        else
        {
            rightMin.push(num);
        }

        // Balance the heaps
        if (leftMax.size() > rightMin.size() + 1)
        {
            rightMin.push(leftMax.top());
            leftMax.pop();
        }
        else if (rightMin.size() > leftMax.size())
        {
            leftMax.push(rightMin.top());
            rightMin.pop();
        }
    }

    // Return current median
    double findMedian()
    {
        if (leftMax.size() == rightMin.size())
        {
            return (leftMax.top() + rightMin.top()) / 2.0;
        }
        return leftMax.top(); // leftMax always has >= elements
    }
};

int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    Solution sol;
    int n;
    cin >> n; // number of elements in the stream

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        sol.addNum(x);
        cout << "Median after " << (i + 1) << " elements = " << sol.findMedian() << "\n";
    }

    return 0;
}
