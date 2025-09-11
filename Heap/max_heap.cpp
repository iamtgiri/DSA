/*
File: 0-max_heap.cpp
Date: 2025-09-11 20:10

Problem: Max Heap Implementation + HeapSort
Link: URL
Problem Statement:
    Implement a Max Heap using an array (fixed size = 1000).
    Support the following operations:
        1. insert(key)        → Insert a new element.
        2. getMax()           → Get the maximum element.
        3. extract_max()      → Remove and return the maximum element.
        4. maxheapify(i)      → Restore heap property from index i.
        5. build_heap(arr,n)  → Build a heap from an input array.
        6. increaseKey(i,k)   → Increase value at index i by k.
        7. printHeap()        → Print heap contents.
        8. heapSort(arr,n)    → Sort array using HeapSort.

Example:
    Input: arr = [8, 5, 4, 63, 14, 7, 6]
    After build_heap → [63, 14, 7, 5, 8, 4, 6]
    getMax()         → 63
    insert(999)      → Heap becomes [999, 63, 7, 14, 8, 4, 6, 5]
    increaseKey(3,500) → Heap updates accordingly
    extract_max()    → Returns 999
    heapSort(arr,n)  → Array sorted in ascending order.

-------------------------------------------------
❌ Brute Force
- Idea: On every operation, scan the array to find max.
- Time complexity:
    - insert: O(1)
    - getMax: O(N)
    - extract_max: O(N)
- Space complexity: O(1)
- Limitations: Too slow.

✅ Optimized Approach (Heap)
- Idea: Maintain a max heap.
- Time complexity:
    - insert: O(log N)
    - getMax: O(1)
    - extract_max: O(log N)
    - build_heap: O(N)
    - increaseKey: O(log N)
    - heapSort: O(N log N)
- Space complexity: O(1) (in-place).
- Benefits: Efficient for priority queue operations.

💡 Key Pattern:
- Complete Binary Tree stored in an array
- Parent-child index relationship:
    parent(i) = (i-1)/2
    left(i)   = 2*i+1
    right(i)  = 2*i+2

Keywords:
- MaxHeap, HeapSort, priority queue, binary tree

🗒️ Notes
- HeapSort is in-place but not stable.
- Good practice for implementing priority queues.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class MaxHeap
{
    int arr[1000]; // fixed size array
    int size;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

public:
    MaxHeap() : size(0) {}

    // 1. Insert
    void insert(int key)
    {
        if (size >= 1000)
        {
            cout << "Heap Overflow!\n";
            return;
        }
        int i = size++;
        arr[i] = key;

        // Bubble up
        while (i != 0 && arr[parent(i)] < arr[i])
        {
            swap(arr[i], arr[parent(i)]);
            i = parent(i);
        }
    }

    // 2. Get maximum
    int getMax()
    {
        if (size == 0)
            return -1;
        return arr[0];
    }

    // 3. Extract maximum
    int extract_max()
    {
        if (size == 0)
            return -1;
        int root = arr[0];
        arr[0] = arr[--size];
        maxheapify(0);
        return root;
    }

    // 4. MaxHeapify
    void maxheapify(int i)
    {
        int l = left(i), r = right(i), largest = i;
        if (l < size && arr[l] > arr[largest])
            largest = l;
        if (r < size && arr[r] > arr[largest])
            largest = r;
        if (largest != i)
        {
            swap(arr[i], arr[largest]);
            maxheapify(largest);
        }
    }

    // 5. Build Heap
    void build_heap(int input[], int n)
    {
        size = n;
        for (int i = 0; i < n; i++)
            arr[i] = input[i];
        for (int i = (n / 2 - 1); i >= 0; i--)
            maxheapify(i);
    }

    // 6. Increase Key
    void increaseKey(int i, int k)
    {
        if (i < 0 || i >= size)
            return;
        arr[i] += k;
        // Bubble up
        while (i != 0 && arr[parent(i)] < arr[i])
        {
            swap(arr[i], arr[parent(i)]);
            i = parent(i);
        }
    }

    // 7. Print Heap
    void printHeap()
    {
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << "\n";
    }

    // 8. HeapSort
    void heapSort(int input[], int n)
    {
        build_heap(input, n);
        for (int i = n - 1; i > 0; i--)
        {
            swap(arr[0], arr[i]);
            size--; // reduce heap size
            maxheapify(0);
        }
        // Copy back sorted array
        for (int i = 0; i < n; i++)
            input[i] = arr[i];
    }
};

int main()
{
    int arr[] = {8, 5, 4, 63, 14, 7, 6, 1, 5, 6, 7825, 9, 25, 564};
    int n = sizeof(arr) / sizeof(arr[0]);

    MaxHeap mh;
    mh.build_heap(arr, n);

    cout << "Heap built: ";
    mh.printHeap();

    cout << "Max element: " << mh.getMax() << "\n";

    mh.insert(999);
    cout << "After insert(999): ";
    mh.printHeap();

    mh.increaseKey(3, 500);
    cout << "After increaseKey(3,500): ";
    mh.printHeap();

    cout << "Extract max: " << mh.extract_max() << "\n";
    mh.printHeap();

    // HeapSort
    mh.heapSort(arr, n);
    cout << "Array after HeapSort: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";
    return 0;
}
