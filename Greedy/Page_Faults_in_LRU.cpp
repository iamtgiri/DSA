/*
File: Page_Faults_in_LRU.cpp
Date: 2025-09-23 00:05

Problem: Page Faults in LRU
Link: https://www.geeksforgeeks.org/problems/page-faults-in-lru5603/1

Problem Statement:
Given a sequence of pages in an array pages[] of length N and memory capacity C,
find the number of page faults using Least Recently Used (LRU) Algorithm.
Note: Revising the OS LRU cache mechanism is recommended.

Example 1:
Input: N = 9, C = 4
pages = {5, 0, 1, 3, 2, 4, 1, 0, 5}
Output: 8
Explanation:
- First 4 pages (5,0,1,3) → all page faults = 4
- Page 2 replaces LRU (5) → page faults = 5
- Page 4 replaces LRU (0) → page faults = 6
- Page 1 already present → no fault
- Page 0 replaces LRU (3) → page faults = 7
- Page 5 replaces LRU (2) → page faults = 8

-------------------------------------------------
❌ Naive Simulation
- Idea: Maintain pages in a vector + set. On hit, move page to the back (most recent). On miss, evict from the front.
- Time complexity: O(N * C), since updating/moving takes linear time.
- Space complexity: O(C).
- Status: Passes small constraints, but inefficient for large N, C.

✅ Optimized Approach (LRU Cache with List + Hash Map)
- Idea: Use a doubly linked list + hash map for O(1) eviction and updates.
- Approach:
  1. Maintain a list<int> where front = least recent, back = most recent.
  2. Maintain unordered_map<int, list<int>::iterator> for O(1) lookup & removal.
  3. On hit: move page to the back.
  4. On miss: evict from front if full, then insert page at back.
- Time complexity: O(N).
- Space complexity: O(C).
- Status: Efficient and handles large inputs.

💡 Key Pattern:
- **LRU = Hash Map + Doubly Linked List**

ℹ️ Keywords:
- LRU, Page Replacement, Cache, Hash Map, Doubly Linked List, OS Scheduling

🗒️ Notes:
- The naive solution is useful for understanding the mechanism.
- Optimized approach is standard LRU cache design.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Naive O(N*C) simulation of LRU page faults.
     * @param N Number of pages in sequence.
     * @param C Cache capacity.
     * @param pages Page sequence array.
     * @return Total page faults.
     */
    int pageFaults(int N, int C, int pages[])
    {
        unordered_set<int> inCache; // Track presence
        vector<int> cache;          // LRU order: front = least recent, back = most recent

        int faults = 0;

        for (int i = 0; i < N; i++)
        {
            int page = pages[i];

            // Page Hit → move to back
            if (inCache.count(page))
            {
                move_last(cache, page);
            }
            // Page Fault
            else
            {
                faults++;
                if ((int)cache.size() == C)
                {
                    int evict = cache.front();
                    cache.erase(cache.begin());
                    inCache.erase(evict);
                }
                cache.push_back(page);
                inCache.insert(page);
            }
        }
        return faults;
    }

    /**
     * @brief Optimized O(N) solution using LRU cache (list + hashmap).
     * @param N Number of pages in sequence.
     * @param C Cache capacity.
     * @param pages Page sequence array.
     * @return Total page faults.
     */
    int pageFaultsOpt(int N, int C, int pages[])
    {
        list<int> lru_list;  // Front = LRU, Back = MRU
        unordered_map<int, list<int>::iterator> page_map; // page → iterator in list
        int faults = 0;

        for (int i = 0; i < N; i++)
        {
            int page = pages[i];

            // Hit → move to back
            if (page_map.find(page) != page_map.end())
            {
                lru_list.erase(page_map[page]);
                lru_list.push_back(page);
                page_map[page] = --lru_list.end();
            }
            // Fault
            else
            {
                faults++;
                if ((int)lru_list.size() == C)
                {
                    int lru_page = lru_list.front();
                    lru_list.pop_front();
                    page_map.erase(lru_page);
                }
                lru_list.push_back(page);
                page_map[page] = --lru_list.end();
            }
        }
        return faults;
    }

private:
    /// @brief Move existing element to back (for naive simulation).
    void move_last(vector<int> &arr, int val)
    {
        int n = arr.size();
        int i = 0;
        for (; i < n; i++)
        {
            if (arr[i] == val)
                break;
        }
        for (; i < n - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        arr[n - 1] = val;
    }
};

int main()
{
    Solution sol;

    // Example 1
    int N1 = 9, C1 = 4;
    int pages1[] = {5, 0, 1, 3, 2, 4, 1, 0, 5};

    cout << "Naive Approach: Page faults = " << sol.pageFaults(N1, C1, pages1) << endl;
    cout << "Optimized Approach: Page faults = " << sol.pageFaultsOpt(N1, C1, pages1) << endl;
    // Expected: 8

    return 0;
}
