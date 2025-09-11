/*
File: 4-allocate_books.cpp
Date: 2025-09-11 11:20

Problem: Allocate Minimum Pages
Link: URL
Problem Statement:
    You are given `n` books, where `arr[i]` denotes the number of pages in the i-th book.
    You need to allocate all books to exactly `days` students (each student must get 
    at least one book). A student can only read books allocated to them sequentially.
    
    Condition:
        - Each student must read contiguous books.
        - Goal: Minimize the maximum number of pages assigned to any student.
    
    Return the minimum possible value of the maximum pages.

Example:
    Input:
        n = 4, days = 2
        arr = [12, 34, 67, 90]
    Output:
        113
    Explanation:
        Allocate [12, 34, 67] to student1 (113 pages),
                 [90] to student2 (90 pages).
        Maximum = 113 → minimized.

-------------------------------------------------
❌ Brute Force
- Idea: Try all possible partitions of books into `days` parts and take the minimum
        of the maximum pages.
- Time complexity: Exponential (O(2^N)).
- Space complexity: O(1).
- Limitations: Not feasible for large N.

✅ Optimized Approach (Binary Search on Answer)
- Idea:
    1. The answer (max pages) lies between 1 and max(arr).
    2. Use binary search to check if a given max limit is feasible 
       (i.e., can we allocate within `days` students?).
    3. Narrow search space until minimum feasible value is found.
- Time complexity: O(N log(max(arr)))
- Space complexity: O(1)

💡 Key Pattern:
- Binary search on answer
- Feasibility check function

Keywords:
- Binary search, greedy allocation, book allocation problem

🗒️ Notes
- Classic problem: "Allocate Minimum Number of Pages".
- Careful with feasibility check (rounding up pages, overflow).
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Feasibility check: can we allocate books so that no student exceeds 'mid' pages?
    bool isValid(const vector<int> &arr, int days, long long mid) {
        long long studentsRequired = 0;
        for (long long book : arr) {
            // Each book contributes ceil(book / mid) students
            studentsRequired += (book + mid - 1) / mid;
            if (studentsRequired > days) return false; // too many students needed
        }
        return true;
    }

    // Binary search on the minimum maximum pages
    int pages(const vector<int> &arr, int days) {
        long long low = 1;
        long long high = *max_element(arr.begin(), arr.end());

        while (low < high) {
            long long mid = low + (high - low) / 2;

            if (isValid(arr, days, mid))
                high = mid;    // feasible → try smaller max
            else
                low = mid + 1; // not feasible → increase limit
        }
        return (int)low;
    }
};

int main() {
    Solution sol;
    int n, days;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i];
    cin >> days;

    // Each student must get at least one book
    if (n > days) {
        cout << "Not Possible\n";
        return 0;
    }

    cout << sol.pages(arr, days) << "\n";
    return 0;
}
