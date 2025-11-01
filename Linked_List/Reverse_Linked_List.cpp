/*
File: Reverse_Linked_List.cpp
Date: 2025-10-24 22:59

Problem: Reverse Linked List
Link: https://leetcode.com/problems/reverse-linked-list/description/

Problem Statement:
Given the head of a singly linked list, reverse the list, and return the reversed list.

-------------------------------------------------
❌ Brute Force
- Idea: Traverse the list, copy all values into an auxiliary structure (like a stack or vector), and then construct a new linked list by iterating through the auxiliary structure in reverse order.
- Time complexity: O(N) for traversal and O(N) for reconstruction/copy. Total O(N).
- Space complexity: O(N) to store the auxiliary data.
- Limitations: Inefficient in terms of space usage compared to the optimized in-place reversal.

✅ Optimized Approachs
- Idea: Reverse the list in-place by changing the direction of the `next` pointers as we traverse the list.
- Approach: Iterative In-place Pointer Reversal.
- Algorithm:
    1. Initialize three pointers: `prev` (to track the previously reversed node, starting at `nullptr`), `head` (to track the current node being processed), and `temp` (to temporarily store the next node before overwriting `head->next`).
    2. Iterate while `head` is not `nullptr`.
    3. Inside the loop, first store the next node: `temp = head->next;`.
    4. Reverse the current node's pointer: `head->next = prev;`.
    5. Move `prev` forward to the current node: `prev = head;`.
    6. Move `head` forward to the stored next node: `head = temp;`.
    7. Once the loop finishes, `prev` will be pointing to the former tail (which is the new head). Return `prev`.
- Time complexity: O(N), as each node is visited and its pointer is modified exactly once.
- Space complexity: O(1), as only a few constant-space pointers are used.

💡 Key Pattern:
- **Singly Linked List Reversal:** This is the quintessential iterative solution, relying on the `prev`, `curr` (renamed `head` in the code), and `temp` pointers to safely redirect links.

ℹ️ Keywords:
- Linked List, In-place Reversal, Iterative, Pointer Manipulation, O(1) Space.

🗒️ Notes
- This problem can also be solved recursively, but the iterative approach is generally preferred for its O(1) space complexity (excluding the function call stack overhead, which is O(N) for recursion).
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    /**
     * @brief Reverses a singly linked list iteratively.
     * @param head The head of the list to reverse.
     * @return The new head (the old tail).
     */
    ListNode *reverseList(ListNode *head)
    {
        ListNode *prev = nullptr;
        // The loop condition uses 'head' as the current pointer
        while (head)
        {
            // 1. Store the next node before modifying the current node's 'next' pointer
            ListNode *temp = head->next;

            // 2. Reverse the link: current node points to the previous node
            head->next = prev;

            // 3. Move 'prev' one step forward (it becomes the current node)
            prev = head;

            // 4. Move 'head' one step forward (it becomes the stored 'next' node)
            head = temp;
        }
        // 'prev' now holds the new head of the reversed list
        return prev;
    }
};

// --- Helper Functions for Test Cases ---

// Helper function to create a linked list from a vector
ListNode *createList(const vector<int> &nums)
{
    if (nums.empty())
        return nullptr;
    ListNode *head = new ListNode(nums[0]);
    ListNode *current = head;
    for (size_t i = 1; i < nums.size(); ++i)
    {
        current->next = new ListNode(nums[i]);
        current = current->next;
    }
    return head;
}

// Helper function to print a linked list (for verification)
void printList(ListNode *head)
{
    ListNode *current = head;
    while (current)
    {
        cout << current->val << (current->next ? " -> " : "");
        current = current->next;
    }
    cout << endl;
}

// Helper function to delete a linked list
void deleteList(ListNode *head)
{
    ListNode *current = head;
    while (current)
    {
        ListNode *next = current->next;
        delete current;
        current = next;
    }
}

int main()
{
    Solution sol;

    cout << "--- Reverse Linked List ---\n";

    // Test Case 1: Standard list (Odd length)
    // Input: 1 -> 2 -> 3 -> 4 -> 5
    // Expected: 5 -> 4 -> 3 -> 2 -> 1
    vector<int> nums1 = {1, 2, 3, 4, 5};
    ListNode *head1 = createList(nums1);
    cout << "Test 1 Input: ";
    printList(head1);
    head1 = sol.reverseList(head1);
    cout << "Test 1 Output (Reversed): ";
    printList(head1); // Expected: 5 -> 4 -> 3 -> 2 -> 1
    deleteList(head1);
    cout << "--------------------------------\n";

    // Test Case 2: Even length list
    // Input: 10 -> 20 -> 30 -> 40
    // Expected: 40 -> 30 -> 20 -> 10
    vector<int> nums2 = {10, 20, 30, 40};
    ListNode *head2 = createList(nums2);
    cout << "Test 2 Input: ";
    printList(head2);
    head2 = sol.reverseList(head2);
    cout << "Test 2 Output (Reversed): ";
    printList(head2); // Expected: 40 -> 30 -> 20 -> 10
    deleteList(head2);
    cout << "--------------------------------\n";

    // Test Case 3: Edge case (Single node)
    // Input: 99
    // Expected: 99
    vector<int> nums3 = {99};
    ListNode *head3 = createList(nums3);
    cout << "Test 3 Input: ";
    printList(head3);
    head3 = sol.reverseList(head3);
    cout << "Test 3 Output (Reversed): ";
    printList(head3); // Expected: 99
    deleteList(head3);
    cout << "--------------------------------\n";

    // Test Case 4: Edge case (Empty list)
    // Input: []
    // Expected: []
    vector<int> nums4 = {};
    ListNode *head4 = createList(nums4);
    cout << "Test 4 Input: ";
    printList(head4);
    head4 = sol.reverseList(head4);
    cout << "Test 4 Output (Reversed): ";
    printList(head4); // Expected: (empty)
    deleteList(head4);
    cout << "--------------------------------\n";

    return 0;
}
